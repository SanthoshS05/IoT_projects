//You can simulate this code using wokwi
//diagram.json &libraries.txt attached in same folder
//Happy Learning
//LINK----https://wokwi.com/projects/379912270128056321
//For more IOT projects 
//https://github.com/santh0sh05/IoT_projects.git



//Replace this field with Your auth token
#define BLYNK_TEMPLATE_ID "TMPL3Fa6eQf9e"
#define BLYNK_TEMPLATE_NAME "Smart parking"
#define BLYNK_AUTH_TOKEN "C5yd-C-cAOwEMMiqohaSeoJRModhyTzl"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


//Replace this field with your wifi credentials
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


#define ECHO_A 2
#define TRIG_A 18
#define ECHO_B 4
#define TRIG_B 5
#define ECHO_C 13
#define TRIG_C 14
#define ECHO_D 17
#define TRIG_D 16
int a,b,c,d;
int Slot;
//char full[] = "Full";
//char fr[] = "Free";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(TRIG_A, OUTPUT);
  pinMode(ECHO_A, INPUT);
  pinMode(TRIG_B, OUTPUT);
  pinMode(ECHO_B, INPUT);
  pinMode(TRIG_C, OUTPUT);
  pinMode(ECHO_C, INPUT);
  pinMode(TRIG_D, OUTPUT);
  pinMode(ECHO_D, INPUT);
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
  a=check(TRIG_A,ECHO_A);
  if(a==0){
     Blynk.virtualWrite(V1, 0 );
  }
  else{
     Blynk.virtualWrite(V1, 1);
  }
  b=check(TRIG_B,ECHO_B);
  if(b==0){
     Blynk.virtualWrite(V2, 0 );
  }
  else{
     Blynk.virtualWrite(V2, 1);
  }
  c=check(TRIG_C,ECHO_C);
  if(c==0){
     Blynk.virtualWrite(V3, 0 );
  }
  else{
     Blynk.virtualWrite(V3, 1);
  }
  d=check(TRIG_D,ECHO_D);
  if(d==0){
     Blynk.virtualWrite(V4, 0 );
  }
  else{
     Blynk.virtualWrite(V4, 1);
  }
  Serial.printf("%d %d %d %d \n",a,b,c,d);
  Slot=a+b+c+d;
  Serial.printf("slots free=%d \n",Slot);
  Blynk.virtualWrite(V0, Slot);
  delay(2000); // this speeds up the simulation
}
float check(int trigerpin, int echopin){
    float distance, duration;
    digitalWrite(trigerpin, LOW);
    delay(2);
    digitalWrite(trigerpin, HIGH);
    delay(10);
    digitalWrite(trigerpin, LOW);
    duration=pulseIn(echopin,HIGH);
    distance=duration/2*0.034;
    Serial.print("distance (in cm)=");
    Serial.println(distance);
    delay(10);
    if(distance>30){
      return 1;

    } 
    else{
      return 0;
    }
 }



