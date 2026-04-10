/*
 * exp_board.c
 *
 *  Created on: Feb 18, 2023
 *      Author: Adam
 */
#include "main.h"

void initPins(uint16_t pins)
{
    // Initialize specified pins as outputs
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pins;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void deinitPins(uint16_t pins)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = pins;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void ZeroLEDs(void)
{
	deinitPins(RGB_LED_1_Pin | RGB_LED_2_Pin | RGB_LED_3_Pin);
}

void DisplayColor(int R, int G, int B)
{
	int pulse_R = (256 - R);
	int pulse_G = (256 - G);
	int pulse_B = (256 - B);



	TIM_HandleTypeDef htim3;
	htim3.Instance = TIM3;

	TIM_OC_InitTypeDef sConfigOC = {0};

	sConfigOC.Pulse = pulse_R;
	if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
	Error_Handler();
	}
	sConfigOC.Pulse = pulse_G;
	if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
	Error_Handler();
	}
	sConfigOC.Pulse = pulse_B;
	if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
	Error_Handler();
	}


}


void TurnOnLed(int led_no, int led_col)
{
	// Set all pins to high impedance (input mode)
	// HAL_GPIO_DeInit(GPIOB, RGB_LED_1_Pin | RGB_LED_2_Pin | RGB_LED_3_Pin | RGB_LED_4_Pin);
	deinitPins(RGB_LED_1_Pin | RGB_LED_2_Pin | RGB_LED_3_Pin | RGB_LED_4_Pin);

	switch(led_no){
		case 1:
			initPins(RGB_LED_4_Pin);
			HAL_GPIO_WritePin(RGB_LED_4_GPIO_Port, RGB_LED_4_Pin, GPIO_PIN_SET);

			switch(led_col){
				case 'r':
					initPins(RGB_LED_1_Pin);
					HAL_GPIO_WritePin(RGB_LED_1_GPIO_Port, RGB_LED_1_Pin, GPIO_PIN_RESET);
					break;

				case 'g':
					initPins(RGB_LED_2_Pin);
					HAL_GPIO_WritePin(RGB_LED_2_GPIO_Port, RGB_LED_2_Pin, GPIO_PIN_RESET);
					break;

				case 'b':
					initPins(RGB_LED_3_Pin);
					HAL_GPIO_WritePin(RGB_LED_3_GPIO_Port, RGB_LED_3_Pin, GPIO_PIN_RESET);
					break;

				case 'm':
					initPins(RGB_LED_1_Pin | RGB_LED_3_Pin);
					HAL_GPIO_WritePin(RGB_LED_1_GPIO_Port, RGB_LED_1_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(RGB_LED_3_GPIO_Port, RGB_LED_3_Pin, GPIO_PIN_RESET);
					break;
			}
			break;

		case 2:
			initPins(RGB_LED_3_Pin);
			HAL_GPIO_WritePin(RGB_LED_3_GPIO_Port, RGB_LED_3_Pin, GPIO_PIN_SET);

			switch(led_col){
				case 'r':
					initPins(RGB_LED_4_Pin);
					HAL_GPIO_WritePin(RGB_LED_4_GPIO_Port, RGB_LED_4_Pin, GPIO_PIN_RESET);
					break;

				case 'g':
					initPins(RGB_LED_1_Pin);
					HAL_GPIO_WritePin(RGB_LED_1_GPIO_Port, RGB_LED_1_Pin, GPIO_PIN_RESET);
					break;

				case 'b':
					initPins(RGB_LED_2_Pin);
					HAL_GPIO_WritePin(RGB_LED_2_GPIO_Port, RGB_LED_2_Pin, GPIO_PIN_RESET);
					break;
			}
			break;

		case 3:
			initPins(RGB_LED_2_Pin);
			HAL_GPIO_WritePin(RGB_LED_2_GPIO_Port, RGB_LED_2_Pin, GPIO_PIN_SET);

			switch(led_col){
				case 'r':
					initPins(RGB_LED_3_Pin);
					HAL_GPIO_WritePin(RGB_LED_3_GPIO_Port, RGB_LED_3_Pin, GPIO_PIN_RESET);
					break;

				case 'g':
					initPins(RGB_LED_4_Pin);
					HAL_GPIO_WritePin(RGB_LED_4_GPIO_Port, RGB_LED_4_Pin, GPIO_PIN_RESET);
					break;

				case 'b':
					initPins(RGB_LED_1_Pin);
					HAL_GPIO_WritePin(RGB_LED_1_GPIO_Port, RGB_LED_1_Pin, GPIO_PIN_RESET);
					break;
			}
			break;

		case 4:
			initPins(RGB_LED_1_Pin);
			HAL_GPIO_WritePin(RGB_LED_1_GPIO_Port, RGB_LED_1_Pin, GPIO_PIN_SET);

			switch(led_col){
				case 'r':
					initPins(RGB_LED_2_Pin);
					HAL_GPIO_WritePin(RGB_LED_2_GPIO_Port, RGB_LED_2_Pin, GPIO_PIN_RESET);
					break;

				case 'g':
					initPins(RGB_LED_3_Pin);
					HAL_GPIO_WritePin(RGB_LED_3_GPIO_Port, RGB_LED_3_Pin, GPIO_PIN_RESET);
					break;

				case 'b':
					initPins(RGB_LED_4_Pin);
					HAL_GPIO_WritePin(RGB_LED_4_GPIO_Port, RGB_LED_4_Pin, GPIO_PIN_RESET);
					break;
			}
			break;


	}



}
