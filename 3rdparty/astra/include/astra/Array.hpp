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
#ifndef ASTRA_ARRAY_HPP
#define ASTRA_ARRAY_HPP

namespace astra {
    /*!
      \ingroup cpp_basic_types_ref
      \brief Simple wrapper around primitive arrays
      \details Provides a strongly-typed wrapper around primitive C-style arrays.
      Array does not copy or consider itself the owner of the data provided
      through the constructor. Users should make sure that the Array instance does
      not live longer than the data it points to.
    */
    template<typename T>
    class Array
    {
    public:
        /*! \brief Default constructs zero-length array */
        inline Array() : ptr_(nullptr), size_(0) {}
        /*! \brief Implicit conversion constructor from nullptr to a zero-length array */
        inline Array(decltype(nullptr)) : ptr_(nullptr), size_(0) {}
        /*! \brief Constructs array from pointer and size */
        inline Array(T* ptr, size_t size) : ptr_(ptr), size_(size) {}
        /*! \brief Constructs array from begin and end iterators */
        inline Array(T* begin, T* end) : ptr_(begin), size_(end - begin) {}

        /*! \brief Gets size of array */
        inline size_t size() const { return size_; }
        /*! \brief Returns true if array is zero length */
        inline bool empty() const { return size_ == 0; }

        /*! \brief Gets mutable raw pointer to array data */
        inline T* data() { return ptr_; }
        /*! \brief Gets immutable raw pointer to array data */
        inline const T* data() const { return ptr_; }

        /*! \brief Gets mutable iterator pointing to beginning of array */
        inline T* begin() { return ptr_; }
        /*! \brief Gets immutable iterator pointing to beginning of array */
        inline const T* begin() const { return ptr_; }
        /*! \brief Gets mutable iterator pointing to one past the end of array */
        inline T* end() { return ptr_ + size_; }
        /*! \brief Gets iterator pointing to one past the end of array */
        inline const T* end() const { return ptr_ + size_; }

        /*! \brief Gets mutable reference to first array element */
        inline T& front() { return *ptr_; }
        /*! \brief Gets immutable reference to first array element */
        inline const T& front() const { return *ptr_; }
        /*! \brief Gets mutable reference to last array element */
        inline T& back() { return ptr_[size_ - 1]; }
        /*! \brief Gets immutable reference to last array element */
        inline const T& back() const { return ptr_[size_ - 1]; }

        /*!
          \brief Mutable index operator into array
          \param [in] index Index into array
        */
        inline T& operator[](size_t index)
        {
            return ptr_[index];
        }

        /*!
          \brief Immutable index operator into array
          \param [in] index Index into array
        */
        inline const T& operator[](size_t index) const
        {
            return ptr_[index];
        }

        /*!
          \brief Creates a mutable sub-array of the same type based on a start and end index
          \param [in] start Start index
          \param [in] end End index (exclusive)
        */
        inline Array<T> slice(size_t start, size_t end)
        {
            return Array<T>(ptr_ + start, end - start);
        }

        /*!
          \brief Creates an immutable sub-array of the same type based on
          a start and end index
          \param [in] start Start index
          \param [in] end End index (exclusive)
        */
        inline Array<const T> slice(size_t start, size_t end) const
        {
            return Array<const T>(ptr_ + start, end - start);
        }

        /*! \brief Identity based equality operator */
        inline bool operator==(const Array& other) const
        {
            if (this == &other) { return true; }
            return this->ptr_ == other.ptr_;
        }

        /*! \brief Identity based inequality operator */
        inline bool operator!=(const Array& other) const { return !(*this == other); }

    private:
        T* ptr_;
        size_t size_;
    };

    /*!
      \ingroup cpp_basic_types_ref
      \brief Simplifies \ref Array construction by leveraging
      function template type deduction
      \param [in] ptr Pointer to array
      \param [in] size Size of array
    */
    template<typename T>
    inline Array<T> make_array(T* ptr, std::size_t size)
    {
        return Array<T>(ptr, size);
    }

}

#endif // ASTRA_ARRAY_HPP
