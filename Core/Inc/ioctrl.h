/**
  ******************************************************************************
  * @file           : ioctrl.h
  * @brief          : Header for IO Control functions
  ******************************************************************************
  * @attention
  * @PIC: ricky.siah@georgekent.net
  * @Created: 03 Dec 2025
  * @Copyright: George Kent (Malaysia) Berhad.
  *
  ******************************************************************************
**/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IO_CONTROL_H_
#define IO_CONTROL_H_

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  OFF = 0,
  ON = !OFF
} IOCTRL_Pin_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void IOCTRL_MainPower_Enable(IOCTRL_Pin_t enable);
IOCTRL_Pin_t IOCTRL_MainPower_IsEnabled(void);
void IOCTRL_NFCPower_Enable(IOCTRL_Pin_t enable);
IOCTRL_Pin_t IOCTRL_NFCPower_IsEnable(void);
void IOCTRL_RadioPower_Enable(IOCTRL_Pin_t enable);
void IOCTRL_RadioPowerBypass_Enable(IOCTRL_Pin_t enable);
void IOCTRL_RadioPowerSignal_Enable(IOCTRL_Pin_t enable);
void IOCTRL_RadioReset_Enable(IOCTRL_Pin_t enable);
void IOCTRL_LCGpio1_Enable(IOCTRL_Pin_t enable);
void IOCTRL_LCGpio2_Enable(IOCTRL_Pin_t enable);

#endif /* IO_CONTROL_H_ */
