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
#ifndef COLORIZED_BODY_CAPI_H
#define COLORIZED_BODY_CAPI_H

#include <astra_core/capi/astra_types.h>
#include "colorized_body_types.h"

ASTRA_BEGIN_DECLS

/**
 * \defgroup colorized_body_ref colorized body stream apis
 * \ingroup c_high_api_ref
 * @{
 */
ASTRA_API_EX astra_status_t astra_reader_get_colorizedbodystream(astra_reader_t reader,
                                                                  astra_colorizedbodystream_t* colorizedbodyStream);

ASTRA_API_EX astra_status_t astra_colorizedbodystream_is_available(astra_colorizedbodystream_t colorizedbodyStream,
                                                                   bool* isAvailable);

ASTRA_API_EX astra_status_t astra_frame_get_colorizedbodyframe(astra_reader_frame_t readerFrame,
                                                                astra_colorizedbodyframe_t* colorizedbodyFrame);

ASTRA_API_EX astra_status_t astra_frame_get_colorizedbodyframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                             astra_stream_subtype_t subtype,
                                                                             astra_colorizedbodyframe_t* colorizedbodyFrame);

ASTRA_API_EX astra_status_t astra_colorizedbodyframe_get_data_byte_length(astra_colorizedbodyframe_t colorizedbodyFrame,
                                                                        uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_colorizedbodyframe_get_data_ptr(astra_colorizedbodyframe_t colorizedbodyFrame,
                                                                astra_rgba_pixel_t** data,
                                                                uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_colorizedbodyframe_copy_data(astra_colorizedbodyframe_t colorizedbodyFrame,
                                                              astra_rgba_pixel_t* data);

ASTRA_API_EX astra_status_t astra_colorizedbodyframe_get_metadata(astra_colorizedbodyframe_t colorizedbodyFrame,
                                                                   astra_image_metadata_t* metadata);

ASTRA_API_EX astra_status_t astra_colorizedbodyframe_get_frameindex(astra_colorizedbodyframe_t colorizedbodyFrame,
                                                                     astra_frame_index_t* index);
/** @} */
ASTRA_END_DECLS

#endif /* COLORIZED_BODY_CAPI_H */
