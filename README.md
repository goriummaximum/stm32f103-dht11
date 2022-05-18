# An implementation of communication between STM32F103C8T6 and DHT11 on STM32 side.

## What?
An implementation of communication between STM32F103C8T6 and DHT11 on STM32 side to request and read humidity and temperature values from DHT11. By setting a timer to us, the MCU is able to sample signal sent by DHT11.

## When?
Semester HK212, 2021-2022; In my free time.

## Where?
My house.

## Why?
To practice STM32 MCU programming, manipulate timer. 
To update my CV, i know, LOL.

## How?
C programming with STM32CUBEMX, using HAL framework, upload code to real hardware.

## File system
`Core` Folder contains my code for `dht11.h`, `dht11.c`, `main.c`. 
