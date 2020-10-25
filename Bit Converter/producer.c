/* Assignment 2 
 * Title: producer.c
 * Aim: Read in from producerTest.txt file, convert
 *      to binary then write out to test.out.txt
 *
 * version 1.1, child of tester.c
 * author: Devin O'Brien
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int ASCII_to_binary(int input);
int char_to_vc(char c);
int convert(char symbol);
void jump();

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(int argc, char * argv[])
{
	//OPEN FILE
	int fd;
	char fileBuff[700];
	if((fd = open("input.txt",O_RDONLY)) == -1)
	{
		write(STDOUT,"Error accessing file.",22);
	}
	else
	{
		//DERIVE FILE SIZE
		struct stat status;
		int fileInfo = stat("input.txt", &status);
  		if((fileInfo) != 0)
  		{
  			printf("Error in deriving file size.");
  		}
  		else
  		{
  			//READ THEN CLOSE FILE
  			read(fd,fileBuff,status.st_size);
  			close(fd);

  			int fdo; //FILE DES OUT
  			if((fdo = open("binary.txt",O_CREAT|O_WRONLY)) == -1)
			{
				write(STDOUT,"Error accessing file.",22);
			}
			else
			{
				int length;
				for(int i = 0; i < strlen(fileBuff); i++)
				{
					char str[8],nwStr[8];
					sprintf(str,"%d",convert(fileBuff[i]));
				
  					length = strlen(str);
  					if(length == 7)
  					{
  					 	write(fdo,str,sizeof(str));
  					}
  					else if(length == 6)
	  				{
	  					sprintf(nwStr,"0%s",str);
	  					write(fdo,nwStr,sizeof(nwStr));
	  				}
				}
				close(fdo);
			}
  		}
	}
}

int ASCII_to_binary(int input)
{
	 int result = 0, i = 1, remainder;

        while (input > 0) 
        {
                remainder = input % 2;
                result = result + (i * remainder);
                input = input / 2;
                i = i * 10;
        }
        return(result);
}

int char_to_ASCII(char c)
{
	int a = c;
	return a;
}

int convert(char symbol)
{
	return ASCII_to_binary(char_to_ASCII(symbol));
}

