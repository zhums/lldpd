#ifndef _COMMON_H
#define _COMMON_H

#include "../src/daemon/lldpd.h"

/* See:
 * http://wiki.wireshark.org/Development/LibpcapFileFormat
 */
struct pcap_hdr {
        u_int32_t magic_number;   /* magic number */
        u_int16_t version_major;  /* major version number */
        u_int16_t version_minor;  /* minor version number */
        u_int32_t thiszone;       /* GMT to local correction */
        u_int32_t sigfigs;        /* accuracy of timestamps */
        u_int32_t snaplen;        /* max length of captured packets, in octets */
        u_int32_t network;        /* data link type */
};
struct pcaprec_hdr {
	u_int32_t ts_sec;         /* timestamp seconds */
        u_int32_t ts_usec;        /* timestamp microseconds */
        u_int32_t incl_len;       /* number of octets of packet saved in file */
        u_int32_t orig_len;       /* actual length of packet */
};

struct packet {
	TAILQ_ENTRY(packet) next;
	int size;
	char data[];
};
TAILQ_HEAD(pkts_t, packet);

extern int dump;		/* Dump file descriptor in pcap format */
extern char filenameprefix[];	/* Prefix for filename dumping */
extern char *filename;		/* Filename we are dumping to */
extern char macaddress[];	  /* MAC address we use to send */
extern struct pkts_t pkts; /* List of sent packets */
extern struct lldpd_hardware hardware;
extern struct lldpd_chassis chassis;

int pcap_send(struct lldpd *, struct lldpd_hardware *, char *, size_t);
void pcap_setup();
void pcap_teardown();

#endif
