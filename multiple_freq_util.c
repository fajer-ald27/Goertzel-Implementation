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
		
		System_printf("\n Please press a key ( 0 to 9 or A, B, C, D or *, # ) \n");
		System_flush();
		scanf(" %c", &input);

        mag1 = 32768.0, mag2 = 32768.0;
        
        
        switch (input) {
            
                // 0
            case 8398128:
                freq1 = 941;
                freq2 = 1335;
                break;
                
                // 1
                
            
            case 8398129:
                freq1 = 697;
                freq2 = 1209;
                break;
                
                //2
           
            case 8398130:
                freq1 = 697;
                freq2 = 1335;
                break;
                
                //3
            
            case 8398131:
                freq1 = 697;
                freq2 = 1477;
                break;
                
                //4
            
            case 8398132:
                freq1 = 770;
                freq2 = 1209;
                break;
                
                //5
            
            case 8398133:
                freq1 = 770;
                freq2 = 1335;
                break;
                
                //6
                
            case 8398134:
                freq1 = 770;
                freq2 = 1477;
                break;
                
                //7
            
            case 8398135:
                freq1 = 852;
                freq2 = 1209;
                break;
                
                //8
                
            case 8398136:
                freq1 = 852;
                freq2 = 1335;
                break;
                
                //9
            
            case 8398137:
                freq1 = 852;
                freq2 = 1477;
                break;
                
                
            //A
            
            case 8398145:
                freq1 = 1633;
                freq2 = 697;
                break;
                
            //a
            case 8398177:
                freq1 = 1633;
                freq2 = 697;
                break;
                
            //B
            case 8398146:
                freq1 = 1633;
                freq2 = 770;
                break;
            //b
            case 8398178:
                freq1 = 1633;
                freq2 = 770;
                break;
            //C
            case 8398147:
                freq1 = 1633;
                freq2 = 852;
                break;
            //c
            case 8398179:
                freq1 = 1633;
                freq2 = 852;
                break;
            //D
            case 8398148:
                freq1 = 1633;
                freq2 = 941;
                break;
            //d
            case 8398180:
                freq1 = 1633;
                freq2 = 941;
                break;
            //*
            case 8398122:
                freq1 = 1209;
                freq2 = 941;
                break;
            //#
            case 8398115:
                freq1 = 1477;
                freq2 = 941;
                break;
    
            default:
                mag1 = 00000.0;
                mag2 = 00000.0;
                freq1 = 000;
                freq2 = 0000;
                break;
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




		 if(gtz_out[0] >1000 && gtz_out[4]  >1000){
			System_printf("\n The Button is 1");
			System_flush();
		}else if(gtz_out[0]  >1000 && gtz_out[5]  >1000){
			System_printf("\n The Button is 2");
			System_flush();
		}else if(gtz_out[0]  >1000 && gtz_out[6]  >1000){
			System_printf("\n The Button is 3");
			System_flush();
		}else if(gtz_out[0]  >1000 && gtz_out[7]  >1000){
			System_printf("\n The Button is A");
			System_flush();
		}else if(gtz_out[1]  >1000 && gtz_out[4]  >1000){
			System_printf("\n The Button is 4");
			System_flush();
		}else if(gtz_out[1]  >1000 && gtz_out[5]  >1000){
			System_printf("\n The Button is 5");
			System_flush();
		}else if(gtz_out[1]  >1000 && gtz_out[6]  >1000){
			System_printf("\n The Button is 6");
			System_flush();
		}else if(gtz_out[1]  >1000 && gtz_out[7]  >1000){
			System_printf("\n The Button is B");
			System_flush();
		}else if(gtz_out[2]  >1000 && gtz_out[4]  >1000){
			System_printf("\n The Button is 7");
			System_flush();
		}else if(gtz_out[2]  >1000 && gtz_out[5]  >1000){
			System_printf("\n The Button is 8");
			System_flush();
        }else if(gtz_out[2]  >1000 && gtz_out[6]  >1000){
			System_printf("\n The Button is 9");
			System_flush();
        }else if(gtz_out[2]  >1000 && gtz_out[7]  >1000){
			System_printf("\n The Button is C");
			System_flush();
        }else if(gtz_out[3]  >1000 && gtz_out[4] >1000){
			System_printf("\n The Button is *");
			System_flush();
        }else if(gtz_out[3]  >1000 && gtz_out[5] >1000){
			System_printf("\n The Button is 0");
			System_flush();
        }else if(gtz_out[3]  >1000 && gtz_out[6] >1000){
			System_printf("\n The Button is #");
			System_flush();
        }else if(gtz_out[3]  >1000 && gtz_out[7]  >1000){
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

