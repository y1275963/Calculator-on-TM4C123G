/*
 * pad.c
 *
 *  Created on: Nov 11, 2014
 *      Author: tk
 */
#include "pad.h"
#include "timer.h"
#include "debug.h"

void pad_init(void){
	int delay;

	SYSCTL_RCGC2_R |= 0x18;
	delay = 0;

	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_CR_R |= 0x0F;
	GPIO_PORTD_AMSEL_R &= ~0x0F;
	GPIO_PORTD_AFSEL_R &= ~0x0F;
	GPIO_PORTD_PCTL_R &= ~0xFFFF;

	GPIO_PORTE_LOCK_R = 0x4C4F434B;
	GPIO_PORTE_CR_R |= 0x0F;
	GPIO_PORTE_AMSEL_R &= ~0x0F;
	GPIO_PORTE_AFSEL_R &= ~0x0F;
	GPIO_PORTE_PCTL_R &= ~0xFFFF;

	GPIO_PORTE_DEN_R |= 0x0F;
	GPIO_PORTD_DEN_R |= 0x0F;
	GPIO_PORTE_PDR_R |= 0x0F;
	GPIO_PORTD_PDR_R |= 0x0F;
	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTE_DIR_R |= 0x0F;
	GPIO_PORTE_DATA_R = 0;
	GPIO_PORTD_DATA_R = 0;
}

int pad_xvalue(void){

	GPIO_PORTE_DIR_R &= ~0x0F;



	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTD_DATA_R |= 0x0F;

	int i;
	for(i=0;i<=3;i++)
	{
		if ((GPIO_PORTE_DATA_R>>i)&0x01) return i;

	}
	return -1;
}
int pad_yvalue(void){

	GPIO_PORTD_DIR_R &= ~0x0F;



	GPIO_PORTE_DIR_R |= 0x0F;
	GPIO_PORTE_DATA_R |= 0x0F;

	int i = 0;
	for(i=0;i<=3;i++){
		if ((GPIO_PORTD_DATA_R>>i)&0x01) return i;
	}
	return -1;
}

int pad_xy(int * loc){
	more_delay(1);
	int temp = pad_xvalue();
	if(temp != -1)
	{
		temp = pad_xvalue();
		if(temp != -1){
			loc[0] = temp;
			temp = pad_yvalue();
			loc[1] = temp;
			return 0;
		}
		else{
			return -1;
		}
	}
	else{
		return -1;
	}


}

unsigned char pad_value(void){
	int loc[2] = {0};
	const char mat[][4] ={{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','*'},{'d','0','#','/'}};

	if(pad_xy(loc)==0)
	{
	//	UARTprintf("pad_value(): %c",mat[loc[0]][loc[1]]);
		return mat[loc[0]][loc[1]];
	}
	else{
		return 0;
	}
}

