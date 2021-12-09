#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESPAsyncTCP.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include "pagehtml.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Hash.h>

//ABP


#define FIREBASE_HOST "medicaosilo-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "eHq0UXMJJH97b88DieMCN56iL7yo61r64F1SdfcU"

AsyncWebServer server(80);

const char* ssid = "Richard";
const char* password = "0808viga";

const char* PARAM_INPUT_1 = "input1";


//#define rPin 12 //D6
//#define gPin 14 //D5
//#define bPin 0  //D3
//#define trigSensor 13 //D7
//#define echoSensor 15 //D8


//bruno karine
#define rPin 12 //D12
#define gPin 4 //4
#define bPin 5  //D1
#define trigSensor D3 //D3
#define echoSensor D2 //D2

float duration, cm, altura, volume, abastecimento;
const float pi = 3.14;
String lampada;
bool ledState = 0;

  String inputMessage = "";
  String inputParam = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");



void setup() {
  Serial.begin(115200);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  pinMode(trigSensor, OUTPUT);
  pinMode(echoSensor, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }

  
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  timeClient.begin();
  timeClient.setTimeOffset(-10800);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", paginahtml);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
  // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
  if (request->hasParam(PARAM_INPUT_1)) {
    inputMessage = request->getParam(PARAM_INPUT_1)->value();
    inputParam = PARAM_INPUT_1;
  }
  else {
    inputMessage = "Sem mensagem enviada";
    inputParam = "nenhum";
  }
  request->redirect("https://medicaosilo.web.app/");
});
  
  server.begin();
}

void loop() {

  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;

  String currentDate = String(monthDay) + "/" + String(currentMonth) + "/" + String(currentYear) + " " + timeClient.getHours() + ":" + timeClient.getMinutes();

  digitalWrite(trigSensor, LOW);
  delayMicroseconds(5);
  digitalWrite(trigSensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigSensor, LOW);

  pinMode(echoSensor, INPUT);
  duration = pulseIn(echoSensor, HIGH);
  cm = (duration/2) / 29.1;
  //4 metros menos a distancia em centimetros, conversão para metros
  altura = (100-cm)/100;
  altura = (altura<0? 0:altura);

  //V = π.r².h      r = 1.5, r² = 2.25 
  volume = pi * 2.25 * altura;

  int luz = analogRead(A0);

  if(volume < 5){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
  }

  if(luz>800){
      lampada = "Apagada";
      setColor(255, 0, 0);
    }else{
      lampada = "Acesa";
      setColor(0, 255, 0);
    }

  if(inputMessage != ""){
    Firebase.setString(sha1(inputMessage) + "/volume",String(volume));      
    Firebase.setString(sha1(inputMessage) + "/abastecimento",String(altura*100));
    Firebase.setString(sha1(inputMessage) + "/lampada",String(lampada));
    Firebase.setString(sha1(inputMessage) + "/data",String(currentDate));
    Firebase.setString(sha1(inputMessage) + "/email",String(inputMessage));
    if (Firebase.failed()) { 
        Serial.print("Getting /Value failed :");
        Serial.println(Firebase.error()); 
        return;
    }
  }
  
  
  Serial.println("");
  Serial.println("Sensor de luminosidade..: " + String(luz));
  Serial.println("Sensor HC-SR04..........: " + String(cm) + "cm");
  Serial.println("Volume de arroz.........: " + String(volume) + "m³");
  Serial.println("Ultima atualização......: " + String(currentDate));
  if(inputMessage != ""){
  Serial.println("Email Cadastrado........: " + String(inputMessage));
  Serial.println("Chave SHA1..............: " + String(sha1(inputMessage)));  
    }
  delay(500);

  
}

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(rPin, redValue);
  analogWrite(gPin, greenValue);
  analogWrite(bPin, blueValue);
}
