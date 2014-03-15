#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"

typedef enum
{
	FIND_NULL,
	FIND_THE_FIRST_WORD,
	FIND_THE_SECOND_WORD,
	FIND_THE_THREAD_WORD,
	FIND_OK,
}CURRENT_FIND_STATUS_ENUM;

static int getResult = 0;

static CURRENT_FIND_STATUS_ENUM currentStatus = FIND_NULL;

int main(void)
{
	FILE *fp = NULL;
	bool findOver = false;
	char needString[50] = {'0'};
	char tempString[30] = {'0'};
	char tempChar;
	int i = 0, counter = 0;
	fp = fopen("Log.txt", "r");
	if(fp == NULL)
	{
		printf("Error! No that file");
		return 0;
	}

	while((tempChar = fgetc(fp)) != EOF && !findOver)
	{	
		tempString[i] = tempChar;

		switch(currentStatus)
		{
		case FIND_NULL:
			{
				if(tempString[i] == 32)   //Meet space
				{
					tempString[i] = '\0';
					if(!strcmp(tempString, "counter")) //Compare ok
					{
						counter = i;
						strncpy(needString, tempString, i);
						currentStatus = FIND_THE_FIRST_WORD;
					}
					
					memset(tempString, 0, sizeof(tempString));
					i = 0;
				}
				else
				{
					i++;
				}
			}
			break;
		case FIND_THE_FIRST_WORD:
			{
				if(tempString[i] == 32)
				{
					tempString[i] = '\0';
                    if(!strcmp(tempString, "-")) //Compare ok
					{
						counter += i;
						strncat(needString, tempString, i);
						currentStatus = FIND_THE_SECOND_WORD;
					}
					memset(tempString, 0, sizeof(tempString));
					i = 0;
				}
				else
				{
					i++;
				}
			}
			break;
		case FIND_THE_SECOND_WORD:
			{
                if(tempString[i] == 32)
				{
					tempString[i] = '\0';
					if(!strcmp(tempString, "counter1")) //Compare ok
					{
						int j = 0;
						strncat(needString, tempString, i);
						for(i = 0; i < 6; i++)
						{
                            tempChar = fgetc(fp);
							if(isdigit(tempChar))
							{
								tempString[j++] = tempChar;
							}
						}
						tempString[j] = '\0';
						if(atoi(tempString) > 1500)
						{
							getResult++;
							printf("Get one!\ncounter - counter1 = %d", atoi(tempString));
						}
						memset(needString, 0, sizeof(needString));
						currentStatus = FIND_NULL;
						//findOver = true;
					}
					memset(tempString, 0, sizeof(tempString));
					i = 0;	
					
				}
				else
				{
					i++;
				}
		    }
		    break;
		}
	}
	fclose(fp);
	//printf("The need string is %s\n", needString);
}