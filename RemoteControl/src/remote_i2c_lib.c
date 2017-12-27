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

/*!
 *  @brief This function configures the I2C interface to communicate via pins
 *         P0_5 & P0_11
 *  @param none
 *  @return on success this function returns 0
 */
/**
 * [remote_i2c_to_mems_init description]
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
 * [remote_i2c_write description]
 * @param  channel [description]
 * @param  data [description]
 * @return [description]
 */
uint8_t remote_i2c_write(XMC_USIC_CH_t * const channel, uint8_t data) {

	XMC_I2C_CH_MasterTransmit(channel, data);
	remote_i2c_wait_for_ack(channel);

	return data;

}

/**
 * [remote_i2c_read description]
 * @param  channel [description]
 * @param  id [description]
 * @return [description]
 */
uint8_t remote_i2c_read(XMC_USIC_CH_t * const channel, uint8_t id) {



/*
	uint8_t recv = 0; // TODO was char before

	XMC_I2C_CH_MasterRepeatedStart(channel, id, XMC_I2C_CH_CMD_READ);
	remote_i2c_wait_for_ack(channel);

	XMC_I2C_CH_MasterReceiveNack(channel);

	while ((XMC_USIC_CH_GetReceiveBufferStatus(channel)
			!= (uint32_t) XMC_USIC_CH_RBUF_STATUS_DATA_VALID1)
			&& ((uint32_t) XMC_USIC_CH_GetReceiveBufferStatus(channel)
					!= (uint32_t) XMC_USIC_CH_RBUF_STATUS_DATA_VALID0))
		;

	recv = XMC_I2C_CH_GetReceivedData(channel);

	return recv;
*/
}

/**
 * [remote_i2c_wait_for_ack description]
 * @param  channel [description]
 * @return [description]
 */
uint8_t remote_i2c_wait_for_ack(XMC_USIC_CH_t * const channel) {

	while ((XMC_I2C_CH_GetStatusFlag(channel)
			& XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U) {
		/* wait for ACK */
	}
	XMC_I2C_CH_ClearStatusFlag(channel, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);
	return 0;
}

/**
 * [remote_i2c_write_read description]
 * @param  id [description]
 * @param  reg_addr [description]
 * @param  i2c_data [description]
 * @param  write_read [description]
 * @return [description]
 */
uint8_t remote_i2c_write_read(uint8_t id, uint8_t reg_addr, uint8_t i2c_data,
		_Bool write_read) {
	XMC_ASSERT("XMC_USIC_CH_Enable: channel not valid",
			XMC_USIC_IsChannelValid (channel));
	XMC_USIC_CH_t *channel;

	uint8_t id_tmp = 0;
	uint8_t ret = 0;

	if (id == ADJD_S311_ADR || id == TCS3471_ADR) {
		channel = XMC_I2C1_CH0;
	}

	if (id == ADJD_S311_ADR)
		id_tmp = ADJD_S311_RD_ADR;
	if (id == TCS3471_ADR)
		id_tmp = TCS3471_RD_ADR;

	/**
	 * Involes the start condition on the I2C interface and sends the address of
	 * 	the desired slave
	 * @param channel I2C Channel on which the data should be sent
	 * @param id_tmp Address of the desired slave
	 * @param XMC_I2C_CH_CMD_WRITE distinction between read and write
	 */
	XMC_I2C_CH_MasterStart(channel, id_tmp, XMC_I2C_CH_CMD_WRITE);
	remote_i2c_wait_for_ack(channel);

	XMC_I2C_CH_MasterTransmit(channel, reg_addr);
	remote_i2c_wait_for_ack(channel);

	if (write_read) { // read = 1
		ret = remote_i2c_read(channel, id_tmp);
	} else { // write = 0
		ret = remote_i2c_write(channel, i2c_data);
	}

	XMC_I2C_CH_MasterStop(channel);
	return ret;
}
