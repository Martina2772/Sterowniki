const int PwmP=;   
const int PwmT=;
//rotacja
const int RPT=;  
const int RLT=;
const int RPP=;
const int RLP=;


void jazda()
{
  for (int v = 0; v <= 124; v++) {  
    analogWrite(pwm, v);  
    delay(10); 
  }
}
void wyhamowanie()
{
  for (int v = 255; v >= 124; v--) {  
    analogWrite(PwmP, v);
    delay(10); 
  }
}
void setup() {
 
  pinMode(pwmPrawy, OUTPUT);
  pinMode(pwmLewy,OUTPUT);
  pinMode(RPT, OUTPUT);
  pinMode(RPP,OUTPUT);
  pinMode(RLT, OUTPUT);
  pinMode(RLP,OUTPUT);


  digitalWrite(RPT, HIGH);  
  
}

void loop() {
 
  jazda();
  //wyhamowanie(); 
  analogWrite(pwmP,0);
  delay(2000);
  digitalWrite(RPT, LOW); 
  jazda();
  //wyhamowanie();
  analogWrite(pwmP,0);
  delay(500); 
}

