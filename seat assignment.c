//seat assignment
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{	
	int a,b,c;
	//The number of student
	int NumOfStu = 173;
	//hold group of seats number
	int groupseat[] = {16,10,10,9,9,9,12,12,12,12,9,9,9,8,10,12};
	//hold missing number
	int missednum[] = {30,59,98,130,160};
	//array of the number of student
	int stunum[TnoStu];
	//all seats in the class
	int seat = 0;
	//input date
	char day[10];
	//count array(groupseat)
	int NumOfGS = sizeof groupseat / sizeof groupseat[0];
	//count array(missednum)
	int NumOfmissednum = sizeof missednum / sizeof missednum[0];
	
	printf("Input the date when you will do the test.\nEx:10/15→1015,5/7→0507\n→");
	scanf("%s",&day);
	srand(atoi(day));
	
	int *SN;
	SN = (int *)calloc(NumOfStu, sizeof(int));

	for (a = 0; a < NumOfGS; a++)
		{
			//calculate all seats in the class
			seat = seat + groupseat[a];
		}
	
	if (( NumOfStu - NumOfmissednum) != seat)
		{
			//if error happened, this code will work
			printf("Something going wrong.Please check it again."); 
        		return 0;
		}

	for (a = 0; a < NumOfStu; a++)
	{
		for (b = 0; b < NumOfmissednum; b++)
		{
			if (a + 1 == missednum[b] )
			{
				//break;&continue; become infinite loop
				goto out;
			}
		}
	
	do
	{
		//output random number	
		c = rand() % 16;
	} while(groupseat[c] == 0);
	
	groupseat[c] = groupseat[c] - 1;
	SN[a] = c + 1; 	
	out:;
	
	}

	FILE *fp;

	char name[] = "seat";
	
	//make a file name
	strcat(name,day);
	strcat(name,".csv");

	//open the file
	fp = fopen(name,"w");

	for (a = 0; a < NumOfStu; a++)
	{
		if(SN[a] != 0)
		{
			fprintf(fp,"1832%03d,mv%d\n" ,a + 1 ,SN[a]);
		}
	}
	
	fclose(fp);
	return 0;
	
}
