/* THIS FILE AUTO-GENERATED FROM astra_streamservice_proxy.h.lpp. DO NOT EDIT. */
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
#ifndef ASTRA_STREAMSERVICE_PROXY_H
#define ASTRA_STREAMSERVICE_PROXY_H

#include "astra_types.h"

struct astra_streamservice_proxy_t
{
    void* streamService;

    astra_status_t (ASTRA_CALLBACK *notify_plugin_event)(void*,
                                                         astra_event_id,
                                                         const void*,
                                                         uint32_t);

    astra_status_t (ASTRA_CALLBACK *streamset_is_available)(void*,
                                                            astra_streamsetconnection_t,
                                                            bool*);

    astra_status_t (ASTRA_CALLBACK *streamset_open)(void*,
                                                    const char*,
                                                    astra_streamsetconnection_t*);

    astra_status_t (ASTRA_CALLBACK *streamset_close)(void*,
                                                     astra_streamsetconnection_t*);

    astra_status_t (ASTRA_CALLBACK *streamset_get_uri)(void*,
                                                       astra_streamsetconnection_t,
                                                       char*,
                                                       int32_t);

    astra_status_t (ASTRA_CALLBACK *reader_create)(void*,
                                                   astra_streamsetconnection_t,
                                                   astra_reader_t*);

    astra_status_t (ASTRA_CALLBACK *reader_destroy)(void*,
                                                    astra_reader_t*);

    astra_status_t (ASTRA_CALLBACK *reader_get_stream)(void*,
                                                       astra_reader_t,
                                                       astra_stream_type_t,
                                                       astra_stream_subtype_t,
                                                       astra_streamconnection_t*);

    astra_status_t (ASTRA_CALLBACK *stream_get_description)(void*,
                                                            astra_streamconnection_t,
                                                            astra_stream_desc_t*);

    astra_status_t (ASTRA_CALLBACK *stream_is_available)(void*,
                                                         astra_streamconnection_t,
                                                         bool*);

    astra_status_t (ASTRA_CALLBACK *stream_start)(void*,
                                                  astra_streamconnection_t);

    astra_status_t (ASTRA_CALLBACK *stream_stop)(void*,
                                                 astra_streamconnection_t);

    astra_status_t (ASTRA_CALLBACK *reader_has_new_frame)(void*,
                                                          astra_reader_t,
                                                          bool*);

    astra_status_t (ASTRA_CALLBACK *reader_open_frame)(void*,
                                                       astra_reader_t,
                                                       int,
                                                       astra_reader_frame_t*);

    astra_status_t (ASTRA_CALLBACK *reader_close_frame)(void*,
                                                        astra_reader_frame_t*);

    astra_status_t (ASTRA_CALLBACK *reader_register_frame_ready_callback)(void*,
                                                                          astra_reader_t,
                                                                          astra_frame_ready_callback_t,
                                                                          void*,
                                                                          astra_reader_callback_id_t*);

    astra_status_t (ASTRA_CALLBACK *reader_unregister_frame_ready_callback)(void*,
                                                                            astra_reader_callback_id_t*);

    astra_status_t (ASTRA_CALLBACK *reader_get_frame)(void*,
                                                      astra_reader_frame_t,
                                                      astra_stream_type_t,
                                                      astra_stream_subtype_t,
                                                      astra_frame_t**);

    astra_status_t (ASTRA_CALLBACK *stream_set_parameter)(void*,
                                                          astra_streamconnection_t,
                                                          astra_parameter_id,
                                                          uint32_t,
                                                          astra_parameter_data_t);

    astra_status_t (ASTRA_CALLBACK *stream_get_parameter)(void*,
                                                          astra_streamconnection_t,
                                                          astra_parameter_id,
                                                          uint32_t*,
                                                          astra_result_token_t*);

    astra_status_t (ASTRA_CALLBACK *stream_get_result)(void*,
                                                       astra_streamconnection_t,
                                                       astra_result_token_t,
                                                       uint32_t,
                                                       astra_parameter_data_t);

    astra_status_t (ASTRA_CALLBACK *stream_invoke)(void*,
                                                   astra_streamconnection_t,
                                                   astra_command_id,
                                                   uint32_t,
                                                   astra_parameter_data_t,
                                                   uint32_t*,
                                                   astra_result_token_t*);

    astra_status_t (ASTRA_CALLBACK *update)(void*);

};

#endif /* ASTRA_STREAMSERVICE_PROXY_H */
