#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

#include <errno.h>

extern caddr_t PLATFORM_DEBUG_CHARPORT;
extern caddr_t CPU_HEAP_START;
extern caddr_t CPU_HEAP_END;
extern void platform_debug_puts (char * string);
extern void platform_debug_puts_len (char * string, int len);

char *__env[1] = { 0 };
char **environ = __env;
struct timeval;

/*
#include <reent.h>

struct _reent _impure_data = _REENT_INIT(_impure_data);
struct _reent * _impure_ptr = &_impure_data;
struct _reent *_CONST _global_impure_ptr = &_impure_data;
*/

// --- Process Control ---
int execve(char  *name, char **argv, char **env)
{
	platform_debug_puts("SysCall: execve\n");
    errno = ENOSYS;
    return -1;
}

void _exit()
{
	platform_debug_puts("SysCall: _exit\n");
    /* Convince GCC that this function never returns.  */
    for (;;)
        ;
}

int fork()
{
	platform_debug_puts("SysCall: fork\n");
    errno = ENOSYS;
    return -1;
}

int getpid()
{
	platform_debug_puts("SysCall: getpid\n");
    return 1;     // MYPID
}

int kill(int pid, int sig)
{
	platform_debug_puts("SysCall: kill\n");
    errno = ENOSYS;
    return -1;
}

int wait(int *status)
{
	platform_debug_puts("SysCall: wait\n");
    errno = ENOSYS;
    return -1;
}

// --- Memory ---
caddr_t sbrk(int incr)
{
    static caddr_t ptr_heap_loc = NULL;
    caddr_t ptr_start = NULL;
	platform_debug_puts("SysCall: sbrk\n");

    if(!ptr_heap_loc)
    {
        ptr_heap_loc = CPU_HEAP_START;
    }

    if((ptr_heap_loc + incr) < CPU_HEAP_END)
    {
        ptr_start = (caddr_t)(((unsigned int)(ptr_heap_loc + 8)) & 0xFFFFFFF8);
        ptr_heap_loc = ptr_heap_loc + incr;
        return ptr_start;
    }

    errno = ENOMEM;
    return -1;
}

// --- I/O ---
int chown(const char *path, uid_t owner, gid_t group)
{
	platform_debug_puts("SysCall: chown\n");
    errno = ENOSYS;
    return -1;
}

int close(int file)
{
	platform_debug_puts("SysCall: close\n");
    errno = ENOSYS;
    return -1;
}

int fstat(int file, struct stat *st)
{
	platform_debug_puts("SysCall: fstat\n");
    st -> st_mode = S_IFCHR;
    return 0;
}

int isatty(int file)
{
	platform_debug_puts("SysCall: istty\n");
    return 1;
}

int link(char *old, char *new)
{
	platform_debug_puts("SysCall: link\n");
    errno = EMLINK;
    return -1;
}

int open(const char *name, int flags, ...)
{
	platform_debug_puts("SysCall: open\n");
    errno = ENOSYS;
    return -1;
}

int read(int file, char *ptr, int len)
{
	platform_debug_puts("SysCall: read\n");
//    errno = ENOSYS;
//    return -1;
    return 0;
}

int readlink(const char *path, char *buf, size_t bufsize)
{
	platform_debug_puts("SysCall: readlink\n");
    errno = ENOSYS;
    return -1;
}

int getdents(unsigned int fd, struct dirent *dirp, unsigned int count)
{
	platform_debug_puts("SysCall: getdents\n");
    errno = ENOSYS;
    return -1;
}

int ioctl(int fd, int request, ...)
{
	platform_debug_puts("SysCall: ioctl\n");
    errno = ENOSYS;
    return -1;
}

int lseek(int file, off_t ptr, int dir)
{
	platform_debug_puts("SysCall: lseek\n");
    return 0;
}

int stat(const char *file, struct stat *st)
{
	platform_debug_puts("SysCall: stat\n");
    st -> st_mode = S_IFCHR;
    return 0;
}

int symlink(const char *path1, const char *path2)
{
	platform_debug_puts("SysCall: symlink\n");
    errno = ENOSYS;
    return -1;
}

int unlink(char *name)
{
	platform_debug_puts("SysCall: unlink\n");
    errno = EMLINK;
    return -1;
}

int write(int file, char *ptr, int len)
{
    switch(file)
    {
        case 1: /* stdout */
            platform_debug_puts_len(ptr, len);            
            return len;
        break;

        case 2: /* stderr */
            //printf("file = %d, len = %d, ptr = %s\n", file, len, ptr);
            platform_debug_puts_len(ptr, len);
            return len;
        break;
    }

    return -1;
}

// --- Other ---
#ifndef _REENT_ONLY
extern int errno;
int * __errno ()
{
    return & errno;
}
#endif

int gettimeofday(struct timeval *p, void *z)
{
	platform_debug_puts("SysCall: gettimeofday\n");
    errno = ENOSYS;
    return -1;
}

clock_t times(struct tms *buf)
{
	platform_debug_puts("SysCall: times\n");
    errno = ENOSYS;
    return -1;
}


