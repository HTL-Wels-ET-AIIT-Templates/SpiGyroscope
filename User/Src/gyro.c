//
// AIIT project template for STM32F429I-Discovery board
// Project: gyroscope
//


// Includes ------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "gyro.h"
#include "stm32f429i_discovery_lcd.h"

// Variables ------------------------------------------------------------------
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define L3GD20_FLAG_TIMEOUT             ((uint32_t)0x1000)

SPI_HandleTypeDef spiHandle;

static int ballDirection = 0;

// Function Declarations ------------------------------------------------------
static void gpioInit(void);
static void spiInit(void);
static void gyroConfig(void);
static void gyroWrite(uint8_t* pBuffer, uint8_t writeAddr, uint16_t numByteToWrite);
static void gyroRead(uint8_t* pBuffer, uint8_t readAddr, uint16_t numByteToRead);

static void movingBall(void);
static void setBallDirection(int dir);

// Functions ------------------------------------------------------------------

/**
 * Initialization Code for module gyro
 * @param None
 * @retval None
 */
void gyroInit(void) {
	gpioInit();
	spiInit();

	// check if SPI works by reading Who_Am_I Register
	//  uint8_t who;
	//  gyroRead(&who, L3GD20_WHO_AM_I_ADDR, 1);
	//  LCD_SetPrintPosition(4,0);
	//  printf("who: %x", who);

	gyroConfig();

}

/**
 * Task function of module gyro.
 * TODO: Read data and show it on display
 * @param None
 * @retval None
 */
void gyroTask(void) {
	// TODO: What has to be done in our main loop?


}

/**
 * @brief  draw the moving ball
 * @param  None
 * @retval None
 */
static void movingBall(void) {
	static int x = 120;
	static int y = 290;

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_FillCircle(x, y, 10);

	if (ballDirection > 0 && x < LCD_GetXSize()) {
		x++;
	}
	if (ballDirection < 0 && x > 0) {
		x--;
	}

	LCD_SetTextColor(LCD_COLOR_YELLOW);
	LCD_FillCircle(x, y, 10);

}

/**
 * @brief  change direction of moving ball
 * @param  dir direction (0 stop, 1 move right, -1 move left)
 * @retval None
 */
static void setBallDirection(int dir) {
	ballDirection = dir;
}

/**
 * @brief  configure gpios for application
 * @param  None
 * @retval None
 */
static void gpioInit(void) {
	// TODO: What GPIOs do we need? -> Configure them!

}

/**
 * @brief  configure spi communication for application
 * @param  None
 * @retval None
 */
void spiInit(void) {
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
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);

	/* Send the Address of the indexed register */
	if(HAL_SPI_Transmit(&spiHandle, &writeAddr, 1, L3GD20_FLAG_TIMEOUT) != HAL_OK)
	{
		/* Transfer error in transmission process */
		Error_Handler();
	}

	/* Send the data that will be written into the device (MSB First) */
	if(HAL_SPI_Transmit(&spiHandle, pBuffer, numByteToWrite, L3GD20_FLAG_TIMEOUT) != HAL_OK)
	{
		/* Transfer error in transmission process */
		Error_Handler();
	}

	/* Set chip select High at the end of the transmission */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
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
	if(numByteToRead > 0x01) {

	}
	else {

	}
}  



