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
#ifndef ASTRA_MASKEDCOLOR_HPP
#define ASTRA_MASKEDCOLOR_HPP

#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/masked_color_capi.h>
#include <astra/streams/Image.hpp>

namespace astra {

    /*!
      \defgroup cpp_maskedcolor_api_ref masked color stream apis
      \ingroup cpp_high_api_ref
      @{
     */

    /*!
      \brief A Masked Color Stream

      \details A Masked Color Stream.
     */
    class MaskedColorStream : public DataStream
    {
    public:
        MaskedColorStream()
        {}

        explicit MaskedColorStream(astra_streamconnection_t connection)
            : DataStream(connection)
        {
            maskedcolorStream_ = reinterpret_cast<astra_maskedcolorstream_t>(connection);
        }

        static const astra_stream_type_t id = ASTRA_STREAM_MASKED_COLOR;

    private:
        astra_maskedcolorstream_t maskedcolorStream_;
    };

    /*!
      \brief A Masked Color Frame of Masked Color Stream

      \details A Masked Color Frame of Masked Color Stream
     */
    class MaskedColorFrame : public ImageFrame<RgbaPixel, ASTRA_STREAM_MASKED_COLOR>
    {
    public:
        MaskedColorFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGBA)
        {}
    };
    /** @} */
}

#endif // ASTRA_MASKEDCOLOR_HPP
