#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define Password_Length 5

Servo myservo;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int pos = 0;

char Data[Password_Length];
char Master[Password_Length] = "1234";

byte data_count = 0, master_count = 0;

bool Pass_is_good = false;
bool door = false;

char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {0, 1, 2, 3}; 
byte colPins[COLS] = {4, 5, 6, 7};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}

void setup() {
  lcd.begin(16, 2);
  myservo.attach(9);
  myservo.write(0);

  lcd.print("Door Lock");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");

  customKey = keypad.getKey();

  if (customKey) {
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print("*");
    data_count++;
  }

  if (data_count == Password_Length - 1) {
    lcd.clear();

    if (!strcmp(Data, Master)) {
      lcd.print("Access Granted");
      myservo.write(90);  
      delay(3000);
      myservo.write(0);   
    } else {
      lcd.print("Access Denied");
      delay(2000);
    }

    lcd.clear();
    clearData();
  }
}