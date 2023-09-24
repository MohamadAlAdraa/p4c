#include "ebpf_kernel.h"


#define EBPF_MASK(t, w) ((((t)(1)) << (w)) - (t)1)
#define BYTES(w) ((w) / 8)
#define write_partial(a, w, s, v) do { *((u8*)a) = ((*((u8*)a)) & ~(EBPF_MASK(u8, w) << s)) | (v << s) ; } while (0)
#define write_byte(base, offset, v) do { *(u8*)((base) + (offset)) = (v); } while (0)
#define bpf_trace_message(fmt, ...)


struct ethernet_t {
    u64 dstAddr; /* EthernetAddress */
    u64 srcAddr; /* EthernetAddress */
    u16 etherType; /* bit<16> */
    u8 ebpf_valid;
};
struct ipv4_t {
    u8 version; /* bit<4> */
    u8 ihl; /* bit<4> */
    u8 diffserv; /* bit<8> */
    u16 totalLen; /* bit<16> */
    u16 identification; /* bit<16> */
    u8 flags; /* bit<3> */
    u16 fragOffset; /* bit<13> */
    u8 ttl; /* bit<8> */
    u8 protocol; /* bit<8> */
    u16 hdrChecksum; /* bit<16> */
    u32 srcAddr; /* IPv4Address */
    u32 dstAddr; /* IPv4Address */
    u8 ebpf_valid;
};
struct tcp_t {
    u16 srcPort; /* bit<16> */
    u16 dstPort; /* bit<16> */
    u32 seqNo; /* bit<32> */
    u32 ackNo; /* bit<32> */
    u8 dataOffset; /* bit<4> */
    u8 res; /* bit<4> */
    u8 flags; /* bit<8> */
    u16 window; /* bit<16> */
    u16 checksum; /* bit<16> */
    u16 urgentPtr; /* bit<16> */
    u8 ebpf_valid;
};
struct metadata_t {
};
struct headers_t {
    struct ethernet_t eth; /* ethernet_t */
    struct ipv4_t ipv4; /* ipv4_t */
    struct tcp_t tcp; /* tcp_t */
};