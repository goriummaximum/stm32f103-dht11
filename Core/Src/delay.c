/**
  ******************************************************************************
  * @file           : delay.c
  * @brief          :
  *                   This file contains the implementation of the delay
  *
  *                   Created on:	May 17th, 2022
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "delay.h"

static TIM_HandleTypeDef *htim;
static uint16_t start_tick;

void delay_init(TIM_HandleTypeDef *htim_para) {
	htim = htim_para;
}

void delay_us(uint16_t wait) {
	__HAL_TIM_SET_COUNTER(htim, 0);
	start_tick = __HAL_TIM_GET_COUNTER(htim);
	while (__HAL_TIM_GET_COUNTER(htim) - start_tick < wait) {};
}
