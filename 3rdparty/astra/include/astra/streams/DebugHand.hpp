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
#ifndef ASTRA_HAND_DEBUG_HPP
#define ASTRA_HAND_DEBUG_HPP

#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/hand_capi.h>

namespace astra {

    using DebugHandViewType = astra_debug_hand_view_type_t;

    /*!
      \defgroup cpp_debughand_api_ref debug hand stream apis
      \ingroup cpp_high_api_ref
      @{
     */

    /*!
      \brief A Debug Hand Stream

      \details A Debug Hand Stream. for debug use
     */
    class DebugHandStream : public DataStream
    {
    public:
        /*! 
        \brief default constructs
        
        \param[in] connection
        */
        explicit DebugHandStream(astra_streamconnection_t connection)
            : DataStream(connection),
              debugHandStream_(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_DEBUG_HAND;

        /*! 
        \brief set view type
        
        \param[in] Debug Hand View Type
        */
        void set_view_type(DebugHandViewType view)
        {
            astra_debug_handstream_set_view_type(debugHandStream_, view);
        }

        /*! 
        \brief set is use mouse probe
        
        \param[in] is use mouse probe
        */
        void set_use_mouse_probe(bool useMouseProbe)
        {
            astra_debug_handstream_set_use_mouse_probe(debugHandStream_, useMouseProbe);
        }

        /*! 
        \brief set mouse position
        
        \param[in] mouse position
        */
        void set_mouse_position(Vector2f position)
        {
            astra_debug_handstream_set_mouse_position(debugHandStream_, position);
        }

        /*! 
        \brief set pause input
        
        \param[in] pause input
        */
        void set_pause_input(bool pauseInput)
        {
            astra_debug_handstream_set_pause_input(debugHandStream_, pauseInput);
        }

        /*! 
        \brief set lock spawn point
        
        \param[in] lock spawn point
        */
        void set_lock_spawn_point(bool lockSpawnPoint)
        {
            astra_debug_handstream_set_lock_spawn_point(debugHandStream_, lockSpawnPoint);
        }

        /*! 
        \brief get view type
        
        \return Debug Hand View Type
        */
        DebugHandViewType get_view_type() const
        {
            DebugHandViewType view;
            astra_debug_handstream_get_view_type(debugHandStream_, &view);
            return view;
        }

    private:
        astra_debug_handstream_t debugHandStream_;
    };

    /*!
      \brief A Debug Hand Frame

      \details A Debug Hand Frame
     */
    class DebugHandFrame : public ImageFrame<RgbPixel, ASTRA_STREAM_DEBUG_HAND>
    {
    public:
        /*! 
        \brief default constructs
        
        \param[in] frame
        */
        DebugHandFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGB888)
        {}
    };
    /** @} */
}

#endif /* ASTRA_HAND_DEBUG_HPP */
