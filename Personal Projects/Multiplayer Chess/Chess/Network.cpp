#pragma once
#include "stdafx.h"

#undef UNICODE

#include "Chess.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512

WSADATA wsaData;
int iResult;

SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;

struct addrinfo *result = NULL;
struct addrinfo hints;

int iSendResult;
char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;


struct addrinfo *ptr = NULL;


string startServer(string port)
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return "WSAStartup failed with error: " + iResult;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
	if (iResult != 0) {
		WSACleanup();
		return "getaddrinfo failed with error: " + iResult;

	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		string err = "socket failed with error: " + WSAGetLastError();
		freeaddrinfo(result);
		WSACleanup();
		return err;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		string err = "bind failed with error: " + WSAGetLastError();
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return err;

	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		string err = "listen failed with error: " + WSAGetLastError();
		closesocket(ListenSocket);
		WSACleanup();
		return err;
	}
	shutdown(ListenSocket, SD_BOTH);
	return "Server Started";
}

string connectToClient()
{
	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		string err = "accept failed with error: " + WSAGetLastError();
		closesocket(ListenSocket);
		WSACleanup();
		return err;
	}

	// No longer need server socket
	closesocket(ListenSocket);
	return "Opponent Connected";
}

void cancelConnect()
{
	shutdown(ListenSocket, SD_RECEIVE);		
	closesocket(ListenSocket);
	WSACleanup();
}

string stopServer()
{
	iResult = shutdown(ClientSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		string err = "shutdown failed with error: " + WSAGetLastError();
		closesocket(ClientSocket);
		WSACleanup();
		return err;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return "Server stopped";
}

string clientConnect(string ip, string port)
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return "WSAStartup failed with error: " + iResult;		
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0) {		
		WSACleanup();
		return "getaddrinfo failed with error: " + iResult;		
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ClientSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ClientSocket == INVALID_SOCKET) {
			string err = "socket failed with error: " + WSAGetLastError();
			WSACleanup();
			return err;
		}

		// Connect to server.
		iResult = connect(ClientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ClientSocket);
			ClientSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ClientSocket == INVALID_SOCKET) {
		
		WSACleanup();
		return "Unable to connect to server!";
	}
	return "Connected to server";
}


string clientShutdown()
{
	iResult = shutdown(ClientSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		string err = "shutdown failed with error: " + WSAGetLastError();
		closesocket(ClientSocket);
		WSACleanup();
		return err;
	}
	closesocket(ClientSocket);
	WSACleanup();
	return "Connection stopped";
}


string readMessage()
{
	while (true)
	{
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			send(ClientSocket, "received", 9, 0);
			return recvbuf;
		}
		else if (iResult == 0)
		{
			//nothing received
			//return "Nothing";
		}
		else {
			string err = "recv failed with error: " + WSAGetLastError();
			closesocket(ClientSocket);
			WSACleanup();
			return err;
		}
	}
}

string sendMessage(string message)
{
	while (true)
	{
		iSendResult = send(ClientSocket, message.c_str(), message.length() + 1, 0);
		if (iSendResult == SOCKET_ERROR) {
			string err = "send failed with error: " + WSAGetLastError();
			closesocket(ClientSocket);
			WSACleanup();
			return err;
		}
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			if (strcmp(recvbuf, "received")==0)
			{
				break;
			}
		}

	}
	return "Message Sent";
}





