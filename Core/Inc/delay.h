/**
  ******************************************************************************
  * @file           : delay.h
  * @brief          : Header for delay.c file.
  *                   This file contains the definition of delay
  *
  *                   Created on:	May 17th, 2022
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __DELAY_H
#define __DELAY_H

void delay_init(TIM_HandleTypeDef *htim_para);
void delay_us(uint16_t wait);

#endif /* __DELAY_H */
