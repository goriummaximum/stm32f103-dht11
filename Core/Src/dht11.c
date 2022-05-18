/**
  ******************************************************************************
  * @file           : dht11.c
  * @brief          :
  *                   This file contains the implementation of the one-wire communication
  *                   of DHT11.
  *
  *                   Created on:	May 16th, 2022
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "dht11.h"

static dht11_data_t data_buffer;
static dht11_data_t data_tmp;
static uint64_t bit_buffer = 0;
static uint8_t bit_counter = 0;

/*DEBUGGER*/
static UART_HandleTypeDef *huart;
static char uart_buf[100];
static uint8_t uart_buf_len = 0;

static TIM_HandleTypeDef *htim;
static uint16_t start_tick;

void dht11_init(TIM_HandleTypeDef *htim_para, UART_HandleTypeDef *huart_para) {
	htim = htim_para;
	huart = huart_para;
}

static void delay_us(uint16_t wait) {
	__HAL_TIM_SET_COUNTER(htim, 0);
	start_tick = __HAL_TIM_GET_COUNTER(htim);
	while (__HAL_TIM_GET_COUNTER(htim) - start_tick < wait) {};
}

static void set_data_pin_input(void) {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = DATA_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(DATA_PORT, &GPIO_InitStruct);
}

static void set_data_pin_output(void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DATA_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DATA_PORT, &GPIO_InitStruct);
}

static void pull_down_data_pin(void) {
	HAL_GPIO_WritePin(DATA_PORT, DATA_PIN, GPIO_PIN_RESET);
}

static void pull_up_data_pin(void) {
	HAL_GPIO_WritePin(DATA_PORT, DATA_PIN, GPIO_PIN_SET);
}

static GPIO_PinState read_data_pin(void) {
	return HAL_GPIO_ReadPin(DATA_PORT, DATA_PIN);
}

static void extract_data(void) {
	data_tmp.humidity_integral = (bit_buffer >> 32) & 0xFF;
	data_tmp.humidity_decimal = (bit_buffer >> 24) & 0xFF;
	data_tmp.temperature_integral = (bit_buffer >> 16) & 0xFF;
	data_tmp.temperature_decimal = (bit_buffer >> 8) & 0xFF;
	data_tmp.checksum = bit_buffer & 0xFF;
}

static uint8_t is_data_error(void) {
	return (data_tmp.humidity_integral
			+ data_tmp.humidity_decimal
			+ data_tmp.temperature_integral
			+ data_tmp.temperature_decimal) != data_tmp.checksum;
}

static void reset(void) {
	bit_buffer = 0;
	bit_counter = 0;
}

static uint8_t send_start(void) {
	//pull down data pin for 18ms
	set_data_pin_output();
	pull_down_data_pin();
	delay_us(20000);
	//pull up data pin for 30us, and wait for 40us to check resp from DHT11
	pull_up_data_pin();
	set_data_pin_input();
	delay_us(30 + 40);
	//check resp
	if (read_data_pin() == GPIO_PIN_RESET) {
		//delay for 80us to check for pullup data pin of DHT11
		delay_us(80);
		if (read_data_pin() == GPIO_PIN_SET) {
			return 1;
		}
	}

	return 0;
}

static void read_data(void) {
	while (bit_counter < 40) {
		//wait for next bit
		while (read_data_pin() != GPIO_PIN_RESET) {};
		while (read_data_pin() != GPIO_PIN_SET) {};
		//delay 40us to check the different point between bit 0 and 1
		delay_us(40);
		//if data pin still set -> bit 1
		if (read_data_pin() == GPIO_PIN_SET) {
			bit_buffer = (bit_buffer << 1) | 1;
		}
		//data pin is unset after 40us -> bit 0
		else {
			bit_buffer = bit_buffer << 1;
		}

		bit_counter++;
	}
}

uint8_t get_env_data(void) {
	reset();
	if (send_start()) {
		read_data();
		extract_data();
		if (!is_data_error()) {
			data_buffer = data_tmp;
			return 1;
		}
	}

	return 0;
}

float get_humidity(void) {
	return (float)data_buffer.humidity_integral + (float)data_buffer.humidity_decimal / 10;
}

float get_temperature(void) {
	return (float)data_buffer.temperature_integral + (float)data_buffer.temperature_decimal / 10;
}

