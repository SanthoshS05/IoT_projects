//You can simulate this code using wokwi
//diagram.json &libraries.txt attached in same folder
//Happy Learning
//LINK----https://wokwi.com/projects/379902997023813633
//For more IOT projects 
//https://github.com/santh0sh05/IoT_projects.git

//replace with your Blynk credentials
#define BLYNK_TEMPLATE_ID "TMPL3-VBCPY"
#define BLYNK_TEMPLATE_NAME "water fountain"
#define BLYNK_AUTH_TOKEN "88q5QUnUB7tqWGrbsLJgcfrIsAqleTnF"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


//Your wifi credentials
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}
#define Fountain_motor 17
#define Motor 4
#define trigerpin1 27
#define echopin1 26
float a;
int san();

void setup(){
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(trigerpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  pinMode(Fountain_motor, OUTPUT);
  pinMode(Motor, OUTPUT);
  //used to measure duration of clock pulses
  
  
  
  Serial.println("hello sandy");
}

void loop(){
  a=san(trigerpin1,echopin1);
  Serial.print("distance (in cm)=");
  Serial.println(a);
  Blynk.virtualWrite(V0, a);
  delay(2000);
  //To show water level of the fountain
  Blynk.virtualWrite(V3, 4);
  if(a>10&&a<30){
    Blynk.virtualWrite(V3, 3);
  }else if(a>30&&a<50){
    Blynk.virtualWrite(V3, 2);
  }else if(a>50&&a<70){
    Blynk.virtualWrite(V3, 1);
  }else if(a>70){
    Blynk.virtualWrite(V3, 0);
  }
  //To turn on and of the fountain automatically
  if(a<10){
    digitalWrite(Fountain_motor, HIGH);
    digitalWrite(Motor, LOW);
    Blynk.virtualWrite(V1, 1);//foun
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V4, "Fountain Pump ON");
  }
  else{
    digitalWrite(Motor, HIGH);
    digitalWrite(Fountain_motor, LOW);
    Blynk.virtualWrite(V1, 0);//foun
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V4, "Filling Reservoir");

  }
}
//To read distance value from Ultrasonic sensor
int san(int trigerpin, int echopin){
    float distance, duration;
    digitalWrite(trigerpin, LOW);
    delay(2);
    digitalWrite(trigerpin, HIGH);
    delay(10);
    digitalWrite(trigerpin, LOW);
    duration=pulseIn(echopin,HIGH);
    distance=duration/2*0.034;
    //Serial.print("distance (in cm)=");
    //Serial.println(distance);
    delay(10);
    return distance;
  }