EESchema Schematic File Version 2  date Сбт 23 Мар 2013 00:37:49
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
LIBS:stm32f102r
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "22 mar 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 7550 3600 0    60   ~ 0
usb_dsc
Text Label 1900 5250 2    60   ~ 0
usb_dsc
$Comp
L R R?
U 1 1 514CBEFF
P 2150 5250
F 0 "R?" V 2230 5250 50  0000 C CNN
F 1 "1k" V 2150 5250 50  0000 C CNN
	1    2150 5250
	0    -1   -1   0   
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CBEE1
P 2400 4750
F 0 "#PWR?" H 2400 4850 40  0001 C CNN
F 1 "3V3" H 2400 4875 40  0000 C CNN
	1    2400 4750
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 514CBED3
P 2400 5000
F 0 "R?" V 2480 5000 50  0000 C CNN
F 1 "47k" V 2400 5000 50  0000 C CNN
	1    2400 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5550 2900 5550
Wire Wire Line
	2700 5550 2700 5450
Wire Wire Line
	2900 5550 2900 5650
Wire Wire Line
	5750 4350 5750 4600
Wire Wire Line
	5750 4350 4500 4350
Wire Wire Line
	5400 2400 5500 2400
Wire Wire Line
	5500 2400 5500 3000
Wire Wire Line
	5500 3000 5950 3000
Wire Wire Line
	5400 2100 5600 2100
Wire Wire Line
	5600 2100 5600 2700
Wire Wire Line
	5600 2700 5950 2700
Wire Wire Line
	5400 1800 5400 1600
Wire Wire Line
	5400 1600 4600 1600
Wire Wire Line
	4600 1600 4600 1800
Connection ~ 4600 2600
Connection ~ 4600 2400
Connection ~ 4600 2200
Connection ~ 4600 2000
Wire Wire Line
	7550 3300 8900 3300
Connection ~ 8150 3800
Wire Wire Line
	7550 3500 7900 3500
Wire Wire Line
	7900 3500 7900 3800
Wire Wire Line
	7900 3800 8450 3800
Connection ~ 8150 3400
Connection ~ 8750 3200
Wire Wire Line
	7550 3200 9200 3200
Wire Wire Line
	9200 3200 9200 2900
Wire Wire Line
	8850 2500 8750 2500
Wire Wire Line
	8250 2500 8150 2500
Wire Wire Line
	7550 2800 7700 2800
Wire Wire Line
	7700 2800 7700 2300
Wire Wire Line
	8750 2500 8750 2300
Wire Wire Line
	7550 2600 7600 2600
Wire Wire Line
	7600 2600 7600 2400
Wire Wire Line
	7600 2400 8150 2400
Wire Wire Line
	8150 2400 8150 2500
Wire Wire Line
	7550 3100 8450 3100
Wire Wire Line
	8450 3100 8450 2900
Wire Wire Line
	7850 2900 7550 2900
Wire Wire Line
	5800 2500 5950 2500
Wire Wire Line
	5650 3300 5650 3650
Wire Wire Line
	5650 3300 5950 3300
Wire Wire Line
	4750 3050 4750 3800
Connection ~ 4750 3650
Wire Wire Line
	5950 3200 5650 3200
Wire Wire Line
	5650 3200 5650 3050
Wire Wire Line
	5650 3050 5150 3050
Wire Wire Line
	5650 3650 5150 3650
Wire Wire Line
	8150 2900 8150 3000
Wire Wire Line
	8150 3000 7550 3000
Wire Wire Line
	8750 2900 8750 3200
Wire Wire Line
	8450 2350 8450 2500
Wire Wire Line
	8450 2350 7650 2350
Wire Wire Line
	7650 2350 7650 2700
Wire Wire Line
	7650 2700 7550 2700
Wire Wire Line
	7550 2500 7950 2500
Connection ~ 7850 2500
Wire Wire Line
	8450 2500 8550 2500
Wire Wire Line
	9200 2500 9200 2300
Wire Wire Line
	9200 2300 7700 2300
Connection ~ 8750 2300
Wire Wire Line
	7550 3400 8550 3400
Connection ~ 8450 3400
Connection ~ 4600 2100
Connection ~ 4600 2300
Connection ~ 4600 2500
Wire Wire Line
	4600 1900 4600 2800
Connection ~ 4600 2700
Wire Wire Line
	5950 2600 5650 2600
Wire Wire Line
	5650 2600 5650 2000
Wire Wire Line
	5650 2000 5400 2000
Wire Wire Line
	5950 2800 5550 2800
Wire Wire Line
	5550 2800 5550 2200
Wire Wire Line
	5550 2200 5400 2200
Wire Wire Line
	5400 1900 5700 1900
Wire Wire Line
	5700 1900 5700 3100
Wire Wire Line
	5700 3100 5950 3100
Wire Wire Line
	5750 4600 5950 4600
Wire Wire Line
	4500 4500 5950 4500
Wire Wire Line
	3750 5750 4600 5750
Wire Wire Line
	4600 5750 4600 4350
Connection ~ 4600 4350
Wire Wire Line
	3100 4500 3250 4500
Wire Wire Line
	3250 4350 2900 4350
Wire Wire Line
	2900 4350 2900 4550
Wire Wire Line
	2700 5050 3450 5050
Connection ~ 2900 5050
$Comp
L BC817-40 Q?
U 1 1 514CBEB5
P 2600 5250
F 0 "Q?" H 2600 5101 40  0000 R CNN
F 1 "BC817-40" H 2600 5400 40  0000 R CNN
F 2 "SOT-23" H 2400 5352 29  0000 C CNN
	1    2600 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 514CBE96
P 2900 5650
F 0 "#PWR?" H 2900 5650 30  0001 C CNN
F 1 "GND" H 2900 5580 30  0001 C CNN
	1    2900 5650
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 514CBE6A
P 2900 5300
F 0 "R?" V 2980 5300 50  0000 C CNN
F 1 "36k" V 2900 5300 50  0000 C CNN
	1    2900 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 514CBDED
P 3100 4500
F 0 "#PWR?" H 3100 4500 30  0001 C CNN
F 1 "GND" H 3100 4430 30  0001 C CNN
	1    3100 4500
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 514CBD9D
P 2900 4800
F 0 "R?" V 2980 4800 50  0000 C CNN
F 1 "10k" V 2900 4800 50  0000 C CNN
	1    2900 4800
	-1   0    0    1   
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CBD5D
P 3750 4850
F 0 "#PWR?" H 3750 4950 40  0001 C CNN
F 1 "3V3" H 3750 4975 40  0000 C CNN
	1    3750 4850
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 514CBD51
P 3750 5500
F 0 "R?" V 3830 5500 50  0000 C CNN
F 1 "1.5k" V 3750 5500 50  0000 C CNN
	1    3750 5500
	1    0    0    -1  
$EndComp
$Comp
L BC817-40 Q?
U 1 1 514CBD3D
P 3650 5050
F 0 "Q?" H 3650 4901 40  0000 R CNN
F 1 "BC817-40" H 3650 5200 40  0000 R CNN
F 2 "SOT-23" H 3450 5152 29  0000 C CNN
	1    3650 5050
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 514CB729
P 4250 4350
F 0 "R?" V 4330 4350 50  0000 C CNN
F 1 "22" V 4250 4350 50  0000 C CNN
	1    4250 4350
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 514CB716
P 4250 4500
F 0 "R?" V 4330 4500 50  0000 C CNN
F 1 "22" V 4250 4500 50  0000 C CNN
	1    4250 4500
	0    -1   -1   0   
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CB419
P 5400 1800
F 0 "#PWR?" H 5400 1900 40  0001 C CNN
F 1 "3V3" H 5400 1925 40  0000 C CNN
	1    5400 1800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 514CB3B3
P 4600 2800
F 0 "#PWR?" H 4600 2800 30  0001 C CNN
F 1 "GND" H 4600 2730 30  0001 C CNN
	1    4600 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_10X2 P?
U 1 1 514CB362
P 5000 2250
F 0 "P?" H 5000 2800 60  0000 C CNN
F 1 "JATG" V 5000 2150 50  0000 C CNN
	1    5000 2250
	-1   0    0    -1  
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CB245
P 8900 3300
F 0 "#PWR?" H 8900 3400 40  0001 C CNN
F 1 "3V3" H 8900 3425 40  0000 C CNN
	1    8900 3300
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 514CB232
P 8900 3700
F 0 "#PWR?" H 8900 3700 30  0001 C CNN
F 1 "GND" H 8900 3630 30  0001 C CNN
	1    8900 3700
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 514CB225
P 8900 3500
F 0 "C?" H 8950 3600 50  0000 L CNN
F 1 "100n" H 8950 3400 50  0000 L CNN
	1    8900 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 514CB177
P 8550 3400
F 0 "#PWR?" H 8550 3400 30  0001 C CNN
F 1 "GND" H 8550 3330 30  0001 C CNN
	1    8550 3400
	0    -1   -1   0   
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CB16A
P 8450 3800
F 0 "#PWR?" H 8450 3900 40  0001 C CNN
F 1 "3V3" H 8450 3925 40  0000 C CNN
	1    8450 3800
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 514CB144
P 8450 3600
F 0 "C?" H 8500 3700 50  0000 L CNN
F 1 "1u" H 8500 3500 50  0000 L CNN
	1    8450 3600
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 514CB13D
P 8150 3600
F 0 "C?" H 8200 3700 50  0000 L CNN
F 1 "100n" H 8200 3500 50  0000 L CNN
	1    8150 3600
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 514CB119
P 9200 2700
F 0 "C?" H 9250 2800 50  0000 L CNN
F 1 "4.7u" H 9250 2600 50  0000 L CNN
	1    9200 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 514CB0A3
P 8850 2500
F 0 "#PWR?" H 8850 2500 30  0001 C CNN
F 1 "GND" H 8850 2430 30  0001 C CNN
	1    8850 2500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 514CB095
P 8550 2500
F 0 "#PWR?" H 8550 2500 30  0001 C CNN
F 1 "GND" H 8550 2430 30  0001 C CNN
	1    8550 2500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 514CB08E
P 8250 2500
F 0 "#PWR?" H 8250 2500 30  0001 C CNN
F 1 "GND" H 8250 2430 30  0001 C CNN
	1    8250 2500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 514CB087
P 7950 2500
F 0 "#PWR?" H 7950 2500 30  0001 C CNN
F 1 "GND" H 7950 2430 30  0001 C CNN
	1    7950 2500
	0    -1   -1   0   
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CB07E
P 8750 2900
F 0 "#PWR?" H 8750 3000 40  0001 C CNN
F 1 "3V3" H 8750 3025 40  0000 C CNN
	1    8750 2900
	0    1    1    0   
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CB078
P 8450 2900
F 0 "#PWR?" H 8450 3000 40  0001 C CNN
F 1 "3V3" H 8450 3025 40  0000 C CNN
	1    8450 2900
	0    1    1    0   
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CB070
P 8150 2900
F 0 "#PWR?" H 8150 3000 40  0001 C CNN
F 1 "3V3" H 8150 3025 40  0000 C CNN
	1    8150 2900
	0    1    1    0   
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 514CB055
P 7850 2900
F 0 "#PWR?" H 7850 3000 40  0001 C CNN
F 1 "3V3" H 7850 3025 40  0000 C CNN
	1    7850 2900
	0    1    -1   0   
$EndComp
$Comp
L C C?
U 1 1 514CAFC0
P 8750 2700
F 0 "C?" H 8800 2800 50  0000 L CNN
F 1 "100n" H 8800 2600 50  0000 L CNN
	1    8750 2700
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 514CAFB9
P 8450 2700
F 0 "C?" H 8500 2800 50  0000 L CNN
F 1 "100n" H 8500 2600 50  0000 L CNN
	1    8450 2700
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 514CAFB6
P 8150 2700
F 0 "C?" H 8200 2800 50  0000 L CNN
F 1 "100n" H 8200 2600 50  0000 L CNN
	1    8150 2700
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 514CAFB1
P 7850 2700
F 0 "C?" H 7900 2800 50  0000 L CNN
F 1 "100n" H 7900 2600 50  0000 L CNN
	1    7850 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 514CAD39
P 5800 2500
F 0 "#PWR?" H 5800 2500 30  0001 C CNN
F 1 "GND" H 5800 2430 30  0001 C CNN
	1    5800 2500
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 514CACA4
P 4750 3800
F 0 "#PWR?" H 4750 3800 30  0001 C CNN
F 1 "GND" H 4750 3730 30  0001 C CNN
	1    4750 3800
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 514CAC8F
P 4950 3650
F 0 "C?" H 5000 3750 50  0000 L CNN
F 1 "18p" H 5000 3550 50  0000 L CNN
	1    4950 3650
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 514CAC87
P 4950 3050
F 0 "C?" H 5000 3150 50  0000 L CNN
F 1 "18p" H 5000 2950 50  0000 L CNN
	1    4950 3050
	0    -1   -1   0   
$EndComp
$Comp
L USB J?
U 1 1 514CA98E
P 3650 4150
F 0 "J?" H 3600 4550 60  0000 C CNN
F 1 "USB" V 3400 4300 60  0000 C CNN
	1    3650 4150
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X?
U 1 1 514CA983
P 5150 3350
F 0 "X?" H 5150 3500 60  0000 C CNN
F 1 "8MHz" H 5150 3200 60  0000 C CNN
	1    5150 3350
	0    -1   -1   0   
$EndComp
$Comp
L STM32F102R D?
U 1 1 514CA8C9
P 6800 4050
F 0 "D?" H 6350 2200 60  0000 C CNN
F 1 "STM32F102R" H 6600 2300 60  0000 C CNN
	1    6800 4050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
