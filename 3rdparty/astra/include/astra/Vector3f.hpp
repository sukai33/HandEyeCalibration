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
#ifndef ASTRA_VECTOR3F_HPP
#define ASTRA_VECTOR3F_HPP

#include <cmath>
#include "capi/astra_ctypes.h"

namespace astra {

    /*! 
    \ingroup cpp_basic_types_ref
    \brief Represents a float 3d vector 
    */
    struct Vector3f : public astra_vector3f_t
    {
        Vector3f()
        {
            this->x = 0.0;
            this->y = 0.0;
            this->z = 0.0;
        }

        Vector3f(const astra_vector3f_t& v)
        {
            *this = v;
        }

        Vector3f& operator=(const astra_vector3f_t& rhs)
        {
            ::astra_vector3f_t::x = rhs.x;
            ::astra_vector3f_t::y = rhs.y;
            ::astra_vector3f_t::z = rhs.z;

            return *this;
        }

        Vector3f(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        inline operator ::astra_vector3f_t*() { return this; }
        inline operator const ::astra_vector3f_t*() const { return this; }

        float length() const;
        float length_squared() const;
        float dot(const Vector3f& v) const;

        Vector3f cross(const Vector3f& v) const;

        static inline Vector3f zero();
        static Vector3f normalize(Vector3f v);

        friend bool operator==(const Vector3f& lhs, const Vector3f& rhs);
        friend bool operator!=(const Vector3f& lhs, const Vector3f& rhs);

        bool is_zero() const;

        Vector3f& operator+=(const Vector3f& rhs);
        Vector3f& operator-=(const Vector3f& rhs);
        Vector3f& operator*=(const float& rhs);
        Vector3f& operator/=(const float& rhs);

        friend Vector3f operator+(const Vector3f& lhs, const Vector3f& rhs);
        friend Vector3f operator-(const Vector3f& lhs, const Vector3f& rhs);
        friend Vector3f operator*(const Vector3f& lhs, const float& rhs);
        friend Vector3f operator*(const float& lhs, const Vector3f& rhs);
        friend Vector3f operator/(const Vector3f& lhs, const float& rhs);

        Vector3f operator-();
    };

    inline float Vector3f::length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    inline float Vector3f::length_squared() const
    {
        return x * x + y * y + z * z;
    }

    inline float Vector3f::dot(const Vector3f& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    inline Vector3f Vector3f::cross(const Vector3f& v) const
    {
        return Vector3f(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }

    inline Vector3f Vector3f::normalize(Vector3f v)
    {
        double length = std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
        if (length < 1e-9)
        {
            return Vector3f(0.0f, 0.0f, 0.0f);
        }
        else
        {
            return Vector3f(
                static_cast<float>(v.x / length),
                static_cast<float>(v.y / length),
                static_cast<float>(v.z / length));
        }
    }

    inline Vector3f Vector3f::zero()
    {
        static Vector3f zero;
        return zero;
    }

    inline bool Vector3f::is_zero() const
    {
        return *this == zero();
    }

    inline Vector3f& Vector3f::operator+=(const Vector3f& rhs)
    {
        this->x = this->x + rhs.x;
        this->y = this->y + rhs.y;
        this->z = this->z + rhs.z;
        return *this;
    }

    inline Vector3f& Vector3f::operator-=(const Vector3f& rhs)
    {
        this->x = this->x - rhs.x;
        this->y = this->y - rhs.y;
        this->z = this->z - rhs.z;
        return *this;
    }

    inline Vector3f& Vector3f::operator*=(const float& rhs)
    {
        this->x = this->x * rhs;
        this->y = this->y * rhs;
        this->z = this->z * rhs;
        return *this;
    }

    inline Vector3f& Vector3f::operator/=(const float& rhs)
    {
        this->x = this->x / rhs;
        this->y = this->y / rhs;
        this->z = this->z / rhs;
        return *this;
    }

    inline Vector3f Vector3f::operator-()
    {
        return Vector3f(-this->x, -this->y, -this->z);
    }

    inline bool operator==(const Vector3f& lhs, const Vector3f& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }

    inline bool operator!=(const Vector3f& lhs, const Vector3f& rhs)
    {
        return !(lhs == rhs);
    }

    inline Vector3f operator+(const Vector3f& lhs, const Vector3f& rhs)
    {
        return Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    inline Vector3f operator-(const Vector3f& lhs, const Vector3f& rhs)
    {
        return Vector3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    inline Vector3f operator*(const Vector3f& lhs, const float& rhs)
    {
        return Vector3f(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }

    inline Vector3f operator*(const float& lhs, const Vector3f& rhs)
    {
        return rhs * lhs;
    }

    inline Vector3f operator/(const Vector3f& lhs, const float& rhs)
    {
        return Vector3f(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
    }
}

#endif /* ASTRA_VECTOR3F_HPP */
