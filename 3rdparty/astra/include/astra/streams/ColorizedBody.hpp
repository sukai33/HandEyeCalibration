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
#ifndef ASTRA_COLORIZEDBODY_HPP
#define ASTRA_COLORIZEDBODY_HPP

#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/colorized_body_capi.h>
#include <astra/streams/Image.hpp>

namespace astra {

    /*!
      \defgroup cpp_colorbody_api_ref colorized body stream apis
      \ingroup cpp_high_api_ref
      @{
     */

    /*!
      \brief A Colorized Body Stream

      \details A Colorized Body Stream
     */
    class ColorizedBodyStream : public DataStream
    {
    public:
		ColorizedBodyStream()
        {}

        explicit ColorizedBodyStream(astra_streamconnection_t connection)
            : DataStream(connection)
        {
			colorizedbodyStream_ = reinterpret_cast<astra_colorizedbodystream_t>(connection);
        }

        static const astra_stream_type_t id = ASTRA_STREAM_COLORIZED_BODY;

    private:
		astra_colorizedbodystream_t colorizedbodyStream_;
    };

    /*!
      \brief A Colorized Body Frame

      \details A Colorized Body Frame
     */
    class ColorizedBodyFrame : public ImageFrame<RgbaPixel, ASTRA_STREAM_COLORIZED_BODY>
    {
    public:
		ColorizedBodyFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGBA)
        {}
    };
    /** @} */
}

#endif // ASTRA_COLORIZEDBODY_HPP
