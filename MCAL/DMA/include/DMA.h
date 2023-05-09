#include "Std_Types.h"

/**
 * @defgroup DMA_Channel_selection DMA Channel selection
 * @brief    DMA channel selection
 * @{
 */
#define DMA_CHANNEL_0 (u32)0x10000000
#define DMA_CHANNEL_1 (u32)0x12000000
#define DMA_CHANNEL_2 (u32)0x14000000
#define DMA_CHANNEL_3 (u32)0x16000000
#define DMA_CHANNEL_4 (u32)0x18000000
#define DMA_CHANNEL_5 (u32)0x1A000000
#define DMA_CHANNEL_6 (u32)0x1C000000
#define DMA_CHANNEL_7 (u32)0x1E000000

/**
  * @defgroup DMA_Memory_burst DMA Memory burst
  * @brief    DMA memory burst 
  * @{
  */ 
#define DMA_MBURST_SINGLE  (u32)0x10000000
#define DMA_MBURST_INC4  (u32)0x10800000          
#define DMA_MBURST_INC8  (u32)0x11000000          
#define DMA_MBURST_INC16 (u32)0x11800000    

/**
  * @defgroup DMA_Peripheral_burst DMA Peripheral burst
  * @brief    DMA Peripheral burst 
  * @{
  */ 
#define DMA_PBURST_SINGLE  (u32)0x10000000
#define DMA_PBURST_INC4  (u32)0x10200000          
#define DMA_PBURST_INC8  (u32)0x10400000          
#define DMA_PBURST_INC16 (u32)0x10600000 

/** @defgroup DMA_Priority_level DMA Priority level
  * @brief    DMA priority levels 
  * @{
  */
#define DMA_PRIORITY_LOW           (u32)0x10000000
#define DMA_PRIORITY_MEDIUM        (u32)0x10010000
#define DMA_PRIORITY_HIGH          (u32)0x10020000
#define DMA_PRIORITY_VERY_HIGH     (u32)0x10030000

/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @brief    DMA memory data size 
  * @{ 
  */
#define DMA_MSIZE_BYTE              (u32)0x10000000
#define DMA_MSIZE_HALFWORD          (u32)0x10002000
#define DMA_MSIZE_WORD              (u32)0x10004000
#define DMA_MSIZE_RESERVED          (u32)0x10006000


/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
  * @brief    DMA peripheral data size 
  * @{
  */ 
#define DMA_PSIZE_BYTE          (u32)0x10000000
#define DMA_PSIZE_HALFWORD      (u32)0x10000800
#define DMA_PSIZE_WORD          (u32)0x10001000
#define DMA_PSIZE_RESERVED      (u32)0x10001800

/** @defgroup DMA_Memory_incremented_mode DMA Memory incremented mode
  * @brief    DMA memory incremented mode 
  * @{
  */ 
#define DMA_MINC_ENABLE       (u32)0x10000400  
#define DMA_MINC_DISABLE      (u32)0x10000000  

/** @defgroup DMA_Peripheral_incremented_mode DMA Peripheral incremented mode
  * @brief    DMA peripheral incremented mode 
  * @{
  */ 
#define DMA_PINC_ENABLE       (u32)0x10000200  
#define DMA_PINC_DISABLE      (u32)0x10000000  

/** @defgroup DMA_Data_transfer_direction DMA Data transfer direction
  * @brief    DMA data transfer direction 
  * @{
  */ 
#define DMA_PERIPH_TO_MEMORY  (u32)0x10000000
#define DMA_MEMORY_TO_PERIPH  (u32)0x10000040       
#define DMA_MEMORY_TO_MEMORY  (u32)0x10000080      

/** @defgroup DMA_mode DMA mode
  * @brief    DMA mode 
  * @{
  */ 
#define DMA_NORMAL         (u32)0x10000000
#define DMA_CIRCULAR       (u32)0x10000100
#define DMA_PFCTRL         (u32)0x10000020

/** @defgroup DMA_FIFO_direct_mode DMA FIFO direct mode
  * @brief    DMA FIFO direct mode
  * @{
  */
#define DMA_FIFOMODE_DISABLE   (u32)0x10000000    
#define DMA_FIFOMODE_ENABLE    (u32)0x10000004  

/** @defgroup DMA_FIFO_threshold_level DMA FIFO threshold level
  * @brief    DMA FIFO level 
  * @{
  */
#define DMA_FIFO_THRESHOLD_1QUARTERFULL      (u32)0x10000000
#define DMA_FIFO_THRESHOLD_HALFFULL          (u32)0x10000001
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL     (u32)0x10000002 
#define DMA_FIFO_THRESHOLD_FULL              (u32)0x10000003

/** @defgroup DMA_interrupt_enable_definitions DMA interrupt enable definitions
  * @brief    DMA interrupts definition 
  * @{
  */
#define DMA_IT_TC                         (u32)0x10000010
#define DMA_IT_HT                         (u32)0x10000008
#define DMA_IT_TE                         (u32)0x10000004
#define DMA_IT_DME                        (u32)0x10000002
#define DMA_IT_FE                         (u32)0x10000080 //FIFO ERROR

/** @defgroup DMA__Enable_definition DMA enable definition
  * @brief    DMA enable definition
  * @{
  */
#define DMA_ENABLE                        (u32)0x00000001


typedef enum
{
    DMA_enuOK,
    DMA_enuNOK,
    DMA_enuNullPtr
} DMA_enuErrorStatus_t;

/** @enum DMA_enuInstance_t DMA Instance
  * @brief    DMA Instance 
  * @{
  */ 
typedef enum
{
    DMA1,
    DMA2,
    DMA_enuInstanceCount
} DMA_enuInstance_t;

/** @enum DMA_enuStream_t DMA Stream
  * @brief    DMA Stream 
  * @{
  */ 
typedef enum
{
    DMA_enuStream0,
    DMA_enuStream1,
    DMA_enuStream2,
    DMA_enuStream3,
    DMA_enuStream4,
    DMA_enuStream5,
    DMA_enuStream6,
    DMA_enuStream7,
    DMA_enuStreamCount
} DMA_enuStream_t;

/**
 * @brief  DMA Configuration Structure definition
 */
typedef struct
{
    u32 Instance; /*!< Specifies the Instance of the used DMA used for the specified MCU.
                           This parameter can be a value of @ref DMA_enuInstance_t                    */

    u32 Stream;  /*!< Specifies the Stream used for the specified DMA.
                           This parameter can be a value of @ref DMA_enuStream_t                    */

    u32 Channel; /*!< Specifies the channel used for the specified stream.
                           This parameter can be a value of @ref DMA_Channel_selection                    */

    u32 Direction; /*!< Specifies if the data will be transferred from memory to peripheral,
                             from memory to memory or from peripheral to memory.
                             This parameter can be a value of @ref DMA_Data_transfer_direction              */

    u32 PeriphInc; /*!< Specifies whether the Peripheral address register should be incremented or not.
                             This parameter can be a value of @ref DMA_Peripheral_incremented_mode          */

    u32 MemInc; /*!< Specifies whether the memory address register should be incremented or not.
                          This parameter can be a value of @ref DMA_Memory_incremented_mode              */

    u32 PeriphDataAlignment; /*!< Specifies the Peripheral data width.
                                       This parameter can be a value of @ref DMA_Peripheral_data_size                 */

    u32 MemDataAlignment; /*!< Specifies the Memory data width.
                                    This parameter can be a value of @ref DMA_Memory_data_size                     */

    u32 Mode; /*!< Specifies the operation mode of the DMAy Streamx.
                        This parameter can be a value of @ref DMA_mode
                        @note The circular buffer mode cannot be used if the memory-to-memory
                              data transfer is configured on the selected Stream                        */

    u32 Priority; /*!< Specifies the software priority for the DMAy Streamx.
                            This parameter can be a value of @ref DMA_Priority_level                       */

    u32 FIFOMode; /*!< Specifies if the FIFO mode or Direct mode will be used for the specified stream.
                            This parameter can be a value of @ref DMA_FIFO_direct_mode
                            @note The Direct mode (FIFO mode disabled) cannot be used if the
                                  memory-to-memory data transfer is configured on the selected stream       */

    u32 FIFOThreshold; /*!< Specifies the FIFO threshold level.
                                 This parameter can be a value of @ref DMA_FIFO_threshold_level                  */

    u32 MemBurst; /*!< Specifies the Burst transfer configuration for the memory transfers.
                            It specifies the amount of data to be transferred in a single non interruptible
                            transaction.
                            This parameter can be a value of @ref DMA_Memory_burst
                            @note The burst mode is possible only if the address Increment mode is enabled. */

    u32 PeriphBurst; /*!< Specifies the Burst transfer configuration for the peripheral transfers.
                               It specifies the amount of data to be transferred in a single non interruptible
                               transaction.
                               This parameter can be a value of @ref DMA_Peripheral_burst
                               @note The burst mode is possible only if the address Increment mode is enabled. */
} DMA_strCfg_t;



/**
 * @return Error status if wrong configurations or Null Pointer Exception
 * @param Addr_pstrCfg : Address pointer to created object for the post compile configurations
 * @brief Initialize DMA Module
*/
DMA_enuErrorStatus_t DMA_enuInit(DMA_strCfg_t * Addr_pstrCfg);
/**
 * @return Error status if wrong configurations or Null Pointer Exception
 * @param Addr_pstrCfg : Address pointer to created object for the post compile configurations
 * @param Addr_pu32SrcAddress : Source address 
 * @param Addr_pu32DstAddress : Destination address
 * @param Cpy_u16DataLength : Data Length
 * @brief Start DMA specified stream
*/
DMA_enuErrorStatus_t DMA_enuStart(DMA_strCfg_t *Addr_pstrCfg,u32 * Addr_pu32SrcAddress,u32 * Addr_pu32DstAddress,u16 Cpy_u16DataLength);

/**
 * @return Error status if wrong configurations
 * @param Cpy_enuInstance : Instance of the DMA used 
 * @param Stream : Current used Stream
 * @brief Disable DMA specified stream
*/
DMA_enuErrorStatus_t DMA_enuAbort(DMA_enuInstance_t Cpy_enuInstance, DMA_enuStream_t Cpy_u32Stream);


/**
 * @return Error status if wrong configurations
 * @param Cpy_enuInstance : Instance of the DMA used 
 * @param Stream : Current used Stream
 * @param Cpy_u32InterruptEnable : @ref DMA_interrupt_enable_definitions
 * @brief Enable desired interrupts for the DMA module
*/
DMA_enuErrorStatus_t DMA_enuEnableInterrupt(DMA_enuInstance_t Cpy_enuInstance, DMA_enuStream_t Cpy_u32Stream,u32 Cpy_u32InterruptEnable);


/**
 * @return Error status if wrong configurations
 * @param Cpy_enuInstance : Instance of the DMA used 
 * @param Stream : Current used Stream
 * @param Cpy_u32InterruptEnable : @ref DMA_interrupt_enable_definitions
 * @brief Disable desired interrupts for the DMA module
*/
DMA_enuErrorStatus_t DMA_enuDisableInterrupt(DMA_enuInstance_t Cpy_enuInstance, DMA_enuStream_t Cpy_u32Stream,u32 Cpy_u32InterruptEnable);
