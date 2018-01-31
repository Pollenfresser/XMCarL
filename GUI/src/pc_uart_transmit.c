/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg
 * Modified: Lucas Ullrich
 *
 * Date of creation: 27.12.2017
 *
 * File description: UART communication on the pc side
 * Data is send by the xmc to the pc - will be forwarded
 * via bluetooth to the car and visualised in gui_data_visualisation.c
 *
 * Status: is working
 *
 */

#include <gui_main.h>
//#define DEBUG

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

int pc_uart_init(gpointer data) {

	widgets *a = (widgets *) data;
	int bdrate = 115200;

	char mode[] = {
      '8',   // 8 Databits
			'N',   // No parity
			'1',   // 1 stopbit
			0 };

	if (RS232_OpenComport(cport_nr, bdrate, mode)) {
		a->status.remote = ERROR;
		strcpy(a->status.remote_info, "Cannot open com port");
		return 1;
	}

	a->status.remote = CONNECTED;
	sprintf(a->status.remote_info, "COM Port is connected to: %d", cport_nr);
	return 0;

}

// if something has to be: close, unable to open comport : No such file or directory
// free, unref, ...
void pc_uart_clean() {

}

/*!
 * \brief Reads the whole serial register and returns the last 2 values for x
 *        and y to the rcv struct
 * \param none
 * \return none
 */
gboolean pc_uart_receive(gpointer data) {

#if DEBUG_DATA
  printf("Receive started\n");
#endif

	int received_bytes = 0;
	char receive_buff[RECEIVE_BUFF_SIZE];
  char *token;
  char *prev_token;

  received_bytes = RS232_PollComport(cport_nr, receive_buff, RECEIVE_BUFF_SIZE - 1);

  if(received_bytes > 0)
  {
    prev_token  = calloc(strlen(receive_buff), sizeof(receive_buff));
    token = calloc(strlen(receive_buff), sizeof(receive_buff));

    token = strtok(receive_buff, " \n");
    while(token != NULL)
    {

      #if DEBUG_DATA
      printf("prev: %s\n", prev_token);
      printf("toke: %s\n", token);
      #endif

      if(strncmp(prev_token, "UART_X", strlen("UART_X")) == 0)
      {
        #if DEBUG_DATA
        printf("~writing steering\n");
        #endif
        received.steering = strtol(token, NULL, 10);
        #if DEBUG_DATA
        printf("token: '%s'\t\t%ld\n", token, received.steering);
        #endif
      }
      else if(strncmp(prev_token, "UART_Y", strlen("UART_Y")) == 0)
      {
        #if DEBUG_DATA
        printf("~writing throttle\n");
        #endif
        received.throttle = strtol(token, NULL, 10);
        #if DEBUG_DATA
        printf("token: '%s',\t\t%ld\n", token, received.throttle);
        #endif
      }

      memset(prev_token, '\0', strlen(prev_token));
      strncpy(prev_token, token, strlen(token));
      token = strtok(NULL, " \n");
    }

    free(prev_token);
    free(token);

    #if DEBUG_DATA
    printf("steering: %ld\n", received.steering);
    printf("throttle: %ld\n", received.throttle);
    #endif
  }

  return TRUE;
}
