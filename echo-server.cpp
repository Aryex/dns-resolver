#include "UDPSocket.h"
#include <string>
#include <netdb.h>
#include <memory>

int main(int argc, char *argv[])
{
    unique_ptr<UDPSocket> socket(openUDPSocket("localhost", 8088));
    cout << "Listening on " << socket->toString() << endl;
    struct sockaddr client;
    
    while(true){
        unique_ptr<Packet> packet(socket->waitAndRecv());
        sockaddr source = packet->getSource();
        socket->sendTo(source, *packet);
    }

    return 0;
}