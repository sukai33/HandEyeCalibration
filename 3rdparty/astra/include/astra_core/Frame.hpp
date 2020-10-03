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
#ifndef ASTRA_FRAME_HPP
#define ASTRA_FRAME_HPP

#include <memory>
#include "capi/astra_core.h"

namespace astra {

    /*!
      \ingroup cpp_core_api_ref
      \brief Frame class

      \details Basic frame class of frame
     */
    class Frame
    {
    public:
        Frame(astra_reader_frame_t readerFrame, const bool autoCloseFrame)
            : frameRef_(std::make_shared<FrameRef>(readerFrame, autoCloseFrame))
        { }

        Frame(astra_reader_frame_t readerFrame)
            : Frame(readerFrame, true)
        { }

        template<typename T>
        T get()
        {
            return get<T>(DEFAULT_SUBTYPE);
        }

        template<typename T>
        T get(astra_stream_subtype_t subtype)
        {
            return T::template acquire<T>(frameRef_->get_frame(), subtype);
        }

        bool is_valid()
        {
            return frameRef_->get_frame() != nullptr;
        }

        operator bool()
        {
            return is_valid();
        }

    private:
        class FrameRef
        {
        public:
            FrameRef(astra_reader_frame_t readerFrame, const bool autoCloseFrame)
                :  frame_(readerFrame),
                   autoCloseFrame_(autoCloseFrame)
            { }

            ~FrameRef()
            {
                if (frame_ != nullptr && autoCloseFrame_)
                {
                    astra_reader_close_frame(&frame_);
                }
            }

            astra_reader_frame_t get_frame() const { return frame_; }

        private:
            astra_reader_frame_t frame_;
            const bool autoCloseFrame_;
        };

        std::shared_ptr<FrameRef> frameRef_;
    };
}

#endif // ASTRA_FRAME_HPP
