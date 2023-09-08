#INCLUDE <16F887.H>
#include <string.h>
#FUSES NOWDT, PUT, HS, NOPROTECT, NOLVP
#USE DELAY(CLOCK=20M)
#define sensor_s1 PIN_A0
#define sensor_s2 PIN_A1
#define sensor_s3 PIN_A2
#define sensor_s4 PIN_B0
#define sensor_s5 PIN_B1

int s1, s2, s3, s4, s5;
UNSIGNED INT16 value1, value2;

VOID GO_STRAIGHT(){
   value1 = 400;
   value2 = 400;
   SET_PWM1_DUTY(value1);
   SET_PWM2_DUTY(value2);
}

VOID TURN_RIGHT(){
   value1 = 0;
   value2 = 500;
   SET_PWM1_DUTY(value1);
   SET_PWM2_DUTY(value2);
}

VOID TURN_LEFT(){
   value1 = 500;
   value2 = 0;
   SET_PWM1_DUTY(value1);
   SET_PWM2_DUTY(value2);

}
VOID STOP(){
   value1 = 0;
   value2 = 0;
   SET_PWM1_DUTY(value1);
   SET_PWM2_DUTY(value1);
}

VOID MAIN()
{
 SET_TRIS_C(0X00);
 SET_TRIS_A(0XFF);
 SET_TRIS_B(0xFF);
 SETUP_TIMER_2(T2_DIV_BY_16,249,1);
 SETUP_CCP1(CCP_PWM);
 SETUP_CCP2(CCP_PWM);
 value1 = 0;
 value2 = 0;
 SET_PWM1_DUTY(value1);
 SET_PWM2_DUTY(value2);
 OUTPUT_LOW(PIN_C3);
 OUTPUT_LOW(PIN_C0);

 WHILE(TRUE){
 s1 = INPUT(sensor_s1);
 s2 = INPUT(sensor_s2);
 s3 = INPUT(sensor_s3);
 s4 = INPUT(sensor_s4);
 s5 = INPUT(sensor_s5);
   //if ( s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1 && s5 == 1){GO_STRAIGHT();}
   //if ( s2 == 0 && s3 == 1 && s4 == 0) {GO_STRAIGHT();}
   //if ( s2 == 0 && s3 == 0 && s4 == 1) {TURN_RIGHT();}
   //if ( s2 == 0 && s3 == 1 && s4 == 1) {TURN_RIGHT();}
   
   //if ( s2 == 1 && s3 == 0 && s4 == 0) {TURN_LEFT();}
   //if ( s2 == 1 && s3 == 1 && s4 == 0) {TURN_LEFT();}
   //if ( s2 == 0 && s3 == 0 && s4 == 0){STOP();}
   if (s2 == 0 && s3 == 1 && s4 == 0){GO_STRAIGHT();}
   
   if (s2 == 0 && s3 == 0 && s4 == 1) {TURN_RIGHT();}
   if (s2 == 0 && s3 == 1 && s4 == 1) {TURN_RIGHT();}
   
    if (s2 == 1 && s3 == 0 && s4 == 0) {TURN_LEFT();}
   if (s2 == 1 && s3 == 1 && s4 == 0) {TURN_LEFT();}
   
   if (s2 == 1 && s3 == 1 && s4 == 1) {STOP();}
   if (s2 == 0 && s3 == 0 && s4 == 0) {STOP();}
 }
}
