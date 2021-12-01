#pragma once

#include "resource.h"
#include <string>

using namespace std;

string startServer(string port);

string connectToClient();
string stopServer();
void cancelConnect();
string clientConnect(string ip, string port);
string clientShutdown();
string sendMessage(string message);
string readMessage();
