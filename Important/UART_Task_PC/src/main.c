#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../inc/rs232.h"


//#define DEBUG
#define RECEIVE_BUFF_SIZE 4096


int cport_nr = 16;    // /dev/ttyUSB0


int init_serial_com(void)
{
  int bdrate = 115200;

  char mode[] =
  {'8',   // 8 Databits
   'N',   // No parity
   '1',   // 1 stopbit
   0};

   if(RS232_OpenComport(cport_nr, bdrate, mode))
   {
     printf("Can not open comport\n");

     return 0;
   }
   return 1;
}

int check_printable(char *str)
{
  for (int char_counter = 0; char_counter < (strlen(str) - 1); char_counter++)
  {
    if(!isprint(str[char_counter]))
    {
      if(str[char_counter] != '\n')
      {
        return 0;
      }
    }
  }
  return 1;
}




int main (int argc, char **argv)
{

  char *transmit = NULL;
  size_t length = 0;
  int received_bytes = 0;
  char receive_buff[RECEIVE_BUFF_SIZE];

  if(!init_serial_com())
  {
    return 0;
  }
  while (1)
  {
    printf("Send: ");
    if(getline(&transmit, &length, stdin) == -1)
    {
      printf ("Could not read input\n");
      continue;
    }
    #ifdef DEBUG
    printf("DEBUG-Information:\n");
    printf("transmit: %s", transmit);
    printf("if in next line, a newline is present in read\n");
    #endif

    RS232_cputs(cport_nr, transmit);
    #ifdef DEBUG
    printf("Transmit passed\n");
    #endif
    do
    {
      received_bytes =
        RS232_PollComport(cport_nr, receive_buff, (RECEIVE_BUFF_SIZE - 1));
        #ifdef DEBUG
          printf("receive_buff: %s\n"
            "n: %d\n", receive_buff, received_bytes);
        #endif
        usleep(500000);
    } while (received_bytes == 0);
    receive_buff[received_bytes] = 0;   // Setting NULL at the end of the String
    received_bytes = 0;
    #ifdef DEBUG
    printf("Receive passed\n");
    #endif
    if (!check_printable(receive_buff))
    {
      printf("NACK\n");
      printf("Unprintable characters\n");
      memset (&receive_buff, 0, sizeof(receive_buff));
      continue;
    }
    RS232_cputs(cport_nr, "ACK\n");
    printf("Received: %s", receive_buff);
  }

  return 0;

}
