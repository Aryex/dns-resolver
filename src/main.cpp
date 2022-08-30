#include <iostream>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "my_library.h"

void resolveHostName(const char *hostname)
{
    using std::cout;
    using std::endl;
   const hostent *result = gethostbyname(hostname);
   cout << "hostname: " << result->h_name << endl;

   cout << "adresses: " << endl;
   struct in_addr **addr_list = (struct in_addr **)result->h_addr_list;
   for (int i = 0; addr_list[i] != NULL; i++)
   {
      cout << " - " << inet_ntoa(*addr_list[i]) << endl;
   }
   cout << "--------------------" << endl;
}

int main(int argc, char *argv[])
{
    using std::cout; 
    using std::endl;
    
    initialize();
    terminate();

   if (argc < 2)
   {
      cout << "Please enter at least one hostname" << endl;
      return 0;
   }

   for (int i = 1; i < argc; i++)
   {
      resolveHostName(argv[i]);
   }
}
