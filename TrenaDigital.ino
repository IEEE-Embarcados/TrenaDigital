#include <LiquidCrystal.h>
LiquidCrystal lcd(3,4,11,10,9,8);

#include <Ultrasonic.h>
Ultrasonic ultrasonic(7,6); //define the name of sensor and set the pins -> trig(7) and echo(6) respectively

int distance = 0;
int readValue = 0;
int perimetro = 0;
int area = 1;

int inputMode = 12;
int inputModeState=0;

int btnReadDist = 13;
int btnReadState=0;

int btnClearValues = 5;
int clearValuesState=0;

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

  pinMode(inputMode, INPUT_PULLUP);
  pinMode(btnReadDist, INPUT_PULLUP);
  pinMode(btnClearValues, INPUT_PULLUP);

  Serial.begin(9600); //serial comumnication 9600 bauds rates.
}

void loop() {
  readValue = ultrasonic.Ranging(CM);//return the distance in CM

  lcd.setCursor(15,3);
  lcd.print("    ");
  delay(10);


  lcd.setCursor(14,3);
  lcd.print(distance);    
  lcd.setCursor(17,3);
  lcd.print("cm");

  //Resolver a medida;
  inputModeState = digitalRead(inputMode);
  btnReadState = digitalRead(btnReadDist);
  clearValuesState = digitalRead(btnClearValues);

  if(btnReadState == LOW){
    Serial.println("____________________________________________________");
    distance = readValue;

    if(inputModeState == HIGH){
      distance = readValue;
      area *= distance;
      Serial.print("area: ");
      Serial.print(area);
      Serial.println("CM");
      Serial.print("distance: ");
      Serial.print(distance);
      Serial.println("CM"); 


      clearDisplay();
      lcd.setCursor(14,1);
      lcd.print(area);    
      lcd.setCursor(17,1);
      lcd.print("cm");
    }

    if(inputModeState == LOW){
      perimetro += distance;
      Serial.print("perimetro: ");
      Serial.print(perimetro);
      Serial.println("CM");
      Serial.print("distance: ");
      Serial.print(distance);
      Serial.println("CM"); 

      clearDisplay();
      lcd.setCursor(14,2);
      lcd.print(perimetro);    
      lcd.setCursor(17,2);
      lcd.print("cm");    
    }
    delay(10);
  }
  
  if(clearValuesState == LOW){
    distance = 0;
    area = 1;
    perimetro = 0;
  }
  
  delay(500);
}

void clearDisplay(){
  lcd.clear();
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
}



