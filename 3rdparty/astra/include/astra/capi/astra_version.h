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
#ifndef ASTRA_VERSION_H
#define ASTRA_VERSION_H

#include <astra_core/capi/astra_defines.h>
#include <astra_core/capi/astra_types.h>

ASTRA_BEGIN_DECLS

/**
 * \ingroup c_ref
 * get current sdk version.
 * @param info structure of astra_version_info_t, shouldn't be null.
 */
ASTRA_API_EX astra_status_t astra_version(astra_version_info_t* info);

ASTRA_END_DECLS

#endif /* ASTRA_VERSION_H */
