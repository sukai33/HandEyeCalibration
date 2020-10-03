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
#ifndef DEPTH_CAPI_H
#define DEPTH_CAPI_H

#include <astra_core/capi/astra_defines.h>
#include <astra_core/capi/astra_types.h>
#include <astra/capi/streams/depth_types.h>
#include <stdbool.h>

#define ASTRA_SERIAL_NUMBER_MAX 256

ASTRA_BEGIN_DECLS

/**
 * \defgroup depth_ref depth stream apis
 * \ingroup c_low_api_ref
 * @{
 */
ASTRA_API_EX astra_status_t astra_convert_depth_to_world(astra_depthstream_t depthStream,
                                                         float depthX, float depthY, float depthZ,
                                                         float* pWorldX, float* pWorldY, float* pWorldZ);

ASTRA_API_EX astra_status_t astra_convert_world_to_depth(astra_depthstream_t depthStream,
                                                         float worldX, float worldY, float worldZ,
                                                         float* pDepthX, float* pDepthY, float* pDepthZ);

ASTRA_API_EX astra_status_t astra_reader_get_depthstream(astra_reader_t reader,
                                                         astra_depthstream_t* depthStream);

ASTRA_API_EX astra_status_t astra_depthstream_is_available(astra_depthstream_t depthStream,
                                                           bool* isAvailable);

ASTRA_API_EX astra_status_t astra_depthstream_get_depth_to_world_data(astra_depthstream_t depthStream,
                                                                      astra_conversion_cache_t* conversionData);

ASTRA_API_EX astra_status_t astra_depthstream_get_hfov(astra_depthstream_t depthStream,
                                                       float* hFov);

ASTRA_API_EX astra_status_t astra_depthstream_get_vfov(astra_depthstream_t depthStream,
                                                       float* vFov);

ASTRA_API_EX astra_status_t astra_depthstream_get_registration(astra_depthstream_t depthStream,
                                                               bool* enabled);

ASTRA_API_EX astra_status_t astra_depthstream_set_registration(astra_depthstream_t depthStream,
                                                               bool enabled);

/**
 * get depth to color resolution if device supports.
 * @param mode refer to device.
 */
ASTRA_API_EX astra_status_t astra_depthstream_get_d2c_resolution(astra_depthstream_t depthStream,
                                                              int *mode);

/**
 * set depth to color resolution if device supports.
 * @param mode refer to device.
 */
ASTRA_API_EX astra_status_t astra_depthstream_set_d2c_resolution(astra_depthstream_t depthStream,
                                                              int mode);
                                                               
ASTRA_API_EX astra_status_t astra_depthstream_get_serialnumber(astra_depthstream_t depthStream,
                                                               char* serialnumber,
                                                               uint32_t length);

ASTRA_API_EX astra_status_t astra_depthstream_get_chip_id(astra_depthstream_t depthStream,
                                                          uint32_t* chipId);

ASTRA_API_EX astra_status_t astra_depthstream_get_usb_info(astra_depthstream_t depthStream,
	                                                   astra_usb_info_t* usbInfo);

ASTRA_API_EX astra_status_t astra_depthstream_start_record(astra_depthstream_t depthStream,
                                                           const char* filename);

ASTRA_API_EX astra_status_t astra_depthstream_stop_record(astra_depthstream_t depthStream);

ASTRA_API_EX astra_status_t astra_frame_get_depthframe(astra_reader_frame_t readerFrame,
                                                       astra_depthframe_t* depthFrame);

ASTRA_API_EX astra_status_t astra_frame_get_depthframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                    astra_stream_subtype_t subtype,
                                                                    astra_depthframe_t* colorFrame);

ASTRA_API_EX astra_status_t astra_depthframe_get_data_byte_length(astra_depthframe_t depthFrame,
                                                                  uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_depthframe_get_data_ptr(astra_depthframe_t depthFrame,
                                                          int16_t** data,
                                                          uint32_t* byteLength);

ASTRA_API_EX astra_status_t astra_depthframe_copy_data(astra_depthframe_t depthFrame,
                                                       int16_t* data);

ASTRA_API_EX astra_status_t astra_depthframe_get_metadata(astra_depthframe_t depthFrame,
                                                          astra_image_metadata_t* metadata );

ASTRA_API_EX astra_status_t astra_depthframe_get_frameindex(astra_depthframe_t depthFrame,
                                                            astra_frame_index_t* index);

/** @} */
ASTRA_END_DECLS

#endif // DEPTH_CAPI_H
