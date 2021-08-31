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


bool Server::initialize()
{  
    std::cout << "SERVER: Initializing..." << std::endl;

    // socket create and verification
    if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cout << "SERVER: socket creation failed." << std::endl;
        return false;
    }

    std::cout << "SERVER: Socket successfully created." << std::endl;
    bzero(&_serverAddress, sizeof(_serverAddress));
  
    // assign IP, PORT
    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    _serverAddress.sin_port = htons(localPort);
  
    // Binding newly created socket to given IP and verification
    if ((bind(_sock, (struct sockaddr*)&_serverAddress, sizeof(_serverAddress))) < 0) {
        std::cout << "SERVER: Socket binding failed." << std::endl;
        return false;
    }

    std::cout <<  "SERVER: Socket successfully bound." << std::endl;
  
    // Now server is ready to listen and verification
    if ((listen(_sock, 3)) < 0) {
        std::cout << "SERVER: Listen failed...\n" << std::endl;
        return false;
    }

    std::cout << "SERVER: Server successfully listening..." << std::endl;
    _len = sizeof(struct sockaddr_in);
    
    std::cout << "SERVER: Waiting for connection request.." << std::endl;
    // Accept the data packet from client and verification
    if ((_conn = accept(_sock, (struct sockaddr*)&_client, (socklen_t*)&_len)) < 0) {
        std::cout << "SERVER: Server acccept failed." << std::endl;
        return false;
    }

    std::cout << "SERVER: Server acccepted the client." << std::endl;

    return true;
}  

std::string Server::receiveData(void) 
{    
    std::cout << "SERVER: Entered receiveData()..." << std::endl;
    char recvBuf[MAX];
    int n;

    bzero(recvBuf, MAX);

    std::cout << "SERVER: read()..." << std::endl;
    // read the message from client and copy it in buffer
    if(read(_conn, recvBuf, MAX) < 0)
    {
        std::cout << "SERVER: Receive data timed out." << std::endl;
        return "err";
    }
    
    if (n < 0) {
        printf("ERROR reading from socket");
        return "err";
    }
    
    // print buffer which contains the client contents
    printf("SERVER: From client: %s\n", recvBuf);
    
    //bzero(recvBuf, MAX);
    //n = 0;

    char sendBuf[MAX] = "OK";

    // and send that buffer to client
    write(_conn, sendBuf, sizeof(sendBuf));

    // if msg contains "Exit" then server exit and chat ended.
    if (strncmp("exit", sendBuf, 4) == 0) {
        printf("SERVER: Server Exit...\n");
    }
    return recvBuf;
}


bool Client::connectServer(std::string ipAddr) {
	
    std::cout << "CLIENT: Trying to connect to server... " << ipAddr << ":" << targetPort << std::endl;
	//Create socket
	if ((_sock = socket(AF_INET , SOCK_STREAM , 0)) == -1)
	{
		std::cout << "CLIENT: Failed to create socket." << std::endl;
        return false;
	}

	std::cout << "CLIENT: Socket created successfully" << std::endl;
	
	server.sin_addr.s_addr = inet_addr(ipAddr.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons( targetPort );

	//Connect to remote server
	if (connect(_sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("CLIENT: Failed to establish connection.");
		return false;
	}

    std::cout << "CLIENT: Connection established succesfully" << std::endl;
    return true;
}

bool Client::sendData(std::string data) 
{    
    std::cout << "CLIENT: sendData() send" << std::endl;

    // Send some data
    strcpy(message, data.c_str());

    if(send(_sock, data.c_str(), strlen(message), 0) < 0)
    {
        std::cout << "CLIENT: Failed to send data." << std::endl;
        return false;
    }
    
    std::cout << "CLIENT: sendData() recv" << std::endl;
    // Receive a reply from the server
    if(recv(_sock, response, MAX, 0) < 0)
    {
        std::cout << "CLIENT: Receive data timed out." << std::endl;
        return false;
    }
    
    std::cout << "CLIENT: Server reply :" << response << std::endl;
    return true;
}