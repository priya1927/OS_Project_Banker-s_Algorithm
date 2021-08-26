#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
void sig_handler(int signo);
void display_file(char filenm[]);

void main()
{
  	FILE *f1;
	int fd,create;
	char filename[20],ch[2];
	printf("\t\t PREDICTING SAFE SEQUENCE USING BANKER'S ALGORITHM\t\t\n");
        printf("\nEnter the File name \n");
	scanf("%s",filename);
	f1=fopen(filename,"r");
	if(f1==NULL)
	{
		printf("Cannot open file...check filename spelling or if the file exist...\nThank You!!!\n");	
		printf("Do you want to create a new file \nPress 1  to create\nPress 0 to exit\n");
		scanf("%d",&create);
		if(create==1)
		{
			fd=open(filename,O_RDWR|O_CREAT,S_IRWXU);
			if(signal(SIGINT,sig_handler) == SIG_ERR)
			{
				printf("\n cant catch the signal");	
			}
			if(signal(SIGTSTP,sig_handler) == SIG_ERR)
			{
				printf("\n cant catch the signal");	
			}

			printf("\n Please enter the content in the file as shown on the screen\n");
			display_file("reference.txt");
			printf("\nAfter adding the data please press $ to stop adding to file");
			printf("\nPLease press enter and ctrl+c if you make any mistakes while adding data\n");
			printf("\nSTART TYPING BELOW\n");
			fflush(stdout);
			read(1,ch,1);
			ch[1]='\0';
			while(ch[0]!='$')
			 {
				write(fd,ch,1);
				read(1,ch,1);
				ch[1]='\0';
				
			 }
			close(fd);
			printf("\nFile content added successfully");
			
			char *args[]={"./new_file",filename,NULL};
			execvp(args[0],args);
			printf("//ERROR1");
		}
		else
		{
			exit(0);
		}
	}
	else
	{

		
		fclose(f1);
		char *args[]={"./new_file",filename,NULL};
		execvp(args[0],args);
		printf("//ERROR2");
	}

}

void sig_handler(int signo)
{	
	if(signo == SIGINT)
	{
		printf("\nError while editing data...Restarting program\n\n");
		sleep(2);
		main();
	}
	if(signo == SIGTSTP)
	{
		printf("Exiting Program");
		fflush(stdout);	
		exit(0);
		
	}
	
}

void display_file(char filenm[])
{
	char ch;
        FILE *fp;
	fp=fopen(filenm,"r");
	if(fp==NULL)
	{
		printf("can't open file for reading");
		exit(0);
        }
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		printf("%c", ch);
		ch=fgetc(fp);
	}
	fclose(fp);
	
}

