
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Blynk.h>
#define DHTPIN 0
#define PUMP 16
#define LEDRED 14
#define LEDGREEN 5
#define LEDYELLOW 12
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE,10);
int value,real_value;
int i=0;
int a=0, b=100;
const char *ssid="TP-Link_25B4";
const char *pass="";
static char celsiustemp[7];
static char fahrenheittemp[7];
static char humiditytemp[7];
void setup() {
  serial.begin(115200);
  pinmode(PUMP,OUTPUT);
  pinmode(LEDGREEN,OUTPUT);
  pinmode(LEDRED,OUTPUT);
  pinmode(LEDYELLOW,OUTPUT);
  delay(100);

  wifi.begin(ssid,pass);
  serial.println("");
  serial.print("connect to:");
  serial.print (ssid);
  while(wifi.status() != WL_CONNECTED){
    serial.print(".");
    delay(100);
  }
  serial.println(".");
  serial.println("CONNECTED TO WIFI");
  dht.begin();
}

void loop() {
  float h= dht.readHumidity();
  float t= dht.readTemperature();
  if (isnan(h) || isnan(t)){
    serial.println("Failed to read from DHT sensor!");
    }
    else {
      delay(1000);
      serial.print("Temperature:");
      serial.print(t);
      serial.print(" *C\t Humidity:");
      serial.print(h);
      delay(2000);
      }
  for (i=0;i<=9;i++){
    real_value+= analogRead(A0);
  }
  value=real_value/10;
  int percent= map(value,350,1023,0,100);
  percent=100-percent;
  real_value=0;
  serial.print(percent);
  serial.print("%");
  serial.print("  ");
  serial.print("Gia tri analog:");
  serial.print(value);
  delay(2000);
  if(a<b){
    a++;
  }  
  if(b>a){
    b--;
  }
  if (b<100){
    b++;
  }
  delay(2000);
  digitalWrite(LEDGREEN,1);
  digitalWrite(LEDRED,0);
  digitalWrite(LEDYELLOW,0);
  digitalWrite(PUMP,0);
  if(percent<a){
    digitalWrite(LEDGREEN,0);
    digitalWrite(LEDRED,1);
    digitalWrite(LEDYELLOW,0);
    digitalWrite(PUMP,1);
    delay(2000);
  }
  if(percent>b){
    digitalWrite(LEDGREEN,0);
    digitalWrite(LEDRED,0);
    digitalWrite(LEDYELLOW,1);
    digitalWrite(PUMP,0);
  }

}
