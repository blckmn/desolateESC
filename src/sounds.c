/*This file is part of desolateESC CC BY-NC-SA*/
#include "main.h"
static uint16_t sinwave[300] = {5,5,4,4,4,3,3,3,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,11,11,12,13,13,14,15,16,16,17,18,19,20,21,21,22,23,24,25,26,27,28,29,30,31,32,33,34,34,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,51,52,53,54,55,56,57,58,59,60,61,62,63,64,66,66,67,68,69,70,71,72,73,74,75,76,77,78,79,79,80,81,82,83,84,84,85,86,87,87,88,89,89,90,91,91,92,92,93,93,94,94,95,95,96,96,97,97,97,98,98,98,98,99,99,99,99,99,100,100,100,100,100,100,100,100,100,100,100,100,100,99,99,99,99,99,98,98,98,97,97,97,96,96,96,95,95,94,94,93,93,92,91,91,90,90,89,88,88,87,86,85,85,84,83,82,82,81,80,79,78,77,76,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,24,23,22,21,20,19,18,18,17,16,15,15,14,13,12,12,11,10,10,9,9,8,7,7,6,6};
//desolate noise 
void noise(uint8_t tonetype, uint8_t fadeIn, uint8_t fadeOut){
	setComparatorInterruptStatus(0);
	PHASE_A_FLOATING;
	PHASE_B_FLOATING;
	PHASE_C_FLOATING;
	setPWMcompares(0); 
	if(!fadeIn) setPWMcompares(30);
	for(uint8_t w=0;w<6;w++){
		if(w < 3){
			if(fadeIn)setPWMcompares((w*7)+15);
		}else{
			if(fadeOut)setPWMcompares(((3-(w-3))*7)+15);
		}
		for(uint16_t i = 0;i<300;i++){
			resetWDT();
			PHASE_A_LOW;
			uint16_t desolateSound = micros16()&0x7F;
			uint16_t leftover = 0;
			if(sinwave[i] < 50){
				PHASE_C_FLOATING;
				if(desolateSound > 0x5F){
					PHASE_C_PWM;
					delay16(desolateSound);
					PHASE_C_FLOATING;
				}
				PHASE_B_PWM;
				delay16(sinwave[i]/tonetype);
				leftover = (50-sinwave[i])/tonetype;
			}else{
				PHASE_B_FLOATING;
				if(desolateSound > 0x5F){
					PHASE_B_PWM;
					delay16(desolateSound);
					PHASE_B_FLOATING;
				}
				PHASE_A_PWM;
				delay16((sinwave[i]-50)/tonetype);	
				leftover = (50-(sinwave[i]-50))/tonetype;
			}
			PHASE_A_FLOATING;
			PHASE_B_FLOATING;
			PHASE_C_FLOATING;
			delay16(leftover);	
		}
	}
	setPWMcompares(0);
	PHASE_A_FLOATING;
	PHASE_B_FLOATING;
	PHASE_C_FLOATING;
}