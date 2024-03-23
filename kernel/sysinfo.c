#include "types.h"
#include "sysinfo.h"

// defs.h is dependent on riscv.h
#include "riscv.h"
#include "defs.h"

// proc.h is dependent on param.h and spinlock.h
#include "spinlock.h"
#include "param.h"
#include "proc.h"

int
sysinfo(uint64 addr)
{
    struct sysinfo info;
    info.freemem = freemem();
    info.nproc = nproc();
    
    struct proc *p = myproc();
    if (copyout(p->pagetable, addr, (char *)&info, sizeof(info)) < 0)
        return -1;
    
    return 0;
}