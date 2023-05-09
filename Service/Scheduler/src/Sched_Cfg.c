#include "Sched_Cfg.h"
#include "LED.h"

void led_on_20MS(void)
{
    static u16 ToggleFlag = 0x55;

    if (ToggleFlag == 0x55)
    {
        LED_enuSetLedStatus(Led_enu20ms, LED_STATE_ON);
        ToggleFlag = ~ToggleFlag;
    }
    else
    {
        LED_enuSetLedStatus(Led_enu20ms, LED_STATE_OFF);
        ToggleFlag = ~ToggleFlag;
    }
}

void led_on_100MS(void)
{
    static u16 ToggleFlag = 0x55;

    if (ToggleFlag == 0x55)
    {
        LED_enuSetLedStatus(Led_enu100ms, LED_STATE_ON);
        ToggleFlag = ~ToggleFlag;
    }
    else
    {
        LED_enuSetLedStatus(Led_enu100ms, LED_STATE_OFF);
        ToggleFlag = ~ToggleFlag;
    }
}

void led_on_500MS(void)
{
    static u16 ToggleFlag = 0x55;

    if (ToggleFlag == 0x55)
    {
        LED_enuSetLedStatus(Led_enu500ms, LED_STATE_ON);
        ToggleFlag = ~ToggleFlag;
    }
    else
    {
        LED_enuSetLedStatus(Led_enu500ms, LED_STATE_OFF);
        ToggleFlag = ~ToggleFlag;
    }
}


Runnable_strCfg_t Tasks[Task_enuCount] =
    {
        [Task1] =
            {
                .Name = "App1",
                .Periodicity = 100,
                .StartDelay = 0,
                .Cbf = led_on_20MS
            },
        [Task2] =
            {
                .Name = "App2",
                .Periodicity = 250,
                .StartDelay = 0,
                .Cbf = led_on_100MS
            },
        [Task3] =
            {
                .Name = "App3",
                .Periodicity = 400,
                .StartDelay = 0,
                .Cbf = led_on_500MS
            }
        

};
