#define PWM_L 9  //Sygnał PWM silnika L
#define PWM_R 10 //Sygnał PWM silnika R
#define DIR_L 7 //Kierunek obrotu koła L
#define DIR_R 8 //Kierunek obrotu koła P
#define JOY_FB 5 //Joystick F/B
#define JOY_RL 6 //Joystick R/L

#define MIDDLE_FB 512 //2.5 V
#define MIDDLE_RL 512 //2.5 V
#define FORWARD 1
#define BACKWARD 0
#define TURN_LEFT 1
#define TURN_RIGHT -1
#define NO_TURN 0
#define SPEED_MULTIPLIER 255
#define TURN_MULTIPIER 255
//CALIBRATIONS
#define JOYSTICK_CALIBRATION 0.15
#define MAX_SPEED_LIMIT 0.6
#define MAX_TURN_LIMIT 0.3 //to musi byc mala wartosc, im blizej 1 tym jedno kolo bardziej zahamuje przy skrecaniu

bool _dir = 0; //Kierunek obrotu kół 1=f  0=b
int speed = 0; //0-255

// bool getKierunekKolo(prawy/lewy, przod/tyl)
// {
//   if prawy and dir
//   return 0
//   else if lewy return 1
// }

void setup() {
  // put your setup code here, to run once:
  //do zrobienia
  pinMode(PWM_R, OUTPUT); //Sygnał PWM silnika R
  pinMode(PWM_L, OUTPUT); //Sygnał PWM silnika L
  pinMode(DIR_R, OUTPUT); //Kierunek obrotu koła R
  pinMode(DIR_L, OUTPUT); //Kierunek obrotu koła L
  pinMode(JOY_FB, INPUT); //Joystick F/B
  pinMode(JOY_RL, INPUT); //Joystick R/L
}

void loop() {
  // put your main code here, to run repeatedly:
  double fb = analogRead(JOY_FB);
  double rl = analogRead(JOY_RL);
  double wheelR, wheelL;
  
  setDirectionFB(fb);
  velocityFB = getVelocityFB(fb);
  wheelR = velocityFB * MAX_SPEED * MAX_SPEED_LIMIT;
  wheelL = velocityFB * MAX_SPEED * MAX_SPEED_LIMIT;

  turn = getDirectionRL(rl);
  if (turn == TURN_LEFT)
    wheelL = wheelL - getVelocityRL(rl) * TURN_MULTIPIER * MAX_TURN_LIMIT; //zmniejszamy predkosc kola L o wartosc z przedzialu (0-1) * mnozniki stałe
  else if (turn == TURN_RIGHT)
    wheelR = wheelR - getVelocityRL(rl) * TURN_MULTIPIER * MAX_TURN_LIMIT;
  
  //ustaw wartosci wheelR i wheelL do odpowiednich pinow
  setLeftWheel(wheelL);
  setRightWheel(wheelR);
}

// przod y=0
// tyl y=1023
// lewo x=0
// prawo x=1023

// skret 5 - 2.5 V lewo | 2.5 - 0 V prawo
// jazda 0 - 2.5 przód | 2.5 - 5 tył


void setDirectionFB(double fb_input){
// direction 0 - 2.5 forward | 2.5 - 5 backward
  // if (getVelocity > 0) //todo: ile???? ograniczenie predkosci
  //   return;

  if (fb_input <= MIDDLE_FB - MIDDLE_FB * JOYSTICK_CALIBRATION){  //jazda do przodu
    if(_dir != FORWARD){
      _dir = FORWARD;
      digitalWrite(DIR_L, _dir);
      digitalWrite(DIR_R, !_dir);
    }
  } 
  else if (fb_input >= MIDDLE_FB + MIDDLE_FB * JOYSTICK_CALIBRATION){ //jazda do tyłu
    if(_dir != BACKWARD){
      _dir = BACKWARD;
      digitalWrite(DIR_L, !_dir);
      digitalWrite(DIR_R, _dir);
    }
  }
}

bool getDirectionFB(){
  // 1 - forward || 0 - backward
  return _dir;
}

double getVelocityFB(double fb_input){ //zwraca prędkość od 0 do 1
  // 1 - MAX_SPEED || 0 - MIN_SPEED
  if (fb_input <= MIDDLE_FB - MIDDLE_FB * JOYSTICK_CALIBRATION)
    return 1.0 - (fb_input/(MIDDLE_FB - MIDDLE_FB * JOYSTICK_CALIBRATION));
  else if (fb_input >= MIDDLE_FB + MIDDLE_FB * JOYSTICK_CALIBRATION)
    return (fb_input/(MIDDLE_FB + MIDDLE_FB * JOYSTICK_CALIBRATION)) - 1.0;
}

int getDirectionRL(double turn){
  // 1 - left || -1 - right || 0 - nothing
  if (turn <= MIDDLE_RL - MIDDLE_RL * JOYSTICK_CALIBRATION)
    return TURN_RIGHT;
  else if (turn >= MIDDLE_RL + MIDDLE_RL * JOYSTICK_CALIBRATION)
    return TURN_LEFT;
  return NO_TURN;
}

double getVelocityRL(double rl_input){ //zwraca skręt od 0 do 1
  // 1 - MAX_TURN || 0 - MIN_TURN
  if (rl_input <= MIDDLE_RL - MIDDLE_RL * JOYSTICK_CALIBRATION)
    return 1.0 - (rl_input/(MIDDLE_RL - MIDDLE_RL * JOYSTICK_CALIBRATION));
  else if (rl_input >= MIDDLE_RL + MIDDLE_RL * JOYSTICK_CALIBRATION)
    return (rl_input/(MIDDLE_RL + MIDDLE_RL * JOYSTICK_CALIBRATION)) - 1.0;
}


void setLeftWheel(double vel){
  analogWrite(PWM_L, int(vel));
}

void setRightWheel(double vel){
  analogWrite(PWM_R, int(vel));
}
