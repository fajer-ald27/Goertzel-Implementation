/*
 *  ======== gtz.c ========
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

void clk_SWI_Generate_DTMF(UArg arg0);
void clk_SWI_GTZ_0697Hz(UArg arg0);
void clk_SWI_GTZ_0770Hz(UArg arg0);
void clk_SWI_GTZ_0852Hz(UArg arg0);
void clk_SWI_GTZ_0941Hz(UArg arg0);
void clk_SWI_GTZ_01209Hz(UArg arg0);
void clk_SWI_GTZ_01336Hz(UArg arg0);
void clk_SWI_GTZ_01477Hz(UArg arg0);
void clk_SWI_GTZ_01633Hz(UArg arg0);

extern void task0_dtmfGen(void);
extern void task1_dtmfDetect(void);

extern char digit;
extern int sample, mag1, mag2, freq1, freq2, gtz_out[8];
extern short coef[8];
/*
 *  ======== main ========
 */
void main(void)
{


	   System_printf("\n I am in main :\n");
	   System_flush();
	/* Create a Clock Instance */
    Clock_Params clkParams;

    /* Initialise Clock Instance with time period and timeout (system ticks) */
    Clock_Params_init(&clkParams);
    clkParams.period = 1;
    clkParams.startFlag = TRUE;

    /* Instantiate ISR for tone generation  */
	Clock_create(clk_SWI_Generate_DTMF, TIMEOUT, &clkParams, NULL);

    /* Instantiate 8 parallel ISRs for each of the eight Goertzel coefficients */
	Clock_create(clk_SWI_GTZ_0697Hz, TIMEOUT, &clkParams, NULL);
	Clock_create(clk_SWI_GTZ_0770Hz, TIMEOUT, &clkParams, NULL);
	Clock_create(clk_SWI_GTZ_0852Hz, TIMEOUT, &clkParams, NULL);
	Clock_create(clk_SWI_GTZ_0941Hz, TIMEOUT, &clkParams, NULL);
	Clock_create(clk_SWI_GTZ_01209Hz,TIMEOUT, &clkParams, NULL);
	Clock_create(clk_SWI_GTZ_01336Hz,TIMEOUT, &clkParams, NULL);
	Clock_create(clk_SWI_GTZ_01477Hz,TIMEOUT, &clkParams, NULL);
	Clock_create(clk_SWI_GTZ_01633Hz, TIMEOUT, &clkParams, NULL);


	/* Start SYS_BIOS */
    BIOS_start();
}

/*
 *  ====== clk0Fxn =====
 *  Dual-Tone Generation
 *  ====================
 */
void clk_SWI_Generate_DTMF(UArg arg0)
{
	static int tick;


	tick = Clock_getTicks();

	sample = (int) 32768.0*sin(2.0*PI*freq1*TICK_PERItickOD*) + 32768.0*sin(2.0*PI*freq2*TICK_PERIOD*tick);
sample = sample >>8;
}

/*
 *  ====== clk_SWI_GTZ =====
 *  gtz sweep
 *  ====================
 */
void clk_SWI_GTZ_0697Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;



   	coef_1 = coef[0];
    input = (short) (sample);

    prod1 = (delay_1*coef_1)>>14;
    delay = input + (short)prod1-delay_2;
    delay_2 = delay_1;
    delay_1 = delay;
    N++;

    if(N == 206){
    prod1 = (delay_1 * delay_1);
    prod2 = (delay_2 * delay_2);
    prod3 = (delay_1 * coef_1)>>14;
    prod3 = prod3 * delay_2;

    Goertzel_Value = (prod1+prod2-prod3) >>15;
    Goertzel_Value <<= 8; // Scale up value for sensitivity
    N = 0;
    delay_1 = delay_2 =0;
    }

    gtz_out[0] = Goertzel_Value;

    return;

}

void clk_SWI_GTZ_0770Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;



   	coef_1 = coef[1];
    input = (short) (sample);

    prod1 = (delay_1*coef_1)>>14;
    delay = input + (short)prod1-delay_2;
    delay_2 = delay_1;
    delay_1 = delay;
    N++;

    if(N == 206){
    prod1 = (delay_1 * delay_1);
    prod2 = (delay_2 * delay_2);
    prod3 = (delay_1 * coef_1)>>14;
    prod3 = prod3 * delay_2;

    Goertzel_Value = (prod1+prod2-prod3) >>15;
    Goertzel_Value <<= 8; // Scale up value for sensitivity
    N = 0;
    delay_1 = delay_2 =0;
    }

    gtz_out[1] = Goertzel_Value;

    return;

}

void clk_SWI_GTZ_0852Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;

   	coef_1 = coef[2];
    input = (short) (sample);

    prod1 = (delay_1*coef_1)>>14;
    delay = input + (short)prod1-delay_2;
    delay_2 = delay_1;
    delay_1 = delay;
    N++;

    if(N == 206){
    prod1 = (delay_1 * delay_1);
    prod2 = (delay_2 * delay_2);
    prod3 = (delay_1 * coef_1)>>14;
    prod3 = prod3 * delay_2;

    Goertzel_Value = (prod1+prod2-prod3) >>15;
    Goertzel_Value <<= 8; // Scale up value for sensitivity
    N = 0;
    delay_1 = delay_2 =0;
    }

    gtz_out[2] = Goertzel_Value;

    return;
}

void clk_SWI_GTZ_0941Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;

   	coef_1 = coef[3];
    input = (short) (sample);

    prod1 = (delay_1*coef_1)>>14;
    delay = input + (short)prod1-delay_2;
    delay_2 = delay_1;
    delay_1 = delay;
    N++;

    if(N == 206){
    prod1 = (delay_1 * delay_1);
    prod2 = (delay_2 * delay_2);
    prod3 = (delay_1 * coef_1)>>14;
    prod3 = prod3 * delay_2;

    Goertzel_Value = (prod1+prod2-prod3) >>15;
    Goertzel_Value <<= 8; // Scale up value for sensitivity
    N = 0;
    delay_1 = delay_2 =0;
    }

    gtz_out[3] = Goertzel_Value;

    return;
}


void clk_SWI_GTZ_01209Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;

   	coef_1 = coef[4];
    input = (short) (sample);

    prod1 = (delay_1*coef_1)>>14;
    delay = input + (short)prod1-delay_2;
    delay_2 = delay_1;
    delay_1 = delay;
    N++;

    if(N == 206){
    prod1 = (delay_1 * delay_1);
    prod2 = (delay_2 * delay_2);
    prod3 = (delay_1 * coef_1)>>14;
    prod3 = prod3 * delay_2;

    Goertzel_Value = (prod1+prod2-prod3) >>15;
    Goertzel_Value <<= 8; // Scale up value for sensitivity
    N = 0;
    delay_1 = delay_2 =0;
    }

    gtz_out[4] = Goertzel_Value;

    return;
}
void clk_SWI_GTZ_01336Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;

   	coef_1 = coef[5];
    input = (short) (sample);

    prod1 = (delay_1*coef_1)>>14;
    delay = input + (short)prod1-delay_2;
    delay_2 = delay_1;
    delay_1 = delay;
    N++;

    if(N == 206){
    prod1 = (delay_1 * delay_1);
    prod2 = (delay_2 * delay_2);
    prod3 = (delay_1 * coef_1)>>14;
    prod3 = prod3 * delay_2;

    Goertzel_Value = (prod1+prod2-prod3) >>15;
    Goertzel_Value <<= 8; // Scale up value for sensitivity
    N = 0;
    delay_1 = delay_2 =0;
    }

    gtz_out[5] = Goertzel_Value;

    return;
}

void clk_SWI_GTZ_01477Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;

   	coef_1 = coef[6];
    input = (short) (sample);

    prod1 = (delay_1*coef_1)>>14;
    delay = input + (short)prod1-delay_2;
    delay_2 = delay_1;
    delay_1 = delay;
    N++;

    if(N == 206){
    prod1 = (delay_1 * delay_1);
    prod2 = (delay_2 * delay_2);
    prod3 = (delay_1 * coef_1)>>14;
    prod3 = prod3 * delay_2;

    Goertzel_Value = (prod1+prod2-prod3) >>15;
    Goertzel_Value <<= 8; // Scale up value for sensitivity
    N = 0;
    delay_1 = delay_2 =0;
    }

    gtz_out[6] = Goertzel_Value;

    return;
}


void clk_SWI_GTZ_01633Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;

   	coef_1 = coef[7];
    input = (short) (sample);

    prod1 = (delay_1*coef_1)>>14;
    delay = input + (short)prod1-delay_2;
    delay_2 = delay_1;
    delay_1 = delay;
    N++;

    if(N == 206){
    prod1 = (delay_1 * delay_1);
    prod2 = (delay_2 * delay_2);
    prod3 = (delay_1 * coef_1)>>14;
    prod3 = prod3 * delay_2;

    Goertzel_Value = (prod1+prod2-prod3) >>15;
    Goertzel_Value <<= 8; // Scale up value for sensitivity
    N = 0;
    delay_1 = delay_2 =0;
    }

    gtz_out[7] = Goertzel_Value;

    return;
}

