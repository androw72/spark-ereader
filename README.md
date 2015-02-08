# spark-ereader
Wyolums ereader code run on a spark core. A 'wif' file is read from the sd-card and displayed on the epaper display. Instruction on how to setup the EPD can be found [here](https://github.com/androw72/setup_instruction_spark_ereader)    

Hardware:  
Repaper display development board and a adafruit sd-card breakout board is used together with the spark-core. Note! this code only support the COG V1 EPD.

Ereader library and sd card info on http://wyolum.com/wyolum-ereader-library/  
SD card library: https://github.com/mumblepins/sd-card-library based on https://github.com/technobly/SparkCore-SD

Pin Number	Description	Color

1.	Vcc 3V	Red	3.3V*
2.	(LED1)	White	-	-	-
3.	(UART_RX)	Grey	-	-	-
4.	(UART_TX)	Purple	-	-	-
5.	(SW2)	Blue	-	-	-
6.	Temperature	Green	A0
7.	SPI_CLK	Yellow	A3
8.	BUSY	Orange	D7
9.	PWM	Brown	A7
10.	/RESET	Black	D6
11.	PANEL_ON	Red	D2
12.	DISCHARGE	White	D4
13.	BORDER_CONTROL	Grey	D3
14.	SPI_MISO	Purple	A4
15.	SPI_MOSI	Blue	A5
16.	(RST/SBWTDIO)	Green	-	-	-
17.	(TEST/SBWTCK)	Yellow	-	-	-
18.	FLASH_CS	Orange	D1
19.	/EPD_CS	Brown	D0
20.	GND	Black	GND


Sd card brakeout board:

CS Chip Select A2   
DI: MOSI A5  
DI: MISO A4  
CLK:SCK A3  
GND GND  
VCC (3.3v) 3V3  












