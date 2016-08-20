#pragma once

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

struct LIST
{
	long long nValue;
	struct LIST* pNext;

};

struct LIST* LstNew();
struct LIST* LstPop(struct LIST* pList, long long nIndex);
struct LIST* LstPush(struct LIST* pList, long long nValue);

long long LstCount(struct LIST* pList);
long long LstAt(struct LIST* pList, long long nIndex);
long long LstFind(struct LIST* pList, long long nValue);

bool LstisEnd(struct LIST* pList);
bool LstisValid(struct LIST* pList);
