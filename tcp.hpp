#pragma once

/* TCP socket options */
#ifndef TCP_NODELAY
#define TCP_NODELAY     1   /* Turn off Nagle's algorithm. */
#endif
#ifndef TCP_MAXSEG
#define TCP_MAXSEG      2   /* Limit MSS */
#endif
#ifndef TCP_CORK
#define TCP_CORK        3   /* Never send partially complete segments */
#endif
#ifndef TCP_KEEPIDLE
#define TCP_KEEPIDLE        4   /* Start keeplives after this period */
#endif
#ifndef TCP_KEEPINTVL
#define TCP_KEEPINTVL       5   /* Interval between keepalives */
#endif
#ifndef TCP_KEEPCNT
#define TCP_KEEPCNT     6   /* Number of keepalives before death */
#endif
#ifndef TCP_SYNCNT
#define TCP_SYNCNT      7   /* Number of SYN retransmits */
#endif
#ifndef TCP_LINGER2
#define TCP_LINGER2     8   /* Life time of orphaned FIN-WAIT-2 state */
#endif
#ifndef TCP_DEFER_ACCEPT
#define TCP_DEFER_ACCEPT    9   /* Wake up listener only when data arrive */
#endif
#ifndef TCP_WINDOW_CLAMP
#define TCP_WINDOW_CLAMP    10  /* Bound advertised window */
#endif
#ifndef TCP_INFO
#define TCP_INFO        11  /* Information about this connection. */
#endif
#ifndef TCP_QUICKACK
#define TCP_QUICKACK        12  /* Block/reenable quick acks */
#endif
#ifndef TCP_CONGESTION
#define TCP_CONGESTION      13  /* Congestion control algorithm */
#endif
#ifndef TCP_MD5SIG
#define TCP_MD5SIG      14  /* TCP MD5 Signature (RFC2385) */
#endif
#ifndef TCP_THIN_LINEAR_TIMEOUTS
#define TCP_THIN_LINEAR_TIMEOUTS 16      /* Use linear timeouts for thin streams*/
#endif
#ifndef TCP_THIN_DUPACK
#define TCP_THIN_DUPACK         17      /* Fast retrans. after 1 dupack */
#endif
#ifndef TCP_USER_TIMEOUT
#define TCP_USER_TIMEOUT    18  /* How long for loss retry before timeout */
#endif
#ifndef TCP_REPAIR
#define TCP_REPAIR      19  /* TCP sock is under repair right now */
#endif
#ifndef TCP_REPAIR_QUEUE
#define TCP_REPAIR_QUEUE    20
#endif
#ifndef TCP_QUEUE_SEQ
#define TCP_QUEUE_SEQ       21
#endif
#ifndef TCP_REPAIR_OPTIONS
#define TCP_REPAIR_OPTIONS  22
#endif
#ifndef TCP_FASTOPEN
#define TCP_FASTOPEN        23  /* Enable FastOpen on listeners */
#endif
#ifndef TCP_TIMESTAMP
#define TCP_TIMESTAMP       24
#endif
#ifndef TCP_NOTSENT_LOWAT
#define TCP_NOTSENT_LOWAT   25  /* limit number of unsent bytes in write queue */
#endif
#ifndef TCP_CC_INFO
#define TCP_CC_INFO     26  /* Get Congestion Control (optional) info */
#endif
#ifndef TCP_SAVE_SYN
#define TCP_SAVE_SYN        27  /* Record SYN headers for new connections */
#endif
#ifndef TCP_SAVED_SYN
#define TCP_SAVED_SYN       28  /* Get SYN headers recorded for connection */
#endif
#ifndef TCP_REPAIR_WINDOW
#define TCP_REPAIR_WINDOW   29  /* Get/set window parameters */
#endif
#ifndef TCP_FASTOPEN_CONNECT
#define TCP_FASTOPEN_CONNECT    30  /* Attempt FastOpen with connect */
#endif
#ifndef TCP_ULP
#define TCP_ULP         31  /* Attach a ULP to a TCP connection */
#endif
#ifndef TCP_MD5SIG_EXT
#define TCP_MD5SIG_EXT      32  /* TCP MD5 Signature with extensions */
#endif
#ifndef TCP_FASTOPEN_KEY
#define TCP_FASTOPEN_KEY    33  /* Set the key for Fast Open (cookie) */
#endif
#ifndef TCP_FASTOPEN_NO_COOKIE
#define TCP_FASTOPEN_NO_COOKIE  34  /* Enable TFO without a TFO cookie */
#endif
#ifndef TCP_ZEROCOPY_RECEIVE
#define TCP_ZEROCOPY_RECEIVE    35
#endif
#ifndef TCP_INQ
#define TCP_INQ         36  /* Notify bytes available to read as a cmsg on read */
#endif

