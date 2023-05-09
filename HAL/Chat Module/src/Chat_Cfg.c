#include "Chat_Cfg.h"

const ChatStream_strCfg_t ChatStream_strCfg[ChatStreams_NUM] =
    {
        [ChatStream0] =
            {
                //USART1 cfgs
                .USART_Cfg.TXPin = GPIO_PIN9,
                .USART_Cfg.RXPin = GPIO_PIN10,
                .USART_Cfg.DataDirection = USART_TRANSMITER_RECEIVER,
                .USART_Cfg.Mode = USART_MODE_ASYNC_OVERSAMPLE__16_CHARSIZE__8_IDLEWAKEUP_EVENPARITY_NOBREAK_1STOP,
                .USART_Cfg.BaudRate = USART_enuBAUD_9600,
                .USART_Cfg.Channel = USART1

                //Other Protocols cfgs
            },
        [ChatStream1] =
            {
                //USART2 cfgs
                .USART_Cfg.TXPin = GPIO_PIN2,
                .USART_Cfg.RXPin = GPIO_PIN3,
                .USART_Cfg.DataDirection = USART_TRANSMITER_RECEIVER,
                .USART_Cfg.Mode = USART_MODE_ASYNC_OVERSAMPLE__16_CHARSIZE__8_IDLEWAKEUP_EVENPARITY_NOBREAK_1STOP,
                .USART_Cfg.BaudRate = USART_enuBAUD_9600,
                .USART_Cfg.Channel = USART2

                //Other Protocols cfgs
            },
        [ChatStream2] =
            {
                //USART6 cfgs
                .USART_Cfg.TXPin = GPIO_PIN11,
                .USART_Cfg.RXPin = GPIO_PIN12,
                .USART_Cfg.DataDirection = USART_TRANSMITER_RECEIVER,
                .USART_Cfg.Mode = USART_MODE_ASYNC_OVERSAMPLE__16_CHARSIZE__8_IDLEWAKEUP_EVENPARITY_NOBREAK_1STOP,
                .USART_Cfg.BaudRate = USART_enuBAUD_9600,
                .USART_Cfg.Channel = USART6

                //Other Protocols cfgs
            }};
