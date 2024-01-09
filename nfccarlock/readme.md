# Security  

The Code in this Project is not considerd to be safty critical because it only interfaces wirelessly wia a pre existing controller with the cars Locking System.  

---

## Considerations :  

Here are listed possible security risks that can cause problems and the corresponding section explaining the countermeasures that were taken: 

1. Theft of the Car => Problems with general functionality
2. Locking of the Car whyle driving => Problems with general functionality
3. Car doesnt get unlocked when it should => escape possibilities
4. Controller drawing to much currant so that the battery gets empty whyle not driving. => electrical problems

---

## problems with general functionality:
it is not possible to performe a brought force attack becouse after 10 wrong Keys (this is configurable) the nfc turns off. and the only way to athentificate is via a web page that is hosted on the ESP32.
The worst thing that can happen in this sate is that it is not possible to unlock the car via the NFC chip. in this case a normal pysical key hase to be used.

---


## escape possibilities:
This product is particularly suitable for older vehicles that still have a manual locking system that can be operated whyle beeing inside the car.  
If it is not possible to unlock the car while sitting inside, this product is not suitable for this application.

---

## electrical problems:
When the defice is drawing to much currant from the car battery then it is possible taht the car wont start.
A fire hazard is not given because the currant is limmited by a fuse on the ESP32.
Errors in the electrical wiring are not accounted fore because the person installing the system is accountable for a correct and save electrical wiring.  

---


## Pinout:
|  RC522       | ESP32    |
| ------------ | -------- |
|3.3v          |3.3v      |
|rst           |17        |
|GND           |GND       |
|IRQ           |5         |
|MISO          |19        |
|MOSI          |23        |
|SCK           |18        |
|SDA           |21        |