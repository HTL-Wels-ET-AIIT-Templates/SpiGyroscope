//
// AIIT project template for STM32F429I-Discovery board
// Project: gyroscope
//


// Includes ------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"

#include "gyro.h"

// Variables ------------------------------------------------------------------
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define L3GD20_FLAG_TIMEOUT             ((uint32_t)0x1000)

// Function Declarations ------------------------------------------------------
static void gpioInit(void);
static void spiInit(void);
static void gyroConfig(void);
static void gyroWrite(uint8_t* pBuffer, uint8_t writeAddr, uint16_t numByteToWrite);
static void gyroRead(uint8_t* pBuffer, uint8_t readAddr, uint16_t numByteToRead);
static uint8_t gyroSendByte(uint8_t byte);


// Functions ------------------------------------------------------------------

/**
  * Initialization Code for module gyro
	* @param None
  * @retval None
  */
void gyroInit(void) {
	gpioInit();
  spiInit();
  gyroConfig();
	
}

/**
  * Task function of module gyro.
	* TODO: Read data and show it on display
	* @param None
  * @retval None
  */
void gyroTask(void){
	// TODO: What has to be done in our main loop?

  
  
}

/**
  * @brief  configure gpios for application
  * @param  None
  * @retval None
  */
static void gpioInit(void)
{
	// TODO: What GPIOs do we need? -> Configure them!

  
  
  
}

/**
  * @brief  configure spi communication for application
  * @param  None
  * @retval None
  */
void spiInit(void) {
	SPI_I2S_DeInit(SPI5);
	// TODO: What SPI is used? -> Configure it!


  
  
  
}

/**
  * @brief  configure gyroscope
  * @param  None
  * @retval None
  */
static void gyroConfig(void) {
	// TODO: Configure CTRL1 and CTRL4 of gyroscope

  
  
  
}

/**
  * @brief  Writes a block of data to the L3GD20.
  * @param  pBuffer : pointer to the buffer containing the data to be written to the L3GD20.
  * @param  writeAddr : L3GD20's internal address to write to.
  * @param  numByteToWrite: Number of bytes to write.
  * @retval None
  */
static void gyroWrite(uint8_t* pBuffer, uint8_t writeAddr, uint16_t numByteToWrite)
{
  /* Configure the MS bit: 
       - When 0, the address will remain unchanged in multiple read/write commands.
       - When 1, the address will be auto incremented in multiple read/write commands.
  */
  if(numByteToWrite > 0x01)
  {
    writeAddr |= (uint8_t)0x40;
  }
  /* Set chip select Low at the start of the transmission */
  GPIO_ResetBits(GPIOC, GPIO_Pin_1);
  
  /* Send the Address of the indexed register */
  gyroSendByte(writeAddr);

  /* Send the data that will be written into the device (MSB First) */
  while(numByteToWrite > 0x00)
  {
    gyroSendByte(*pBuffer);
    numByteToWrite--;
    pBuffer++;
  }
  
  /* Set chip select High at the end of the transmission */ 
  GPIO_SetBits(GPIOC, GPIO_Pin_1);
}

/**
  * @brief  Reads a block of data from the L3GD20.
  * @param  pBuffer : pointer to the buffer that receives the data read from the L3GD20.
  * @param  readAddr : L3GD20's internal address to read from.
  * @param  numByteToRead : number of bytes to read from the L3GD20.
  * @retval None
  */
static void gyroRead(uint8_t* pBuffer, uint8_t readAddr, uint16_t numByteToRead)
{  
	// TODO: Implement reading of registers from gyroscope
  if(numByteToRead > 0x01)
  {

  }
  else
  {

  }

  
  
  
  
}  

/**
  * @brief  Sends a Byte through the SPI interface and return the Byte received 
  *         from the SPI bus.
  * @param  Byte : Byte send.
  * @retval The received byte value
  */
static uint8_t gyroSendByte(uint8_t byte)
{
  /* Loop while DR register in not empty */
  uint32_t L3GD20Timeout = L3GD20_FLAG_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) == RESET)
  {
    if((L3GD20Timeout--) == 0) 
      return 0xFF;
  }
  
  /* Send a Byte through the SPI peripheral */
  SPI_I2S_SendData(SPI5, (uint16_t)byte);
  /* Wait to receive a Byte */
  L3GD20Timeout = L3GD20_FLAG_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_RXNE) == RESET)
  {
    if((L3GD20Timeout--) == 0) 
      return 0xFE;
  }
  
  /* Return the Byte read from the SPI bus */
  return (uint8_t)SPI_I2S_ReceiveData(SPI5);
}

