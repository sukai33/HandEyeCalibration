/* THIS FILE AUTO-GENERATED FROM astra_core.h.lpp. DO NOT EDIT. */
#ifndef ASTRA_CAPI_H
#define ASTRA_CAPI_H

#include "astra_defines.h"
#include "astra_types.h"
#include "astra_core_version.h"
#include <stdbool.h>

ASTRA_BEGIN_DECLS

/*!
 * \defgroup c_core_api_ref astra core apis
 * \ingroup c_ref
 * @{
 */

/*!
 * \brief Initializes the library.
 * \details This function must be called before calling any other function.
 */
ASTRA_API astra_status_t astra_initialize();

/*!
 * \brief Terminate the library, destroying all its streams. 
 * \details This function must be called when library not used, otherwise there will be problems when re-initialize it.And do not call any other function after calling this method.
 */
ASTRA_API astra_status_t astra_terminate();

/*!
 * \brief Notify plugins an event.
 * \details App use this function to notify plugins an event.
 * 
 * \param[in] id event ID.
 * \param[in] data A pointer to the event data.
 * \param[in] dataSize Size of the data.
 */
ASTRA_API astra_status_t astra_notify_plugin_event(astra_event_id id,
                                                   const void* data,
                                                   uint32_t dataSize);

/*!
 * @name streamset apis
 * @{
 */
/*!
 * \brief Test whether the \ref concepts_streamset is valid.
 * 
 * \param[in] connection The handle to the \ref concepts_streamset.
 * \param[out] isAvailable The test result(true:valid false:invalid)
 */
ASTRA_API astra_status_t astra_streamset_is_available(astra_streamsetconnection_t connection,
                                                      bool* isAvailable);

/*!
 * \brief Open a \ref concepts_streamset.
 * \details The \ref concepts_streamset to be opened is identified by the uri.
 * 
 * \param[in] connectionString A string-based unique identifier addressed the device.
 * \param[out] streamSet The output handle to \ref concepts_streamset.
 */
ASTRA_API astra_status_t astra_streamset_open(const char* connectionString,
                                              astra_streamsetconnection_t* streamSet);

/*!
 * \brief Close the handle to \ref concepts_streamset.
 * 
 * \param[in] streamSet The handle to \ref concepts_streamset.
 */
ASTRA_API astra_status_t astra_streamset_close(astra_streamsetconnection_t* streamSet);

/*!
 * \brief Get the URI of \ref concepts_streamset.
 * 
 * \param[in] connection The handle to the \ref concepts_streamset.
 * \param[out] uri Pointer to the buffer which receives output data.
 * \param[in] size Size of the buffer.
 */
ASTRA_API astra_status_t astra_streamset_get_uri(astra_streamsetconnection_t connection,
                                                 char* uri,
                                                 int32_t size);
/*! @} */
/*!
 * @name stream reader apis
 * @{
 */
/*!
 * \brief Create a \ref concepts_streamreader in \ref concepts_streamset.
 * 
 * \param[in] streamSet The handle to \ref concepts_streamset.
 * \param[out] reader The handle to \ref concepts_streamreader.
 */
ASTRA_API astra_status_t astra_reader_create(astra_streamsetconnection_t streamSet,
                                             astra_reader_t* reader);

/*!
 * \brief Destroy the handle to \ref concepts_streamreader.
 * \details The \ref concepts_streamreader must be destroyed when not used.
 * 
 * \param[in] reader The handle to \ref concepts_streamreader created by astra_reader_create().
 */
ASTRA_API astra_status_t astra_reader_destroy(astra_reader_t* reader);

/*!
 * \brief Get specified stream from \ref concepts_streamreader reader.
 * 
 * \param[in] reader The handle to \ref concepts_streamreader.
 * \param[in] type type of \ref concepts_stream.
 * \param[in] subtype subtype of \ref concepts_stream.
 * \param[out] connection The output handle to \ref concepts_stream.
 */
ASTRA_API astra_status_t astra_reader_get_stream(astra_reader_t reader,
                                                 astra_stream_type_t type,
                                                 astra_stream_subtype_t subtype,
                                                 astra_streamconnection_t* connection);

/*!
 * \brief Test whether there is a new frame.
 * 
 * \param[in] reader The handle to \ref concepts_streamreader.
 * \param[out] hasNewFrame
 */
ASTRA_API astra_status_t astra_reader_has_new_frame(astra_reader_t reader,
                                                    bool* hasNewFrame);

/*!
 * \brief Open 
 * 
 * \param[in] reader
 * \param[in] timeoutMillis
 * \param[in] frame
 */
ASTRA_API astra_status_t astra_reader_open_frame(astra_reader_t reader,
                                                 int timeoutMillis,
                                                 astra_reader_frame_t* frame);

/*!
 * \brief Close 
 * 
 * \param[in] frame
 */
ASTRA_API astra_status_t astra_reader_close_frame(astra_reader_frame_t* frame);

/*!
 * \brief Registers a callback function to \ref concepts_streamreader.
 * 
 * \param[in] reader The reader that callback will be registered to.
 * \param[in] callback A pointer to a function that will be called when frame ready to read. 
 * \param[in] clientTag A user cookie that will be passed to the callback function.
 * \param[in] callbackId Output handle to be passed to astra_reader_unregister_frame_ready_callback() after later.
 */
ASTRA_API astra_status_t astra_reader_register_frame_ready_callback(astra_reader_t reader,
                                                                    astra_frame_ready_callback_t callback,
                                                                    void* clientTag,
                                                                    astra_reader_callback_id_t* callbackId);

/*!
 * \brief Unregisters the callback function.
 * 
 * \param[in] callbackId The handle created by astra_reader_register_frame_ready_callback() before.
 */
ASTRA_API astra_status_t astra_reader_unregister_frame_ready_callback(astra_reader_callback_id_t* callbackId);

/*!
 * \brief Read a frame.
 * 
 * \param[in] frame The handle to Frame.
 * \param[in] type
 * \param[in] subtype
 * \param[in] subFrame
 */
ASTRA_API astra_status_t astra_reader_get_frame(astra_reader_frame_t frame,
                                                astra_stream_type_t type,
                                                astra_stream_subtype_t subtype,
                                                astra_frame_t** subFrame);

/*! @} */

/*!
 * @name stream apis
 * @{
 */
/*!
 * \brief Get description of \ref concepts_stream.
 *
 * \param[in] connection The handle to \ref concepts_stream.
 * \param[out] description The output location for description pointer.
 */
ASTRA_API astra_status_t astra_stream_get_description(astra_streamconnection_t connection,
                                                      astra_stream_desc_t* description);

/*!
* \brief Test whether the handle to \ref concepts_stream is valid.
*
* \param[in] connection The handle to \ref concepts_stream.
* \param[in] isAvailable The test result(true:valid false:invalid).
*/
ASTRA_API astra_status_t astra_stream_is_available(astra_streamconnection_t connection,
                                                   bool* isAvailable);

/*!
* \brief Start the \ref concepts_stream.
* \details The \ref concepts_stream must be started before reading frame it.
*
* \param[in] connection The handle to \ref concepts_stream.
*/
ASTRA_API astra_status_t astra_stream_start(astra_streamconnection_t connection);

/*!
* \brief Stop the \ref concepts_stream.
* \details After stoping the \ref concepts_stream, can't read frame from it anymore.
*
* \param[in] connection The handle to \ref concepts_stream.
*/
ASTRA_API astra_status_t astra_stream_stop(astra_streamconnection_t connection);

/*!
 * \brief Set parameter to \ref concepts_streamset.
 * 
 * \param[in] connection
 * \param[in] parameterId
 * \param[in] resultByteLength
 * \param[in] token
 */
ASTRA_API astra_status_t astra_stream_set_parameter(astra_streamconnection_t connection,
                                                    astra_parameter_id parameterId,
                                                    uint32_t inByteLength,
                                                    astra_parameter_data_t inData);

/*!
 * \brief Get parameter from \ref concepts_streamset.
 * 
 * \param[in] connection
 * \param[in] parameterId
 * \param[in] resultByteLength
 * \param[in] token
 */
ASTRA_API astra_status_t astra_stream_get_parameter(astra_streamconnection_t connection,
                                                    astra_parameter_id parameterId,
                                                    uint32_t* resultByteLength,
                                                    astra_result_token_t* token);

ASTRA_API astra_status_t astra_stream_get_result(astra_streamconnection_t connection,
                                                 astra_result_token_t token,
                                                 uint32_t dataByteLength,
                                                 astra_parameter_data_t dataDestination);

ASTRA_API astra_status_t astra_stream_invoke(astra_streamconnection_t connection,
                                             astra_command_id commandId,
                                             uint32_t inByteLength,
                                             astra_parameter_data_t inData,
                                             uint32_t* resultByteLength,
                                             astra_result_token_t* token);

/*! @} */

/*!
 * \brief Drive the library to get a new frame of stream.
 * \details call this function in while loop until there is a new frame,
 *          using sleep to block cpu for several ms in while loop is recommended.
 */
ASTRA_API astra_status_t astra_update();
/*! @} */

ASTRA_END_DECLS

#endif /* ASTRA_CAPI_H */
