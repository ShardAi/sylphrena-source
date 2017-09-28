/*!
 * Sylphrena AI core program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

#include "syl_core.h"

sylCore::sylCore()
{
	counter = 0;
}

sylCore::~sylCore()
{
    delete server;
}

void sylCore::startServer()
{
	server = new sylSocketServer(this);
}

void sylCore::counterMethod()
{
	counter++;
}

void sylCore::msgReceived(string msg)
{
    //TODO: Use msg!
    if(msg.length() < 13)
        return;
    cout << "EIRIKDEBUG PRINTING. " << endl;
    vector<string> tokens = sylLib::split(msg, ' ');

    for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
    {
        //TODO run command to neural network IF it is valid.
        cout << "{cmd: " << *it << ", cmd.length(): " << (*it).length() << ".} ";
    }
    cout << endl;
}
