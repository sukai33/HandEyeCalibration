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
#ifndef STREAM_TYPES_H
#define STREAM_TYPES_H

#include "body_types.h"
#include "depth_types.h"
#include "color_types.h"
#include "hand_types.h"
#include "image_types.h"

#if __GNUC__
    #define ASTRA_ALIGN(X) __attribute__((__aligned__(X)))
#elif _MSC_VER
    #define ASTRA_ALIGN(X) __declspec(align(X))
#else
    #error "Unsupported compiler"
#endif

// https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
// http://stackoverflow.com/questions/3350852/how-to-correctly-fix-zero-sized-array-in-struct-union-warning-c4200-without

struct _astra_imageframe {
    union {
        astra_frame_t* frame;
        uint64_t pad0;
    };

    astra_image_metadata_t metadata;
    union {
        void* data;
        uint64_t pad1;
    };
};

struct _astra_handframe {
    union {
        astra_frame_t* frame;
        uint64_t pad0;
    };
    size_t handCount;
    union {
        astra_handpoint_t* handpoints;
        uint64_t pad1;
    };
};

struct _astra_bodyframe {
    union {
        astra_frame_t* frame;
        uint64_t pad0;
    };
    astra_bodyframe_info_t info;
    ASTRA_ALIGN(32) astra_bodymask_t bodyMask;
    astra_floor_info_t floorInfo;
    astra_body_list_t bodyList;
};

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4200 )
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc99-extensions"
#endif

typedef struct _astra_imageframe_wrapper {
    _astra_imageframe frame;
    ASTRA_ALIGN(32) char frame_data[];
} astra_imageframe_wrapper_t;

typedef struct _astra_handframe_wrapper {
    _astra_handframe frame;
    char frame_data[];
} astra_handframe_wrapper_t;

typedef struct _astra_bodyframe_wrapper {
    _astra_bodyframe frame;
    char frame_data[];
} astra_bodyframe_wrapper_t;

#if defined(_MSC_VER)
#pragma warning( pop )
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif /* STREAM_TYPES_H */
