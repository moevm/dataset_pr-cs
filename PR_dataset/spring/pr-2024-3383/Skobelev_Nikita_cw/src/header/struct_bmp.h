//
// Created by niks on 27.04.2024.
//

#ifndef CW_STRUCT_BMP_H
#define CW_STRUCT_BMP_H
#include <bits/stdc++.h>
#pragma pack(push,1)
struct BMP_file_header {
    //char file_type[2];
    uint16_t file_type{0x4D42};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{0};
};
struct BMP_info_header {
    uint32_t size{0 };
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{0};
    uint32_t compression{0};
    uint32_t image_size{0};
    int32_t x_resolution{0};
    int32_t y_resolution{0};
    uint32_t colors {0};
    uint32_t important_colors{0};
};
#pragma pack(pop)
#endif //CW_STRUCT_BMP_H
