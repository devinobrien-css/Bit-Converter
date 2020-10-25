/* Bit converter
 * Title: consumer.c
 * Aim: Read binary file binary.txt, convert
 *      back to char, and produce file 
 *      output.txt
 *
 * version 1.0
 * author: Devin O'Brien
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

char ASCII_to_char(int num);

int main(int argc, char* argv[])
{
    //OPEN FILE
	int fdin;
	if((fdin = open("binary.txt",O_RDONLY)) == -1)
	{
		write(0,"Error accessing file.",22);
	}
	else
	{
		//DERIVE FILE SIZE
		struct stat status;
		int fileInfo = stat("binary.txt", &status);
  		if((fileInfo) != 0)
  		{
  			printf("Error in deriving file info.");
  		}
  		else
  		{
  			//READ THEN CLOSE FILE INTO BUFFER
            char fileBuff[7000];
    	    read(fdin,&fileBuff,status.st_size);
            close(fdin);

            //OPEN FILE OUT
            int fdout;
            if((fdout = open("output.txt",O_WRONLY|O_CREAT)) == -1)
            {
                write(0,"Error accessing file.",22);
            } 
            else
            {
                //bit_value is the value of 2^n where bit_index = n
                int bit_value[] = {64,32,16,8,4,2,1};
                //bit_index is the current bit in a byte
                int bit_index = 0;
                //ASCII_value is a variable to hold the calculated ASCII value of the byte
                int ASCII_value = 0;
                //letter holds the ASCII character of the integer value of the byte
                char letter[2];

                //LOOP THROUGH ALL BITS IN BINARY FILE | bit_index resets after a byte is read and char value is printed
                for(int i = 0; i < status.st_size; i++)
                {
                    if(bit_index == 6)//if the current bit in memory is the eighth bit of a given byte
                    {
                        if(fileBuff[i] == '0')
                        {
                            sprintf(letter,"%c",ASCII_value);
                            write(fdout,letter, sizeof(letter));
                        }
                        else if(fileBuff[i] == '1')
                        {
                            ASCII_value += bit_value[bit_index];
                            sprintf(letter,"%c",ASCII_value);
                            write(fdout,letter, sizeof(letter));
                        }
                        bit_index = 0;
                        ASCII_value = 0;
                    }
                    else if(fileBuff[i] == '0')
                    {
                        bit_index++;
                    }
                    else if(fileBuff[i] == '1')
                    {
                        ASCII_value += bit_value[bit_index];
                        bit_index++;
                    }
                  
                }
            }
        }
	}
}
