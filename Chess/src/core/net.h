#pragma once

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>	//write
#include <iostream>

#define TXRX_LEN 256

class Server
{
public:
    Server() {};
    ~Server() {};
    bool initialize(void);
    std::string receiveData();
    uint16_t localPort;    
private:
    int _sock, _conn, _len;
    struct sockaddr_in _serverAddress, _client;
};

class Client 
{
public:
    Client() {};
    ~Client() {};
    bool connectServer(std::string ip);
    bool sendData(std::string data);
    uint16_t targetPort;
private:
    int _sock;
	sockaddr_in _server;
	char message[TXRX_LEN], response[TXRX_LEN];
};