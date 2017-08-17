
//LCD1602
//You should now see your LCD1602 display the flowing characters "SUNFOUNDER" and "hello, world"
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7

#include <LiquidCrystal.h>// include the library code
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-up resistor

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;


char array2[] = "This is the Main Menu"; //the string to print on the LCD
char array1[] = "Time Temperature"; //the string to print on the LCD
String array3 = "Sunlight"; //the string to print on the LCD
char array4[] = "Daily Report"; //the string to print on the LCD
String array5 = "Soil Moisture"; //the string to print on the LCD
int inputArray[100];

int tim = 400; //the value of delay time
// initialize the library with the numbers of the interface pins
const int keyPin = 2; //the number of the key pin
static boolean isLongFormat = false;
int thermistor = A0;
int soil = A1;
int photo = A2;

/*********************************************************/
void setup()
{
  pinMode(keyPin, INPUT); //initialize the key pin as input
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  Serial.begin(9600);
      Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  //setTime(6, 27, 30, 9, 4, 17);

}
/*********************************************************/
void loop()
{
  // int counter = 1;
  char a = 'a';

  //switch(counter){

  // case 1:

  do {
    lcd.clear();
    lcd.setCursor(0,0); // set the cursor to column 15, line 0
    DateTime now = RTC.now(); 
    lcd.print(now.year(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    lcd.print(' ');
    lcd.setCursor(0,2); // set the cursor to column 15, line 0
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
   // lcd.println(); 
    // if(counter>1)
    //  break;
    // set the cursor to column 0, line 0

    //digitalClockDisplay();
    delay(tim);
  } while (digitalRead(keyPin) == LOW);
  lcd.clear();
  /* for (int positionCounter2 = 0; positionCounter2 < sizeof(array2) / sizeof(a)-1; positionCounter2++)
    {
      lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
      lcd.print(array2[positionCounter2]); // Print a message to the LCD.
      delay(tim); //wait for 250 microseconds
      if(digitalRead(keyPin) ==HIGH)
        break;

    }*/
  lcd.clear();

  do {
    //read thermistor value
    //
    //
    int a = getReading(thermistor);
    //the calculating formula of temperature
    float tempC = beta / (log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
    float tempF = 1.8 * tempC + 32.0;
    lcd.setCursor(0, 0); // set the cursor to column 0, line 0
    lcd.print("Temp: ");// Print a message of "Temp: "to the LCD.
    // Print a centigrade temperature to the LCD.
    lcd.print(tempC);
    // Print the unit of the centigrade temperature to the LCD.
    lcd.print(char(223));//print the unit" ℃ "
    lcd.print("C");
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1); // set the cursor to column 0, line 1
    lcd.print("Fahr: ");
    lcd.print(tempF);// Print a Fahrenheit temperature to the LCD.
    lcd.print(" F"); // Print the unit of the Fahrenheit temperature to the LCD.
    delay(tim);

  } while (digitalRead(keyPin) == LOW);

  lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.


  //  case2:
  //soil sensor
  int sensorValue;

    lcd.setCursor(0, 0); // set the cursor to column 15, line 0
    lcd.print(array5); // Print a message to the LCD.


  do {
    lcd.setCursor(0, 1);

    //if(counter == 5){
    sensorValue = getReading(soil);
    //  counter = 0;
    lcd.print(sensorValue);
    //}
    delay(tim);

    //counter++;
  } while (digitalRead(keyPin) == LOW);

  // light sensor
    lcd.clear();  
    lcd.setCursor(0, 0); // set the cursor to column 15, line 0
    lcd.print(array3); // Print a message to the LCD.
    
  do {
    
    lcd.setCursor(0, 1);
    sensorValue = getReading(photo);
    lcd.print(sensorValue);
    delay(tim); //wait for 250 microseconds

  } while (digitalRead(keyPin) == LOW);

  //case 4:
  do {

    lcd.setCursor(15, 0); // set the cursor to column 15, line 0
    for ( int positionCounter4 = 0; positionCounter4 < sizeof(array4) / sizeof(a) - 1; positionCounter4++)
    {
      lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
      lcd.print(array4[positionCounter4]); // Print a message to the LCD.
      delay(tim); //wait for 250 microseconds
      if (digitalRead(keyPin) == HIGH)
        break;

    }
    lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.

  } while (digitalRead(keyPin) == LOW);
  // end switch

}


void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  lcd.print(":");
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}


int getReading(int analogIn) {
  for (int i = 0; i < (sizeof(inputArray) / sizeof(int)); i++) {
  inputArray[i] = analogRead(analogIn);
  Serial.print("Reading... ");
  Serial.print( inputArray[i]);
  Serial.println();
  }
  int average = averageArray(inputArray);
  
  Serial.print("Average: ");
  Serial.print(average);
  Serial.println();
  int variance = 0;
  int dif;  // x - xbar
  for (int i = 0; i < (sizeof(inputArray) / sizeof(int)); i++) {
    dif = dif + sq(inputArray[i] - average);
  }
  variance = dif / ((sizeof(inputArray) / sizeof(int)) - 1);
  Serial.print("Variance: ");
  Serial.print(variance);
  Serial.println();
  int stDev = sqrt(variance);
  Serial.print("Stndard Deviation: ");
  Serial.print(stDev);
  Serial.println();
  //smoothing
  int sum = 0;
  int n = 0;
  for (int i = 0; i < (sizeof(inputArray) / sizeof(int)); i++) {
    if (inputArray[i] > (average + (3 * stDev)) || inputArray[i] < (average - (3 * stDev))) {
       inputArray[i] = average;
     }
         sum = sum + inputArray[i];
         n++;
  }
  Serial.print("Smoothed: ");
  Serial.print(sum /(sizeof(inputArray) / sizeof(int)) );
  Serial.println();
  return (sum /(sizeof(inputArray) / sizeof(int)) );

}

int averageArray(int arr[100]){
  int sumOfArray = 0;
  for (int i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
      sumOfArray = sumOfArray + arr[i];
  }
  return(sumOfArray / (sizeof(arr) / sizeof(int)));

}

