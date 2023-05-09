#include "Chat.h"
#include "Chat_Cfg.h"

Chat_enuErrorStatus_t Chat_Init(void)
{
   Chat_enuErrorStatus_t Local_enuChatErrorstatus = ChatStream_enuOK;
   GPIO_enuErrorStatus_t Local_enuGpioErrorstatus = GPIO_enuOK;
   USART_enuErrorStatus Local_enuUsartErrorstatus = USART_enuOK;
   u8 Local_u8Idx = 0;
   u8 Local_GPIO_AF = 0;

   for (Local_u8Idx = 0; Local_u8Idx < ChatStreams_NUM; Local_u8Idx++)
   {
       if (ChatStream_strCfg[Local_u8Idx].USART_Cfg)
       {
           /*Select the suitable Alternate function based on the selected channel*/
           switch (ChatStream_strCfg[Local_u8Idx].USART_Cfg.Channel)
           {
           case USART1:
               Local_GPIO_AF = GPIO_AF7;
               break;
           case USART2:
               Local_GPIO_AF = GPIO_AF7;
               break;
           case USART6:
               Local_GPIO_AF = GPIO_AF8;
               break;
           default:
               Local_enuUsartErrorstatus = USART_enuWrong_Cfg;
               break;
           }
           /*Configure Tx & Rx pins */
           switch (ChatStream_strCfg[Local_u8Idx].USART_Cfg.DataDirection)
           {
           case USART_TRANSMITER:
               Local_enuGpioErrorstatus = GPIO_enuInit(&ChatStream_strCfg[Local_u8Idx].USART_Cfg.TXPin);
               Local_enuGpioErrorstatus = GPIO_enuSelectAF(Local_GPIO_AF, ChatStream_strCfg[Local_u8Idx].USART_Cfg.TXPin.Port_Num, ChatStream_strCfg[Local_u8Idx].USART_Cfg.TXPin.Pin_Num);
               break;
           case USART_RECEIVER:
               Local_enuGpioErrorstatus = GPIO_enuInit(&ChatStream_strCfg[Local_u8Idx].USART_Cfg.RXPin);
               Local_enuGpioErrorstatus = GPIO_enuSelectAF(Local_GPIO_AF, ChatStream_strCfg[Local_u8Idx].USART_Cfg.RXPin.Port_Num, ChatStream_strCfg[Local_u8Idx].USART_Cfg.RXPin.Pin_Num);
               break;
           case USART_TRANSMITER_RECEIVER:
               Local_enuGpioErrorstatus = GPIO_enuInit(&ChatStream_strCfg[Local_u8Idx].USART_Cfg.TXPin);
               Local_enuGpioErrorstatus = GPIO_enuInit(&ChatStream_strCfg[Local_u8Idx].USART_Cfg.RXPin);
               Local_enuGpioErrorstatus = GPIO_enuSelectAF(Local_GPIO_AF, ChatStream_strCfg[Local_u8Idx].USART_Cfg.TXPin.Port_Num, ChatStream_strCfg[Local_u8Idx].USART_Cfg.TXPin.Pin_Num);
               Local_enuGpioErrorstatus = GPIO_enuSelectAF(Local_GPIO_AF, ChatStream_strCfg[Local_u8Idx].USART_Cfg.RXPin.Port_Num, ChatStream_strCfg[Local_u8Idx].USART_Cfg.RXPin.Pin_Num);
               break;
           default:
               Local_enuUsartErrorstatus = USART_enuWrong_Cfg;
               break;
           }
           if (Local_enuUsartErrorstatus != USART_enuOK)
           {
               Local_enuChatErrorstatus = ChatStream_enuNOK;
               break;
           }
           else
           {
               Local_enuUsartErrorstatus = USART_Init(&ChatStream_strCfg[Local_u8Idx].USART_Cfg);
               if (Local_enuUsartErrorstatus != USART_enuOK)
               {
                   Local_enuChatErrorstatus = ChatStream_enuNOK;
                   break;
               }
               else
               {
                   /*Do Nothing*/
               }
           }
       }
   }

   return Local_enuChatErrorstatus;
}
