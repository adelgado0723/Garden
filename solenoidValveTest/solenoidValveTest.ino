int solenoidPin1 = 7;
int solenoidPin2 = 8; //This is the output pin on the Arduino we are using

void setup() {
  // put your setup code here, to run once:
pinMode(solenoidPin1, OUTPUT);
pinMode(solenoidPin2, OUTPUT);//Sets the pin as an output
}

void loop() {
  // put your main code here, to run repeatedly:  
  digitalWrite(solenoidPin1, HIGH);    //Switch Solenoid ON
  
   digitalWrite(solenoidPin2, HIGH);
   delay(1000);                      //Wait 1 Second
  digitalWrite(solenoidPin1, LOW); 
   digitalWrite(solenoidPin2, LOW);//Switch Solenoid OFF
  delay(1000);                      //Wait 1 Second
  digitalWrite(solenoidPin1, HIGH);    //Switch Solenoid ON
  
   
   delay(1000);                      //Wait 1 Second
  digitalWrite(solenoidPin1, LOW); 
   digitalWrite(solenoidPin2, HIGH);//Switch Solenoid OFF
  delay(1000);                      //Wait 1 Second
}


