/*
 * tcs3471_sens.c
 *
 *  Created on: Sep 14, 2017
 *      Author: rbeneder
 */

#include <tcs3471_sens.h>
#include <xmc4500_i2c_lib.h>

/*!
 *  @brief This function configures the I2C Module 1 channel 0 of the XMC4500
 *  to communicate with the CMOS Color Sensor.
 *  @param none
 *  @return on success this function returns 0
 */
uint8_t _tcs3471_init (void)
{
	_init_i2c1_ch0();

	return 0;
}

/*!
 *  @brief This function identifies the I2C device and forwards the given
 *  parameters to the I2C library layer.
 *  @param dev_addr ... TCS3471 I2C device address (0x29)
 *         reg_addr ... TCS3471 I2C register address
 *         i2c_data ... TCS3471 I2C register value (only relevant if a write
 *                      request is triggered)
 *         rd_wr    ... TCS3471 I2C read or write request
 *  @return on success this function returns 0
 */
uint8_t _tcs3471_xfer (uint16_t dev_addr, uint8_t reg_addr, uint8_t i2c_data,
		       _Bool rd_wr)
{
	if (dev_addr == TCS3471_ADR)
		return _i2c_xfer (TCS3471_ADR, reg_addr, i2c_data, rd_wr);
	else
		return 1;
}
