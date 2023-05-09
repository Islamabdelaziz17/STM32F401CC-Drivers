#include "include/Sched.h"

u32 Global_Timercounter;

static u8 Global_Sched_flag = 0;

Sched_enuErrorStatus Sched_enuInit(void)
{
    Sched_enuErrorStatus Local_enuerrorstatus = Sched_enuOK;
    Local_enuerrorstatus = Set_NotificationFunc(Sched_Tickcbf);
    Set_Systick_Interrupt();
    Local_enuerrorstatus = Set_CLK_Source(SYSTICK_CLK_SRC_AHB);
    Systick_Stop();
    Set_Period_MS(1, &Global_Timercounter);
    return Local_enuerrorstatus;
}
void Sched_vidStart(void)
{
    Systick_Start();
    while (1)
    {
        if (Global_Sched_flag)
        {
            Sched_vidTask();
            Global_Sched_flag = 0;
        }
    };
}
static void Sched_vidTask(void)
{
    u8 Local_idx = 0;
    for (Local_idx = 0; Local_idx < Task_enuCount; Local_idx++)
    {
        if (Tasks[Local_idx].Cbf)
        {
            if (Tasks[Local_idx].StartDelay == 0)
            {
                Tasks[Local_idx].Cbf();
                Tasks[Local_idx].StartDelay = Tasks[Local_idx].Periodicity;
            }
        }
        else
        {
            /*NULL POINTER*/
            /*Do Nothing*/
        }
        Tasks[Local_idx].StartDelay -= TICK_TIME_MS;
    }
}
static void Sched_Tickcbf(void)
{
    Global_Sched_flag = 1;
}
