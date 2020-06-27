#include "ns.h"

extern union Nsipc nsipcbuf;

void
output(envid_t ns_envid)
{
	binaryname = "ns_output";
	int r;
	envid_t whom;
	struct jif_pkt *pkt;

	// LAB 6: Your code here:
	// 	- read a packet from the network server
	//	- send the packet to the device driver
	while(1) {

		if((r = ipc_recv(&whom, &nsipcbuf, 0))<0) {
			panic("%s: ipc_recv :%e\n",binaryname, r);
		}
		if(whom != ns_envid) {
			cprintf("output: received packets from wrong envid: %x\n", whom);
			return;
		}
		pkt = (struct jif_pkt *)&nsipcbuf;
		cprintf("output: pkt->jp_data: %s\n",pkt->jp_data);
		sys_net_tx((void *)pkt->jp_data, (size_t)pkt->jp_len); 

	}
}
