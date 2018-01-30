

#include <main.h>
#include <remote_mems.h>

/**
 * Initialises the sensor to the necessary specifications
 * @return [description]
 */
/*!
 * \brief Initialises the mems sensor to the necessary specifications
 * \param none
 * \return 0 on success
 */
uint8_t remote_mems_init(void)
{
  /*!< Initialises register 1 of the sensor to select a desired refresh
        rate and enable X & Y Axis */
  while(remote_i2c_write_read(MEMS_ADDRESS, MEMS_CTRL_REG1, TWENTYFIFE_HZ_X_AND_Y, 0) == 0xFFFF)
  {
    XMC_GPIO_ToggleOutput(LED1);
    #if DEBUG
      printf("CTRL_REG1 failed\n");
    #endif
  }
#if DEBUG
  printf("Mems Init MEMS_CTRL_REG1 finished\n");
#endif


  /*!< Initialises register 3 of the sensor to enable data ready interrupt
        forwarding to the INT1 pin */
  while(remote_i2c_write_read(MEMS_ADDRESS, MEMS_CTRL_REG3, 0b00010000, 0) == 0xFFFF)
  {
    XMC_GPIO_ToggleOutput(LED1);
    #if DEBUG
      printf("CTRL_REG1 failed\n");
    #endif
  }
#if DEBUG
  printf("Mems Init MEMS_CTRL_REG3 finished\n");
#endif


  /*!< Initialises register 4 of the sensor to ensure full scale selection of 2G */
  while(remote_i2c_write_read(MEMS_ADDRESS, MEMS_CTRL_REG4, 0, 0) == 0xFFFF)
  {
    XMC_GPIO_ToggleOutput(LED1);
    #if DEBUG
    printf("CTRL_REG4 failed\n");
    #endif
  }
#if DEBUG
  printf("Mems Init MEMS_CTRL_REG4 finished\n");
#endif

  return 0;
}

/*!
   \brief Transmitts the data of the mems sensor to the PC
   \param data  ... string of the data to be transmitted
   \return 0 on success
*/
uint8_t remote_transmit_data(uint8_t *data)
{
  int16_t data_x = data[1];
  data_x <<= 8;
  data_x |= data[0];
  int16_t data_y = data[3];
  data_y <<= 8;
  data_y |= data[2];
  #if DEBUG
    printf("UART_X: %d\n", data_x);
    printf("UART_Y: %d\n\n", data_y);
  #endif
  remote_uart_printf("UART_X: %d\n", data_x);
  remote_uart_printf("UART_Y: %d\n", data_y);
  return 0;
}
