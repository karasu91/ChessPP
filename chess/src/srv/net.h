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

class NetServer
{
public:
    NetServer() {};
    ~NetServer();
    bool initialize(void);
    std::string receiveData();
    uint16_t localPort;
	void sendData(std::string);
private:
    int _sock, _conn, _len;
    struct sockaddr_in _serverAddress, _client;
};

class NetClient
{
public:
    NetClient() {};
    ~NetClient();
    bool connectServer(std::string ip);
    bool sendData(std::string data);
    uint16_t targetPort;
private:
    int _sock;
	sockaddr_in _server;
	char message[TXRX_LEN], response[TXRX_LEN];
};
