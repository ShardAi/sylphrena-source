/*!
 * Sylphrena AI core program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

#include "syl_socketServer.h"

sylSocketServer::sylSocketServer(sylCore *core)
{
    this->core = core;
    portNum = 1500;
    connected = false;
    bufSize = 1024;

    while(true)
    {
        connect();
        if(!connected)
            sleep(1);
    }
}

sylSocketServer::~sylSocketServer()
{
    if(server >= 0)
        close(server);
    if(client >= 0)
        close(client);
}

void sylSocketServer::connect()
{
    //init socket
    client = socket(AF_INET, SOCK_STREAM, 0);

    if(client < 0)
    {
        //TODO: Make syslog error and exit program.
        connected = false;
        return;
    }

    connected = true;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    if(bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        connected = false;
        return;
    }

    size = sizeof(server_addr);

    listenForClients();

    close(client);
}

void sylSocketServer::listenForClients()
{
    //listening socket
    listen(client, 1);

    //accept client
    server = accept(client, (struct sockaddr*)&server_addr, &size);

    if(server < 0)
    {
        connected = false;
        return;
    }

    connected = true;

    listenToClient();
}

void sylSocketServer::listenToClient()
{

    char buffer[bufSize];
    bool isExit = false;

    while(!isExit)//(server > 0)
    {
        strcpy(buffer, "Server connected...\n");
        send(server, buffer, bufSize, 0);

        //Connected with client
        //Enter # to end the connection
        //Client:
        do
        {
            char msg[bufSize];
            strcpy(msg, "");
            do
            {
                recv(server, buffer, bufSize, 0);
                strcat(msg, buffer);
                strcat(msg, " ");
                if(*buffer == '#')
                {
                    *buffer = '*';
                    isExit = true;
                }
            } while(*buffer != '*');
            messageReceived(msg);
        } while(!isExit);

        close(server);
        connected = false;
    }
}

void sylSocketServer::messageReceived(const char *msg)
{
    core->msgReceived(msg);

    char reply[bufSize];
    strcpy(reply, "Message received: ");
    strcat(reply, msg);
    strcat(reply, "\n");
    send(server, reply, bufSize, 0);
    syslog(LOG_INFO, msg);
}

