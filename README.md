# An implementation of communication between STM32F103C8T6 and DHT11 on STM32 side.

## What?
An implementation of communication between STM32F103C8T6 and DHT11 on STM32 side to request and read humidity and temperature values from DHT11 then output to the screen via UART. By setting a timer to us, the MCU is able to sample signal sent by DHT11.

## When?
Semester HK212, 2021-2022; In my free time.

## Where?
My house.

## Why?
To practice STM32 MCU programming, manipulate timer. 
To update my CV, i know, LOL.

## How?
C programming with STM32CUBEMX, using HAL framework, upload code to real hardware using STMFlashDemostrator via UART, debug via UART.

## How to run?
You can use STM32CUBEMXIDE, choose STM32F10C8 and refer to the code here.

## Result
Schematic  
<img src="https://github.com/goriummaximum/stm32f103-dht11/blob/main/images/schematic.png" height="500">  
Real circuit  
<img src="https://github.com/goriummaximum/stm32f103-dht11/blob/main/images/real_circuit.jpg" height="500">  
UART output to the screen  
<img src="https://github.com/goriummaximum/stm32f103-dht11/blob/main/images/print.PNG" height="500">  

## File system
`Core` Folder contains my code for `dht11.h`, `dht11.c`, `main.c`. 

## Others
To understand more about the communication process, please visit: https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf
