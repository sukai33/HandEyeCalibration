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
#ifndef ASTRA_STREAMSET_HPP
#define ASTRA_STREAMSET_HPP

#include <string>
#include "capi/astra_core.h"
#include "StreamReader.hpp"
#include <stdexcept>

namespace astra {

    static const char* ASTRA_DEFAULT_DEVICE_URI = "device/default";

    /*!
      \ingroup cpp_core_api_ref
      \brief Stream Set Class

      \details Stream Set \ref concepts_streamset.
     */
    class StreamSet
    {
    public:
        StreamSet()
            : StreamSet(ASTRA_DEFAULT_DEVICE_URI)
        {}

        StreamSet(const char* uri)
        {
            setRef_ = std::make_shared<StreamSetRef>(uri);
            setRef_->connect();
        }

        StreamSet(const StreamSet& other)
            : setRef_(other.setRef_)
        {}

        StreamSet& operator=(const StreamSet& rhs)
        {
            this->setRef_ = rhs.setRef_;
            return *this;
        }

        std::string uri()
        {
            char uri[ASTRA_STREAMSET_URI_MAX_LENGTH];
            astra_streamset_get_uri(setRef_->connection_handle(), uri, ASTRA_STREAMSET_URI_MAX_LENGTH);
            return std::string(uri);
        }

        bool is_valid() { return setRef_ != nullptr; }

        bool is_available()
        {
            bool isAvailable = false;
            if (setRef_ == nullptr || setRef_->connection_handle() == nullptr)
            {
                return isAvailable;
            }
            astra_streamset_is_available(setRef_->connection_handle(), &isAvailable);
            return isAvailable;
        }

        inline StreamReader create_reader();
        astra_streamsetconnection_t get_handle() const { return setRef_->connection_handle(); }

    private:
        class StreamSetRef;
        using StreamSetRefPtr = std::shared_ptr<StreamSetRef>;

        class StreamSetRef :
            public std::enable_shared_from_this<StreamSetRef>
        {
        public:
            StreamSetRef(std::string uri)
                :  uri_(uri)
            { }

            void connect()
            {
                if (!is_connected())
                    astra_streamset_open(uri_.c_str(), &connection_);
            }

            bool is_connected() { return connection_ != nullptr; }

            ~StreamSetRef()
            {
                if (is_connected())
                    astra_streamset_close(&connection_);
            }

            astra_streamsetconnection_t connection_handle() const { return connection_; }

        private:
            astra_streamsetconnection_t connection_{nullptr};
            std::string uri_;
        };

        StreamSetRefPtr setRef_;

        friend bool operator==(const StreamSet& lhs, const StreamSet& rhs);
        friend bool operator!=(const StreamSet& lhs, const StreamSet& rhs);
    };

    inline bool operator==(const StreamSet& lhs, const StreamSet& rhs)
    {
        return lhs.setRef_ == rhs.setRef_;
    }

    inline bool operator!=(const StreamSet& lhs, const StreamSet& rhs)
    {
        return !(lhs == rhs);
    }

    StreamReader StreamSet::create_reader()
    {
        if (!setRef_->is_connected())
            setRef_->connect();

        astra_reader_t reader;
        astra_reader_create(get_handle(), &reader);

        return StreamReader(reader);
    }
}

#endif // ASTRA_STREAMSET_HPP
