
#include "FileView.h"

extern char s_szPath[MAX_PATH];
extern char s_szDirs[MAX_PATH][MAX_COUNT];
extern char s_szFile[MAX_PATH][MAX_COUNT];

extern int s_nDirsCounts;
extern int s_nFileCounts;


int main(int argc, char* argv[])
{
	int nDiryIndex = 0, nControl = 0;
	if(argc > 1 && GetPath(argv[1]))
		strcpy(s_szPath, argv[1]);
	GetPath(s_szPath);
	PrintFileView(s_szPath, s_szDirs, s_szFile, s_nDirsCounts, s_nFileCounts, nDiryIndex);
	while(nControl != KEY_ESC)
	{
		nControl = getch();
		switch(nControl)
		{
		case KEY_ESC:	
			return 0;
		case KEY_UP:	
			{
				if(nDiryIndex > 0 && s_nDirsCounts > 0) 
				{
					nDiryIndex--; 
				}
				else if(s_nDirsCounts > 0) 
				{
					nDiryIndex = s_nDirsCounts - 1; 
				}
				break;
			}
		case KEY_DOWN:
			{
				if(nDiryIndex < s_nDirsCounts - 1 && s_nDirsCounts > 0)
				{
					nDiryIndex++; 
				}
				else
				{
					nDiryIndex = 0;
				}
				break;
			}
		case KEY_BACK:
			{
				MoveParent(s_szPath); 
				nDiryIndex = 0; 
				GetPath(s_szPath); 
				break;
			}
		case KEY_ENTER: 
			{
				if(s_nDirsCounts > 0) 
				{ 
					EnterDirectory(s_szPath, s_szDirs[nDiryIndex]); 
					nDiryIndex = 0; 
					GetPath(s_szPath); 
				} 
				break;
			}
		default: 
			continue;
		}
		PrintFileView(s_szPath, s_szDirs, s_szFile, s_nDirsCounts, s_nFileCounts, nDiryIndex);
	}
	return 0;
}

bool PrintFileView(char* szPath, char szDirs[][MAX_COUNT], char szFile[][MAX_COUNT], int nDirsCounts, int nFileCounts, int nDiryIndex)
{
	system("cls");
	int i = 0;
	if(strcmp(szPath, PATH_ROOT))
		printf("┏ %s\\\n", szPath);
	else
		printf("┏ %s\n", szPath);
	for(i = 0; i < nDirsCounts; i++)
	{
		printf("┣> %c %s\\\n", nDiryIndex == i ? '*' : ' ',szDirs[i]);
	}
	for(i = 0; i < nFileCounts; i++)
	{
		printf("┣┅  %s\n", szFile[i]);
	}
	printf("┗ ^\n");
	return true;
}

char* MoveParent(char* szPath)
{
	if(2 != strlen(szPath) && strcmp(szPath, PATH_ROOT)) 
	{
		char * szTemp = NULL;
		szTemp = strrchr(szPath, '\\');
		int nLoc = (int)strrchr(szPath, '\\') - (int)szPath;
		szPath[nLoc] = '\0';
		if(2 == strlen(szPath)) strcat(szPath, "\\");
	}
	else
	{
		strcpy(szPath, PATH_ROOT);
	}
	return szPath;
}

char* EnterDirectory(char* szPath, char* szDiry)
{
	if(strcmp(szPath, PATH_ROOT)) 
	{
		strcat(szPath, "\\");
		strcat(szPath, szDiry);
	}
	else
	{
		strcpy(szPath, szDiry);
		strcat(szPath, "\\");
	}
	return szPath;
}

bool GetPath(char* szPath)
{
	if(!strcmp(szPath, PATH_ROOT))
		return GetRoot();
	//if('\\' != szPath[strlen(szPath) - 1])
	//	strcat(szPath, "\\");
	char szSysCmd[1024] = "";
	s_nFileCounts = s_nDirsCounts = 0;
	sprintf(szSysCmd, CMD_FILE, szPath);
	system(szSysCmd);
	char szBuffer[BUFF_SIZE];
	FILE *fp;
    if(NULL == (fp = fopen("path.io", "r")))
	{
        printf("\nOpen file failed! Press any key to continue...");
		getch();
		return false;
    }
	while(!feof(fp))
	{
		char* szTemp = NULL;
		int nLen = 0;
		fgets(szBuffer, BUFF_SIZE, fp);
		if(BUFF_SIZE <= strnlen(szBuffer, BUFF_SIZE)) 
		{
			szPath[strlen(szPath) - 1] = '\0';
			return false;
		}
		szBuffer[strlen(szBuffer) - 1] = '\0';
		if(strstr(szBuffer, "\\"))
		{
			trim(szBuffer);
			int nLoc = (int)strrchr(szBuffer, ' ') - (int)szBuffer;
			szBuffer[nLoc] = '\0';
			strcpy(s_szPath, szBuffer);
			if('\\' == s_szPath[strlen(s_szPath) - 1])
				s_szPath[strlen(s_szPath) - 1] = '\0';
		}
		else if(' ' == szBuffer[0])
		{
			continue;
		}
		else if(strstr(szBuffer, "<DIR>"))
		{
			szTemp = strstr(szBuffer, "<DIR>") + 5;
			nLen = strlen(szTemp);
			strncpy(szBuffer, szTemp, nLen);
			szBuffer[nLen] = '\0';
			trim(szBuffer);
			if(!(nLen = strcmp(szBuffer, "..")) || !strcmp(szBuffer, "."))
				continue;
			strcpy(s_szDirs[s_nDirsCounts], szBuffer);
			s_nDirsCounts++;
		}
		else if(strstr(szBuffer, " "))
		{
			szTemp = strstr(szBuffer, " ");
			nLen = strlen(szTemp);
			strncpy(szBuffer, szTemp, nLen);
			szBuffer[nLen] = '\0';
			trim(szBuffer);

			szTemp = strstr(szBuffer, " ");
			nLen = strlen(szTemp);
			strncpy(szBuffer, szTemp, nLen);
			szBuffer[nLen] = '\0';
			trim(szBuffer);

			szTemp = strstr(szBuffer, " ");
			nLen = strlen(szTemp);
			strncpy(szBuffer, szTemp, nLen);
			szBuffer[nLen] = '\0';
			trim(szBuffer);

			strcpy(s_szFile[s_nFileCounts], szBuffer);
			s_nFileCounts++;
		}
	}
	fclose(fp);
	return true;
}

bool GetRoot()
{
	system(CMD_DISK);
	s_nFileCounts = s_nDirsCounts = 0;
	char szBuffer[BUFF_SIZE];
	FILE *fp;
	// 驱动器: C:\ D:\ E:\ F:\ 
    if(NULL == (fp = fopen("path.io", "r")))
	{
        printf("\nOpen file failed! Press any key to continue...");
		getch();
		return false;
    }
	while(!feof(fp))
	{
		char* szTemp = NULL;
		int nLen = 0;
		fgets(szBuffer, BUFF_SIZE, fp);
		szBuffer[strlen(szBuffer) - 1] = '\0';
		if(strstr(szBuffer, "\\"))
		{
			trim(szBuffer);
			szTemp = strstr(szBuffer, " ");
			nLen = strlen(szTemp);
			strncpy(szBuffer, szTemp, nLen);
			szBuffer[nLen] = '\0';
			trim(szBuffer);

			while(NULL != (szTemp = strchr(szBuffer, ' ')))
			{
				int nLen = (int)szTemp - (int)szBuffer;
				strncpy(s_szDirs[s_nDirsCounts], szBuffer, nLen);
				s_szDirs[s_nDirsCounts][nLen - 1] = '\0';
				s_nDirsCounts++;
				nLen = strlen(szTemp);
				strncpy(szBuffer, szTemp, nLen);
				szBuffer[nLen] = '\0';
				trim(szBuffer);
			}
			strcpy(s_szDirs[s_nDirsCounts], szBuffer);
			s_szDirs[s_nDirsCounts][strlen(s_szDirs[s_nDirsCounts]) - 1] = '\0';
			s_nDirsCounts++;
		}
	}
	fclose(fp);
	return true;
}

char* trim(char *str)
{
    char *str_last,*str_cur;
    if(str == NULL)
        return NULL;
    for(str_cur = str;*str_cur == 0x20 || *str_cur == '\t'; ++str_cur);
	strncpy(str, str_cur, strlen(str_cur));
	str[strlen(str_cur)] = '\0';
    for(str_last = str_cur = str; *str_cur != '\0'; ++str_cur)
        if(*str_cur != 0x20 && *str_cur != '\t')
            str_last = str_cur;
    *++str_last = '\0';
    return str;
}
