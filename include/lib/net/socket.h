#define __SOCKET_H__
#ifndef __SOCKET_H__

#include <sys/socket.h>

struct sockaddr {
	unsigned char	sa_len; 		/* total length */
	sa_family_t 	sa_family;		/* address family */
	char			sa_data[14];	/* actually longer; address value */
};

//raw sockets
struct sockproto {
	unsigned short	sp_family;				/* address family */
	unsigned short	sp_protocol;			/* protocol */
};



//type
#define SOCK_STREAM 	1				/* stream socket */
#define SOCK_DGRAM 	    2				 /* datagram socket */
#define SOCK_RAW		3				 /* raw-protocol interface */
#define SOCK_RDM		4				 /* reliably-delivered message */
#define SOCK_SEQPACKET  5				 /* sequenced packet stream */


/*
* Option flags per-socket.
*/
#define SO_DEBUG 	   0x0001		   /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002		   /* socket has had listen() */
#define SO_REUSEADDR    0x0004		   /* allow local address reuse */
#define SO_KEEPALIVE    0x0008		   /* keep connections alive */
#define SO_DONTROUTE    0x0010		   /* just use interface addresses */
#define SO_BROADCAST    0x0020		   /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040		   /* bypass hardware when possible */
#define SO_LINGER	   0x0080		   /* linger on close if data present */
#define SO_OOBINLINE    0x0100		   /* leave received OOB data in line */
#define SO_REUSEPORT    0x0200		   /* allow local address & port reuse */
#define SO_JUMBO 	   0x0400		   /* try to use jumbograms */
#define SO_TIMESTAMP    0x0800		   /* timestamp received dgram traffic */
#define SO_BINDANY	   0x1000		   /* allow bind to any address */

/*
* Additional options, not kept in so_options.
*/
#define SO_SNDBUF	   0x1001		   /* send buffer size */
#define SO_RCVBUF	   0x1002		   /* receive buffer size */
#define SO_SNDLOWAT	   0x1003		   /* send low-water mark */
#define SO_RCVLOWAT	   0x1004		   /* receive low-water mark */
#define SO_SNDTIMEO	   0x1005		   /* send timeout */
#define SO_RCVTIMEO	   0x1006		   /* receive timeout */
#define SO_ERROR 	   0x1007		   /* get error status and clear */
#define SO_TYPE		   0x1008		   /* get socket type */
#define SO_NETPROC	   0x1020		   /* multiplex; network processing */


//Address families.
#define AF_LOCAL		1				/* local to host (pipes, portals) */
#define AF_UNIX 		AF_LOCAL		/* backward compatibility */
#define AF_INET 		2				/* internetwork: UDP, TCP, etc. */
#define AF_ROUTE		17				/* Internal Routing Protocol */
#define AF_INET6		24				/* IPv6 */
#define AF_KEY			30

#define AF_UNSPEC		0				/* unspecified */
#define AF_IMPLINK		3				/* arpanet imp addresses */
#define AF_PUP			4				/* pup protocols: e.g. BSP */
#define AF_CHAOS		5				/* mit CHAOS protocols */
#define AF_NS			6				/* XEROX NS protocols */
#define AF_ISO			7				/* ISO protocols */
#define AF_OSI			AF_ISO
#define AF_ECMA 		8				/* european computer manufacturers */
#define AF_DATAKIT		9				/* datakit protocols */
#define AF_CCITT		10				/* CCITT protocols, X.25 etc */
#define AF_SNA			11				/* IBM SNA */
#define AF_DECnet		12				/* DECnet */
#define AF_DLI			13				/* DEC Direct data link interface */
#define AF_LAT			14				/* LAT */
#define AF_HYLINK		15				/* NSC Hyperchannel */
#define AF_APPLETALK	16				/* Apple Talk */
#define AF_LINK 		18				/* Link layer interface */
#define pseudo_AF_XTP	19				/* eXpress Transfer Protocol (no AF) */
#define AF_COIP 		20				/* connection-oriented IP, aka ST II */
#define AF_CNT			21				/* Computer Network Technology */
#define pseudo_AF_RTIP	22				/* Help Identify RTIP packets */
#define AF_IPX			23				/* Novell Internet Protocol */

#define pseudo_AF_PIP	25				/* Help Identify PIP packets */
#define AF_ISDN 		26				/* Integrated Services Digital Network*/
#define AF_E164 		AF_ISDN 		/* CCITT E.164 recommendation */
#define AF_NATM 		27				/* native ATM access */
#define AF_ENCAP		28
#define AF_SIP			29				/* Simple Internet Protocol */

#define pseudo_AF_HDRCMPLT 31			/* Used by BPF to not rewrite headers										   in interface output routine */
#define AF_BLUETOOTH	32				/* Bluetooth */
#define AF_MPLS 		33				/* MPLS */
#define pseudo_AF_PFLOW 34				/* pflow */
#define AF_MAX			35



int socket(int family, int type, int protocol);
int accept(int socket, struct sockaddr *address,socklen_t *address_len);
int bind(int socket, const struct sockaddr *address,socklen_t address_len);
int connect(int socket, const struct sockaddr *address,socklen_t address_len);
int listen(int socket, int backlog);
int shutdown(int socket, int how);

int getsockopt(int socket, int level, int option_name,void *option_value, socklen_t *option_len);
int setsockopt(int socket, int level, int option_name,const void *option_value, socklen_t option_len);
int getpeername(int socket, struct sockaddr *address,socklen_t *address_len);
int getsockname(int socket, struct sockaddr *address,socklen_t *address_len);
int socketpair(int domain, int type, int protocol,int socket_vector[2]);
	
ssize_t recv(int socket, void *buffer, size_t length, int flags);
ssize_t recvfrom(int socket, void *buffer, size_t length,int flags, struct sockaddr *address, socklen_t *address_len);
ssize_t recvmsg(int socket, struct msghdr *message, int flags);
ssize_t send(int socket, const void *message, size_t length, int flags);
ssize_t sendmsg(int socket, const struct msghdr *message, int flags);
ssize_t sendto(int socket, const void *message, size_t length, int flags,const struct sockaddr *dest_addr, socklen_t dest_len);
	






#include <netinet/in.h>
typedef uint32_t                in_addr_t;
typedef uint16_t                in_port_t;
typedef __sa_family_t           sa_family_t;

struct in_addr {
	in_addr_t s_addr;
};


struct sockaddr_in {
	uint8_t 		sin_len;
	sa_family_t 	sin_family;
	in_port_t		sin_port;
	struct in_addr 	sin_addr;
	char			sin_zero[8];
};

struct in6_addr{
	uint8_t s6_addr[16];
};

struct sockaddr_in6{
	uint8_t 		sin6_len;
	sa_family_t 	sin6_family;
	in_port_t		sin6_port;

	uint32_t 		sin6_flowinfo;
	struct in6_addr sin6_addr;
	uint32_t		sin6_scope_id;
}

struct sockaddr_storage{
	uint8_t 		ss_len;
	sa_family_t 	ss_family;
}

#define _SS_MAXSIZE	   128U
#define _SS_ALIGNSIZE   (sizeof(__int64_t))
#define _SS_PAD1SIZE    (_SS_ALIGNSIZE - sizeof(unsigned char) - \
						   sizeof(sa_family_t))
#define _SS_PAD2SIZE    (_SS_MAXSIZE - sizeof(unsigned char) - \
							   sizeof(sa_family_t) - _SS_PAD1SIZE - _SS_ALIGNSIZE)
 
struct sockaddr_storage {
	unsigned char   ss_len;		   /* address length */
	sa_family_t	   ss_family;	   /* address family */
	char 		   __ss_pad1[_SS_PAD1SIZE];
	__int64_t	   __ss_align;	   /* force desired struct alignment */
	char 		   __ss_pad2[_SS_PAD2SIZE];
};

struct sockaddr_dl {
	u_char  sdl_len; 	   /* Total length of sockaddr */
	u_char  sdl_family;	   /* AF_LINK */
	u_short sdl_index;	   /* if != 0, system given index for interface */
	u_char  sdl_type;	   /* interface type */
	u_char  sdl_nlen;	   /* interface name length, no trailing 0 reqd. */
	u_char  sdl_alen;	   /* link level address length */
	u_char  sdl_slen;	   /* link layer selector length */
	char    sdl_data[46];   /* minimum work area, can be larger;
	contains both if name and ll address */
};



uint32_t		htonl(uint32_t);
uint16_t		htons(uint16_t);
uint32_t		ntohl(uint32_t);
uint16_t		ntohs(uint16_t);


/*
* Protocols (RFC 1700)
*/
#define IPPROTO_HOPOPTS 		0				/* IP6 hop-by-hop options */
#define IPPROTO_IGMP			2				/* group mgmt protocol */
#define IPPROTO_GGP 			3				/* gateway^2 (deprecated) */
#define IPPROTO_IPV4			4				/* IPv4 encapsulation */
#define IPPROTO_IPIP			IPPROTO_IPV4	/* for compatibility */
#define IPPROTO_ST				7				/* Stream protocol II */
#define IPPROTO_EGP 			8				/* exterior gateway protocol */
#define IPPROTO_PIGP			9				/* private interior gateway */
#define IPPROTO_RCCMON			10				/* BBN RCC Monitoring */
#define IPPROTO_NVPII			11				/* network voice protocol*/
#define IPPROTO_PUP 			12				/* pup */
#define IPPROTO_ARGUS			13				/* Argus */
#define IPPROTO_EMCON			14				/* EMCON */
#define IPPROTO_XNET			15				/* Cross Net Debugger */
#define IPPROTO_CHAOS			16				/* Chaos*/
#define IPPROTO_MUX 			18				/* Multiplexing */
#define IPPROTO_MEAS			19				/* DCN Measurement Subsystems */
#define IPPROTO_HMP 			20				/* Host Monitoring */
#define IPPROTO_PRM 			21				/* Packet Radio Measurement */
#define IPPROTO_IDP 			22				/* xns idp */
#define IPPROTO_TRUNK1			23				/* Trunk-1 */
#define IPPROTO_TRUNK2			24				/* Trunk-2 */
#define IPPROTO_LEAF1			25				/* Leaf-1 */
#define IPPROTO_LEAF2			26				/* Leaf-2 */
#define IPPROTO_RDP 			27				/* Reliable Data */
#define IPPROTO_IRTP			28				/* Reliable Transaction */
#define IPPROTO_TP				29				/* tp-4 w/ class negotiation */
#define IPPROTO_BLT 			30				/* Bulk Data Transfer */
#define IPPROTO_NSP 			31				/* Network Services */
#define IPPROTO_INP 			32				/* Merit Internodal */
#define IPPROTO_SEP 			33				/* Sequential Exchange */
#define IPPROTO_3PC 			34				/* Third Party Connect */
#define IPPROTO_IDPR			35				/* InterDomain Policy Routing */
#define IPPROTO_XTP 			36				/* XTP */
#define IPPROTO_DDP 			37				/* Datagram Delivery */
#define IPPROTO_CMTP			38				/* Control Message Transport */
#define IPPROTO_TPXX			39				/* TP++ Transport */
#define IPPROTO_IL				40				/* IL transport protocol */
#define IPPROTO_SDRP			42				/* Source Demand Routing */
#define IPPROTO_ROUTING 		43				/* IP6 routing header */
#define IPPROTO_FRAGMENT		44				/* IP6 fragmentation header */
#define IPPROTO_IDRP			45				/* InterDomain Routing*/
#define IPPROTO_RSVP			46				/* resource reservation */
#define IPPROTO_GRE 			47				/* General Routing Encap. */
#define IPPROTO_MHRP			48				/* Mobile Host Routing */
#define IPPROTO_BHA 			49				/* BHA */
#define IPPROTO_ESP 			50				/* IP6 Encap Sec. Payload */
#define IPPROTO_AH				51				/* IP6 Auth Header */
#define IPPROTO_INLSP			52				/* Integ. Net Layer Security */
#define IPPROTO_SWIPE			53				/* IP with encryption */
#define IPPROTO_NHRP			54				/* Next Hop Resolution */
#define IPPROTO_MOBILE			55				/* IP Mobility */
#define IPPROTO_TLSP			56				/* Transport Layer Security */
#define IPPROTO_SKIP			57				/* SKIP */
#define IPPROTO_ICMPV6			58				/* ICMP6 */
#define IPPROTO_NONE			59				/* IP6 no next header */
#define IPPROTO_DSTOPTS 		60				/* IP6 destination option */
#define IPPROTO_AHIP			61				/* any host internal protocol */
#define IPPROTO_CFTP			62				/* CFTP */
#define IPPROTO_HELLO			63				/* "hello" routing protocol */
#define IPPROTO_SATEXPAK		64				/* SATNET/Backroom EXPAK */
#define IPPROTO_KRYPTOLAN		65				/* Kryptolan */
#define IPPROTO_RVD 			66				/* Remote Virtual Disk */
#define IPPROTO_IPPC			67				/* Pluribus Packet Core */
#define IPPROTO_ADFS			68				/* Any distributed FS */
#define IPPROTO_SATMON			69				/* Satnet Monitoring */
#define IPPROTO_VISA			70				/* VISA Protocol */
#define IPPROTO_IPCV			71				/* Packet Core Utility */
#define IPPROTO_CPNX			72				/* Comp. Prot. Net. Executive */
#define IPPROTO_CPHB			73				/* Comp. Prot. HeartBeat */
#define IPPROTO_WSN 			74				/* Wang Span Network */
#define IPPROTO_PVP 			75				/* Packet Video Protocol */
#define IPPROTO_BRSATMON		76				/* BackRoom SATNET Monitoring */
#define IPPROTO_ND				77				/* Sun net disk proto (temp.) */
#define IPPROTO_WBMON			78				/* WIDEBAND Monitoring */
#define IPPROTO_WBEXPAK 		79				/* WIDEBAND EXPAK */
#define IPPROTO_EON 			80				/* ISO cnlp */
#define IPPROTO_VMTP			81				/* VMTP */
#define IPPROTO_SVMTP			82				/* Secure VMTP */
#define IPPROTO_VINES			83				/* Banyon VINES */
#define IPPROTO_TTP 			84				/* TTP */
#define IPPROTO_IGP 			85				/* NSFNET-IGP */
#define IPPROTO_DGP 			86				/* dissimilar gateway prot. */
#define IPPROTO_TCF 			87				/* TCF */
#define IPPROTO_IGRP			88				/* Cisco/GXS IGRP */
#define IPPROTO_OSPFIGP 		89				/* OSPFIGP */
#define IPPROTO_SRPC			90				/* Strite RPC protocol */
#define IPPROTO_LARP			91				/* Locus Address Resoloution */
#define IPPROTO_MTP 			92				/* Multicast Transport */
#define IPPROTO_AX25			93				/* AX.25 Frames */
#define IPPROTO_IPEIP			94				/* IP encapsulated in IP */
#define IPPROTO_MICP			95				/* Mobile Int.ing control */
#define IPPROTO_SCCSP			96				/* Semaphore Comm. security */
#define IPPROTO_ETHERIP 		97				/* Ethernet IP encapsulation */
#define IPPROTO_ENCAP			98				/* encapsulation header */
#define IPPROTO_APES			99				/* any private encr. scheme */
#define IPPROTO_GMTP			100 			/* GMTP*/
#define IPPROTO_IPCOMP			108 			/* payload compression (IPComp) */
#define IPPROTO_SCTP			132 			/* SCTP */
#define IPPROTO_MH				135 			/* IPv6 Mobility Header */
#define IPPROTO_UDPLITE 		136 			/* UDP-Lite */
#define IPPROTO_HIP 			139 			/* IP6 Host Identity Protocol */
#define IPPROTO_SHIM6			140 			/* IP6 Shim6 Protocol */
/* 101-254: Partly Unassigned */
#define IPPROTO_PIM 			103 			/* Protocol Independent Mcast */
#define IPPROTO_CARP			112 			/* CARP */
#define IPPROTO_PGM 			113 			/* PGM */
#define IPPROTO_MPLS			137 			/* MPLS-in-IP */
#define IPPROTO_PFSYNC			240 			/* PFSYNC */
#define IPPROTO_RESERVED_253	253 			/* Reserved */
#define IPPROTO_RESERVED_254	254 			/* Reserved */
/* 255: Reserved */
/* BSD Private, local use, namespace incursion, no longer used */
#define IPPROTO_OLD_DIVERT		254 			/* OLD divert pseudo-proto */
#define IPPROTO_MAX 			256

/* last return value of *_input(), meaning "all job for this pkt is done".	*/
#define IPPROTO_DONE			257

/* Only used internally, so can be outside the range of valid IP protocols. */
#define IPPROTO_DIVERT			258 			/* divert pseudo-protocol */
#define IPPROTO_SEND			259 			/* SeND pseudo-protocol */
 
/*
* Defined to avoid confusion.	The master value is defined by
* PROTO_SPACER in sys/protosw.h.
*/
#define IPPROTO_SPACER			32767			/* spacer for loadable protos */
#define IPPORT_RESERVED 		1024
 
/*
* Default local port range, used by IP_PORTRANGE_DEFAULT
*/
#define IPPORT_EPHEMERALFIRST	10000
#define IPPORT_EPHEMERALLAST	65535 
 
/*
* Dynamic port range, used by IP_PORTRANGE_HIGH.
*/
#define IPPORT_HIFIRSTAUTO		49152
#define IPPORT_HILASTAUTO		65535

/*
* Scanning for a free reserved port return a value below IPPORT_RESERVED,
* but higher than IPPORT_RESERVEDSTART.  Traditionally the start value was
* 512, but that conflicts with some well-known-services that firewalls may
* have a fit if we use.
*/
#define IPPORT_RESERVEDSTART	600
#define IPPORT_MAX				65535


/*
* Options for use with [gs]etsockopt at the IP level.
* First word of comment is data type; bool is stored in int.
 */
#define IP_OPTIONS				1	 /* buf/ip_opts; set/get IP options */
#define IP_HDRINCL				2	 /* int; header is included with data */
#define IP_TOS					3	 /* int; IP type of service and preced. */
#define IP_TTL					4	 /* int; IP time to live */
#define IP_RECVOPTS 			5	 /* bool; receive all IP opts w/dgram */
#define IP_RECVRETOPTS			6	 /* bool; receive IP opts for response */
#define IP_RECVDSTADDR			7	 /* bool; receive IP dst addr w/dgram */
#define IP_SENDSRCADDR			IP_RECVDSTADDR /* cmsg_type to set src addr */
#define IP_RETOPTS				8	 /* ip_opts; set/get IP options */
#define IP_MULTICAST_IF 		9	 /* struct in_addr *or* struct ip_mreqn;
									  * set/get IP multicast i/f  */
#define IP_MULTICAST_TTL		10	 /* u_char; set/get IP multicast ttl */
#define IP_MULTICAST_LOOP		11	 /* u_char; set/get IP multicast loopback */
#define IP_ADD_MEMBERSHIP		12	 /* ip_mreq; add an IP group membership */
#define IP_DROP_MEMBERSHIP		13	 /* ip_mreq; drop an IP group membership */
#define IP_MULTICAST_VIF		14	 /* set/get IP mcast virt. iface */
#define IP_RSVP_ON				15	 /* enable RSVP in kernel */
#define IP_RSVP_OFF 			16	 /* disable RSVP in kernel */
#define IP_RSVP_VIF_ON			17	 /* set RSVP per-vif socket */
#define IP_RSVP_VIF_OFF 		18	 /* unset RSVP per-vif socket */
#define IP_PORTRANGE			19	 /* int; range to choose for unspec port */
#define IP_RECVIF				20	 /* bool; receive reception if w/dgram */
/* for IPSEC */
#define IP_IPSEC_POLICY 		21	 /* int; set/get security policy */
 									 /* unused; was IP_FAITH */
#define IP_ONESBCAST			23	 /* bool: send all-ones broadcast */
#define IP_BINDANY				24	 /* bool: allow bind to any address */
#define IP_BINDMULTI			25	 /* bool: allow multiple listeners on a tuple */
#define IP_RSS_LISTEN_BUCKET	26	 /* int; set RSS listen bucket */
#define IP_ORIGDSTADDR			27	 /* bool: receive IP dst addr/port w/dgram */




struct sockaddr_un {
		   unsigned char   sun_len; 	   /* sockaddr len including null */
		   sa_family_t	   sun_family;	   /* AF_UNIX */
		   char    sun_path[104];		   /* path name (gag) */
};



#include <sys/select.h>

struct timeval{
	long    tv_sec;      //Seconds. 
	long    tv_usec;     //Microseconds. Œ¢√Ó
};

struct timeval{
	time_t  tv_sec;    //Seconds. 
	long    tv_nsec;   //Nanoseconds.ƒ…√Î
}

void FD_SET(int fd, fd_set *fdset);
void FD_CLR(int fd, fd_set *fdset);
void FD_ZERO(fd_set *fdset);
int  FD_ISSET(int, fd_set *fdset);


int select(int maxfdpl, fd_set *readset, fd_set *writeset, fd_set *exceptset, struct timeval *timeout);
int  pselect(int, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timespec *timeout, const sigset_t *sigmask);



#include <poll.h>

struct  pollfd{
	int         fd;        //the following descriptor being polled
	short int   events;    //the input event flags (see below)
	short int   revents;   //the output event flags (see below)
}

int   poll(struct pollfd *fdarray, unsigned long nfds, int timeout_usec);


#endif


