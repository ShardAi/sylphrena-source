/*!
 * Sylphrena AI input program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

#ifndef SYLSOCKETCLIENT_H
#define SYLSOCKETCLIENT_H

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <syslog.h>
#include "syl_nlp.h"

using namespace std;

/*
*This is a basic socket class setting up a client to send info to a server.
*/
class sylSocketClient
{
public:
	explicit sylSocketClient();
	~sylSocketClient();
    bool isConnected() { return connected; }
    void connectToServer();
private:
    bool connected;
    int client;
    int portNum;
    struct sockaddr_in server_addr;
    int bufSize;
    char* ip;

    void readyReadAndWrite();

    sylNlp *nlp;
};

#endif //SYLSOCKETCLIENT_H

