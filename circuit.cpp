
// include the library code:
#include <LiquidCrystal.h>

int cm = 0;
int firstTime = 1;

int buttonStateYES = 0;
int buttonStateNO = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600); 
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hi, it's deafa");
  
  if (firstTime == 1){
    lcd.setCursor(0, 1);
    lcd.print("Run the tuto");
  }
  delay(3000);
  lcd.clear();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  
  if (cm > 60 && cm < 250){
    lcd.setCursor(0, 0);
    lcd.println("Activate :");
    
    buttonStateYES = digitalRead(8);
    buttonStateNO = digitalRead(9);
    
    while (buttonStateYES == LOW && buttonStateNO == LOW){
      lcd.setCursor(0, 1);
      lcd.println("Question ?");
      buttonStateYES = digitalRead(8);
      buttonStateNO = digitalRead(9);
    }
    
    if (buttonStateYES == HIGH) {
      buttonStateYES = 0;
      buttonStateNO = 0;
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.println("Sign question :");
      Serial.println("Analyse sign");
      delay(2000);
      lcd.clear();
      Serial.println("Call to API for question");
      lcd.println("Answer");
      
      while (buttonStateYES == LOW && buttonStateNO == LOW){
        lcd.setCursor(0, 1);
      	lcd.println("Good for you ?");
        buttonStateYES = digitalRead(8);
        buttonStateNO = digitalRead(9);
        
        if (buttonStateYES == HIGH){
          lcd.clear();
          lcd.println("Nice");
        }
        else if (buttonStateNO == HIGH){
          lcd.clear();
          lcd.println("Reformule pls");
        }
      }
    }
    else if (buttonStateNO == HIGH){
      buttonStateYES = 0;
      buttonStateNO = 0;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.println("Sign demande :");
      Serial.println("Analyse sign");
      delay(2000);
      lcd.clear();
      Serial.println("Call to API for demande");

      while (buttonStateYES == LOW && buttonStateNO == LOW){
        lcd.setCursor(0, 0);
        lcd.println("Reserve train ?");
        buttonStateYES = digitalRead(8);
        buttonStateNO = digitalRead(9);

        if (buttonStateYES == HIGH){
          delay(100);
          lcd.clear();
          buttonStateYES = 0;
      	  buttonStateNO = 0;
          lcd.setCursor(0, 0);
          lcd.println("Go to Paris ?");
          while (buttonStateYES == LOW && buttonStateNO == LOW){
            lcd.setCursor(0, 0);
          	lcd.println("Go to Paris ?");
            buttonStateYES = digitalRead(8);
        	buttonStateNO = digitalRead(9);
          }
          if (buttonStateYES == HIGH){
            lcd.clear();
            lcd.println("Ok it's reversed");
          }
          else if (buttonStateNO == HIGH){
            lcd.clear();
            lcd.println("Reformule pls");
          }
        }
        else if (buttonStateNO == HIGH){
          lcd.clear();
          lcd.println("Reformule pls");
        }
      }
    }
  }
  else if (cm < 60){
    lcd.println("Too close !");
  }
  else if (cm > 250){
   	lcd.println("Too far !"); 
  }
  delay(1000);
  lcd.clear();
}
 
