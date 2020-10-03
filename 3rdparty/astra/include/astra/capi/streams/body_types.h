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
#ifndef BODY_TYPES_H
#define BODY_TYPES_H

#include <astra_core/capi/astra_types.h>
#include <astra/capi/astra_ctypes.h>

/*!
  \brief Maximum number of joints permitted
  \ingroup CTypes
*/
#define ASTRA_MAX_JOINTS 19

#define ASTRA_INVALID_BODY_ID 0
#define ASTRA_MIN_BODY_ID 1
#define ASTRA_MAX_BODY_ID 255
#define ASTRA_MAX_BODIES 6

#define ASTRA_TEMP_IMAGE_WIDTH 640
#define ASTRA_TEMP_IMAGE_HEIGHT 480
#define ASTRA_TEMP_IMAGE_LENGTH ASTRA_TEMP_IMAGE_WIDTH*ASTRA_TEMP_IMAGE_HEIGHT

/*!
  \ingroup CTypes
  \brief Joint type enumeration
*/
typedef enum _astra_joint_type {
    /*! \brief Head */
    ASTRA_JOINT_HEAD              = 0,
    /*! \brief Shoulder spine */
    ASTRA_JOINT_SHOULDER_SPINE    = 1,
    /*! \brief Left Shoulder */
    ASTRA_JOINT_LEFT_SHOULDER     = 2,
    /*! \brief Left Elbow */
    ASTRA_JOINT_LEFT_ELBOW        = 3,
    /*! \brief Left Hand */
    ASTRA_JOINT_LEFT_HAND         = 4,
    /*! \brief Right Shoulder */
    ASTRA_JOINT_RIGHT_SHOULDER    = 5,
    /*! \brief Right Elbow */
    ASTRA_JOINT_RIGHT_ELBOW       = 6,
    /*! \brief Right Hand */
    ASTRA_JOINT_RIGHT_HAND        = 7,
    /*! \brief Mid spine */
    ASTRA_JOINT_MID_SPINE         = 8,
    /*! \brief Base spine */
    ASTRA_JOINT_BASE_SPINE        = 9,
    /*! \brief Left Hip */
    ASTRA_JOINT_LEFT_HIP          = 10,
    /*! \brief Left Knee */
    ASTRA_JOINT_LEFT_KNEE         = 11,
    /*! \brief Left Foot */
    ASTRA_JOINT_LEFT_FOOT         = 12,
    /*! \brief Right Hip */
    ASTRA_JOINT_RIGHT_HIP         = 13,
    /*! \brief Rigth Knee */
    ASTRA_JOINT_RIGHT_KNEE        = 14,
    /*! \brief Right Foot */
    ASTRA_JOINT_RIGHT_FOOT        = 15,
    /*! \brief Left Wrist */
    ASTRA_JOINT_LEFT_WRIST        = 16,
    /*! \brief Right Wrist */
    ASTRA_JOINT_RIGHT_WRIST       = 17,
    /*! \brief Neck */
    ASTRA_JOINT_NECK              = 18,
    /*! \brief Unknown */
    ASTRA_JOINT_UNKNOWN           = 255,
} astra_joint_type_v;

/*!
  \ingroup CTypes
  \brief Joint type value

  Values coincide with enum \ref astra_joint_type_v
  \see astra_joint_type_v for possible values
*/
typedef uint8_t astra_joint_type_t;

/*!
  \ingroup CTypes
  \brief Joint status enumeration
*/
typedef enum _astra_joint_status {
    /*! \brief Joint not currently tracked */
    ASTRA_JOINT_STATUS_NOT_TRACKED    = 0,
    /*!
      \brief Joint is currently tracked
      with low confidence possibly due to an occlusion
    */
    ASTRA_JOINT_STATUS_LOW_CONFIDENCE = 1,
    /*! \brief Joint is currently tracked */
    ASTRA_JOINT_STATUS_TRACKED        = 2,
} astra_joint_status_v;

/*!
  \ingroup CTypes
  \brief Joint status type value

  Values coincide with \ref astra_joint_status_v
  \see astra_joint_status_v for possible values
*/
typedef uint8_t astra_joint_status_t;

/*!
  \ingroup CTypes
  \brief Joint information
*/
typedef struct _astra_joint {
    /*!
      \brief Joint type
      \see astra_joint_type_v for potential values
    */
    astra_joint_type_t type;
    /*!
      \brief Joint status
      \see astra_joint_status_v for potential values
    */
    astra_joint_status_t status;
    /*! \brief Depth ("projective") position of joint */
    astra_vector2f_t depthPosition;
    /*! \brief Real world position of joint */
    astra_vector3f_t worldPosition;
    /*! \brief 3x3 Rotation matrix representing the rotation of this joint.*/
    // TODO: is this rotation relative to the parent? is Y up?
    astra_matrix3x3_t orientation;
} astra_joint_t;

/*!
  \ingroup CTypes
  \brief Body tracking status enum
*/
typedef enum _astra_body_status {
    /*! Body is not currently tracked */
    ASTRA_BODY_STATUS_NOT_TRACKING = 0,
    /*! Tracking of body was lost */
    ASTRA_BODY_STATUS_LOST = 1,
    /*! Tracking of body has begun */
    ASTRA_BODY_STATUS_TRACKING_STARTED = 2,
    /*! Body is currently being tracked */
    ASTRA_BODY_STATUS_TRACKING = 3,
} astra_body_status_v;

/*!
  \ingroup CTypes
  \brief Body status
  Values coincide with enum \ref astra_body_status_v

  \see astra_body_status_v for possible values
*/
typedef uint8_t astra_body_status_t;

/*!
  \ingroup CTypes
  \brief Hand pose enum.
    Enumeration of the hand poses that can be detected.
*/
typedef enum _astra_handpose {
    /*! Hand pose is not known or unrecognized */
    ASTRA_HANDPOSE_UNKNOWN = 0,
    /*! Grip pose */
    ASTRA_HANDPOSE_GRIP = 1
} astra_handpose_v;

/*!
  \ingroup CTypes
  \brief Represents the currently detected hand pose

  \see astra_handpose_v for possible values
*/
typedef uint8_t astra_handpose_t;

typedef struct _astra_handpose_info {
    astra_handpose_t leftHand;
    astra_handpose_t rightHand;
} astra_handpose_info_t;

/*!
  \ingroup CTypes
  \brief Bitmask of body features
    Represents the possible features that body tracking can produce
    on a body. This is a bitmask so multiple features can be combined.
*/
typedef enum _astra_body_features {
    /*! No features beyond minimal body mask segmentation */
    ASTRA_BODY_TRACKING_SEGMENTATION = 0,
    /*! Tracking of joints */
    ASTRA_BODY_TRACKING_JOINTS = 1,
    /*! Recognition of hand poses */
    ASTRA_BODY_TRACKING_HAND_POSES = 3
} astra_body_tracking_feature_flags_v;

/*!
  \ingroup CTypes
  \brief Represents a bitmask of body features

  \see astra_body_tracking_feature_flags_v for possible values
*/
typedef uint32_t astra_body_tracking_feature_flags_t;

/*!
  \ingroup CTypes
  \brief Skeleton profile representing the set of joints to be tracked.
*/
typedef enum _astra_skeleton_profile {
    /*! All supported joints */
    ASTRA_SKELETON_PROFILE_FULL = 0,
    /*! Upper body only */
    ASTRA_SKELETON_PROFILE_UPPER_BODY = 1,
    /*! Only four basic joints: Head, MidSpine, LeftHand, RightHand */
    ASTRA_SKELETON_PROFILE_BASIC = 2
} astra_skeleton_profile_v;

/*!
  \ingroup CTypes
  \brief Skeleton profile representing the set of joints to be tracked.

  \see astra_skeleton_profile_v for possible values;
*/
typedef uint32_t astra_skeleton_profile_t;

/*!
  \ingroup CTypes
  \brief Represents the body tracking configuration that trades-off
  tracking accuracy, memory, and CPU usage.
*/
typedef enum _astra_skeleton_optimization {
    ASTRA_SKELETON_OPTIMIZATION_1 = 1,
    /*! Configuration that minimizes memory usage at a cost of lower tracking accuracy */
    ASTRA_SKELETON_OPTIMIZATION_MINIMIZE_MEMORY = 2,
    ASTRA_SKELETON_OPTIMIZATION_2 = 2,
    ASTRA_SKELETON_OPTIMIZATION_3 = 3,
    ASTRA_SKELETON_OPTIMIZATION_4 = 4,
    /*! Configuration that balances accuracy with lower memory and CPU usage */
    ASTRA_SKELETON_OPTIMIZATION_BALANCED = 5,
    ASTRA_SKELETON_OPTIMIZATION_5 = 5,
    ASTRA_SKELETON_OPTIMIZATION_6 = 6,
    ASTRA_SKELETON_OPTIMIZATION_7 = 7,
    ASTRA_SKELETON_OPTIMIZATION_8 = 8,
    ASTRA_SKELETON_OPTIMIZATION_9 = 9,
    /*! Configuration that produces the best tracking accuracy */
    ASTRA_SKELETON_OPTIMIZATION_BEST_ACCURACY = 9,
} astra_skeleton_optimization_v;


/*!
  \ingroup CTypes
  \brief Represents the body tracking configuration that trades-off
  tracking accuracy, memory, and CPU usage.

  \see astra_skeleton_optimization_v for possible values;
*/
typedef uint32_t astra_skeleton_optimization_t;

typedef enum _astra_body_orientation {
    ASTRA_BODY_ORIENTATION_TOP = 0,
    ASTRA_BODY_ORIENTATION_LEFT = 1,
    ASTRA_BODY_ORIENTATION_RIGHT = 2,
} astra_body_orientation_v;

/*!
  \ingroup CTypes
  \brief the orientation of people's heads in depth image.

  \see astra_body_orientation_v for possible values;
*/
typedef uint32_t astra_body_orientation_t;

/*!
  \ingroup CTypes
  \brief Body identifier
*/
typedef uint8_t astra_body_id_t;

/*!
  \ingroup CTypes
  \brief Struct containing body tracking information
*/
typedef struct _astra_body {
    /*! \brief Bitmask of features that are enabled.

      \see astra_body_tracking_feature_flags_v for possible values
    */
    astra_body_tracking_feature_flags_t features;
    /*! \brief Single point describing the center of mass of a body.

      Always present, even if \ref ASTRA_BODY_TRACKING_JOINTS is not enabled.
      Useful for doing general calculations about the relative positions of bodies.
    */
    astra_vector3f_t centerOfMass;
    /*! \brief Array of tracked joints */
    astra_joint_t joints[ASTRA_MAX_JOINTS];
    /*! \brief Hand poses */
    astra_handpose_info_t handPoses;
    /*! \brief Persistent Id

      An astra_body_id_t value can be used to match a particular
      active astra_body_t across frames. Additionally, \ref astra_body_id_t
      values match the values in a \ref astra_bodymask_t
    */
    astra_body_id_t id;
    /*!
      \brief Tracking status

      \see astra_body_status_v for possible values
    */
    astra_body_status_t status;
} astra_body_t;

/*!
  \ingroup CTypes
  \brief Struct containing a variable-sized
  array of \ref astra_body_t structs
*/
typedef struct _astra_body_list {
    /*! \brief Pointer to an array of \ref astra_body_t */
    // astra_body_t* bodies;
    astra_body_t bodies[ASTRA_MAX_BODIES];
    /*! \brief Number of astra_body_t in bodies */
    int32_t count;
} astra_body_list_t;

/*!
  \ingroup CTypes
  \brief Struct representing a 2-dimensional bitmask

  A mask pixel is a uint8_t. All non-zero values are considered
  to be part of the mask.
*/
typedef struct _astra_bitmapmask {
    /*! \brief mask pixels */
    // uint8_t* data;
    uint8_t data[ASTRA_TEMP_IMAGE_LENGTH];
    /*! \brief width in pixels */
    int32_t width;
    /*! \brief height in pixels */
    int32_t height;
} astra_bitmapmask_t;

/*!
  \ingroup CTypes
  \brief Represents a 2-dimensional bitmask of bodies

  Non-zero values map to the \ref astra_body_id_t of a astra_body_t
  \see astra_body_t for more info on a body's id
  \see astra_bitmapmask_t for available struct fields
*/
typedef astra_bitmapmask_t astra_bodymask_t;
/*!
  \ingroup CTypes
  \brief Represents a 2-dimensional bitmask of floor pixels

  Non-zero values are considered to belong to the floor
  \see astra_bitmapmask_t for available struct fields
*/
typedef astra_bitmapmask_t astra_floormask_t;

/*!
  \ingroup CTypes
  \brief Struct representing a geometric 3-dimensional plane

  The normal of the plane is defined to be (A, B, C). The plane coefficients and real world
  coordinates (x, y, and z) are related by the plane equation:

  Ax + By + Cz + D = 0

  \remark The vector v = (A, B, C) represents the normal to the plane and
  D represents the signed distance along the normal between the plane and the origin
  of the coordinate system. The the origin of the coordinate system is the camera's
  depth sensor
*/
typedef struct _astra_plane {
    /*! \brief A coefficient */
    float a;
    /*! \brief B coefficient */
    float b;
    /*! \brief C coefficient */
    float c;
    /*! \brief D coefficient */
    float d;
} astra_plane_t;

/*!
  \ingroup CTypes
  \brief Struct containing general body frame information
*/
typedef struct _astra_bodyframe_info {
    /*! \brief Frame width */
    int32_t width;
    /*! \brief Frame height */
    int32_t height;
    /*! \brief If the frame was estimated due to a slow CPU */
    int8_t isEstimated;
} astra_bodyframe_info_t;

/*!
  \ingroup CTypes
  \brief Struct containing floor information about the scene
*/
typedef struct _astra_floor_info {
    /*! \brief Floor mask */
    astra_floormask_t floorMask;
    /*! \brief Floor plane */
    astra_plane_t floorPlane;
    /*! \brief If the floor is detected, ASTRA_TRUE. Otherwise, ASTRA_FALSE.

      If a floor is not detected, floorPlane and floorMask will not contain
      meaningful data.
     */
    astra_bool_t floorDetected;
} astra_floor_info_t;

typedef struct _astra_bodyframe* astra_bodyframe_t;
typedef astra_streamconnection_t astra_bodystream_t;

typedef struct {
    astra_body_id_t bodyId;
    astra_body_tracking_feature_flags_t feature;
} astra_body_feature_command_t;

#endif /* BODY_TYPES_H */
