#ifndef DEFINED_H
#define DEFINED_H

#define Log // shows lowest level of information
#define LogLv2 // Learning a new key
#define LogLv3 // Show high level errro of kery reading
#define LogLv4 //Shows Lock state
#define Reset

#define irqPin 5
#define SDA_Pin 21
#define RST_PIN 17

#define LockPin 24
#define UnLockPin 25

#define DelayTime 100
#define ReadDelayTime 300
#define waitingTimeToToggle 1000

#define EEPROM_SIZE 4096

// basicly the error is handles by a dripping bucket system.
// one correct recived massage has a weight of -1 whyle a bad massage has a weight of standar 2 (can be ajusted).
// When too much erros acured then no nfc tag will be read again until a reeboot of the system.
#define ErrorWeight 2
#define ErrorThreshold 20

// Memory Layout
// Address: 0 = CarState (Locked(1)/UnLocked(2))
// Address: 1 =
// Address: 2 = allowed Key is stored if 1
// Address: 3-19 = KeyData
#define CarStateAddr 0
#define undefined 1
#define KeySizeAddr 2
#define KeyDataStart 3


//NFC Statuscodes
#define OK 0
#define ERROR_Unspe 1
#define ERROR_TooFast 2
#define ERROR_TryedToOften 3

#endif
