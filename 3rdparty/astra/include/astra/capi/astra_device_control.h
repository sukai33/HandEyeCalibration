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
#ifndef _ASTRA_DEIVCE_CONTROL_H_
#define _ASTRA_DEIVCE_CONTROL_H_

#include <astra_core/capi/astra_defines.h>
#include <astra_core/capi/astra_types.h>
#include <stdbool.h>

ASTRA_BEGIN_DECLS

typedef struct {    
    const char *uri;
    const char *command;
    char *out;
    int32_t outLength;
    astra_status_t result;
} astra_device_command_t;

typedef struct
{
    float l_intr_p[4];//[fx,fy,cx,cy]
    float r_intr_p[4];//[fx,fy,cx,cy]
    float r2l_r[9];//[r00,r01,r02;r10,r11,r12;r20,r21,r22]
    float r2l_t[3];//[t1,t2,t3]
    float l_k[5];//[k1,k2,p1,p2,k3]
    float r_k[5];
} orbbec_camera_params;

/**
 * \defgroup dev_ctrl_ref device control apis
 * \details get information from device or set states of device.
 *          before you use this, check if the StreamSet is available.
 * \ingroup c_ref
 * @{
 */

/**
 * set distortion 
 * @param status the value can be 0, 1 or 2.
 */
ASTRA_API_EX astra_status_t astra_distortion_enable(astra_streamsetconnection_t connect, int32_t status);
ASTRA_API_EX astra_status_t astra_set_ir_gain_value(astra_streamsetconnection_t connect, int32_t value);
ASTRA_API_EX astra_status_t astra_set_ir_exposure_value(astra_streamsetconnection_t connect, int32_t value);
ASTRA_API_EX astra_status_t astra_ldp_enable(astra_streamsetconnection_t connect, bool enable);
ASTRA_API_EX astra_status_t astra_laser_enable(astra_streamsetconnection_t connect, bool enable);

ASTRA_API_EX astra_status_t astra_get_orbbec_camera_params(astra_streamsetconnection_t connect, orbbec_camera_params* params);
ASTRA_API_EX astra_status_t astra_get_ir_gain_value(astra_streamsetconnection_t connect, int32_t* value);
ASTRA_API_EX astra_status_t astra_get_ir_exposure_value(astra_streamsetconnection_t connect, int32_t* value);
/** @} */

ASTRA_END_DECLS

#endif