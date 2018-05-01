EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
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
LIBS:nodemcu
LIBS:enem
LIBS:EnemDoubleShutter-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR01
U 1 1 5AE0C572
P 4650 4750
F 0 "#PWR01" H 4650 4500 50  0001 C CNN
F 1 "GND" H 4650 4600 50  0000 C CNN
F 2 "" H 4650 4750 50  0001 C CNN
F 3 "" H 4650 4750 50  0001 C CNN
	1    4650 4750
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR02
U 1 1 5AE34FA2
P 4650 4850
F 0 "#PWR02" H 4650 4700 50  0001 C CNN
F 1 "+5V" H 4650 4990 50  0000 C CNN
F 2 "" H 4650 4850 50  0001 C CNN
F 3 "" H 4650 4850 50  0001 C CNN
	1    4650 4850
	-1   0    0    1   
$EndComp
NoConn ~ 4900 3450
NoConn ~ 4900 3550
NoConn ~ 4900 3650
NoConn ~ 4900 4050
NoConn ~ 4900 4150
NoConn ~ 4900 4250
NoConn ~ 4900 4550
NoConn ~ 4900 4650
NoConn ~ 5800 3450
NoConn ~ 5800 4550
NoConn ~ 5800 4650
$Comp
L PWR_FLAG #FLG03
U 1 1 5AE354EB
P 2600 2750
F 0 "#FLG03" H 2600 2825 50  0001 C CNN
F 1 "PWR_FLAG" H 2600 2900 50  0000 C CNN
F 2 "" H 2600 2750 50  0001 C CNN
F 3 "" H 2600 2750 50  0001 C CNN
	1    2600 2750
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 5AE35505
P 3050 2750
F 0 "#FLG04" H 3050 2825 50  0001 C CNN
F 1 "PWR_FLAG" H 3050 2900 50  0000 C CNN
F 2 "" H 3050 2750 50  0001 C CNN
F 3 "" H 3050 2750 50  0001 C CNN
	1    3050 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5AE3551F
P 2600 2750
F 0 "#PWR05" H 2600 2500 50  0001 C CNN
F 1 "GND" H 2600 2600 50  0000 C CNN
F 2 "" H 2600 2750 50  0001 C CNN
F 3 "" H 2600 2750 50  0001 C CNN
	1    2600 2750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 5AE35537
P 3050 2750
F 0 "#PWR06" H 3050 2600 50  0001 C CNN
F 1 "+5V" H 3050 2890 50  0000 C CNN
F 2 "" H 3050 2750 50  0001 C CNN
F 3 "" H 3050 2750 50  0001 C CNN
	1    3050 2750
	-1   0    0    1   
$EndComp
$Comp
L Alim A1
U 1 1 5AE61C3A
P 3150 3400
F 0 "A1" H 3150 3600 60  0000 C CNN
F 1 "Alim" H 3150 3400 60  0000 C CNN
F 2 "enemLib:ModuleAlim" H 3700 3950 60  0001 C CNN
F 3 "" H 3700 3950 60  0001 C CNN
	1    3150 3400
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J1
U 1 1 5AE61E8A
P 2350 3350
F 0 "J1" H 2350 3450 50  0000 C CNN
F 1 "Conn_01x02" H 2350 3150 50  0000 C CNN
F 2 "enemLib:Bornier2" H 2350 3350 50  0001 C CNN
F 3 "" H 2350 3350 50  0001 C CNN
	1    2350 3350
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5AE62183
P 3750 3450
F 0 "#PWR07" H 3750 3200 50  0001 C CNN
F 1 "GND" H 3750 3300 50  0000 C CNN
F 2 "" H 3750 3450 50  0001 C CNN
F 3 "" H 3750 3450 50  0001 C CNN
	1    3750 3450
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR08
U 1 1 5AE6219F
P 3750 3350
F 0 "#PWR08" H 3750 3200 50  0001 C CNN
F 1 "+5V" H 3750 3490 50  0000 C CNN
F 2 "" H 3750 3350 50  0001 C CNN
F 3 "" H 3750 3350 50  0001 C CNN
	1    3750 3350
	1    0    0    -1  
$EndComp
$Comp
L 2RelaysModule Relay1
U 1 1 5AE6251D
P 7050 2800
F 0 "Relay1" H 7050 3300 60  0000 C CNN
F 1 "2RelaysModule" H 7050 2800 60  0000 C CNN
F 2 "enemLib:relayModule" H 7050 3300 60  0001 C CNN
F 3 "" H 7050 3300 60  0001 C CNN
	1    7050 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5AE629DE
P 6000 2500
F 0 "#PWR09" H 6000 2250 50  0001 C CNN
F 1 "GND" H 6000 2350 50  0000 C CNN
F 2 "" H 6000 2500 50  0001 C CNN
F 3 "" H 6000 2500 50  0001 C CNN
	1    6000 2500
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR010
U 1 1 5AE62AB6
P 5950 4850
F 0 "#PWR010" H 5950 4700 50  0001 C CNN
F 1 "+3.3V" H 5950 4990 50  0000 C CNN
F 2 "" H 5950 4850 50  0001 C CNN
F 3 "" H 5950 4850 50  0001 C CNN
	1    5950 4850
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 5AE62AFA
P 3500 2750
F 0 "#PWR011" H 3500 2600 50  0001 C CNN
F 1 "+3.3V" H 3500 2890 50  0000 C CNN
F 2 "" H 3500 2750 50  0001 C CNN
F 3 "" H 3500 2750 50  0001 C CNN
	1    3500 2750
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG012
U 1 1 5AE62B41
P 3500 2750
F 0 "#FLG012" H 3500 2825 50  0001 C CNN
F 1 "PWR_FLAG" H 3500 2900 50  0000 C CNN
F 2 "" H 3500 2750 50  0001 C CNN
F 3 "" H 3500 2750 50  0001 C CNN
	1    3500 2750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR013
U 1 1 5AE62B99
P 5800 2600
F 0 "#PWR013" H 5800 2450 50  0001 C CNN
F 1 "+3.3V" H 5800 2740 50  0000 C CNN
F 2 "" H 5800 2600 50  0001 C CNN
F 3 "" H 5800 2600 50  0001 C CNN
	1    5800 2600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR014
U 1 1 5AE62BE5
P 5550 2700
F 0 "#PWR014" H 5550 2550 50  0001 C CNN
F 1 "+5V" H 5550 2840 50  0000 C CNN
F 2 "" H 5550 2700 50  0001 C CNN
F 3 "" H 5550 2700 50  0001 C CNN
	1    5550 2700
	1    0    0    -1  
$EndComp
NoConn ~ 7950 2500
NoConn ~ 7950 2600
NoConn ~ 7950 2700
NoConn ~ 7950 2900
NoConn ~ 7950 3000
NoConn ~ 7950 3100
$Comp
L Conn_01x03 J2
U 1 1 5AE62F81
P 6650 3750
F 0 "J2" H 6650 3950 50  0000 C CNN
F 1 "Bouton 1" H 6650 3550 50  0000 C CNN
F 2 "enemLib:Bornier3" H 6650 3750 50  0001 C CNN
F 3 "" H 6650 3750 50  0001 C CNN
	1    6650 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5AE6306B
P 6350 3650
F 0 "#PWR015" H 6350 3400 50  0001 C CNN
F 1 "GND" H 6350 3500 50  0000 C CNN
F 2 "" H 6350 3650 50  0001 C CNN
F 3 "" H 6350 3650 50  0001 C CNN
	1    6350 3650
	-1   0    0    1   
$EndComp
$Comp
L 2RelaysModule Relay2
U 1 1 5AE8BB79
P 8450 4050
F 0 "Relay2" H 8450 4550 60  0000 C CNN
F 1 "2RelaysModule" H 8450 4050 60  0000 C CNN
F 2 "enemLib:relayModule" H 8450 4550 60  0001 C CNN
F 3 "" H 8450 4550 60  0001 C CNN
	1    8450 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5AE8BBDB
P 7400 3750
F 0 "#PWR016" H 7400 3500 50  0001 C CNN
F 1 "GND" H 7400 3600 50  0000 C CNN
F 2 "" H 7400 3750 50  0001 C CNN
F 3 "" H 7400 3750 50  0001 C CNN
	1    7400 3750
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR017
U 1 1 5AE8BBF8
P 7200 3850
F 0 "#PWR017" H 7200 3700 50  0001 C CNN
F 1 "+3.3V" H 7200 3990 50  0000 C CNN
F 2 "" H 7200 3850 50  0001 C CNN
F 3 "" H 7200 3850 50  0001 C CNN
	1    7200 3850
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR018
U 1 1 5AE8BC15
P 7000 3950
F 0 "#PWR018" H 7000 3800 50  0001 C CNN
F 1 "+5V" H 7000 4090 50  0000 C CNN
F 2 "" H 7000 3950 50  0001 C CNN
F 3 "" H 7000 3950 50  0001 C CNN
	1    7000 3950
	1    0    0    -1  
$EndComp
NoConn ~ 9350 3750
NoConn ~ 9350 3850
NoConn ~ 9350 3950
NoConn ~ 9350 4150
NoConn ~ 9350 4250
NoConn ~ 9350 4350
$Comp
L Conn_01x03 J3
U 1 1 5AE8C308
P 4300 3850
F 0 "J3" H 4300 4050 50  0000 C CNN
F 1 "Bouton 2" H 4300 3650 50  0000 C CNN
F 2 "enemLib:Bornier3" H 4300 3850 50  0001 C CNN
F 3 "" H 4300 3850 50  0001 C CNN
	1    4300 3850
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5AE8C3D5
P 4600 3750
F 0 "#PWR019" H 4600 3500 50  0001 C CNN
F 1 "GND" H 4600 3600 50  0000 C CNN
F 2 "" H 4600 3750 50  0001 C CNN
F 3 "" H 4600 3750 50  0001 C CNN
	1    4600 3750
	1    0    0    1   
$EndComp
NoConn ~ 5800 4150
$Comp
L NodeMCU_Amica_R2 U1
U 1 1 5AE34C07
P 5350 4150
F 0 "U1" H 5350 4950 50  0000 C CNN
F 1 "NodeMCU_Amica_R2" H 5350 3300 50  0000 C CNN
F 2 "enemLib:NodeMCU_simple" H 5600 4150 50  0001 C CNN
F 3 "" H 5600 4150 50  0000 C CNN
	1    5350 4150
	1    0    0    -1  
$EndComp
NoConn ~ 4900 3950
NoConn ~ 5800 4450
$Comp
L +3.3V #PWR020
U 1 1 5AE8D74B
P 4400 4450
F 0 "#PWR020" H 4400 4300 50  0001 C CNN
F 1 "+3.3V" H 4400 4590 50  0000 C CNN
F 2 "" H 4400 4450 50  0001 C CNN
F 3 "" H 4400 4450 50  0001 C CNN
	1    4400 4450
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR021
U 1 1 5AE8D72B
P 4650 4350
F 0 "#PWR021" H 4650 4100 50  0001 C CNN
F 1 "GND" H 4650 4200 50  0000 C CNN
F 2 "" H 4650 4350 50  0001 C CNN
F 3 "" H 4650 4350 50  0001 C CNN
	1    4650 4350
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 4750 4900 4750
Wire Wire Line
	2550 3350 2650 3350
Wire Wire Line
	2550 3450 2650 3450
Wire Wire Line
	3650 3350 3750 3350
Wire Wire Line
	3750 3450 3650 3450
Wire Wire Line
	4900 4850 4650 4850
Wire Wire Line
	5800 4850 5950 4850
Wire Wire Line
	6000 2500 6150 2500
Wire Wire Line
	5800 2600 6150 2600
Wire Wire Line
	6150 2700 5550 2700
Wire Wire Line
	6350 3650 6450 3650
Wire Wire Line
	7400 3750 7550 3750
Wire Wire Line
	7200 3850 7550 3850
Wire Wire Line
	7000 3950 7550 3950
Wire Wire Line
	5900 3000 5900 3550
Wire Wire Line
	5900 3550 5800 3550
Wire Wire Line
	6000 3100 6000 3650
Wire Wire Line
	6000 3650 5800 3650
Wire Wire Line
	7550 4250 5800 4250
Wire Wire Line
	5800 4350 7550 4350
Wire Wire Line
	4600 3750 4500 3750
Wire Wire Line
	4500 3850 4900 3850
Wire Wire Line
	4500 3950 4750 3950
Wire Wire Line
	4750 3950 4750 3750
Wire Wire Line
	4750 3750 4900 3750
Wire Wire Line
	4900 4350 4650 4350
Wire Wire Line
	4900 4450 4400 4450
$Comp
L GND #PWR022
U 1 1 5AE8D865
P 5900 4100
F 0 "#PWR022" H 5900 3850 50  0001 C CNN
F 1 "GND" H 5900 3950 50  0000 C CNN
F 2 "" H 5900 4100 50  0001 C CNN
F 3 "" H 5900 4100 50  0001 C CNN
	1    5900 4100
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR023
U 1 1 5AE8D885
P 6250 3950
F 0 "#PWR023" H 6250 3800 50  0001 C CNN
F 1 "+3.3V" H 6250 4090 50  0000 C CNN
F 2 "" H 6250 3950 50  0001 C CNN
F 3 "" H 6250 3950 50  0001 C CNN
	1    6250 3950
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR024
U 1 1 5AE8D8A5
P 6000 4750
F 0 "#PWR024" H 6000 4500 50  0001 C CNN
F 1 "GND" H 6000 4600 50  0000 C CNN
F 2 "" H 6000 4750 50  0001 C CNN
F 3 "" H 6000 4750 50  0001 C CNN
	1    6000 4750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 4050 5900 4050
Wire Wire Line
	5900 4050 5900 4100
Wire Wire Line
	5800 3950 6250 3950
Wire Wire Line
	5800 4750 6000 4750
Wire Wire Line
	5800 3850 6450 3850
Wire Wire Line
	6450 3750 5800 3750
Wire Wire Line
	6000 3100 6150 3100
Wire Wire Line
	5900 3000 6150 3000
NoConn ~ 6150 3200
NoConn ~ 6150 3300
NoConn ~ 7550 4450
NoConn ~ 7550 4550
$EndSCHEMATC
