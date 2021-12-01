#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define cone true    //set to true when uploading to the cone arduinos
                     

uint8_t transceiverID = 2;

RF24 radio(9, 10); 

uint8_t address[][6] = {"FSAER", "FSAET"}; //Pipe address

unsigned int count = 0;

typedef struct {
  uint8_t id = transceiverID;
  unsigned long val;
  uint8_t num = count;
} PACKET;

PACKET payload; 

unsigned long start = 0;
unsigned long temp = 0;

uint8_t mostRecent1 = 100;
uint8_t mostRecent2 = 100;

void setup() 
{
  Serial.begin(9600);  //open serial port
  
  while (!radio.begin()) 
  {
    Serial.println("Radio disconnected");
    delay(3000);
  }
  
  //set to an arbitrary value 0-125 to avoid interference with others
  radio.setChannel(76);
  
  radio.setPALevel(RF24_PA_HIGH); 
 
  radio.setPayloadSize(sizeof(payload));

  

  radio.setRetries(0, 1);
  
  if (cone) 
  {
    pinMode(3, INPUT_PULLUP); //ir sensor input pin    

    pinMode(LED_BUILTIN, OUTPUT); //default arduino led
    
    radio.openWritingPipe(address[1]);
    radio.openReadingPipe(1, address[0]);       
    radio.startListening();  // put radio in RX mode
  } 
  else //receiver
  {
    pinMode(4, INPUT_PULLUP); //on switch
    while (!Serial)
    {
      ;  //do nothing until the serial connection is made
    }

    
    
    Serial.println("SAE Connected");  //the handshake keyword that tells the python script this is the receiver

    
    radio.openWritingPipe(address[0]);
    radio.openReadingPipe(1, address[1]);   
    radio.startListening(); // put radio in RX mode
  }
}

void loop() 
{    
  start:
  if (cone) 
  {         
    if (digitalRead(3)==HIGH) //if the signal was tripped
    {                  
      start = millis();
      radio.stopListening();
      payload.id = transceiverID;
      payload.val = millis()-start;
      payload.num = count;      
      digitalWrite(LED_BUILTIN, HIGH);
      while(!radio.write(&payload, sizeof(payload)))
      {
        Serial.println("Send failed");
        //delay(10);
        payload.val = millis()-start;
      }      
      digitalWrite(LED_BUILTIN, LOW);
      count++;      
      Serial.println("Data sent");          
      Serial.print("Sent: ");
      Serial.println(payload.val);      
      radio.startListening();
      while (millis()-start < 3000) //wait 3 seconds to avoid accidentally sending multiple signals for one pass
      {
        ;        
      }
    }
  } 
  else //receiver
  { 
    if (radio.available()) 
    {   
      uint8_t bytes = radio.getPayloadSize(); //size of incoming data
      radio.read(&payload, bytes);            //read to the buffer 'payload'                        
      if (digitalRead(4)==LOW)              //on switch must be active
      {  
        if (payload.id == 1)
        {
          if (mostRecent1 != payload.num)
          {
            mostRecent1 = payload.num;
          }
          else
          {
            goto start;
          }
        }
        else if (payload.id == 2)
        {
          if (mostRecent2 != payload.num)
          {
            mostRecent2 = payload.num;                  
          }
          else
          {
            goto start;
          }
        }
        else
        {
          goto start;
        }
        Serial.print("T: ");       //send start signal to datalogger
        Serial.print(payload.val);
        Serial.print(", From ");
        Serial.println(payload.id); 
      }
    }
  }
}
