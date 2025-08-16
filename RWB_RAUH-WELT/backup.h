#include <TFT_eSPI.h> 
#include "kiter1.h"
#include "kiter2.h"
#include "kiter3.h"
#include "kiter4.h"
#include "kiter5.h"
#include "city.h"
#include "time.h"
#include <WiFiManager.h>
#include <WiFi.h>
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite kiter1Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter2Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter3Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter4Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter5Sprite= TFT_eSprite(&tft);
TFT_eSprite background= TFT_eSprite(&tft);
TFT_eSprite txtSprite= TFT_eSprite(&tft);
TFT_eSprite tftSprite= TFT_eSprite(&tft);

int randomVals[0];
long randNumber;
long randNumber1;
long randNumber2;

char timeHour[3];
char timeMin[3];
char timeSec[3];
char day[3];
char month[10];
char year[5];
char timeWeekDay[10];
int dayInWeek;
String IP;
uint32_t volt ;
bool isCon=false;
bool isConSer=false;
int x=20;
String num="";
String Day[7]={"Sunday","MO","TU","WE","TH","FR","SA"};
String SDay[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
String Months[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
int mm[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int dayCounter=0;
int dayInMonth=0;
int daysInMonth=0;
int firstDay=0;
int brightness=50;
 int seg=0;  
 long t=0;
#define b 16
#define a 21
int cx,cy=0;
float n1=0;
float n2=0;

int operation=0;
unsigned long lastUpdate = 0;   // Store the last time x was incremented
const int updateInterval = 50; // Time interval between updates (in milliseconds)

void setup() {

 randomSeed(analogRead(0));   // Seed generator...
pinMode(0,INPUT_PULLUP);
pinMode(14,INPUT_PULLUP);
 ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, brightness);




 tft.init();
 tft.setRotation(1);
 tft.setSwapBytes(true);
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec =3600;            //time zone * 3600 , my time zone is  +1 GTM
const int   daylightOffset_sec = 3600;   
 //tft.createSprite(80,80);
 background.createSprite(320,170);
 background.setSwapBytes(true);
  
 kiter1Sprite.createSprite(160,200);
  kiter2Sprite.createSprite(60,60);
    kiter3Sprite.createSprite(150,50);
     kiter4Sprite.createSprite(80,160);
 kiter5Sprite.createSprite(80,160);
 txtSprite.createSprite(320,170);
 txtSprite.setTextColor(TFT_BLACK,TFT_BLACK);
 //arrowSprite.setSwapBytes(true);
 tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
        tft.drawString("#MyClock",14,60);
   tft.drawString("Please connect wifi KWind ",14,17);

if(!isCon)
 {
    WiFiManager wifiManager;
    wifiManager.setConfigPortalTimeout(300);
    if(!wifiManager.autoConnect("KWind IoT","")) {
           delay(1000);
               ESP.restart(); 
    }
  
      isCon=true;
        }
    //WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
   }

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      }



void getLocalTime()
  {
  //volt = (analogRead(4) * 2 * 3.3 * 1000) / 4096; 
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return;
  }
  strftime(timeHour,3, "%H", &timeinfo);
  strftime(timeMin,3, "%M", &timeinfo);
  strftime(timeSec,3, "%S", &timeinfo);
   strftime(timeWeekDay,10, "%A", &timeinfo);
 String InWeek=String(timeWeekDay);
  for(int i=0;i<7;i++)
  {
    if(InWeek==SDay[i])
    dayInWeek=i;
    }
strftime(day,3, "%d", &timeinfo);
  strftime(month,10, "%B", &timeinfo);
  strftime(year,5, "%Y", &timeinfo);
dayInMonth=String(day).toInt();
   for(int i=0;i<12;i++)
  {
    if(String(month)==Months[i])
    daysInMonth=mm[i];
    }
  
  int j=dayInWeek;
  for(int i=dayInMonth;i>0;i--)
  {
    firstDay=j;
    j--;
    if(j==-1)
    j=6;
    }
  }
 
int caw=0;
   int cay=140;
   int cax=110;
   int cah=0;
















void loop() {
    // Update the local time every second
    if (t + 1000 < millis()) {
        getLocalTime();
        t = millis();
    }

    // Increment x only after the specified interval has passed
    if (millis() - lastUpdate >= updateInterval) {
        x++;                   // Increment x
        lastUpdate = millis(); // Update the last increment time
    }

    // Reset x when it exceeds the limit
    if (x > 630) {
        x = -100;
    }

    // Adjust brightness with buttons
    if (digitalRead(14) == 0 && brightness < 240) {
        brightness++;
        ledcWrite(0, brightness);
    }

    if (digitalRead(0) == 0 && brightness > 50) {
        brightness--;
        ledcWrite(0, brightness);
    }

    // Prepare the background
    background.setSwapBytes(false);
    background.pushImage(0, 0, 320, 170, city);

    // Prepare the text sprite
    txtSprite.fillSprite(TFT_BLACK);
    txtSprite.setSwapBytes(true);
    txtSprite.setFreeFont(&Orbitron_Light_32);
    txtSprite.drawString(String(timeHour) + ":" + String(timeMin), 80, 0);
    txtSprite.setFreeFont(&Orbitron_Light_24);
    txtSprite.drawString(String(timeSec), 200, 0);
    txtSprite.setTextColor(TFT_GOLD, TFT_BLACK);
    txtSprite.drawString(String(month) + " " + String(dayInMonth), 65, 35);
    txtSprite.drawString(SDay[dayInWeek], cax, cay);
    txtSprite.setTextFont(4);
    txtSprite.drawString("Priti", 5, 50);

    // Generate random numbers for sprite movement
    randNumber = random(1, 2);
    randNumber1 = random(1, 2);
    randNumber2 = random(1, 2);

    // Draw sprites with updated positions
    kiter1Sprite.pushImage(0, 0, 80, 170, kiter1);
    kiter1Sprite.pushToSprite(&background, x - 50, 80 + randNumber1, TFT_BLACK);

    kiter2Sprite.pushImage(0, 0, 60, 60, kiter2);
    kiter2Sprite.pushToSprite(&background, x + 80, 0 + randNumber + 110, TFT_BLACK);

    kiter3Sprite.pushImage(0, 0, 120, 100, kiter3);
    kiter3Sprite.pushToSprite(&background, x - 50 + x, 40 + randNumber1, TFT_BLACK);

    kiter4Sprite.pushImage(0, 0, 100, 100, kiter4);
    kiter4Sprite.pushToSprite(&background, x, 80, TFT_BLACK);

    kiter5Sprite.pushImage(0, 0, 80, 30, kiter5);
    kiter5Sprite.pushToSprite(&background, x - 110 + x, 150 + randNumber2 - x, TFT_BLACK);

    // Add text sprite to the background
    txtSprite.pushToSprite(&background, 0, 0, TFT_BLACK);

    // Push the final image to the screen
    background.pushSprite(0, 0);
}


kiter1Sprite.pushImage(0,35,200,160,kiter1); //move:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 kiter1Sprite.pushToSprite(&background,x,0,TFT_BLACK); //move up down


 kiter2Sprite.pushImage(30,0,60,60,kiter2); //move:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 kiter2Sprite.pushToSprite(&background,x+80+x++,-randNumber+x++,TFT_BLACK); //move up down move kiter

 kiter3Sprite.pushImage(0,0,150,50,kiter3); //move:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 kiter3Sprite.pushToSprite(&background,x-50+x++,+randNumber1,TFT_BLACK); //move up down move kiter

 kiter4Sprite.pushImage(0,0,80,160,kiter4); //move:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 kiter4Sprite.pushToSprite(&background,x-80+randNumber,20,TFT_BLACK); //move up down move kiter
