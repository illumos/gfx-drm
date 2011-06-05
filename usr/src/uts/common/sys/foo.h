
#define	FOO_IOC_GETCNT	1
typedef uint32_t foocnt_t;

#ifndef	_KERNEL
extern int foo_getcnt(uint32_t *);
#endif
