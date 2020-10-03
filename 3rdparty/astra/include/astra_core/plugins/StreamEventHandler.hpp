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
#ifndef ASTRA_STREAM_EVENT_HANDLER_HPP
#define ASTRA_STREAM_EVENT_HANDLER_HPP

#include <astra_core/astra_core.hpp>
#include <cstdint>

namespace astra { namespace plugins {

    class stream;

    class stream_event_handler
    {
    public:
        virtual void on_connection_added(astra::plugins::stream* stream,
                                         astra_streamconnection_t connection)
        {}

        virtual void on_connection_removed(astra::plugins::stream* stream,
                                           astra_bin_t bin,
                                           astra_streamconnection_t connection) {}

        virtual void on_connection_started(astra::plugins::stream* stream,
                                           astra_streamconnection_t connection) {}

        virtual void on_connection_stopped(astra::plugins::stream* stream,
                                           astra_streamconnection_t connection) {}

        virtual astra_status_t on_set_parameter(astra::plugins::stream* stream,
                                      astra_streamconnection_t connection,
                                      astra_parameter_id id,
                                      std::uint32_t inByteLength,
                                      astra_parameter_data_t inData) 
        {
            return ASTRA_STATUS_SUCCESS;
        }

        virtual astra_status_t on_get_parameter(astra::plugins::stream* stream,
                                      astra_streamconnection_t connection,
                                      astra_parameter_id id,
                                      astra_parameter_bin_t& parameterBin) 
        {
            return ASTRA_STATUS_SUCCESS;
        }

        virtual astra_status_t on_invoke(astra::plugins::stream* stream,
                               astra_streamconnection_t connection,
                               astra_command_id commandId,
                               std::uint32_t inByteLength,
                               astra_parameter_data_t inData,
                               astra_parameter_bin_t& parameterBin) 
        {
            return ASTRA_STATUS_SUCCESS;
        }
    };

}}  // astra::plugins

#endif /* ASTRA_STREAM_EVENT_HANDLER_HPP */
