/**
 * Project: XMCarL
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
#include <car_pwm_lib.h>


/******************************************************************************
 * Start of user functions
 *****************************************************************************/
void car_pwm_init(void)
{
  XMC_CCU4_SetModuleClock(CCU4_MODULE, XMC_CCU4_CLOCK_SCU);
  XMC_CCU4_Init(CCU4_MODULE, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
  XMC_CCU4_EnableClock(CCU4_MODULE, 0);
  XMC_CCU4_EnableClock(CCU4_MODULE, 1);   // Might be an error source for wrong period time

  XMC_CCU4_StartPrescaler(CCU4_MODULE);
  XMC_CCU4_SLICE_CompareInit(CCU4_SLICE_0, &g_timer_object);
  XMC_CCU4_SLICE_CompareInit(CCU4_SLICE_1, &g_timer_object);

  XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU4_SLICE_0, PERIOD_FOR_64_PRESCALING);
  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU4_SLICE_0, IDLE_FOR_64_PRESCALING);

  XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU4_SLICE_1, PERIOD_FOR_64_PRESCALING);
  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU4_SLICE_1, IDLE_FOR_64_PRESCALING);

  XMC_CCU4_EnableShadowTransfer(CCU4_MODULE, XMC_CCU4_SHADOW_TRANSFER_SLICE_0);
  XMC_CCU4_EnableShadowTransfer(CCU4_MODULE, XMC_CCU4_SHADOW_TRANSFER_SLICE_1);

  XMC_CCU4_SLICE_StartTimer(CCU4_SLICE_0);
  XMC_CCU4_SLICE_StartTimer(CCU4_SLICE_1);
}


void car_set_pwm(char *rx_buff)
{

  long steering;
  long throttle;
  char *end;
  int16_t steering_offset;
  int16_t throttle_offset;

  steering = strtol(rx_buff, &end, 10);
  // Needs to be changed
  if(rx_buff == end) {
    return;
  }
  rx_buff = end;
  throttle = strtol(rx_buff, &end, 10);

  #if DEBUG
  printf("steering: %ld\nthrottle: %ld\n", steering, throttle);
  #endif

  if (steering > MAX_RECEIVE)
  {
    steering = MAX_RECEIVE;
  }
  if (throttle > MAX_RECEIVE)
  {
    throttle = MAX_RECEIVE;
  }

  steering_offset = (steering / 17);
  throttle_offset = (throttle / 17);

  #if DEBUG
  printf("st_offset: %d\nth_offset: %d\n", steering_offset, throttle_offset);
  #endif

  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU4_SLICE_0, (IDLE_FOR_64_PRESCALING + throttle_offset));
  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU4_SLICE_1, (IDLE_FOR_64_PRESCALING + steering_offset));

  XMC_CCU4_EnableShadowTransfer(CCU4_MODULE, XMC_CCU4_SHADOW_TRANSFER_SLICE_0);
  XMC_CCU4_EnableShadowTransfer(CCU4_MODULE, XMC_CCU4_SHADOW_TRANSFER_SLICE_1);

}
