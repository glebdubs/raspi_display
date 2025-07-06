/** Arduino Liquid Crystal Clock
 *
 * 
 *
 */
#include <Arduino.h>
#include <Ds1302.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int PIN_ENA = 2;
const int PIN_CLK = 4;
const int PIN_DAT = 3;

int secondCounter = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// DS1302 RTC instance
Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);

const static char* WeekDays[] =
{
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};


void setup()
{
    Serial.begin(9600);

    // initialize the RTC
    rtc.init();

    lcd.begin();
    lcd.backlight();

    lcd.print("initialising...");

    // test if clock is halted and set a date-time (see example 2) to start it
    if (rtc.isHalted())
    {
        Serial.println("RTC is halted. Setting time...");

        Ds1302::DateTime dt = { // change this time to current time before running
            .year = 25,
            .month = Ds1302::MONTH_JUL,
            .day = 3,
            .hour = 4,
            .minute = 51,
            .second = 30,
            .dow = Ds1302::DOW_TUE
        };

        rtc.setDateTime(&dt);
    }
}


void loop()
{
    // get the current time
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    static uint8_t last_second = 0;
    if (last_second != now.second)
    {
        last_second = now.second;

        Serial.print("20");
        Serial.print(now.year);    // 00-99
        Serial.print('-');
        if (now.month < 10) Serial.print('0');
        Serial.print(now.month);   // 01-12
        Serial.print('-');
        if (now.day < 10) Serial.print('0');
        Serial.print(now.day);     // 01-31
        Serial.print(' ');
        Serial.print(WeekDays[now.dow - 1]); // 1-7
        Serial.print(' ');
        if (now.hour < 10) Serial.print('0');
        Serial.print(now.hour);    // 00-23
        Serial.print(':');
        if (now.minute < 10) Serial.print('0');
        Serial.print(now.minute);  // 00-59
        Serial.print(':');
        if (now.second < 10) Serial.print('0');
        Serial.print(now.second);  // 00-59
        Serial.println();
    }

    if(secondCounter == 59) {
      secondCounter = 0;
      lcd.clear(); // reset

      lcd.setCursor(2, 0);

      lcd.print(WeekDays[now.dow - 1]); // day of the week
      lcd.print(" ");
      
      if (now.month < 10) lcd.print('0'); // leading zero if necessary
      lcd.print(now.day); // day of the month
      lcd.print('-');
      if (now.day < 10) lcd.print('0');
      lcd.print(now.month); // month number

      lcd.setCursor(6, 1);

       if (now.hour < 10) lcd.print('0');
      lcd.print(now.hour);    // 00-23
      lcd.print(':');
      if (now.minute < 10) lcd.print('0');
      lcd.print(now.minute);  // 00-59

    } else {
      secondCounter++;
    }



    

    delay(100);
}

