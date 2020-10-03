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
#ifndef FRAMESTREAMREADER_H
#define FRAMESTREAMREADER_H

#include "StreamFileModels.h"
#include "FrameInputStream.h"
#include "../clock/Pulser.h"

namespace astra { namespace serialization {

    FrameInputStream* open_frame_input_stream(const char* path);

    class FrameStreamReader
    {
    public:
        FrameStreamReader(FrameInputStream* frameStream);
        ~FrameStreamReader();

        void close();
        bool read();
        bool seek(int numberOfFrames);
        int get_stream_type();
        int get_buffer_length();
        bool is_end_of_file();
        Frame& peek();
        FrameInputStream* get_frame_input_stream();

    private:

        FrameInputStream* m_inputStream;
        FrameDescription* m_frameDescription;
        StreamHeader* m_streamHeader;
        Frame* m_frame;
        clock::Pulser m_pulser;

        bool m_isEndOfFile{ false };
    };
}}

#endif /* FRAMESTREAMREADER_H */