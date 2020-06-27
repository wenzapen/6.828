#ifndef JOS_KERN_E1000_H
#define JOS_KERN_E1000_H

#include <kern/pci.h>

#define E1000_REG(offset) e1000[(offset)/4]
#define TDH E1000_REG(E1000_TDH)
#define TDT E1000_REG(E1000_TDT)
#define TDLEN (E1000_REG(E1000_TDLEN)/16)

#define VENDOR_ID_E1000 0x8086
#define DEVICE_ID_E1000 0x100E

#define E1000_CTRL        0x0000
#define E1000_CTRL_DUP    0x0004
#define E1000_STATUS      0x0008

#define E1000_TDBAL	0x3800
#define E1000_TDBAH	0x3804
#define E1000_TDLEN	0x3808
#define E1000_TDH	0x3810
#define E1000_TDT	0x3818

#define E1000_TCTL	0x0400
    #define E1000_TCTL_RST	0x00000001
    #define E1000_TCTL_EN	0x00000002
    #define E1000_TCTL_BCE	0x00000004
    #define E1000_TCTL_PSP	0x00000008
    #define E1000_TCTL_CT	0x00000ff0
    #define E1000_TCTL_COLD	0x003ff000
#define E1000_TIPG	0x0410

#define TX_DESC_LEN    0x10
#define RX_DESC_LEN    0x10
#define BUFFER_SIZE    1518

struct tx_desc {
	uint64_t addr;
	uint16_t length;
	uint8_t cso;
	uint8_t cmd;
	uint8_t status;
	uint8_t css;
	uint16_t special;
};

#define E1000_TXD_STAT_DD    0x01
#define E1000_TXD_CMD_RS     0x08

int pci_e1000_attach(struct pci_func *pcif);
int e1000_transmit(void *packet, size_t len);

#endif  // SOL >= 6
