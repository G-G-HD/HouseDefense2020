#include <Servo.h>
#include <LiquidCrystal.h>

Servo servoX;
Servo servoY;

int accellerazioneX;
int accellerazioneY;
//Bottoni
int up = 4;
int down = 5;
int left = 3;
int right = 6;


int statoLaser = 12;

int serX = 11;
int serY = 10;
String input;             //Stringa dove salvare il contenuto della finestra seriale
String coordinate;        //Stringa di stampa XY
int x, y;              //Variabili dove vengono calcolati i valori di accellerazione x e y;
int premi;                //Variabile dove viene registrato R3 (premere joystick)
int gradiX;
int gradiY;
int laser = 8;

//INPUT
int pulsanteToggleLaser = 2;
int joyX = 4;
int joyY = 3;
int joyPress = 5;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  pinMode(laser, OUTPUT);
  pinMode(pulsanteToggleLaser, INPUT);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(joyPress, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);

  pinMode(statoLaser, OUTPUT);


  servoX.attach(serX);
  servoY.attach(serY);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
  AssegnaValoriButton();
  Stampa();
  Aim();
  VerificaLaserLed();

  if (digitalRead(pulsanteToggleLaser) == HIGH) {
    ToggleLaser();
  }
  //LCD();
}

void serialEvent() {
  input = Serial.readString();
  LaserSerial();
}

void VerificaLaserLed() {                     //Accende il led se il laser è acceso
  if (digitalRead(laser) == HIGH) {
    digitalWrite(statoLaser, HIGH); 
  } else {
    digitalWrite(statoLaser, LOW);
  }
}

void ToggleLaser() {                          //toggla il laser
  if (digitalRead(laser) == HIGH) {
      digitalWrite(laser, LOW);
  } else if (digitalRead(laser) == LOW) {
    digitalWrite(laser, HIGH);
  }
  VerificaLaserLed();
  delay(1000);
}

void LaserSerial() {
  if (input == "LASER_ON\n") {
    digitalWrite(laser, HIGH);
  } else if (input == "LASER_OFF\n") {
    digitalWrite(laser, LOW);
  }
}
void AssegnaValoriButton() {
  
  //ASSEGNO VALORI DI ACCELLERAZIONE SUI BOTTONI
  
  if (digitalRead(up) == 1 && digitalRead(down) == 0) {
    accellerazioneY = 2;
  } else if (digitalRead(up) == 0 && digitalRead(down) == 1) {
    accellerazioneY = -2;
  } else if (digitalRead(left) == 0 && digitalRead(down) == 0) {
    accellerazioneY = 0;
  }

  if (digitalRead(left) == 1 && digitalRead(right) == 0) {
    accellerazioneX = 2;
  } else if (digitalRead(right) == 1 && digitalRead(left) == 0) {
    accellerazioneX = -2;
  } else if (digitalRead(right) == 0 && digitalRead(left) == 0) {
    accellerazioneX = 0;
  }
}

//Stampa valori
void Stampa() {

  // X JOYSTICK _-------------------------------------------
  //Leggo tutti gli ingressi e applico lo scaling per far si che vada da -1 a 1
  //x = analogRead(joyX);
  //x = (x / (1023 / 10)) - 5;
  //y = analogRead(joyY);
  //y = (y / (1023 / 10)) - 5;
  //premi = analogRead(joyPress);

  // Gestisco R3 Metto premi a 1 se vieni un risultato > 0
  //if (premi == 0)
  //  premi = 1;
  //else
  //  premi = 0;

  //stampa con joystick
  //coordinate = "X" + String(x) + "\tY" + String(y) + "\tPremi" + String(premi) + "\tServoX" + String(servoX.read()) + "\tServoY" + String(servoY.read());

  //stampa bottoni
  coordinate = "AccellerazioneX" + String(accellerazioneX) + "\tAccellerazioneY" + String(accellerazioneY) + "\t||\tPosXServo " + String(servoX.read()) + "\tPosYServo " + String(servoY.read());
  Serial.println(coordinate);
}


//-------------------MIRA/SHOOTING
void Aim() {
  //JOYSTICK CONTROL
  //gradiX = servoX.read() - x;
  //gradiY = servoY.read() - y;

  //BUTTON CONTROL
  gradiX = servoX.read() + accellerazioneX;
  gradiY = servoY.read() - accellerazioneY;


  //Write sui servo
  servoX.write(gradiX);
  servoY.write(gradiY);
}

void LCD(){
  if (up==1){
    lcd.setCursor(3,0);
    lcd.print("^");
  }else{
    lcd.setCursor(3,0);
    lcd.print(" ");
  }
  if (down==1){
    lcd.setCursor(3,1);
    lcd.print("v");
  }else{
    lcd.setCursor(3,1);
    lcd.print(" ");
  }
  if (left==1){
    lcd.setCursor(0,0);
    lcd.print("<");
  }else{
    lcd.setCursor(0,0);
    lcd.print(" ");
  }
  if (right==1){
    lcd.setCursor(1,0);
    lcd.print(">");
  }else{
    lcd.setCursor(1,0);
    lcd.print(" ");
  }
  if(laser==HIGH){
    lcd.setCursor(10,0);
    lcd.print("---*");
  }else{
    lcd.setCursor(10,0);
    lcd.print("    ");
  }
}
