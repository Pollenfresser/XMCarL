/*
 * tcs3471_sens.h
 *
 *  Created on: Sep 14, 2017
 *      Author: rbeneder
 */

#ifndef INC_TCS3471_SENS_H_
#define INC_TCS3471_SENS_H_

#include <stdio.h>
#include <stdlib.h>
#include <xmc_gpio.h>
#include <GPIO.h>

uint8_t _tcs3471_init(void);
uint8_t _tcs3471_xfer(uint16_t dev_addr, uint8_t reg_addr, uint8_t i2c_data, _Bool rd_wr);

#define USE_TCS3471					1

#define TCS3471_SDA_PIN 			P0_5
#define TCS3471_SCL_PIN 			P0_11
#define TCS3471_RD 					1
#define TCS3471_WR 					0

#define TCS3471_ADR 				0x29
#define TCS3471_RD_ADR				(TCS3471_ADR<<1)
#define TCS3471_ENABLE_ADR			0x80
#define TCS3471_ATIME_ADR			0x81
#define TCS3471_WTIME_ADR			0x83
#define TCS3471_AILTL_ADR			0x84
#define TCS3471_AILTH_ADR			0x85
#define TCS3471_AIHTL_ADR			0x86
#define TCS3471_AIHTH_ADR			0x87
#define TCS3471_PERS_ADR			0x8C
#define TCS3471_CONFIG_ADR			0x8D
#define TCS3471_CONTROL_ADR			0x8F
#define TCS3471_ID_ADR				0x92
#define TCS3471_STATUS_ADR			0x93
#define TCS3471_CDATA_ADR			0x94
#define TCS3471_CDATAH				0x95
#define TCS3471_RDATA				0x96
#define TCS3471_RDATAH				0x97
#define TCS3471_GDATA				0x98
#define TCS3471_GDATAH				0x99
#define TCS3471_BDATA				0x9A
#define TCS3471_BDATAH				0x9B

#endif /* INC_TCS3471_SENS_H_ */
