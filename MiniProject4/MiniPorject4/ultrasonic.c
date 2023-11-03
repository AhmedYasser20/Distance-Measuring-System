#include "ultrasonic.h"
#include "std_types.h"
#include "common_macros.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>


void (*Ptr_Ultrasonic_edgeProcessing)()=Ultrasonic_edgeProcessing;

static uint8 Edge_num=0;
static uint8 DataIsReady;

uint16 time_period=0;



void Ultrasonic_init(void){
	ICU_ConfigType Config_ICU={F_CPU_8,RAISING};
	ICU_init(&Config_ICU);
	ICU_setCallBack(Ptr_Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(PORTD_ID,PIN6_ID,PIN_INPUT);
}

void Ultrasonic_Trigger(void){
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	DataIsReady=0;
	ICU_clearTimerValue();
	while(DataIsReady!=1);
	DataIsReady=0;
	uint16 distance=time_period*0.017;
	return distance;
}
void Ultrasonic_edgeProcessing(void){
	Edge_num++;
	if(Edge_num==1){
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else{
		time_period=ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		DataIsReady=1;
		ICU_setEdgeDetectionType(RAISING);
		Edge_num=0;
	}
}
