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
#ifndef ASTRA_MATRIX3X3_HPP
#define ASTRA_MATRIX3X3_HPP

#include <cmath>
#include "Vector3f.hpp"
#include "capi/astra_ctypes.h"

namespace astra {

    /*! 
    \ingroup cpp_basic_types_ref
    \brief Represents a 3x3 rotation matrix 
    */
    struct Matrix3x3 : private ::astra_matrix3x3_t
    {
        Matrix3x3()
        {
            ::astra_matrix3x3_t::m00 = 0.f;
            ::astra_matrix3x3_t::m10 = 0.f;
            ::astra_matrix3x3_t::m20 = 0.f;

            ::astra_matrix3x3_t::m01 = 0.f;
            ::astra_matrix3x3_t::m11 = 0.f;
            ::astra_matrix3x3_t::m21 = 0.f;

            ::astra_matrix3x3_t::m02 = 0.f;
            ::astra_matrix3x3_t::m12 = 0.f;
            ::astra_matrix3x3_t::m22 = 0.f;
        }

        /*! \brief X axis basis vector, or the first column vector. */
        const Vector3f& x_axis() const
        {
            return *static_cast<const Vector3f*>(&(::astra_matrix3x3_t::xAxis));
        }
        /*! \brief Y axis basis vector, or the second column vector. */
        const Vector3f& y_axis() const
        {
            return *static_cast<const Vector3f*>(&(::astra_matrix3x3_t::yAxis));
        }
        /*! \brief Z axis basis vector, or the third column vector. */
        const Vector3f& z_axis() const
        {
            return *static_cast<const Vector3f*>(&(::astra_matrix3x3_t::zAxis));
        }

        float m00() const { return ::astra_matrix3x3_t::m00; }
        float m10() const { return ::astra_matrix3x3_t::m10; }
        float m20() const { return ::astra_matrix3x3_t::m20; }

        float m01() const { return ::astra_matrix3x3_t::m01; }
        float m11() const { return ::astra_matrix3x3_t::m11; }
        float m21() const { return ::astra_matrix3x3_t::m21; }

        float m02() const { return ::astra_matrix3x3_t::m02; }
        float m12() const { return ::astra_matrix3x3_t::m12; }
        float m22() const { return ::astra_matrix3x3_t::m22; }

        friend class Joint;
    };
}

#endif /* ASTRA_MATRIX3X3_HPP */
