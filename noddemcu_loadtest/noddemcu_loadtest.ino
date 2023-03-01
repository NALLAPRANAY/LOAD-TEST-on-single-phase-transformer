#define BLYNK_TEMPLATE_ID "TMPLTMQIdhaF"
#define BLYNK_DEVICE_NAME "Secondary"
#define BLYNK_AUTH_TOKEN "fhuOie_TVJlJEv9q661APCGovOiIohHZ"
#define BLYNK_PRINT Serial

#include<SoftwareSerial.h>
#include<BlynkSimpleEsp8266.h>
#include<ESP8266WiFi.h>



char auth[]=BLYNK_AUTH_TOKEN;
BlynkTimer timer;
WiFiClient client;

const char* ssid  ="";
const char* password  ="srinunalla";



float vout=0.0;
float vin=0.0;
float r1=30000;
float r2=7500;
int vsensor=A0;
int val;
float correctionfactor=8.0;


BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}



void setup() {
  Serial.begin(115200);
  pinMode(vsensor,A0);
  Blynk.begin(auth, ssid, password);
  WiFi.mode(WIFI_STA);
  Serial.print("connected to ssid");
  Serial.println(ssid);

  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  Blynk.run();
  upload();

}
void upload(){
val=analogRead(vsensor);
vout=(val*5.0)/1023.0;
vin=vout/(r2/(r1+r2));
vin=vin-correctionfactor;
Serial.println(vin);
Blynk.virtualWrite(V4,vin);
}
