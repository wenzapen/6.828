#include <kern/e1000.h>
#include <kern/pmap.h>
#include <inc/string.h>
#include <inc/error.h>

// LAB 6: Your driver code here
//

physaddr_t e1000_addr;
volatile uint32_t *e1000;

struct tx_desc tx_descs[TX_DESC_LEN] __attribute__((aligned(16)));
char tx_bufs[TX_DESC_LEN][TX_BUFFER_SIZE];
struct rx_desc rx_descs[RX_DESC_LEN] __attribute__((aligned(16)));
char rx_bufs[RX_DESC_LEN][RX_BUFFER_SIZE];

static void e1000_tx_init();
static void e1000_rx_init();
static void e1000_tx_test(int n);
static void e1000_rx_descs_print();

static void e1000_rx_descs_print()  {
	for(int i=0; i<RX_DESC_LEN;i++) {
		if(rx_descs[i].status & E1000_RD_STAT_DD)
			cprintf("e1000_rx_descs_print: rx_descs[%d] has data\n",i);
	}
}

static void
hexdump(const char *prefix, const void *data, int len)
{
        int i;
        char buf[80];
        char *end = buf + sizeof(buf);
        char *out = NULL;
        for (i = 0; i < len; i++) {
                if (i % 16 == 0)
                        out = buf + snprintf(buf, end - buf,
                                             "%s%04x   ", prefix, i);
                out += snprintf(out, end - out, "%02x", ((uint8_t*)data)[i]);
                if (i % 16 == 15 || i == len - 1)
                        cprintf("%.*s\n", out - buf, buf);
                if (i % 2 == 1)
                        *(out++) = ' ';
                if (i % 16 == 7)
                        *(out++) = ' ';
        }
}


int pci_e1000_attach(struct pci_func *pcif) {
	pci_func_enable(pcif);
	for(int i=0; i<6; i++) {
//		cprintf("pci_e1000_attach: reg_base[%x]: %x reg_size[%x]: %x \n",i,pcif->reg_base[i], i, pcif->reg_size[i]);

	}
	e1000_addr = pcif->reg_base[0];
	size_t size = pcif->reg_size[0];

	e1000 = mmio_map_region(e1000_addr, size);
//	cprintf("pci_e1000_attach: e1000: %x\n", e1000);
//	cprintf("pci_e1000_attach: status: %x\n", E1000_REG(E1000_STATUS));
	e1000_tx_init();
	e1000_rx_init();
//	cprintf("pci_e1000_attach: e1000 tx initiated: %x\n", E1000_REG(E1000_TCTL));
	return 0;
}

static void e1000_tx_init() {
	assert(((uint32_t)(&tx_descs[0])) % 16 == 0);
	assert((sizeof(tx_descs)) % 128 == 0);

	for(int i=0; i<TX_DESC_LEN; i++) {
//		cprintf("e1000_tx_init: &txbufs[%d]: %x pa: %x\n",i, &tx_bufs[i], PADDR(&tx_bufs[i])); 
		tx_descs[i].addr = PADDR(&tx_bufs[i]);
	}
	E1000_REG(E1000_TDBAL) = PADDR(&tx_descs[0]);
	E1000_REG(E1000_TDBAH) = 0;
	E1000_REG(E1000_TDLEN) = sizeof(tx_descs);
	E1000_REG(E1000_TDH) = 0;
	E1000_REG(E1000_TDT) = 0;
	E1000_REG(E1000_TCTL) |= E1000_TCTL_PSP;
	E1000_REG(E1000_TCTL) &= ~E1000_TCTL_COLD;
	E1000_REG(E1000_TCTL) |= (0x40 << 12);
	E1000_REG(E1000_TIPG) = 10;
	E1000_REG(E1000_TCTL) |= E1000_TCTL_EN;

//	e1000_tx_test(20);

}

static void e1000_rx_init() {
	assert(((uint32_t)(&rx_descs[0])) % 16 == 0);
	assert((sizeof(rx_descs)) % 128 == 0);

	for(int i=0; i<RX_DESC_LEN; i++) {
//		cprintf("e1000_rx_init: &rxbufs[%d]: %x pa: %x\n",i, &rx_bufs[i], PADDR(&rx_bufs[i])); 
		rx_descs[i].addr = PADDR(&rx_bufs[i]);
	}
	E1000_REG(E1000_RDBAL) = PADDR(&rx_descs[0]);
	E1000_REG(E1000_RDBAH) = 0;
	E1000_REG(E1000_RDLEN) = sizeof(rx_descs);
	E1000_REG(E1000_RDH) = 0;
	E1000_REG(E1000_RDT) = RX_DESC_LEN - 1;
	E1000_REG(E1000_RAL) = 0x12005452;
	E1000_REG(E1000_RAH) = 0x5634 & 0x0000ffff;
	E1000_REG(E1000_RAH) |= 0x80000000;
	E1000_REG(E1000_MTA) = 0;
	E1000_REG(E1000_RCTL) |= E1000_RCTL_SECRC;
	E1000_REG(E1000_RCTL) &= ~E1000_RCTL_LPE;
	E1000_REG(E1000_RCTL) |= E1000_RCTL_EN;
//	cprintf("e1000_rx_init: RAH: %x\n", E1000_REG(E1000_RAH));

//	e1000_tx_test(20);

}

int e1000_transmit(void *packet, size_t len) {
//	cprintf("e1000_transmit: TDT: %d TDH: %d RS: %d DD: %d\n",TDT, TDH,(tx_descs[TDT].cmd & E1000_TXD_CMD_RS), (tx_descs[TDT].status & E1000_TXD_STAT_DD));
	if((TDT == TDH) && !(tx_descs[TDT].status & E1000_TXD_STAT_DD) && (tx_descs[TDT].cmd & E1000_TXD_CMD_RS)) {
//		cprintf("e1000_transmit: transmit buffer is full\n");
		return -E_TX_BUF_FULL;
	}
	
	memcpy(tx_bufs[TDT], packet, len);
//	cprintf("e1000_transmit: tx_descs[%d]: %s\n",TDT,(char *)(tx_bufs[TDT]));
	tx_descs[TDT].cmd |= E1000_TXD_CMD_RS | E1000_TXD_CMD_EOP;
	tx_descs[TDT].status &= ~E1000_TXD_STAT_DD;
	tx_descs[TDT].length = len;
//	cprintf("e1000_transmit: tx_descs[%d]: cmd:  %d status: %d length: %d\n",TDT, tx_descs[TDT].cmd, tx_descs[TDT].status, tx_descs[TDT].length);
	TDT = (TDT+1) % TDLEN;
	return 0;
}

//return the size of received packet in case of success
int e1000_receive(void *packet) {
//	cprintf("e1000_transmit: TDT: %d TDH: %d RS: %d DD: %d\n",TDT, TDH,(tx_descs[TDT].cmd & E1000_TXD_CMD_RS), (tx_descs[TDT].status & E1000_TXD_STAT_DD));
//	e1000_rx_descs_print();
	if( !(rx_descs[(RDT+1) % RDLEN].status & E1000_RD_STAT_DD) ) {
//		cprintf("e1000_receive: receive buffer is empty\n");
		return -E_RX_BUF_EMPTY;
	}
	
	RDT = (RDT+1) % RDLEN;
	if(rx_descs[RDT].length > RX_BUFFER_SIZE)
		return -E_PACKET_TOO_LONG;
	int len = rx_descs[RDT].length;
//	cprintf("e1000_receive: before memcpy: addr of packet: %x addr of rxbuf: %x len: %d\n",packet, &rx_bufs[RDT], len);
	memcpy(packet, &rx_bufs[RDT], len);
//	hexdump("input", packet, len);
//	cprintf("e1000_receive: rx_descs[%d]: %s\n",RDT,(char *)(rx_bufs[RDT]));
	tx_descs[RDT].status = 0;
	return len;
}

void e1000_tx_test(int n) {
	char packet[1518];
	size_t len = 1518;
	int r;
	for(int i=0; i<n; i++) {
		memset(packet, 1, len);
		while(1) {
			if((r = e1000_transmit((void*)packet, len)) == 0)
				break;
		}
		cprintf("e1000_tx_test: sent packet: %d\n",i);
	}	
}
