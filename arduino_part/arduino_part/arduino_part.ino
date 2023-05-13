#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BAUD_RATE 9600

#define TEMP_KEY 'T' /* T - Temperature */
#define HUM_KEY 'H' /* H - Humidity */
#define CLEAR_KEY 'C' /* C - LCD Clear */

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(BAUD_RATE);

  lcd.init();               
  lcd.backlight();
}


void loop()
{
  if(Serial.available() > 0)
  {
    
    char key = Serial.read();
    int value = Serial.parseInt();

    switch(key)
    {
      case TEMP_KEY:
      {
        lcd.setCursor(0,0);
        lcd.print("temp: ");
        lcd.print(value);
        lcd.print("C");
        break;
      }
      case HUM_KEY:
      {
        lcd.setCursor(0, 1);
        lcd.print("hum: ");
        lcd.print(value);
        lcd.print("%");
        break;
      }
      case CLEAR_KEY:
      {
        lcd.clear();
        break;
      }
    }
  }
}

