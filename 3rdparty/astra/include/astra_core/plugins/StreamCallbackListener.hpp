/* THIS FILE AUTO-GENERATED FROM StreamCallbackListener.hpp.lpp. DO NOT EDIT. */
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
#ifndef ASTRA_STREAMCALLBACK_LISTENER_HPP
#define ASTRA_STREAMCALLBACK_LISTENER_HPP

#include "../capi/astra_types.h"
#include <astra_core/capi/plugins/astra_plugin_callbacks.h>
#include <cstdint>

namespace astra {

    class stream_callback_listener
    {
    public:
        virtual ~stream_callback_listener() = default;
    private:

        static astra_status_t ASTRA_CALLBACK set_parameter_thunk(void* instance,
                                                                 astra_streamconnection_t connection,
                                                                 astra_parameter_id id,
                                                                 uint32_t inByteLength,
                                                                 astra_parameter_data_t inData)
        {
            return static_cast<stream_callback_listener*>(instance)->set_parameter(connection,
                                                                                   id,
                                                                                   inByteLength,
                                                                                   inData);
        }

        static astra_status_t ASTRA_CALLBACK get_parameter_thunk(void* instance,
                                                                 astra_streamconnection_t connection,
                                                                 astra_parameter_id id,
                                                                 astra_parameter_bin_t* parameterBin)
        {
            return static_cast<stream_callback_listener*>(instance)->get_parameter(connection,
                                                                                   id,
                                                                                   *parameterBin);
        }

        static astra_status_t ASTRA_CALLBACK invoke_thunk(void* instance,
                                                          astra_streamconnection_t connection,
                                                          astra_command_id commandId,
                                                          uint32_t inByteLength,
                                                          astra_parameter_data_t inData,
                                                          astra_parameter_bin_t* parameterBin)
        {
            return static_cast<stream_callback_listener*>(instance)->invoke(connection,
                                                                            commandId,
                                                                            inByteLength,
                                                                            inData,
                                                                            *parameterBin);
        }

        static void ASTRA_CALLBACK connection_added_thunk(void* instance,
                                                          astra_stream_t stream,
                                                          astra_streamconnection_t connection)
        {
             static_cast<stream_callback_listener*>(instance)->connection_added(stream,
                                                                                connection);
        }

        static void ASTRA_CALLBACK connection_removed_thunk(void* instance,
                                                            astra_stream_t stream,
                                                            astra_bin_t bin,
                                                            astra_streamconnection_t connection)
        {
             static_cast<stream_callback_listener*>(instance)->connection_removed(stream,
                                                                                  bin,
                                                                                  connection);
        }

        static void ASTRA_CALLBACK connection_started_thunk(void* instance,
                                                            astra_stream_t stream,
                                                            astra_streamconnection_t connection)
        {
             static_cast<stream_callback_listener*>(instance)->connection_started(stream,
                                                                                  connection);
        }

        static void ASTRA_CALLBACK connection_stopped_thunk(void* instance,
                                                            astra_stream_t stream,
                                                            astra_streamconnection_t connection)
        {
             static_cast<stream_callback_listener*>(instance)->connection_stopped(stream,
                                                                                  connection);
        }

        virtual astra_status_t set_parameter(astra_streamconnection_t connection,
                                             astra_parameter_id id,
                                             uint32_t inByteLength,
                                             astra_parameter_data_t inData)
        {
            return astra_status_t::ASTRA_STATUS_INVALID_OPERATION;
        }

        virtual astra_status_t get_parameter(astra_streamconnection_t connection,
                                             astra_parameter_id id,
                                             astra_parameter_bin_t& parameterBin)
        {
            return astra_status_t::ASTRA_STATUS_INVALID_OPERATION;
        }

        virtual astra_status_t invoke(astra_streamconnection_t connection,
                                      astra_command_id commandId,
                                      uint32_t inByteLength,
                                      astra_parameter_data_t inData,
                                      astra_parameter_bin_t& parameterBin)
        {
            return astra_status_t::ASTRA_STATUS_INVALID_OPERATION;
        }

        virtual void connection_added(astra_stream_t stream,
                                      astra_streamconnection_t connection)
        {
            
        }

        virtual void connection_removed(astra_stream_t stream,
                                        astra_bin_t bin,
                                        astra_streamconnection_t connection)
        {
            
        }

        virtual void connection_started(astra_stream_t stream,
                                        astra_streamconnection_t connection)
        {
            
        }

        virtual void connection_stopped(astra_stream_t stream,
                                        astra_streamconnection_t connection)
        {
            
        }


        friend stream_callbacks_t create_plugin_callbacks(stream_callback_listener* context);
    };

    inline stream_callbacks_t create_plugin_callbacks(stream_callback_listener* context)
    {
        stream_callbacks_t callbacks;

        callbacks.context = context;
        callbacks.set_parameter_callback = &stream_callback_listener::set_parameter_thunk;
        callbacks.get_parameter_callback = &stream_callback_listener::get_parameter_thunk;
        callbacks.invoke_callback = &stream_callback_listener::invoke_thunk;
        callbacks.connection_added_callback = &stream_callback_listener::connection_added_thunk;
        callbacks.connection_removed_callback = &stream_callback_listener::connection_removed_thunk;
        callbacks.connection_started_callback = &stream_callback_listener::connection_started_thunk;
        callbacks.connection_stopped_callback = &stream_callback_listener::connection_stopped_thunk;

        return callbacks;
    }
}

#endif // ASTRA_STREAMCALLBACK_LISTENER_HPP
