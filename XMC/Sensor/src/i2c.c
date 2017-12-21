XMC_I2C_CONFIG_t i2c_cfg = { .baudrate = 100000U, };

/*
 * @brief I2C on chanel 0; Used pins: P0_5 andP0_11
 * @param none
 * @return on success: 0
 */
uint8_t i2c_to_mems_init(void) {

	XMC_I2C_CH_Init(XMC_I2C1_CH0, &i2c_cfg);
	XMC_I2C_CH_SetInputSource(XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SDA,
			USIC1_C0_DX0_P0_5);
	XMC_I2C_CH_SetInputSource(XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SCL,
			USIC1_C0_DX1_SCLKOUT);
	XMC_I2C_CH_Start(XMC_I2C1_CH0);

	return 0;
}

/*
 *
 */
uint8_t i2c_to_memes_read_write(void) {

	XMC_ASSERT ("XMC_USIC_CH_Enable: channel not valid", XMC_USIC_IsChannelValid (channel));
	XMC_USIC_CH_t *channel;
	char tmp_i2c_recv = 0;
	uint8_t tmp_id = 0;

	XMC_I2C_CH_MasterStart(channel, tmp_id, XMC_I2C_CH_CMD_WRITE);
	while((XMC_I2C_CH_GetStatusFlag (channel) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U){
		// waits for ACK
	}


}

/* EOF */
