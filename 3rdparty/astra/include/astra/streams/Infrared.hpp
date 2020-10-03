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
#ifndef ASTRA_INFRARED_HPP
#define ASTRA_INFRARED_HPP

#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/infrared_capi.h>
#include <astra/streams/Image.hpp>
#include <astra/Vector.hpp>

namespace astra {

    /*!
      \defgroup cpp_ir_api_ref infrared stream apis
      \ingroup cpp_low_api_ref
      @{
     */

    /*!
      \brief A Infrared Stream

      \details A Infrared Stream.
     */
    class InfraredStream : public ImageStream
    {
    public:
        explicit InfraredStream(astra_streamconnection_t connection)
            : ImageStream(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_INFRARED;
    };

    /*!
      \brief A Infrared Frame use 16bit unsigned short format.

      \details A Infrared Frame use 16bit unsigned short format.
     */
    class InfraredFrame16 : public ImageFrame<uint16_t, ASTRA_STREAM_INFRARED>
    {
    public:
        InfraredFrame16(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_GRAY16)
        {}
    };

    /*!
      \brief A Infrared Frame use rgb format.

      \details A Infrared Frame use rgb format.
     */
    class InfraredFrameRgb : public ImageFrame<RgbPixel, ASTRA_STREAM_INFRARED>
    {
    public:
        InfraredFrameRgb(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGB888)
        {}
    };
    /** @} */
}

#endif /* ASTRA_INFRARED_HPP */
