#include "Std_Types.h"
#include "USART.h"

/*Create ChatStream ## num If needed*/
typedef enum
{
   ChatStream0,
   ChatStream1,
   ChatStream2,
   ChatStreams_NUM
}ChatStream_enuInstances;

typedef struct
{
   USART_strCfg_t USART_Cfg;  //----------USART Configuration struct
   /*SPI_strCfg_t SPI_Cfg;*/  //-----------Spi  Configuration struct
   /*I2C_strCfg_t I2C_Cfg;*/  //-----------I2c  Configuration struct
   /*More Stuct for each protocol to configure*/

}ChatStream_strCfg_t;

extern const ChatStream_strCfg_t ChatStream_strCfg[ChatStreams_NUM];
