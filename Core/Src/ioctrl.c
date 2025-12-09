/**
 ******************************************************************************
 * @file           : ioctrl.c
 * @brief          : Functions for IO Control
 ******************************************************************************
 * @attention
 * @PIC: ricky.siah@georgekent.net
 * @Created: 09 Dec 2025
 * @Copyright: George Kent (Malaysia) Berhad.
 *
 ******************************************************************************
 **/

/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "ioctrl.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
void IOCTRL_MainPower_Enable(IOCTRL_Pin_t enable)
{
	HAL_GPIO_WritePin(PWR_EN_GPIO_Port, PWR_EN_Pin, (enable == ON) ? ON : OFF);
}

IOCTRL_Pin_t IOCTRL_MainPower_IsEnabled(void)
{
	return ((HAL_GPIO_ReadPin(PWR_EN_GPIO_Port, PWR_EN_Pin)) == GPIO_PIN_SET) ? ON : OFF;
}

void IOCTRL_NFCPower_Enable(IOCTRL_Pin_t enable)
{
	HAL_GPIO_WritePin(NFC_PWR_GPIO_Port, NFC_PWR_Pin, (enable == ON) ? ON : OFF);
}

IOCTRL_Pin_t IOCTRL_NFCPower_IsEnable(void)
{
	return ((HAL_GPIO_ReadPin(NFC_PWR_GPIO_Port, NFC_PWR_Pin)) == GPIO_PIN_SET) ? ON : OFF;
}

void IOCTRL_RadioPower_Enable(IOCTRL_Pin_t enable)
{
	HAL_GPIO_WritePin(NB_PWR_EN_GPIO_Port, NB_PWR_EN_Pin, (enable == ON) ? ON : OFF);
}

void IOCTRL_RadioPowerBypass_Enable(IOCTRL_Pin_t enable)
{
	HAL_GPIO_WritePin(NB_PWR_BYPASS_GPIO_Port, NB_PWR_BYPASS_Pin, (enable == ON) ? ON : OFF);
}

void IOCTRL_RadioPowerSignal_Enable(IOCTRL_Pin_t enable)
{
	HAL_GPIO_WritePin(NB_ONOFF_GPIO_Port, NB_ONOFF_Pin, (enable == ON) ? ON : OFF);
}

void IOCTRL_RadioReset_Enable(IOCTRL_Pin_t enable)
{
	HAL_GPIO_WritePin(NB_RESET_GPIO_Port, NB_RESET_Pin, (enable == ON) ? ON : OFF);
}

void IOCTRL_LCGpio1_Enable(IOCTRL_Pin_t enable)
{
	HAL_GPIO_WritePin(COMP2_INP_CH1_GPIO_Port, COMP2_INP_CH1_Pin, (enable == ON) ? ON : OFF);
}

void IOCTRL_LCGpio2_Enable(IOCTRL_Pin_t enable)
{
	HAL_GPIO_WritePin(COMP2_INP_CH2_GPIO_Port, COMP2_INP_CH2_Pin, (enable == ON) ? ON : OFF);
}