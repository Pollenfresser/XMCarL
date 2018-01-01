/**
 * Project: XMCarL
 *
 *  Description:
 *    - XMC as Remote Control:
 *      The first XMC is connected to an accelerometer sensor via I2C, reads the data
 *      from it and forwards it to our GUI on a PC via UART.
 *
 *    - PC - GUI:
 *      The PC is used to graphically display the current position of the sensor
 *      and display a video feed of the GoPro Hero5 mounted on a RC car.
 *      Furthermore it is connected to both XMC's to act as a
 *      transmission pipeline.
 *
 *    - XMC on Car:
 *      The XMC is directly connected directly to the controls of the RC car and via
 *      bluetooth to the PC. The forwarded data from the PC is used to control
 *      the car.
 *
 * Author: Christina Bornberg, Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: This is the main function of the XMC as Remote Control.
 * We use a mems sensor which is connected by I2C to the XMC.
 *
 * Status: Doing I2C (Chrisy)
 *
 */


/**
 * Included Files
 */
#include <main.h>


/**
 * Defines
 */

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define RX_BUFFER_SIZE 64 // UART

/**
 * Global variables
 */
/*!< UART lib */
_Bool str_available = false;
char rx_buffer[RX_BUFFER_SIZE] = {0};
XMC_GPIO_CONFIG_t uart_tx = {
	.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
	.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

XMC_GPIO_CONFIG_t uart_rx = {
	.mode = XMC_GPIO_MODE_INPUT_TRISTATE
};

XMC_UART_CH_CONFIG_t uart_config = {
	.data_bits = 8U,
	.stop_bits = 1U,
	.baudrate = 115200U
};


/*!< I2C lib */
XMC_GPIO_CONFIG_t i2c_sda = {
		.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
		.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

XMC_GPIO_CONFIG_t i2c_scl = {
		.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
		.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

XMC_I2C_CH_CONFIG_t i2c_cfg = {
		.baudrate = 100000U
};

/******************************************************************************
 * Start of user functions
 *****************************************************************************/


void SysTick_Handler (void)
{
	static uint32_t ticks = 0;

	ticks++;
	if (ticks >= TICKS_WAIT) {
		XMC_GPIO_ToggleOutput(LED1);
		XMC_GPIO_ToggleOutput(LED2);

		ticks = 0;
	}
}


int main (void)
{

	uint8_t data[4];
	uint8_t mems_status;

	initRetargetSwo();

	XMC_GPIO_CONFIG_t led_config;
	led_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
	led_config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
	led_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
	XMC_GPIO_Init(LED1, &led_config);

	led_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
	XMC_GPIO_Init(LED2, &led_config);

	XMC_GPIO_CONFIG_t interrupt_config;
	interrupt_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
	XMC_GPIO_Init(DATAREADY, &interrupt_config);

#if DEBUG
	printf("Pin Init finished\n");
#endif

	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

#if I2C
	remote_i2c_to_mems_init();
	#if DEBUG
		printf("I2C Init finished\n");
	#endif
	remote_mems_init();
	#if DEBUG
		printf("Mems Init finished\n");
	#endif
	__NOP();
#endif // I2C

#if UART
	remote_uart_to_pc_init();
#endif // UART

	while (1) {
		__NOP();
		#if DEBUG
			printf("while loop started\n");
		#endif
		if(XMC_GPIO_GetInput(DATAREADY))
		{
			__NOP();
			mems_status = remote_i2c_write_read(MEMS_ADDRESS, MEMS_STATUS_REG2, 0, 1);
			#if DEBUG
				printf("mems_status: %x", mems_status);
			#endif
			if(mems_status & (1 << 3))
			{
				__NOP();
				#if I2C
				remote_i2c_read_xy(MEMS_ADDRESS, MEMS_OUT_X_L, data);
				#endif // I2C

				#if UART
				remote_transmit_data(data);
				#endif	// UART
			}
		}
		#if DEBUG
			printf("data: %s", data);
		#endif

	}
}

/* EOF */
