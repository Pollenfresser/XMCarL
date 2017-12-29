/**
 * Project: XMCarL
 *
 * Author:
 * Modified: Christina Bornberg, Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: This is the I2C header file of the XMC as Remote Control.
 * We use a mems sensor which is connected by I2C to the XMC.
 *
 * Status: Done I2C (Chrisy)
 * Lucas Review
 */

#ifndef REMOTE_I2C_H_
#define REMOTE_I2C_H_

/**
 * Included Files
 */
#include <main.h>
#include <xmc_i2c.h>
#include <xmc_usic.h>


/**
 * Defines
 */


/**
 * Global variables
 */

extern XMC_GPIO_CONFIG_t i2c_sda;
extern XMC_GPIO_CONFIG_t i2c_scl;
extern XMC_I2C_CH_CONFIG_t i2c_cfg;


/**
 * Prototypes
 */

uint8_t remote_i2c_to_mems_init(void);

uint16_t remote_i2c_write_read(uint8_t id, uint8_t reg_addr, uint8_t i2c_data, _Bool write_read);
uint8_t	 remote_i2c_read_xy(uint8_t id, uint8_t reg_addr, uint8_t *received);
uint16_t remote_i2c_write(XMC_USIC_CH_t * const channel, uint8_t data);
uint16_t remote_i2c_read(XMC_USIC_CH_t * const channel, uint8_t id);

uint8_t remote_i2c_wait_for_ack(XMC_USIC_CH_t *const channel);

#endif /* REMOTE_I2C_H_ */

/* EOF */
