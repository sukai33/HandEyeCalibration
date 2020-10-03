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
#ifndef ASTRA_PLUGIN_H
#define ASTRA_PLUGIN_H

#include "../astra_core.h"
#include "astra_plugin_callbacks.h"
#include "astra_pluginservice_proxy.h"

struct _astra_streamconnection {
    astra_streamconnection_handle_t handle;
    astra_stream_desc_t desc;
};

struct _astra_reader_callback_id {
    astra_reader_t reader;
    astra_callback_id_t callbackId;
};

struct _astra_frame {
    uint32_t byteLength;
    astra_frame_index_t frameIndex;
    union {
        void* data;
        uint64_t pad0;
    };
};

struct astra_plugin_info_t {
    astra_version_info_t versionInfo;
};

#endif /* ASTRA_PLUGIN_H */
