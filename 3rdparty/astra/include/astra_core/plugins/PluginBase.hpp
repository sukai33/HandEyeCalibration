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
#ifndef ASTRA_PLUGINBASE_HPP
#define ASTRA_PLUGINBASE_HPP

#include <cassert>

#include "../capi/astra_types.h"
#include "../capi/astra_host_events.h"
#include "PluginServiceProxy.hpp"
#include "PluginLogging.hpp"
#include <astra_core/capi/astra_types.h>

namespace astra { namespace plugins {

    inline const char* get_uri_for_streamset(PluginServiceProxy& pluginService, astra_streamset_t streamSet)
    {
        const char* uri;
        pluginService.get_streamset_uri(streamSet, &uri);

        return uri;
    }

    class plugin_base
    {
    public:
        plugin_base(PluginServiceProxy* pluginService, const char* pluginName)
            :  pluginService_(pluginService)
        {
            assert(pluginService != nullptr);
        }

        virtual ~plugin_base() = default;

        void initialize() { on_initialize(); };

        virtual void update() { };

    protected:
        inline PluginServiceProxy& pluginService() const { return *pluginService_; }

        void register_for_stream_events()
        {
            pluginService().
                register_stream_registered_callback(&plugin_base::stream_added_handler_thunk,
                                                    this,
                                                    &streamAddedCallbackId_);

            pluginService().
                register_stream_unregistering_callback(&plugin_base::stream_removing_handler_thunk,
                                                       this,
                                                       &streamRemovingCallbackId_);
        }

        void register_for_host_events()
        {

            pluginService().
                register_host_event_callback(&plugin_base::host_event_handler_thunk,
                                             this,
                                             &hostEventCallbackId_);
        }

        void unregister_for_stream_events()
        {
            pluginService().unregister_stream_registered_callback(streamAddedCallbackId_);
            pluginService().unregister_stream_unregistering_callback(streamRemovingCallbackId_);
        }

        void unregister_for_host_events()
        {
            pluginService().unregister_host_event_callback(hostEventCallbackId_);
        }

    private:
        PluginServiceProxy* pluginService_{nullptr};

        virtual void on_initialize() { };

        static void ASTRA_CALLBACK stream_added_handler_thunk(void* clientTag,
                                                              astra_streamset_t setHandle,
                                                              astra_stream_t streamHandle,
                                                              astra_stream_desc_t desc)
        {
            plugin_base* plugin = static_cast<plugin_base*>(clientTag);
            plugin->stream_added_handler(setHandle, streamHandle, desc);
        }

        static void ASTRA_CALLBACK stream_removing_handler_thunk(void* clientTag,
                                                                 astra_streamset_t setHandle,
                                                                 astra_stream_t streamHandle,
                                                                 astra_stream_desc_t desc)

        {
            plugin_base* plugin = static_cast<plugin_base*>(clientTag);
            plugin->stream_removing_handler(setHandle, streamHandle, desc);
        }

        static void ASTRA_CALLBACK host_event_handler_thunk(void* clientTag,
                                                            astra_event_id id,
                                                            const void* data,
                                                            uint32_t dataSize)
        {
            plugin_base* self = static_cast<plugin_base*>(clientTag);
            self->host_event_handler(id, data, dataSize);
        }

        void stream_added_handler(astra_streamset_t setHandle,
                                  astra_stream_t streamHandle,
                                  astra_stream_desc_t desc)
        {
            on_stream_added(setHandle, streamHandle, desc);
        }

        void stream_removing_handler(astra_streamset_t setHandle,
                                     astra_stream_t streamHandle,
                                     astra_stream_desc_t desc)
        {
            on_stream_removed(setHandle, streamHandle, desc);
        }

        void host_event_handler(astra_event_id id,
                                const void* data,
                                uint32_t dataSize)
        {
            on_host_event(id, data, dataSize);
        }

        virtual void on_stream_added(astra_streamset_t setHandle,
                                     astra_stream_t streamHandle,
                                     astra_stream_desc_t desc)
        {}

        virtual void on_stream_removed(astra_streamset_t setHandle,
                                       astra_stream_t streamHandle,
                                       astra_stream_desc_t desc)
        {}

        virtual void on_host_event(astra_event_id id, const void* data, uint32_t dataSize)
        {}

        astra_callback_id_t streamAddedCallbackId_;
        astra_callback_id_t streamRemovingCallbackId_;
        astra_callback_id_t hostEventCallbackId_;
    };
}}

#define EXPORT_PLUGIN(className)                                                               \
                                                                                               \
    static std::unique_ptr<className> g_plugin;                                                \
    /* __g_serviceProxy is shared by plugins, don't set to null after first init */            \
    astra::PluginServiceProxy* __g_serviceProxy;                                               \
                                                                                               \
    ASTRA_BEGIN_DECLS                                                                          \
                                                                                               \
    ASTRA_EXPORT void astra_plugin_initialize(astra_pluginservice_proxy_t* pluginProxy)        \
    {                                                                                          \
        __g_serviceProxy = reinterpret_cast<astra::PluginServiceProxy*>(pluginProxy);          \
        g_plugin = astra::make_unique<className>(__g_serviceProxy);                            \
        g_plugin->initialize();                                                                \
    }                                                                                          \
                                                                                               \
    ASTRA_EXPORT void astra_plugin_update()                                                    \
    {                                                                                          \
        g_plugin->update();                                                                    \
    }                                                                                          \
                                                                                               \
    ASTRA_EXPORT void astra_plugin_terminate()                                                 \
    {                                                                                          \
        g_plugin = nullptr;                                                                    \
    }                                                                                          \
                                                                                               \
    ASTRA_EXPORT astra_status_t astra_plugin_info(astra_plugin_info_t* info)                   \
    {                                                                                          \
        if (info == nullptr)                                                                   \
        {                                                                                      \
            return ASTRA_STATUS_INVALID_PARAMETER;                                             \
        }                                                                                      \
        else                                                                                   \
        {                                                                                      \
            info->versionInfo.majorVersion = astra::MajorVersion;                              \
            info->versionInfo.minorVersion = astra::MinorVersion;                              \
            info->versionInfo.patchVersion = astra::PatchVersion;                              \
            info->versionInfo.versionSuffix = const_cast<char*>(astra::VersionSuffix);         \
            info->versionInfo.gitCommitSha1 = const_cast<char*>(astra::GitSha);                \
            info->versionInfo.friendlyVersionString = const_cast<char*>(astra::FriendlyName);  \
            info->versionInfo.apiLevel = astra::ApiLevel;                                      \
            return ASTRA_STATUS_SUCCESS;                                                       \
        }                                                                                      \
    }                                                                                          \
                                                                                               \
ASTRA_END_DECLS

#endif /* ASTRA_PLUGIN_BASE_HPP */
