#include <VarSpeedServo.h>
 
VarSpeedServo gimbal;
VarSpeedServo gyro; 

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
        int amount2 = map(amount, 0, 255, 90,0);
        gimbal.slowmove(amount2, amount);
        delay(300);
        gimbal.slowmove(90, 15);
}

void steer_right(int amount)
{
        Serial.print("Rechts");
        int amount2 = map(amount, 0, 255, 90,179);
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
        delay(5000);
        gyro_spinup(100);
        delay(2000);
        power(12);
}

void loop()
{
        delay(2000);
        steer_left(70);
        delay(2000);
        steer_right(70);
// Mystery delay....
delay(10);
}
