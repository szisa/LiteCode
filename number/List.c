#include "List.h"
#include <malloc.h>
#include <stdio.h>

#define HEAD -1

long long LstAt(struct LIST* pList, long long nIndex)
{
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;
	long long nCurIndex = 0;

	if(NULL == pList) return 0;

	for(pCurr = pHead->pNext; LstisValid(pCurr) && nCurIndex < nIndex; pCurr = pCurr->pNext) nCurIndex++;

	return pCurr->nValue;
}

long long LstFind(struct LIST* pList, long long nValue)
{
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;
	long long nCurIndex = 0;

	if(NULL == pList) return -1;

	for(pCurr = pHead->pNext; LstisValid(pCurr) && pCurr->nValue != nValue; pCurr = pCurr->pNext) nCurIndex++;

	if(pCurr->nValue != nValue) return -1;

	return nCurIndex;
}

long long LstCount(struct LIST* pList)
{
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;
	long long nIndex = 0;

	if(NULL == pList) return 0;

	for(pCurr = pHead->pNext; LstisValid(pCurr); pCurr = pCurr->pNext) nIndex++;

	return nIndex;
}

bool LstisEnd(struct LIST* pList)
{
	return NULL == pList->pNext;
}

bool LstisValid(struct LIST* pList)
{
	return NULL != pList;
}

struct LIST* LstNew()
{
	struct LIST* pList = (struct LIST*)malloc(sizeof(struct LIST));
	pList->nValue = HEAD;
	pList->pNext = NULL;
	return pList;
}

struct LIST* LstPop(struct LIST* pList, long long nIndex)
{
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;
	struct LIST* pTemp = NULL;
	long long nCurIndex = 0;

	if(NULL == pList) return NULL;

	for(pCurr = pHead; LstisValid(pCurr) && nCurIndex < nIndex; pCurr = pCurr->pNext) nCurIndex++;

	if(nCurIndex < nIndex) return pList;
	if(LstisValid(pCurr))
	{
		pTemp = pCurr->pNext;
		pCurr->pNext = pTemp->pNext;
	}

	if(NULL != pTemp)
		free(pTemp);

	return pList;
}

struct LIST* LstPush(struct LIST* pList, long long nValue)
{
	struct LIST* pHead = pList;
	struct LIST* pCurr = NULL;
	struct LIST* pNew = NULL;
	long long nIndex = 0;

	if(NULL == pList) return NULL;

	for(pCurr = pHead; !LstisEnd(pCurr); pCurr = pCurr->pNext) nIndex++;

	pNew = (struct LIST*)malloc(sizeof(struct LIST));

	if(NULL == pNew)
	{ 
		printf("\nOut of Memory..\n");
		return NULL;
	}

	pNew->nValue = nValue;
	pNew->pNext = NULL;

	pCurr->pNext = pNew;

	return pNew;
}
