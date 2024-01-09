#include <SPI.h>
#include <MFRC522.h>
#include <Defines.h>
#include <EEPROM.h>
#include <LockHandler.h>
#include <LogStuff.h>

MFRC522 rfid(SDA_Pin, RST_PIN);
MFRC522::MIFARE_Key key;
int ErrorCounter = 0;
byte KeySize = 0;
unsigned long timelastToken = 0;
unsigned long timeLastRead = 0;

byte correctKey[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool LoadKeyFromEeprom()
{
    KeySize = EEPROM.read(KeySizeAddr);
    if (KeySize > 0)
    {
        for (byte i = 0; i < KeySize; i++)
        {
            correctKey[i] = EEPROM.read(i + KeyDataStart);
        }
#ifdef Log
        Serial.println("Key:");
        printHex(correctKey, 16);
        Serial.println("KeyLenth:");
        Serial.println(KeySize);
#endif
        return true;
    }
    return false;
}

bool LearnKey()
{
#ifdef LogLv2
    Serial.println("Pleas hold a Key to learn near by");
#endif
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
    {
        KeySize = rfid.uid.size;
        EEPROM.write(KeySizeAddr, KeySize);
        EEPROM.commit();

        if (rfid.uid.size > 0)
        {
            for (byte i = 0; i < KeySize; i++)
            {
                EEPROM.write(i + KeyDataStart, rfid.uid.uidByte[i]);
            }
            EEPROM.commit();

            rfid.PICC_HaltA();
            rfid.PCD_StopCrypto1();
#ifdef LogLv2
            Serial.println("Learned Key");
#endif
            return true;
        }
    }
    return false;
}

bool ValidateKey(byte *buffer, byte bufferSize)
{
#ifdef Log
    Serial.println();
    Serial.println("Key: ");
    printHex(buffer, bufferSize);
    Serial.println("StroredKey: ");
    printHex(correctKey, KeySize);
    Serial.print("keyLenth: ");
    Serial.println(KeySize);
#endif

    for (byte i = 0; i < KeySize; i++)
    {
        if (!(buffer[i] == correctKey[i]))
        {
#ifdef Log
            Serial.print("False Key");
#endif
            ErrorCounter = ErrorCounter + ErrorWeight;
            return false;
        }
    }
#ifdef Log
    Serial.print("Correct Key");
#endif

    if (ErrorCounter > 0)
    {
        ErrorCounter--;
    }
    else
    {
        ErrorCounter = 0;
    }

    Lockhandler();
    return true;
}

byte HandleNFCCom(void)
{
    // TODO reading to fast slow reading interval down
    if (ErrorCounter >= ErrorThreshold)
    {
        rfid.PCD_SoftPowerDown();
        rfid.PCD_AntennaOff();
#ifdef LogLv3
        Serial.println("Error");
#endif
        return ERROR_TryedToOften;
    }
    if (millis() - timeLastRead > ReadDelayTime)
    {
        if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
        {
            if (millis() - timelastToken < waitingTimeToToggle)
            {
#ifdef LogLv3
                Serial.println("To Fast Key read");
#endif
                return ERROR_TooFast;
            }
            ValidateKey(rfid.uid.uidByte, rfid.uid.size);
            timelastToken = millis();
            rfid.PICC_HaltA();
            rfid.PCD_StopCrypto1();
        }
    }
    if (rfid.PCD_PerformSelfTest())
    {
        return OK;
    }
    return ERROR_Unspe;
}

void NfcBegin()
{
    rfid.PCD_Init();
    rfid.PCD_SetRegisterBitMask(rfid.RFCfgReg, (0x07 << 4));
    while (!LoadKeyFromEeprom())
    {
        LearnKey();
    }
}