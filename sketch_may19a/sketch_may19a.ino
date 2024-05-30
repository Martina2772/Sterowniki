#define PWM_L 9  //Sygnał PWM silnika L
#define PWM_R 3 //Sygnał PWM silnika R
#define DIR_L 7 //Kierunek obrotu koła L
#define DIR_R 8 //Kierunek obrotu koła P
#define JOY_FB A0 //Joystick F/B
#define JOY_RL A1 //Joystick R/L
#define hamowanie 11
#define Prawe 5 //info o prędkości
#define Lewe 6

//enable 2 oraz 13
#define MIDDLE_V 512 //2.5 V
#define FORWARD 0
#define BACKWARD 1
#define SPEED_MULTIPLIER 255
//CALIBRATIONS
#define JOYSTICK_CALIBRATION 0.15
#define MAX_TURN_LIMIT 1 //to musi byc mala wartosc, im blizej 1 tym jedno kolo bardziej zahamuje przy skrecaniu

bool _dir = 0;

void setup() {
  pinMode(PWM_R, OUTPUT); //Sygnał PWM silnika R
  pinMode(PWM_L, OUTPUT); //Sygnał PWM silnika L
  pinMode(DIR_R, OUTPUT); //Kierunek obrotu koła R
  pinMode(DIR_L, OUTPUT); //Kierunek obrotu koła L
  pinMode(JOY_FB, INPUT); //Joystick F/B
  pinMode(JOY_RL, INPUT); //Joystick R/L
   Serial.begin(9600);
}

void loop() {
  double fb = analogRead(JOY_FB);
  double rl = analogRead(JOY_RL);
  double wheelR, wheelL; 
  
  setDirectionFB(fb);
   
  wheelR =  getVelocity(fb)* SPEED_MULTIPLIER;
  wheelL =  getVelocity(fb)* SPEED_MULTIPLIER;

Serial.print("FB      ");
Serial.println(fb);
Serial.print("RL      ");
Serial.println(rl);

  
  if (rl <= MIDDLE_V - MIDDLE_V * JOYSTICK_CALIBRATION){
  wheelR = wheelR - wheelR*((getVelocity(rl) * SPEED_MULTIPLIER * MAX_TURN_LIMIT)/255);
  Serial.print("wartosc skrety:  ");
  Serial.println(wheelL);
  Serial.println(wheelR);
    
  }else if (rl >= MIDDLE_V + MIDDLE_V * JOYSTICK_CALIBRATION){
   wheelL = wheelL - wheelL*((getVelocity(rl) * SPEED_MULTIPLIER * MAX_TURN_LIMIT)/255);
  Serial.print("wartosc skrety:  ");
  Serial.println(wheelL);
  Serial.println(wheelR);  
  }

 setLeftWheel(wheelL);
  setRightWheel(wheelR);

  Serial.print("Ustawienie predkosci prawe:  ");
  Serial.println(wheelR);
  Serial.print("Ustawienie predkosci lewe:  ");
  Serial.println(wheelL);
}

// skret 5 - 2.5 V lewo | 2.5 - 0 V prawo
// jazda 0 - 2.5 przód | 2.5 - 5 tył


void setDirectionFB(double fb_input){

  if (fb_input <= (MIDDLE_V - MIDDLE_V * JOYSTICK_CALIBRATION)){  //jazda do przodu
      _dir = FORWARD;
      digitalWrite(DIR_L, !_dir);
      digitalWrite(DIR_R, _dir);
  Serial.print("kierunek:  ");
  Serial.println(_dir);
    
  } 
  else if (fb_input >= (MIDDLE_V + MIDDLE_V * JOYSTICK_CALIBRATION)){ //jazda do tyłu
      _dir = BACKWARD;
      digitalWrite(DIR_L, !_dir);
      digitalWrite(DIR_R, _dir);
      Serial.print("kierunek:  ");
       Serial.println(_dir);
    
    }
  }

double getVelocity(double fb_input){ //zwraca prędkość od 0 do 1
  // 1 - MAX_SPEED || 0 - MIN_SPEED
  if (fb_input <= MIDDLE_V - MIDDLE_V * JOYSTICK_CALIBRATION)
    return 1.0 - (fb_input/(MIDDLE_V - MIDDLE_V * JOYSTICK_CALIBRATION));
  else if (fb_input >= MIDDLE_V + MIDDLE_V * JOYSTICK_CALIBRATION)
    return (fb_input/MIDDLE_V ) - 1.0;
  else
  return 0;
  Serial.print("getValocity:  ");
  Serial.println(fb_input); 
}

// int getDirectionRL(double rl_input){
//   if (rl_input <= MIDDLE_V - MIDDLE_V * JOYSTICK_CALIBRATION)
//     return 1;
//   else if (rl_input >= MIDDLE_V + MIDDLE_V * JOYSTICK_CALIBRATION)
//     return 2;
//   return 0;
// }



void setLeftWheel(double vel){
  analogWrite(PWM_L, int(vel));
    
}

void setRightWheel(double vel){
  analogWrite(PWM_R, int(vel));
}
