#pragma once


#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

enum CALC
{
	CALC_MIN = 1,
	CALC_MAX,
	CALC_SUM,
	CALC_AVG,
	CALC_VRC,	// ·½²î
	CALC_DVA,	// ˜ËœÊ²î
	CALC_COUNT
};

void PrintMenu();

bool View(struct LIST* pList);
bool Push(struct LIST* pList);
bool Pop(struct LIST* pList);

bool Save(struct LIST* pList);
bool Load(struct LIST* pList);
bool Rand(struct LIST* pList);
bool Clear(struct LIST* pList);

bool Calc(struct LIST* pList, int nOperation);
