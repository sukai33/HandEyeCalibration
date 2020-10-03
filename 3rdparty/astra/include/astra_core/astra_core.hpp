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
#ifndef ASTRA_CORE_HPP
#define ASTRA_CORE_HPP

#include "StreamSet.hpp"
#include "StreamDescription.hpp"
#include "Frame.hpp"
#include "FrameListener.hpp"
#include "StreamReader.hpp"
#include "DataStream.hpp"
#include "astra_cxx_make_unique.hpp"

namespace astra {

    /*!
     * \ingroup cpp_core_api_ref
     * \brief Initializes the library.
     * \details This function must be called before calling any other function.
     */
    inline astra_status_t initialize()
    {
        return astra_initialize();
    }

    /*!
     * \ingroup cpp_core_api_ref
     * \brief Terminate the library, destroying all its streams. 
     * \details This function must be called when library not used, otherwise there will be problems when re-initialize it.And do not call any other function after calling this method.
     */
    inline astra_status_t terminate()
    {
        return astra_terminate();
    }
}

#endif // ASTRA_CORE_HPP
