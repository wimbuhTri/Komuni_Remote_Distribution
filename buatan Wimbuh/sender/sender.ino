char mystr[25]; //String data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  //Serial1.begin(9600); //komunikasi ke ESP8266
}

float value = 0;
void loop() {
  String param = "PARAMETER XCV:";
  
  for (int n=100; n<513; n++){
    value = n+0.01;
    String(param+value).toCharArray(mystr, sizeof(mystr));
    //mystr[sizeof(value)] = char(value);
    //Serial.println(mystr); // jangan print saat writing serial
    Serial.write(mystr,25); //Write the serial data
    //Serial.println(sizeof(mystr));
    delay(1000);
    
    }
  for (int m = 513; m>1; m--){
    value = m+0.01;
    
    String(param+value).toCharArray(mystr, sizeof(mystr));
    //mystr[sizeof(value)] = char(value);
    Serial.write(mystr,10); //Write the serial data
    //Serial.println(mystr); // jangan print saat writing serial
    delay(1000);
    }
}
