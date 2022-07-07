#include "net.h"

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>	//write
#include <arpa/inet.h>	//inet_addr

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio.hpp>

#include <stdio.h>
#include <iostream>
#include "inttypes.h"

void NetServer::on_message(websocketpp::connection_hdl, server::message_ptr msg) {
	// handle different types of messages ?
	std::printf("Received: {}\n", msg->get_payload().c_str());
}




bool NetServer::initialize()
{
	printf("Initializing server...\n");
	_srv.set_message_handler(websocketpp::lib::bind(&NetServer::on_message, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
    _srv.set_access_channels(websocketpp::log::alevel::all);
    _srv.set_error_channels(websocketpp::log::elevel::all);

    _srv.init_asio();
    _srv.listen(_port);
    _srv.start_accept();

	initialized = true;
	std::cout << "Initialized successfully on port " << _port << std::endl;
	return true;
}

bool NetServer::run()
{
	std::printf("Starting server...\n");
	if (!initialized) {
		printf("Server is not initialized.\n Initialize first and try again.");
		return false;
	}

	_srv.run();

	return true;
};

void NetServer::send_data(const std::string s) {
	std::printf("Attempt to send_data...\n");
}

bool NetServer::set_port(const uint16_t& p)
{
	_port = p;
	std::printf("asdf");
	return true;
}

//
//NetServer::~NetServer() {
//	std::printf("SERVER: Closing socket...\n");
//	close(_sock);
//}
//
//bool NetServer::initialize()
//{
//    std::printf("SERVER: Initializing...\n");
//
//    // Create socket
//    if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//        std::printf("SERVER: socket creation failed.\n");
//        return false;
//    }
//
//    std::printf("SERVER: Socket successfully created.\n");
//    bzero(&_serverAddress, sizeof(_serverAddress));
//
//    // /* Assign listening method, port, etc.
//    _serverAddress.sin_family = AF_INET;
//    _serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
//    _serverAddress.sin_port = htons(localPort);
//
//    // Binding newly created socket to given IP and verification
//    if ((bind(_sock, (struct sockaddr*)&_serverAddress, sizeof(_serverAddress))) < 0) {
//        std::printf("SERVER: Socket binding failed.\n");
//        return false;
//    }
//
//    std::printf("SERVER: Socket successfully bound.\n");
//
//    // Set the server to accept maximum N connections simultaneously.
//    // (listen(_sock, N))
//    if ((listen(_sock, 3)) < 0) {
//        std::printf("SERVER: Listen failed...\n");
//        return false;
//    }
//    std::printf("SERVER: Started accepting connections...\n");
//
//    _len = sizeof(struct sockaddr_in);
//    std::printf("SERVER: Waiting for connections...\n");
//
//    // Establish/accept the connection and make it persistent over the session.
//    if ((_conn = accept(_sock, (struct sockaddr*)&_client, (socklen_t*)&_len)) < 0) {
//        printf("SERVER: Server acccept failed.");
//        return false;
//    }
//    printf("SERVER: Server acccepted a client (%s)\n", inet_ntoa(_client.sin_addr));
//
//    return true;
//}
//
//std::string NetServer::receiveData(void)
//{
//    char recvBuf[TXRX_LEN];
//    bzero(recvBuf, TXRX_LEN);
//
//    // Wait for a new message from the established client connection.
//    // read() blocks the execution until data is received.
//    if(read(_conn, recvBuf, TXRX_LEN) < 0)
//    {
//        printf("SERVER: Receive data timed out.\n");
//        return "err";
//    }
//
//	std::printf("SERVER: From client: %s\n", recvBuf);
//
//    // Prepare for 'handshake' message (verify that both ends received the message properly)
//    char sendBuf[TXRX_LEN] = "ACK";
//    write(_conn, sendBuf, sizeof(sendBuf));
//
//    return recvBuf;
//}
//
//void NetServer::sendData(std::string data) {
//	char sendBuf[TXRX_LEN];  // Make sure there's enough space
//	strcpy(sendBuf, data.c_str());
//	write(_conn, sendBuf, sizeof(sendBuf));
//}
//
//NetClient::~NetClient() {
//	std::printf("Closing socket...\n");
//	close(_sock);
//}
//
//
//
//bool NetClient::connectServer() {
//
//	if (ipaddr.length() < 7 || targetPort == 0)
//	{
//		_msgBuffer.push_back("Ip address (" + ipaddr + ") or port (" + std::to_string(targetPort) + ") is not set.\n");
//		return false;
//	}
//
//    _msgBuffer.push_back("Trying to connect to server... "+ ipaddr + ":" + std::to_string(targetPort));
//	// Create the initial socket
//	if ((_sock = socket(AF_INET , SOCK_STREAM , 0)) == -1)
//	{
//		_msgBuffer.push_back("Failed to create socket.\n");
//        return false;
//	}
//
//	_msgBuffer.push_back("Socket created successfully.\n");
//
//	_server.sin_addr.s_addr = inet_addr(ipaddr.c_str());
//	_server.sin_family = AF_INET;
//	_server.sin_port = htons( targetPort );
//
//	//Connect to remote server (server does ACCEPT for the connection if possible)
//	if (connect(_sock , (struct sockaddr *)&_server , sizeof(_server)) < 0)
//	{
//		_msgBuffer.push_back("Failed to establish connection.\n");
//		return false;
//	}
//
//    return true;
//}
//
//std::vector<std::string> NetClient::getMsgBuffer() {
//	return _msgBuffer;
//}
//
//bool NetClient::sendData(std::string data)
//{
//    // std::string not supported in send() -function ->
//    // the string must be copied into temporary buffer.
//    strcpy(message, data.c_str());
//
//    if(send(_sock, data.c_str(), strlen(message), 0) < 0)
//    {
//        _msgBuffer.push_back("Failed to send data.\n");
//        return false;
//    }
//
//    _msgBuffer.push_back("sendData() recv\n");
//
//    // Wait for the handshake message.
//    if(recv(_sock, response, TXRX_LEN, 0) < 0)
//    {
//        _msgBuffer.push_back("Receive data timed out.\n");
//        return false;
//    }
//
//    _msgBuffer.push_back("Server reply :" + std::string(response));
//	if (response != "OK") {
//		return false;
//	}
//
//
//    return true;
//}
