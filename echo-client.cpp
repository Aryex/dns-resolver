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
#include <cstring>
#include "UDPSocket.h"
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
//    UDPSocket *udp = openUDPSocket("localhost", 35907);
   unique_ptr<UDPSocket> udp(openUDPSocket("localhost", 35907));
   cout << udp->toString() << endl;

   char ipstr[INET6_ADDRSTRLEN];
   unique_ptr<addrinfo> toAddr(getAddrInfo("localhost", 8088, SOCK_DGRAM));
   sockaddr *target = toAddr->ai_addr;

   udp->sendTo(target, "Catdog");

   unique_ptr<Packet> packet(udp->waitAndRecv());
   cout << "Server said: " << packet->getContent() << endl;
   udp->closeSocket();

   return 0;
}