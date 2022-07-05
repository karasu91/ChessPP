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


NetServer::~NetServer() {
	std::cout << "SERVER: Closing socket..." << std::endl;
	close(_sock);
}

bool NetServer::initialize()
{
    std::cout << "SERVER: Initializing..." << std::endl;

    // Create socket
    if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cout << "SERVER: socket creation failed." << std::endl;
        return false;
    }

    std::cout << "SERVER: Socket successfully created." << std::endl;
    bzero(&_serverAddress, sizeof(_serverAddress));

    // /* Assign listening method, port, etc.
    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    _serverAddress.sin_port = htons(localPort);

    // Binding newly created socket to given IP and verification
    if ((bind(_sock, (struct sockaddr*)&_serverAddress, sizeof(_serverAddress))) < 0) {
        std::cout << "SERVER: Socket binding failed." << std::endl;
        return false;
    }

    std::cout <<  "SERVER: Socket successfully bound." << std::endl;

    // Set the server to accept maximum N connections simultaneously.
    // (listen(_sock, N))
    if ((listen(_sock, 3)) < 0) {
        std::cout << "SERVER: Listen failed...\n" << std::endl;
        return false;
    }
    std::cout << "SERVER: Started accepting connections..." << std::endl;

    _len = sizeof(struct sockaddr_in);
    std::cout << "SERVER: Waiting for connections..." << std::endl;

    // Establish/accept the connection and make it persistent over the session.
    if ((_conn = accept(_sock, (struct sockaddr*)&_client, (socklen_t*)&_len)) < 0) {
        std::cout << "SERVER: Server acccept failed." << std::endl;
        return false;
    }
    std::cout << "SERVER: Server acccepted a client." << std::endl;

    return true;
}

std::string NetServer::receiveData(void)
{
    char recvBuf[TXRX_LEN];
    bzero(recvBuf, TXRX_LEN);

    // Wait for a new message from the established client connection.
    // read() blocks the execution until data is received.
    if(read(_conn, recvBuf, TXRX_LEN) < 0)
    {
        std::cout << "SERVER: Receive data timed out." << std::endl;
        return "err";
    }

    printf("SERVER: From client: %s\n", recvBuf);

    // Prepare for 'handshake' message (verify that both ends received the message properly)
    char sendBuf[TXRX_LEN] = "OK";
    write(_conn, sendBuf, sizeof(sendBuf));

    return recvBuf;
}

void NetServer::sendData(std::string data) {
	char sendBuf[TXRX_LEN];  // Make sure there's enough space
	strcpy(sendBuf, data.c_str());
	write(_conn, sendBuf, sizeof(sendBuf));
}

NetClient::~NetClient() {
	std::cout << "CLIENT: Closing socket..." << std::endl;
	close(_sock);
}

bool NetClient::connectServer(std::string ipAddr) {

    std::cout << "CLIENT: Trying to connect to server... " << ipAddr << ":" << targetPort << std::endl;
	// Create the initial socket
	if ((_sock = socket(AF_INET , SOCK_STREAM , 0)) == -1)
	{
		std::cout << "CLIENT: Failed to create socket." << std::endl;
        return false;
	}

	std::cout << "CLIENT: Socket created successfully" << std::endl;

	_server.sin_addr.s_addr = inet_addr(ipAddr.c_str());
	_server.sin_family = AF_INET;
	_server.sin_port = htons( targetPort );

	//Connect to remote server (server does ACCEPT for the connection if possible)
	if (connect(_sock , (struct sockaddr *)&_server , sizeof(_server)) < 0)
	{
		perror("CLIENT: Failed to establish connection.");
		return false;
	}

    std::cout << "CLIENT: Connection established succesfully" << std::endl;
    return true;
}

bool NetClient::sendData(std::string data)
{
    // std::string not supported in send() -function ->
    // the string must be copied into temporary buffer.
    strcpy(message, data.c_str());

    if(send(_sock, data.c_str(), strlen(message), 0) < 0)
    {
        std::cout << "CLIENT: Failed to send data." << std::endl;
        return false;
    }

    std::cout << "CLIENT: sendData() recv" << std::endl;

    // Wait for the handshake message.
    if(recv(_sock, response, TXRX_LEN, 0) < 0)
    {
        std::cout << "CLIENT: Receive data timed out." << std::endl;
        return false;
    }

    std::cout << "CLIENT: Server reply :" << response << std::endl;
	if (response != "OK") {
		return false;
	}


    return true;
}
