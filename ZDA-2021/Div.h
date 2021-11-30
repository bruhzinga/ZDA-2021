#pragma once
#include "stdafx.h"
#include "Log.h"

#define max_word 1000
#define size_word 20

char** divideText(char source[], int size);
void cleanup(char source[], int size, Log::LOG logfile);