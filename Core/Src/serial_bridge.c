/**
 ******************************************************************************
 * @file           : serial_bridge.c
 * @brief          : Functions for serial bridge
 ******************************************************************************
 * @attention
 * @PIC: ricky.siah@georgekent.net
 * @Created: 03 Dec 2025
 * @Copyright: George Kent (Malaysia) Berhad.
 *
 ******************************************************************************
 **/

/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "ring_fifo.h"
#include "serial _bridge.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define MAX_BUFFER	1024

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
char rxByte;
char rxBuffer[MAX_BUFFER];
int rxLen = 0;
bool isCommReady = false;
RING_Fifo_t dbgReceived;

void init_serial_bridge(void)
{
	rbst_init(&dbgReceived, (uint8_t *)rxBuffer, MAX_BUFFER);
	printf("--- L433-BC66 Serial Bridge Test ---\r\n");

	if(HAL_UART_Receive_IT(&huart1, (uint8_t *)&rxByte, 1) != HAL_OK)
	{
		/* Transfer error in reception process */
		Error_Handler();
	}
}

// Function to handle the actual command processing
void process_command(char* cmd, int length)
{
	int nwLen = length - sizeof(COMMAND_BRG);
	if ((cmd[0] == STA_COMM) && (cmd[3] == END_COMM))
	{
		if (strncmp(&cmd[1], COMMAND_BRG, sizeof(COMMAND_BRG)) == 0)
		{
			// route AT command to BC66
			HAL_UART_Transmit(&hlpuart1, (uint8_t *)&cmd[4], nwLen, (10 * nwLen));
		}
		else if (strncmp(&cmd[1], COMMAND_GPIO, sizeof(COMMAND_GPIO)) == 0)
		{

		}
		else
		{
			printf("Received unknown command: %s\n", cmd);
		}
	}
	else
	{
		printf("Wrong STA/END command\r\n");
	}
}

void serial_bridge_task(void)
{
	char chKey = 0;

	if (!isCommReady && rbst_pop(&dbgReceived, (uint8_t *)&chKey) == SUCCESS)
	{
		printf("%c", chKey);	// echo key press

        // Append the character to our local buffer
        if (rxLen < (MAX_BUFFER - 1))
        {
        	rxBuffer[rxLen++] = chKey;

            // Check for end-of-line marker (simple check for '\n')
            if ((chKey == '\r') || (chKey == '\n'))
            {
                isCommReady = true;
            }
        }
        else
        {
            // Buffer overflow prevention/handling:
            // Reset buffer if too long without an EOL.
            rxLen = 0;
            printf("\nError: Command too long, buffer reset.\n");
        }
	}
	if (isCommReady) // Process the command once it's fully received
	{
		process_command(rxBuffer, rxLen);
		// Reset state for the next command
		rxLen = 0;
		isCommReady = false;
		memset(rxBuffer, 0, MAX_BUFFER); // Clear buffer for good measure
	}
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report end of IT Rx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	if(UartHandle == &huart1)
	{
		// Start another reception: provide the buffer pointer with offset and the buffer size
		if(HAL_UART_Receive_IT(&huart1, (uint8_t *)&rxByte, 1) != HAL_OK)
		{
			/* Transfer error in reception process */
			Error_Handler();
		}
		else
			rbst_push(&dbgReceived, rxByte);
	}
}

