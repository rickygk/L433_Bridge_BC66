/**
  ******************************************************************************
  * @file           : serial_bridge.h
  * @brief          : Header for serial bridge
  ******************************************************************************
  * @attention
  * @PIC: ricky.siah@georgekent.net
  * @Created: 03 Dec 2025
  * @Copyright: George Kent (Malaysia) Berhad.
  *
  ******************************************************************************
**/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SERIAL_BRIDGE_H_
#define SERIAL_BRIDGE_H_

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	NONE_LCpin,
	PIN_LC1,
	PIN_LC2
} LC_Pin_t;

/* Exported constants --------------------------------------------------------*/
#define STA_COMM		'#'		// start command
#define END_COMM		':'		// end command, ex. #BG:{msg}

#define COMMAND_BRG 	"BG"	// bridge to BC66
#define COMMAND_GPIO	"IO"	// bridge to all GPIOs
#define COMMAND_EEP		"EP"	// bridge to EEPROM M95M01

/* Exported macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void init_serial_bridge(void);
void serial_bridge_task(void);

#endif /* SERIAL_BRIDGE_H_ */
