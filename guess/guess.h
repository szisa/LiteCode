#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif


void PrintMenu(int nRange);
bool Guess(int nRange);
void Setting(int* pRange);
bool View();
bool Save(int nNumber, int nRange, int nCount);

