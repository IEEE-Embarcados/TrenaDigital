#include <LiquidCrystal.h>
LiquidCrystal lcd(3,4,11,10,9,8);

#include <Ultrasonic.h>
Ultrasonic ultrasonic(7,6); //define the name of sensor and set the pins -> trig(8) and echo(7) respectively

int distance = 0;
int readValue = 0;
int perimetro = 0;
int area = 1;

int inputMode = 12;
int btnReadDist = 13;
int inputModeState=0;
int btnReadState=0;

void setup() {
  lcd.begin(20,4);
  lcd.setCursor(1,0);
  lcd.print("Trena Digital");
  lcd.setCursor(15,0);
  lcd.print("IEEE");
  lcd.setCursor(3,1);
  lcd.print("Area:");
  lcd.setCursor(3,2);
  lcd.print("Perimetro:");
  lcd.setCursor(3,3);
  lcd.print("Medida:");

  pinMode(inputMode, INPUT);
  pinMode(btnReadDist, INPUT_PULLUP);

  Serial.begin(9600); //serial comumnication 9600 bauds rates.
}

void loop() {
  readValue = ultrasonic.Ranging(CM);//return the distance in CM

  lcd.setCursor(15,3);
  lcd.print("    ");
  delay(10);


  lcd.setCursor(14,3);
  Serial.print(distance);
  Serial.print("\n");
  lcd.print(distance);    
  lcd.setCursor(17,3);
  lcd.print("cm");

  //Resolver a medida;
  inputModeState = digitalRead(inputMode);
  btnReadState = digitalRead(btnReadDist);

  if(btnReadState == HIGH){
    distance = readValue;

    if(inputModeState == HIGH){
      distance = readValue;
      area = area * distance;
      Serial.print(area);
      Serial.println("CM"); 

      lcd.setCursor(15,1);
      lcd.print("    ");
      delay(1);

      lcd.setCursor(14,1);
      lcd.print(area);    
      lcd.setCursor(17,1);
      lcd.print("cm");
    }

    if(inputModeState == LOW){
      perimetro = perimetro + distance;
      Serial.print(perimetro);
      Serial.println("CM");

      lcd.setCursor(15,2);
      lcd.print("    ");
      delay(1);

      lcd.setCursor(14,2);
      lcd.print(perimetro);    
      lcd.setCursor(17,2);
      lcd.print("cm");    
    }
      delay(100);
  }
}


