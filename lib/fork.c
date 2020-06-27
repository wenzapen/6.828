// implement fork from user space

#include <inc/string.h>
#include <inc/lib.h>

// PTE_COW marks copy-on-write page table entries.
// It is one of the bits explicitly allocated to user processes (PTE_AVAIL).
#define PTE_COW		0x800

//
// Custom page fault handler - if faulting page is copy-on-write,
// map in our own private writable copy.
//
static void
pgfault(struct UTrapframe *utf)
{
	void *addr = (void *) utf->utf_fault_va;
	uint32_t err = utf->utf_err;
	int r;

	// Check that the faulting access was (1) a write, and (2) to a
	// copy-on-write page.  If not, panic.
	// Hint:
	//   Use the read-only page table mappings at uvpt
	//   (see <inc/memlayout.h>).

	// LAB 4: Your code here.
//	cprintf("uvpt: %x addr: %x uvpt[addr>>12] : %x\n",uvpt, addr, uvpt[(uint32_t)addr>>12]);
	if(!((err | PTE_W) && (uvpt[(uint32_t)addr>>12] | PTE_COW)))
		panic("pgfault: addr is not COW or faulting address is not write\n");

	// Allocate a new page, map it at a temporary location (PFTEMP),
	// copy the data from the old page to the new page, then move the new
	// page to the old page's address.
	// Hint:
	//   You should make three system calls.

	// LAB 4: Your code here.
//	cprintf("pgfault: running in stack: %x\n", ROUNDDOWN(&err, PGSIZE));
	if((r = sys_page_alloc(0, (void*)PFTEMP, PTE_W|PTE_U|PTE_P)) < 0)
		panic("sys_page_alloc:  %e\n", r);
	memmove(PFTEMP, ROUNDDOWN(addr,PGSIZE), PGSIZE);
	if((r = sys_page_map(0, (void*)PFTEMP, 0, ROUNDDOWN(addr,PGSIZE), PTE_W|PTE_U|PTE_P)) < 0)
		panic("sys_page_map: %e\n", r);
	if((r = sys_page_unmap(0, (void*)PFTEMP)) < 0)
		panic("sys_page_unmap: %e\n", r);

//	panic("pgfault not implemented");
}

//
// Map our virtual page pn (address pn*PGSIZE) into the target envid
// at the same virtual address.  If the page is writable or copy-on-write,
// the new mapping must be created copy-on-write, and then our mapping must be
// marked copy-on-write as well.  (Exercise: Why do we need to mark ours
// copy-on-write again if it was already copy-on-write at the beginning of
// this function?)
//
// Returns: 0 on success, < 0 on error.
// It is also OK to panic on error.
//
static int
duppage(envid_t envid, unsigned pn)
{
	int r;
	int perm = PTE_U | PTE_P;

	// LAB 4: Your code here.
//	cprintf("duppage: dstenvid: %x pn: %x va: %x\n",envid, pn, pn*PGSIZE);
	if((uvpt[pn] & PTE_SHARE) && (uvpt[pn] & PTE_COW))
		panic("duppage: PTE_SHARE && PTE_COW\n");
	if(uvpt[pn] & PTE_SHARE)
		perm = uvpt[pn] & PTE_SYSCALL;
	else if(uvpt[pn] & (PTE_W | PTE_COW))
		perm |= PTE_COW;
//	cprintf("duppage: perm: %x \n", perm);
	if((r = sys_page_map(0, (void*)(pn*PGSIZE), envid, (void*)(pn*PGSIZE), perm)) < 0)
		panic("sys_page_map: %e\n",r);
	if(perm & PTE_COW)
		if((r = sys_page_map(0, (void*)(pn*PGSIZE), 0, (void*)(pn*PGSIZE), perm)) < 0)
			panic("sys_page_map: %e\n",r);
//	panic("duppage not implemented");
	return 0;
}

//
// User-level fork with copy-on-write.
// Set up our page fault handler appropriately.
// Create a child.
// Copy our address space and page fault handler setup to the child.
// Then mark the child as runnable and return.
//
// Returns: child's envid to the parent, 0 to the child, < 0 on error.
// It is also OK to panic on error.
//
// Hint:
//   Use uvpd, uvpt, and duppage.
//   Remember to fix "thisenv" in the child process.
//   Neither user exception stack should ever be marked copy-on-write,
//   so you must allocate a new page for the child's user exception stack.
//
envid_t
fork(void)
{
	// LAB 4: Your code here.
	int r;
	envid_t envid;
	int pn = 0;
	set_pgfault_handler(pgfault);
	envid = sys_exofork();
	if(envid == 0) {
                thisenv = &envs[ENVX(sys_getenvid())];
                return 0;
	}
	// we are now in parent environment and envid is the ID of child
	while(pn < ((UXSTACKTOP - PGSIZE) >> 12)) {
//		cprintf("pn: %d\n",pn);
		if(!(uvpd[pn >> 10] & PTE_P)) {
			pn += 1024;
			continue;
		}
		if(uvpt[pn] & PTE_P) 
			duppage(envid, pn);
		pn++;
	}
	if((r = sys_page_alloc(envid, (void*)(UXSTACKTOP-PGSIZE), PTE_W|PTE_U|PTE_P)) < 0)
		panic("sys_page_alloc: %e\n",r);
	if((r = sys_env_set_pgfault_upcall(envid, thisenv->env_pgfault_upcall)) < 0)
		panic("sys_env_set_pgfault_upcall: %e\n",r);
	if((r = sys_env_set_status(envid, ENV_RUNNABLE)) < 0)
		panic("sys_env_set_status: %e\n",r);
	cprintf("parent: %x child: %x child status: %d\n",thisenv->env_id, envid, envs[ENVX(envid)].env_status);
	return envid;	
//	panic("fork not implemented");
}

// Challenge!
int
sfork(void)
{
	panic("sfork not implemented");
	return -E_INVAL;
}
