
#include <RH_ASK.h>   // Kirjasto ASK-modulaatioon
#include <SPI.h>      // Kirjasto synkroniseen tiedonsiirtoon

#define sensorPin 0  // Lämpötilasensorin analog-pinni

RH_ASK rf_sender; 

// Asetukset
void setup(){
    rf_sender.init(); // rf-olion alustus
}

// Loop:n sisältöä suoritetaan non-stoppina
void loop(){
    float analogIn = analogRead(sensorPin);         // Sensorista luettu arvo [0..1023]
    float temp = (1023.0*10000)/analogIn-10000;       // Skaalattu arvo Kelvineiksi
    float temp1 = (3435.0/(log(temp/10000)+(3435.0/(273.15+25)))) - 273.15;
    //Lämpötilan lasku vastuksen resistanssista

    String lampoString = String(temp1);
    static char *msg = (lampoString).c_str();       // Parsitaan C++:n char-jonoksi
    
    rf_sender.send((uint8_t *)msg, strlen(msg));    // Lähetys
    rf_sender.waitPacketSent();                   
    delay(500);                                     // Odotetaan 0.5s
}
