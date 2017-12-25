/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg, Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: This is the header file of the XMC as Remote Control.
 * We use a mems sensor which is connected by I2C to the XMC.
 *
 * Status: Doing I2C (Chrisy)
 *
 */

#ifndef INC_REMOTE_I2C_LIB_H_
#define INC_REMOTE_I2C_LIB_H_

/**
 * Included Files
 */


#include <stdio.h>
#include <stdlib.h>
#include <xmc_i2c.h>
#include <xmc_gpio.h>
#include <xmc_usic.h>

/**
 * Defines
 */


/**
 * Global variables
 */

/**
 * Prototypes
 */


uint8_t _init_i2c1_ch0(void);
uint8_t _i2c_xfer(uint8_t id, uint8_t reg_addr, uint8_t i2c_data, _Bool rd_wr);

#endif /* INC_REMOTE_I2C_LIB_H_ */

/* EOF */


