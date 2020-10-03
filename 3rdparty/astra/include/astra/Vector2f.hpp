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
#ifndef ASTRA_VECTOR2F_HPP
#define ASTRA_VECTOR2F_HPP

#include <cmath>
#include "capi/astra_ctypes.h"

namespace astra
{
    /*! 
    \ingroup cpp_basic_types_ref
    \brief Represents a float 2d vector 
    */
    struct Vector2f : public astra_vector2f_t
    {
        Vector2f()
        {
            this->x = 0.0f;
            this->y = 0.0f;
        }

        Vector2f(const astra_vector2f_t& v)
        {
            *this = v;
        }

        Vector2f& operator=(const astra_vector2f_t& rhs)
        {
            ::astra_vector2f_t::x = rhs.x;
            ::astra_vector2f_t::y = rhs.y;

            return *this;
        }

        Vector2f(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        inline operator ::astra_vector2f_t*() { return this; }
        inline operator const ::astra_vector2f_t*() const { return this; }

        float length() const;
        float length_squared() const;
        float dot(const Vector2f& v) const;

        static Vector2f normalize(Vector2f v);

        static inline Vector2f zero();
        inline bool is_zero() const;

        friend bool operator==(const Vector2f& lhs, const Vector2f& rhs);
        friend Vector2f operator+(const Vector2f& lhs, const Vector2f& rhs);
        friend Vector2f operator-(const Vector2f& lhs, const Vector2f& rhs);
        friend Vector2f operator*(const Vector2f& lhs, const float& rhs);
        friend Vector2f operator*(const float& lhs, const Vector2f& rhs);
        friend Vector2f operator/(const Vector2f& lhs, const float& rhs);

        Vector2f operator-();
        Vector2f& operator+=(const Vector2f& rhs);
        Vector2f& operator-=(const Vector2f& rhs);
        Vector2f& operator*=(const float& rhs);
        Vector2f& operator/=(const float& rhs);
    };

    inline Vector2f Vector2f::normalize(Vector2f v)
    {
        double length = std::sqrt(v.x*v.x + v.y*v.y);

        if (length < 1e-9)
        {
            return Vector2f(0.0f, 0.0f);
        }
        else
        {
            return Vector2f(
                static_cast<float>(v.x / length),
                static_cast<float>(v.y / length));
        }
    }

    inline float Vector2f::length() const
    {
        return std::sqrt(x * x + y * y);
    }

    inline float Vector2f::length_squared() const
    {
        return x * x + y * y;
    }

    inline float Vector2f::dot(const Vector2f& v) const
    {
        return x * v.x + y * v.y;
    }

    inline Vector2f& Vector2f::operator+=(const Vector2f& rhs)
    {
        this->x = this->x + rhs.x;
        this->y = this->y + rhs.y;
        return *this;
    }

    inline Vector2f& Vector2f::operator-=(const Vector2f& rhs)
    {
        this->x = this->x - rhs.x;
        this->y = this->y - rhs.y;
        return *this;
    }

    inline Vector2f& Vector2f::operator*=(const float& rhs)
    {
        this->x = this->x * rhs;
        this->y = this->y * rhs;
        return *this;
    }

    inline Vector2f& Vector2f::operator/=(const float& rhs)
    {
        this->x = this->x / rhs;
        this->y = this->y / rhs;
        return *this;
    }

    inline Vector2f Vector2f::operator-()
    {
        return Vector2f(-this->x, -this->y);
    }

    inline bool operator==(const Vector2f& lhs, const Vector2f& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    inline bool operator!=(const Vector2f& lhs, const Vector2f& rhs)
    {
        return !(lhs == rhs);
    }

    inline Vector2f operator+(const Vector2f& lhs, const Vector2f& rhs)
    {
        return Vector2f(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    inline Vector2f operator-(const Vector2f& lhs, const Vector2f& rhs)
    {
        return Vector2f(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    inline Vector2f operator*(const Vector2f& lhs, const float& rhs)
    {
        return Vector2f(lhs.x * rhs, lhs.y * rhs);
    }

    inline Vector2f operator*(const float& lhs, const Vector2f& rhs)
    {
        return rhs * lhs;
    }

    inline Vector2f operator/(const Vector2f& lhs, const float& rhs)
    {
        return Vector2f(lhs.x / rhs, lhs.y / rhs);
    }

    inline Vector2f Vector2f::zero()
    {
        Vector2f zero;
        return zero;
    }

    inline bool Vector2f::is_zero() const
    {
        return *this == zero();
    }

}

#endif // ASTRA_VECTOR2F_HPP
