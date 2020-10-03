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
#ifndef ASTRA_DEVICECONTROLLER_HPP
#define ASTRA_DEVICECONTROLLER_HPP

#include <string>
#include <astra_core/astra_core.hpp>
#include "astra/capi/astra_device_control.h"
#include <stdexcept>


namespace astra {
    /*!
    \ingroup cpp_ref
    \brief Device Controller Class

    \details get information from device or set states of device.
             before you use this, check if the StreamSet is available.
    */
    class DeviceController
    {
    public:
        DeviceController(StreamSet& set): set_(set){}

        void set_ir_gain_value(int32_t value)
        {
            astra_set_ir_gain_value(set_.get_handle(), value);
        }

        int32_t get_ir_gain_value()
        {
            int32_t value;
            astra_get_ir_gain_value(set_.get_handle(), &value);
            return value;
        }

        void set_ir_exposure_value(int32_t value)
        {
            astra_set_ir_exposure_value(set_.get_handle(), value);
        }

        int32_t get_ir_exposure_value()
        {
            int32_t value;
            astra_get_ir_exposure_value(set_.get_handle(), &value);
            return value;
        }

        void enable_ldp(bool enable)
        {
            astra_ldp_enable(set_.get_handle(), enable);
        }

        void enable_laser(bool enable)
        {
            astra_laser_enable(set_.get_handle(), enable);
        }

        /**
        * set distortion
        * @param status the value can be 0, 1 or 2.
        */
        void enable_distortion(int status)
        {
            astra_distortion_enable(set_.get_handle(), status);
        }

        void get_orbbec_camera_params(orbbec_camera_params& params)
        {
            astra_get_orbbec_camera_params(set_.get_handle(), &params);
        }
        
    private:
        StreamSet set_;
    };
}
#endif //ASTRA_DEVICECONTROLLER_HPP