/* THIS FILE AUTO-GENERATED FROM PluginServiceProxy.hpp.lpp. DO NOT EDIT. */
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
#ifndef ASTRA_PLUGINSERVICE_PROXY_HPP
#define ASTRA_PLUGINSERVICE_PROXY_HPP

#include <astra_core/capi/plugins/astra_pluginservice_proxy.h>
#include <cstdarg>
#include <cstdio>
#include <cstdint>

namespace astra {

    class PluginServiceProxy : public astra_pluginservice_proxy_t
    {
    public:

    astra_status_t register_stream_registered_callback(stream_registered_callback_t callback,
                                                       void* clientTag,
                                                       astra_callback_id_t* callbackId)
    {
        return astra_pluginservice_proxy_t::register_stream_registered_callback(pluginService, callback, clientTag, callbackId);
    }

    astra_status_t register_stream_unregistering_callback(stream_unregistering_callback_t callback,
                                                          void* clientTag,
                                                          astra_callback_id_t* callbackId)
    {
        return astra_pluginservice_proxy_t::register_stream_unregistering_callback(pluginService, callback, clientTag, callbackId);
    }

    astra_status_t register_host_event_callback(host_event_callback_t callback,
                                                void* clientTag,
                                                astra_callback_id_t* callbackId)
    {
        return astra_pluginservice_proxy_t::register_host_event_callback(pluginService, callback, clientTag, callbackId);
    }

    astra_status_t unregister_host_event_callback(astra_callback_id_t callback)
    {
        return astra_pluginservice_proxy_t::unregister_host_event_callback(pluginService, callback);
    }

    astra_status_t unregister_stream_registered_callback(astra_callback_id_t callback)
    {
        return astra_pluginservice_proxy_t::unregister_stream_registered_callback(pluginService, callback);
    }

    astra_status_t unregister_stream_unregistering_callback(astra_callback_id_t callback)
    {
        return astra_pluginservice_proxy_t::unregister_stream_unregistering_callback(pluginService, callback);
    }

    astra_status_t create_stream_set(const char* setUri,
                                     astra_streamset_t& setHandle)
    {
        return astra_pluginservice_proxy_t::create_stream_set(pluginService, setUri, setHandle);
    }

    astra_status_t destroy_stream_set(astra_streamset_t& setHandle)
    {
        return astra_pluginservice_proxy_t::destroy_stream_set(pluginService, setHandle);
    }

    astra_status_t get_streamset_uri(astra_streamset_t setHandle,
                                     const char** uri)
    {
        return astra_pluginservice_proxy_t::get_streamset_uri(pluginService, setHandle, uri);
    }

    astra_status_t create_stream(astra_streamset_t setHandle,
                                 astra_stream_desc_t desc,
                                 astra_stream_t* handle)
    {
        return astra_pluginservice_proxy_t::create_stream(pluginService, setHandle, desc, handle);
    }

    astra_status_t register_stream(astra_stream_t handle,
                                   stream_callbacks_t pluginCallbacks)
    {
        return astra_pluginservice_proxy_t::register_stream(pluginService, handle, pluginCallbacks);
    }

    astra_status_t unregister_stream(astra_stream_t handle)
    {
        return astra_pluginservice_proxy_t::unregister_stream(pluginService, handle);
    }

    astra_status_t destroy_stream(astra_stream_t& handle)
    {
        return astra_pluginservice_proxy_t::destroy_stream(pluginService, handle);
    }

    astra_status_t create_stream_bin(astra_stream_t streamHandle,
                                     uint32_t lengthInBytes,
                                     astra_bin_t* binHandle,
                                     astra_frame_t** binBuffer)
    {
        return astra_pluginservice_proxy_t::create_stream_bin(pluginService, streamHandle, lengthInBytes, binHandle, binBuffer);
    }

    astra_status_t destroy_stream_bin(astra_stream_t streamHandle,
                                      astra_bin_t* binHandle,
                                      astra_frame_t** binBuffer)
    {
        return astra_pluginservice_proxy_t::destroy_stream_bin(pluginService, streamHandle, binHandle, binBuffer);
    }

    astra_status_t bin_has_connections(astra_bin_t binHandle,
                                       bool* hasConnections)
    {
        return astra_pluginservice_proxy_t::bin_has_connections(pluginService, binHandle, hasConnections);
    }

    astra_status_t cycle_bin_buffers(astra_bin_t binHandle,
                                     astra_frame_t** binBuffer)
    {
        return astra_pluginservice_proxy_t::cycle_bin_buffers(pluginService, binHandle, binBuffer);
    }

    astra_status_t link_connection_to_bin(astra_streamconnection_t connection,
                                          astra_bin_t binHandle)
    {
        return astra_pluginservice_proxy_t::link_connection_to_bin(pluginService, connection, binHandle);
    }

    astra_status_t get_parameter_bin(uint32_t byteSize,
                                     astra_parameter_bin_t* binHandle,
                                     astra_parameter_data_t* parameterData)
    {
        return astra_pluginservice_proxy_t::get_parameter_bin(pluginService, byteSize, binHandle, parameterData);
    }

    astra_status_t log(const char* channel,
                       astra_log_severity_t logLevel,
                       const char* fileName,
                       int lineNo,
                       const char* func,
                       const char* format,
                       va_list args)
    {
        return astra_pluginservice_proxy_t::log(pluginService, channel, logLevel, fileName, lineNo, func, format, args);
    }
    };
}

#endif // ASTRA_PLUGINSERVICE_PROXY_HPP
