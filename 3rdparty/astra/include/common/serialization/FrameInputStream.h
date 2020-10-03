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
#ifndef FRAMEINPUTSTREAM_H
#define FRAMEINPUTSTREAM_H

#include "StreamFileModels.h"
#include <cstdint>
#include <exception>

#ifndef __has_feature
#define __has_feature(x) 0
#endif

// Is noexcept supported?
#if (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46) || \
    (defined(__clang__) && defined(__has_feature) && __has_feature(cxx_noexcept)) || \
    (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023026)
#  define NOEXCEPT noexcept
#else
#  define NOEXCEPT
#endif

namespace astra { namespace serialization {


    class ResourceNotFoundException : std::exception
    {
    public:
        ResourceNotFoundException(const char* uri)
            : m_uri(uri)
        {

        }

        const char* what() const NOEXCEPT override
        {
            return m_uri;
        }

    private:
        const char* m_uri;
    };

    class FrameInputStream
    {
    public:
        FrameInputStream() { }
        virtual ~FrameInputStream() { }

        virtual void close() = 0;
        virtual bool read_frame(Frame*& frame) = 0;
        virtual bool read_frame_description(FrameDescription*& frameDescription) = 0;
        virtual bool read_stream_header(StreamHeader*& streamHeader) = 0;
        virtual bool seek(int offset) = 0;
        virtual bool seek_to_first_frame() = 0;
        virtual int64_t get_position() = 0;
        virtual bool is_end_of_file() = 0;
        virtual int get_frame_description_size() = 0;
        virtual int get_stream_header_size() = 0;
    };
}}

#endif /* FRAMEINPUTSTREAM_H */
