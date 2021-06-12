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

#define threshold 2000

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
        }else if(input == 65 || input == 97){
			freq1 = 1633;
			freq2 = 697;
        // B, b
        }else if(input == 66 || input == 98){
			freq1 = 1633;
			freq2 = 770;
        // C, c
        }else if(input == 67 || input == 99){
			freq1 = 1633;
			freq2 = 852;
        // D, d
        }else if(input == 68 || input == 100){
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

		/*gtz_out[0]= 697Hz
		gtz_out[1]= 770Hz
		gtz_out[2]= 852Hz
		gtz_out[3]= 941Hz
		gtz_out[4]= 1209Hz
		gtz_out[5]= 1336Hz
		gtz_out[6]= 1477Hz
		gtz_out[7]= 1633Hz
		*/




		 if(gtz_out[0] != 0 && gtz_out[4] != 0){
			System_printf("\n The Button is 1");
			System_flush();
		}else if(gtz_out[0] != 0 && gtz_out[5] != 0){
			System_printf("\n The Button is 2");
			System_flush();
		}else if(gtz_out[0] != 0 && gtz_out[6] != 0){
			System_printf("\n The Button is 3");
			System_flush();
		}else if(gtz_out[0] != 0 && gtz_out[7] != 0){
			System_printf("\n The Button is A");
			System_flush();
		}else if(gtz_out[1] != 0 && gtz_out[4] != 0){
			System_printf("\n The Button is 4");
			System_flush();
		}else if(gtz_out[1] != 0 && gtz_out[5] != 0){
			System_printf("\n The Button is 5");
			System_flush();
		}else if(gtz_out[1] != 0 && gtz_out[6] != 0){
			System_printf("\n The Button is 6");
			System_flush();
		}else if(gtz_out[1] != 0 && gtz_out[7] != 0){
			System_printf("\n The Button is B");
			System_flush();
		}else if(gtz_out[2] != 0 && gtz_out[4] != 0){
			System_printf("\n The Button is 7");
			System_flush();
		}else if(gtz_out[2] != 0 && gtz_out[5] != 0){
			System_printf("\n The Button is 8");
			System_flush();
        }else if(gtz_out[2] != 0 && gtz_out[6] != 0){
			System_printf("\n The Button is 9");
			System_flush();
        }else if(gtz_out[2] != 0 && gtz_out[7] != 0){
			System_printf("\n The Button is C");
			System_flush();
        }else if(gtz_out[3] != 0 && gtz_out[4]!= 0){
			System_printf("\n The Button is *");
			System_flush();
        }else if(gtz_out[3] != 0 && gtz_out[5]!= 0){
			System_printf("\n The Button is 0");
			System_flush();
        }else if(gtz_out[3] != 0 && gtz_out[6]!= 0){
			System_printf("\n The Button is #");
			System_flush();
        }else if(gtz_out[3] != 0 && gtz_out[7] != 0){
			System_printf("\n The Button is D");
			System_flush();
		}
        else {
			System_printf("The wrong Button has been pressed");
			System_flush();
		}
            



    a1=0, a2=0, f1=0, f2=0;

    
	}
}

