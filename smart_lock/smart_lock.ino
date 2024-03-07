#include <Keypad.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);


#define codeLength 4
Servo myservo;

char Code[codeLength];
char Password[codeLength] = "123"; //make password *
byte keyCount = 0; //counts keys pressed *

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = { //map rows and columns to buttons on keypad *
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); //mapping keys to pins 

void setup(){
  Serial.begin(9600);
  myservo.attach(10); //attach the servo at pin 10*
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Lock");
  lcd.setCursor(0,1);
  lcd.print("By Shivang");
  delay(2000);
  lcd.clear();
}

void loop(){
  char key = keypad.getKey();
    lcd.setCursor(0,0);
    lcd.print("Enter Code");
  if (key){
    //Serial.println(key); USE THIS FOR TESTING
    Code[keyCount] = key; //add to key count when we press a button, store in the array*
    Serial.print(Code[keyCount]); //USE THIS FOR WHEN DOING REAL CODE
    lcd.setCursor(0,1);
    lcd.print(Code[keyCount]);
    keyCount++;
    delay(300);
  }
  
  if (keyCount == codeLength-1) { //checking when to see if code length is achieved
    Serial.println("   ");
    
    lcd.setCursor(0,1);
    lcd.print("    ");
    //delay(200);
    lcd.clear();
   
    lcd.setCursor(0,0);
    lcd.print("Enter Code");
     delay(3000);
    if(!strcmp(Code,Password)){ //string compare - is input keys the same as the keys pressed
      Serial.println("Correct");
      lcd.setCursor(0,1);
      lcd.print("Correct");
      myservo.write(0); //unlock
      delay(4000);
      lcd.clear();
      
    }
    else{
      Serial.println("Incorrect");
      lcd.setCursor(0,1);
      lcd.print("Incorrect Code");
      myservo.write(90); //lock
      delay (2000);
      lcd.clear();
    }
  deleteCount();
  }
}
  
void deleteCount(){
  while (keyCount !=0) { //!= not equal to
    Code[keyCount --]=0;
  }
  return;
}
