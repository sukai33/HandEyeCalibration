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
#ifndef BODY_PARAMETERS_H
#define BODY_PARAMETERS_H

enum {
    ASTRA_PARAMETER_BODY_DEFAULT_BODY_FEATURES = 1,
    ASTRA_PARAMETER_BODY_SKELETON_PROFILE = 2,
    ASTRA_PARAMETER_BODY_SKELETON_OPTIMIZATION = 3,
    ASTRA_PARAMETER_BODY_ORIENTATION = 4
};

enum {
    ASTRA_COMMAND_GET_BODY_FEATURES = 1001,
    ASTRA_COMMAND_SET_BODY_FEATURES = 1002,
};

enum {
    ORBBEC_BODY_TRACKING_EVENT_SET_LICENSE = 1001
};

#endif /* BODY_PARAMETERS_H */
