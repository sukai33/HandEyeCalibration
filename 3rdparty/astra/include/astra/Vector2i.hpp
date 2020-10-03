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
#ifndef ASTRA_VECTOR2I_HPP
#define ASTRA_VECTOR2I_HPP

#include <cmath>
#include <cstdint>
#include "capi/astra_ctypes.h"

namespace astra
{
    /*! 
    \ingroup cpp_basic_types_ref
    \brief Represents a float 2d vector 
    */
    struct Vector2i : public astra_vector2i_t
    {
        Vector2i()
        {
            this->x = 0;
            this->y = 0;
        }

        Vector2i(const astra_vector2i_t& v)
        {
            *this = v;
        }

        Vector2i& operator=(const astra_vector2i_t& rhs)
        {
            ::astra_vector2i_t::x = rhs.x;
            ::astra_vector2i_t::y = rhs.y;

            return *this;
        }

        Vector2i(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        inline operator ::astra_vector2i_t*() { return this; }
        inline operator const ::astra_vector2i_t*() const { return this; }

        float length() const;
        std::int32_t length_squared() const;
        std::int32_t dot(const Vector2i& v) const;

        static Vector2i normalize(const Vector2i& v);

        static inline const Vector2i& zero();

        inline bool is_zero() const;

        friend bool operator==(const Vector2i& lhs, const Vector2i& rhs);
        friend Vector2i operator+(const Vector2i& lhs, const Vector2i& rhs);
        friend Vector2i operator-(const Vector2i& lhs, const Vector2i& rhs);
        friend Vector2i operator*(const Vector2i& lhs, const std::int32_t rhs);
        friend Vector2i operator*(const std::int32_t lhs, const Vector2i& rhs);
        friend Vector2i operator/(const Vector2i& lhs, const std::int32_t rhs);

        Vector2i operator-();
        Vector2i& operator+=(const Vector2i& rhs);
        Vector2i& operator-=(const Vector2i& rhs);
        Vector2i& operator*=(const std::int32_t rhs);
        Vector2i& operator/=(const std::int32_t rhs);
    };

    inline Vector2i Vector2i::normalize(const Vector2i& v)
    {
        double length = std::sqrt(
            static_cast<float>(v.x*v.x + v.y*v.y));

        if (length < 1e-9)
        {
            return Vector2i(0, 0);
        }
        else
        {
            return Vector2i(
                static_cast<std::int32_t>(v.x / length),
                static_cast<std::int32_t>(v.y / length));
        }
    }

    inline float Vector2i::length() const
    {
        return std::sqrt(
            static_cast<float>(x * x + y * y));
    }

    inline std::int32_t Vector2i::length_squared() const
    {
        return x * x + y * y;
    }


    inline std::int32_t Vector2i::dot(const Vector2i& v) const
    {
        return x * v.x + y * v.y;
    }

    inline Vector2i& Vector2i::operator+=(const Vector2i& rhs)
    {
        this->x = this->x + rhs.x;
        this->y = this->y + rhs.y;
        return *this;
    }

    inline Vector2i& Vector2i::operator-=(const Vector2i& rhs)
    {
        this->x = this->x - rhs.x;
        this->y = this->y - rhs.y;
        return *this;
    }

    inline Vector2i& Vector2i::operator*=(const std::int32_t rhs)
    {
        this->x = static_cast<std::int32_t>(this->x * rhs);
        this->y = static_cast<std::int32_t>(this->y * rhs);
        return *this;
    }

    inline Vector2i& Vector2i::operator/=(const std::int32_t rhs)
    {
        this->x = static_cast<std::int32_t>(this->x / rhs);
        this->y = static_cast<std::int32_t>(this->y / rhs);

        return *this;
    }

    inline Vector2i Vector2i::operator-()
    {
        return Vector2i(-this->x, -this->y);
    }

    inline bool operator==(const Vector2i& lhs, const Vector2i& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    inline bool operator!=(const Vector2i& lhs, const Vector2i& rhs)
    {
        return !(lhs == rhs);
    }

    inline Vector2i operator+(const Vector2i& lhs, const Vector2i& rhs)
    {
        return Vector2i(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    inline Vector2i operator-(const Vector2i& lhs, const Vector2i& rhs)
    {
        return Vector2i(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    inline Vector2i operator*(const Vector2i& lhs, const std::int32_t rhs)
    {
        return Vector2i(
            static_cast<std::int32_t>(lhs.x * rhs),
            static_cast<std::int32_t>(lhs.y * rhs));
    }

    inline Vector2i operator*(const std::int32_t lhs, const Vector2i& rhs)
    {
        return rhs * lhs;
    }

    inline Vector2i operator/(const Vector2i& lhs, const std::int32_t rhs)
    {
        return Vector2i(
            static_cast<std::int32_t>(lhs.x / rhs),
            static_cast<std::int32_t>(lhs.y / rhs));
    }

    inline const Vector2i& Vector2i::zero()
    {
        static Vector2i zero;
        return zero;
    }

    inline bool Vector2i::is_zero() const
    {
        return *this == zero();
    }
}

#endif // ASTRA_VECTOR2I_HPP
