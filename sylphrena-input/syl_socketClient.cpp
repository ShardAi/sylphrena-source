/*!
 * Sylphrena AI input program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

#include "syl_socketClient.h"

sylSocketClient::sylSocketClient()
{
    portNum = 1500; //Must be the same for both client and server. Can be used to setup different applications communicating with the server and differentiating them!
    bufSize = 1024;
    ip = "127.0.0.1";
}
sylSocketClient::~sylSocketClient()
{
    if(client >= 0)
        close(client);
}

void sylSocketClient::connectToServer()
{
    client = socket(AF_INET, SOCK_STREAM, 0);

    if(client < 0)
    {
        //TODO: Make syslog error and exit program.
        connected = false;
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    if(connect(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0)
        cout << "--- Connection to the sylphrena server port number: " << portNum << endl;

    readyReadAndWrite();

    close(client);
    return;
}

void sylSocketClient::readyReadAndWrite()
{
    char buffer[bufSize];
    bool isExit = false;

    cout << "--- Awaiting confirmation from server...." << endl;
    recv(client, buffer, bufSize, 0);
    cout << "--- Connection confirmed by message: " << buffer << endl;
    cout << "--- You can now type the message you want to send. Send message by adding \* at the end." << endl;
    cout << "--- Enter # to end the connection and exit this program." << endl;

    do
    {
        cout << "Client: ";
        do
        {
            cin >> buffer;
            send(client, buffer, bufSize, 0);
            if(*buffer == '#')
            {
                send(client, buffer, bufSize, 0);
                *buffer = '*';
                isExit = true;
            }
        } while(*buffer != '*');

        cout << "Server: ";
        recv(client, buffer, bufSize, 0);
        cout << buffer << " ";
        if(*buffer == '#')
        {
            *buffer = '*';
            isExit = true;
        }
        cout << endl;
    } while(!isExit);
}
