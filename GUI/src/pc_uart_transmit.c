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

	int received_bytes = 0;
	char receive_buff[RECEIVE_BUFF_SIZE];
  char *dummy_buff;
  char *x_buff;
  char *y_buff;

  x_buff = NULL;
  y_buff = NULL;

  received_bytes = RS232_PollComport(cport_nr, receive_buff, RECEIVE_BUFF_SIZE-1);

  if(received_bytes)
  {
    dummy_buff = strtok(receive_buff, " ");
    while(dummy_buff != NULL)
    {
      if(strncmp(dummy_buff, "UART_X", strlen("UART_X")) == 0)
      {
        dummy_buff = strtok(NULL, "\n");
        x_buff = calloc(strlen(dummy_buff), sizeof(char));
        strncpy(x_buff, dummy_buff, strlen(dummy_buff));
        #if DEBUG
          printf("-UART_X: %s\n", x_buff);
        #endif
        received.x = strtol(x_buff, NULL, 10);
      } else if(strncmp(dummy_buff, "UART_Y", strlen("UART_Y")) == 0)
      {
        dummy_buff = strtok(NULL, "\n");
        y_buff = calloc(strlen(dummy_buff), sizeof(char));
        strncpy(y_buff, dummy_buff, strlen(dummy_buff));
        #if DEBUG
          printf("-UART_Y: %s\n", y_buff);
        #endif
        received.y = strtol(y_buff, NULL, 10);
      } else
      {
        dummy_buff = strtok(NULL, " \n");
        #if DEBUG
          printf("~~dummy: %s\n", dummy_buff);
        #endif
      }

      if(x_buff != NULL) {
        free(x_buff);
        x_buff = NULL;
      }
      if(y_buff != NULL) {
        free(y_buff);
        y_buff = NULL;
      }
    }
  }
  return TRUE;
}
