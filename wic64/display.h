#ifndef WIC64_DISPLAY_H
#define WIC64_DISPLAY_H

#include <cstdint>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
#include "WString.h"
#include "Wire.h"

namespace WiC64 {
    class Display {
        public:
            static const char* TAG;

            Display();
            void setRotation(uint8_t rotation);
            void setIp(String ip);
            void resetIp(void);
            void setSSID(String ssid);
            void setRSSI(int8_t rssi);
            void setStatus(String status);

        private:
            const int I2C_SDA_PIN = 13;
            const int I2C_SCL_PIN = 15;
            const int8_t RESET_PIN_NOT_CONNECTED = -1;

            const uint8_t WIDTH = 128;
            const uint8_t HEIGHT = 64;

            const GFXfont* FONT_BUILTIN = NULL;         // builtin 6x8 font
            const GFXfont* FONT_BIG = &FreeSerif9pt7b;  // big font used for IP
            static const uint8_t MAX_CHARS_FOR_RSSI = 8;
            static const uint8_t MAX_CHARS_PER_LINE = 21;

            Adafruit_SSD1306 *display;
            uint8_t rotation = 0;
            String ip = "";
            String ssid = "";
            String status = "";

            char rssi[MAX_CHARS_FOR_RSSI+1] = "";
            char line[MAX_CHARS_PER_LINE+1] = "";

            void update(void);
            char* abbreviated(String string);
            char* abbreviated(String string, uint8_t width);
            void printStatusAndRSSI(void);

            const unsigned char logo[128*64/8] PROGMEM = {
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x80, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x01, 0xff, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x03, 0xff, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0xff, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x07, 0xc0, 0x08, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x07, 0xc0, 0x38, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0x78, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0x78, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            };
    };
    }
#endif // WIC64_DISPLAY_H
