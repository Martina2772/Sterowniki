#define PWM_1 9 //Sygnał PWM silnika nr 1
#define DIR1 7 //Kierunek obrotu koła 1

bool _dir = 0; //Kierunek obrotu kół
int speed = 0; //0-255

void zmiana_kierunku(){
  _dir = !_dir;
})

void rozpedzanie(){
  for (int i = 0, i <= 255, i = i + 20)
    speed = int;
    delay(1000);
}


void setup() {


  pinMode(PWM_1, OUTPUT); //Sygnał PWM silnika nr 1
  
  pinMode(DIR1, OUTPUT); //Sygnały sterujące kierunkiem obrotów silnika nr 1
 // pinMode(8, OUTPUT);

}

void loop() {

analogWrite(PWM_1, 100); //Niska prędkość
digitalWrite(DIR1, _dir); //Jazda do przodu
//digitalWrite(7, LOW); //Silnik nr 1 - obroty w lewo
//digitalWrite(8, HIGH);
delay(1500);
  
analogWrite(PWM_1, 255); //Maksymalna prędkość
//digitalWrite(8, LOW);
//digitalWrite(7, HIGH); //Silnik nr 1 - obroty w prawo
delay(1500);         

analogWrite(PWM_1, 0);
delay(5000);

zmiana_kierunku();
analogWrite(PWM_1, 170);
delay(3000);

analogWrite(PWM_1, 0);
rozpedzanie();

analogWrite(PWM_1, 0);


}
