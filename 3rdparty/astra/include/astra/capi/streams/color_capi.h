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
#ifndef COLOR_CAPI_H
#define COLOR_CAPI_H

#include <astra_core/capi/astra_types.h>
#include "color_types.h"
#include <stdbool.h>

ASTRA_BEGIN_DECLS

/**
 * \defgroup color_ref color stream apis
 * \ingroup c_low_api_ref
 * @{
 */
ASTRA_API_EX astra_status_t astra_reader_get_colorstream(astra_reader_t reader,
                                                         astra_colorstream_t* colorStream);

ASTRA_API_EX astra_status_t astra_colorstream_is_available(astra_colorstream_t colorStream,
                                                           bool* isAvailable);

ASTRA_API_EX astra_status_t astra_colorstream_get_usb_info(astra_colorstream_t colorStream,
                                                           astra_usb_info_t* usbInfo);

ASTRA_API_EX astra_status_t astra_frame_get_colorframe(astra_reader_frame_t readerFrame,
                                                       astra_colorframe_t* colorFrame);

ASTRA_API_EX astra_status_t astra_frame_get_colorframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                    astra_stream_subtype_t subtype,
                                                                    astra_colorframe_t* colorFrame);

ASTRA_API_EX astra_status_t astra_colorframe_get_data_byte_length(astra_colorframe_t colorFrame,
                                                                  uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_colorframe_get_data_ptr(astra_colorframe_t colorFrame,
                                                          uint8_t** data,
                                                          uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_colorframe_get_data_rgb_ptr(astra_colorframe_t colorFrame,
                                                              astra_rgb_pixel_t** data,
                                                              uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_colorframe_copy_data(astra_colorframe_t colorFrame,
                                                       uint8_t* data);

ASTRA_API_EX astra_status_t astra_colorframe_get_metadata(astra_colorframe_t colorFrame,
                                                          astra_image_metadata_t* metadata);

ASTRA_API_EX astra_status_t astra_colorframe_get_frameindex(astra_colorframe_t colorFrame,
                                                            astra_frame_index_t* index);
/** @} */
ASTRA_END_DECLS

#endif /* COLOR_CAPI_H */
