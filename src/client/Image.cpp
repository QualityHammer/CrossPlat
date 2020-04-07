#include "Image.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <cmath>

namespace ImagePack {
    namespace Draw {
        void rectangle(Image &img, const size_t img_w, const size_t img_h,
                        const size_t x, const size_t y, const size_t w,
                        const size_t h, const Pixel color) {
            for (size_t i{0}; i < w; i++) {
                for (size_t j{0}; j < h; j++) {
                    size_t cx = x + i;
                    size_t cy = y + j;
                    if (cx >= img_w || cy >= img_h) continue;
                    img[cx + cy * img_w] = color;
                }
            }
        }
    }

    const Pixel packColor(const u8 r, const u8 g, const u8 b, const u8 a) {
        return {r, g, b, a};
    }

    void ppmImageCreate(const std::string filename, const Image &image,
                        const size_t w, const size_t h) {
        assert(image.size() == w * h);
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "P6\n" << w << " " << h << "\n255\n";
        for (size_t i{0}; i < h * w; ++i) {
            ofs << static_cast<char>(image[i].r)
                << static_cast<char>(image[i].g)
                << static_cast<char>(image[i].b);
        }
        ofs.close();
    }

    void generateImage() {
        constexpr size_t win_w{1024};
        constexpr size_t win_h{512};
        Image framebuffer{win_w * win_h, packColor(255, 255, 255)};

        const size_t map_w = 16; // map width
        const size_t map_h = 16; // map height
        const char gMap[] = "0000222222220000"\
                           "1              0"\
                           "1      11111   0"\
                           "1     0        0"\
                           "0     0  1110000"\
                           "0     3        0"\
                           "0   10000      0"\
                           "0   0   11100  0"\
                           "0   0   0      0"\
                           "0   0   1  00000"\
                           "0       1      0"\
                           "2       1      0"\
                           "0       0      0"\
                           "0 0000000      0"\
                           "0              0"\
                           "0002222222200000"; // our game map
        assert(sizeof(gMap) == map_w*map_h+1); // +1 for the null terminated string
        float player_x{3.456};
        float player_y{2.345};
        float player_a{1.323};
        const float fov{M_PI / 3};

        // Create map overlay
        const size_t rect_w{win_w / (map_w * 2)};
        const size_t rect_h{win_h / map_h};
        for (size_t j{0}; j < map_h; j++) {
            for (size_t i{0}; i < map_w; i++) {
                if (gMap[i + j * map_w] == ' ') continue;
                size_t rect_x{i * rect_w};
                size_t rect_y{j * rect_h};
                Draw::rectangle(framebuffer, win_w, win_h, rect_x,
                                rect_y, rect_w, rect_h,
                                packColor(0, 255, 255));
            }
        }

        // Fov tracer
        for (size_t i{0}; i < win_w / 2; i++) {
            float angle{player_a - fov / 2 + fov * i / float(win_w / 2)};
            for (float t{0.0}; t < 20.0; t += 0.05) {
                float cx{player_x + t * std::cos(angle)};
                float cy{player_y + t * std::sin(angle)};

                size_t pix_x{cx * rect_w};
                size_t pix_y{cy * rect_h};
                framebuffer[pix_x + pix_y * win_w] = packColor(160, 160, 160);

                if (gMap[int(cx) + int(cy) * map_w] != ' ') {
                    size_t column_height{win_h / t};
                    Draw::rectangle(framebuffer, win_w, win_h, win_w / 2 + i,
                                    win_h / 2 - column_height / 2, 1,
                                    column_height, packColor(0, 255, 255));
                    break;
                }
            }
        }

        ppmImageCreate("./out.ppm", framebuffer, win_w, win_h);
    }
}
