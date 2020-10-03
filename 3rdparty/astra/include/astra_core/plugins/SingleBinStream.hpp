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
#ifndef ASTRA_SINGLEBIN_STREAM_HPP
#define ASTRA_SINGLEBIN_STREAM_HPP

#include "PluginStream.hpp"
#include "StreamBin.hpp"
#include <memory>

namespace astra { namespace plugins {

    template<typename TFrameType>
    class single_bin_stream : public astra::plugins::stream
    {
    public:
        single_bin_stream(PluginServiceProxy& pluginService,
                          astra_streamset_t streamSet,
                          StreamDescription description,
                          std::size_t extraDataSize)
            : stream(pluginService,
                     streamSet,
                     description)
        {
            bin_ = astra::make_unique<bin_type>(pluginService,
                                                get_handle(),
                                                extraDataSize);
        }

        using frame_type = TFrameType;

        std::size_t additional_buffer_size() const
        {
            return bin_->additional_buffer_size();
        }

        void set_additional_buffer_size(const std::size_t additionalBufferSize)
        {
            if (additionalBufferSize != additional_buffer_size())
            {
                std::unique_ptr<bin_type> newBin =
                    astra::make_unique<bin_type>(pluginService(),
                                                 get_handle(),
                                                 additionalBufferSize);
                for(auto& conn : connections_)
                {
                    bin_->unlink_connection(conn);
                    newBin->link_connection(conn);
                }
                bin_ = std::move(newBin);
            }
        }

        bool has_connections() const
        {
            return bin_->has_connections();
        }

        bool has_started_connections() const
        {
            return connectionStartedCount_ > 0;
        }

        TFrameType* begin_write(std::size_t frameIndex)
        {
            return bin_->begin_write(frameIndex);
        }

        void end_write()
        {
            return bin_->end_write();
        }

    protected:
        void on_connection_added(astra_streamconnection_t connection) override
        {
            const bool hadConnections = has_connections();

            const auto it = std::find(connections_.begin(), connections_.end(), connection);

            if (it == connections_.end())
            {
                bin_->link_connection(connection);
                connections_.push_back(connection);
            }

            if (hadConnections != has_connections())
            {
                on_has_connections_changed(has_connections());
            }
        }

        void on_connection_removed(astra_bin_t bin,
                                   astra_streamconnection_t connection) override
        {
            const bool hadConnections = has_connections();

            const auto it = std::find(connections_.begin(), connections_.end(), connection);

            if (it != connections_.end())
            {
                bin_->unlink_connection(connection);
                connections_.erase(it);
            }

            if (hadConnections != has_connections())
            {
                on_has_connections_changed(has_connections());
            }
        }

        virtual void on_has_connections_changed(const bool newHasConnections) {}

        void on_connection_started(astra_streamconnection_t connection) override
        {
            const bool hadStartedConnections = has_started_connections();

            const auto it = std::find(connections_.begin(), connections_.end(), connection);

            if (it != connections_.end())
            {
                connectionStartedCount_++;
            }

            if (hadStartedConnections != has_started_connections())
            {
                on_has_connections_started_changed(has_started_connections());
            }
        }

        void on_connection_stopped(astra_streamconnection_t connection) override
        {
            const bool hadStartedConnections = has_started_connections();

            const auto it = std::find(connections_.begin(), connections_.end(), connection);

            if (it != connections_.end())
            {
                connectionStartedCount_--;
            }

            if (hadStartedConnections != has_started_connections())
            {
                on_has_connections_started_changed(has_started_connections());
            }
        }

        virtual void on_has_connections_started_changed(const bool newHasConnectionsStarted) {}

    private:
        using bin_type = stream_bin<TFrameType>;
        std::unique_ptr<bin_type> bin_;
        std::vector<astra_streamconnection_t> connections_;
        std::size_t connectionStartedCount_{0};
    };
}}

#endif /* ASTRA_SINGLEBIN_STREAM_HPP */
