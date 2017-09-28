/*!
 * Sylphrena AI core program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

#include "syl_lib.h"

vector<string> sylLib::split(const string &s, char delimiter)
{
    vector<string> tokens;
    size_t startPoint = 0, endPoint = 0;
    while((endPoint = s.find(delimiter, startPoint)) != string::npos)
    {
        if(endPoint != startPoint)
            tokens.push_back(s.substr(startPoint, endPoint - startPoint));
        startPoint = endPoint + 1;
    }
    if(endPoint != startPoint)
        tokens.push_back(s.substr(startPoint));
    return tokens;
}
