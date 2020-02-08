#include <IRremote.h>
#include "l_mp.h"
#define STRIPS 5


uint8_t strip [STRIPS] = {3,5,9,10,11};

int RECV_PIN = A1;



void setup()
{  
  /*init variables*/
  is_on = false;
  button = false;
  vol_z1 = 0;
  threshold = 5; 
  stepp = 5; 
  pot_vol = 0;
  cnt = 0;
  potvol_z1 = 0;
  int RECV_PIN = A1;
  
  /*enable commulnication*/
  irrecv.enableIRIn();
  Serial.begin(9600);
  
  /*configure pins*/
  pinMode(A2, INPUT); 
  pinMode( A0, INPUT);
  for (int i = 0 ; i < STRIPS ; i++)
  {
     pinMode(strip [i], OUTPUT);
     digitalWrite(strip [i],LOW);
  }

}



void loop() {

int pot_vol = analogRead(A0)/4;

  if(pot_vol >= potvol_z1 + threshold){
    potvol_z1 += stepp;
  }
  else if(pot_vol <= potvol_z1 - threshold){
    potvol_z1 -= stepp;
  }
 
  if (!button)
  {
      for (int j = 0; j< STRIPS; j++){
        analogWrite(strip [j], potvol_z1);   
      }
  }
  potvol_z1 = pot_vol;
  
    if (cnt > 50){ 
       chack_button();
       cnt=0;
      }
   cnt+=1;
   chack_ir();
//delay (1000);
//Serial.println(pot_vol);
}


void chack_button()
{
    if (digitalRead(A2)&& !is_on)
    {
    fade_in(strip,  STRIPS, 255);
    is_on = true;
    button =true;  
    } 
  if (!digitalRead(A2)&& is_on)
  {
    fade_out(strip,  STRIPS, 0);
    is_on = false;
    button =true;
  }
}
void chack_ir(){
if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     irrecv.resume(); // Receive the next value
    }
}
void fade_out(uint8_t* leds, uint8_t len, int vol){
  for (int i = vol_z1; i >= vol; i--)
  {
      for (int j = 0; j< len; j++)
      {
        analogWrite(leds [j], i);   
      }
      delay(5);
   
   }
     Serial.print("done fade out to -> ");
     Serial.print(vol_z1);
     Serial.print(" to -> ");
     Serial.println(vol);
     vol_z1 = vol;
}

void fade_in(uint8_t* leds, uint8_t len, int vol){
  for (int i = vol_z1; i < vol; i++)
  {
      for (int j =0; j< len; j++){
        analogWrite(leds [j], i);   
      }  
      delay(5);
   
  }
   Serial.print("done fade in from -> ");
   Serial.print(vol_z1);
   Serial.print(" to -> ");
   Serial.println(vol);
   
   vol_z1 = vol;
}


