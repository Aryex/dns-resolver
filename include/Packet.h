#pragma once

#include <string>
#include <netinet/in.h>

using namespace std;

class Packet
{
    const string content;
    const sockaddr source;

public:
    Packet(char *content, sockaddr source) : content{content}, source{source} {};
    const string &getContent() { return this->content; }
    const sockaddr &getSource() { return this->source; }
};