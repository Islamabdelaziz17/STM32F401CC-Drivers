#include "LCD.h"

static u8 LCD_State = LCD_enuNotInit;
static u8 Current_Req_Id = 0;
static u8 LCD_Buffer_Id = 0;
Lcd_Task_Req Tasks_Req[NUMBER_OF_USER_REQS];

void LCD_vidInit()
{

    /* INDEXING PINS TO CONFIGURE */
    u8 Loc_u8PinIndex = 0;
    /* STRUCTURE OF GPIO CONFIGURATION */
    GPIO_Cfg_t cfg;

    /* ITERATE THROUGH ALL THE PINS */
    for (Loc_u8PinIndex = 0; Loc_u8PinIndex < LCD_NUMBER_OF_PINS; Loc_u8PinIndex++)
    {

        cfg.Pin_Num = LCD_strCfg[0].Lcd_pu8Pins[Loc_u8PinIndex];
        cfg.Port_Num = LCD_strCfg[0].Port;
        cfg.Mode = GPIO_MODE_OUTPUT_PP;
        cfg.Speed = GPIO_SPEED_VHIGH;

        /* INITIALIZE GPIO PORTS */
        Gpio_enuInit(&cfg);
    }
}

static void LCD_Task(void)
{
    if (LCD_State != LCD_enuNotInit)
    {
        LCD_vidInitSeq();
    }
    else if (LCD_State == LCD_enuBusyWrite)
    {
        LCD_vidWriteSeq();
    }
}

LCD_enustate_t LCD_enuWriteStringAsync(const u8 *CpyStr, u8 CpyStrLen, u8 Cpy_u8Xpos, u8 Cpy_u8Ypos)
{
    LCD_enustate_t Local_Lcd_State = LCD_enuBusyWrite;
    u8 Local_Idx = 0;

    for (Local_Idx = 0; Local_Idx < NUMBER_OF_USER_REQS; Local_Idx++)
    {
        if (Tasks_Req[Local_Idx].BufferState == Lcd_enuNotBuffered)
        {
            Tasks_Req[Local_Idx].Str = CpyStr;
            Tasks_Req[Local_Idx].Length = CpyStrLen;
            Tasks_Req[Local_Idx].Posx = Cpy_u8Xpos;
            Tasks_Req[Local_Idx].Posy = Cpy_u8Ypos;
            Tasks_Req[Local_Idx].CharIdx = 0;
            Tasks_Req[Local_Idx].BufferState = Lcd_enuBuffered;
        }
    }
    if (LCD_State == LCD_enuIdle)
    {
        LCD_State = LCD_enuBusyWrite;
        Local_Lcd_State = LCD_enuOK;
    }
    else if (LCD_State == LCD_enuNotInit)
    {
        Local_Lcd_State = LCD_enuNotInit;
    }
    return Local_Lcd_State;
}

static void LCD_vidInitSeq(void)
{
    static u8 State;

    switch (State)
    {
    case LCD_Function_Set:
        LCD_enuSend(SEND_COMMAND, FUNCTION_SET_CMD);
        State = LCD_Display;
        break;
    case LCD_Display:
        LCD_enuSend(SEND_COMMAND, DISPLAY_ON_CMD);
        State = LCD_Clear;
        break;
    case LCD_Clear:
        LCD_enuSend(SEND_COMMAND, CLEAR_DISPLAY_CMD);
        break;
    case LCD_InitDone:
        LCD_State = LCD_enuIdle;
        break;
    default:
        /*Do Nothing*/
        break;
    }
}

static void LCD_vidWriteSeq(void)
{
    static u8 State;

    switch (State)
    {
    case LCD_enuWriteStart:

        State = LCD_enuWriteSetPosition;

        break;
    case LCD_enuWriteSetPosition:

        LCD_enuGotoXY(Tasks_Req[Current_Req_Id].Posx, Tasks_Req[Current_Req_Id].Posy);
        State = LCD_enuWriteCharacter;

        break;
    case LCD_enuWriteCharacter:

        LCD_enuSend(SEND_DATA, Tasks_Req[Current_Req_Id].Str[Tasks_Req[Current_Req_Id].CharIdx]);
        Tasks_Req[Current_Req_Id].CharIdx++;
        if (Tasks_Req[Current_Req_Id].CharIdx == Tasks_Req[Current_Req_Id].Length)
        {
            State = LCD_enuWriteDone;
        }

        break;
    case LCD_enuWriteDone:
        Tasks_Req[Current_Req_Id].BufferState = Lcd_enuNotBuffered;
        for (LCD_Buffer_Id = 0; LCD_Buffer_Id < NUMBER_OF_USER_REQS; LCD_Buffer_Id++)
        {
            if (Tasks_Req[Current_Req_Id].BufferState == Lcd_enuBuffered)
            {
                break;
            }
        }
        if (LCD_Buffer_Id == NUMBER_OF_USER_REQS)
        {
            LCD_State = LCD_enuIdle;
            Current_Req_Id = 0;
        }
        else
        {
            State = LCD_enuWriteStart;
            Current_Req_Id = LCD_Buffer_Id;
            // if(Current_Req_Id == NUMBER_OF_USER_REQS)
            // {
            //      Current_Req_Id = 0;
            // }
        }
        break;
    default:
        /*Do Nothing*/
        break;
    }
}
LCD_enuErrorStat_t LCD_enuSend(u8 Data, u8 Cpy_u8Data)
{
    LCD_enuErrorStat_t Local_enuLCDErrorstat = LCD_enuOK;
    u8 SetResetval = 0;

    Local_enuLCDErrorstat = GPIO_enuWritePin(LCD_strCfg[0].Port, LCD_enuEnable, GPIO_BIT_SET);

    if (Data == SEND_COMMAND)
    {
        SetResetval = GPIO_BIT_RESET;
    }
    else
    {
        SetResetval = GPIO_BIT_SET;
    }

    Local_enuLCDErrorstat = GPIO_enuWritePin(LCD_strCfg[0].Port, LCD_enuRS, SetResetval);

    Local_enuLCDErrorstat = GPIO_enuWritePin(LCD_strCfg[0].Port, LCD_enuRW, GPIO_BIT_RESET);

    Local_enuLCDErrorstat = GPIO_enuSetPort(LCD_strCfg[0].Port, Cpy_u8Data);

    Local_enuLCDErrorstat = GPIO_enuWritePin(LCD_strCfg[0].Port, LCD_enuEnable, GPIO_BIT_SET);

    return Local_enuLCDErrorstat;
}

LCD_enuErrorStat_t LCD_enuGotoXY(u8 Cpy_u8Xpos, u8 Cpy_u8Ypos)
{
    u8 Local_u8Location = 0;
    LCD_enuErrorStat_t Local_enuLCDErrorstat = LCD_enuOK;

    if (Cpy_u8Xpos >= LCD_XPOS_FIRST_LINE && Cpy_u8Xpos <= LCD_XPOS_SECOND_LINE)
    {
        if (Cpy_u8Xpos == LCD_XPOS_FIRST_LINE)
        {
            if ((Cpy_u8Ypos) <= LCD_DDRAM_LINE_1_END)
            {
                Local_u8Location = Cpy_u8Ypos;
            }
            else
            {
                Local_enuLCDErrorstat = LCD_enu_Out_OF_DDRAM_Boundary;
            }
        }
        else if (Cpy_u8Xpos == LCD_XPOS_SECOND_LINE)
        {
            if ((LCD_DDRAM_LINE_2_START + Cpy_u8Ypos) <= LCD_DDRAM_LINE_2_END)
            {
                Local_u8Location = LCD_DDRAM_LINE_2_START + Cpy_u8Ypos;
            }
            else
            {
                Local_enuLCDErrorstat = LCD_enu_Out_OF_DDRAM_Boundary;
            }
        }
    }
    else
    {
        Local_enuLCDErrorstat = LCD_enu_Out_OF_DDRAM_Boundary;
    }

    if (Local_enuLCDErrorstat == LCD_enuOK)
    {
        LCD_enuSend(SEND_COMMAND, Local_u8Location + LCD_DDRAM_ADDRESS_CFG);
    }

    return Local_enuLCDErrorstat;
}

LCD_enuErrorStat_t LCD_enuWriteString(u8 *Add_pu8String)
{
    u8 Local_u8Counter = 0;
    LCD_enuErrorStat_t Local_enuLCDErrorstat = LCD_enuOK;
    if (Add_pu8String != Null)
    {

        for (Local_u8Counter = 0; Add_pu8String[Local_u8Counter] != 0; Local_u8Counter++)
        {
            LCD_enuSend(SEND_DATA, Add_pu8String[Local_u8Counter]);
        }
    }
    else
    {
        Local_enuLCDErrorstat = LCD_enu_Null_Pointer;
    }

    return Local_enuLCDErrorstat;
}