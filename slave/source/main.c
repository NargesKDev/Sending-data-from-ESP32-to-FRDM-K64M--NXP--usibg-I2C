
/**
 * @file main.cpp
 * @author Narges Kurkani
 * @brief This code is receiving user data sent by ESP32 using I2C protocol
 * 		  according the received message it turns on different on-board LED color
 * 		   and sends confirmation message to ESP32.
 * @version 0.1
 * @date 2025-04-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <ctype.h>
#include "board.h"
#include "pin_mux.h"
#include "fsl_i2c.h"
#include "fsl_debug_console.h"

// Set default SCL stop hold time to 4us for 100kHz baudrate according to spec.
// For 400kHz and 1mHz the hold time is 0.6us and 0.26us.
#define I2C_SLAVE_HOLD_TIME_NS 4000U
#define I2C_SLAVE_ADDRESS 0x50U
#define I2C_DATA_LENGTH 32U

volatile static bool completed = false;
static char buffer[I2C_DATA_LENGTH] = {0};

#define RED_LED_PORT    PORTB
#define RED_LED_GPIO    GPIOB
#define RED_LED_PIN     22U

#define GREEN_LED_PORT  PORTE
#define GREEN_LED_GPIO  GPIOE
#define GREEN_LED_PIN   26U

#define BLUE_LED_PORT   PORTB
#define BLUE_LED_GPIO   GPIOB
#define BLUE_LED_PIN    21U

const char buffer1[4] = {'d', 'o', 'n', 'e'};
const char buffer2[4] = {'f','a','i','l'};

void led_off()
{
    GPIO_PortSet(RED_LED_GPIO, 1U << RED_LED_PIN);
    GPIO_PortSet(GREEN_LED_GPIO, 1U << GREEN_LED_PIN);
    GPIO_PortSet(BLUE_LED_GPIO, 1U << BLUE_LED_PIN);
}
void simple_delay(volatile uint32_t count)
{
    while (count--)
    {
        __NOP(); // Assembly No Operation (optional, for better optimization)
    }
}
static void i2c_slave_callback(I2C_Type *base, i2c_slave_transfer_t *xfer, void *data)
{
    (void)base;
    (void)data;

    switch (xfer->event)
    {
    /* Address match event */
    case kI2C_SlaveAddressMatchEvent:
        xfer->data = NULL;
        xfer->dataSize = 0;
        break;

    case kI2C_SlaveTransmitEvent:
    	for(int i = 0; i < I2C_DATA_LENGTH; i++) {
    		buffer[i] = toupper(buffer[i]);
    	}
        //xfer->data = buffer;
        //xfer->dataSize = I2C_DATA_LENGTH;

        if (memcmp(buffer, "RED", 3) == 0) {
		   led_off();
		   GPIO_PortClear(RED_LED_GPIO, 1U << RED_LED_PIN);
		   xfer->data = buffer1;
		   xfer->dataSize = I2C_DATA_LENGTH;

		   simple_delay(100000);

	   }
        else if((memcmp(buffer, "GREEN", 5) == 0)){
 		   led_off();
 		   GPIO_PortClear(GREEN_LED_GPIO, 1U << GREEN_LED_PIN);
			xfer->data = buffer1;
			xfer->dataSize = I2C_DATA_LENGTH;
			simple_delay(100000);

 	   }
		else if((memcmp(buffer, "BLUE", 4) == 0)){
		   led_off();
		   GPIO_PortClear(BLUE_LED_GPIO, 1U << BLUE_LED_PIN);
		   xfer->data = buffer1;
		   xfer->dataSize = I2C_DATA_LENGTH;
		   simple_delay(100000);
			   }
		else if((memcmp(buffer, "OFF", 3) == 0)){
		   led_off();
		   xfer->data = buffer1;
		   xfer->dataSize = I2C_DATA_LENGTH;
		   simple_delay(100000);
		}
		else {
			xfer->data = buffer2;
			xfer->dataSize = I2C_DATA_LENGTH;
		}
        break;

    /* Receive request */
    case kI2C_SlaveReceiveEvent:
        // Update information for received process
        xfer->data = buffer;
        xfer->dataSize = I2C_DATA_LENGTH;
        break;

    /* Transfer done */
    case kI2C_SlaveCompletionEvent:
    	completed = true;
        xfer->data = NULL;
        xfer->dataSize = 0;
        break;

    default:
    	completed = false;
        break;
    }
}

int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortE);

	PORT_SetPinMux(RED_LED_PORT, RED_LED_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(GREEN_LED_PORT, GREEN_LED_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(BLUE_LED_PORT, BLUE_LED_PIN, kPORT_MuxAsGpio);

	gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 1}; // Default OFF
	GPIO_PinInit(RED_LED_GPIO, RED_LED_PIN, &led_config);
	GPIO_PinInit(GREEN_LED_GPIO, GREEN_LED_PIN, &led_config);
	GPIO_PinInit(BLUE_LED_GPIO, BLUE_LED_PIN, &led_config);


    i2c_slave_config_t config;
    I2C_SlaveGetDefaultConfig(&config);

    config.addressingMode     = kI2C_Address7bit;
    config.slaveAddress       = I2C_SLAVE_ADDRESS;
    config.upperAddress       = 0; /* not used for this example */
    config.sclStopHoldTime_ns = I2C_SLAVE_HOLD_TIME_NS;

    I2C_SlaveInit(I2C0, &config, CLOCK_GetFreq(I2C0_CLK_SRC));

    i2c_slave_handle_t handle;
    memset(&handle, 0, sizeof(handle));
    I2C_SlaveTransferCreateHandle(I2C0, &handle, i2c_slave_callback, NULL);

    while (1)
    {
    	completed = false;

        // Set up slave transfer.
        I2C_SlaveTransferNonBlocking(I2C0, &handle, kI2C_SlaveCompletionEvent | kI2C_SlaveAddressMatchEvent);

        // wait for transfer completed.
        while (!completed)
        {
        	;
        }
    }

    return 0;
}
