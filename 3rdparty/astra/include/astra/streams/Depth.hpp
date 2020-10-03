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
#ifndef ASTRA_DEPTH_HPP
#define ASTRA_DEPTH_HPP

#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/depth_capi.h>
#include <astra/streams/Image.hpp>
#include <astra/Vector.hpp>

namespace astra {

    /*!
      \defgroup cpp_depth_api_ref depth stream apis
      \ingroup cpp_low_api_ref
      @{
     */

    /*!
      \brief CoordinateMapper

      \details Can convert coordinate system of point.
     */
    class CoordinateMapper
    {
    public:
        /*! 
        \brief Constructs
        */
        CoordinateMapper(astra_depthstream_t depthStream)
            : depthStream_(depthStream)
        { }

        /*! 
        \brief copy Constructs
        */
        CoordinateMapper(const CoordinateMapper& rhs)
        {
            this->depthStream_ = rhs.depthStream_;
        }

        /*! 
        \brief copy Constructs
        */
        CoordinateMapper operator=(const CoordinateMapper& rhs)
        {
            this->depthStream_ = rhs.depthStream_;
            return *this;
        }

        /*!
          \brief convert depth coor to world coor

          \param[in] dpeth position
          \return world position          
        */
        astra::Vector3f convert_depth_to_world(astra::Vector3f depthPosition) const
        {
            float worldX, worldY, worldZ;
            astra_convert_depth_to_world(depthStream_,
                                         depthPosition.x,
                                         depthPosition.y,
                                         depthPosition.z,
                                         &worldX, &worldY, &worldZ);

            return Vector3f(worldX, worldY, worldZ);
        }

        /*!
          \brief convert depth coor to world coor

          \param[in] world position
          \return dpeth position
        */
        Vector3f convert_world_to_depth(Vector3f worldPosition) const
        {
            float depthX, depthY, depthZ;
            astra_convert_world_to_depth(depthStream_,
                                         worldPosition.x,
                                         worldPosition.y,
                                         worldPosition.z,
                                         &depthX, &depthY, &depthZ);

            return Vector3f(depthX, depthY, depthZ);
        }

        /*!
          \brief convert depth coor to world coor

          \param[in] depth x
          \param[in] depth y
          \param[in] depth z
          \param[out] world x
          \param[out] world y
          \param[out] world z
         */
        void convert_depth_to_world(float  depthX, float  depthY, float  depthZ,
                                    float& worldX, float& worldY, float& worldZ) const
        {
            astra_convert_depth_to_world(depthStream_, depthX, depthY, depthZ,
                                         &worldX, &worldY, &worldZ);
        }

         /*!
          \brief convert world coor to depth coor

          \param[in] world x
          \param[in] world y
          \param[in] world z
          \param[out] depth x
          \param[out] depth y
          \param[out] depth z
         */
        void convert_world_to_depth(float  worldX, float  worldY, float  worldZ,
                                    float& depthX, float& depthY, float& depthZ) const
        {
            astra_convert_world_to_depth(depthStream_,
                                         worldX, worldY, worldZ,
                                         &depthX, &depthY, &depthZ);
        }

    private:
        astra_depthstream_t depthStream_;
    };

    /*!
      \brief A Depth Stream

      \details Depth Stream is a stream form depth sensor device.
     */
    class DepthStream : public ImageStream
    {
    public:
        explicit DepthStream(astra_streamconnection_t connection)
            : ImageStream(connection),
              depthStream_(reinterpret_cast<astra_depthstream_t>(connection)),
              coordinateMapper_(reinterpret_cast<astra_depthstream_t>(connection))
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_DEPTH;

        /*!
          \brief get world conversion

          \return world conversion          
         */
        astra_conversion_cache_t depth_to_world_data() const
        {
            astra_conversion_cache_t data;
            astra_depthstream_get_depth_to_world_data(depthStream_, &data);

            return data;
        }

        /*!
          \brief return is registration enabled

          \return registration enabled
         */
        bool registration_enabled() const
        {
            bool enabled = false;
            astra_depthstream_get_registration(depthStream_, &enabled);

            return enabled;
        }

        /*!
          \brief enable registration

          \param[in] enable
         */
        void enable_registration(bool enable)
        {
            astra_depthstream_set_registration(depthStream_, enable);
        }

        /*!
          \brief set depth to color resolution if device supports.

          \param[in] mode refer to device.
         */
        void set_d2c_resolution(int mode)
        {
            astra_depthstream_set_d2c_resolution(depthStream_, mode);
        }

        /*!
          \brief get depth to color resolution if device supports.

          \return mode refer to device.
         */
        int get_d2c_resolution()
        {
            int mode = 0;
            astra_depthstream_get_d2c_resolution(depthStream_, &mode);
            return mode;
        }

        /*!
          \brief get serial number

          \param[in/out] serial number data buffer
          \param[in] length of serial number
         */
        void serial_number(char* serialnumber, uint32_t length) const
        {
            astra_depthstream_get_serialnumber(depthStream_, serialnumber, length);
        }

        /*!
          \brief get serial number

          \return serial number
         */
        std::string serial_number() const
        {
            char serialNumber[ASTRA_SERIAL_NUMBER_MAX];
            astra_depthstream_get_serialnumber(depthStream_, serialNumber, sizeof(serialNumber) / sizeof(char));
            return std::string(serialNumber);
        }

        /*!
          \brief get chip id

          \return chip id
         */
        std::uint32_t chip_id() const
        {
            uint32_t chip_id;
            astra_depthstream_get_chip_id(depthStream_, &chip_id);
            return chip_id;
        }

        /*!
        \brief start record oni file.

        \param[in] filename the full name of oni file.
        */
        void start_record(std::string filename)
        {
            astra_depthstream_start_record(depthStream_, filename.c_str());
        }

        /*!
        \brief stop record oni file.
        */
        void stop_record()
        {
            astra_depthstream_stop_record(depthStream_);
        }

        /*!
          \brief get Coordinate Mapper

          \return Coordinate Mapper
         */
        const CoordinateMapper& coordinateMapper() const { return coordinateMapper_; };

    private:
        astra_depthstream_t depthStream_;
        CoordinateMapper coordinateMapper_;
    };

    
    /*!
      \brief A Depth Frame

      \details Depth Frame of short format, 1 mm per value;
     */
    class DepthFrame : public ImageFrame<int16_t, ASTRA_STREAM_DEPTH>
    {
    public:
        DepthFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_DEPTH_MM)
        {}

    };
    /** @} */
}

#endif /* ASTRA_DEPTH_HPP */
