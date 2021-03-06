EESchema Schematic File Version 2  date Чтв 21 Ноя 2013 00:30:28
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ds1624
LIBS:sensor-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "20 nov 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5500 3000 5500 3100
Wire Wire Line
	4450 1500 4450 1600
Wire Wire Line
	3450 2050 3800 2050
Wire Wire Line
	3450 2350 3800 2350
Connection ~ 5500 1500
Connection ~ 5500 2250
Wire Wire Line
	4850 2250 5500 2250
Wire Wire Line
	5150 2000 5150 2400
Connection ~ 5850 2350
Wire Wire Line
	5850 2000 5850 2400
Wire Wire Line
	5850 2350 4850 2350
Wire Wire Line
	5500 2000 5500 2400
Wire Wire Line
	4850 2150 5150 2150
Connection ~ 5150 2150
Wire Wire Line
	4850 1500 5850 1500
Connection ~ 5150 1500
Wire Wire Line
	4850 1400 4850 2050
Connection ~ 4850 1500
Wire Wire Line
	3450 2150 3800 2150
Wire Wire Line
	3450 1850 3450 1950
Wire Wire Line
	3450 2450 3450 2250
Connection ~ 3450 2350
Wire Wire Line
	5850 3000 5150 3000
Connection ~ 5500 3000
$Comp
L GND #PWR01
U 1 1 528B3DA1
P 5500 3100
F 0 "#PWR01" H 5500 3100 30  0001 C CNN
F 1 "GND" H 5500 3030 30  0001 C CNN
	1    5500 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 528B3D95
P 3450 2450
F 0 "#PWR02" H 3450 2450 30  0001 C CNN
F 1 "GND" H 3450 2380 30  0001 C CNN
	1    3450 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 528B3D8B
P 4450 1600
F 0 "#PWR03" H 4450 1600 30  0001 C CNN
F 1 "GND" H 4450 1530 30  0001 C CNN
	1    4450 1600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 528B3D79
P 3450 1850
F 0 "#PWR04" H 3450 1940 20  0001 C CNN
F 1 "+5V" H 3450 1940 30  0000 C CNN
	1    3450 1850
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P1
U 1 1 528B3D5B
P 3100 2100
F 0 "P1" V 3050 2100 50  0000 C CNN
F 1 "CONN_4" V 3150 2100 50  0000 C CNN
	1    3100 2100
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 528B3D32
P 4850 1400
F 0 "#PWR05" H 4850 1490 20  0001 C CNN
F 1 "+5V" H 4850 1490 30  0000 C CNN
	1    4850 1400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 528B3D2B
P 4850 1400
F 0 "#PWR06" H 4850 1490 20  0001 C CNN
F 1 "+5V" H 4850 1490 30  0000 C CNN
	1    4850 1400
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 528B3D16
P 4650 1500
F 0 "C1" H 4700 1600 50  0000 L CNN
F 1 "C" H 4700 1400 50  0000 L CNN
	1    4650 1500
	0    -1   -1   0   
$EndComp
$Comp
L JUMPER JP3
U 1 1 528B3CD9
P 5850 2700
F 0 "JP3" H 5850 2850 60  0000 C CNN
F 1 "JUMPER" H 5850 2620 40  0000 C CNN
	1    5850 2700
	0    -1   -1   0   
$EndComp
$Comp
L JUMPER JP2
U 1 1 528B3CD5
P 5500 2700
F 0 "JP2" H 5500 2850 60  0000 C CNN
F 1 "JUMPER" H 5500 2620 40  0000 C CNN
	1    5500 2700
	0    -1   -1   0   
$EndComp
$Comp
L JUMPER JP1
U 1 1 528B3CC8
P 5150 2700
F 0 "JP1" H 5150 2850 60  0000 C CNN
F 1 "JUMPER" H 5150 2620 40  0000 C CNN
	1    5150 2700
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 528B3C94
P 5850 1750
F 0 "R3" V 5930 1750 50  0000 C CNN
F 1 "R" V 5850 1750 50  0000 C CNN
	1    5850 1750
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 528B3C90
P 5500 1750
F 0 "R2" V 5580 1750 50  0000 C CNN
F 1 "R" V 5500 1750 50  0000 C CNN
	1    5500 1750
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 528B3C86
P 5150 1750
F 0 "R1" V 5230 1750 50  0000 C CNN
F 1 "R" V 5150 1750 50  0000 C CNN
	1    5150 1750
	1    0    0    -1  
$EndComp
$Comp
L DS1624 D1
U 1 1 528B3C60
P 4350 2200
F 0 "D1" H 4350 2450 60  0000 C CNN
F 1 "DS1624" H 4350 1900 60  0000 C CNN
	1    4350 2200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
