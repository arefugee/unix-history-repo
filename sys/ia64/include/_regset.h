/*
 * Copyright (c) 2002, 2003 Marcel Moolenaar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _MACHINE_REGSET_H_
#define	_MACHINE_REGSET_H_

/*
 * Create register sets, based on the runtime specification. This allows
 * us to better reuse code and to copy sets around more efficiently.
 * Contexts are defined in terms of these sets. These include trapframe,
 * sigframe, pcb, mcontext, reg and fpreg. Other candidates are unwind
 * and coredump related contexts.
 *
 * Notes:
 * o  Constant registers (r0, f0 and f1) are not accounted for,
 * o  The stacked registers (r32-r127) are not accounted for,
 * o  Predicates are not split across sets.
 */

/* A single FP register. */
struct _ia64_fpreg {
	unsigned char	fpr_bits[16];
} __aligned(16);

/*
 * Special registers.
 */
struct _special {
	unsigned long		sp;
	unsigned long		unat;		/* NaT before spilling */
	unsigned long		rp;
	unsigned long		pr;
	unsigned long		pfs;
	unsigned long		bspstore;
	unsigned long		rnat;
	unsigned long		__spare;
	/* Userland context and syscalls */
	unsigned long		tp;
	unsigned long		rsc;
	unsigned long		fpsr;
	unsigned long		psr;
	/* ASYNC: Interrupt specific */
	unsigned long		gp;
	unsigned long		ndirty;
	unsigned long		cfm;
	unsigned long		iip;
	unsigned long		ifa;
	unsigned long		isr;
};

struct _high_fp {
	struct _ia64_fpreg	fr32;
	struct _ia64_fpreg	fr33;
	struct _ia64_fpreg	fr34;
	struct _ia64_fpreg	fr35;
	struct _ia64_fpreg	fr36;
	struct _ia64_fpreg	fr37;
	struct _ia64_fpreg	fr38;
	struct _ia64_fpreg	fr39;
	struct _ia64_fpreg	fr40;
	struct _ia64_fpreg	fr41;
	struct _ia64_fpreg	fr42;
	struct _ia64_fpreg	fr43;
	struct _ia64_fpreg	fr44;
	struct _ia64_fpreg	fr45;
	struct _ia64_fpreg	fr46;
	struct _ia64_fpreg	fr47;
	struct _ia64_fpreg	fr48;
	struct _ia64_fpreg	fr49;
	struct _ia64_fpreg	fr50;
	struct _ia64_fpreg	fr51;
	struct _ia64_fpreg	fr52;
	struct _ia64_fpreg	fr53;
	struct _ia64_fpreg	fr54;
	struct _ia64_fpreg	fr55;
	struct _ia64_fpreg	fr56;
	struct _ia64_fpreg	fr57;
	struct _ia64_fpreg	fr58;
	struct _ia64_fpreg	fr59;
	struct _ia64_fpreg	fr60;
	struct _ia64_fpreg	fr61;
	struct _ia64_fpreg	fr62;
	struct _ia64_fpreg	fr63;
	struct _ia64_fpreg	fr64;
	struct _ia64_fpreg	fr65;
	struct _ia64_fpreg	fr66;
	struct _ia64_fpreg	fr67;
	struct _ia64_fpreg	fr68;
	struct _ia64_fpreg	fr69;
	struct _ia64_fpreg	fr70;
	struct _ia64_fpreg	fr71;
	struct _ia64_fpreg	fr72;
	struct _ia64_fpreg	fr73;
	struct _ia64_fpreg	fr74;
	struct _ia64_fpreg	fr75;
	struct _ia64_fpreg	fr76;
	struct _ia64_fpreg	fr77;
	struct _ia64_fpreg	fr78;
	struct _ia64_fpreg	fr79;
	struct _ia64_fpreg	fr80;
	struct _ia64_fpreg	fr81;
	struct _ia64_fpreg	fr82;
	struct _ia64_fpreg	fr83;
	struct _ia64_fpreg	fr84;
	struct _ia64_fpreg	fr85;
	struct _ia64_fpreg	fr86;
	struct _ia64_fpreg	fr87;
	struct _ia64_fpreg	fr88;
	struct _ia64_fpreg	fr89;
	struct _ia64_fpreg	fr90;
	struct _ia64_fpreg	fr91;
	struct _ia64_fpreg	fr92;
	struct _ia64_fpreg	fr93;
	struct _ia64_fpreg	fr94;
	struct _ia64_fpreg	fr95;
	struct _ia64_fpreg	fr96;
	struct _ia64_fpreg	fr97;
	struct _ia64_fpreg	fr98;
	struct _ia64_fpreg	fr99;
	struct _ia64_fpreg	fr100;
	struct _ia64_fpreg	fr101;
	struct _ia64_fpreg	fr102;
	struct _ia64_fpreg	fr103;
	struct _ia64_fpreg	fr104;
	struct _ia64_fpreg	fr105;
	struct _ia64_fpreg	fr106;
	struct _ia64_fpreg	fr107;
	struct _ia64_fpreg	fr108;
	struct _ia64_fpreg	fr109;
	struct _ia64_fpreg	fr110;
	struct _ia64_fpreg	fr111;
	struct _ia64_fpreg	fr112;
	struct _ia64_fpreg	fr113;
	struct _ia64_fpreg	fr114;
	struct _ia64_fpreg	fr115;
	struct _ia64_fpreg	fr116;
	struct _ia64_fpreg	fr117;
	struct _ia64_fpreg	fr118;
	struct _ia64_fpreg	fr119;
	struct _ia64_fpreg	fr120;
	struct _ia64_fpreg	fr121;
	struct _ia64_fpreg	fr122;
	struct _ia64_fpreg	fr123;
	struct _ia64_fpreg	fr124;
	struct _ia64_fpreg	fr125;
	struct _ia64_fpreg	fr126;
	struct _ia64_fpreg	fr127;
};

/*
 * Preserved registers.
 */
struct _callee_saved {
	unsigned long		unat;		/* NaT after spilling. */
	unsigned long		gr4;
	unsigned long		gr5;
	unsigned long		gr6;
	unsigned long		gr7;
	unsigned long		br1;
	unsigned long		br2;
	unsigned long		br3;
	unsigned long		br4;
	unsigned long		br5;
	unsigned long		lc;
	unsigned long		__spare;
};

struct _callee_saved_fp {
	struct _ia64_fpreg	fr2;
	struct _ia64_fpreg	fr3;
	struct _ia64_fpreg	fr4;
	struct _ia64_fpreg	fr5;
	struct _ia64_fpreg	fr16;
	struct _ia64_fpreg	fr17;
	struct _ia64_fpreg	fr18;
	struct _ia64_fpreg	fr19;
	struct _ia64_fpreg	fr20;
	struct _ia64_fpreg	fr21;
	struct _ia64_fpreg	fr22;
	struct _ia64_fpreg	fr23;
	struct _ia64_fpreg	fr24;
	struct _ia64_fpreg	fr25;
	struct _ia64_fpreg	fr26;
	struct _ia64_fpreg	fr27;
	struct _ia64_fpreg	fr28;
	struct _ia64_fpreg	fr29;
	struct _ia64_fpreg	fr30;
	struct _ia64_fpreg	fr31;
};

/*
 * Scratch registers.
 */
struct _caller_saved {
	unsigned long		unat;		/* NaT after spilling. */
	unsigned long		gr2;
	unsigned long		gr3;
	unsigned long		gr8;
	unsigned long		gr9;
	unsigned long		gr10;
	unsigned long		gr11;
	unsigned long		gr14;
	unsigned long		gr15;
	unsigned long		gr16;
	unsigned long		gr17;
	unsigned long		gr18;
	unsigned long		gr19;
	unsigned long		gr20;
	unsigned long		gr21;
	unsigned long		gr22;
	unsigned long		gr23;
	unsigned long		gr24;
	unsigned long		gr25;
	unsigned long		gr26;
	unsigned long		gr27;
	unsigned long		gr28;
	unsigned long		gr29;
	unsigned long		gr30;
	unsigned long		gr31;
	unsigned long		br6;
	unsigned long		br7;
	unsigned long		ccv;
	unsigned long		csd;
	unsigned long		ssd;
};

struct _caller_saved_fp {
	struct _ia64_fpreg	fr6;
	struct _ia64_fpreg	fr7;
	struct _ia64_fpreg	fr8;
	struct _ia64_fpreg	fr9;
	struct _ia64_fpreg	fr10;
	struct _ia64_fpreg	fr11;
	struct _ia64_fpreg	fr12;
	struct _ia64_fpreg	fr13;
	struct _ia64_fpreg	fr14;
	struct _ia64_fpreg	fr15;
};

#ifdef _KERNEL
void	restore_callee_saved(const struct _callee_saved *);
void	restore_callee_saved_fp(const struct _callee_saved_fp *);
void	restore_high_fp(const struct _high_fp *);
void	save_callee_saved(struct _callee_saved *);
void	save_callee_saved_fp(struct _callee_saved_fp *);
void	save_high_fp(struct _high_fp *);
#endif

#endif	/* _MACHINE_REGSET_H_ */
