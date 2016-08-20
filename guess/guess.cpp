// guess.cpp : Defines the entry point for the console application.
//

#include "guess.h"

int main(int argc, char* argv[])
{
	int nNumber = 0, nRange = 1000;
	srand((unsigned)time(NULL));

	while(true)
	{
		PrintMenu(nRange);
		switch(getch())
		{
		case '1': Guess(nRange); break;
		case '2': Setting(&nRange); break;
		case '3': View(); break;
		case '4': return 0;
		default : continue;		
		}
		system("PAUSE");
	}
	return 0;
}

void PrintMenu(int nRange)
{
	system("CLS");
	printf("Welcome to play 'Guess Number'!\n");
	printf("\n");
	printf("1. Begin to Play!\n");
	printf("2. Setting the Number Range(1 ~ %d)!\n", nRange);
	printf("3. View the Record!\n");
	printf("4. Quit the Game!\n");
	printf("\n");
}

bool View()
{
	int nNumber = 0, nRange = 0, nCount = 0;
	char szbuff[1024] = "";
	FILE * fp = NULL;

    fp = fopen("Record.io", "r");

    if(NULL == fp)
    {
        printf("View Record Failed.. \n");
		return false;
    }   

	printf("Guess\tCount\tRange\n");

	while(!feof(fp)) 
	{
		nNumber = nRange = nCount = 0;
		memset(szbuff, 0, 1024);
		fgets(szbuff, 1024, fp);
		if(strlen(szbuff) <= 0) continue;
		sscanf(szbuff, "%d,%d,%d", &nNumber, &nRange, &nCount);
		printf("%d\t%d\t1~%d\n", nNumber, nCount, nRange);
	}

	fclose(fp);
	return true;
}

void Setting(int* pRange)
{
	printf("The Old Range: 1 ~ %d\n", *pRange);
	printf("The New Range: 1 ~ ");
	scanf("%d", pRange);
	if(*pRange > 0)
		printf("Save Success..The New Range is 1 ~ %d\n", *pRange);
	else
		printf("Not a Vaild Range..\n");
}

bool Guess(int nRange)
{
	int nInput = 0, nCount = 0;
	int nNumber = rand() % nRange + 1;

	system("CLS");
	printf("Begin Game Number now!\n");
	printf("(Note : Input the number zero or less, you can cancel the game.)\n");
	while(true)
	{
		scanf("%d", &nInput);
		if(nInput <= 0)
		{
			printf("Cancel The Game..the number is %d\n", nNumber);
			return false;
		}
		else if(nInput == nNumber)
		{
			printf("Oh! You get it! You Guess %d times.\n", nCount);
			Save(nNumber, nRange, nCount);
			break;
		}
		else if(nInput < nNumber)
		{
			printf("Oh! It's too small!\a\n");
		}
		else if(nInput > nNumber)
		{
			printf("Oh! It's too big!\a\n");
		}

		nCount++;
	}
	return true;
}

bool Save(int nNumber, int nRange, int nCount)
{
	FILE * fp = NULL;

    fp = fopen("Record.io", "ab");

    if(NULL == fp)
    {
        printf("Save Record Failed.. \n");
		return false;
    }   

	fseek(fp, SEEK_END, 0); 

	fprintf(fp, "%d,%d,%d\r\n", nNumber, nRange, nCount);

	fclose(fp);

	return true;
}

bool LoadSetting(int* pRange)
{
	FILE * fp = NULL;

    fp = fopen("Setting.io", "rb");

    if(NULL == fp)
    {
        printf("Save Record Failed.. \n");
		return false;
    }   

	fscanf(fp, "%d", pRange);

	fclose(fp);

	return true;
}

bool SaveSetting(int nRange)
{
	FILE * fp = NULL;

    fp = fopen("Setting.io", "wb");

    if(NULL == fp)
    {
        printf("Save Record Failed.. \n");
		return false;
    }   

	fprintf(fp, "%d", nRange);

	fclose(fp);

	return true;
}