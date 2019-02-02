
#include <LiquidCrystal.h>  // Kirjasto näytölle  
#include <RH_ASK.h>         // kirjasto ASK-modulaatioon
#include <SPI.h>            // Kirjasto synkroniseen tiedonsiirtoon

LiquidCrystal lcd(3, 4, 7, 8, 9, 10);    // Näyttö, määritellään portit
RH_ASK rf_receiver;                      // ASK-olio
char tempArr[]="Temp:";
char minArr[]="MIN";
char maxArr[]="MAX";
 
double temperature;
double max;
double min;

// Alustukset
void setup(){ 
    lcd.begin(16,2);        // 16x2 näyttöalue
    lcd.clear();
    rf_receiver.init();
    /* Printataan näytölle "Temp:"
    ja MIN, MAX*/
    lcd.setCursor(0,0);
    for (int i = 0 ; i <=4 ; i++){
      lcd.print(tempArr[i]);
      delay(100);
    }
    lcd.setCursor(0,1);
    for (int i = 0 ; i <=2 ; i++){
      lcd.print(minArr[i]);
      delay(100);
    }
    lcd.setCursor(8,1);
    for (int i = 0 ; i <=2 ; i++){
      lcd.print(maxArr[i]);
      delay(100);
    }
}
 
void loop(){
    uint8_t packet[5];
    uint8_t packetSize = sizeof(packet);
    // Tarkastetaan datan oikea koko
    if (rf_receiver.recv(packet, &packetSize)){
      lcd.setCursor(6,0);
      String s = String((char*)packet);
      temperature = (s.substring(0,1).toInt())*10+s.substring(1,2).toInt()+(s.substring(3,4).toDouble())/10 +(s.substring(4,5).toDouble())/100; // String double-arvoksi
      lcd.print(temperature);
      lcd.print(" C ");

      // Asetetaan mahd min & max-lämpötilat
      // Printataan uudet arvot vain jos on tapahtunut muutoksia
      if (max && min){        // max & min ei null?
        if (temperature>max){
          max=temperature;
          lcd.setCursor(11,1);
          lcd.print(max);
        }
        if (temperature<min){
          min=temperature;
          lcd.setCursor(3,1);
          lcd.print(min);          
        }
      } else {
      max = temperature;  // Asetetaan oletusarvot, jos null, ja printataan näytölle
      lcd.setCursor(11,1);
      lcd.print(max);  
      min = temperature;
      lcd.setCursor(3,1);
      lcd.print(min);    
      }
      delay(500);         
    }
}
