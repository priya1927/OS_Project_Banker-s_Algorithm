#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void need_matrix(int alloc[][10],int max[][10],int need[][10],int resources,int processes)
{
	int i=0,j=0;
	for(i=0;i<processes;i++)
		for(j=0;j<resources;j++)
			need[i][j]=max[i][j]-alloc[i][j];
	printf("The need matrix is:\n");
	for(i=0;i<processes;i++)
	{	
		for(j=0;j<resources;j++)
			printf("%d ",need[i][j]);
		printf("\n");
	}
}
void main(int argc,char **argv)
{
	FILE *fp=fopen(argv[1],"r");//the filename taken from user is passed as an argument to this file 
	printf("\nContent in %s file is:",argv[1]);
	int processes,resources,line_no=1,i=0,j=0,k=0,max_instances[10],alloc[10][10],max[10][10],need[10][10],available[10],cnt=0;
	char ch;
	if(fp!=NULL)
	{
		
		while((ch=fgetc(fp))!=EOF)
		{
			if(ch=='\n')
				line_no++;
			if(line_no==1 && ch>=48 && ch<=57)//if the line no is 1 and if the character read is a number then it is stored in variable 'resource'
				resources=ch-48;
			else if(line_no==2 && ch>=48 && ch<=57)//if the line no is 2 and if the character read is a number then it is stored in the array of max instances
			{
				max_instances[k++]=ch-48;
				ch=fgetc(fp);
				if(ch=='\n')
					line_no++;
				if(ch >= 48 && ch <= 57)//reads the next character and if it is a number then value of max instance would be two digit number 
				{
					k--;
					max_instances[k]=(10*max_instances[k])+ch-48;
					k++;
				}
				
						
			}
			else if(line_no==3 && ch>=48 && ch<=57)//if the line no is 3 and if the character read is a number then it is the number of processes
			{
				processes=ch-48;
				i=0;
			}
			else if(line_no<=(processes+4))
			{
				if(ch>=48 && ch<=57)
					alloc[i][j++]=ch-48;
				if(j>=resources)//when reading the next row of the alloc matrix
				{
					i++;
					j=0;
				}	
			}
			else 
			{
				if(i>=processes)
				{
					i=0;
					j=0;
				}		
				if(ch>=48 && ch<=57)
					max[i][j++]=ch-48;
				if(j>=resources)//reading the next row
				{
					i++;
					j=0;
				}
			}
				
		}
	}
	else
		printf("\nError!! The file does not exist.");
	if(k != resources)
	{	
		printf("Error... MAX INSTANCE and RESOURCES are not equal... input error");
		exit(0);
				
	}
	fclose(fp);
	printf("\nThe resources are:%d and processes are:%d",resources,processes);
	printf("\nThe max_instances of each resource type are:");
	for(i=0;i<resources;i++)
		printf(" %d",max_instances[i]);
	int sum,P[10],seq[10],safe,exec;
	for(i=0;i<resources;i++)//to compute the number of available resources of each resource type
	{
		sum=0;
		for(j=0;j<processes;j++)//to compute the sum of each column of the alloc matrix
			sum+=alloc[j][i];
		available[cnt]=max_instances[cnt]-sum;//subtracting the sum from total number of instances of that resource type,we get the number of available resources of that resource type  
		cnt++;
	}
	printf("\nThe available resources are:\n");
	for(i=0;i<resources;i++)
		printf("%d ",available[i]);
	printf("\nThe allocated resources are:\n");
	for(i=0;i<processes;i++)
	{
		for(j=0;j<resources;j++)
			printf("%d ",alloc[i][j]);
		printf("\n");
	}
	printf("\nThe max resources are:\n");
	for(i=0;i<processes;i++)
	{
		P[i]=1;//initialising the P[] with all 1's to indicate that no processes have executed,when a process executes its corresponding value in P[] array is set to 0
		for(j=0;j<resources;j++)
			printf("%d ",max[i][j]);
		printf("\n");
	}
	need_matrix(alloc,max,need,resources,processes);
	cnt=0;
	while(cnt<processes)
	{
		safe=0;
		for(i=0;i<processes;i++)
		{
			if(P[i])
			{
				exec=1;
				for(j=0;j<resources;j++)//checks if the resources needed by a process are greater than resources available
				{
					if(need[i][j]>available[j])
					{
						exec=0;
						break;
					}
				}
				if(exec)//if resources needed are less than or equal to available resources
				{
					seq[cnt++]=i+1;
					safe=1;
					P[i]=0;
					printf("\nProcess%d is executing\n", i + 1);
					for(j=0;j<resources;j++)//updating the values of available resources
						available[j]+=alloc[i][j];
					break;
				}
			}
		}
		if (!safe) 
		{
            		printf("\nThe processes are in unsafe state.\n");
            		break;
        	} 
		else 
		{
            		printf("\nThe process is in safe state");
            		printf("\nAvailable vector:");
 
            		for (i = 0; i < resources; i++) 
			{
                		printf("\t%d", available[i]);
            		}
 
		        printf("\n");
        	}
    	}
    	
    	printf("\nThe safe sequence is:");
    	
    	for(i=0;i<cnt;i++)
    	{
    		printf("P[%d]",seq[i]);
    		if(i!=cnt-1)
    			printf(" -> ");
    	}
 
	printf("\n\t\tThank You!!\n");
}



