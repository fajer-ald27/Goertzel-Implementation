/*
 *  ======== util.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "gtz.h"

#define threshold 1000

UInt32 time1, time2;

char digit;

int freq1, freq2;
int mag1, mag2;

int sample, gtz_out[8];

short coef[8] = {0x6D02, 0x68AD, 0x63FC, 0x5EE7, 0x4A70, 0x4090, 0x3290, 0x23CE}; // goertzel coefficients



void task1_dtmfDetect(void)
{
	int i, a1=0, a2=0, f1=0, f2=0, dig;
	int input;

	while (1) {
		
		



		/*	 1. write a code that keep reading the value of "digit" from the keyboard and set the magnitude for mag1 = mag2= 32768.0 and the frequencies freq1 and freq2 according the digit value as:
			 in case when the wrong digit is entered, set: the mag1 = 00000.0, mag2 = 00000.0, freq1 = 000 and freq2 = 0000




						 '0' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1335
						 '1' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1209,
						 '2' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1335,
						 '3' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1477,
						 '4' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1209,
						 '5' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1335,
						 '6' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1477,
						 '7' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1209,
						 '8' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1335,
						 '9' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1477,
						 '*' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1209,
						 '#' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1477,
						 'A' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1633,
						 'B' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1633,
						 'C' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1633,
						 'D' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1633,
						otherwise : mag1 = 00000.0, mag2 = 00000.0, freq1 = 000, freq2 = 0000  */


		Task_sleep(500);

		// 2. Read the GTZ for each frequency and take a decision on which key has been pressed and print it.

		System_printf("\n Please press a key ( 0 to 9 or A, B, C, D or *, # ) \n");
		System_flush();
		scanf(" %c", &input);

        mag1 = 32768.0, mag2 = 32768.0

		if(input == 48){
			freq1 = 941; 
			freq2 = 1335;
		}else if(input == 49){
			freq1 = 697;
			freq2 = 1209;
		}else if(input == 50){
			freq1 = 697;
			freq2 = 1335;
		}else if(input == 51){
			freq1 = 697;
			freq2 = 1477;
		}else if(input == 52){
			freq1 = 770;
			freq2 = 1209;
		}else if(input == 53){
			freq1 = 770;
			freq2 = 1335;
		}else if(input == 54){
			freq1 = 770;
			freq2 = 1477;
		}else if(input == 55){
			freq1 = 852;
			freq2 = 1209;
		}else if(input == 56){
			freq1 = 852;
			freq2 = 1335;
		}else if(input == 57){
			freq1 = 852;
			freq2 = 1477;
        // A, a
        }else if(input == 65 or input == 97){
			freq1 = 1633;
			freq2 = 697;
        // B, b
        }else if(input == 66 or input == 98){
			freq1 = 1633;
			freq2 = 770;
        // C, c
        }else if(input == 67 or input == 99){
			freq1 = 1633;
			freq2 = 852;
        // D, d
        }else if(input == 68 or input == 100){
			freq1 = 1633;
			freq2 = 941;
        // * 
        }else if(input == 42){
			freq1 = 1209;
			freq2 = 941;
        // #
        }else if(input == 35){
			freq1 = 1477;
			freq2 = 941;
		}
        else {
            mag1 = 00000.0, mag2 = 00000.0, freq1 = 000, freq2 = 0000
        }
        
        
    Task_sleep(500);
    a1=0, a2=0, f1=0, f2=0;
