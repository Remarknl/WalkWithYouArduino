#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>
#include <VarSpeedServo.h>
 
VarSpeedServo gimbal;
VarSpeedServo gyro; 

AndroidAccessory GyroGuide("WalkWithYou",                     // Manufacturer
                           "GyroGuide",                       // Model
                           "Gyroscopic controlled navigation",// Description
                           "0.1",                             // Version
                           "http://www.hu.nl",                // URI
                           "0000000012345678");                     // Serial

void gyro_spinup(int powerr)
{      
  Serial.print("Spin up to: ");
  Serial.println(powerr);
  gyro.attach(6);
  gyro.slowmove(0, 0);
  delay(2000);
  // Langzaam optrekken zodat gebruiker het wiel kan aanslingeren
  gyro.slowmove(70, 120);
  power(powerr);
}

void gyro_stop()
{
  Serial.print("Stop");
  gyro.detach();
}

void steer_left(int amount)
{
        Serial.print("Links");
        int amount2 = map(amount, 0, 255, 90,45);
        gimbal.slowmove(amount2, amount);
        delay(300);
        gimbal.slowmove(90, 15);
}

void steer_right(int amount)
{
        Serial.print("Rechts");
        int amount2 = map(amount, 0, 255, 90,135);
        gimbal.slowmove(amount2, amount);
        delay(300);
        gimbal.slowmove(90, 15);
}

void power(int setting)
{
  Serial.print("Power");
  Serial.println(setting);
  switch(setting)
  {
    case 0:
      gyro.slowmove(67, 5);
      break;
    case 1:
      gyro.slowmove(72, 5);
      break;
    case 2:
      gyro.slowmove(77, 5);
      break;
    case 3:
      gyro.slowmove(82, 5);
      break;
    case 4:
      gyro.slowmove(87, 5);
      break;
    case 5:
      gyro.slowmove(92, 5);
      break;
    case 6:
      gyro.slowmove(97, 5);
      break;
    case 7:
      gyro.slowmove(102, 5);
      break;
    case 8:
      gyro.slowmove(107, 5);
      break;
    case 9:
      gyro.slowmove(112, 5);
      break;
    case 10:
      gyro.slowmove(117, 5);
      break;
    case 11:
      gyro.slowmove(127, 5);
      break;
    case 12:
      gyro.slowmove(179, 5);
      break;
  }
}

void setup()
{
        
        Serial.begin(9200);
        Serial.print("\r\nADK Started\r\n");
        
        // Pin 5 en 6 worden gebruikt om de SPI pins vrij te houden voor het gebruik met het NFC shield.
        gimbal.attach(5);
        
        gimbal.slowmove(90, 15);
        GyroGuide.powerOn();
}

void loop()
{
        byte SerialData[3];
        static byte count = 0;
  
        if (GyroGuide.isConnected())
        {
                int length = GyroGuide.read(SerialData, sizeof(SerialData), 1);
                if (length > 0)
                {
                        Serial.print("SerialData is ");
                        Serial.print(SerialData[0]);
                        Serial.print(" en ");
                        Serial.print(SerialData[1]);
                        Serial.print(" en ");
                        Serial.println(SerialData[2]);
                        if (SerialData[0] == 0x2)
                        {
                                switch (SerialData[1])
                                {
                                  case 0x0:
                                    steer_left(0 + SerialData[2]);
                                    break;
                                  case 0x1:
                                    steer_right(0 + SerialData[2]);
                                    break;
                                  case 0x2:
                                    power(0 + SerialData[2]);
                                    break;
                                  case 0x3:
                                    gyro_spinup(0 + SerialData[2]);
                                    break;
                                  case 0x4:
                                    gyro_stop();
                                    break;
                                }
                        }
                        SerialData[0] = 0x1;
                }
        }
// Mystery delay....
delay(10);
}
