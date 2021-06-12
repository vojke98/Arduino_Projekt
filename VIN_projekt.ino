#include "pitches.h"

const int lightBtnPin = 2;
const int playBtnPin = 4;
const int ledPin = 13;
const int ldrPin = A0;
const int buzzerPin = 3;
const int redLED = 12;
const int greenLED = 11;
const int blueLED = 10;

unsigned long lightBtn_LDT = 0;
unsigned long playBtn_LDT = 0;
unsigned long debounceDelay = 25; 
unsigned long time1;
unsigned long time2;

int runMode = 0;
int daylight = 5;
int lightButtonState;
int playButtonState;       
int whiteLEDState = HIGH;    
int lightBtn_LDS = LOW;
int playBtn_LDS = LOW;
int LDR_value = 0;

boolean interupt = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(lightBtnPin, INPUT);
  pinMode(playBtnPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  time1 = millis();

  Serial.begin(9600);

  attachInterrupt(0, interuptF, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  interupt = false;
  
  checkLightBtn();
  checkPlayBtn();

  if(runMode == 0){
    sensor();
  }else if(runMode == 1){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }

  toggleLED(runMode);
}

void toggleLED(int runMode){
  int pin1 = 10 + runMode;
  int pin2 = 10 + (runMode + 1) % 3;
  int pin3 = 10 + (runMode + 2) % 3;

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
}

void interuptF(){
  interupt = true;
}

void checkLightBtn(){
  int button = digitalRead(lightBtnPin);

  if (button != lightBtn_LDS) {
    lightBtn_LDT = millis();
  }

  if ((millis() - lightBtn_LDT) > debounceDelay) {

    if (button != lightButtonState) {
      lightButtonState = button;

      if (lightButtonState == HIGH) {
        runMode++;        
        if(runMode > 2) runMode = 0;
        
        if(runMode == 0) daylight = 5;
        
        btnClick();
      }
    }
  }
  
  lightBtn_LDS = button;
}

void checkPlayBtn(){
  int button = digitalRead(playBtnPin);

  if (button != playBtn_LDS) {
    playBtn_LDT = millis();
  }

  if ((millis() - playBtn_LDT) > debounceDelay) {

    if (button != playButtonState) {
      playButtonState = button;

      if (playButtonState == HIGH) {
        btnClick();
        TakeOnMe();
      }
    }
  }
  
  playBtn_LDS = button;
}

void TakeOnMe(){
  
  int melody[] = {
    
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
    
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8
    
  };

  playSong(melody, sizeof(melody), 180);
}

void playSong(int melody[], int n, int tempo){

  int led = runMode;
  boolean ledS = true;
  
  int notes = n / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;
  
  for (int note = 0; note < notes * 2; note += 2) {
  
    if(interupt) break;

    led++;
    if(led > 2) led = 0;

    toggleLED(led);

    int pin1 = 10 + led;

    divider = melody[note + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    

    tone(buzzerPin, melody[note], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzerPin);
  }
}

void btnClick(){
  digitalWrite(buzzerPin, HIGH);
  delay(50);
  digitalWrite(buzzerPin, LOW);
}

void sensor(){

  time2 = millis();

  if(time2 - time1 > 1000){
    time1 = time2;
  
    LDR_value = analogRead(ldrPin);
  
    if(LDR_value < 800){
      if(daylight > 0) daylight--;
    }else{
      if(daylight < 10) daylight++;
    }

    String s = "[" + String(daylight) + "] " + LDR_value;

    Serial.print(s);

    if(daylight > 6 && whiteLEDState == HIGH) {
      whiteLEDState = LOW;
      digitalWrite(ledPin, whiteLEDState);
      Serial.print(" -> LED OFF");
    }
    else if(daylight < 4 && whiteLEDState == LOW) {
      whiteLEDState = HIGH;
      digitalWrite(ledPin, whiteLEDState);
      Serial.print(" -> LED ON");
    }

    Serial.println();
  }
}
