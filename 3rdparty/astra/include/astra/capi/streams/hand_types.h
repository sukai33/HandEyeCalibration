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
#ifndef HAND_TYPES_H
#define HAND_TYPES_H

#include <astra_core/capi/astra_types.h>
#include <astra/capi/astra_ctypes.h>

#define ASTRA_HANDS_MAX_HAND_COUNT 10

typedef enum {
    DEBUG_HAND_VIEW_DEPTH,
    DEBUG_HAND_VIEW_VELOCITY,
    DEBUG_HAND_VIEW_FILTEREDVELOCITY,
    DEBUG_HAND_VIEW_UPDATE_SEGMENTATION,
    DEBUG_HAND_VIEW_CREATE_SEGMENTATION,
    DEBUG_HAND_VIEW_UPDATE_SEARCHED,
    DEBUG_HAND_VIEW_CREATE_SEARCHED,
    DEBUG_HAND_VIEW_CREATE_SCORE,
    DEBUG_HAND_VIEW_UPDATE_SCORE,
    DEBUG_HAND_VIEW_HANDWINDOW,
    DEBUG_HAND_VIEW_DEPTH_MOD,
    DEBUG_HAND_VIEW_DEPTH_AVG,
    DEBUG_HAND_VIEW_TEST_PASS_MAP,
} astra_debug_hand_view_type_t;

typedef enum {
    HAND_STATUS_NOTTRACKING,
    HAND_STATUS_CANDIDATE,
    HAND_STATUS_TRACKING,
    HAND_STATUS_LOST
} astra_handstatus_t;

typedef struct {
    int32_t trackingId;
    astra_handstatus_t status;
    astra_vector2i_t depthPosition;
    astra_vector3f_t worldPosition;
    astra_vector3f_t worldDeltaPosition;
} astra_handpoint_t;

typedef struct _astra_handframe* astra_handframe_t;
typedef astra_streamconnection_t astra_handstream_t;

typedef struct _astra_imageframe* astra_debug_handframe_t;
typedef astra_streamconnection_t astra_debug_handstream_t;

#endif // HAND_TYPES_H
