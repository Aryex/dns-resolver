#pragma once

#include <string>
#include <netinet/in.h>

using namespace std;

class Packet
{
    string content;
    const sockaddr *source;

public:
    Packet(char *content, sockaddr *source) : content{content}, source{source} {};
    string &getContent() { return this->content; }
    const sockaddr *getSource() { return this->source; }
};