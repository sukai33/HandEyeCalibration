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
#ifndef FRAMESTREAMWRITER_H
#define FRAMESTREAMWRITER_H

#include <astra/astra.hpp>
#include <astra/capi/streams/stream_types.h>
#include <astra_core/capi/plugins/astra_plugin.h>

#include "StreamFileModels.h"
#include "../clock/Stopwatch.h"
#include "FrameOutputStream.h"

#include <memory>

namespace astra { namespace serialization {

    FrameOutputStream* open_frame_output_stream(FILE* file);
    void close_frame_output_stream(FrameOutputStream*& stream);

    class FrameStreamWriter
    {
    public:
        FrameStreamWriter(FrameOutputStream& frameOutputStream);
        ~FrameStreamWriter();

        bool begin_write();
        bool end_write();
        bool write(const DepthFrame& depthFrame);

    private:
        void stage_frame(astra_frame_t& astraFrame);
        void stage_frame_description(astra_frame_t& astraFrame, double fps);
        void populate_frame(astra_frame_t& astraFrame, Frame& frame);
        void populate_frame_description(astra_frame_t& astraFrame, FrameDescription& frameDescription, double fps);

        FrameOutputStream& m_outputStream;
        bool m_shouldWrite{ false };

        Stopwatch m_swatch;
        std::string m_swatchName;
    };

}}

#endif /* FRAMESTREAMWRITER_H */
