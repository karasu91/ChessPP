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
#include <functional>
#include <vector>

#define TXRX_LEN 256


#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

class NetServer
{
public:
	NetServer() { std::printf("ctor"); };
    ~NetServer() { std::printf(""); };

    bool initialize(void);
    std::string receive_data() {};   

    bool set_port(const uint16_t&);
    bool run();

    bool initialized = false;

	void send_data(const std::string d);
	void on_message(websocketpp::connection_hdl, server::message_ptr ptr);
    
private:
    server _srv;
    uint16_t _port;
    int _sock, _conn, _len;
    struct sockaddr_in _serverAddress, _client;
};

class NetClient
{
public:
    NetClient() { std::cout << "Allocating netclient..." << std::endl; };
    ~NetClient();

    bool connectServer();
    bool sendData(std::string data);
    uint16_t targetPort;
	std::string ipaddr;
	std::vector<std::string> getMsgBuffer();
private:
	std::vector<std::string> _msgBuffer;
    int _sock;
	sockaddr_in _server;
	char message[TXRX_LEN], response[TXRX_LEN];
};
