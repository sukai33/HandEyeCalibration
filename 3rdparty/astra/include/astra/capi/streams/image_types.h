// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015-2017 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#ifndef IMAGE_TYPES_H
#define IMAGE_TYPES_H

#include <stdint.h>
#include <astra_core/capi/astra_types.h>

typedef uint32_t astra_pixel_format_t;

typedef enum {
    ASTRA_PIXEL_FORMAT_UNKNOWN = 0,
    ASTRA_PIXEL_FORMAT_DEPTH_MM = 100,

    // color layouts
    ASTRA_PIXEL_FORMAT_RGB888 = 200,
    ASTRA_PIXEL_FORMAT_YUV422 = 201,
    ASTRA_PIXEL_FORMAT_YUYV = 202,
    ASTRA_PIXEL_FORMAT_RGBA = 203,
    ASTRA_PIXEL_FORMAT_NV21 = 204,
    ASTRA_PIXEL_FORMAT_GRAY8 = 300,
    ASTRA_PIXEL_FORMAT_GRAY16 = 301,

    ASTRA_PIXEL_FORMAT_POINT = 400,

} astra_pixel_formats;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} astra_rgb_pixel_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t alpha;
} astra_rgba_pixel_t;


typedef struct {
    uint32_t width;
    uint32_t height;
    astra_pixel_format_t pixelFormat;
} astra_image_metadata_t;

typedef struct {
    uint32_t id;
    uint32_t width;
    uint32_t height;
    astra_pixel_format_t pixelFormat;
    uint8_t fps;
} astra_imagestream_mode_t;

typedef struct _astra_imageframe* astra_imageframe_t;
typedef astra_streamconnection_t astra_imagestream_t;

#endif // IMAGE_TYPES_H
