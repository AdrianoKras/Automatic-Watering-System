#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
int timeRespawn = 100;
int enemySpeed = 6;
int frames = 0;
int y = 1;
int score = 0;
bool jump = false;
int frameJump = 0;
int scoreWidth = 15;
const int arraySize = 5;
struct enemy{
  int x;
  bool move;
};
enemy enemies[arraySize];
void setup() {

  pinMode(9, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  lcd.begin(16, 2); //Deklaracja typu

  for(int i = 0; i<arraySize; i++) {
    enemies[i].move = false;
    enemies[i].x = 17;
  }

}
 
void loop() {
  lcd.setCursor(0, y);
  lcd.print("W");
  if(digitalRead(9) == LOW ) {
    if(!jump) {
      jump = true;
      y = 0;
      digitalWrite(13,HIGH);
    }
  }else {
    if(frameJump % 12 == 0) {
      y = 1;
      jump = false;
      frameJump = 0;
    }
    digitalWrite(13,LOW);
  }
  if(frames % 6 == 0) {
    for(int i = 0; i<arraySize; i++) {
    if(enemies[i].move) {
      enemies[i].x = enemies[i].x -1;
    }
  }

  }
  if(frames % timeRespawn == 0) {
    for(int i = 0; i<arraySize; i++) {
      if(!enemies[i].move) {
        enemies[i].move = true;
        break;
      }
    }
  }
  for(int i = 0; i<arraySize; i++) {
      if(enemies[i].x < 0) {
          enemies[i].move = false;
          enemies[i].x = 17;
          score++;
        }
      lcd.setCursor(enemies[i].x,1);
      lcd.print("d");
      if(enemies[i].x == 0 and y == 1) {
        lcd.setCursor(6,0);
        lcd.print("opps");
      } else {

      }
  }
  if(score > 5) {
    enemySpeed = 4;
    timeRespawn = 70;
  }
  if(jump) {
    frameJump++;
  }
  if(score / 10 > 0) {
    scoreWidth = 14;
  }
  if(score / 100 > 0) {
    scoreWidth = 13;
  }
  lcd.setCursor(scoreWidth,0);
  lcd.print(score);
  frames++;




  delay(100);
  lcd.clear();
}