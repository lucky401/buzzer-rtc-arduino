#include <Arduino.h>
#include <virtuabotixRTC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

virtuabotixRTC myRTC(6, 7, 8);

int buzzer = 11;

int buzzerOnHourArray[] = {10, 10};
int buzzerOnMinuteArray[] = {1, 3};
int buzzerOffHourArray[] = {10, 10};
int buzzerOffMinuteArray[] = {2, 4};

int buzzerFrequency = 330;

void setBuzzerFrequency(int frequency)
{
  tone(buzzer, frequency);
}

void setBuzzerOnOff(int h, int m)
{
  if (myRTC.hours == h && myRTC.minutes == m)
  {
    Serial.println("Buzzer On");
    setBuzzerFrequency(buzzerFrequency);
  }
  else
  {
    Serial.println("Buzzer Off");
    noTone(buzzer);
  }
}

void setup()
{
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  myRTC.setDS1302Time(50, 0, 10, 6, 14, 7, 2023);

  pinMode(buzzer, OUTPUT);
}

void loop()
{
  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();

  if (myRTC.hours == buzzerOnHourArray[0] && myRTC.minutes == buzzerOnMinuteArray[0])
  {
    Serial.println("Buzzer On");
    setBuzzerFrequency(buzzerFrequency);
  }
  else if (myRTC.hours == buzzerOnHourArray[1] && myRTC.minutes == buzzerOnMinuteArray[1])
  {
    Serial.println("Buzzer On");
    setBuzzerFrequency(buzzerFrequency);
  }
  else
  {
    Serial.println("Buzzer Off");
    noTone(buzzer);
  }

  // print the time to the LCD
  lcd.setCursor(0, 0);
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);

  // print frequency
  lcd.setCursor(0, 1);
  lcd.print("F:");
  lcd.setCursor(3, 1);
  lcd.print(buzzerFrequency);
  lcd.setCursor(7, 1);
  lcd.print("Hz");

  lcd.setCursor(11, 0);
  lcd.print(buzzerOnHourArray[0]);
  lcd.print("|");
  lcd.print(buzzerOnMinuteArray[0]);

  lcd.setCursor(11, 1);
  lcd.print(buzzerOnHourArray[1]);
  lcd.print("|");
  lcd.print(buzzerOnMinuteArray[1]);

  delay(1000);
}