````md
<p align="center">
  <a href="https://github.com/rembov/bmp180-neopixel-remote">
    <img src="https://img.shields.io/badge/Arduino-v1.0.0-blue.svg" alt="Version" />
    <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License" />
    <img src="https://img.shields.io/badge/Platform-Arduino-orange.svg" alt="Platform" />
    <img src="https://img.shields.io/badge/Language-C++-yellow.svg" alt="Language" />
  </a>
</p>

<h1 align="center">bmp180-neopixel-remote</h1>
<p align="center">
  <strong>🌡️📟 Управление NeoPixel и мониторинг BMP180 через RemoteXY</strong>
</p>

---

## 📖 Описание

Проект на Arduino для:
- Считывания **температуры** и **давления** с датчика BMP180  
- Отображения данных на **LCD I²C** дисплее (адрес 0x38)  
- Отправки значений на смартфон через **HC-05** 
- Управления **NeoPixel** лентой (пин 13, 155 светодиодов) по температурным порогам

---

## 🔧 Необходимые библиотеки

<details>
  <summary>📚 Список</summary>

  - `SFE_BMP180` — датчик BMP180  
  - `LiquidCrystal_I2C` — I²C LCD 16×2  
  - `Adafruit NeoPixel` — управление RGB-лентой  
  - `RemoteXY` — мобильный интерфейс  
</details>

---

## ⚙️ Настройка

<details>
  <summary>1. Клонирование репозитория</summary>

  ```bash
  git clone https://github.com/rembov/bmp180-neopixel-remote.git
  cd bmp180-neopixel-remote
````

</details>

<details>
  <summary>2. Установка библиотек</summary>

Откройте **Arduino IDE → Sketch → Include Library → Manage Libraries…** и установите:

* SFE\_BMP180
* LiquidCrystal\_I2C
* Adafruit NeoPixel
* RemoteXY

</details>

<details>
  <summary>3. Подключение оборудования</summary>

| Модуль                | Пины           |
| --------------------- | -------------- |
| BMP180 (I²C)          | SDA, SCL       |
| LCD 16×2 (I²C, 0x38)  | SDA, SCL       |
| NeoPixel-лента        | Pin 13         |
| HC-05 (SoftSerial)    | RX — 8, TX — 9 |
| GND, 5V               | Общие шины     |

</details>

---

## 🚀 Использование

<details>
  <summary>Запуск</summary>

1. Откройте `bmp180-neopixel-remote.ino` в Arduino IDE.
2. Выберите плату **Arduino Uno** и правильный COM‑порт.
3. Загрузите скетч.
4. Подключитесь к Bluetooth-модулю в приложении **RemoteXY** на скорости **9600**.

</details>

<details>
  <summary>Интерфейс RemoteXY</summary>

* `RemoteXY.text_2` — температура (°C)
* `RemoteXY.text_1` — давление (мм рт. ст.)
* `RemoteXY.connect_flag` — флаг соединения

</details>

<details>
  <summary>Лента NeoPixel</summary>

Цвета по температуре:

* <span style="color:#FFFF00">Жёлтый</span> — T < 7°C
* <span style="color:#00FF00">Зелёный</span> — 7 ≤ T < 15°C
* <span style="color:#0000FF">Синий</span> — 15 ≤ T < 25°C
* <span style="color:#FF00FF">Фиолет</span> — 25 ≤ T < 30°C
* <span style="color:#FF0000">Красный</span> — T ≥ 30°C

</details>

---

## ✨ Структура проекта

```
bmp180-neopixel-remote/
├── bmp180-neopixel-remote.ino
└── README.md       
```

---


