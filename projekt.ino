#define PWM_1 9 //Sygnał PWM silnika nr 1
#define DIR1 7 //Kierunek obrotu koła 1
#define MIDDLE_FB 2.5
#define MIDDLE_RL 2.5
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
#define MAX_TURN_LIMIT 0.3

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
}

void loop() {
  while{
  // input // jazda 0 (przod)
  // input skret // skret 0 (prawo)
  double fb = 2.5;
  double rl = 2.5;
  double wheelR, wheelL;
  
  setDirectionFB(fb);
  direction = getDirectionFB();
  velocityFB = getVelocityFB(fb);
  wheelR = velocityFB * MAX_SPEED * MAX_SPEED_LIMIT;
  wheelL = velocityFB * MAX_SPEED * MAX_SPEED_LIMIT;

  turn = getDirectionRL(rl);
  if (turn == TURN_LEFT)
    wheelL -= getVelocityRL(rl) * TURN_MULTIPIER * MAX_TURN_LIMIT;
  else if (turn == TURN_RIGHT)
    wheelR -= getVelocityRL(rl) * TURN_MULTIPIER * MAX_TURN_LIMIT;
  
  //ustaw wartosci wheelR i wheelL do odpowiednich pinow
}
}

// przod y=0
// tyl y=1023
// lewo x=0
// prawo x=1023

// skret 5 - 2.5 V lewo | 2.5 - 0 V prawo
// jazda 0 - 2.5 przód | 2.5 - 5 tył


void setDirectionFB(double fb_input){
// direction 0 - 2.5 forward | 2.5 - 5 backward
  if (getVelocity > 0) //todo: ile????
    _dir;

  if (fb_input <= MIDDLE_FB - JOYSTICK_CALIBRATION) //jazda do przodu
    _dir = FORWARD;
  else if (fb_input >= MIDDLE_FB + JOYSTICK_CALIBRATION) //jazda do tyłu
    _dir = BACKWARD;
}

bool getDirectionFB(){
  // 1 - forward || 0 - backward
  return _dir;
}

double getVelocityFB(double fb_input){ //zwraca prędkość od 0 do 1
  // 1 - MAX_SPEED || 0 - MIN_SPEED
  if (fb_input <= MIDDLE_FB - JOYSTICK_CALIBRATION)
    return 1.0 - (fb_input/(MIDDLE_FB - JOYSTICK_CALIBRATION));
  else if (fb_input >= MIDDLE_FB + JOYSTICK_CALIBRATION)
    return (fb_input/(MIDDLE_FB + JOYSTICK_CALIBRATION)) - 1.0;
}

int getDirectionRL(double turn){
  // 1 - left || -1 - right || 0 - nothing
  if (turn <= MIDDLE_RL - JOYSTICK_CALIBRATION)
    return TURN_RIGHT;
  else if (turn >= MIDDLE_RL + JOYSTICK_CALIBRATION)
    return TURN_LEFT;
  return NO_TURN;
}

double getVelocityRL(double rl_input){ //zwraca skręt od 0 do 1
  // 1 - MAX_TURN || 0 - MIN_TURN
  if (rl_input <= MIDDLE_RL - JOYSTICK_CALIBRATION)
    return 1.0 - (rl_input/(MIDDLE_RL - JOYSTICK_CALIBRATION));
  else if (rl_input >= MIDDLE_RL + JOYSTICK_CALIBRATION)
    return (rl_input/(MIDDLE_RL + JOYSTICK_CALIBRATION)) - 1.0;
}

