/**
 * Project: XMCarL
 *
 * Author:
 * Modified: Christina Bornberg
 *
 * Date of creation: 25.12.2017
 *
 * File description: I2C Library
 * Using: XMC_I2C1_CH0 (USIC1)
 *
 * Status: Done I2C (Chrisy)
 * Lucas Review
 *
 */

#include <remote_i2c_lib.h>


/******************************************************************************
 * Start of user functions
 *****************************************************************************/

/**
 * This function configures the I2C interface to communicate via pins P0_5 (SDA)
 * 	& P0_11 (SCL)
 * @return [description]
 */
uint8_t remote_i2c_to_mems_init(void) {
	XMC_I2C_CH_Init(XMC_I2C1_CH0, &i2c_cfg);
	XMC_I2C_CH_SetInputSource(XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SDA,
	USIC1_C0_DX0_P0_5);
	XMC_I2C_CH_SetInputSource(XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SCL,
	USIC1_C0_DX1_SCLKOUT);
	XMC_I2C_CH_Start(XMC_I2C1_CH0);
	XMC_GPIO_Init (P0_11, &i2c_scl);
	XMC_GPIO_Init (P0_5, &i2c_sda);

	return 0;
}

/**
 * This function sends a byte via the I2C interface and waits for the ack
 * @param  channel [description]
 * @param  data [description]
 * @return either the sent data or 0xFFFF on error
 */
uint16_t remote_i2c_write(XMC_USIC_CH_t * const channel, uint8_t data) {

	XMC_I2C_CH_MasterTransmit(channel, data);
	if(remote_i2c_wait_for_ack(channel)) {
		return 0xFFFF;
	}

	return data;

}

/**
 * A restart with a read access is sent to the slave, afterwards the data is
 * 	read and a NACK of the master is sent
 * @param  channel I2C channel to be read of
 * @param  id address of the slave
 * @return either the received value or 0xFFFF on error
 */
uint16_t remote_i2c_read(XMC_USIC_CH_t * const channel, uint8_t id) {

	uint8_t recv = 0;

	XMC_I2C_CH_MasterRepeatedStart(channel, id, XMC_I2C_CH_CMD_READ);
	if(remote_i2c_wait_for_ack(channel)) {
		return 0xFFFF;
	}



	XMC_I2C_CH_MasterReceiveNack(channel);

	while ((XMC_USIC_CH_GetReceiveBufferStatus(channel)
			!= (uint32_t) XMC_USIC_CH_RBUF_STATUS_DATA_VALID1)
			&& ((uint32_t) XMC_USIC_CH_GetReceiveBufferStatus(channel)
					!= (uint32_t) XMC_USIC_CH_RBUF_STATUS_DATA_VALID0))
		;

	XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                           XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);

	recv = XMC_I2C_CH_GetReceivedData(channel);

	return recv;

}

/**
 * Waits for a ack of the slave, if no ack is received after 5000 cycles an
 * 	error is returned
 * @param  channel the channel on which the ack shall be received
 * @return 0 on success, 1 on failure
 */
uint8_t remote_i2c_wait_for_ack(XMC_USIC_CH_t * const channel) {

	uint8_t ret = 0;
	uint16_t timeout_counter = 0;

	while ((XMC_I2C_CH_GetStatusFlag(channel)
			& XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U) {
		/* wait for ACK */
		timeout_counter++;
		if(timeout_counter > 10000) {
			ret = 1;
			break;
		}
	}
	XMC_I2C_CH_ClearStatusFlag(channel, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);
	return ret;
}

/**
 * The function writes a desired register address to a specifyed target, if
 * 	if read mode is selected the mandatory restart ist performed and the
 * 	connection opened in read mode
 * @param  id address of the slave
 * @param  reg_addr register address to be read of or written to
 * @param  i2c_data data to be sent in a write access
 * @param  write_read distinction between write or read access 0 = write / 1 = read
 * @return sent or received data or 0xFFFF in case of an error
 */
uint16_t remote_i2c_write_read(uint8_t id, uint8_t reg_addr, uint8_t i2c_data,
		_Bool write_read) {

	XMC_USIC_CH_t *channel;
	channel = XMC_I2C1_CH0;

	uint16_t ret = 0;

	/**
	 * Invokes the start condition on the I2C interface and sends the address of
	 * 	the desired slave
	 * @param channel I2C Channel on which the data should be sent
	 * @param id Address of the desired slave
	 * @param XMC_I2C_CH_CMD_WRITE distinction between read and write
	 */
	XMC_I2C_CH_MasterStart(channel, id, XMC_I2C_CH_CMD_WRITE);
	#if DEBUG_ALL
		printf("\t-I2C started\n");
	#endif
	if(remote_i2c_wait_for_ack(channel)) {
		return 0xFFFF;
	}
	#if DEBUG_ALL
		printf("\t-ACK received\n");
	#endif

	XMC_I2C_CH_MasterTransmit(channel, reg_addr);
	#if DEBUG_ALL
		printf("\t-reg_addr transmitted\n");
	#endif
	if(remote_i2c_wait_for_ack(channel)) {
		return 0xFFFF;
	}
	#if DEBUG_ALL
		printf("\t-ACK received\n");
	#endif

	if (write_read) { // read = 1
		ret = remote_i2c_read(channel, id);
	} else { // write = 0
		ret = remote_i2c_write(channel, i2c_data);
	}
	#if DEBUG_ALL
		printf("\t-read/write complete\n");
	#endif

	XMC_I2C_CH_MasterStop(channel);
	#if DEBUG_ALL
		printf("\t-I2C finished\n");
	#endif
	return ret;
}


uint8_t remote_i2c_read_xy(uint8_t id, uint8_t reg_addr, uint8_t *received) {
	XMC_USIC_CH_t *channel;
	channel = XMC_I2C1_CH0;

	/**
	 * Invokes the start condition on the I2C interface and sends the address of
	 * 	the desired slave
	 * @param channel I2C Channel on which the data should be sent
	 * @param id Address of the desired slave
	 * @param XMC_I2C_CH_CMD_WRITE distinction between read and write
	 */
	XMC_I2C_CH_MasterStart(channel, id, XMC_I2C_CH_CMD_WRITE);
	if(remote_i2c_wait_for_ack(channel)) {
		return 1;
	}

	XMC_I2C_CH_MasterTransmit(channel, reg_addr);
	if(remote_i2c_wait_for_ack(channel)) {
		return 1;
	}

	XMC_I2C_CH_MasterRepeatedStart(channel, id, XMC_I2C_CH_CMD_READ);
	if(remote_i2c_wait_for_ack(channel)) {
		return 1;
	}


	/*
	 * Waits until valid data is available on reception register
	 */
	for(uint8_t receive_counter = 0; receive_counter < 6; receive_counter++)
	{
		#if DEBUG_ALL
			printf("Retrieving #%d\n", receive_counter);
		#endif
		if(receive_counter < 5) {
			XMC_I2C_CH_MasterReceiveAck(channel);	// is sent as soon as channel is not busy
			#if DEBUG_ALL
				printf("Master ACK is sent\n");
			#endif
		} else {
			XMC_I2C_CH_MasterReceiveNack(channel);
		}
		while ((XMC_USIC_CH_GetReceiveBufferStatus(channel)
				!= (uint32_t) XMC_USIC_CH_RBUF_STATUS_DATA_VALID1) && ( (uint32_t) XMC_USIC_CH_GetReceiveBufferStatus(channel)
					!= (uint32_t) XMC_USIC_CH_RBUF_STATUS_DATA_VALID0));

		XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                             XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);

		#if DEBUG_ALL
			printf("#%d retrieved\n", receive_counter);
		#endif

		received[receive_counter] = XMC_I2C_CH_GetReceivedData(channel);
	}

	XMC_I2C_CH_MasterStop(channel);

	return 0;

}
