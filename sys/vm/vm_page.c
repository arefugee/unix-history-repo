/* 
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)vm_page.c	7.4 (Berkeley) 5/7/91
 *	$Id: vm_page.c,v 1.7 1994/09/27 19:34:16 davidg Exp $
 */

/*
 * Copyright (c) 1987, 1990 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Authors: Avadis Tevanian, Jr., Michael Wayne Young
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

/*
 *	Resident memory management module.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>

#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_map.h>
#include <vm/vm_pageout.h>

/*
 *	Associated with page of user-allocatable memory is a
 *	page structure.
 */

struct pglist	*vm_page_buckets;		/* Array of buckets */
int		vm_page_bucket_count = 0;	/* How big is array? */
int		vm_page_hash_mask;		/* Mask for hash function */
simple_lock_data_t	bucket_lock;		/* lock for all buckets XXX */

struct pglist	vm_page_queue_free;
struct pglist	vm_page_queue_active;
struct pglist	vm_page_queue_inactive;
simple_lock_data_t	vm_page_queue_lock;
simple_lock_data_t	vm_page_queue_free_lock;

/* has physical page allocation been initialized? */
boolean_t vm_page_startup_initialized;

vm_page_t	vm_page_array;
long		first_page;
long		last_page;
vm_offset_t	first_phys_addr;
vm_offset_t	last_phys_addr;
vm_size_t	page_mask;
int		page_shift;

/*
 *	vm_set_page_size:
 *
 *	Sets the page size, perhaps based upon the memory
 *	size.  Must be called before any use of page-size
 *	dependent functions.
 *
 *	Sets page_shift and page_mask from cnt.v_page_size.
 */
void vm_set_page_size()
{

	if (cnt.v_page_size == 0)
		cnt.v_page_size = DEFAULT_PAGE_SIZE;
	page_mask = cnt.v_page_size - 1;
	if ((page_mask & cnt.v_page_size) != 0)
		panic("vm_set_page_size: page size not a power of two");
	for (page_shift = 0; ; page_shift++)
		if ((1 << page_shift) == cnt.v_page_size)
			break;
}

/*
 *	vm_page_startup:
 *
 *	Initializes the resident memory module.
 *
 *	Allocates memory for the page cells, and
 *	for the object/offset-to-page hash table headers.
 *	Each page cell is initialized and placed on the free list.
 */

vm_offset_t
vm_page_startup(starta, enda, vaddr)
	register vm_offset_t	starta;
	vm_offset_t	enda;
	register vm_offset_t	vaddr;
{
	register vm_offset_t	mapped;
	register vm_page_t	m;
	register struct pglist *bucket;
	vm_size_t		npages, page_range;
	register vm_offset_t	new_start;
	int			i;
	vm_offset_t		pa;
	int nblocks;
	vm_offset_t		first_managed_page;
	int			size;

	extern	vm_offset_t	kentry_data;
	extern	vm_size_t	kentry_data_size;
	extern vm_offset_t phys_avail[];
/* the biggest memory array is the second group of pages */
	vm_offset_t start;
	vm_offset_t biggestone, biggestsize;

	vm_offset_t total;

	total = 0;
	biggestsize = 0;
	biggestone = 0;
	nblocks = 0;
	vaddr = round_page(vaddr);

	for (i = 0; phys_avail[i + 1]; i += 2) {
		phys_avail[i] = round_page(phys_avail[i]);
		phys_avail[i+1] = trunc_page(phys_avail[i+1]);
	}
		
	for (i = 0; phys_avail[i + 1]; i += 2) {
		int size = phys_avail[i+1] - phys_avail[i];
		if (size > biggestsize) {
			biggestone = i;
			biggestsize = size;
		}
		++nblocks;
		total += size;
	}

	start = phys_avail[biggestone];


	/*
	 *	Initialize the locks
	 */

	simple_lock_init(&vm_page_queue_free_lock);
	simple_lock_init(&vm_page_queue_lock);

	/*
	 *	Initialize the queue headers for the free queue,
	 *	the active queue and the inactive queue.
	 */

	TAILQ_INIT(&vm_page_queue_free);
	TAILQ_INIT(&vm_page_queue_active);
	TAILQ_INIT(&vm_page_queue_inactive);

	/*
	 *	Allocate (and initialize) the hash table buckets.
	 *
	 *	The number of buckets MUST BE a power of 2, and
	 *	the actual value is the next power of 2 greater
	 *	than the number of physical pages in the system.
	 *
	 *	Note:
	 *		This computation can be tweaked if desired.
	 */
	vm_page_buckets = (struct pglist *)vaddr;
	bucket = vm_page_buckets;
	if (vm_page_bucket_count == 0) {
		vm_page_bucket_count = 1;
		while (vm_page_bucket_count < atop(total))
			vm_page_bucket_count <<= 1;
	}


	vm_page_hash_mask = vm_page_bucket_count - 1;

	/*
	 *	Validate these addresses.
	 */

	new_start = start + vm_page_bucket_count * sizeof(struct pglist);
	new_start = round_page(new_start);
	mapped = vaddr;
	vaddr = pmap_map(mapped, start, new_start,
			VM_PROT_READ|VM_PROT_WRITE);
	start = new_start;
	bzero((caddr_t) mapped, vaddr - mapped);
	mapped = vaddr;

	for (i = 0; i< vm_page_bucket_count; i++) {
		TAILQ_INIT(bucket);
		bucket++;
	}

	simple_lock_init(&bucket_lock);

	/*
	 *	round (or truncate) the addresses to our page size.
	 */

	/*
	 *	Pre-allocate maps and map entries that cannot be dynamically
	 *	allocated via malloc().  The maps include the kernel_map and
	 *	kmem_map which must be initialized before malloc() will
	 *	work (obviously).  Also could include pager maps which would
	 *	be allocated before kmeminit.
	 *
	 *	Allow some kernel map entries... this should be plenty
	 *	since people shouldn't be cluttering up the kernel
	 *	map (they should use their own maps).
	 */

	kentry_data_size = MAX_KMAP * sizeof(struct vm_map) +
			   MAX_KMAPENT * sizeof(struct vm_map_entry);
	kentry_data_size = round_page(kentry_data_size);
	kentry_data = (vm_offset_t) vaddr;
	vaddr += kentry_data_size;

	/*
	 *	Validate these zone addresses.
	 */

	new_start = start + (vaddr - mapped);
	pmap_map(mapped, start, new_start, VM_PROT_READ|VM_PROT_WRITE);
	bzero((caddr_t) mapped, (vaddr - mapped));
	start = round_page(new_start);

	/*
 	 *	Compute the number of pages of memory that will be
	 *	available for use (taking into account the overhead
	 *	of a page structure per page).
	 */

	npages = (total - (start - phys_avail[biggestone])) / (PAGE_SIZE + sizeof(struct vm_page));
	first_page = phys_avail[0] / PAGE_SIZE;

	page_range = (phys_avail[(nblocks-1)*2 + 1] - phys_avail[0]) / PAGE_SIZE;
	/*
	 *	Initialize the mem entry structures now, and
	 *	put them in the free queue.
	 */

	vm_page_array = (vm_page_t) vaddr;
	mapped = vaddr;


	/*
	 *	Validate these addresses.
	 */

	new_start = round_page(start + page_range * sizeof (struct vm_page));
	mapped = pmap_map(mapped, start, new_start,
			VM_PROT_READ|VM_PROT_WRITE);
	start = new_start;

	first_managed_page = start / PAGE_SIZE;

	/*
	 *	Clear all of the page structures
	 */
	bzero((caddr_t)vm_page_array, page_range * sizeof(struct vm_page));

	cnt.v_page_count = 0;
	cnt.v_free_count= 0;
	for (i = 0; phys_avail[i + 1] && npages > 0; i += 2) {
		if (i == biggestone) 
			pa = ptoa(first_managed_page);
		else
			pa = phys_avail[i];
		while (pa < phys_avail[i + 1] && npages-- > 0) {
			++cnt.v_page_count;
			++cnt.v_free_count;
			m = PHYS_TO_VM_PAGE(pa);
			m->flags = PG_CLEAN | PG_FREE;
			m->object = 0;
			m->phys_addr = pa;
			m->hold_count = 0;
			TAILQ_INSERT_TAIL(&vm_page_queue_free, m, pageq);
			pa += PAGE_SIZE;
		}
	}

	/*
	 *	Initialize vm_pages_needed lock here - don't wait for pageout
	 *	daemon	XXX
	 */
	simple_lock_init(&vm_pages_needed_lock);

	return(mapped);
}

/*
 *	vm_page_hash:
 *
 *	Distributes the object/offset key pair among hash buckets.
 *
 *	NOTE:  This macro depends on vm_page_bucket_count being a power of 2.
 */
inline const int
vm_page_hash(object, offset)
	vm_object_t object;
	vm_offset_t offset;
{
	return ((unsigned)object + offset/NBPG) & vm_page_hash_mask;
}

/*
 *	vm_page_insert:		[ internal use only ]
 *
 *	Inserts the given mem entry into the object/object-page
 *	table and object list.
 *
 *	The object and page must be locked.
 */

void vm_page_insert(mem, object, offset)
	register vm_page_t	mem;
	register vm_object_t	object;
	register vm_offset_t	offset;
{
	register struct pglist	*bucket;
	int			s;

	VM_PAGE_CHECK(mem);

	if (mem->flags & PG_TABLED)
		panic("vm_page_insert: already inserted");

	/*
	 *	Record the object/offset pair in this page
	 */

	mem->object = object;
	mem->offset = offset;

	/*
	 *	Insert it into the object_object/offset hash table
	 */

	bucket = &vm_page_buckets[vm_page_hash(object, offset)];
	s = splhigh();
	simple_lock(&bucket_lock);
	TAILQ_INSERT_TAIL(bucket, mem, hashq);
	simple_unlock(&bucket_lock);
	(void) splx(s);

	/*
	 *	Now link into the object's list of backed pages.
	 */

	TAILQ_INSERT_TAIL(&object->memq, mem, listq);
	mem->flags |= PG_TABLED;

	/*
	 *	And show that the object has one more resident
	 *	page.
	 */

	object->resident_page_count++;
}

/*
 *	vm_page_remove:		[ internal use only ]
 *				NOTE: used by device pager as well -wfj
 *
 *	Removes the given mem entry from the object/offset-page
 *	table and the object page list.
 *
 *	The object and page must be locked.
 */

void vm_page_remove(mem)
	register vm_page_t	mem;
{
	register struct pglist	*bucket;
	int			s;

	VM_PAGE_CHECK(mem);

	if (!(mem->flags & PG_TABLED))
		return;

	/*
	 *	Remove from the object_object/offset hash table
	 */

	bucket = &vm_page_buckets[vm_page_hash(mem->object, mem->offset)];
	s = splhigh();
	simple_lock(&bucket_lock);
	TAILQ_REMOVE(bucket, mem, hashq);
	simple_unlock(&bucket_lock);
	(void) splx(s);

	/*
	 *	Now remove from the object's list of backed pages.
	 */

	TAILQ_REMOVE(&mem->object->memq, mem, listq);

	/*
	 *	And show that the object has one fewer resident
	 *	page.
	 */

	mem->object->resident_page_count--;

	mem->flags &= ~PG_TABLED;
}

/*
 *	vm_page_lookup:
 *
 *	Returns the page associated with the object/offset
 *	pair specified; if none is found, NULL is returned.
 *
 *	The object must be locked.  No side effects.
 */

vm_page_t vm_page_lookup(object, offset)
	register vm_object_t	object;
	register vm_offset_t	offset;
{
	register vm_page_t	mem;
	register struct pglist	*bucket;
	int			s;

	/*
	 *	Search the hash table for this object/offset pair
	 */

	bucket = &vm_page_buckets[vm_page_hash(object, offset)];

	s = splhigh();
	simple_lock(&bucket_lock);
	for (mem = bucket->tqh_first; mem != NULL; mem = mem->hashq.tqe_next) {
		VM_PAGE_CHECK(mem);
		if ((mem->object == object) && (mem->offset == offset)) {
			simple_unlock(&bucket_lock);
			splx(s);
			return(mem);
		}
	}

	simple_unlock(&bucket_lock);
	splx(s);
	return(NULL);
}

/*
 *	vm_page_rename:
 *
 *	Move the given memory entry from its
 *	current object to the specified target object/offset.
 *
 *	The object must be locked.
 */
void vm_page_rename(mem, new_object, new_offset)
	register vm_page_t	mem;
	register vm_object_t	new_object;
	vm_offset_t		new_offset;
{
	if (mem->object == new_object)
		return;

	vm_page_lock_queues();	/* keep page from moving out from
				   under pageout daemon */
    	vm_page_remove(mem);
	vm_page_insert(mem, new_object, new_offset);
	vm_page_unlock_queues();
}

/*
 *	vm_page_alloc:
 *
 *	Allocate and return a memory cell associated
 *	with this VM object/offset pair.
 *
 *	Object must be locked.
 */
vm_page_t
vm_page_alloc(object, offset)
	vm_object_t	object;
	vm_offset_t	offset;
{
	register vm_page_t	mem;
	int		s;

	s = splhigh();
	simple_lock(&vm_page_queue_free_lock);
	if (	object != kernel_object &&
		object != kmem_object	&&
		curproc != pageproc && curproc != &proc0 &&
		cnt.v_free_count < cnt.v_free_reserved) {

		simple_unlock(&vm_page_queue_free_lock);
		splx(s);
		/*
		 * this wakeup seems unnecessary, but there is code that
		 * might just check to see if there are free pages, and
		 * punt if there aren't.  VM_WAIT does this too, but
		 * redundant wakeups aren't that bad...
		 */
		if (curproc != pageproc)
			wakeup((caddr_t) &vm_pages_needed);
		return(NULL);
	}
	if (( mem = vm_page_queue_free.tqh_first) == 0) {
		simple_unlock(&vm_page_queue_free_lock);
		printf("No pages???\n");
		splx(s);
		/*
		 * comment above re: wakeups applies here too...
		 */
		if (curproc != pageproc)
			wakeup((caddr_t) &vm_pages_needed);
		return(NULL);
	}

	TAILQ_REMOVE(&vm_page_queue_free, mem, pageq);

	cnt.v_free_count--;
	simple_unlock(&vm_page_queue_free_lock);

	VM_PAGE_INIT(mem, object, offset);
	splx(s);

/*
 * don't wakeup too often, so we wakeup the pageout daemon when
 * we would be nearly out of memory.
 */
	if (curproc != pageproc &&
		(cnt.v_free_count < cnt.v_free_reserved))
		wakeup((caddr_t) &vm_pages_needed);

	return(mem);
}

vm_offset_t
vm_page_alloc_contig(size, low, high, alignment)
	vm_offset_t	size;
	vm_offset_t	low;
	vm_offset_t	high;
	vm_offset_t	alignment;
{
	int i, s, start = 0;
	vm_offset_t addr, phys, tmp_addr;
	vm_page_t pga = vm_page_array;
	extern vm_map_t kernel_map;

	if ((alignment & (alignment - 1)) != 0)
		panic("vm_page_alloc_contig: alignment must be a power of 2");

	s = splhigh();
again:
	/*
	 * Find first page in array that is free, within range, and aligned.
	 */
	for (i = start; i < cnt.v_page_count; i++) {
		phys = VM_PAGE_TO_PHYS(&pga[i]);
		if (((pga[i].flags & PG_FREE) == PG_FREE) &&
		    (phys >= low) && (phys < high) &&
		    ((phys & (alignment - 1)) == 0))
			break;
	}

	/*
	 * If the above failed or we will exceed the upper bound, fail.
	 */
	if ((i == cnt.v_page_count) || ((VM_PAGE_TO_PHYS(&pga[i]) + size) > high)) {
		splx(s);
		return (NULL);
	}

	start = i;

	/*
	 * Check successive pages for contiguous and free.
	 */
	for (i = start + 1; i < (start + size / PAGE_SIZE); i++) {
		if ((VM_PAGE_TO_PHYS(&pga[i]) !=
		    (VM_PAGE_TO_PHYS(&pga[i - 1]) + PAGE_SIZE)) ||
		    ((pga[i].flags & PG_FREE) != PG_FREE)) {
			start++;
			goto again;
		}
	}

	/*
	 * We've found a contiguous chunk that meets are requirements.
	 * Allocate kernel VM, unfree and assign the physical pages to it
	 * and return kernel VM pointer.
	 */
	tmp_addr = addr = kmem_alloc_pageable(kernel_map, size);

	for (i = start; i < (start + size / PAGE_SIZE); i++) {
		TAILQ_REMOVE(&vm_page_queue_free, &pga[i], pageq);
		cnt.v_free_count--;
		vm_page_wire(&pga[i]);
		pga[i].flags = PG_CLEAN; /* shut off PG_FREE and any other flags */
		pmap_kenter(tmp_addr, VM_PAGE_TO_PHYS(&pga[i]));
		tmp_addr += PAGE_SIZE;
	}
	
	splx(s);
	return (addr);
}

/*
 *	vm_page_free:
 *
 *	Returns the given page to the free list,
 *	disassociating it with any VM object.
 *
 *	Object and page must be locked prior to entry.
 */
void vm_page_free(mem)
	register vm_page_t	mem;
{
	int s;
	s = splhigh();
	vm_page_remove(mem);
	if (mem->flags & PG_ACTIVE) {
		TAILQ_REMOVE(&vm_page_queue_active, mem, pageq);
		mem->flags &= ~PG_ACTIVE;
		cnt.v_active_count--;
	}

	if (mem->flags & PG_INACTIVE) {
		TAILQ_REMOVE(&vm_page_queue_inactive, mem, pageq);
		mem->flags &= ~PG_INACTIVE;
		cnt.v_inactive_count--;
	}
	if (mem->flags & PG_FREE)
		panic("vm_page_free: freeing free page");

	if (!(mem->flags & PG_FICTITIOUS)) {

		simple_lock(&vm_page_queue_free_lock);
		if (mem->wire_count) {
			if (mem->wire_count > 1) {
				printf("vm_page_free: wire count > 1 (%d)", mem->wire_count);
				panic("vm_page_free: invalid wire count");
			}
			cnt.v_wire_count--;
			mem->wire_count = 0;
		}

		mem->flags |= PG_FREE;
		TAILQ_INSERT_TAIL(&vm_page_queue_free, mem, pageq);

		cnt.v_free_count++;
		simple_unlock(&vm_page_queue_free_lock);
		splx(s);
		/*
		 * if pageout daemon needs pages, then tell it that there
		 * are some free.
		 */
		if (vm_pageout_pages_needed)
			wakeup((caddr_t)&vm_pageout_pages_needed);

		/*
		 * wakeup processes that are waiting on memory if we
		 * hit a high water mark.
		 */
		if (cnt.v_free_count == cnt.v_free_min) {
			wakeup((caddr_t)&cnt.v_free_count); 
		}
		
		/*
		 * wakeup scheduler process if we have lots of memory.
		 * this process will swapin processes.
		 */
		if (cnt.v_free_count == cnt.v_free_target) {
			wakeup((caddr_t)&proc0);
		}
	} else {
		splx(s);
	}
	wakeup((caddr_t) mem);
}


/*
 *	vm_page_wire:
 *
 *	Mark this page as wired down by yet
 *	another map, removing it from paging queues
 *	as necessary.
 *
 *	The page queues must be locked.
 */
void vm_page_wire(mem)
	register vm_page_t	mem;
{
	int s;
	VM_PAGE_CHECK(mem);

	if (mem->wire_count == 0) {
		s = splhigh();
		if (mem->flags & PG_ACTIVE) {
			TAILQ_REMOVE(&vm_page_queue_active, mem, pageq);
			cnt.v_active_count--;
			mem->flags &= ~PG_ACTIVE;
		}
		if (mem->flags & PG_INACTIVE) {
			TAILQ_REMOVE(&vm_page_queue_inactive, mem, pageq);
			cnt.v_inactive_count--;
			mem->flags &= ~PG_INACTIVE;
		}
		splx(s);
		cnt.v_wire_count++;
	}
	mem->wire_count++;
}

/*
 *	vm_page_unwire:
 *
 *	Release one wiring of this page, potentially
 *	enabling it to be paged again.
 *
 *	The page queues must be locked.
 */
void vm_page_unwire(mem)
	register vm_page_t	mem;
{
	int s;
	VM_PAGE_CHECK(mem);

	s = splhigh();

	if( mem->wire_count)
		mem->wire_count--;
	if (mem->wire_count == 0) {
		TAILQ_INSERT_TAIL(&vm_page_queue_active, mem, pageq);
		cnt.v_active_count++;
		mem->flags |= PG_ACTIVE;
		cnt.v_wire_count--;
	}
	splx(s);
}

/*
 *	vm_page_deactivate:
 *
 *	Returns the given page to the inactive list,
 *	indicating that no physical maps have access
 *	to this page.  [Used by the physical mapping system.]
 *
 *	The page queues must be locked.
 */
void
vm_page_deactivate(m)
	register vm_page_t	m;
{
	int spl;
	VM_PAGE_CHECK(m);

	/*
	 *	Only move active pages -- ignore locked or already
	 *	inactive ones.
	 *
	 *	XXX: sometimes we get pages which aren't wired down
	 *	or on any queue - we need to put them on the inactive
	 *	queue also, otherwise we lose track of them.
	 *	Paul Mackerras (paulus@cs.anu.edu.au) 9-Jan-93.
	 */

	spl = splhigh();
	if (!(m->flags & PG_INACTIVE) && m->wire_count == 0 &&
		m->hold_count == 0) {

		pmap_clear_reference(VM_PAGE_TO_PHYS(m));
		if (m->flags & PG_ACTIVE) {
			TAILQ_REMOVE(&vm_page_queue_active, m, pageq);
			m->flags &= ~PG_ACTIVE;
			cnt.v_active_count--;
		}
		TAILQ_INSERT_TAIL(&vm_page_queue_inactive, m, pageq);
		m->flags |= PG_INACTIVE;
		cnt.v_inactive_count++;
#define NOT_DEACTIVATE_PROTECTS 
#ifndef NOT_DEACTIVATE_PROTECTS
		pmap_page_protect(VM_PAGE_TO_PHYS(m), VM_PROT_NONE);
#else
		if ((m->flags & PG_CLEAN) &&
			pmap_is_modified(VM_PAGE_TO_PHYS(m)))
			m->flags &= ~PG_CLEAN;
#endif
		if ((m->flags & PG_CLEAN) == 0)
			m->flags |= PG_LAUNDRY;
	} 
	splx(spl);
}
/*
 *	vm_page_activate:
 *
 *	Put the specified page on the active list (if appropriate).
 *
 *	The page queues must be locked.
 */

void vm_page_activate(m)
	register vm_page_t	m;
{
	int s;
	VM_PAGE_CHECK(m);

	s = splhigh();
	if (m->flags & PG_INACTIVE) {
		TAILQ_REMOVE(&vm_page_queue_inactive, m, pageq);
		cnt.v_inactive_count--;
		m->flags &= ~PG_INACTIVE;
	}
	if (m->wire_count == 0) {
		if (m->flags & PG_ACTIVE)
			panic("vm_page_activate: already active");

		TAILQ_INSERT_TAIL(&vm_page_queue_active, m, pageq);
		m->flags |= PG_ACTIVE;
		TAILQ_REMOVE(&m->object->memq, m, listq);
		TAILQ_INSERT_TAIL(&m->object->memq, m, listq);
		m->act_count = 1;
		cnt.v_active_count++;
	}
	splx(s);
}

/*
 *	vm_page_zero_fill:
 *
 *	Zero-fill the specified page.
 *	Written as a standard pagein routine, to
 *	be used by the zero-fill object.
 */

boolean_t
vm_page_zero_fill(m)
	vm_page_t	m;
{
	VM_PAGE_CHECK(m);

	pmap_zero_page(VM_PAGE_TO_PHYS(m));
	return(TRUE);
}

/*
 *	vm_page_copy:
 *
 *	Copy one page to another
 */
void
vm_page_copy(src_m, dest_m)
	vm_page_t	src_m;
	vm_page_t	dest_m;
{
	VM_PAGE_CHECK(src_m);
	VM_PAGE_CHECK(dest_m);

	pmap_copy_page(VM_PAGE_TO_PHYS(src_m), VM_PAGE_TO_PHYS(dest_m));
}
