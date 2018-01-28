/**
 * Project: XMCarL
 *
 *  Description: // just in main files
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
 * File description:
 *
 * Status:
 */


// hier ist platz für die .h datei, globals, defines, ... in header
/******************************************************************************
 *  Included files
 * ****************************************************************************/
#include <main.h>

/******************************************************************************
 *  Defines
 * ****************************************************************************/
#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500


/******************************************************************************
 *  Global variables
 * ****************************************************************************/
 /****** UART *******/
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
 	.baudrate = 9600U
 };

 /****** CCU4 *******/
XMC_CCU4_SLICE_COMPARE_CONFIG_t g_timer_object =
{
  .timer_mode           = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,   // Alignment
  .monoshot             = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,   // mode (one shot or continuous)
  .shadow_xfer_clear    = 0,   // shadow not cleared after transfer
  .dither_timer_period  = 0,   // can the period dither
  .dither_duty_cycle    = 0,   // can the compare match dither
  .prescaler_mode       = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,   // fixed or floating division
  .mcm_enable           = 0,   // multi channel mode
  .prescaler_initval    = XMC_CCU4_SLICE_PRESCALER_64,   // value of prescaler
  .float_limit          = 0,   // float prescaler, not used
  .dither_limit         = 0,   // max dither deviation, not used
  .passive_level        = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,   // output level configuration for active and non active cycle
  .timer_concatenation  = 0,   // concatenation for pointed slice
};

/******************************************************************************
 * Start of user functions
 *****************************************************************************/
void SysTick_Handler (void)
{
  static uint32_t ticks = 0;

  ticks ++;
  if(ticks >= TICKS_WAIT)
  {
    XMC_GPIO_ToggleOutput(LED1);
    ticks = 0;
  }
}



int main (void)
{

  char rx_buff[RX_BUFFER_SIZE] = {0};

  initRetargetSwo();
  XMC_GPIO_CONFIG_t led_config;
  led_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  led_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  led_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
  XMC_GPIO_Init(LED1, &led_config);


  XMC_GPIO_CONFIG_t throttle_config;
  throttle_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3;
  throttle_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  throttle_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
  XMC_GPIO_Init(THROTTLE, &throttle_config);

  XMC_GPIO_CONFIG_t steering_config;
  steering_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3;
  steering_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  steering_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
  XMC_GPIO_Init(STEERING, &steering_config);

  #if UART_EN
  car_uart_to_pc_init();
  #endif

  #if PWM_EN
  car_pwm_init();
  #endif

  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
    car_uart_get_string(rx_buff);
  }
  return 0;

}
