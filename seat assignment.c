//seat assignment
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{	
	int a,b,c;
	int TnoStu = 173; //The number of student
	int groupseat[] = {16,10,10,9,9,9,12,12,12,12,9,9,9,8,10,12}; //hold group of seats number
	int missednum[] = {30,59,98,130,160}; //hold missing number
	int stunum[TnoStu]; //array of the number of student
	int seat = 0; //all seats in the class
	char day[10]; //input date
	int TnoGS = sizeof groupseat / sizeof groupseat[0]; //count array(groupseat)
	int Tnomissednum = sizeof missednum / sizeof missednum[0]; //count array(missednum)
	printf("Input the date when you will do the test.\nEx:10/15→1015,5/7→0507\n");
	scanf("%s",&day);
	srand(atoi(day));
	int *SN;
	SN = (int *)calloc(TnoStu, sizeof(int));

	for (a = 0; a < TnoGS; a++)
		{
			seat = seat + groupseat[a]; //calculate all seats in the class
		}
	if (( TnoStu - Tnomissednum) != seat)
		{
			//if error happened, this code will work
			printf("Something going wrong.Please check it again."); 
        		return 0;
		}

	for (a = 0; a < TnoStu; a++)
		{
			for (b = 0; b < Tnomissednum; b++)
				{
					if (a + 1 == missednum[b] )
						{
							goto out; //break;&continue; become infinite loop
						}
				}
	
	do
		{
			c = rand() % 16; //output random number	
		}while(groupseat[c] == 0);
	
	groupseat[c] = groupseat[c] - 1; 
	SN[a] = c + 1; 	
	out:;
}

FILE *fp;

char name[] = "seat";

strcat(name,day);
strcat(name,".csv"); //make a file name

fp = fopen(name,"w"); //open the file

for (a = 0; a < TnoStu; a++)
	{
		if(SN[a] != 0)
			{
				fprintf(fp,"1832%03d,mv%d\n" ,a + 1 ,SN[a]);
			}
	}
	fclose(fp);
	
	return 0;
}
