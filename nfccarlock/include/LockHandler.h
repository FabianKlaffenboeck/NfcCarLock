#include <Arduino.h>
#include <Defines.h>
#include <EEPROM.h>

bool IsLocked = false;

void initCarLock()
{
  byte State = EEPROM.read(CarStateAddr);
  if (State == 0)
  {
    IsLocked = false;
  }
  if (State == 1)
  {
    IsLocked = true;
  }
}

void Lockhandler()
{
  if (IsLocked)
  {
    digitalWrite(UnLockPin, HIGH);
    delay(DelayTime);
    digitalWrite(UnLockPin, LOW);
    IsLocked = false;
  }else{
    digitalWrite(LockPin, HIGH);
    delay(DelayTime);
    digitalWrite(LockPin, LOW);
    IsLocked = true;
  }
  
  EEPROM.write(CarStateAddr, IsLocked);
  EEPROM.commit();

#ifdef LogLv4
  if (IsLocked)
  {
    Serial.println("Car Is Locked");
  }
  else
  {
    Serial.println("Car Is unLocked");
  }
#endif
}