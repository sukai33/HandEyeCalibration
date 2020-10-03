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
#ifndef PULSER_H
#define PULSER_H

#include "Stopwatch.h"
#include <string>

namespace astra { namespace clock {

    class Pulser
    {
    public:
        Pulser();
        ~Pulser();

        void set_period(double period);
        double get_period();

        void start();
        void stop();

        void pause();
        bool is_pulse();
        void reset();

    private:
        Stopwatch m_swatch;
        std::string m_swatchName;

        double m_period{0.0};
    };
}}


#endif /* PULSER_H */