#include "UDPSocket.h"
#include <string>
#include <netdb.h>

int main(int argc, char *argv[])
{
    UDPSocket socket = openUDPSocket("localhost", 8088);
    cout << "Listening on " << socket.toString() << endl;
    struct sockaddr client;
    while(true){
        char* msg = socket.waitAndRecv(&client);
        socket.sendTo(&client, msg);
    }
    
}