/*!
 * Sylphrena AI input program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2018 Eirik Skjeggestad Dale
 */

#ifndef SYLNLP_H
#define SYLNLP_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

/*
*This is the main hub for sylphrenas Natural Language Processing unit.
*/
class sylNlp
{
public:
	explicit sylNlp();
	~sylNlp();
	void handleNewMessage(char *msg);
private:
};

#endif //SYLNLP_H

