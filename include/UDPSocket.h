#pragma once
#include <iostream>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <cstring>
#include "Packet.h"

const int BUFFER_SIZE = 500;

using namespace std;

class UDPSocket
{
    int socketFd = -1;
    in_port_t port;
    string ipAddress;
    string ipVer;

    char buffer[BUFFER_SIZE];

public:
    UDPSocket(const int socketFd);

    int sendTo(const struct sockaddr *target, const char *payload, int flags = 0);

    int sendTo(const struct sockaddr &target, Packet &packet, int flags = 0);

    Packet *waitAndRecv(int flags = MSG_WAITALL);

    void closeSocket() { close(this->socketFd); }

    string toString() { return "UDPSocket(" + this->ipAddress + ":" + to_string(this->port) + ")"; }

    ~ UDPSocket() {this->closeSocket();}
};

/**
 * @brief Get the address information for the specified hostname, port, and socket type.
 *
 * @param hostname
 * @param port
 * @param sockType
 * @return Pointer to a addrinfo
 */
addrinfo *getAddrInfo(const char *hostname, uint16_t port, int sockType = SOCK_DGRAM);


/**
 * @brief create a UDPSocket at hostname:port
 *
 * @param hostname a string hostname
 * @param hostPort the port. If 0 then the system will assign a random port number
 * @return A pointer to a UDPSocket
 */
UDPSocket *openUDPSocket(const char *hostname, uint16_t hostPort);
