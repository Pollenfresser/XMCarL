/**
 * Project: XMCarL
 *
 * Author: Chrisy
 * Modified:
 *
 * Date of creation: 27.12.2017
 *
 * File description: UART communication on the pc side
 * Data is send by the xmc to the pc - will be forwarded
 * via bluetooth to the car and visualised in gui_data_visualisation.c
 *
 * Status: at the beginning
 *
 */

#include <gui_main.h>
//#define DEBUG

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

int pc_uart_init(void) {

	int bdrate = 115200;

	char mode[] = {
      '8',   // 8 Databits
			'N',   // No parity
			'1',   // 1 stopbit
			0 };

	if (RS232_OpenComport(cport_nr, bdrate, mode)) {
		printf("Cannot open com port\n");

		return 1;
	}
	return 0;

}

// if something has to be: close, free, unref, ...
void pc_uart_clean() {

}


// ergebnis -> durch 2000 wird an gui
// durch 2*9.81 an car - ich schicke nur mehr pulsdauer in millisec
// es sind immer 2 verschiedene werte - eines für throttle, eines für steering
// pulsdauer zw 1 & 2 ms
// ich bekomme wahrscheinlich eine 16bit zahl
void pc_uart_result_manipulation(){


}


// whatever i get here should be forwarded to the bluetooth
// file and to the gui-visualisation file

/*!
 * \brief Reads the whole serial register and returns the last 2 values for x
 *        and y to the rcv struct
 * \param none
 * \return none
 */
gboolean pc_uart_receive(gpointer data) {

#if DEBUG
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
