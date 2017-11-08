/*
SparkFun Inventor's Kit

Calculator with 2 buttons

Version 1.0 2/2013 MDG
*/

#include <LiquidCrystal.h>

#include <String.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int BUTTON_COUNT = 14;
const int buttonPin_1 = 1; // Number button pin 
const int buttonPin_2 = 0; // Enter/Delete button pin 

int number_count = 0;

int button1_State = HIGH;
int button2_State = HIGH;

long number_1 = 0;
long number_2 = 0;
long calculator_operator = 0;

int enter_button_click = 0;

boolean deletePressed = false;

String expression;
String operands[2];
int op;

void setup()
{
lcd.begin(16,2);
lcd.clear();
pinMode(buttonPin_1,INPUT);
pinMode(buttonPin_2,INPUT);

lcd.cursor();
lcd.setCursor(15,0);
lcd.blink();
}

String data[] = {"0","1","2","3","4","5","6","7","8","9","+","-","/","*","S","D"};

void loop() {

  //If button 1 was pressed, display the numbers and increment number for each button click.
  if(button1_State == HIGH && digitalRead(buttonPin_1) == LOW) 
  {
    button1_State = LOW;
    if(number_count <= 8) {
      number_count = number_count + 1;
      number_1 = number_count;
    }
    else if (number_count > 8 && number_count <= 14) {
      number_count = number_count + 1;
      calculator_operator = number_count;
    }
    else {
      number_count = 0;
    }
  }
  else if(button1_State == LOW && digitalRead(buttonPin_1) == HIGH)
  {
    button1_State = HIGH;
  }

  lcd.cursor();
  String s_number1 = data[number_count];
  lcd.setCursor(16 - s_number1.length(),0);
  lcd.blink();
  lcd.print(s_number1);
  delay(100);

  if(button2_State == HIGH && digitalRead(buttonPin_2) == LOW) {
    deletePressed = false;
    button2_State = LOW;
    enter_button_click = enter_button_click + 1;
   
    if(s_number1.equals("S")){
      lcd.clear();
      evaluateMyExpression();
      lcd.blink();
      delay(1000);
    }
    else if(s_number1.equals("D")){
      deletePressed = true;
      int length = expression.length() -1;
      expression = expression.substring(0,length);
      if(length > 0) {
          lcd.clear();
          lcd.setCursor(16 - expression.length() - 1,0);
          lcd.print(expression);
          lcd.setCursor(16 - expression.length(),0);
          lcd.blink();
          delay(1000);
      }
    }
    else {
    expression += s_number1;
    if(s_number1.equals("+")){
      op = 0;
    }
     if(s_number1.equals("-")){
      op = 1;
    }
     if(s_number1.equals("*")){
      op = 2;
    }
     if(s_number1.equals("/")){
      op = 3;
    }
    if(!(deletePressed)){
    lcd.clear();
    lcd.setCursor(16 - expression.length() - 1, 0);
    lcd.print(expression);
    lcd.setCursor(16 - expression.length(),0);
    lcd.blink();
    delay(1000);
    }
    }  
  }

  else if(button2_State == LOW && digitalRead(buttonPin_2) == HIGH) {
    button2_State = HIGH;
  }
}

void evaluateMyExpression() {
   int operand1, operand2,result;
   String answer;
    char * pch;
    int i;
   char *cstr = new char[expression.length() + 1];
   strcpy(cstr, expression.c_str());
 
    switch(op){
        case 0:
            pch = strtok (cstr,"+");
            while (pch != NULL) {
              operands[i++]=pch;
              pch = strtok(NULL, "+");
            }
             operand1 =  atoi(operands[0].c_str());
             operand2 =  atoi(operands[1].c_str());
             result = operand1 + operand2;
            lcd.setCursor(16 - String(result).length() ,1);
            lcd .print(result);
            break;
        case 1:
            pch = strtok (cstr,"-");
            
            while (pch != NULL) {
              operands[i++]=pch;
              pch = strtok(NULL, "-");
            }
            operand1 =  atoi(operands[0].c_str());
             operand2 =  atoi(operands[1].c_str());
             result = operand1 - operand2;
            lcd.setCursor(16 - String(result).length() ,1);
            lcd .print(result);
            break;
        case 2:
            pch = strtok (cstr,"*");
            while (pch != NULL) {
              operands[i++]=pch;
              pch = strtok(NULL, "*");
            }
             operand1 =  atoi(operands[0].c_str());
             operand2 =  atoi(operands[1].c_str());
             result = operand1 * operand2;
            lcd.setCursor(16 - String(result).length() ,1);
            lcd .print(result);
            break;
        case 3:
            pch = strtok (cstr,"/");
            while (pch != NULL) {
              operands[i++]=pch;
              pch = strtok(NULL, "/");
            }
             operand1 =  atoi(operands[0].c_str());
             operand2 =  atoi(operands[1].c_str());
             if(operand2 != 0) {
              result = operand1 / operand2;
              answer = String(result);
             }
             else {
              answer = "invalid";
             }
            
            lcd.setCursor(16 - answer.length() ,1);
            lcd .print(answer);
            break;
            
            
    }
   
}


