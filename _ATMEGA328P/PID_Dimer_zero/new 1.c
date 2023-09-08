#include <PID_v1.h>

int firing_triac = 1;    // OUTPUT TO CONTROL TRIAC
int zero_in = 2; // INPUT FROM ZERO DETECTION   
double value_zero = 0;
int pot_pin = A1;

int temperature = 0;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
double lastupdate;
double newSetpointPot;
double newSetpoint;

double consKp = 1, consKi = 0.05, consKd = 0.25;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

void setup()
{
 
  myPID.SetOutputLimits(0, 220);
  myPID.SetMode(AUTOMATIC);
  lastupdate = millis();
  Setpoint = 0;
  pinMode(firing_triac, OUTPUT); // Set the AC Load as output
  pinMode(zero_in, INPUT);
  digitalWrite(zero_in, HIGH); // pull up
  attachInterrupt(0, zero_crosss_int, RISING);
}

void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{
  int dimtime = (40*Output);     
  delayMicroseconds(dimtime);    // Off cycle
  digitalWrite(firing_triac, HIGH);   // triac firing
  delayMicroseconds(10);         // triac On propagation delay
  digitalWrite(firing_triac, LOW);    // triac Off
}

void loop()
{
 
  Input = 0;
  for(int i=0;i<50;i++)
  Input += analogRead(A0);
  Input /= 50;
  Input = map(Input, 0, 550, 25, 400);
  temperature = Input;
  newSetpointPot = analogRead(pot_pin);
  newSetpoint = map(newSetpointPot, 0, 1023, 150, 400);
  //Display setpoint
  if (abs(newSetpoint - Setpoint) > 3) {
    Setpoint = newSetpoint;
    temperature = newSetpoint;
    lastupdate = millis();
  }
  myPID.SetTunings(consKp, consKi, consKd);
  noInterrupts();
  myPID.Compute();
  interrupts();
  //delay(1000);
}