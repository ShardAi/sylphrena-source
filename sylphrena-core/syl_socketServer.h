/*!
 * Sylphrena AI core program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

#ifndef SYLSOCKETSERVER_H
#define SYLSOCKETSERVER_H

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <syslog.h>
#include "syl_core.h"

using namespace std;

/*
*This is a basic socket class setting up a server listening to a single client.
*/
class sylCore;

class sylSocketServer
{
public:
	explicit sylSocketServer(sylCore *core);
	explicit sylSocketServer() {}
	~sylSocketServer();
    bool isConnected() { return connected; }
private:
    sylCore *core;
    bool connected;
    int client;
    int server;
    int portNum;
    struct sockaddr_in server_addr;
    socklen_t size;
    int bufSize;

    void connect();
    void listenForClients();
    void listenToClient();
    void messageReceived(const char* msg);
};

#endif //SYLSOCKETHANDLER_H

