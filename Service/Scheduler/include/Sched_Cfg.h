#include "Std_Types.h"

#define TICK_TIME_MS 1

typedef void (*Runnable_Cbf)(void);

typedef struct
{
    char *Name;
    u16 Periodicity;
    u16 StartDelay;
    Runnable_Cbf Cbf;

} Runnable_strCfg_t;

typedef enum
{
    Task1,
    Task2,
    Task3,
    Task_enuCount

} Runnables_enu_t;

extern Runnable_strCfg_t Tasks[Task_enuCount];
