// NumberApp.cpp : Defines the entry point for the console application.
//

#include "Number.h"
#include "KeyDefine.h"

int main(int argc, char* argv[])
{
	struct LIST* pList = LstNew();
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;

	int nControl = 0;
	bool bSuccess = true;

	srand((unsigned)time(NULL));
	PrintMenu();
	while(nControl != KEY_ESC)
	{
		nControl = getch();
		//PrintMenu();
		//system("CLS");
		switch(nControl)
		{
		case '+': bSuccess = Push(pList); break;
		case '-': bSuccess = Pop(pList);  break;

		case '0': bSuccess = View(pList); break;
		case '1': bSuccess = Calc(pList, CALC_MIN);  break;
		case '2': bSuccess = Calc(pList, CALC_MAX);	 break;
		case '3': bSuccess = Calc(pList, CALC_AVG);  break;
		case '4': bSuccess = Calc(pList, CALC_SUM);  break;
		case '5': bSuccess = Calc(pList, CALC_VRC);  break;
		case '6': bSuccess = Calc(pList, CALC_DVA);  break;

		case KEY_CTRL_S: bSuccess = Save(pList);   break;
		case KEY_CTRL_L: bSuccess = Load(pList);   break;
		case KEY_CTRL_R: bSuccess = Rand(pList);   break;
		case KEY_CTRL_C: bSuccess = Clear(pList);  break;

		default : continue;
		}
		if(!bSuccess) printf("\a");
	}
	return 0;
}

bool View(struct LIST* pList)
{
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;
	long long nIndex = 0;

	if(NULL == pList) return false;

	printf("View All Number(%I64d): \n", LstCount(pList));

	for(pCurr = pHead->pNext; LstisValid(pCurr); pCurr = pCurr->pNext) 
	{
		printf("[%I64d] %I64d\t", nIndex ++, pCurr->nValue);
		if(nIndex % 5 == 0) printf("\b\n");
	}
	
	printf("(End)\n", LstCount(pList));
	return true;
}

bool Push(struct LIST* pList)
{
	long long nInput = 0;

	if(NULL == pList) return false;

	printf("Push: ");
	scanf("%I64d", &nInput);
	if(NULL == LstPush(pList, nInput))
		return false;
	printf("Push Success\n");
	return true;
}

bool Pop(struct LIST* pList)
{
	long long nInput = 0;

	if(NULL == pList) return false;

	printf("Pop(index): ");
	scanf("%I64d", &nInput);
	
	if(nInput >= LstCount(pList))
	{
		printf("Out of List Index!\n");
		return false;
	}
	
	if(NULL == LstPop(pList, nInput))
		return false;
	printf("Pop Success\n");
	return true;
}

bool Clear(struct LIST* pList)
{
	struct LIST* pHead = pList;

	if(NULL == pList) return false;

	while(!LstisEnd(pHead)) 
		LstPop(pHead, 0);

	system("CLS");
	PrintMenu();

	return true;
}

bool Rand(struct LIST* pList)
{
	FILE *fp;
	long long i = 0, nCount = 0, nNumber = 0;
	char* szPath[260] = {0};

	if(NULL == pList) return false;

	printf("\rNumber Count: ");
	scanf("%d", &nCount);
	printf("\rFile name: ");
	scanf_s("%s", szPath, 260);

    if(NULL == (fp = fopen(szPath, "wb+")))
	{
        printf("Open file failed!\n");
		getch();
		return 0;
    }

	for(i = 0; i < nCount; i++) 
	{
		nNumber = (long long)rand() % 1000;
		fprintf(fp, "%I64d\n", nNumber);
		LstPush(pList, nNumber);
		printf("\rCreate Number (%.3lf%%) : %I64d", i * 100.0 / nCount, nNumber);
	}

	printf("\rCreate Number (100%%).\t\t\t\n");
	fclose(fp);
	return true;
}

bool Save(struct LIST* pList)
{
	FILE *fp;
	char* szPath[260] = {0};
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;

	if(NULL == pList) return false;

	printf("\rFile name: ");
	scanf_s("%s", szPath, 260);

    if(NULL == (fp = fopen(szPath, "wb+")))
	{
        printf("Open file failed!\n");
		getch();
		return 0;
    }

	for(pCurr = pHead->pNext; LstisValid(pCurr); pCurr = pCurr->pNext) 
		fprintf(fp, "%I64d\n", pCurr->nValue);

	fclose(fp);
	return true;
}

bool Load(struct LIST* pList)
{
	FILE *fp;
	char* szPath[260] = {0};
	char szBuffer[100] = {0};
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;
	long long nIndex = 0;

	if(NULL == pList) return false;

	printf("\rFile name: ");
	scanf_s("%s", szPath, 260);

    if(NULL == (fp = fopen(szPath, "r")))
	{
        printf("Open file failed!\n");
		getch();
		return 0;
    }

	printf("Loading File");
	while(!feof(fp))
	{
		memset(szBuffer, 0, 100);
		fgets(szBuffer, 100, fp);
		if(strlen(szBuffer) <= 0 || szBuffer[0] > '9' || szBuffer[0] < '0')
			continue;
		LstPush(pList, atol(szBuffer));
		nIndex++;
		printf("\rLoading File(%I64d)", nIndex);
		if(0 == nIndex % 4000) printf("");
		else if(0 == nIndex % 3000) printf("...");
		else if(0 == nIndex % 2000) printf("..");
		else if(0 == nIndex % 1000) printf(".");
	}

    printf("\r\t\t\t\rLoad %I64d Number(s)!\n", nIndex);

	fclose(fp);
	return true;
}

bool Calc(struct LIST* pList, int nOperation)
{
	long long nSum = 0, nMin = 0, nMax = 0, nCount = 0;
	double fAvg = 0.0, fVrc = 0.0, fOffset = 0.0;
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;

	if(NULL == pList) return false;

	if(nOperation >= CALC_COUNT)
	{
		printf("Unknowen operations...\n");
		return false;
	}

	printf("Being calculations...");

	if((CALC_MIN == nOperation|| CALC_MAX == nOperation) && LstisValid(pHead->pNext))
		nMin = nMax = pHead->pNext->nValue;

	for(pCurr = pHead->pNext; LstisValid(pCurr); pCurr = pCurr->pNext) 
	{
		if(CALC_MAX == nOperation && pCurr->nValue > nMax)
			nMax = pCurr->nValue;
		if(CALC_MAX == nOperation && pCurr->nValue < nMin)
			nMin = pCurr->nValue;
		if(CALC_SUM <= nOperation)
			nSum += pCurr->nValue;
		nCount ++;
	}

	if(CALC_MAX == nOperation)
	{
		printf("\r\t\t\t\t\t\rNmax = %ld\n", nMax);
		return true;
	}

	if(CALC_MIN == nOperation)
	{
		printf("\r\t\t\t\t\t\rNmin = %ld\n", nMin);
		return true;
	}

	if(CALC_SUM == nOperation)
	{
		printf("\r\t\t\t\t\t\rNsum = %ld\n", nSum);
		return true;
	}

	fAvg = (double)nSum / (double)nCount;

	if(CALC_AVG == nOperation)
	{
		printf("\r\t\t\t\t\t\rNavg = %.5lf\n", fAvg);
		return true;
	}
	
	for(pCurr = pHead->pNext; LstisValid(pCurr); pCurr = pCurr->pNext) 
	{
		fOffset = (double)pCurr->nValue - fAvg;
		fVrc += fOffset * fOffset;
	}

	if(CALC_VRC == nOperation)
	{
		printf("\r\t\t\t\t\t\rNvrc = %.5lf\n", fVrc);
		return true;
	}

	if(CALC_DVA == nOperation)
	{
		printf("\r\t\t\t\t\t\rNdva = %.5lf\n", sqrt(fVrc));
		return true;
	}

	return true;
}

void PrintMenu()
{
	printf("/***********************************************************\\\n");
	printf("|                 按下按鍵去選擇不同的功能                  |\n");
	printf("\\***********************************************************/\n\n");
	printf("\t\t+ : 添加一個新的數字到列表\n");
	printf("\t\t- : 移除列表指定索引的數字\n");
	printf("\n");
	printf("\t\t0 : 輸出列表中所有的數字\n");
	printf("\t\t1 : 輸出列表中最大的數字\n");
	printf("\t\t2 : 輸出列表中最小的數字\n");
	printf("\t\t3 : 輸出列表中的數字的和\n");
	printf("\t\t4 : 輸出列表中的數字的平均數\n");
	printf("\t\t5 : 輸出列表中的數字的方差\n");
	printf("\t\t6 : 輸出列表中的數字的標準差\n");
	printf("\n");
	printf("\t\tCtrl + S : 保存數字\n");
	printf("\t\tCtrl + L : 加載數字\n");
	printf("\t\tCtrl + R : 產生隨機數字\n");
	printf("\t\tCtrl + C : 清空數字並重載畫面\n");
}