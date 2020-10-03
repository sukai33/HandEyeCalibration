/* THIS FILE AUTO-GENERATED FROM astra_pluginservice_proxy.h.lpp. DO NOT EDIT. */
#ifndef ASTRA_PLUGINSERVICE_PROXY_H
#define ASTRA_PLUGINSERVICE_PROXY_H

#include "../astra_types.h"
#include "astra_plugin.h"
#include <stdarg.h>

struct astra_pluginservice_proxy_t
{
    void* pluginService;

    astra_status_t (ASTRA_CALLBACK *register_stream_registered_callback)(void*,
                                                                         stream_registered_callback_t,
                                                                         void*,
                                                                         astra_callback_id_t*);

    astra_status_t (ASTRA_CALLBACK *register_stream_unregistering_callback)(void*,
                                                                            stream_unregistering_callback_t,
                                                                            void*,
                                                                            astra_callback_id_t*);

    astra_status_t (ASTRA_CALLBACK *register_host_event_callback)(void*,
                                                                  host_event_callback_t,
                                                                  void*,
                                                                  astra_callback_id_t*);

    astra_status_t (ASTRA_CALLBACK *unregister_host_event_callback)(void*,
                                                                    astra_callback_id_t);

    astra_status_t (ASTRA_CALLBACK *unregister_stream_registered_callback)(void*,
                                                                           astra_callback_id_t);

    astra_status_t (ASTRA_CALLBACK *unregister_stream_unregistering_callback)(void*,
                                                                              astra_callback_id_t);

    astra_status_t (ASTRA_CALLBACK *create_stream_set)(void*,
                                                       const char*,
                                                       astra_streamset_t&);

    astra_status_t (ASTRA_CALLBACK *destroy_stream_set)(void*,
                                                        astra_streamset_t&);

    astra_status_t (ASTRA_CALLBACK *get_streamset_uri)(void*,
                                                       astra_streamset_t,
                                                       const char**);

    astra_status_t (ASTRA_CALLBACK *create_stream)(void*,
                                                   astra_streamset_t,
                                                   astra_stream_desc_t,
                                                   astra_stream_t*);

    astra_status_t (ASTRA_CALLBACK *register_stream)(void*,
                                                     astra_stream_t,
                                                     stream_callbacks_t);

    astra_status_t (ASTRA_CALLBACK *unregister_stream)(void*,
                                                       astra_stream_t);

    astra_status_t (ASTRA_CALLBACK *destroy_stream)(void*,
                                                    astra_stream_t&);

    astra_status_t (ASTRA_CALLBACK *create_stream_bin)(void*,
                                                       astra_stream_t,
                                                       uint32_t,
                                                       astra_bin_t*,
                                                       astra_frame_t**);

    astra_status_t (ASTRA_CALLBACK *destroy_stream_bin)(void*,
                                                        astra_stream_t,
                                                        astra_bin_t*,
                                                        astra_frame_t**);

    astra_status_t (ASTRA_CALLBACK *bin_has_connections)(void*,
                                                         astra_bin_t,
                                                         bool*);

    astra_status_t (ASTRA_CALLBACK *cycle_bin_buffers)(void*,
                                                       astra_bin_t,
                                                       astra_frame_t**);

    astra_status_t (ASTRA_CALLBACK *link_connection_to_bin)(void*,
                                                            astra_streamconnection_t,
                                                            astra_bin_t);

    astra_status_t (ASTRA_CALLBACK *get_parameter_bin)(void*,
                                                       uint32_t,
                                                       astra_parameter_bin_t*,
                                                       astra_parameter_data_t*);

    astra_status_t (ASTRA_CALLBACK *log)(void*,
                                         const char*,
                                         astra_log_severity_t,
                                         const char*,
                                         int,
                                         const char*,
                                         const char*,
                                         va_list);

};

#endif /* ASTRA_PLUGINSERVICE_PROXY_H */
