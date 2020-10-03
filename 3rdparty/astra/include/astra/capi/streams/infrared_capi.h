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
#ifndef INFRARED_CAPI_H
#define INFRARED_CAPI_H

#include <astra_core/capi/astra_defines.h>
#include <astra_core/capi/astra_types.h>
#include <astra/capi/streams/infrared_types.h>
#include <stdbool.h>

ASTRA_BEGIN_DECLS

/**
 * \defgroup infrared_ref infrared stream apis
 * \ingroup c_low_api_ref
 * @{
 */
ASTRA_API_EX astra_status_t astra_reader_get_infraredstream(astra_reader_t reader,
                                                            astra_infraredstream_t* infraredstream);

ASTRA_API_EX astra_status_t astra_infraredstream_is_available(astra_infraredstream_t infraredStream,
                                                              bool* isAvailable);

ASTRA_API_EX astra_status_t astra_infraredstream_get_hfov(astra_infraredstream_t infraredstream,
                                                          float* hFov);

ASTRA_API_EX astra_status_t astra_infraredstream_get_vfov(astra_infraredstream_t infraredstream,
                                                          float* vFov);

ASTRA_API_EX astra_status_t astra_infraredstream_get_usb_info(astra_infraredstream_t infraredStream,
                                                              astra_usb_info_t* usbInfo);

ASTRA_API_EX astra_status_t astra_frame_get_infraredframe(astra_reader_frame_t readerFrame,
                                                          astra_infraredframe_t* infraredframe);

ASTRA_API_EX astra_status_t astra_frame_get_infraredframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                       astra_stream_subtype_t subtype,
                                                                       astra_infraredframe_t* colorFrame);

ASTRA_API_EX astra_status_t astra_infraredframe_get_data_byte_length(astra_infraredframe_t infraredframe,
                                                                     uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_infraredframe_get_data_ptr(astra_infraredframe_t infraredframe,
                                                             uint8_t** data,
                                                             uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_infraredframe_copy_data(astra_infraredframe_t infraredframe,
                                                          uint8_t* data);

ASTRA_API_EX astra_status_t astra_infraredframe_get_metadata(astra_infraredframe_t infraredframe,
                                                             astra_image_metadata_t* metadata );

ASTRA_API_EX astra_status_t astra_infraredframe_get_frameindex(astra_infraredframe_t infraredframe,
                                                               astra_frame_index_t* index);
/** @} */

ASTRA_END_DECLS


#endif /* INFRARED_CAPI_H */
