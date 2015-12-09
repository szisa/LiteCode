#pragma once


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

#define KEY_ESC		0x00001B	// Esc
#define KEY_CMD		0x000003	// Ctrl + C

#define KEY_DIRE	0x0000E0	// ¡û
#define KEY_LEFT	0x00004B	// ¡û
#define KEY_RIGHT	0x00004D	// ¡ú
#define KEY_UP		0x000048	// ¡ü
#define KEY_DOWN	0x000050	// ¡ý

#define KEY_CT		0x000054	// T
#define KEY_CS		0x000053	// S
#define KEY_CQ		0x000051	// Q
#define KEY_T		0x000074	// t
#define KEY_S		0x000073	// s
#define KEY_Q		0x000071	// q

void Init();
int TranslateCommand(int* pYear, int* pMonth, int nToday);

int  PrintCalendar(int nYear, int nMonth);
int  PrintMonth(int nWeek, int nDay);

int fPrintMonth(FILE *fp, int nWeek, int nDay, int nToday);
int fPrintCalendar(char* szFileName, int nYear, int nMonth, int nToady);

void MoveMonth(int* pYear, int* pMonth, int nMove);
void MoveYear(int* pYear, int* pMonth, int nMove);

void GetDate(int* pYear, int* pMonth, int* nDay);
