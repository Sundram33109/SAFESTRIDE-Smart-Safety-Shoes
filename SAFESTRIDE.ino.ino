#include <TinyGPS++.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;

HardwareSerial GPS(1);
HardwareSerial GSM(2);

#define SOS_BUTTON 4

String phone = "+919263324524";

void setup() {

Serial.begin(115200);

pinMode(SOS_BUTTON, INPUT_PULLUP);

GPS.begin(9600, SERIAL_8N1, 16, 17);

GSM.begin(9600, SERIAL_8N1, 26, 27);

delay(2000);

}

void loop() {

while (GPS.available()) {
gps.encode(GPS.read());
}

if (digitalRead(SOS_BUTTON)==LOW){

sendSOS();

delay(5000);

}

}

void sendSOS(){

String latitude="Unknown";
String longitude="Unknown";

if(gps.location.isValid()){

latitude=String(gps.location.lat(),6);

longitude=String(gps.location.lng(),6);

}

String link="https://maps.google.com/?q="+latitude+","+longitude;

sendSMS(link);

makeCall();

}

void sendSMS(String link){

GSM.println("AT+CMGF=1");
delay(1000);

GSM.println("AT+CMGS=\""+phone+"\"");
delay(1000);

GSM.println("🚨 EMERGENCY ALERT 🚨");
GSM.println("SAFESTRIDE Smart Safety Shoes");
GSM.println("Immediate help needed.");
GSM.println(link);

GSM.write(26);

}

void makeCall(){

GSM.println("ATD"+phone+";");

delay(20000);

GSM.println("ATH");

},
