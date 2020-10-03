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
#ifndef HOST_EVENTS_H
#define HOST_EVENTS_H

#include "astra_defines.h"
#include "astra_types.h"
#include <stddef.h>
#include <stdint.h>

ASTRA_BEGIN_DECLS

ASTRA_API astra_status_t astra_notify_host_event(astra_event_id id, const void* data, uint32_t dataSize);
ASTRA_API astra_status_t astra_notify_resource_available(const char* resourceURI);
ASTRA_API astra_status_t astra_notify_resource_unavailable(const char* resourceURI);

enum {
    ASTRA_EVENT_RESOURCE_AVAILABLE = 1,
    ASTRA_EVENT_RESOURCE_UNAVAILABLE = 2,
    ASTRA_EVENT_OPENNI_CONTROL = 3
};

ASTRA_END_DECLS

#endif /* HOST_EVENTS_H */
