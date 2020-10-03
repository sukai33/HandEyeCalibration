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
#ifndef ASTRA_IMAGE_HPP
#define ASTRA_IMAGE_HPP

#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/image_capi.h>
#include <astra/capi/streams/stream_types.h>

namespace astra {

    /*! 
        \defgroup cpp_image_api_ref image stream apis
        \ingroup cpp_low_api_ref
        @{
     */

    /*!
        \brief rgb pixel struct
    */
    struct RgbPixel : public astra_rgb_pixel_t
    {
        /*! 
        \brief Default constructs all zero 
        */
        RgbPixel()
            : RgbPixel(0, 0, 0)
        {}

        /*! 
        \brief constructs
        
        \param[in] red value
        \param[in] green value
        \param[in] blue value
        */
        RgbPixel(std::uint8_t r, std::uint8_t g, std::uint8_t b)
        {
            ::astra_rgb_pixel_t::r = r;
            ::astra_rgb_pixel_t::g = g;
            ::astra_rgb_pixel_t::b = b;
        }
    };
    
    /*! 
        \brief rgba pixel struct
    */
    struct RgbaPixel : public astra_rgba_pixel_t
    {
        /*! 
        \brief Default constructs all zero 
        */
        RgbaPixel()
            : RgbaPixel(0, 0,0,0)
        {}

        /*! 
        \brief constructs
        
        \param[in] red value
        \param[in] green value
        \param[in] blue value
        \param[in] alpha value
        */
        RgbaPixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t alpha)
        {
            ::astra_rgba_pixel_t::r = r;
            ::astra_rgba_pixel_t::g = g;
            ::astra_rgba_pixel_t::b = b;
            ::astra_rgba_pixel_t::alpha = alpha;
        }
    };

    // DEPRECATED
    typedef RgbaPixel RGBAPixel;

    /*! 
        \brief Image Stream Mode               
    */
    class ImageStreamMode : private ::astra_imagestream_mode_t
    {
    public:
        /*! 
        \brief Default constructs 
        */
        ImageStreamMode()
         : ImageStreamMode(0, 0, 0, ASTRA_PIXEL_FORMAT_UNKNOWN)
        {}

        /*! 
        \brief constructs
        
        \param[in] width
        \param[in] height
        \param[in] fps
        \param[in] format
        */
        ImageStreamMode(std::uint32_t width, std::uint32_t height, std::uint8_t fps, astra_pixel_format_t format)
        {
            set_width(width);
            set_height(height);
            set_fps(fps);
            set_pixel_format(format);
        }

        /*! 
        \brief copy constructs
        
        \param[in] other mode        
        */
        ImageStreamMode(const ::astra_imagestream_mode_t& mode)
        {
            *this = mode;
        }

        /*! 
        \brief copy constructs
        
        \param[in] other mode
        */
        ImageStreamMode& operator=(const ::astra_imagestream_mode_t& mode)
        {
            set_width(mode.width);
            set_height(mode.height);
            set_fps(mode.fps);
            set_pixel_format(mode.pixelFormat);

            return *this;
        }

        operator ::astra_imagestream_mode_t*() { return this; }
        operator const ::astra_imagestream_mode_t*() const { return this; }

        /*! 
        \brief get fps
        
        \return fps
        */
        std::uint8_t fps() const { return astra_imagestream_mode_t::fps; }
        
        /*! 
        \brief set fps
        
        \param[in] fps
        */
        void set_fps(std::uint8_t fps) { astra_imagestream_mode_t::fps = fps; }

        /*! 
        \brief get bytes per pixel 
        
        \return bytes per pixel 
        */
        const std::uint8_t bytes_per_pixel() const
        {
            std::uint8_t bpp;
            astra_pixelformat_get_bytes_per_pixel(pixel_format(), &bpp);
            return bpp;
        }

        /*! 
        \brief get width
        
        \return width
        */
        std::uint32_t width() const { return astra_imagestream_mode_t::width; }
        
        /*! 
        \brief set width
        
        \param[in] width
        */
        void set_width(std::uint32_t width) { astra_imagestream_mode_t::width = width; }

        /*! 
        \brief get height
        
        \return height
        */
        std::uint32_t height() const { return astra_imagestream_mode_t::height; }
        
        /*! 
        \brief set height
        
        \param[in] height
        */
        void set_height(std::uint32_t height) { astra_imagestream_mode_t::height = height; }

        /*! 
        \brief get height
        
        \return pixel format
        */
        astra_pixel_format_t pixel_format() const { return astra_imagestream_mode_t::pixelFormat; }
        
        /*! 
        \brief set fps
        
        \param[in] pixel format
        */
        void set_pixel_format(astra_pixel_format_t format) { astra_imagestream_mode_t::pixelFormat = format; }

        friend std::ostream& operator<<(std::ostream& os, const ImageStreamMode& ism);
    };

     /*! 
        \brief compare is ImageStreamMode equal
        
        \param[in] ImageStreamMode
        \param[in] ImageStreamMode
        \return is ImageStreamMode equal
        */
    inline bool operator==(const ImageStreamMode& lhs, const ImageStreamMode& rhs)
    {
        return
            lhs.width() == rhs.width() &&
            lhs.height() == rhs.height() &&
            lhs.pixel_format() == rhs.pixel_format() &&
            lhs.fps() == rhs.fps() &&
            lhs.bytes_per_pixel() && rhs.bytes_per_pixel();
    }

     /*! 
        \brief compare is ImageStreamMode not equal
        
        \param[in] ImageStreamMode
        \param[in] ImageStreamMode
        \return is ImageStreamMode not equal
        */
    inline bool operator!=(const ImageStreamMode& lhs, const ImageStreamMode& rhs)
    {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ImageStreamMode& ism)
    {
        os << ism.width()
           << "x"
           << ism.height()
           << "x"
           << static_cast<int>(ism.bytes_per_pixel())
           << "@"
           << static_cast<int>(ism.fps())
           << " pf:"
           << ism.pixel_format();

        return os;
    }

    /*! 
        \brief basic Image Stream
    */
    class ImageStream : public DataStream
    {
    public:
        explicit ImageStream(astra_streamconnection_t connection)
            : DataStream(connection),
              imageStream_(reinterpret_cast<astra_imagestream_t>(connection))
        {}

        /*! 
            \brief get horizontal fov
            
            \return horizontal fov
        */
        float hFov() const
        {
            float hFov = 0.0f;
            astra_imagestream_get_hfov(imageStream_, &hFov);

            return hFov;
        }

        /*! 
            \brief get vertical fov
            
            \return vertical fov
        */
        float vFov() const
        {
            float vFov = 0.0f;
            astra_imagestream_get_vfov(imageStream_, &vFov);

            return vFov;
        }

        /*! 
            \brief get usb_info
            
            \return usb_info
        */
        astra_usb_info_t usb_info()const
        {
            astra_usb_info_t usbInfo;
            astra_imagestream_get_usb_info(imageStream_, &usbInfo);
            return usbInfo;
        }

        /*! 
            \brief get is mirroring
            
            \return is mirroring
        */
        bool mirroring_enabled() const
        {
            bool mirroring = false;
            astra_imagestream_get_mirroring(imageStream_, &mirroring);

            return mirroring;
        }

        /*! 
            \brief enable mirroring
            
            \param[int] mirroring
        */
        void enable_mirroring(bool mirroring)
        {
            astra_imagestream_set_mirroring(imageStream_, mirroring);
        }

        /*! 
            \brief get available_modes
            
            \return available modes
        */
        std::vector<ImageStreamMode> available_modes() const
        {
            astra_result_token_t token;
            std::uint32_t count = 0;
            astra_status_t ret = astra_imagestream_request_modes(imageStream_, &token, &count);
            if (ret != ASTRA_STATUS_SUCCESS)
                return std::vector<ImageStreamMode>();

            std::vector<ImageStreamMode> result;
            result.resize(count);

            astra_imagestream_get_modes_result(imageStream_,
                                               token,
                                               reinterpret_cast<astra_imagestream_mode_t*>(&result[0]),
                                               count);

            return result;
        }

        /*! 
            \brief get current image mode
            
            \return current image mode
        */
        ImageStreamMode mode() const
        {
            ImageStreamMode mode;
            astra_imagestream_mode_t* cMode = mode;
            astra_imagestream_get_mode(imageStream_, cMode);
            return mode;
        }

        /*! 
            \brief set current image mode
            
            \param[in] image mode
        */
        void set_mode(const ImageStreamMode& mode)
        {
            const astra_imagestream_mode_t* cMode = mode;
            astra_imagestream_set_mode(imageStream_, cMode);
        }

    private:
        astra_imagestream_t imageStream_;
    };

    
    /*! 
        \brief Basic Image Frame
    */
    template<typename TDataType, astra_stream_type_t TStreamType>
    class ImageFrame
    {
    public:
        /*! 
        \brief Default constructs 
        
        \param[in] frame
        \param[in] expected_format
        */
        ImageFrame(astra_imageframe_t frame, astra_pixel_format_t expected_format)
        {
            imageFrame_ = frame;
            if (imageFrame_)
            {                
                if (imageFrame_->metadata.pixelFormat != expected_format)
                {
                    //wrong format -- this must be an invalid frame
                    imageFrame_ = nullptr;
                    return;
                }

                astra_imageframe_get_frameindex(imageFrame_, &frameIndex_);

                void* voidData = nullptr;
                astra_imageframe_get_data_ptr(imageFrame_, &voidData, &byteLength_);
                dataPtr_ = static_cast<TDataType*>(voidData);
            }
        }

        /*! 
        \brief get is vaild
        
        \return is vaild       
        */
        const bool is_valid() const { return imageFrame_ != nullptr; }

        /*! 
        \brief get width
        
        \return width
        */
        const int width() const { throw_if_invalid_frame(); return imageFrame_->metadata.width; }
        
        /*! 
        \brief get height
        
        \return height
        */
        const int height() const { throw_if_invalid_frame(); return imageFrame_->metadata.height; }

        /*! 
        \brief get bytes per pixel
        
        \return bytes per pixel
        */
        const std::uint8_t bytes_per_pixel() const
        {
            throw_if_invalid_frame();

            std::uint8_t bpp;
            astra_pixelformat_get_bytes_per_pixel(imageFrame_->metadata.pixelFormat, &bpp);
            return bpp;
        }

        /*! 
        \brief get frame index
        
        \return frame index
        */
        const astra_frame_index_t frame_index() const { throw_if_invalid_frame(); return frameIndex_; }
        
        /*! 
        \brief get handle
        
        \return handle
        */
        const astra_imageframe_t handle() const { return imageFrame_; }

        /*! 
        \brief get stream type
        
        \return stream type
        */
        static astra_stream_type_t stream_type() { return TStreamType; }

        /*! 
        \brief get data pointer
        
        \return data pointer
        */
        const TDataType* data() const { throw_if_invalid_frame(); return dataPtr_; }
        
        /*! 
        \brief get byte length
        
        \return byte length
        */
        const size_t byte_length() const { throw_if_invalid_frame(); return byteLength_; }
        
        /*! 
        \brief get length
        
        \return length
        */
        const size_t length() const { throw_if_invalid_frame(); return imageFrame_->metadata.width * imageFrame_->metadata.height; }

        /*! 
        \brief copy to buffer
        
        \param[in/out] buffer
        */
        void copy_to(TDataType* buffer) const
        {
            throw_if_invalid_frame();
            astra_imageframe_copy_data(imageFrame_, buffer);
        }

        /*! 
        \brief acquire frame
        
        \return a frame
        */
        template<typename TFrameType>
        static TFrameType acquire(astra_reader_frame_t readerFrame,
                                  astra_stream_subtype_t subtype)
        {
            if (readerFrame != nullptr)
            {
                astra_imageframe_t imageFrame;
                astra_reader_get_imageframe(readerFrame, TStreamType, subtype, &imageFrame);

                return TFrameType(imageFrame);
            }

            return TFrameType(nullptr);
        }


        /**
         * rotate image frame, such as depth, color, masked color
         * @param angle the angle of clockwise direction rotation, can be 90 and 270.
         */
		void rotate(int angle)
		{
			astra_imageframe_rotate(imageFrame_, angle);
		}

    private:
        void throw_if_invalid_frame() const
        {
            if (!imageFrame_) { throw std::logic_error("Cannot operate on an invalid frame"); }
        }

        astra_imageframe_t imageFrame_{nullptr};       
        astra_frame_index_t frameIndex_;

        TDataType* dataPtr_;
        std::uint32_t byteLength_;
    };
    /** @} */
}

#endif // ASTRA_IMAGE_HPP
