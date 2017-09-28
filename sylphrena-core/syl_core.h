/*!
 * Sylphrena AI core program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

#ifndef SYLCORE_H
#define SYLCORE_H

#include <stdlib.h>
#include <iostream>
#include <syslog.h>
#include <vector>
#include <sstream>
#include <iterator>
#include "syl_socketServer.h"
#include "syl_lib.h"

using namespace std;

class sylSocketServer;

class sylCore
{
public:
	explicit sylCore();
	~sylCore();

	void counterMethod();
	void startServer();
	void msgReceived(string msg);

private:
	int counter;
	sylSocketServer *server;
};

#endif //SYLCORE_H
