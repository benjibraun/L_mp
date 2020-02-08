#include <IRremote.h>
#define STRIPS 5


uint8_t strip [STRIPS] = {3,5,9,10,11};
int vol_z1 = 0;
uint8_t threshold = 5; 
uint8_t stepp = 5; 
int pot_vol = 0;
int cnt = 0;
int potvol_z1 = 0;
int OnOff_Button = 0xFFA25D; // mybe extra 0 needed ----> 0xFFA25D0  
int Plus_Button = 0xFF02FD; // mybe extra 0 needed  ----> 0xFF02FD0
int Minus_Button = 0xFF9867; // mybe extra 0 needed ----> 0xFF98670
int Hold_Button = 0xFFFFFFFF;
int RECV_PIN = A1;
bool is_on = false;
bool button = false;
void fade_out(uint8_t* leds, uint8_t len, int vol);
void fade_in(uint8_t* leds, uint8_t len, int vol);
void chack_ir();
void chack_button();
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() {
irrecv.enableIRIn();
pinMode(A2, INPUT); 
pinMode( A0, INPUT);
Serial.begin(9600);
for (int i = 0 ; i < STRIPS ; i++){
   pinMode(strip [i], OUTPUT);
   digitalWrite(strip [i],LOW);
}

}



void loop() {
fade_in(strip,STRIPS, 255);
delay(1000);
fade_out(strip,STRIPS,0);
delay(1000);
/*
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
  */
//Serial.println(potvol_z1); 
}
/*
if (vol_z1 < pot_vol-threshold){
  fade_in(strip,STRIPS, pot_vol);
}
if (vol_z1 > pot_vol+threshold){
  fade_out(strip,STRIPS,pot_vol);
}

if (pot_vol < 240){
  fade_in(strip,STRIPS,pot_vol);
  pot_vol += 5; 
}
else {
  fade_in(strip,STRIPS,pot_vol);
  pot_vol -= 5; 
}
*/



//delay (1000);
//Serial.println(pot_vol);


void chack_button(){
    if (digitalRead(A2)&& !is_on){
    fade_in(strip,  STRIPS, 255);
    is_on = true;
    button =true;
  
  }
  
  if (!digitalRead(A2)&& is_on){
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
  for (int i = vol_z1; i >= vol; i--){//  !!!! Not Working  
    for (int j = 0; j< len; j++){
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
  for (int i = vol_z1; i < vol; i++){
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


