/*!
 * Sylphrena AI input program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "syl_socketClient.h"

using namespace std;

#define DAEMON_NAME "sylInputDaemon"

void print_usage()
{
    cout << "-----------Valid input for the core program is:------------------------" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "-----------\"#\": Close the program -----------------------------------" << endl;
    cout << "-----------\"iXXXXvYYYY\":  Give input node i (XXXX) value v (YYYY)----" << endl;
    cout << "-----------\"examplecommand\": Examplecommand result ------------------" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
}

int main(int argc, char *argv[])
{
	cout << "-----------Starting application to send input to Sylphrena-------------" << endl;


	/* A string listing valid short options letters. */
	const char* const short_options = "h:";
	/* An array describing valid long options. */
	const struct option long_options[] = {
		{ "help",		no_argument, NULL, 'h' },
		{ "NULL",		0, NULL, 0 } /* Required at end of array. */
	};

	int option_index = 0;
	int next_option;

	do
	{
		next_option = getopt_long(argc, argv, short_options, long_options, &option_index);
		switch (next_option)
		{
		case 'h': /* -h or --help */
			print_usage();
			break;
		case '?': /* The user specified an invalid option. */
			print_usage();
		case -1: /* Done with options. */
			break;
		default: /* Something else: unexpected. */
			abort();
		}
	}
	while (next_option != -1);

	sylSocketClient *c = new sylSocketClient();

	c->connectToServer();

	cout << "-----------Connection shut down, exiting sylphrena input program-------------" << endl;
	return 0;
}

