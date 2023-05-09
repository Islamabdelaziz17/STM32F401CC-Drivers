#include "Std_Types.h"
#include "Systick.h"
#include "Sched_Cfg.h"

typedef enum
{
    Sched_enuOK,
    Sched_enuNOK
} Sched_enuErrorStatus;


Sched_enuErrorStatus Sched_enuInit(void);

extern void Sched_vidStart(void);

static void Sched_vidTask(void);

static void Sched_Tickcbf(void);