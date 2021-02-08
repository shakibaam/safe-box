#include<Keypad.h> // KEYPAD LIBRARY FOR KEYPAD INTERFACING 
#include<LiquidCrystal.h> // LIBRARY FOR LCD INTERFACING
#include<Servo.h>// LIBRARY FOR SERVO MOTOR
//#include<String.h>
//#define buzzer 24 // DEFINING PIN FOR BUZZER.

LiquidCrystal lcd(14, 15, 16, 17, 18, 19); // PINS FOR LCD

char keys[4][4] = { // LAYOUT OF KEYPAD

  {'7', '8', '9', 'C'},
  {'4', '5', '6', 'B'},
  {'1', '2', '3', 'A'},
  {'*', '0', '#', 'D'}
};

byte rowPin[4] = {4, 5, 6, 7}; // ROW PINS OF KEYPAD
byte colPin[4] = {8, 2, 10, 11}; // COLUMN PINS OF KEYPAD

Servo servo_Motor;
int password = 159;  // SETTING DEFAULT PASSWORD.
int timer=10;
String str="";
int flag = 0;
int second;
int lock;
char key;



int redPin = 12; // DEFINING PIN FOR RED LED
int greenPin = 13; // DEFINING PIN FOR GREEN LED

Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, 4, 4);
// MAPPING THE KEYPAD.


int total = 0; // VARIABLE TO DETERMINE THE NUMBER OF WRONG ATTEMPTS.

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("DOOR LOCK SYSTEM");
  lcd.setCursor(0, 2);
  lcd.print("       BY:");
  delay(2000);
  lcd.clear();
  lcd.print("shakiba");
  lcd.setCursor(0, 2);
  lcd.print("    amirshahi");
  delay(2000);
  lcd.clear();
  servo_Motor.attach(9);
  setLocked(0);
  lock = 0;
  delay(1000);

  pinMode(24, OUTPUT);
}

void loop()
{


  if (lock == 1) {




    for (int i = 0; i < timer; i++) {

      if (digitalRead(20) == HIGH) {

       

        lcd.clear();
        delay(1000);
        lcd.print("closing");

        setLocked(0);
        lock = 0;
        
        digitalWrite(20,LOW);
        flag=1;
      

        break;


        //      }




      }






      else  {
        lcd.clear();
        lcd.print(i);
        delay(1000);

      }



    }

    if(flag==0){

    setLocked(0);}





  }

  if (lock == 0) {


    


    lcd.clear();
 
    lcd.print("Enter Password:");
    delay(100);

    char pressed = keypad.getKey(); 

if(pressed){


  if (pressed=='*' ){
    
    password=str.toInt();
    lcd.clear();
    lcd.print("new password");
    delay(1000);
    }

    if(pressed=='D'){
      timer=str.toInt();
    lcd.clear();
    lcd.print("new timer");
    delay(1000);
      
     }


     if (pressed=='*' ){
    
    password=str.toInt();
    lcd.clear();
    lcd.print("new password");
    delay(1000);
    }
    

       if (pressed=='#' ){


        if(str.toInt()!=password){


           lcd.clear();
          lcd.print("WRONG");
          lcd.setCursor(5, 2);
          lcd.print("PASSWORD");
          delay(2000);
        
        }

          else if(str.toInt()==password){

           lcd.clear();
          lcd.print("PASSWORD");
          lcd.setCursor(6, 2);
          lcd.print("ACCEPTED");
          delay(2000);
          lcd.clear();
          lcd.print("Door Open");


          delay(2000);
          setLocked(1);
        
        }
      }

    


        else{

          lcd.setCursor(0,1);
          lcd.print(pressed);
          delay(1000);
          str+=pressed;
          }
    
}
    
   




  }
}

void setLocked(int locked)// FUNCTION TO CHANGE STATUS OF SERVO MOTOR.
{
  if (locked == 1)
  {

    lock = 1;






    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    delay(2000);
    digitalWrite(greenPin, LOW);
    tone(24, 1000); // Send 1KHz sound signal...
    delay(1000);

    noTone(24);
    servo_Motor.attach(9);
    servo_Motor.write(0);

    delay(1000);
    servo_Motor.detach();
    delay(1000);

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print( "door is open");

   








  }

  else if (locked == 0)
  {

    lock = 0;




    digitalWrite(redPin, HIGH);

    delay(2000);
    digitalWrite(redPin, LOW);
    //          delay(2000);
    delay(1000);

    tone(24, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(24);
    servo_Motor.attach(9);
    servo_Motor.write(90);
    delay(1000);
    servo_Motor.detach();
    //           delay(1000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("door is close  ");
  }
}
