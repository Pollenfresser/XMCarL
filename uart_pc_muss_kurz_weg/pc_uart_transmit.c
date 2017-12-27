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

#include <pc_uart.h>
//#define DEBUG

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

/*int pc_uart_init() {

	int bdrate = 115200;

	char mode[] = { '8',   // 8 Databits
			'N',   // No parity
			'1',   // 1 stopbit
			0 };

	if (RS232_OpenComport(cport_nr, bdrate, mode)) {
		printf("Cannot open com port\n");

		return 0;
	}
	return 1;

}

// if something has to be: close, free, unref, ...
void pc_uart_clean() {

}


// ergebnis -> durch 9.81 wird an an gui
// durch 2*9.81 an car - ich schicke nur mehr pulsdauer in millisec
// es sind immer 2 verschiedene werte - eines für throttle, eines für steering
// pulsdauer zw 1 & 2 ms
// ich bekomme wahrscheinlich eine 16bit zahl
void pc_uart_result_manipulation(){


}


// whatever i get here should be forwarded to the bluetooth
// file and to the gui-visualisation file

/*
 * timer, wenn der abgelaufen ist
 * interrupt
 * uart from remote abfragen
 * manipulieren
 * bluetooth 2 car senden
 */
/*
void pc_uart_receive() {

	int received_bytes = 0;
	char receive_buff[RECEIVE_BUFF_SIZE];


	do {
				received_bytes = RS232_PollComport(cport_nr, receive_buff,
						(RECEIVE_BUFF_SIZE - 1));
	#ifdef DEBUG
				printf("receive_buff: %s\n"
						"n: %d\n", receive_buff, received_bytes);
	#endif
				usleep(500000);
			} while (received_bytes == 0);
			receive_buff[received_bytes] = 0; // Setting NULL at the end of the String
			received_bytes = 0;
	#ifdef DEBUG
			printf("Receive passed\n");
	#endif

			printf("Received: %s", receive_buff);
}

int pc_uart_routine() {

	if (!pc_uart_init()) {
		return 0;
	}

	while (1) {

		pc_uart_receive();
		RS232_cputs(cport_nr, "ACK\n");

	}

	return 0;
}*/
