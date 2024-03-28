#include <Arduino.h>
#include <Defines.h>
#include <EEPROM.h>
#include <HandleNFC.h>

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  EEPROM.begin(EEPROM_SIZE);

#ifdef Reset
  for (int i = 0; i < 100; i++)
  {
    EEPROM.write(i, 0);
    Serial.println(i);
  }
  Serial.println("EEPROM Clear");
#endif

  NfcBegin();
  initCarLock();
}

void loop()
{
  byte handleResp = HandleNFCCom();
  if (handleResp == ERROR_TryedToOften || handleResp == ERROR_Unspe)
  {
    Serial.println("emergany unlock");
  }
}