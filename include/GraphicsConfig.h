//
// Created by tia on 2020/01/02.
//

#ifndef TIEOS_GRAPHICSCONFIG_H
#define TIEOS_GRAPHICSCONFIG_H


#include <cstdint>

namespace graphics_config {

    extern uint8_t FONT0[0x100][16];

    enum EFI_GRAPHICS_PIXEL_FORMAT {
        PixelRedGreenBlueReserved8BitPerColor,
        PixelBlueGreenRedReserved8BitPerColor,
        PixelBitMask,
        PixelBltOnly,
        PixelFormatMax
    };

    struct _EFI_PIXEL_BITMASK {
        uint32_t            RedMask;
        uint32_t            GreenMask;
        uint32_t            BlueMask;
        uint32_t            ReservedMask;
    };

    struct _EFI_GRAPHICS_OUTPUT_MODE_INFORMATION {
        uint32_t                            Version;
        uint32_t                            HorizontalResolution;
        uint32_t                            VerticalResolution;
        enum EFI_GRAPHICS_PIXEL_FORMAT      PixelFormat;
        struct _EFI_PIXEL_BITMASK            PixelInformation;
        uint32_t                            PixelsPerScanLine;
    };

    struct _GraphicsConfig {
        uint8_t *framebuffer;
        struct _EFI_GRAPHICS_OUTPUT_MODE_INFORMATION info;
    };

    class GraphicsConfig {
    private:
        uint8_t *frame_buffer;
        uint32_t width;
        uint32_t height;
        EFI_GRAPHICS_PIXEL_FORMAT pixel_format;
        _EFI_PIXEL_BITMASK pixel_information;
        uint32_t pixel_per_scan_line;
        uint32_t version;

        uint64_t console_width;
        uint64_t console_height;

    public:
        GraphicsConfig() {}
        GraphicsConfig(_GraphicsConfig*);

        uint64_t get_console_width();
        uint64_t get_console_height();

        void fill_screen(uint32_t);
        bool draw_pixel(uint64_t x, uint64_t y, uint32_t color);
        bool draw_char(char c, uint64_t x, uint64_t y, uint32_t color);
        bool draw_char(char c, uint64_t x, uint64_t y, uint32_t color, uint32_t bg_color);
        bool put_char(char c, uint64_t x, uint64_t y, uint32_t color);
        bool put_char(char c, uint64_t x, uint64_t y, uint32_t color, uint32_t bg_color);
        bool put_string(const char * str, uint64_t x, uint64_t y, uint32_t color);
        bool put_string(const char * str, uint64_t x, uint64_t y, uint32_t color, uint32_t bg_color);
        bool put_strings(uint64_t x, uint64_t y, uint32_t color, ...);
        bool put_strings(uint64_t x, uint64_t y, uint32_t color, uint32_t bg_color, ...);
    };
}

#endif //TIEOS_GRAPHICSCONFIG_H
