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
#ifndef MASKED_COLOR_CAPI_H
#define MASKED_COLOR_CAPI_H

#include <astra_core/capi/astra_types.h>
#include "masked_color_types.h"

ASTRA_BEGIN_DECLS

/**
 * \defgroup masked_color_ref masked color stream apis
 * \ingroup c_high_api_ref
 * @{
 */
ASTRA_API_EX astra_status_t astra_reader_get_maskedcolorstream(astra_reader_t reader,
                                                                  astra_maskedcolorstream_t* maskedcolorStream);

ASTRA_API_EX astra_status_t astra_maskedcolorstream_is_available(astra_maskedcolorstream_t maskedcolorStream,
                                                                 bool* isAvailable);

ASTRA_API_EX astra_status_t astra_frame_get_maskedcolorframe(astra_reader_frame_t readerFrame,
                                                                astra_maskedcolorframe_t* maskedcolorFrame);

ASTRA_API_EX astra_status_t astra_frame_get_maskedcolorframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                             astra_stream_subtype_t subtype,
                                                                             astra_maskedcolorframe_t* maskedcolorFrame);

ASTRA_API_EX astra_status_t astra_maskedcolorframe_get_data_byte_length(astra_maskedcolorframe_t maskedcolorFrame,
                                                                        uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_maskedcolorframe_get_data_ptr(astra_maskedcolorframe_t maskedcolorFrame,
                                                                astra_rgba_pixel_t** data,
                                                                uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_maskedcolorframe_copy_data(astra_maskedcolorframe_t maskedcolorFrame,
                                                              astra_rgba_pixel_t* data);

ASTRA_API_EX astra_status_t astra_maskedcolorframe_get_metadata(astra_maskedcolorframe_t maskedcolorFrame,
                                                                   astra_image_metadata_t* metadata);

ASTRA_API_EX astra_status_t astra_maskedcolorframe_get_frameindex(astra_maskedcolorframe_t maskedcolorFrame,
                                                                     astra_frame_index_t* index);
/** @} */
ASTRA_END_DECLS

#endif /* MASKED_COLOR_CAPI_H */
