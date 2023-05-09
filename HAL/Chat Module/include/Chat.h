#include "Std_Types.h"
#include "USART.h"

typedef void(*Chat_vidCBF)(void);

typedef enum
{
   ChatStream_enuOK,
   ChatStream_enuNOK
}Chat_enuErrorStatus_t;

/*Enumuration defining the options a user can use in the application to send the data needed*/
typedef enum
{
   ChatStream_USART1,
   ChatStream_USART2,
   ChatStream_USART6,
   ChatStream_SPI1,
   ChatStream_SPI2,
   ChatStream_SPI3,
   ChatStream_SPI4,
   ChatStream_I2C1,
   ChatStream_I2C2,
   ChatStream_I2C3

}ChatStream_enuChannel_t;

/*****************************************************************
* Return : Error status if wrong configurations
*
* Input  : void
*
* Description : Initialize Chat module based on the pre-cfg added in the cfg.c file
* ***************************************************************
*/
Chat_enuErrorStatus_t Chat_Init(void);
/*****************************************************************
* Return : Error status if wrong configurations
*
* Input  : -ChatStream Channel Enumeration type identifying the desired Communication Protocol Channel
*          -u16 Pointer to the desired buffer to be sent
*          -u32 size of the buffer
*          -void Callback function to notify the user after send is done
*
* Description : Handles send request needed for the user
* ***************************************************************
*/
Chat_enuErrorStatus_t Chat_SendMsg(ChatStream_enuChannel_t Cpy_enuChannel, u16 *Add_pu16Msg, u32 Cpy_u32Size,Chat_vidCBF CBF);
/*****************************************************************
* Return : Error status if wrong configurations
*
* Input  : -ChatStream Channel Enumeration type identifying the desired Communication Protocol Channel
*          -u16 Pointer to the desired buffer to be Received
*          -u32 size of the buffer
*          -void Callback function to notify the user after Receive is done
*
* Description : Handles Receive request needed for the user
* ***************************************************************
*/
Chat_enuErrorStatus_t Chat_RecvMsg(ChatStream_enuChannel_t Cpy_enuChannel, u16 *Add_pu16Msg, u32 Cpy_u32Size,Chat_vidCBF CBF);
