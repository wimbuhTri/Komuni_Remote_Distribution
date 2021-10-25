
#include <ModbusMaster.h>


// instantiate ModbusMaster object
ModbusMaster node;
int r_enable = 2;
int t_enable = 3;
char mystr[25]; //String data


void sendToESP(String parameter, String value){
  //send to ESP8266
  String(parameter+value).toCharArray(mystr, sizeof(mystr));   
  Serial1.write(mystr,25); //Write the serial data
  }

void setup()
{
  // use Serial (port 0); initialize Modbus communication baud rate
  Serial.begin(19200);
  Serial3.begin(9600);
  Serial1.begin(9600); //komunikasi ke ESP8266
  // communicate with Modbus slave ID 1 over Serial (port 3)
  node.begin(1, Serial3);
}


float value = 0;

void loop()
{
  delay (5000);
  uint8_t cnt;
  uint16_t data[100];
  uint32_t datal[100];
  uint32_t lw;
  float fval;
  uint8_t j,result;

  result = node.readHoldingRegisters(0x02,6);  // 40000
  if (result == node.ku8MBSuccess)
  {
    delay (1000);
    Serial.println("");
    Serial.println(" Hasil readHoldingRegisters(0x02,6)");
      for (j=1; j<6 ; j++)
      {
        data[j]=node.getResponseBuffer(j);
      }
    delay(1000);
    
    Serial.print("CT Secondary : ");  
    Serial.println(data[0]);
    Serial.println(data[0]);
    value = data[0];
    //String("CT Secondary:").toCharArray(mystr, sizeof(mystr));   
    //Serial1.write(mystr+data[0],25); //Write the serial data
	sendToESP("CT Secondary:", data[0])
    
    //*
    delay(100);
    Serial.print("CT Primary   : ");
    Serial.println(data[1]);
    sendToESP("CT Primary:", data[1])
    delay(100);
       
    Serial.print("PT Secondary : ");
    Serial.println(data[2]);
    sendToESP("PT Secondary:", data[2])
    delay(100);

    float finalFloatValue = 0;
    uint32_t tempVariable = 0;
    Serial.print("PT Primary   : ");
    tempVariable = data[3];
    tempVariable = tempVariable << 16;
    tempVariable = data[4] | (tempVariable ); ;
    Serial.println(tempVariable);
    sendToESP("PT Primary:", tempVariable)
    
    
    Serial.print("ID : ");
    Serial.println(data[5]);
    delay(100);
    Serial.println(data[6]);
    sendToESP("ID:", data[5]);
    sendToESP("", data[6]);
    Serial.println("....... step break ..........");
    Serial.println("");
    node.clearResponseBuffer();
    //*/
  }

// second phase
  Serial.println( "");
  uint8_t Count = 65;
  Serial.println( Count);
  ///*
  //    result = node.readHoldingRegisters(0,65);//*(0x00,Count);
  result = node.readInputRegisters(0x00,Count);//

  if (result == node.ku8MBSuccess)
  {
    Serial.println(" second part ");
    sendToESP("--second part--","");
    for (j=0; j<Count+1 ; j++)
    {
      datal[j]=node.getResponseBuffer(j);
    }
    float finalFloatValue = 0;

    uint32_t tempVariable = 0;
    tempVariable = datal[1] | 0x00000000;
    tempVariable = datal[0] | (tempVariable << 16); ;
    finalFloatValue = *(float*)& tempVariable ;

    Serial.print("Dalam volt phase A = ");
    Serial.println(finalFloatValue);
    sendToESP("Dalam volt phase A :",String(finalFloatValue));
    
    //Serial.println(datal[1]);
    //Serial.println(datal[0]);
    
    delay(1000);

    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[3] | 0x00000000;
    tempVariable = datal[2] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Dalam volt phase B = ");
    Serial.println(finalFloatValue);
    sendToESP("Dalam volt phase B:",String(finalFloatValue));
    //Serial.println(datal[3]);
    //Serial.println(datal[2]);
    delay (1000);
//2
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[5] | 0x00000000;
    tempVariable = datal[4] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Dalam volt phase c = ");
    Serial.println(finalFloatValue);
    sendToESP("Dalam volt phase C:",String(finalFloatValue));
    //Serial.println(datal[5]);
    //Serial.println(datal[4]);
    delay (1000);
//3
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[7] | 0x00000000;
    tempVariable = datal[6] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Average voltage LN = ");
    Serial.println(finalFloatValue);
    sendToESP("Average voltage LN:",String(finalFloatValue));
    //Serial.println(datal[7]);
    //Serial.println(datal[6]);
    Serial.println( "");
    delay (1000);
//4
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[9] | 0x00000000;
    tempVariable = datal[8] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("voltage V12: = ");
    Serial.println(finalFloatValue);
    sendToESP("voltage V12:",String(finalFloatValue));
    //Serial.println(datal[9]);
    //Serial.println(datal[8]);    
    delay (1000);
//5
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[11] | 0x00000000;
    tempVariable = datal[10] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("voltage V23: = ");
    Serial.println(finalFloatValue);
    sendToESP("voltage V23:",String(finalFloatValue));
    //Serial.println(datal[11]);
    //Serial.println(datal[10]);
    delay (1000);

//6
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[13] | 0x00000000;
    tempVariable = datal[12] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("voltage V31: = ");
    Serial.println(finalFloatValue);
    sendToESP("voltage V31:",String(finalFloatValue));
    //Serial.println(datal[13]);
    //Serial.println(datal[12]);
 
    delay (1000);
//7
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[15] | 0x00000000;
    tempVariable = datal[14] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("average voltage LL = ");
    Serial.println(finalFloatValue);
    sendToESP("average voltage LL:",String(finalFloatValue));
         Serial.println( "");
    //Serial.println(datal[15]);
    //Serial.println(datal[14]);
    delay (1000);
//8
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[17] | 0x00000000;
    tempVariable = datal[16] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Current I1 = ");
    Serial.println(finalFloatValue);
    sendToESP("Current I1:",String(finalFloatValue));
    delay (1000);
//9
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[19] | 0x00000000;
    tempVariable = datal[18] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Current I2 = ");
    Serial.println(finalFloatValue);
    sendToESP("Current I2:",String(finalFloatValue));
    delay (1000);
//10
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[21] | 0x00000000;
    tempVariable = datal[20] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Current I3 = ");
    delay (1000);
    sendToESP("Current I3:",String(finalFloatValue));
    Serial.println(finalFloatValue);
    


//11
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[23] | 0x00000000;
    tempVariable = datal[22] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Average Current I = ");
    Serial.println(finalFloatValue);
       Serial.println( ""); 
    sendToESP("Average Current I:",String(finalFloatValue));
    delay (1000);

//12
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[25] | 0x00000000;
    tempVariable = datal[24] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 1 (kWh)= ");
    Serial.println(finalFloatValue);
    sendToESP("Power 1 (kWh):",String(finalFloatValue));
    delay (1000);


//13
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[27] | 0x00000000;
    tempVariable = datal[26] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 2 (kWh)= ");
    Serial.println(finalFloatValue);
    sendToESP("Power 2 (kWh):",String(finalFloatValue));
    delay (1000);
    
//14
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[29] | 0x00000000;
    tempVariable = datal[28] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 3 (kWh)= ");
    Serial.println(finalFloatValue);
           Serial.println( ""); 
    sendToESP("Power 3 (kWh):",String(finalFloatValue));
    delay (1000);

//15
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[31] | 0x00000000;
    tempVariable = datal[30] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 1 (kVA)= ");
    Serial.println(finalFloatValue);
    sendToESP("Power 1 (kVA):",String(finalFloatValue));
    delay (1000);


//16
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[33] | 0x00000000;
    tempVariable = datal[32] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 2 (kVA)= ");
    Serial.println(finalFloatValue);
    sendToESP("Power 2 (kVA):",String(finalFloatValue));
    delay (1000);
    
//17
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[35] | 0x00000000;
    tempVariable = datal[34] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 3 (kVA)= ");
    Serial.println(finalFloatValue);
           Serial.println( ""); 
    sendToESP("Power 3 (kVA):",String(finalFloatValue));
    delay (1000);

//18
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[37] | 0x00000000;
    tempVariable = datal[36] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 1 (kVAr)= ");
    Serial.println(finalFloatValue);
    sendToESP("Power 1 (kVAr):",String(finalFloatValue));
    delay (1000);


//19
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[39] | 0x00000000;
    tempVariable = datal[38] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 2 (kVAr)= ");
    Serial.println(finalFloatValue);
    sendToESP("Power 2 (kVAr):",String(finalFloatValue));
    delay (1000);
    
//20
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[41] | 0x00000000;
    tempVariable = datal[40] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Power 3 (kVAr)= ");
    Serial.println(finalFloatValue);
           Serial.println( ""); 
    sendToESP("Power 3 (kVAr):",String(finalFloatValue));
    delay (1000);

//21
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[43] | 0x00000000;
    tempVariable = datal[42] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Total  (kW)= ");
    Serial.println(finalFloatValue);
    sendToESP("Total (kW):",String(finalFloatValue));
    delay (1000);


//22
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[45] | 0x00000000;
    tempVariable = datal[44] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Total (kVA)= ");
    Serial.println(finalFloatValue);
    sendToESP("Total (kVA):",String(finalFloatValue));
    delay (1000);
    
//23
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[47] | 0x00000000;
    tempVariable = datal[46] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("TOtal(kVAr)= ");
    Serial.println(finalFloatValue);
           Serial.println( ""); 
    sendToESP("Total (kVAr):",String(finalFloatValue));
    delay (1000);

//24
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[49] | 0x00000000;
    tempVariable = datal[48] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("PF1 = ");
    Serial.println(finalFloatValue);
    sendToESP("PF1:",String(finalFloatValue));
    delay (1000);


//25
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[51] | 0x00000000;
    tempVariable = datal[50] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("PF2 = ");
    Serial.println(finalFloatValue);
    sendToESP("PF2:",String(finalFloatValue));
    delay (1000);
    
//26
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[53] | 0x00000000;
    tempVariable = datal[52] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("PF3 = ");
    Serial.println(finalFloatValue);
    sendToESP("PF3:",String(finalFloatValue));
    delay (1000);

//27
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[55] | 0x00000000;
    tempVariable = datal[54] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Average PF = ");
    Serial.println(finalFloatValue);
           Serial.println( ""); 
    sendToESP("Average PF:",String(finalFloatValue));
    delay (1000);
    
//28
    finalFloatValue = 0 ;
    tempVariable = 0;
    tempVariable = datal[57] | 0x00000000;
    tempVariable = datal[56] | (tempVariable << 16);
    finalFloatValue = *(float*)&tempVariable;
    Serial.print("Frequency = ");
    Serial.println(finalFloatValue);
           Serial.println( ""); 
    sendToESP("Frequency:",String(finalFloatValue));
    delay (1000);

    
  }
  //*/
}
