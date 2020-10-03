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
#ifndef ASTRA_FRAMELISTENER_HPP
#define ASTRA_FRAMELISTENER_HPP

namespace astra {

    class StreamReader;
    class Frame;

    /*! 
     \ingroup cpp_core_api_ref
     \brief Frame Listener class
     \details inherits this class to receive data and regist it,then when astra update has data,we will call on_frame_ready
    */
    class FrameListener
    {
    public:
        virtual ~FrameListener() = default;
        virtual void on_frame_ready(StreamReader& reader, Frame& frame) = 0;
    };

    inline bool operator==(const FrameListener& l, const FrameListener& r)
    {
        return &l == &r;
    }
}

#endif // ASTRA_FRAMELISTENER_HPP
