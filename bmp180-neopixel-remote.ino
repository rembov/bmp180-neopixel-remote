#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SFE_BMP180.h>
#include <Adafruit_NeoPixel.h>
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>
#include <RemoteXY.h>

// Настройки дисплея
LiquidCrystal_I2C lcd(0x38, 16, 2);

// Настройки датчика давления/температуры BMP180
SFE_BMP180 pressure;

// Настройки NeoPixel
#define PIN        13
#define NUM_LEDS   155
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Настройки RemoteXY (UART)
#define REMOTEXY_SERIAL_RX    8
#define REMOTEXY_SERIAL_TX    9
#define REMOTEXY_SERIAL_SPEED 9600

unsigned char RemoteXY_CONF[] = {
  255,0,0,22,0,75,0,8,13,0,
  67,4,7,14,26,12,12,26,11,67,
  4,54,14,26,12,6,26,11,129,0,
  9,6,18,6,12,208,148,208,176,208,
  178,208,187,208,181,208,189,208,184,208,
  181,0,129,0,51,7,29,6,6,208,
  162,208,181,208,188,208,191,208,181,209,
  128,208,176,209,130,209,131,209,128,208,
  176,0
};

struct {
  char text_1[11];      // давление (мм рт. ст.)
  char text_2[11];      // температура (°C)
  unsigned char connect_flag;
} RemoteXY;

void setup() {
  // Инициализация интерфейса RemoteXY
  RemoteXY_Init();
  Serial.begin(9600);

  // Настройка LCD
  lcd.begin();
  lcd.backlight();

  // Настройка NeoPixel
  strip.begin();
  strip.setBrightness(150);
  strip.clear();
  strip.show();
}

void loop() {
  RemoteXY_Handler();

  // Считываем температуру
  char status = pressure.startTemperature();
  double T, P;
  if (status) {
    delay(status);
    status = pressure.getTemperature(T);
    if (status) {
      dtostrf(T, 0, 1, RemoteXY.text_2);
      Serial.print(T, 1);
    }
  }

  // Считываем давление (с компенсированной температурой)
  status = pressure.startPressure(3);
  if (status) {
    delay(status);
    status = pressure.getPressure(P, T);
    if (status) {
      double bar_mmHg = P * 0.7500637554192;
      dtostrf(bar_mmHg, 0, 1, RemoteXY.text_1);
      Serial.print(bar_mmHg, 1);

      // Обновляем LCD
      lcd.setCursor(4, 0);
      lcd.print("Temp:");
      lcd.print(T, 1);
      lcd.setCursor(4, 1);
      lcd.print("Bar:");
      lcd.print(bar_mmHg, 1);

      // Подсветка ленты по температуре
      uint32_t color;
      if      (T < 7)   color = 0xFFFF00;  // желтый
      else if (T < 15)  color = 0x00FF00;  // зеленый
      else if (T < 25)  color = 0x0000FF;  // синий
      else if (T < 30)  color = 0xFF00FF;  // фиолетовый
      else               color = 0xFF0000; // красный

      for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, color);
      }
      strip.show();
      delay(1000);
    }
  }
}

