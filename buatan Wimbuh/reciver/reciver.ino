void setup(){
  Serial.begin(9600);
//inisiasi input dan output pin
/*
pinMode(D1,OUTPUT);
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
pinMode(D4,OUTPUT);
pinMode(D5,OUTPUT);
*/
}

char mystr[25]; //Initialized variable to store recieved data
void loop(){
Serial.readBytes(mystr,25); //Read the serial data and store in var
Serial.println(mystr); //Print data on Serial Monitor
delay(500);
  

}
