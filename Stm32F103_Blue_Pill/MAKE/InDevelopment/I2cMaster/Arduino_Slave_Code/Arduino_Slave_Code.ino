//Arduino code for the blue pill
#include <Wire.h>

#define LEDPIN 13
#define BUTTONPIN 6
#define SLAVEADDRESS 0x8

byte sendData = 0;

void setup()
{
pinMode(LEDPIN,OUTPUT);
Wire.begin(SLAVEADDRESS);
Wire.onReceive(receiveFun);
Wire.onRequest(requestFun);
}

void loop()
{
delay(100);
}

void receiveFun (int bytes)
{
byte recvData = Wire.read();

if (recvData == 1)
{
digitalWrite(LEDPIN,HIGH);
}
else
{
digitalWrite(LEDPIN,LOW);
}
delay(500);

}

void requestFun()
{
int buttonValue = digitalRead(BUTTONPIN);
if (buttonValue == HIGH)
{
sendData = 1;
}
else
{
sendData = 0;
}
Wire.write(sendData);
}
