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

#define PATH_ROOT	"ÎÒµÄµçÄÔ"

#define KEY_ESC		0x00001B	// Esc
#define KEY_CMD		0x000003	// Ctrl + C
#define KEY_FIND	0x000006	// Ctrl + F

#define KEY_LEFT	0x00004B	// ¡û
#define KEY_RIGHT	0x00004D	// ¡ú
#define KEY_UP		0x000048	// ¡ü
#define KEY_DOWN	0x000050	// ¡ý
#define KEY_BACK	0x000008	// Backspace
#define KEY_ENTER	0x00000D	// Enter


#define CMD_FILE "dir \"%s\" /OG /N>path.io"
#define CMD_DISK "fsutil fsinfo drives>path.io"
#define MAX_PATH  2600
#define MAX_COUNT 2600
#define BUFF_SIZE 10240

static char s_szPath[MAX_PATH] = "";
static char s_szDirs[MAX_PATH][MAX_COUNT] = {0};
static char s_szFile[MAX_PATH][MAX_COUNT] = {0};

static int s_nDirsCounts = 0;
static int s_nFileCounts = 0;

char* MoveParent(char* szPath);
char* EnterDirectory(char* szPath, char* szDiry);
bool CmdCtrl(int nKey, int* pDiryIndex);
bool PrintFileView(char* szPath, char szDirs[][MAX_COUNT], char szFile[][MAX_COUNT], int nDirsCounts, int nFileCounts, int nDiryIndex);
bool GetPath(char* szPath);
bool GetRoot();
char* trim(char *str);
