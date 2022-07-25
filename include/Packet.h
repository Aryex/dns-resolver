#pragma once

#include <string>
#include <netinet/in.h>

using namespace std;

class Packet
{
    string content;
    sockaddr *source;

public:
    Packet(char *content, sockaddr *source) : content{content}, source{source} {};
    string &getContent() { return this->content; }
    sockaddr &getSource() { return *(this->source); }
};