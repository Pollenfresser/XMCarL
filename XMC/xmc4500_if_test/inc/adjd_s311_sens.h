/*
 * adjd_s311_sens.h
 *
 *  Created on: 25 Jul 2017
 *      Author: rbeneder
 */

#ifndef INC_ADJD_S311_SENS_H_
#define INC_ADJD_S311_SENS_H_

#include <stdio.h>
#include <stdlib.h>
#include <xmc_gpio.h>
#include <GPIO.h>

uint8_t _adjd_s311_init(void);
uint8_t _adjd_s311_xfer(uint16_t dev_addr, uint8_t reg_addr, uint8_t i2c_data, _Bool rd_wr);
void _adjd_s311_toggle_led(void);

#define USE_ADJD_S311				0

#define TCS3471_LED 				P0_2
#define ADJD_S311_SDA_PIN 			P0_5
#define ADJD_S311_SCL_PIN 			P0_11
#define ADJD_S311_RD 				1
#define ADJD_S311_WR 				0

#define ADJD_S311_ADR 				0x74
#define ADJD_S311_RD_ADR			(ADJD_S311_ADR<<1)
#define ADJD_S311_REG_CTRL 			0x00
#define ADJD_S311_REG_CONFIG 		0x01
#define ADJD_S311_REG_CAP_RED		0x06
#define ADJD_S311_REG_CAP_GREEN		0x07
#define ADJD_S311_REG_CAP_BLUE		0x08
#define ADJD_S311_REG_CAP_CLEAR		0x09
#define ADJD_S311_REG_INT_RED_LO	0x0A
#define ADJD_S311_REG_INT_RED_HI	0x0B
#define ADJD_S311_REG_INT_GREEN_LO	0x0C
#define ADJD_S311_REG_INT_GREEN_HI	0x0D
#define ADJD_S311_REG_INT_BLUE_LO	0x0E
#define ADJD_S311_REG_INT_BLUE_HI	0x0F
#define ADJD_S311_REG_INT_CLEAR_LO	0x10
#define ADJD_S311_REG_INT_CLEAR_HI	0x11
#define ADJD_S311_REG_DATA_RED_LO	0x40
#define ADJD_S311_REG_DATA_RED_HI	0x41
#define ADJD_S311_REG_DATA_GREEN_LO	0x42
#define ADJD_S311_REG_DATA_GREEN_HI	0x43
#define ADJD_S311_REG_DATA_BLUE_LO	0x44
#define ADJD_S311_REG_DATA_BLUE_HI	0x45
#define ADJD_S311_REG_DATA_CLEAR_LO	0x46
#define ADJD_S311_REG_DATA_CLEAR_HI	0x47
#define ADJD_S311_REG_OFFSET_RED	0x48
#define ADJD_S311_REG_OFFSET_GREEN	0x49
#define ADJD_S311_REG_OFFSET_BLUE	0x4A
#define ADJD_S311_REG_OFFSET_CLEAR	0x4B

#endif /* INC_ADJD_S311_SENS_H_ */
