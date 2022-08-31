
#include "UDPSocket.h"

using namespace std;

UDPSocket::UDPSocket(const int socketFd) : socketFd{socketFd}
{
    sockaddr sockAddr;
    socklen_t sockLen = (socklen_t)(sizeof sockAddr);
    getsockname(socketFd, &sockAddr, &sockLen);

    void *addr;
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)&sockAddr;
    addr = &(ipv4->sin_addr);
    ipVer = "IPv4";
    this->port = ntohs(ipv4->sin_port);

    char ipStr[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET, addr, ipStr, sizeof ipStr);
    this->ipAddress = ipStr;
}

int UDPSocket::sendTo(const struct sockaddr *target, const char *payload, int flags)
{
    char ipstr[INET6_ADDRSTRLEN];
    const struct sockaddr_in *targetIn = (sockaddr_in *)target;
    inet_ntop(targetIn->sin_family, &(targetIn->sin_addr), ipstr, sizeof ipstr);
    cout << "Sending udp packet to " << ipstr << ":" << ntohs(targetIn->sin_port) << endl;

    const int result = sendto(this->socketFd, payload, strlen(payload), flags, target, sizeof(*target));
    if (result < 0)
    {
        cout << "UDP send error: " << strerror(errno) << endl;
    }
    else
    {
        cout << "UDP message sent" << endl;
    }
    return result;
}

int UDPSocket::sendTo(const struct sockaddr &target, Packet &packet, int flags)
{
    const char* payload = packet.getContent().c_str();
    return UDPSocket::sendTo(&target, payload);
}

Packet *UDPSocket::waitAndRecv(int flags)
{
    cout << "listening..." << endl;
    sockaddr from;
    socklen_t socketLen = sizeof(struct sockaddr);
    const int recvLen = recvfrom(this->socketFd, this->buffer, BUFFER_SIZE, flags, &from, &socketLen);
    if (recvLen < 0)
    {
        cout << "UDP receive error: " << strerror(errno) << endl;
    }
    else
    {
        sockaddr_in *fromAddress = ((sockaddr_in *)&from);
        in_addr ipAddress = fromAddress->sin_addr;
        string port = to_string(ntohs(fromAddress->sin_port));
        cout << "received udp packet of " << recvLen << " bytes from " << inet_ntoa(ipAddress) << ":" << port << endl;
    }
    this->buffer[recvLen] = '\0';
    string str(this->buffer, strlen(buffer));
    cout << "got " << str << endl;
    return new Packet(buffer, from);
}

addrinfo *getAddrInfo(const char *hostname, uint16_t port, int sockType)
{
    struct addrinfo *addrInfoResults;
    int status;

    struct addrinfo hints = {};
    hints.ai_family = AF_UNSPEC; // either ip4 or ipv6
    hints.ai_socktype = sockType;
    hints.ai_flags = AI_PASSIVE; // let os decides the ip

    const char *portStr = to_string(port).c_str();

    if ((status = getaddrinfo(hostname, portStr, &hints, &addrInfoResults)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    return addrInfoResults;
}

UDPSocket *openUDPSocket(const char *hostname, uint16_t hostPort)
{
    struct addrinfo *addrInfoResults = getAddrInfo(hostname, hostPort, SOCK_DGRAM);

    int socketFd;
    char ipstr[INET6_ADDRSTRLEN];
    in_port_t port = 0;
    for (struct addrinfo *addrInfo = addrInfoResults; addrInfo != NULL; addrInfo = addrInfo->ai_next)
    {
        void *addr;
        char *ipver;

        if (addrInfo->ai_family == AF_INET)
        { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)addrInfo->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
            port = ntohs(ipv4->sin_port);
        }
        else
        { // IPv6 - Not supported yet so should error here?
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)addrInfo->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // convert the IP to a string and print it:
        inet_ntop(addrInfo->ai_family, addr, ipstr, sizeof ipstr);
        cout << "Binding to " << ipstr << ":" << port << endl;
        socketFd = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);

        // If stmts below check for errors.
        if (socketFd == -1)
            continue;

        if (bind(socketFd, addrInfo->ai_addr, addrInfo->ai_addrlen) == 0)
            break; /*Success!*/

        close(socketFd);
    }

    freeaddrinfo(addrInfoResults); // free the linked list
    return new UDPSocket(socketFd);
}
