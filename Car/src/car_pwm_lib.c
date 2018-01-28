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
