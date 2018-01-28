/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg, Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: This is the header file of the XMC as Car Control.
 * We use a mems sensor which is connected by I2C to the XMC.
 *
 * Status:
 *
 */

#ifndef _CAR_PWM_LIB_
#define _CAR_PWM_LIB_

/**
 * Included Files
 */


#include <stdio.h>
#include <stdlib.h>

#include <xmc_ccu4.h>
#include <xmc_gpio.h>


/**
 * Defines
 */
#define THROTTLE  P1_3    // Slice 0
#define STEERING  P1_2    // Slice 1

#define CCU4_SLICE_0    CCU40_CC40
#define CCU4_SLICE_1    CCU40_CC41
#define CCU4_MODULE     CCU40

#define PERIOD_FOR_64_PRESCALING 37500
#define IDLE_FOR_64_PRESCALING 2812

/**
 * Global variables
 */
extern XMC_CCU4_SLICE_COMPARE_CONFIG_t g_timer_object;


/**
 * Prototypes
 */
void car_pwm_init(void);
void car_set_pwm(char *rx_buff);

#endif /* _CAR_PWM_LIB_ */

/* EOF */
