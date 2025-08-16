#include <TFT_eSPI.h>
#include "kiter1.h"
#include "kiter2.h"
#include "kiter3.h"
#include "kiter4.h"
#include "kiter5.h"
#include "kiter6.h"
#include "kiter7.h"
#include "kiter8.h"
#include "kiter9.h"
#include "kiter10.h"
#include "kiter11.h"
#include "kiter12.h"
#include "kiter13.h"
#include "kiter14.h"
#include "kiter15.h"
#include "kiter16.h"
#include "kiter17.h"
#include "kiter18.h"
#include "logo.h"
#include "city.h"
#include "time.h"
#include <WiFiManager.h>
#include <WiFi.h>
#include <Arduino.h>
#include <ArduinoJson.h>

TFT_eSPI tft = TFT_eSPI(); 
 TFT_eSprite logoSprite= TFT_eSprite(&tft);
TFT_eSprite kiter1Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter2Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter3Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter4Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter5Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter6Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter7Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter8Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter9Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter10Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter11Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter12Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter13Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter14Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter15Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter16Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter17Sprite= TFT_eSprite(&tft);
TFT_eSprite kiter18Sprite= TFT_eSprite(&tft);
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
//String Months[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
String Months[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
int mm[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int dayCounter=0;
int dayInMonth=0;
int daysInMonth=0;
int firstDay=0;
int brightnesses[7]={35,70,105,140,175,210,250};
int bright=5;
int deb=0;
int deb2=0;
bool scheme=0;








int values[24]={0};
int values2[24]={0};
//char timeHour[3]="00";
//char timeMin[3]="00";
int gw=10;
int gh=10;// water level ???
int gx=0; // Linen to right
int gy=180;  // water level
//int curent=0;
int curent=0;


 int seg=0;  
 long t=0;
#define b 16
#define a 21
int cx,cy=0;
float n1=0;
float n2=0;
int operation=0;

#define kiter3h 150
#define kiter3w 150

void setup() {
 Serial.begin(115200);
 randomSeed(analogRead(0));   // Seed generator...
pinMode(0,INPUT_PULLUP);
pinMode(14,INPUT_PULLUP);
 tft.init();
 tft.setRotation(3);
 tft.setSwapBytes(true);

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec =3600;            //time zone * 3600 , my time zone is  +1 GTM
const int   daylightOffset_sec = 3600;   
 //tft.createSprite(80,80);
 background.createSprite(320,170);
 background.setSwapBytes(true);
  
 kiter1Sprite.createSprite(kiter1_HEIGHT,kiter1_WIDTH);
  kiter2Sprite.createSprite(kiter2_HEIGHT,kiter2_WIDTH);
    kiter3Sprite.createSprite(kiter3_HEIGHT,kiter3_WIDTH);
     kiter4Sprite.createSprite(kiter4_HEIGHT,kiter4_WIDTH);
 kiter5Sprite.createSprite(kiter5_HEIGHT,kiter5_WIDTH);
  kiter6Sprite.createSprite(kiter6_HEIGHT,kiter6_WIDTH);
    kiter7Sprite.createSprite(kiter7_HEIGHT,kiter7_WIDTH);
        kiter8Sprite.createSprite(kiter8_HEIGHT,kiter8_WIDTH);
           kiter9Sprite.createSprite(kiter9_HEIGHT,kiter9_WIDTH);
              kiter10Sprite.createSprite(kiter10_HEIGHT,kiter10_WIDTH);
                kiter11Sprite.createSprite(kiter11_HEIGHT,kiter11_WIDTH);
                  kiter12Sprite.createSprite(kiter12_HEIGHT,kiter12_WIDTH);
                   kiter13Sprite.createSprite(kiter13_HEIGHT,kiter13_WIDTH);
 kiter14Sprite.createSprite(kiter14_HEIGHT,kiter14_WIDTH);
  kiter15Sprite.createSprite(kiter15_HEIGHT,kiter15_WIDTH);
 kiter16Sprite.createSprite(kiter16_HEIGHT,kiter16_WIDTH);
 kiter17Sprite.createSprite(kiter17_HEIGHT,kiter17_WIDTH);
 kiter18Sprite.createSprite(kiter18_HEIGHT,kiter18_WIDTH);


  logoSprite.createSprite(20,20);

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
  
      isCon=false;
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
 
int counter=0;
int Min=gh/2;
int Max=gh/2;
int average=0;
String minT="";
String maxT="";
long lastMillis=0;
int fps=0;

int caw=0;
   int cay=140;
   int cax=112;
   int cah=0;

int middleX = tft.width() / 2 - 220; // 40 is half of kiter4Sprite width (80px)
int middleY = tft.height() / 2 - 140; // 80 is half of kiter4Sprite height (160px)


unsigned long lastUpdate = 0;   // Store the last time x was incremented
const int updateInterval =28; // Time interval between updates (33ms for ~30 FPS) 10,33,50



void loop() {
    // Update the local time every second
    if (t + 1000 < millis()) {
        getLocalTime();
        t = millis();
    }

    // Increment x for smooth movement
    if (millis() - lastUpdate >= updateInterval) {
        x++;                   // Increment x
        lastUpdate = millis(); // Update the last increment time
    }

    // Reset x when it exceeds the limit to loop
    if (x > 100) {
        x = -80;
    }
if(digitalRead(0)==0)  
  {if(deb==0)
   {deb=1; bright++; if(bright==7) bright=0;
   ledcWrite(0, brightnesses[bright]); }
  }else deb=0;
    // Prepare the background
    background.setSwapBytes(false);
    background.pushImage(0, 0, with, hight, city);

    // Prepare the text sprite
    txtSprite.fillSprite(TFT_BLACK);
    txtSprite.setSwapBytes(true);
    txtSprite.setFreeFont(&Orbitron_Light_32);
    txtSprite.drawString(String(timeHour) + ":" + String(timeMin), 100, -2);
    txtSprite.setFreeFont(&Orbitron_Light_24);
    txtSprite.drawString(String(timeSec), 220, 2);
    txtSprite.setTextColor(TFT_GOLD, TFT_BLACK);
    txtSprite.setTextFont(2);
    txtSprite.drawString(String(month) + " " + String(dayInMonth), 30, 5);
     txtSprite.setTextFont(2);
    txtSprite.drawString(SDay[dayInWeek],268 ,5 );
    txtSprite.setTextFont(2);
    txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
    txtSprite.drawString("Akira Nakai ", 130, 150);
 txtSprite.setTextColor(TFT_GOLD, TFT_BLACK);
    // Generate random numbers for sprite movement
    randNumber = random(1, 2);  // Adjust range as needed for smoother movements
    randNumber1 = random(3, 5);
    randNumber2 = random(3, 5 );

    logoSprite.pushImage(0, 0, 20, 20, logo);
    logoSprite.pushToSprite(&background,2 , 0 , TFT_BLACK);
    // Draw sprites with updated positions

    // Princi
    kiter1Sprite.pushImage(0, 40, kiter1_HEIGHT,kiter1_WIDTH, kiter1);
    kiter1Sprite.pushToSprite(&background, x + 270 + x * 4, 0+ randNumber-x*0, TFT_BLACK);

    // Chris Fast
    kiter2Sprite.pushImage(0, 10, kiter2_HEIGHT,kiter2_WIDTH, kiter2);
    kiter2Sprite.pushToSprite(&background, x + 20 + x * 13, 0 + randNumber, TFT_BLACK);

    // Nini TINI liam caro
    kiter3Sprite.pushImage(0, 30, kiter3_HEIGHT,kiter3_WIDTH, kiter3);
    kiter3Sprite.pushToSprite(&background, x -80 *17 + x *16, -70+ randNumber, TFT_BLACK);//greend

    // Dani (kiter4Sprite)
    kiter4Sprite.pushImage(0, 0, kiter4_HEIGHT,kiter4_WIDTH, kiter4);
   kiter4Sprite.pushToSprite(&background, x - 260 + x * 10, 20 - x*3, TFT_BLACK);

 kiter6Sprite.pushImage(0, 0, kiter6_HEIGHT,kiter6_WIDTH, kiter6);
  kiter6Sprite.pushToSprite(&background, x - 755 + x * 11, 10-x, TFT_BLACK);//blau
    // Nati Fast Up
    kiter5Sprite.pushImage(0, 0, kiter5_HEIGHT,kiter5_WIDTH, kiter5);
    kiter5Sprite.pushToSprite(&background, x - 460 + x * 8, 40 - x, TFT_BLACK); //akira

    // Nini Leg
  

   //Nini Dark dani loop /////////////////////////LOOP
kiter7Sprite.pushImage(0, 0, kiter7_HEIGHT, kiter7_WIDTH, kiter7);
 kiter7Sprite.pushToSprite(&background, x - 720 + x * 8, -10  , TFT_BLACK); //akira

    // Kite Janek core
    //kiter8Sprite.pushImage(0, 0, kiter8_HEIGHT,kiter8_WIDTH, kiter8);
    //kiter8Sprite.pushToSprite(&background, x - 210 + x+randNumber, 80-x, TFT_BLACK);

    // Kite Duo nati fly small kite
    //kiter9Sprite.pushImage(0, 0,kiter9_HEIGHT,kiter9_WIDTH, kiter9);
   // kiter9Sprite.pushToSprite(&background, x - 290 + x+randNumber2, 0+randNumber2, TFT_BLACK);

    // Abbas Down
   // kiter10Sprite.pushImage(0, 0, kiter10_HEIGHT,kiter10_WIDTH, kiter10);
   // kiter10Sprite.pushToSprite(&background, x - 320 + x, 55-randNumber1, TFT_BLACK); //+ move y down

    // Zara
    //kiter11Sprite.pushImage(0, 0, kiter11_HEIGHT,kiter11_WIDTH,kiter11);
    //kiter11Sprite.pushToSprite(&background, x - 430 + x+randNumber, -30+randNumber, TFT_BLACK); //- is kiter up

    // Giel
    //kiter12Sprite.pushImage(0, 0, kiter12_HEIGHT,kiter12_WIDTH, kiter12);
   // kiter12Sprite.pushToSprite(&background, x - 400 + x+randNumber1, 190-x, TFT_BLACK);

     // Kite rita handslide
    //kiter13Sprite.pushImage(0, 0, kiter13_HEIGHT,kiter13_WIDTH, kiter13);
    //kiter13Sprite.pushToSprite(&background, x - 75 + x, 55, TFT_BLACK);


 // rita
   // kiter14Sprite.pushImage(0, 0, kiter14_HEIGHT,kiter14_WIDTH,kiter14);
    //kiter14Sprite.pushToSprite(&background, x -540 + x, 250-x, TFT_BLACK);


 // Kite rita fly above abbas
    //kiter15Sprite.pushImage(0, 0, kiter15_HEIGHT,kiter15_WIDTH, kiter15);
    //kiter15Sprite.pushToSprite(&background, x -290 + x,-10, TFT_BLACK);


 // Kite rita hand hello
    //kiter16Sprite.pushImage(0, 0, kiter16_HEIGHT,kiter16_WIDTH, kiter16);
   // kiter16Sprite.pushToSprite(&background, x -220 + x, 70, TFT_BLACK);


 // Kite Duo wing finn
   // kiter17Sprite.pushImage(0, 0, kiter17_HEIGHT,kiter17_WIDTH,kiter17);
   // kiter17Sprite.pushToSprite(&background, x - 520 + x+randNumber2, 40+randNumber2, TFT_BLACK);


 // Kite Duo
    //kiter18Sprite.pushImage(0, 0, kiter18_HEIGHT,kiter18_WIDTH,kiter18);
    //kiter18Sprite.pushToSprite(&background, x +100+x*3 + x+randNumber2, 50+randNumber2, TFT_BLACK);


    // Add text sprite to the background
    txtSprite.pushToSprite(&background, 0, 0, TFT_BLACK);

    // Push the final image to the screen
    background.pushSprite(0, 0);
    //delay(10);
}
