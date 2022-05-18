/**
  ******************************************************************************
  * @file           : dht11.h
  * @brief          : Header for dht11.c file.
  *                   This file contains the definition of the one-wire communication
  *                   of DHT11.
  *
  *                   Created on:	May 16th, 2022
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __DHT11_H
#define __DHT11_H

#define DATA_PORT	GPIOA
#define DATA_PIN	GPIO_PIN_5

typedef struct {
	uint8_t humidity_integral;
	uint8_t humidity_decimal;
	uint8_t temperature_integral;
	uint8_t temperature_decimal;
	uint8_t checksum;
} dht11_data_t;

void dht11_init(TIM_HandleTypeDef *htim_para, UART_HandleTypeDef *huart);
uint8_t get_env_data(void);
float get_humidity(void);
float get_temperature(void);

#endif /* __DHT11_H */
