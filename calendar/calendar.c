// calendar.cpp : Defines the entry point for the console application.
//

#include "calendar.h"

struct Config
{
	bool bShowToday;

}_config;

int main(int argc, char* argv[])
{
	int nYear = 0, nMonth = 0, nControl = 0;
	int nYearNow = 0, nMonthNow = 0, nDayNow = 0;

	Init();
	GetDate(&nYearNow, &nMonthNow, &nDayNow);
	nYear = nYearNow;
	nMonth = nMonthNow;
	PrintCalendar(nYear, nMonth, nDayNow);

	while(nControl != KEY_ESC)
	{
		nControl = getch();
		switch(nControl)
		{
		case KEY_DIRE:
			switch(getch())
			{
			case KEY_LEFT	: MoveMonth(&nYear, &nMonth, -1); break; // ←
			case KEY_UP		: MoveYear(&nYear,  &nMonth, -1); break; // ↑
			case KEY_RIGHT	: MoveMonth(&nYear, &nMonth,  1); break; // →
			case KEY_DOWN	: MoveYear(&nYear,  &nMonth,  1); break; // ↓
			}
			break;
		case KEY_CT		: 
		case KEY_T		: 
			if(TranslateCommand(&nYear, &nMonth, (nMonth != nMonthNow || nYear != nYearNow) ? -1 : nDayNow, 'T'))
			{
				PrintCalendar(nYear, nMonth, (nMonth != nMonthNow || nYear != nYearNow) ? -1 : nDayNow);
				printf("\aError Year Or month! ");
				continue; 
			}
			else
			{
				break; 
			}
		case KEY_CQ		: 
		case KEY_Q		: 
			TranslateCommand(&nYear, &nMonth, (nMonth != nMonthNow || nYear != nYearNow) ? -1 : nDayNow, 'Q');
			break;
		case KEY_CS		: 
		case KEY_S		: 
			if(TranslateCommand(&nYear, &nMonth, (nMonth != nMonthNow || nYear != nYearNow) ? -1 : nDayNow, 'S'))
			{
				PrintCalendar(nYear, nMonth, (nMonth != nMonthNow || nYear != nYearNow) ? -1 : nDayNow);
				printf("\aSave Failed! ");
				continue;
			}
			else
			{
				printf("\aSave Success! ");
				getchar(); 
				break;
			}
		default: continue;
		}
		PrintCalendar(nYear, nMonth, (nMonth != nMonthNow || nYear != nYearNow) ? -1 : nDayNow);
	}

	return 0;
}

void Init()
{
	_config.bShowToday = true;
}

int TranslateCommand(int* pYear, int* pMonth, int nToday, char cCmd)
{
	if('T' == cCmd)
	{
		int nYear = 0, nMonth = 0;
		printf("\r\t\t\t\t\t\t\t\rYear-Month: ");
		scanf("%d-%d", &nYear, &nMonth);
		if(nYear <= 0 || nMonth > 12 || nMonth <= 0)
			return 1;
		*pYear = nYear;
		*pMonth = nMonth;
		printf("\a");
		return 0;
	}
	if('S' == cCmd)
	{
		char szFile[260];
		printf("\rPrint the file name: ");
		scanf_s("%s", szFile, 260);
		return fPrintCalendar(szFile, *pYear, *pMonth, nToday); // Save Calendar to File
	}
	if('Q' == cCmd)
	{
		exit(0); // Quit
	}
	return 0;
}

int PrintMonth(int nWeek, int nDay, int nToday)
{
	int i = 0;

	if(nWeek > 7 || nWeek < 0 || nDay > 31 || nDay < 0)
		return 1;

	for(i = 0; i < nWeek; i++)
		printf("   ");
	for(i = 1; i <= nDay; i++)
	{
		_config.bShowToday && nToday == i ? printf("|") : (_config.bShowToday && nToday == i - 1 ? printf("|") : printf(" "));
		printf("%2d", i);
		nWeek++;
		if(0 == nWeek % 7)
			printf("\n");
	}
	nToday == i - 1 ? printf("|") : printf(" ");
	printf("\n");

	return 0;
}

int PrintCalendar(int nYear, int nMonth, int nToady)
{
	int nWeek = 0, i = 0;	// nWeek is the week of first Day，nFebDays is Feb.'s days in this year 
	int nDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(nMonth > 12 || nMonth < 1 || nYear < 0) 
		return 1;

	system("cls");

	nWeek = nYear + (nYear - 1) / 4 - (nYear-1) / 100 + (nYear - 1) / 400;
	nWeek = nWeek -(nWeek / 7) * 7;

	if(nMonth > 1 && ((nYear % 4 == 0)&&(nYear % 100 != 0))||(nYear % 400 == 0)) 
		nDays[1] = 29;

	for(i = nMonth - 2; i >= 0; i--)
	{
		nWeek += nDays[i];
	}

	nWeek = nWeek % 7;

	printf("      %04d - %02d	\n", nYear, nMonth);
	printf(" 日 一 二 三 四 五 六\n");

	PrintMonth(nWeek, nDays[nMonth - 1], nToady);

	printf("S - Save  T - To Date  Q - Quit\n");
	return 0;
}

int fPrintMonth(FILE *fp, int nWeek, int nDay, int nToday)
{
	int i = 0;

	if(nWeek > 7 || nWeek < 0 || nDay > 31 || nDay < 0)
		return 1;

	for(i = 0; i < nWeek; i++)
		fprintf(fp, "   ");
	for(i = 1; i <= nDay; i++)
	{
		_config.bShowToday && nToday == i ? fprintf(fp, "|") : (_config.bShowToday && nToday == i - 1 ? fprintf(fp, "|") : fprintf(fp, " "));
		fprintf(fp, "%2d", i);
		nWeek++;
		if(0 == nWeek % 7)
			fprintf(fp, "\r\n");
	}
	nToday == i - 1 ? fprintf(fp, "|") : fprintf(fp, " ");
	fprintf(fp, "\r\n");

	return 0;
}

int fPrintCalendar(char* szFileName, int nYear, int nMonth, int nToady)
{
	FILE *fp;

	int nWeek = 0, i = 0;	// nWeek is the week of first Day，nFebDays is Feb.'s days in this year 
	int nDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(nMonth > 12 || nMonth < 1 || nYear < 0) 
		return 1;

    if(NULL == (fp = fopen(szFileName, "wb+")))
	{
        printf("\nOpen file failed! Press any key to continue...");
		getch();
		return 0;
    }

	nWeek = nYear + (nYear - 1) / 4 - (nYear-1) / 100 + (nYear - 1) / 400;
	nWeek = nWeek -(nWeek / 7) * 7;

	if(nMonth > 1 && ((nYear % 4 == 0)&&(nYear % 100 != 0))||(nYear % 400 == 0)) 
		nDays[1] = 29;

	for(i = nMonth - 2; i >= 0; i--)
	{
		nWeek += nDays[i];
	}

	nWeek = nWeek % 7;

	fprintf(fp, "      %04d - %02d	\r\n", nYear, nMonth);
	fprintf(fp, " 日 一 二 三 四 五 六\r\n");

	fPrintMonth(fp, nWeek, nDays[nMonth - 1], nToady);

	fclose(fp);

	return 0;
}

void MoveMonth(int* pYear, int* pMonth, int nMove)
{
	*pMonth += nMove;
	if(*pMonth > 12)
	{
		*pYear += *pMonth / 12;
		*pMonth = *pMonth % 12;
	}
	if(*pMonth < 1)
	{
		*pYear -= 1;
		*pMonth = *pMonth + 12;
	}
}

void MoveYear(int* pYear, int* pMonth, int nMove)
{
	*pYear += nMove;
}

void GetDate(int* pYear, int* pMonth, int* pDay)
{
	time_t rawtime; 
	struct tm * timeinfo; 
	time(&rawtime); 
	timeinfo = localtime(&rawtime); 
	*pYear = timeinfo->tm_year + 1900;
	*pMonth = timeinfo->tm_mon + 1;
	*pDay = timeinfo->tm_mday;
}

bool isNumber(char* szInput)
{
	int i = 0;
	while(szInput[i] != '\0')
	{
		if(!isdigit(szInput[i++]))
			return false;
	}
	return true;
}
