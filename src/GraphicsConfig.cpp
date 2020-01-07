//
// Created by tia on 2020/01/02.
//

#include <cstdint>
#include <cstdarg>

#include "GraphicsConfig.h"

namespace graphics_config {

#include "font/hankaku.c"

    GraphicsConfig::GraphicsConfig(_GraphicsConfig *graphics_config) {
        frame_buffer = graphics_config->framebuffer;
        width = graphics_config->info.HorizontalResolution;
        height = graphics_config->info.VerticalResolution;
        pixel_format = graphics_config->info.PixelFormat;
        pixel_information = graphics_config->info.PixelInformation;
        pixel_per_scan_line = graphics_config->info.PixelsPerScanLine;
        version = graphics_config->info.Version;

        console_width = width / 8;
        console_height = height / 16;
    }

    uint64_t GraphicsConfig::get_console_width() { return console_width; }

    uint64_t GraphicsConfig::get_console_height() { return console_height; }

    void GraphicsConfig::fill_screen(uint32_t color) {
        uint64_t *b;
        const uint64_t c = (uint64_t) color << 32u | color;
        b = (uint64_t *) frame_buffer;

        for (uint64_t i = 0; i < width * height / 2; i++) {
            *(b++) = c;
        }
    }

    bool GraphicsConfig::draw_pixel(uint64_t x, uint64_t y, uint32_t color) {
        if (x >= width || y >= height)
            return false;

        uint64_t p = x + (y * width);
        *((uint32_t *) frame_buffer + p) = color;
        return true;
    }

    bool GraphicsConfig::draw_char(char c, uint64_t x, uint64_t y, uint32_t color) {
        uint8_t *f = FONT[c];
        bool ret = false;

        for (uint64_t i = 0; i < 16; i++) {
            for (uint64_t j = 0; j < 8; j++) {
                uint8_t a = f[i] & (0b10000000u >> j);
                if (a) {
                    ret |= !draw_pixel(x + j, y + i, color);
                }
            }
        }

        return !ret;
    }

    bool GraphicsConfig::draw_char(char c, uint64_t x, uint64_t y, uint32_t color, uint32_t bg_color) {
        uint8_t *f = FONT[c];
        bool ret = false;

        for (uint64_t i = 0; i < 16; i++) {
            for (uint64_t j = 0; j < 8; j++) {
                uint8_t a = f[i] & (0b10000000u >> j);
                if (a) {
                    ret |= !draw_pixel(x + j, y + i, color);
                } else {
                    ret |= !draw_pixel(x + j, y + i, bg_color);
                }
            }
        }

        return !ret;
    }

    bool GraphicsConfig::put_char(char c, uint64_t x, uint64_t y, uint32_t color) {
        return draw_char(c, x * 8, y * 16, color);
    }

    bool GraphicsConfig::put_char(char c, uint64_t x, uint64_t y, uint32_t color, uint32_t bg_color) {
        return draw_char(c, x * 8, y * 16, color, bg_color);
    }

    bool GraphicsConfig::put_string(const char *str, uint64_t x, uint64_t y, uint32_t color) {
        bool ret = false;
        for (uint64_t i = 0; str[i]; i++) {
            ret |= !put_char(str[i], x, y, color);
            x++;
            y += x / console_width;
            x = x % console_width;
        }
        return !ret;
    }

    bool GraphicsConfig::put_string(const char *str, uint64_t x, uint64_t y, uint32_t color, uint32_t bg_color) {
        bool ret = false;
        for (uint64_t i = 0; str[i]; i++) {
            ret |= !put_char(str[i], x, y, color, bg_color);
            x++;
            y += x / console_width;
            x = x % console_width;
        }
        return !ret;
    }

    bool GraphicsConfig::put_strings(uint64_t x, uint64_t y, uint32_t color, ...) {
        va_list ap;
        va_start(ap, color);
        bool ret = false;

        for (uint64_t v = 0;; v++) {
            char *str = va_arg(ap, char*);
            if (str == ((char *) nullptr)) break;
            for (uint64_t i = 0; str[i]; i++) {
                ret |= !put_char(str[i], x, y, color);
                x++;
                y += x / console_width;
                x = x % console_width;
            }
        }
        return !ret;
    }

    bool GraphicsConfig::put_strings(uint64_t x, uint64_t y, uint32_t color, uint32_t bg_color, ...) {
        va_list ap;
        va_start(ap, bg_color);
        bool ret = false;

        for (uint64_t v = 0;; v++) {
            char *str = va_arg(ap, char*);
            if (str == ((char *) nullptr)) break;
            for (uint64_t i = 0; str[i]; i++) {
                ret |= !put_char(str[i], x, y, color, bg_color);
                x++;
                y += x / console_width;
                x = x % console_width;
            }
        }
        return !ret;
    }


}
