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
#ifndef POINT_CAPI_H
#define POINT_CAPI_H

#include <astra_core/capi/astra_types.h>
#include "point_types.h"

ASTRA_BEGIN_DECLS

/**
 * \defgroup point_ref point stream apis
 * \ingroup c_high_api_ref
 * @{
 */
ASTRA_API_EX astra_status_t astra_reader_get_pointstream(astra_reader_t reader,
                                                                  astra_pointstream_t* pointStream);

ASTRA_API_EX astra_status_t astra_pointstream_is_available(astra_pointstream_t pointStream,
                                                           bool* isAvailable);

ASTRA_API_EX astra_status_t astra_frame_get_pointframe(astra_reader_frame_t readerFrame,
                                                                astra_pointframe_t* pointFrame);

ASTRA_API_EX astra_status_t astra_frame_get_pointframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                             astra_stream_subtype_t subtype,
                                                                             astra_pointframe_t* pointFrame);

ASTRA_API_EX astra_status_t astra_pointframe_get_data_byte_length(astra_pointframe_t pointFrame,
                                                                           uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_pointframe_get_data_ptr(astra_pointframe_t pointFrame,
                                                                   astra_vector3f_t** data,
                                                                   uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_pointframe_copy_data(astra_pointframe_t pointFrame,
                                                                astra_vector3f_t* data);

ASTRA_API_EX astra_status_t astra_pointframe_get_metadata(astra_pointframe_t pointFrame,
                                                                   astra_image_metadata_t* metadata);

ASTRA_API_EX astra_status_t astra_pointframe_get_frameindex(astra_pointframe_t pointFrame,
                                                                     astra_frame_index_t* index);
/** @} */
ASTRA_END_DECLS

#endif /* POINT_CAPI_H */
