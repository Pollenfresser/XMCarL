

#include <main.h>
#include <remote_mems.h>

/**
 * Initialises the sensor to the necessary specifications
 * @return [description]
 */
uint8_t remote_mems_init(void)
{
  /**
   * @param MEMS_ADDRESS addressing acceleration sensor
   * @param MEMS_CTRL_REG1 addressing register for data rate and axis enabling
   * @param b00110011 25 Hz data rate, X & Y axis enabled, normal power mode
   * @param 0 write access
   */
  while(remote_i2c_write_read(MEMS_ADDRESS, MEMS_CTRL_REG1, ONE_HZ_X_AND_Y, 0) == 0xFFFF)
  {
    XMC_GPIO_ToggleOutput(LED1);
    #if DEBUG
      printf("CTRL_REG1 failed\n");
    #endif
  }
#if DEBUG
  printf("Mems Init MEMS_CTRL_REG1 finished\n");
#endif


  /*!
     \brief "Description"
     \param "Param description"
     \pre "Pre-conditions"
     \post "Post-conditions"
     \return "Return of the function"
  */
  while(remote_i2c_write_read(MEMS_ADDRESS, MEMS_CTRL_REG4, 0, 0) == 0xFFFF)
  {
    XMC_GPIO_ToggleOutput(LED1);
    #if DEBUG
      printf("CTRL_REG1 failed\n");
    #endif
  }


  /**
   * @param MEMS_ADDRESS addressing acceleration sensor
   * @param MEMS_CTRL_REG3 addressing register for interrupt on pin INT1
   * @param b00010000 enabling interrupt to indicate a new set of data
   * @param 0 write access
   */
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
  return 0;
}

/*!
   \brief ""
   \param "Param description"
   \pre "Pre-conditions"
   \post "Post-conditions"
   \return "Return of the function"
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
  remote_uart_printf("X: %d\n", data_x);
  remote_uart_printf("Y: %d\n", data_y);
  return 0;
}
