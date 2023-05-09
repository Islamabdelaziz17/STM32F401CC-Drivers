#include "Std_Types.h"
#include "GPIO.h"
#include "LCD_Cfg.h"

#ifndef LCD_H
#define LCD_H

#define SEND_COMMAND 0
#define SEND_DATA 1

#define LCD_DDRAM_LINE_1_START 0x00
#define LCD_DDRAM_LINE_2_START 0x40
#define LCD_DDRAM_LINE_1_END 0x0F
#define LCD_DDRAM_LINE_2_END 0x4F
#define LCD_DDRAM_ADDRESS_CFG 128

#define FUNCTION_SET_CMD 0b00111010
#define DISPLAY_ON_CMD 0b00001100
#define DISPLAY_ON_CURSOR_ON_CMD 0b00001110
#define DISPLAY_ON_CURSOR_ON_BLINK_ON_CMD 0b00001111
#define CLEAR_DISPLAY_CMD 0b00000001

#define LCD_XPOS_FIRST_LINE 0
#define LCD_XPOS_SECOND_LINE 1

#define LCD_YPOS0 0
#define LCD_YPOS1 1
#define LCD_YPOS2 2
#define LCD_YPOS3 3
#define LCD_YPOS4 4
#define LCD_YPOS5 5
#define LCD_YPOS6 6
#define LCD_YPOS7 7
#define LCD_YPOS8 8
#define LCD_YPOS9 9
#define LCD_YPOS10 10
#define LCD_YPOS11 11
#define LCD_YPOS12 12
#define LCD_YPOS13 13
#define LCD_YPOS14 14
#define LCD_YPOS15 15

#define LCD_BLOCK0 0
#define LCD_BLOCK1 1
#define LCD_BLOCK2 2
#define LCD_BLOCK3 3
#define LCD_BLOCK4 4
#define LCD_BLOCK5 5
#define LCD_BLOCK6 6
#define LCD_BLOCK7 7

typedef enum
{

    //LCD_enuOK,
    LCD_enu_NotOk,
    LCD_enu_Out_OF_DDRAM_Boundary,
    LCD_enu_Out_OF_CGRAM_Boundary,
    LCD_enu_Null_Pointer

} LCD_enuErrorStat_t;

typedef enum
{
    LCD_enuNotInit,
    LCD_enuIdle,
    LCD_enuOK,
    LCD_enuBusyWrite,
    LCD_enuBusyClear

} LCD_enustate_t;

typedef enum
{
    LCD_Function_Set,
    LCD_Display,
    LCD_Clear,
    LCD_InitDone

} LCD_enuInitSeq_t;

typedef enum
{
    LCD_enuWriteStart,
    LCD_enuWriteSetPosition,
    LCD_enuWriteCharacter,
    LCD_enuWriteDone
} LCD_enuWriteSeq_t;

typedef enum
{
    Lcd_enuNotBuffered,
    Lcd_enuBuffered

} Lcd_Req_Buffer_t;
typedef struct
{
    u8 *Str;
    u8 Length;
    u8 Posx;
    u8 Posy;
    u8 CharIdx;
    Lcd_Req_Buffer_t BufferState;
} Lcd_Task_Req;

extern Lcd_Task_Req Tasks_Req[NUMBER_OF_USER_REQS];


void LCD_vidInit();

static void LCD_vidInitSeq(void);

static void LCD_vidWriteSeq(void);

LCD_enuErrorStat_t LCD_enuSend(u8 Data, u8 Cpy_u8Data);

LCD_enuErrorStat_t LCD_enuGotoXY(u8 Cpy_u8Xpos, u8 Cpy_u8Ypos);

LCD_enuErrorStat_t LCD_enuWriteString(u8 *Add_pu8String);

LCD_enustate_t LCD_enuWriteStringAsync(const u8 *CpyStr, u8 CpyStrLen, u8 Cpy_u8Xpos, u8 Cpy_u8Ypos);

static void LCD_Task(void);

#endif
