#include <PN532.h>
 
/*
 * Corrected MISO/MOSI/SCK for Mega from Jonathan Hogg (www.jonathanhogg.com)
 * SS is the same, due to NFC Shield schematic
 */
#define SS 10
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  #define MISO 50
  #define MOSI 51
  #define SCK 52
#else
  #define MISO 12
  #define MOSI 11
  #define SCK 13
#endif
 
PN532 nfc(SCK, MISO, MOSI, SS);
 
void setup(void) {
  Serial.begin(9600);
 
  nfc.begin();
 
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  Serial.print("Supports "); Serial.println(versiondata & 0xFF, HEX);
 
  // configure board to read RFID tags and cards
  nfc.SAMConfig();
}
 

void loop(void) {
    uint32_t id;
    // look for MiFare type cards
    id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);

    if (id != 0)
    {
        Serial.print("Read card #");
        Serial.println(id);
        Serial.println();

        uint8_t keys[]= {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};  // default key of a fresh card
        for(uint8_t blockn=0;blockn<64;blockn++) {
            if(nfc.authenticateBlock(1, id ,blockn,KEY_A,keys)) //authenticate block blockn
            {
                //if authentication successful
                uint8_t block[16];
                //read memory block blockn
                if(nfc.readMemoryBlock(1,blockn,block))
                {
                    //if read operation is successful
                    for(uint8_t i=0;i<16;i++)
                    {
                        //print memory block
                        Serial.print(block[i],HEX);
                        if(block[i] <= 0xF) //Data arrangement / beautify
                        {
                            Serial.print("  ");
                        }
                        else
                        {
                            Serial.print(" ");
                        }
                    }

                    Serial.print("| Block ");
                    if(blockn <= 9) //Data arrangement / beautify
                    {
                        Serial.print(" ");
                    }
                    Serial.print(blockn,DEC);
                    Serial.print(" | ");

                    if(blockn == 0)
                    {
                        Serial.println("Manufacturer Block");
                    }
                    else
                    {
                        if(((blockn + 1) % 4) == 0)
                        {
                            Serial.println("Sector Trailer");
                        }
                        else
                        {
                            Serial.println("Data Block");
                        }
                    }
                }
            }
        }
    }
    delay(2000);
}


