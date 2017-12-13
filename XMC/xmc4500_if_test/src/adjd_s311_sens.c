/*
 * adjd_s311_sens.c
 *
 *  Created on: 25 Jul 2017
 *      Author: rbeneder
 */

#include <adjd_s311_sens.h>
#include <xmc4500_i2c_lib.h>

XMC_GPIO_CONFIG_t adjd_s311_gpio_config;

/*!
 *  @brief This function toggles the LED on the ADJD-S311 Breakout-Board
 *  @param none
 *  @return none
 */
void _adjd_s311_toggle_led (void)
{
	XMC_GPIO_ToggleOutput (TCS3471_LED);
}

/*!
 *  @brief This function configures the calibration LED on the ADJD-S311
 *  breakout-board to output and P0_2. Additionally the I2C Module 1 channel 0
 *  of the XMC4500 is configured to communicate with the CMOS color sensor.
 *  @param none
 *  @return on success this function returns 0
 */
uint8_t _adjd_s311_init (void)
{
	adjd_s311_gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
	adjd_s311_gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
	adjd_s311_gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;

	XMC_GPIO_Init (TCS3471_LED, &adjd_s311_gpio_config);

	_init_i2c1_ch0();

	return 0;
}

/*!
 *  @brief This function identifies the I2C device and forwards the given
 *  parameters to the I2C library layer.
 *  @param dev_addr ... ADJD S311 I2C device address (0x74)
 *         reg_addr ... ADJD S311 I2C register address
 *         i2c_data ... ADJD S311 I2C register value (only relevant if a write
 *                                  request is triggered)
 *         rd_wr    ... ADJD S311 I2C read or write request
 *  @return on success this function returns 0
 */
uint8_t _adjd_s311_xfer (uint16_t dev_addr, uint8_t reg_addr, uint8_t i2c_data,
			 _Bool rd_wr)
{
	if (dev_addr == ADJD_S311_ADR)
		return _i2c_xfer (ADJD_S311_ADR, reg_addr, i2c_data, rd_wr);
	else
		return 1;
}
