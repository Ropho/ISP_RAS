#ifndef TCP_H
#define TCP_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>


enum ERRORS {

    SOCKET_VERSION_ERROR    = 1,
    IP_TRANSLATION_ERROR    = 2,
    SOCKET_INIT_ERROR       = 3,
    RECEIVIN_ERROR          = 4,
    BINDIN_ERROR            = 5,
    SENDIN_ERROR            = 6,
    LISTENIN_ERROR          = 7,
    CONNECTIN_ERROR         = 8,
};


enum REGIME {
    
    SERVER = 0,
    CLIENT = 1,
};


#endif