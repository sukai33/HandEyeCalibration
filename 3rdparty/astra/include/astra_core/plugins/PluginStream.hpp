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
#ifndef ASTRA_PLUGIN_STREAM_HPP
#define ASTRA_PLUGIN_STREAM_HPP

#include <astra_core/astra_core.hpp>
#include <astra_core/plugins/PluginLogging.hpp>
#include <astra_core/plugins/PluginServiceProxy.hpp>
#include <astra_core/plugins/StreamCallbackListener.hpp>
#include <astra_core/plugins/StreamEventHandler.hpp>
#include <system_error>
#include <cassert>
#include <unordered_set>
#include <cstdint>

namespace astra { namespace plugins {

    class StreamHandleHash
    {
    public:
        std::size_t operator()(const astra_stream_t streamHandle) const
        {
            return std::hash<astra_stream_t>()(streamHandle);
        }
    };

    class StreamHandleEqualTo
    {
    public:
        std::size_t operator()(const astra_stream_t& lhs,
                               const astra_stream_t& rhs) const
        {
            return lhs == rhs;
        }
    };

    template<class T, class U>
    T* make_stream(U&& u)
    {
        T* t = new T(std::forward<U>(u));
        t->register_self();

        return t;
    }

    template<class T, class... U>
    T* make_stream(U&&... u)
    {
        T* t = new T(std::forward<U>(u)...);
        t->register_self();

        return t;
    }

    class stream : public stream_callback_listener
    {
    public:
        stream(PluginServiceProxy& pluginService,
               astra_streamset_t streamSet,
               StreamDescription description)
            : pluginService_(pluginService),
              streamSet_(streamSet),
              description_(description)
        {
            create_stream(description);
        }

        virtual ~stream()
        {
            pluginService_.destroy_stream(streamHandle_);
        }

        void register_self()
        {
            if (registered_)
                return;

            stream_callbacks_t pluginCallbacks = create_plugin_callbacks(this);
            pluginService_.register_stream(streamHandle_, pluginCallbacks);
            registered_ = true;
        }

        void set_handler(stream_event_handler* handler)
        {
            eventHandler_ = handler;
        }

        inline const StreamDescription& description() { return description_; }
        inline astra_stream_t get_handle() { return streamHandle_; }

    protected:
        inline PluginServiceProxy& pluginService() const { return pluginService_; }
    private:
        virtual void connection_added(astra_stream_t stream,
                                      astra_streamconnection_t connection) override final;

        virtual void connection_removed(astra_stream_t stream,
                                        astra_bin_t bin,
                                        astra_streamconnection_t connection) override final;

        virtual void connection_started(astra_stream_t stream,
                                        astra_streamconnection_t connection) override final;

        virtual void connection_stopped(astra_stream_t stream,
                                        astra_streamconnection_t connection) override final;

        virtual astra_status_t set_parameter(astra_streamconnection_t connection,
                                             astra_parameter_id id,
                                             std::uint32_t inByteLength,
                                             astra_parameter_data_t inData) override final;

        virtual astra_status_t get_parameter(astra_streamconnection_t connection,
                                              astra_parameter_id id,
                                              astra_parameter_bin_t& parameterBin) override final;

        virtual astra_status_t invoke(astra_streamconnection_t connection,
                                      astra_command_id commandId,
                                      std::uint32_t inByteLength,
                                      astra_parameter_data_t inData,
                                      astra_parameter_bin_t& parameterBin) override final;

        virtual void on_connection_added(astra_streamconnection_t connection) {}

        virtual void on_connection_removed(astra_bin_t bin,
                                           astra_streamconnection_t connection) {}

        virtual void on_connection_started(astra_streamconnection_t connection) {}

        virtual void on_connection_stopped(astra_streamconnection_t connection) {}

        virtual astra_status_t on_set_parameter(astra_streamconnection_t connection,
                                                astra_parameter_id id,
                                                std::uint32_t inByteLength,
                                                astra_parameter_data_t inData)
        {
            // should we have a unsupported status?
            return astra_status_t::ASTRA_STATUS_INVALID_OPERATION;
        }

        virtual astra_status_t on_get_parameter(astra_streamconnection_t connection,
                                                astra_parameter_id id,
                                                astra_parameter_bin_t& parameterBin)
        {
            return astra_status_t::ASTRA_STATUS_INVALID_OPERATION;
        }

        virtual astra_status_t on_invoke(astra_streamconnection_t connection,
                                         astra_command_id commandId,
                                         std::uint32_t inByteLength,
                                         astra_parameter_data_t inData,
                                         astra_parameter_bin_t& parameterBin)
        {
            return astra_status_t::ASTRA_STATUS_INVALID_OPERATION;
        };

        void create_stream(StreamDescription& description)
        {
            assert(streamHandle_ == nullptr);

            astra_stream_desc_t* desc = static_cast<astra_stream_desc_t*>(description_);

            LOG_INFO("astra.plugins.stream", "creating a %u, %u", desc->type, desc->subtype);
            pluginService_.create_stream(streamSet_,
                                         *desc,
                                         &streamHandle_);
        }

        bool registered_{false};
        PluginServiceProxy& pluginService_;
        astra_streamset_t streamSet_{nullptr};
        StreamDescription description_;
        astra_stream_t streamHandle_{nullptr};
        stream_event_handler* eventHandler_{nullptr};
    };

    inline astra_status_t stream::set_parameter(astra_streamconnection_t connection,
                                                astra_parameter_id id,
                                                std::uint32_t inByteLength,
                                                astra_parameter_data_t inData)
    {
        if (eventHandler_)
            return eventHandler_->on_set_parameter(this, connection, id, inByteLength, inData);

        return on_set_parameter(connection, id, inByteLength, inData);
    }

    inline astra_status_t stream::get_parameter(astra_streamconnection_t connection,
                                                astra_parameter_id id,
                                                astra_parameter_bin_t& parameterBin)
    {
        if (eventHandler_)
            return eventHandler_->on_get_parameter(this, connection, id, parameterBin);

        return on_get_parameter(connection, id, parameterBin);
    }

    inline astra_status_t stream::invoke(astra_streamconnection_t connection,
                                         astra_command_id commandId,
                                         std::uint32_t inByteLength,
                                         astra_parameter_data_t inData,
                                         astra_parameter_bin_t& parameterBin)
    {
        if (eventHandler_)
            return eventHandler_->on_invoke(this, connection, commandId, inByteLength, inData, parameterBin);

        return on_invoke(connection, commandId, inByteLength, inData, parameterBin);
    }

    inline void stream::connection_added(astra_stream_t stream,
                                         astra_streamconnection_t connection)
    {
        assert(stream == streamHandle_);

        LOG_INFO("astra.plugins.stream", "adding connection");

        if (eventHandler_)
            eventHandler_->on_connection_added(this, connection);

        on_connection_added(connection);
    }

    inline void stream::connection_removed(astra_stream_t stream,
                                           astra_bin_t bin,
                                           astra_streamconnection_t connection)
    {
        assert(stream == streamHandle_);

        LOG_INFO("astra.plugins.stream", "removing connection");

        if (eventHandler_)
            eventHandler_->on_connection_removed(this, bin, connection);

        on_connection_removed(bin, connection);
    }

    inline void stream::connection_started(astra_stream_t stream,
                                           astra_streamconnection_t connection)
    {
        assert(stream == streamHandle_);

        if (eventHandler_)
            eventHandler_->on_connection_started(this, connection);

        on_connection_started(connection);
    }

    inline void stream::connection_stopped(astra_stream_t stream,
                                           astra_streamconnection_t connection)
    {
        assert(stream == streamHandle_);

        if (eventHandler_)
            eventHandler_->on_connection_stopped(this, connection);

        on_connection_stopped(connection);
    }
}}

#endif /* ASTRA_PLUGIN_STREAM_HPP */
