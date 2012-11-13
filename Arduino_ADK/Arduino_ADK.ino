#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo gyro;  // create servo object to control a servo 
 

#define  LED1_RED       9
#define  LED1_GREEN     4
#define  LED1_BLUE      3

#define  LED2_RED       5
#define  LED2_GREEN     7
#define  LED2_BLUE      6

#define  LED3_RED       8
#define  LED3_GREEN     10
#define  LED3_BLUE      13

#define  RELAY1         A0
#define  RELAY2         A1

#define  BUTTON1        A2
#define  BUTTON2        A3
#define  BUTTON3        A4

#define  LIGHT_SENSOR   A5


AndroidAccessory acc("Google, Inc.",            // Manufacturer
                     "DemoKit",                 // Model
                     "DemoKit Arduino Board",   // Description
                     "1.0",                     // Version
                     "http://www.android.com",  // URI
                     "0000000012345678");       // Serial

void setup();
void loop();

void init_buttons()
{
	pinMode(BUTTON1, INPUT);
	pinMode(BUTTON2, INPUT);
	pinMode(BUTTON3, INPUT);
	
	// enable the internal pullups
	digitalWrite(BUTTON1, HIGH);
	digitalWrite(BUTTON2, HIGH);
	digitalWrite(BUTTON3, HIGH);
	
}

void init_relays()
{
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
}

void init_led()
{
        digitalWrite(LED1_RED, 1);
	digitalWrite(LED1_GREEN, 1);
	digitalWrite(LED1_BLUE, 1);
	
        pinMode(LED1_RED, OUTPUT);
	pinMode(LED1_GREEN, OUTPUT);
	pinMode(LED1_BLUE, OUTPUT);

	digitalWrite(LED2_RED, 1);
	digitalWrite(LED2_GREEN, 1);
	digitalWrite(LED2_BLUE, 1);

	pinMode(LED2_RED, OUTPUT);
	pinMode(LED2_GREEN, OUTPUT);
	pinMode(LED2_BLUE, OUTPUT);

	digitalWrite(LED3_RED, 1);
	digitalWrite(LED3_GREEN, 1);
	digitalWrite(LED3_BLUE, 1);

	pinMode(LED3_RED, OUTPUT);
	pinMode(LED3_GREEN, OUTPUT);
	pinMode(LED3_BLUE, OUTPUT);
}

byte b1, b2, b3;

void setup()
{
        Serial.begin(115200);
        Serial.print("\r\nADK Started\r\n");
myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
        init_led();
        init_relays();
        init_buttons();
  
  	b1 = digitalRead(BUTTON1);
	b2 = digitalRead(BUTTON2);
	b3 = digitalRead(BUTTON3);

  // Power On Android Accessory interface and init USB controller
  acc.powerOn();
  analogWrite(LED1_RED, 0);
  analogWrite(LED1_GREEN, 0);
  analogWrite(LED1_BLUE, 0);
  analogWrite(LED2_RED, 0);
  analogWrite(LED2_GREEN, 0);
  analogWrite(LED2_BLUE, 0);
  analogWrite(LED3_RED, 0);
  analogWrite(LED3_GREEN, 0);
  analogWrite(LED3_BLUE, 0);
}

void loop()
{
  byte msg[3];
  static byte count = 0;
  
  if (acc.isConnected()) {
    int len = acc.read(msg, sizeof(msg), 1);
    byte b;
        uint16_t val;
    
    if (len > 0) {
            if (msg[0] == 0x2) {
                    if (msg[1] == 0x0) 
                        {
                          int val = map(0 + msg[2], 0, 255, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
                          Serial.println(val);
                          myservo.write(val);  
                          delay(36);
                        }
                    else if (msg[1] == 0x1)
	                                analogWrite(LED1_GREEN, 0 + msg[2]);
	                        else if (msg[1] == 0x2)
	                                analogWrite(LED1_BLUE, 0 + msg[2]);
				else if (msg[1] == 0x3)
					analogWrite(LED2_RED, 0 + msg[2]);
				else if (msg[1] == 0x4)
					analogWrite(LED2_GREEN, 0 + msg[2]);
				else if (msg[1] == 0x5)
					analogWrite(LED2_BLUE, 0 + msg[2]);
				else if (msg[1] == 0x6)
					analogWrite(LED3_RED, 0 + msg[2]);
				else if (msg[1] == 0x7)
					analogWrite(LED3_GREEN, 0 + msg[2]);
				else if (msg[1] == 0x8)
					analogWrite(LED3_BLUE, 0 + msg[2]);
			} else if (msg[0] == 0x3) {
				if (msg[1] == 0x0)
					digitalWrite(RELAY1, msg[2] ? HIGH : LOW);
				else if (msg[1] == 0x1)
					digitalWrite(RELAY2, msg[2] ? HIGH : LOW);
			}
          }
          
          msg[0] = 0x1;

		b = digitalRead(BUTTON1);
		if (b != b1) {
			msg[1] = 0;
			msg[2] = b ? 0 : 1;
			acc.write(msg, 3);
			b1 = b;
		}

		b = digitalRead(BUTTON2);
		if (b != b2) {
			msg[1] = 1;
			msg[2] = b ? 0 : 1;
			acc.write(msg, 3);
			b2 = b;
		}

		b = digitalRead(BUTTON3);
		if (b != b3) {
			msg[1] = 2;
			msg[2] = b ? 0 : 1;
			acc.write(msg, 3);
			b3 = b;
		}

		switch (count++ % 0x10) {

		case 0x4:
			val = analogRead(LIGHT_SENSOR);
			msg[0] = 0x5;
			msg[1] = val >> 8;
			msg[2] = val & 0xff;
			acc.write(msg, 3);
			break;

    }
  }

  delay(10);
}
