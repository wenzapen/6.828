#include <kern/e1000.h>
#include <kern/pmap.h>
#include <inc/string.h>

// LAB 6: Your driver code here
//

physaddr_t e1000_addr;
volatile uint32_t *e1000;

struct tx_desc tx_descs[TX_DESC_LEN] __attribute__((aligned(16)));
char tx_bufs[TX_DESC_LEN][BUFFER_SIZE];

static void e1000_tx_init();
static void e1000_rx_init();
static void e1000_tx_test(int n);

int pci_e1000_attach(struct pci_func *pcif) {
	pci_func_enable(pcif);
	for(int i=0; i<6; i++) {
		cprintf("pci_e1000_attach: reg_base[%x]: %x reg_size[%x]: %x \n",i,pcif->reg_base[i], i, pcif->reg_size[i]);

	}
	e1000_addr = pcif->reg_base[0];
	size_t size = pcif->reg_size[0];

	e1000 = mmio_map_region(e1000_addr, size);
	cprintf("pci_e1000_attach: e1000: %x\n", e1000);
	cprintf("pci_e1000_attach: status: %x\n", E1000_REG(E1000_STATUS));
	e1000_tx_init();
	cprintf("pci_e1000_attach: e1000 tx initiated: %x\n", E1000_REG(E1000_TCTL));
	return 0;
}

static void e1000_tx_init() {
	assert(((uint32_t)(&tx_descs[0])) % 16 == 0);
	assert((sizeof(tx_descs)) % 128 == 0);

	for(int i=0; i<TX_DESC_LEN; i++) {
		tx_descs[i].addr = (uint32_t)&tx_bufs[i];
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

int e1000_transmit(void *packet, size_t len) {
//	cprintf("e1000_transmit: TDT: %d TDH: %d RS: %d DD: %d\n",TDT, TDH,(tx_descs[TDT].cmd & E1000_TXD_CMD_RS), (tx_descs[TDT].status & E1000_TXD_STAT_DD));
	if((TDT == TDH) && !(tx_descs[TDT].status & E1000_TXD_STAT_DD) && (tx_descs[TDT].cmd & E1000_TXD_CMD_RS)) {
		cprintf("e1000_transmit: transmit buffer is full\n");
		return -1;
	}
	memcpy((void *)((uint32_t)tx_descs[TDT].addr), packet, len);
	cprintf("e1000_transmit: tx_descs[%d]: %s\n",TDT,(char *)((uint32_t)tx_descs[TDT].addr));
	tx_descs[TDT].cmd |= E1000_TXD_CMD_RS;
	tx_descs[TDT].status &= ~E1000_TXD_STAT_DD;
//	cprintf("e1000_transmit: TDT: %d RS: %d DD: %d\n",TDT, (tx_descs[TDT].cmd & E1000_TXD_CMD_RS), (tx_descs[TDT].status & E1000_TXD_STAT_DD));
	TDT = (TDT+1) % TDLEN;
	return 0;
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
