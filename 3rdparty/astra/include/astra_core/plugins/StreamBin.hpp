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
#ifndef ASTRA_PLUGIN_STREAM_BIN_HPP
#define ASTRA_PLUGIN_STREAM_BIN_HPP

#include <cstdint>
#include "../capi/astra_types.h"
#include <astra_core/capi/plugins/astra_plugin.h>
#include <astra_core/plugins/PluginServiceProxy.hpp>

namespace astra { namespace plugins {

    template<typename TFrameType>
    class stream_bin
    {
    public:
        stream_bin(PluginServiceProxy& pluginService,
                   astra_stream_t streamHandle,
                   const std::uint32_t additionalDataSize)
            : streamHandle_(streamHandle),
              pluginService_(pluginService),
              additionalBufferSize_(additionalDataSize),
              totalBufferSize_(additionalDataSize + sizeof(TFrameType))
        {
            pluginService_.create_stream_bin(streamHandle,
                                             totalBufferSize_,
                                             &binHandle_,
                                             &currentBuffer_);
        }

        ~stream_bin()
        {
            pluginService_.destroy_stream_bin(streamHandle_, &binHandle_, &currentBuffer_);
        }

        bool has_connections() const
        {
            bool hasConnections = false;
            pluginService_.bin_has_connections(binHandle_, &hasConnections);

            return hasConnections;
        }

        void cycle()
        {
            pluginService_.cycle_bin_buffers(binHandle_, &currentBuffer_);
        }

        TFrameType* begin_write(const std::size_t frameIndex)
        {
            if (locked_)
                return reinterpret_cast<TFrameType*>(currentBuffer_->data);

            locked_ = true;
            currentBuffer_->frameIndex = frameIndex;
            return reinterpret_cast<TFrameType*>(currentBuffer_->data);
        }

        std::pair<astra_frame_t*, TFrameType*> begin_write_ex(const std::size_t frameIndex)
        {
            if (locked_)
            {
                return std::make_pair(currentBuffer_, reinterpret_cast<TFrameType*>(currentBuffer_->data));
            }

            locked_ = true;
            currentBuffer_->frameIndex = frameIndex;

            return std::make_pair(currentBuffer_, reinterpret_cast<TFrameType*>(currentBuffer_->data));
        }

        void end_write()
        {
            if (!locked_)
                return;

            cycle();
            locked_ = false;
        }

        void link_connection(astra_streamconnection_t connection)
        {
            pluginService_.link_connection_to_bin(connection, binHandle_);

        }

        void unlink_connection(astra_streamconnection_t connection)
        {
            pluginService_.link_connection_to_bin(connection, nullptr);
        }

        std::uint32_t total_buffer_size() const
        {
            return totalBufferSize_;
        }

        std::uint32_t main_buffer_size() const
        {
            return sizeof(TFrameType);
        }

        std::uint32_t additional_buffer_size() const
        {
            return additionalBufferSize_;
        }

    private:
        astra_stream_t streamHandle_;
        PluginServiceProxy& pluginService_;
        std::uint32_t additionalBufferSize_{0};
        std::uint32_t totalBufferSize_{0};
        astra_bin_t binHandle_;
        astra_frame_t* currentBuffer_{nullptr};
        bool locked_{false};
    };
}}

#endif /* ASTRA_PLUGIN_STREAM_BIN_HPP */
