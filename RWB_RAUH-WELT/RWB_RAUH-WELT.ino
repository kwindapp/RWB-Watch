#include <TFT_eSPI.h>
#include "kiterRWB1.h"
#include "kiterRWB2.h"
#include "kiterRWB3.h"
#include "kiterRWB4.h"
#include "kiterRWB5.h"
#include "kiterRWB6.h"
#include "kiterRWB7.h"
#include "kiterRWB8.h"
#include "kiterRWB9.h"
#include "kiterRWB10.h"

#include "logo.h"
#include "backg.h"
#include "time.h"
#include <WiFiManager.h>
#include <WiFi.h>
#include <Arduino.h>
#include <ArduinoJson.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite logoSprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB1Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB2Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB3Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB4Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB5Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB6Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB7Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB8Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB9Sprite = TFT_eSprite(&tft);
TFT_eSprite kiterRWB10Sprite = TFT_eSprite(&tft);

TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite txtSprite = TFT_eSprite(&tft);

char timeHour[3];
char timeMin[3];
char timeSec[3];
char day[3];
char month[10];
char year[5];
char timeWeekDay[10];
int dayInWeek;

int brightnesses[7] = {35, 70, 105, 140, 175, 210, 250};
int bright = 5;
int deb = 0;

String SDay[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String Months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
int mm[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int dayInMonth = 0;
int daysInMonth = 0;
int firstDay = 0;

float x = 20; // smooth animation
long randNumber, randNumber1, randNumber2;

unsigned long t = 0;
unsigned long lastUpdate = 0;
const int updateInterval = 28;

#define kiterRWB3h 150
#define kiterRWB3w 150

// Time zone variables
long gmtOffset_sec = 3600; // Default GMT+1
const int daylightOffset_sec = 3600;
int tzButtonPin = 14;
int tzDebounce = 0;

void setup() {
    Serial.begin(115200);
    randomSeed(analogRead(0));

    pinMode(0, INPUT_PULLUP); // brightness button
    pinMode(tzButtonPin, INPUT_PULLUP); // time zone button

    tft.init();
    tft.setRotation(3);
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);

    background.createSprite(320, 170);
    background.setSwapBytes(true);

    kiterRWB1Sprite.createSprite(kiterRWB1_HEIGHT, kiterRWB1_WIDTH);
    kiterRWB2Sprite.createSprite(kiterRWB2_HEIGHT, kiterRWB2_WIDTH);
    kiterRWB3Sprite.createSprite(kiterRWB3_HEIGHT, kiterRWB3_WIDTH);
    kiterRWB4Sprite.createSprite(kiterRWB4_HEIGHT, kiterRWB4_WIDTH);
    kiterRWB5Sprite.createSprite(kiterRWB5_HEIGHT, kiterRWB5_WIDTH);
    kiterRWB6Sprite.createSprite(kiterRWB6_HEIGHT, kiterRWB6_WIDTH);
    kiterRWB7Sprite.createSprite(kiterRWB7_HEIGHT, kiterRWB7_WIDTH);
    kiterRWB8Sprite.createSprite(kiterRWB8_HEIGHT, kiterRWB8_WIDTH);
    kiterRWB9Sprite.createSprite(kiterRWB9_HEIGHT, kiterRWB9_WIDTH);
    kiterRWB10Sprite.createSprite(kiterRWB10_HEIGHT, kiterRWB10_WIDTH);

    logoSprite.createSprite(20, 20);
    txtSprite.createSprite(320, 170);
    txtSprite.setTextColor(TFT_BLACK, TFT_BLACK);

    tft.setTextFont(4);
    tft.drawString("#MyClock", 14, 60);
    tft.drawString("Please connect wifi KWind", 14, 17);

    WiFiManager wifiManager;
    wifiManager.setConfigPortalTimeout(300);
    if (!wifiManager.autoConnect("KWind IoT", "")) {
        delay(1000);
        ESP.restart();
    }

    while (WiFi.status() != WL_CONNECTED) {
        delay(3000);
    }

    configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");
}

void getLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return;

    strftime(timeHour, 3, "%H", &timeinfo);
    strftime(timeMin, 3, "%M", &timeinfo);
    strftime(timeSec, 3, "%S", &timeinfo);
    strftime(timeWeekDay, 10, "%A", &timeinfo);

    for (int i = 0; i < 7; i++) {
        if (String(timeWeekDay) == SDay[i]) dayInWeek = i;
    }

    strftime(day, 3, "%d", &timeinfo);
    strftime(month, 10, "%B", &timeinfo);
    strftime(year, 5, "%Y", &timeinfo);

    dayInMonth = String(day).toInt();
    for (int i = 0; i < 12; i++) {
        if (String(month) == Months[i]) daysInMonth = mm[i];
    }

    int j = dayInWeek;
    for (int i = dayInMonth; i > 0; i--) {
        firstDay = j;
        j--;
        if (j == -1) j = 6;
    }

    printTimeInfo(); // Print all time info
}

void printTimeInfo() {
    Serial.println("=== Time Info ===");
    Serial.print("Hour: "); Serial.println(timeHour);
    Serial.print("Minute: "); Serial.println(timeMin);
    Serial.print("Second: "); Serial.println(timeSec);
    Serial.print("Day: "); Serial.println(day);
    Serial.print("Month: "); Serial.println(month);
    Serial.print("Year: "); Serial.println(year);
    Serial.print("Weekday: "); Serial.println(timeWeekDay);
    Serial.print("Day in week: "); Serial.println(dayInWeek);
    Serial.print("Day in month: "); Serial.println(dayInMonth);
    Serial.print("Days in month: "); Serial.println(daysInMonth);
    Serial.print("First day of month: "); Serial.println(firstDay);
}

void switchTimeZone() {
    gmtOffset_sec += 3600; // add 1 hour
    if (gmtOffset_sec > 12*3600) gmtOffset_sec = -12*3600;
    configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");
    Serial.print("Switched timezone to GMT offset: ");
    Serial.println(gmtOffset_sec / 3600);
}

void checkTimeZoneButton() {
    if (digitalRead(tzButtonPin) == LOW) {
        if (tzDebounce == 0) {
            tzDebounce = 1;
            switchTimeZone();
        }
    } else tzDebounce = 0;
}

void loop() {
    checkTimeZoneButton();

    if (t + 1000 < millis()) {
        getLocalTime();
        t = millis();
    }

    // Smooth movement
    if (millis() - lastUpdate >= updateInterval) {
        x += 1.5; // smooth increment
        lastUpdate = millis();
    }

    if (x > 150) x = -80;

    if (digitalRead(0) == 0) {
        if (deb == 0) {
            deb = 1;
            bright++;
            if (bright == 7) bright = 0;
            ledcWrite(0, brightnesses[bright]);
        }
    } else deb = 0;

    // Draw background
    background.setSwapBytes(false);
    background.pushImage(0, 0, 320, 170, backg);

    // Draw text
    txtSprite.fillSprite(TFT_BLACK);
    txtSprite.setSwapBytes(false);
    txtSprite.setTextColor(0xFEA0, TFT_BLACK); // Gold color
    txtSprite.setFreeFont(&Orbitron_Light_32);
    txtSprite.drawString(String(timeHour) + ":" + String(timeMin), 100, -2);
    txtSprite.setFreeFont(&Orbitron_Light_24);
    txtSprite.drawString(String(timeSec), 215, 2);

    txtSprite.setTextColor(0xFEA0, TFT_BLACK);
    txtSprite.setTextFont(2);
    txtSprite.drawString(String(month) + " " + String(dayInMonth), 30, 5);
    txtSprite.drawString(SDay[dayInWeek], 265, 5);

    txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
    txtSprite.drawString("Akira Nakai", 130, 150);

    // Generate random numbers for kite animation
    randNumber = random(1, 2);
    randNumber1 = random(3, 5);
    randNumber2 = random(3, 5);

    // Push logo
    logoSprite.pushImage(0, 0, 20, 20, logo);
    logoSprite.pushToSprite(&background, 2, 0, TFT_BLACK);

    // Push kites
    kiterRWB1Sprite.pushImage(0, 40, kiterRWB1_HEIGHT, kiterRWB1_WIDTH, kiterRWB1);
    kiterRWB1Sprite.pushToSprite(&background, x + 0 + x * 4, 0 + randNumber - x * 0, TFT_BLACK);

    kiterRWB2Sprite.pushImage(0, 10, kiterRWB2_HEIGHT, kiterRWB2_WIDTH, kiterRWB2);
    kiterRWB2Sprite.pushToSprite(&background, x + 60 + x * 13, 0 + randNumber, TFT_BLACK);

    kiterRWB6Sprite.pushImage(0, 0, kiterRWB6_HEIGHT, kiterRWB6_WIDTH, kiterRWB6);
    kiterRWB6Sprite.pushToSprite(&background, x - 755 + x * 11, 10 - x, TFT_BLACK);

    kiterRWB5Sprite.pushImage(0, 0, kiterRWB5_HEIGHT, kiterRWB5_WIDTH, kiterRWB5);
    kiterRWB5Sprite.pushToSprite(&background, x - 460 + x * 8, 40 - x, TFT_BLACK);

    kiterRWB7Sprite.pushImage(0, 0, kiterRWB7_HEIGHT, kiterRWB7_WIDTH, kiterRWB7);
    kiterRWB7Sprite.pushToSprite(&background, x - 740 + x * 9, -20, TFT_BLACK);

    kiterRWB9Sprite.pushImage(0, 0, kiterRWB9_HEIGHT, kiterRWB9_WIDTH, kiterRWB9);
    kiterRWB9Sprite.pushToSprite(&background, x - 1330 + x * 10, -22, TFT_BLACK);

    kiterRWB8Sprite.pushImage(0, 0, kiterRWB8_HEIGHT, kiterRWB8_WIDTH, kiterRWB8);
    kiterRWB8Sprite.pushToSprite(&background, x - 1290 + x * 12, -20, TFT_BLACK);

    // Push text on top
    txtSprite.pushToSprite(&background, 0, 0, TFT_BLACK);

    // Display everything
    background.pushSprite(0, 0);
}
