/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 * created from FreeBSD: src/sys/i386/linux/syscalls.master,v 1.58 2004/09/06 09:32:59 dfr Exp 
 */

#include "opt_compat.h"
#include <sys/param.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>
#include <i386/linux/linux.h>
#include <i386/linux/linux_proto.h>

#define AS(name) (sizeof(struct name) / sizeof(register_t))

/* The casts are bogus but will do for now. */
struct sysent linux_sysent[] = {
	{ 0, (sy_call_t *)nosys },			/* 0 = setup */
	{ SYF_MPSAFE | AS(sys_exit_args), (sy_call_t *)sys_exit },	/* 1 = exit */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_fork },	/* 2 = linux_fork */
	{ SYF_MPSAFE | AS(read_args), (sy_call_t *)read },	/* 3 = read */
	{ SYF_MPSAFE | AS(write_args), (sy_call_t *)write },	/* 4 = write */
	{ AS(linux_open_args), (sy_call_t *)linux_open },	/* 5 = linux_open */
	{ SYF_MPSAFE | AS(close_args), (sy_call_t *)close },	/* 6 = close */
	{ SYF_MPSAFE | AS(linux_waitpid_args), (sy_call_t *)linux_waitpid },	/* 7 = linux_waitpid */
	{ AS(linux_creat_args), (sy_call_t *)linux_creat },	/* 8 = linux_creat */
	{ AS(linux_link_args), (sy_call_t *)linux_link },	/* 9 = linux_link */
	{ AS(linux_unlink_args), (sy_call_t *)linux_unlink },	/* 10 = linux_unlink */
	{ AS(linux_execve_args), (sy_call_t *)linux_execve },	/* 11 = linux_execve */
	{ AS(linux_chdir_args), (sy_call_t *)linux_chdir },	/* 12 = linux_chdir */
	{ AS(linux_time_args), (sy_call_t *)linux_time },	/* 13 = linux_time */
	{ AS(linux_mknod_args), (sy_call_t *)linux_mknod },	/* 14 = linux_mknod */
	{ AS(linux_chmod_args), (sy_call_t *)linux_chmod },	/* 15 = linux_chmod */
	{ AS(linux_lchown16_args), (sy_call_t *)linux_lchown16 },	/* 16 = linux_lchown16 */
	{ 0, (sy_call_t *)nosys },			/* 17 = break */
	{ AS(linux_stat_args), (sy_call_t *)linux_stat },	/* 18 = linux_stat */
	{ AS(linux_lseek_args), (sy_call_t *)linux_lseek },	/* 19 = linux_lseek */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_getpid },	/* 20 = linux_getpid */
	{ AS(linux_mount_args), (sy_call_t *)linux_mount },	/* 21 = linux_mount */
	{ AS(linux_oldumount_args), (sy_call_t *)linux_oldumount },	/* 22 = linux_oldumount */
	{ SYF_MPSAFE | AS(linux_setuid16_args), (sy_call_t *)linux_setuid16 },	/* 23 = linux_setuid16 */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_getuid16 },	/* 24 = linux_getuid16 */
	{ 0, (sy_call_t *)linux_stime },		/* 25 = linux_stime */
	{ SYF_MPSAFE | AS(linux_ptrace_args), (sy_call_t *)linux_ptrace },	/* 26 = linux_ptrace */
	{ AS(linux_alarm_args), (sy_call_t *)linux_alarm },	/* 27 = linux_alarm */
	{ AS(linux_fstat_args), (sy_call_t *)linux_fstat },	/* 28 = linux_fstat */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_pause },	/* 29 = linux_pause */
	{ AS(linux_utime_args), (sy_call_t *)linux_utime },	/* 30 = linux_utime */
	{ 0, (sy_call_t *)nosys },			/* 31 = stty */
	{ 0, (sy_call_t *)nosys },			/* 32 = gtty */
	{ AS(linux_access_args), (sy_call_t *)linux_access },	/* 33 = linux_access */
	{ SYF_MPSAFE | AS(linux_nice_args), (sy_call_t *)linux_nice },	/* 34 = linux_nice */
	{ 0, (sy_call_t *)nosys },			/* 35 = ftime */
	{ 0, (sy_call_t *)sync },			/* 36 = sync */
	{ SYF_MPSAFE | AS(linux_kill_args), (sy_call_t *)linux_kill },	/* 37 = linux_kill */
	{ AS(linux_rename_args), (sy_call_t *)linux_rename },	/* 38 = linux_rename */
	{ AS(linux_mkdir_args), (sy_call_t *)linux_mkdir },	/* 39 = linux_mkdir */
	{ AS(linux_rmdir_args), (sy_call_t *)linux_rmdir },	/* 40 = linux_rmdir */
	{ SYF_MPSAFE | AS(dup_args), (sy_call_t *)dup },	/* 41 = dup */
	{ SYF_MPSAFE | AS(linux_pipe_args), (sy_call_t *)linux_pipe },	/* 42 = linux_pipe */
	{ AS(linux_times_args), (sy_call_t *)linux_times },	/* 43 = linux_times */
	{ 0, (sy_call_t *)nosys },			/* 44 = prof */
	{ AS(linux_brk_args), (sy_call_t *)linux_brk },	/* 45 = linux_brk */
	{ SYF_MPSAFE | AS(linux_setgid16_args), (sy_call_t *)linux_setgid16 },	/* 46 = linux_setgid16 */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_getgid16 },	/* 47 = linux_getgid16 */
	{ SYF_MPSAFE | AS(linux_signal_args), (sy_call_t *)linux_signal },	/* 48 = linux_signal */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_geteuid16 },	/* 49 = linux_geteuid16 */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_getegid16 },	/* 50 = linux_getegid16 */
	{ SYF_MPSAFE | AS(acct_args), (sy_call_t *)acct },	/* 51 = acct */
	{ AS(linux_umount_args), (sy_call_t *)linux_umount },	/* 52 = linux_umount */
	{ 0, (sy_call_t *)nosys },			/* 53 = lock */
	{ AS(linux_ioctl_args), (sy_call_t *)linux_ioctl },	/* 54 = linux_ioctl */
	{ SYF_MPSAFE | AS(linux_fcntl_args), (sy_call_t *)linux_fcntl },	/* 55 = linux_fcntl */
	{ 0, (sy_call_t *)nosys },			/* 56 = mpx */
	{ SYF_MPSAFE | AS(setpgid_args), (sy_call_t *)setpgid },	/* 57 = setpgid */
	{ 0, (sy_call_t *)nosys },			/* 58 = ulimit */
	{ 0, (sy_call_t *)linux_olduname },		/* 59 = linux_olduname */
	{ SYF_MPSAFE | AS(umask_args), (sy_call_t *)umask },	/* 60 = umask */
	{ AS(chroot_args), (sy_call_t *)chroot },	/* 61 = chroot */
	{ AS(linux_ustat_args), (sy_call_t *)linux_ustat },	/* 62 = linux_ustat */
	{ SYF_MPSAFE | AS(dup2_args), (sy_call_t *)dup2 },	/* 63 = dup2 */
	{ SYF_MPSAFE | 0, (sy_call_t *)getppid },	/* 64 = getppid */
	{ SYF_MPSAFE | 0, (sy_call_t *)getpgrp },	/* 65 = getpgrp */
	{ SYF_MPSAFE | 0, (sy_call_t *)setsid },	/* 66 = setsid */
	{ SYF_MPSAFE | AS(linux_sigaction_args), (sy_call_t *)linux_sigaction },	/* 67 = linux_sigaction */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_sgetmask },	/* 68 = linux_sgetmask */
	{ SYF_MPSAFE | AS(linux_ssetmask_args), (sy_call_t *)linux_ssetmask },	/* 69 = linux_ssetmask */
	{ SYF_MPSAFE | AS(linux_setreuid16_args), (sy_call_t *)linux_setreuid16 },	/* 70 = linux_setreuid16 */
	{ SYF_MPSAFE | AS(linux_setregid16_args), (sy_call_t *)linux_setregid16 },	/* 71 = linux_setregid16 */
	{ SYF_MPSAFE | AS(linux_sigsuspend_args), (sy_call_t *)linux_sigsuspend },	/* 72 = linux_sigsuspend */
	{ SYF_MPSAFE | AS(linux_sigpending_args), (sy_call_t *)linux_sigpending },	/* 73 = linux_sigpending */
	{ SYF_MPSAFE | AS(sethostname_args), (sy_call_t *)osethostname },	/* 74 = osethostname */
	{ SYF_MPSAFE | AS(linux_setrlimit_args), (sy_call_t *)linux_setrlimit },	/* 75 = linux_setrlimit */
	{ SYF_MPSAFE | AS(linux_old_getrlimit_args), (sy_call_t *)linux_old_getrlimit },	/* 76 = linux_old_getrlimit */
	{ SYF_MPSAFE | AS(getrusage_args), (sy_call_t *)getrusage },	/* 77 = getrusage */
	{ SYF_MPSAFE | AS(gettimeofday_args), (sy_call_t *)gettimeofday },	/* 78 = gettimeofday */
	{ SYF_MPSAFE | AS(settimeofday_args), (sy_call_t *)settimeofday },	/* 79 = settimeofday */
	{ SYF_MPSAFE | AS(linux_getgroups16_args), (sy_call_t *)linux_getgroups16 },	/* 80 = linux_getgroups16 */
	{ SYF_MPSAFE | AS(linux_setgroups16_args), (sy_call_t *)linux_setgroups16 },	/* 81 = linux_setgroups16 */
	{ AS(linux_old_select_args), (sy_call_t *)linux_old_select },	/* 82 = linux_old_select */
	{ AS(linux_symlink_args), (sy_call_t *)linux_symlink },	/* 83 = linux_symlink */
	{ AS(ostat_args), (sy_call_t *)ostat },		/* 84 = ostat */
	{ AS(linux_readlink_args), (sy_call_t *)linux_readlink },	/* 85 = linux_readlink */
	{ AS(linux_uselib_args), (sy_call_t *)linux_uselib },	/* 86 = linux_uselib */
	{ AS(swapon_args), (sy_call_t *)swapon },	/* 87 = swapon */
	{ AS(linux_reboot_args), (sy_call_t *)linux_reboot },	/* 88 = linux_reboot */
	{ AS(linux_readdir_args), (sy_call_t *)linux_readdir },	/* 89 = linux_readdir */
	{ AS(linux_mmap_args), (sy_call_t *)linux_mmap },	/* 90 = linux_mmap */
	{ AS(munmap_args), (sy_call_t *)munmap },	/* 91 = munmap */
	{ AS(linux_truncate_args), (sy_call_t *)linux_truncate },	/* 92 = linux_truncate */
	{ AS(oftruncate_args), (sy_call_t *)oftruncate },	/* 93 = oftruncate */
	{ AS(fchmod_args), (sy_call_t *)fchmod },	/* 94 = fchmod */
	{ AS(fchown_args), (sy_call_t *)fchown },	/* 95 = fchown */
	{ SYF_MPSAFE | AS(getpriority_args), (sy_call_t *)getpriority },	/* 96 = getpriority */
	{ SYF_MPSAFE | AS(setpriority_args), (sy_call_t *)setpriority },	/* 97 = setpriority */
	{ 0, (sy_call_t *)nosys },			/* 98 = profil */
	{ AS(linux_statfs_args), (sy_call_t *)linux_statfs },	/* 99 = linux_statfs */
	{ AS(linux_fstatfs_args), (sy_call_t *)linux_fstatfs },	/* 100 = linux_fstatfs */
	{ AS(linux_ioperm_args), (sy_call_t *)linux_ioperm },	/* 101 = linux_ioperm */
	{ AS(linux_socketcall_args), (sy_call_t *)linux_socketcall },	/* 102 = linux_socketcall */
	{ AS(linux_syslog_args), (sy_call_t *)linux_syslog },	/* 103 = linux_syslog */
	{ AS(linux_setitimer_args), (sy_call_t *)linux_setitimer },	/* 104 = linux_setitimer */
	{ AS(linux_getitimer_args), (sy_call_t *)linux_getitimer },	/* 105 = linux_getitimer */
	{ AS(linux_newstat_args), (sy_call_t *)linux_newstat },	/* 106 = linux_newstat */
	{ AS(linux_newlstat_args), (sy_call_t *)linux_newlstat },	/* 107 = linux_newlstat */
	{ AS(linux_newfstat_args), (sy_call_t *)linux_newfstat },	/* 108 = linux_newfstat */
	{ 0, (sy_call_t *)linux_uname },		/* 109 = linux_uname */
	{ AS(linux_iopl_args), (sy_call_t *)linux_iopl },	/* 110 = linux_iopl */
	{ 0, (sy_call_t *)linux_vhangup },		/* 111 = linux_vhangup */
	{ 0, (sy_call_t *)nosys },			/* 112 = idle */
	{ 0, (sy_call_t *)linux_vm86old },		/* 113 = linux_vm86old */
	{ SYF_MPSAFE | AS(linux_wait4_args), (sy_call_t *)linux_wait4 },	/* 114 = linux_wait4 */
	{ 0, (sy_call_t *)linux_swapoff },		/* 115 = linux_swapoff */
	{ AS(linux_sysinfo_args), (sy_call_t *)linux_sysinfo },	/* 116 = linux_sysinfo */
	{ AS(linux_ipc_args), (sy_call_t *)linux_ipc },	/* 117 = linux_ipc */
	{ AS(fsync_args), (sy_call_t *)fsync },		/* 118 = fsync */
	{ SYF_MPSAFE | AS(linux_sigreturn_args), (sy_call_t *)linux_sigreturn },	/* 119 = linux_sigreturn */
	{ SYF_MPSAFE | AS(linux_clone_args), (sy_call_t *)linux_clone },	/* 120 = linux_clone */
	{ SYF_MPSAFE | AS(setdomainname_args), (sy_call_t *)setdomainname },	/* 121 = setdomainname */
	{ AS(linux_newuname_args), (sy_call_t *)linux_newuname },	/* 122 = linux_newuname */
	{ AS(linux_modify_ldt_args), (sy_call_t *)linux_modify_ldt },	/* 123 = linux_modify_ldt */
	{ 0, (sy_call_t *)linux_adjtimex },		/* 124 = linux_adjtimex */
	{ AS(mprotect_args), (sy_call_t *)mprotect },	/* 125 = mprotect */
	{ SYF_MPSAFE | AS(linux_sigprocmask_args), (sy_call_t *)linux_sigprocmask },	/* 126 = linux_sigprocmask */
	{ 0, (sy_call_t *)linux_create_module },	/* 127 = linux_create_module */
	{ 0, (sy_call_t *)linux_init_module },		/* 128 = linux_init_module */
	{ 0, (sy_call_t *)linux_delete_module },	/* 129 = linux_delete_module */
	{ 0, (sy_call_t *)linux_get_kernel_syms },	/* 130 = linux_get_kernel_syms */
	{ 0, (sy_call_t *)linux_quotactl },		/* 131 = linux_quotactl */
	{ AS(getpgid_args), (sy_call_t *)getpgid },	/* 132 = getpgid */
	{ AS(fchdir_args), (sy_call_t *)fchdir },	/* 133 = fchdir */
	{ 0, (sy_call_t *)linux_bdflush },		/* 134 = linux_bdflush */
	{ AS(linux_sysfs_args), (sy_call_t *)linux_sysfs },	/* 135 = linux_sysfs */
	{ AS(linux_personality_args), (sy_call_t *)linux_personality },	/* 136 = linux_personality */
	{ 0, (sy_call_t *)nosys },			/* 137 = afs_syscall */
	{ AS(linux_setfsuid16_args), (sy_call_t *)linux_setfsuid16 },	/* 138 = linux_setfsuid16 */
	{ AS(linux_setfsgid16_args), (sy_call_t *)linux_setfsgid16 },	/* 139 = linux_setfsgid16 */
	{ AS(linux_llseek_args), (sy_call_t *)linux_llseek },	/* 140 = linux_llseek */
	{ AS(linux_getdents_args), (sy_call_t *)linux_getdents },	/* 141 = linux_getdents */
	{ AS(linux_select_args), (sy_call_t *)linux_select },	/* 142 = linux_select */
	{ AS(flock_args), (sy_call_t *)flock },		/* 143 = flock */
	{ AS(linux_msync_args), (sy_call_t *)linux_msync },	/* 144 = linux_msync */
	{ AS(readv_args), (sy_call_t *)readv },		/* 145 = readv */
	{ AS(writev_args), (sy_call_t *)writev },	/* 146 = writev */
	{ SYF_MPSAFE | AS(linux_getsid_args), (sy_call_t *)linux_getsid },	/* 147 = linux_getsid */
	{ AS(linux_fdatasync_args), (sy_call_t *)linux_fdatasync },	/* 148 = linux_fdatasync */
	{ AS(linux_sysctl_args), (sy_call_t *)linux_sysctl },	/* 149 = linux_sysctl */
	{ SYF_MPSAFE | AS(mlock_args), (sy_call_t *)mlock },	/* 150 = mlock */
	{ SYF_MPSAFE | AS(munlock_args), (sy_call_t *)munlock },	/* 151 = munlock */
	{ SYF_MPSAFE | AS(mlockall_args), (sy_call_t *)mlockall },	/* 152 = mlockall */
	{ SYF_MPSAFE | 0, (sy_call_t *)munlockall },	/* 153 = munlockall */
	{ SYF_MPSAFE | AS(sched_setparam_args), (sy_call_t *)sched_setparam },	/* 154 = sched_setparam */
	{ SYF_MPSAFE | AS(sched_getparam_args), (sy_call_t *)sched_getparam },	/* 155 = sched_getparam */
	{ SYF_MPSAFE | AS(linux_sched_setscheduler_args), (sy_call_t *)linux_sched_setscheduler },	/* 156 = linux_sched_setscheduler */
	{ SYF_MPSAFE | AS(linux_sched_getscheduler_args), (sy_call_t *)linux_sched_getscheduler },	/* 157 = linux_sched_getscheduler */
	{ 0, (sy_call_t *)sched_yield },		/* 158 = sched_yield */
	{ SYF_MPSAFE | AS(linux_sched_get_priority_max_args), (sy_call_t *)linux_sched_get_priority_max },	/* 159 = linux_sched_get_priority_max */
	{ SYF_MPSAFE | AS(linux_sched_get_priority_min_args), (sy_call_t *)linux_sched_get_priority_min },	/* 160 = linux_sched_get_priority_min */
	{ SYF_MPSAFE | AS(sched_rr_get_interval_args), (sy_call_t *)sched_rr_get_interval },	/* 161 = sched_rr_get_interval */
	{ SYF_MPSAFE | AS(nanosleep_args), (sy_call_t *)nanosleep },	/* 162 = nanosleep */
	{ AS(linux_mremap_args), (sy_call_t *)linux_mremap },	/* 163 = linux_mremap */
	{ SYF_MPSAFE | AS(linux_setresuid16_args), (sy_call_t *)linux_setresuid16 },	/* 164 = linux_setresuid16 */
	{ SYF_MPSAFE | AS(linux_getresuid16_args), (sy_call_t *)linux_getresuid16 },	/* 165 = linux_getresuid16 */
	{ 0, (sy_call_t *)linux_vm86 },			/* 166 = linux_vm86 */
	{ 0, (sy_call_t *)linux_query_module },		/* 167 = linux_query_module */
	{ AS(poll_args), (sy_call_t *)poll },		/* 168 = poll */
	{ 0, (sy_call_t *)linux_nfsservctl },		/* 169 = linux_nfsservctl */
	{ SYF_MPSAFE | AS(linux_setresgid16_args), (sy_call_t *)linux_setresgid16 },	/* 170 = linux_setresgid16 */
	{ SYF_MPSAFE | AS(linux_getresgid16_args), (sy_call_t *)linux_getresgid16 },	/* 171 = linux_getresgid16 */
	{ 0, (sy_call_t *)linux_prctl },		/* 172 = linux_prctl */
	{ AS(linux_rt_sigreturn_args), (sy_call_t *)linux_rt_sigreturn },	/* 173 = linux_rt_sigreturn */
	{ SYF_MPSAFE | AS(linux_rt_sigaction_args), (sy_call_t *)linux_rt_sigaction },	/* 174 = linux_rt_sigaction */
	{ SYF_MPSAFE | AS(linux_rt_sigprocmask_args), (sy_call_t *)linux_rt_sigprocmask },	/* 175 = linux_rt_sigprocmask */
	{ 0, (sy_call_t *)linux_rt_sigpending },	/* 176 = linux_rt_sigpending */
	{ 0, (sy_call_t *)linux_rt_sigtimedwait },	/* 177 = linux_rt_sigtimedwait */
	{ 0, (sy_call_t *)linux_rt_sigqueueinfo },	/* 178 = linux_rt_sigqueueinfo */
	{ SYF_MPSAFE | AS(linux_rt_sigsuspend_args), (sy_call_t *)linux_rt_sigsuspend },	/* 179 = linux_rt_sigsuspend */
	{ AS(linux_pread_args), (sy_call_t *)linux_pread },	/* 180 = linux_pread */
	{ AS(linux_pwrite_args), (sy_call_t *)linux_pwrite },	/* 181 = linux_pwrite */
	{ AS(linux_chown16_args), (sy_call_t *)linux_chown16 },	/* 182 = linux_chown16 */
	{ AS(linux_getcwd_args), (sy_call_t *)linux_getcwd },	/* 183 = linux_getcwd */
	{ 0, (sy_call_t *)linux_capget },		/* 184 = linux_capget */
	{ 0, (sy_call_t *)linux_capset },		/* 185 = linux_capset */
	{ AS(linux_sigaltstack_args), (sy_call_t *)linux_sigaltstack },	/* 186 = linux_sigaltstack */
	{ 0, (sy_call_t *)linux_sendfile },		/* 187 = linux_sendfile */
	{ 0, (sy_call_t *)nosys },			/* 188 = getpmsg */
	{ 0, (sy_call_t *)nosys },			/* 189 = putpmsg */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_vfork },	/* 190 = linux_vfork */
	{ SYF_MPSAFE | AS(linux_getrlimit_args), (sy_call_t *)linux_getrlimit },	/* 191 = linux_getrlimit */
	{ AS(linux_mmap2_args), (sy_call_t *)linux_mmap2 },	/* 192 = linux_mmap2 */
	{ AS(linux_truncate64_args), (sy_call_t *)linux_truncate64 },	/* 193 = linux_truncate64 */
	{ AS(linux_ftruncate64_args), (sy_call_t *)linux_ftruncate64 },	/* 194 = linux_ftruncate64 */
	{ AS(linux_stat64_args), (sy_call_t *)linux_stat64 },	/* 195 = linux_stat64 */
	{ AS(linux_lstat64_args), (sy_call_t *)linux_lstat64 },	/* 196 = linux_lstat64 */
	{ AS(linux_fstat64_args), (sy_call_t *)linux_fstat64 },	/* 197 = linux_fstat64 */
	{ AS(linux_lchown_args), (sy_call_t *)linux_lchown },	/* 198 = linux_lchown */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_getuid },	/* 199 = linux_getuid */
	{ SYF_MPSAFE | 0, (sy_call_t *)linux_getgid },	/* 200 = linux_getgid */
	{ SYF_MPSAFE | 0, (sy_call_t *)geteuid },	/* 201 = geteuid */
	{ SYF_MPSAFE | 0, (sy_call_t *)getegid },	/* 202 = getegid */
	{ SYF_MPSAFE | AS(setreuid_args), (sy_call_t *)setreuid },	/* 203 = setreuid */
	{ SYF_MPSAFE | AS(setregid_args), (sy_call_t *)setregid },	/* 204 = setregid */
	{ SYF_MPSAFE | AS(linux_getgroups_args), (sy_call_t *)linux_getgroups },	/* 205 = linux_getgroups */
	{ SYF_MPSAFE | AS(linux_setgroups_args), (sy_call_t *)linux_setgroups },	/* 206 = linux_setgroups */
	{ AS(fchown_args), (sy_call_t *)fchown },	/* 207 = fchown */
	{ SYF_MPSAFE | AS(setresuid_args), (sy_call_t *)setresuid },	/* 208 = setresuid */
	{ SYF_MPSAFE | AS(getresuid_args), (sy_call_t *)getresuid },	/* 209 = getresuid */
	{ SYF_MPSAFE | AS(setresgid_args), (sy_call_t *)setresgid },	/* 210 = setresgid */
	{ SYF_MPSAFE | AS(getresgid_args), (sy_call_t *)getresgid },	/* 211 = getresgid */
	{ AS(linux_chown_args), (sy_call_t *)linux_chown },	/* 212 = linux_chown */
	{ SYF_MPSAFE | AS(setuid_args), (sy_call_t *)setuid },	/* 213 = setuid */
	{ SYF_MPSAFE | AS(setgid_args), (sy_call_t *)setgid },	/* 214 = setgid */
	{ AS(linux_setfsuid_args), (sy_call_t *)linux_setfsuid },	/* 215 = linux_setfsuid */
	{ AS(linux_setfsgid_args), (sy_call_t *)linux_setfsgid },	/* 216 = linux_setfsgid */
	{ AS(linux_pivot_root_args), (sy_call_t *)linux_pivot_root },	/* 217 = linux_pivot_root */
	{ AS(linux_mincore_args), (sy_call_t *)linux_mincore },	/* 218 = linux_mincore */
	{ SYF_MPSAFE | AS(madvise_args), (sy_call_t *)madvise },	/* 219 = madvise */
	{ AS(linux_getdents64_args), (sy_call_t *)linux_getdents64 },	/* 220 = linux_getdents64 */
	{ SYF_MPSAFE | AS(linux_fcntl64_args), (sy_call_t *)linux_fcntl64 },	/* 221 = linux_fcntl64 */
	{ 0, (sy_call_t *)nosys },			/* 222 =  */
	{ 0, (sy_call_t *)nosys },			/* 223 =  */
	{ 0, (sy_call_t *)linux_gettid },		/* 224 = linux_gettid */
	{ 0, (sy_call_t *)nosys },			/* 225 = linux_readahead */
	{ 0, (sy_call_t *)linux_setxattr },		/* 226 = linux_setxattr */
	{ 0, (sy_call_t *)linux_lsetxattr },		/* 227 = linux_lsetxattr */
	{ 0, (sy_call_t *)linux_fsetxattr },		/* 228 = linux_fsetxattr */
	{ 0, (sy_call_t *)linux_getxattr },		/* 229 = linux_getxattr */
	{ 0, (sy_call_t *)linux_lgetxattr },		/* 230 = linux_lgetxattr */
	{ 0, (sy_call_t *)linux_fgetxattr },		/* 231 = linux_fgetxattr */
	{ 0, (sy_call_t *)linux_listxattr },		/* 232 = linux_listxattr */
	{ 0, (sy_call_t *)linux_llistxattr },		/* 233 = linux_llistxattr */
	{ 0, (sy_call_t *)linux_flistxattr },		/* 234 = linux_flistxattr */
	{ 0, (sy_call_t *)linux_removexattr },		/* 235 = linux_removexattr */
	{ 0, (sy_call_t *)linux_lremovexattr },		/* 236 = linux_lremovexattr */
	{ 0, (sy_call_t *)linux_fremovexattr },		/* 237 = linux_fremovexattr */
	{ AS(linux_tkill_args), (sy_call_t *)linux_tkill },	/* 238 = linux_tkill */
	{ 0, (sy_call_t *)nosys },			/* 239 = linux_sendfile64 */
	{ 0, (sy_call_t *)nosys },			/* 240 = linux_futex */
	{ 0, (sy_call_t *)nosys },			/* 241 = linux_sched_setaffinity */
	{ 0, (sy_call_t *)nosys },			/* 242 = linux_sched_getaffinity */
	{ AS(linux_set_thread_area_args), (sy_call_t *)linux_set_thread_area },	/* 243 = linux_set_thread_area */
	{ 0, (sy_call_t *)nosys },			/* 244 = linux_get_thread_area */
	{ 0, (sy_call_t *)nosys },			/* 245 = linux_io_setup */
	{ 0, (sy_call_t *)nosys },			/* 246 = linux_io_destroy */
	{ 0, (sy_call_t *)nosys },			/* 247 = linux_io_getevents */
	{ 0, (sy_call_t *)nosys },			/* 248 = linux_io_submit */
	{ 0, (sy_call_t *)nosys },			/* 249 = linux_io_cancel */
	{ 0, (sy_call_t *)linux_fadvise64 },		/* 250 = linux_fadvise64 */
	{ 0, (sy_call_t *)nosys },			/* 251 =  */
	{ SYF_MPSAFE | AS(sys_exit_args), (sy_call_t *)sys_exit },	/* 252 = exit_group */
	{ 0, (sy_call_t *)nosys },			/* 253 = linux_lookup_dcookie */
	{ 0, (sy_call_t *)nosys },			/* 254 = linux_epoll_create */
	{ 0, (sy_call_t *)nosys },			/* 255 = linux_epoll_ctl */
	{ 0, (sy_call_t *)nosys },			/* 256 = linux_epoll_wait */
	{ 0, (sy_call_t *)nosys },			/* 257 = linux_remap_file_pages */
	{ 0, (sy_call_t *)nosys },			/* 258 = linux_set_tid_address */
	{ 0, (sy_call_t *)nosys },			/* 259 = linux_timer_create */
	{ 0, (sy_call_t *)nosys },			/* 260 = linux_timer_settime */
	{ 0, (sy_call_t *)nosys },			/* 261 = linux_timer_gettime */
	{ 0, (sy_call_t *)nosys },			/* 262 = linux_timer_getoverrun */
	{ 0, (sy_call_t *)nosys },			/* 263 = linux_timer_delete */
	{ 0, (sy_call_t *)nosys },			/* 264 = linux_clock_settime */
	{ 0, (sy_call_t *)nosys },			/* 265 = linux_clock_gettime */
	{ 0, (sy_call_t *)nosys },			/* 266 = linux_clock_getres */
	{ 0, (sy_call_t *)nosys },			/* 267 = linux_clock_nanosleep */
};
