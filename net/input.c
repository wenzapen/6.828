#include "ns.h"

extern union Nsipc nsipcbuf;
int waitcount = 10;

void
input(envid_t ns_envid)
{
	binaryname = "ns_input";
	struct jif_pkt *pkt = (struct jif_pkt *)&nsipcbuf;
	int r;

	// LAB 6: Your code here:
	// 	- read a packet from the device driver
	//	- send it to the network server
	// Hint: When you IPC a page to the network server, it will be
	// reading from it for a while, so don't immediately receive
	// another packet in to the same physical page.
	memcpy(pkt->jp_data, "copy on write", 1);
	while(1) {
		while((r=sys_nic_recv((void *)pkt->jp_data)) == -E_RX_BUF_EMPTY) 
			sys_yield();
		if(r <= 0)
			panic("%s: sys_nic_receive: %e\n",binaryname, r);
		pkt->jp_len = r;
		sys_ipc_try_send(ns_envid, NSREQ_INPUT, pkt, PTE_P|PTE_W|PTE_U);
		for(int i=0; i<waitcount; i++)
			sys_yield();

	}
}
