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
#ifndef ASTRA_BODY_HPP
#define ASTRA_BODY_HPP

#include <stdexcept>
#include <cstdint>
#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/body_capi.h>
#include <astra/capi/streams/stream_types.h>
#include <astra/Array.hpp>
#include <astra/Vector.hpp>
#include <astra/Matrix3x3.hpp>

namespace astra {

    using std::uint8_t;
    using std::uint16_t;
    using std::int16_t;
    using std::int32_t;
    using std::uint64_t;

    /*!
      \defgroup cpp_body_api_ref body stream apis
      \ingroup cpp_high_api_ref
      @{
     */

    /*!
      \brief Bitmap representing a 2d mask

      Encapsulates a 2-dimensional bitmask. A non-zero pixel value is considered part
      of the mask.
     */
    class BitmapMask : private ::astra_bitmapmask_t
    {
    public:
        /*! \brief Default constructs an empty zero-sized BitmapMask */
        BitmapMask()
        {
            // ::astra_bitmapmask_t::data = nullptr;
            ::astra_bitmapmask_t::width = 0;
            ::astra_bitmapmask_t::height = 0;
        }

        /*! \brief Gets the width of the mask */
        int32_t width() const { return ::astra_bitmapmask_t::width; }
        /*! \brief Gets the height of the mask */
        int32_t height() const { return ::astra_bitmapmask_t::height; }
        /*! \brief Gets the bytes per pixel */
        int32_t bpp() const { return sizeof(uint8_t); }
        /*! \brief Gets the length of the mask in pixels */
        int32_t length() const
        {
            return ::astra_bitmapmask_t::width *
                   ::astra_bitmapmask_t::height;
        }

        /*! \brief Gets the length of the mask in bytes */
        int32_t byte_length() const
        {
            return ::astra_bitmapmask_t::width *
                   ::astra_bitmapmask_t::height *
                   bpp();
        }

        /*! \brief Gets an immutable raw pointer to mask data */
        const uint8_t* data() const { return ::astra_bitmapmask_t::data; }

        friend class FloorInfo;
        friend class BodyFrame;
    };

    /*! 
      \brief Mask representing pixels that have been
      identified as belonging to tracked bodies 
    */
    using BodyMask = BitmapMask;
    /*! 
      \brief Mask representing pixels that have been
      identified as belonging to the floor plane 
    */
    using FloorMask = BitmapMask;

    /*!
      \brief Bitmask of body features
        Represents the possible features that body tracking can produce
        on a body. This is a bitmask so multiple features can be combined.
    */
    enum class BodyTrackingFeatureFlags : ::astra_body_tracking_feature_flags_t
    {
        /*! No features beyond minimal body mask segmentation */
        Segmentation = 0,
        /*! Tracking of joints */
        Joints = 1,
        /*! Recognition of hand poses */
        HandPoses = 3
    };

    /*!
      \brief Skeleton profile representing the set of joints to be tracked.
    */
    enum class SkeletonProfile : ::astra_skeleton_profile_t {
        /*! All supported joints */
        Full = 0,
        /*! Upper body only */
        UpperBody = 1,
        /*! Only four basic joints: Head, MidSpine, LeftHand, RightHand */
        Basic = 2
    };

    /*!
      \brief Represents the body tracking configuration that trades-off
      tracking accuracy, memory, and CPU usage.
    */
    enum class SkeletonOptimization : ::astra_skeleton_optimization_t {
        Optimization1 = 1,
        /*! Configuration that minimizes memory usage at a cost of lower tracking accuracy */
        MinimizeMemory = 2,
        Optimization2 = 2,
        Optimization3 = 3,
        Optimization4 = 4,
        /*! Configuration that balances accuracy with lower memory and CPU usage */
        Balanced = 5,
        Optimization5 = 5,
        Optimization6 = 6,
        Optimization7 = 7,
        Optimization8 = 8,
        Optimization9 = 9,
        /*! Configuration that produces the best tracking accuracy */
        BestAccuracy = 9,
    };

    /*!
      \brief the orientation of people's heads in depth image.
    */
    enum class BodyOrientation : ::astra_body_orientation_t {
        TOP = 0,
        LEFT = 1,
        RIGHT = 2
    };

    /*!
      \brief Joint status enumeration
    */
    enum class JointStatus : ::astra_joint_status_t
    {
        /*! Joint not currently tracked */
        NotTracked = 0,
        /*!
          Joint is currently tracked with low confidence
          possibly due to occlusion
        */
        LowConfidence = 1,
        /*! Joint is currently tracked */
        Tracked = 2
    };

    /*!
      \brief Joint type enumeration
    */
    enum class JointType : ::astra_joint_type_t
    {
        Head            = 0, /*!< Head */
        ShoulderSpine   = 1, /*!< Shoulder spine */
        LeftShoulder    = 2, /*!< Left Shoulder */
        LeftElbow       = 3, /*!< Left Elbow */
        LeftHand        = 4, /*!< Left hand */
        RightShoulder   = 5, /*!< Right Shoulder */
        RightElbow      = 6, /*!< Right Elbow */
        RightHand       = 7, /*!< Right Hand */
        MidSpine        = 8, /*!< Mid spine */
        BaseSpine       = 9, /*!< Base spine */
        LeftHip         = 10, /*!< Left Hip */
        LeftKnee        = 11, /*!< Left Knee */
        LeftFoot        = 12, /*!< Left Foot */
        RightHip        = 13, /*!< Right Hip */
        RightKnee       = 14, /*!< Right Knee */
        RightFoot       = 15, /*!< Right Foot */
        LeftWrist       = 16, /*!< Left Wrist */
        RightWrist      = 17, /*!< Right Wrist */
        Neck            = 18, /*!< Neck */
        Unknown         = 255, /*!< Unknown */
    };

    /*!
      \brief %Body joint

      Encapsulates information about a particular joint.
      Joint positions are provided in both projective and world coordinates.

      \see JointType for the possible tracked joints
      \see JointStatus for the possible states of joint tracking
    */
    class Joint : private ::astra_joint_t
    {
    public:
        /*! \brief Gets the type of joint */
        JointType type() const
        {
            return static_cast<JointType>(::astra_joint_t::type);
        }

        /*! \brief Gets the current status of the \ref Joint */
        JointStatus status() const
        {
            return static_cast<JointStatus>(::astra_joint_t::status);
        }

        /*!
          \brief Gets the depth ("projective") position of the Joint

          The position reported is given with respect to \ref BodyFrame::width
          and \ref BodyFrame::height, which are the same dimensions as those of the
          input DepthMap
         */
        const Vector2f& depth_position() const
        {
            return *static_cast<const Vector2f*>(&(::astra_joint_t::depthPosition));
        }

        /*! \brief Gets the real world position of the Joint */
        const Vector3f& world_position() const
        {
            return *static_cast<const Vector3f*>(&(::astra_joint_t::worldPosition));
        }

        /*! \brief Gets the 3x3 Rotation matrix representing the rotation of this joint.*/
        const Matrix3x3& orientation() const
        {
            return *static_cast<const Matrix3x3*>(&(::astra_joint_t::orientation));
        }

        friend class Body;
    };

    /*!
      \brief Hand pose enum.
      Enumeration of the hand poses that can be detected.
    */
    enum class HandPose : ::astra_handpose_t
    {
        /*! Hand pose is not known or unrecognized */
        Unknown = 0,
        /*! Grip pose */
        Grip = 1,
    };

    class HandPoseInfo : private ::astra_handpose_info_t
    {
    private:
        using ::astra_handpose_info_t::leftHand;
        using ::astra_handpose_info_t::rightHand;
    public:
        HandPose left_hand()  const { return static_cast<HandPose>(this->leftHand); }
        HandPose right_hand() const { return static_cast<HandPose>(this->rightHand); }

        friend class Body;
    };

    /*!
      \brief Enumeration of possible tracking status of a \ref orbbec::bodytracking::Body
    */
    enum class BodyStatus : ::astra_body_status_t
    {
        /*! Body is not currently tracked */
        NotTracking = 0,
        /*! Tracking of Body was lost */
        TrackingLost = 1,
        /*! Tracking of Body has begun */
        TrackingStarted = 2,
        /*! Body is currently being tracked */
        Tracking = 3,
    };

    /*!
      \brief Type alias for an immutable Array of \link Joint Joints\endlink
     */
    using JointList = Array<const Joint>;

    /*! 
     \brief Identifier type for bodies
     */
    using BodyId = astra_body_id_t;

    /*!
      \brief Human body

      Provides info about a human body tracked by the BodyTracker.
      Joints positions are provided in both projective and world coordinates.

      \see BodyTracker for information how to generate this data
      \see Joint for information related to individual joints
      \see BodyStatus for possible tracking statuses of a Body
    */
    class Body : private ::astra_body_t
    {
    public:
        /*!
          \brief Gets BodyId associated with the Body

          BodyId can be used to match a particular active Body
          across frames. Additionally, BodyId match the
          values in a \ref BodyMask
         */
        BodyId id() const { return ::astra_body_t::id; }

        /*! \brief Gets the tracking status of the body */
        BodyStatus status() const
        {
            return static_cast<BodyStatus>(::astra_body_t::status);
        }

        /*! \brief Gets the real world center of mass estimate */
        const Vector3f& center_of_mass() const
        {
            return *static_cast<const Vector3f*>(&(::astra_body_t::centerOfMass));
        }

        bool joints_enabled() const
        {
            return (::astra_body_t::features & ASTRA_BODY_TRACKING_JOINTS) == ASTRA_BODY_TRACKING_JOINTS;
        }

        bool hand_poses_enabled() const
        {
            return (::astra_body_t::features & ASTRA_BODY_TRACKING_HAND_POSES) == ASTRA_BODY_TRACKING_HAND_POSES;
        }

        /*! \brief Gets the current list of joints (\ref Joint) being currently tracked */
        JointList joints() const
        {
            return make_array(
                static_cast<const Joint*>(&(::astra_body_t::joints[0])), ASTRA_MAX_JOINTS);
        }

        const HandPoseInfo& hand_poses() const
        {
            return *static_cast<const HandPoseInfo*>(&(::astra_body_t::handPoses));
        }

        friend class BodyFrame;
    };

    /*!
      \brief 3D geometric plane

      Represents a 3D plane.

      The normal of the plane is defined to be (A, B, C). The plane coefficients and real world
      coordinates (x, y, and z) are related by the plane equation:

      Ax + By + Cz + D = 0

      \remark The vector v = (A, B, C) represents the normal to the plane and
      D represents the signed distance along the normal between the plane and the origin
      of the coordinate system. The the origin of the coordinate system is the camera's
      depth sensor
     */
    class Plane : private ::astra_plane_t
    {
    public:
        /*! \brief Default constructs a plane that passes though origin,
          has a zero-length normal, and is considered degenerate */
        Plane()
        {
            ::astra_plane_t::a = 0.f;
            ::astra_plane_t::b = 0.f;
            ::astra_plane_t::c = 0.f;
            ::astra_plane_t::d = 0.f;
        }

        /*! \brief Gets the A coefficient */
        float a() const { return ::astra_plane_t::a; }
        /*! \brief Gets the B coefficient */
        float b() const { return ::astra_plane_t::b; }
        /*! \brief Gets the C coefficient */
        float c() const { return ::astra_plane_t::c; }
        /*! \brief Gets the D coefficent (signed distance) */
        float d() const { return ::astra_plane_t::d; }

        /*! \brief Gets the plane normal */
        const Vector3f& normal() const
        {
            // a, b, c are the normal x, y, z. Use address of 'a'
            // for transmutation of a Vector3f from thin air.
            return *reinterpret_cast<const Vector3f*>(&(::astra_plane_t::a));
        }

        /*! \brief Returns whether than plane is considered degenerate (invalid) */
        bool is_degenerate() const
        {
            return ::astra_plane_t::a == 0.f &&
                   ::astra_plane_t::b == 0.f &&
                   ::astra_plane_t::c == 0.f;
        }

        friend class FloorInfo;
    };


    class FloorInfo : private ::astra_floor_info_t
    {
    private:
        using ::astra_floor_info_t::floorMask;
        using ::astra_floor_info_t::floorPlane;
        using ::astra_floor_info_t::floorDetected;
    public:
        const FloorMask& floor_mask() const
        {
            return *static_cast<const FloorMask*>(&this->floorMask);
        }
        const Plane& floor_plane() const
        {
            return *static_cast<const Plane*>(&this->floorPlane);
        }
        bool floor_detected() const { return this->floorDetected != ASTRA_FALSE; }

        friend class BodyFrame;
    };

    class BodyFrameInfo : private ::astra_bodyframe_info_t
    {
    public:
        std::int32_t width()  const { return ::astra_bodyframe_info_t::width; }
        std::int32_t height() const { return ::astra_bodyframe_info_t::height; }
        bool is_estimated() const { return ::astra_bodyframe_info_t::isEstimated != 0; }
        friend class BodyFrame;
    };

    /*!
      \brief Type alias for an immutable Array of 
      \link Body Bodies\endlink
     */
    using BodyList = Array<const Body>;

    /*!
      \brief %Body tracking information produced by a BodyTracker instance
    */
    class BodyFrame
    {
    private:
        ::astra_bodyframe_t handle_;
        astra_frame_index_t frameIndex_;

    public:
        /*! \brief BodyFrame is not copy constructible */
        BodyFrame(const BodyFrame&) = delete;
        /*! \brief BodyFrame is not copy assignable */
        BodyFrame& operator=(const BodyFrame&) = delete;

        /*! \brief BodyFrame is move constructible */
        BodyFrame(BodyFrame&& other)
         : handle_(other.handle_),
           frameIndex_(other.frameIndex_)
        {}

        /*! \brief BodyFrame is move assignable */
        BodyFrame& operator=(BodyFrame&& other)
        {
            handle_ = other.handle_;
            frameIndex_ = other.frameIndex_;

            return *this;
        }

        template<typename TFrameType>
        static TFrameType acquire(astra_reader_frame_t readerFrame,
                                  astra_stream_subtype_t subtype)
        {
            if (readerFrame != nullptr)
            {
                astra_bodyframe_t bodyFrame;
                astra_frame_get_bodyframe(readerFrame, &bodyFrame);
                return TFrameType(bodyFrame);
            }

            return TFrameType(nullptr);
        }

        /*! 
        \brief get body frame is vaild
        
        \return body frame is vaild
        */
        bool is_valid() const { return handle_ != nullptr; }

        /*! 
        \brief get body frame index
        
        \return body frame index
        */
        astra_frame_index_t frame_index() const
        {
            throw_if_invalid_frame();
            return frameIndex_;
        }

        /*! 
        \brief get body frame info
        
        \return body frame info
        */
        const BodyFrameInfo& info() const
        {
            throw_if_invalid_frame();
            return *static_cast<const BodyFrameInfo*>(&handle_->info);
        }

        /*! \brief Gets the \ref BodyMask of the current tracked bodies */
        const BodyMask& body_mask() const
        {
            throw_if_invalid_frame();
            return *static_cast<const BodyMask*>(&handle_->bodyMask);
        }

        const FloorInfo& floor_info() const
        {
            throw_if_invalid_frame();
            return *static_cast<const FloorInfo*>(&handle_->floorInfo);
        }

        /*!
          \brief Gets the current tracked
          bodies associated with the current BodyFrame

         \see Body for body specific information
         */
        BodyList bodies() const
        {
            throw_if_invalid_frame();
            const auto& bodyList = handle_->bodyList;
            return make_array(
                static_cast<const Body*>(&bodyList.bodies[0]), bodyList.count);
        }

        /**
         * rotate body frame
         * @param angle the angle of clockwise direction rotation, can be 90 and 270.
         */
		void rotate(int angle)
		{
			throw_if_invalid_frame();
			astra_bodyframe_rotate(handle_,angle);
		}

    private:
        BodyFrame(astra_bodyframe_t handle)
            : handle_(handle)
        {
            if (handle_)
            {
                astra_bodyframe_get_frameindex(handle, &frameIndex_);
            }
        }

        void throw_if_invalid_frame() const
        {
            if (!is_valid())
            {
                throw std::logic_error("Cannot operate on an invalid frame");
            }
        }
    };

    
    /*!
      \brief A Body Data Stream

      \details A Body Data Stream.
     */
    class BodyStream : public DataStream
    {
    public:
        /*! 
        \brief default constructs
        
        \param[in] connection
        */
        explicit BodyStream(astra_streamconnection_t connection)
            : DataStream(connection),
              bodyStream_(reinterpret_cast<astra_bodystream_t>(connection))
        { }

        /*! 
        \brief get body features
        
        \return body features
        */
        BodyTrackingFeatureFlags get_body_features(astra_body_id_t id)
        {
            astra_body_tracking_feature_flags_t features = ASTRA_BODY_TRACKING_SEGMENTATION;
            astra_bodystream_get_body_features(bodyStream_, id, &features);
            return static_cast<BodyTrackingFeatureFlags>(features);
        }

        /*! 
        \brief set body features
        
        \param[in] body features
        */
        void set_body_features(astra_body_id_t id, BodyTrackingFeatureFlags features)
        {
            astra_bodystream_set_body_features(bodyStream_,
                                               id,
                                               static_cast<astra_body_tracking_feature_flags_t>(features));
        }

        /*! 
        \brief get default body features
        
        \return default body features
        */
        BodyTrackingFeatureFlags get_default_body_features()
        {
            astra_body_tracking_feature_flags_t features = ASTRA_BODY_TRACKING_SEGMENTATION;
            astra_bodystream_get_default_body_features(bodyStream_, &features);
            return static_cast<BodyTrackingFeatureFlags>(features);
        }

        /*! 
        \brief set default body features
        
        \param[in] default body features
        */
        void set_default_body_features(BodyTrackingFeatureFlags features)
        {
            astra_bodystream_set_default_body_features(bodyStream_,
                                                       static_cast<astra_body_tracking_feature_flags_t>(features));
        }

        /*! 
        \brief get skeleton profile
        
        \return skeleton profile
        */
        SkeletonProfile get_skeleton_profile()
        {
            astra_skeleton_profile_t skeletonProfileState = ASTRA_SKELETON_PROFILE_FULL;
            astra_bodystream_get_skeleton_profile(bodyStream_, &skeletonProfileState);
            return static_cast<SkeletonProfile>(skeletonProfileState);
        }

        /*! 
        \brief set skeleton profile
        
        \param[in] skeleton profile
        */
        void set_skeleton_profile(SkeletonProfile skeletonProfile)
        {
            astra_bodystream_set_skeleton_profile(bodyStream_,
                                                  static_cast<astra_skeleton_profile_t>(skeletonProfile));
        }

        /*! 
        \brief get skeleton optimization
        
        \return skeleton optimization
        */
        SkeletonOptimization get_skeleton_optimization()
        {
            astra_skeleton_optimization_t skeletonOptimization = ASTRA_SKELETON_OPTIMIZATION_BEST_ACCURACY;
            astra_bodystream_get_skeleton_optimization(bodyStream_, &skeletonOptimization);
            return static_cast<SkeletonOptimization>(skeletonOptimization);
        }

        /*! 
        \brief set skeleton optimization
        
        \param[in] skeleton optimization
        */
        void set_skeleton_optimization(SkeletonOptimization skeletonOptimization)
        {
            astra_bodystream_set_skeleton_optimization(bodyStream_,
                                                       static_cast<astra_skeleton_optimization_t>(skeletonOptimization));
        }

        /*! 
        \brief get body orientation, default value is BodyOrientation::TOP.
        
        \return body orientation
        */
        BodyOrientation get_body_orientation()
        {
            astra_body_orientation_t bodyOrientation = ASTRA_BODY_ORIENTATION_TOP;
            astra_bodystream_get_body_orientation(bodyStream_, &bodyOrientation);
            return static_cast<BodyOrientation>(bodyOrientation);
        }

        /*! 
        \brief set body orientation
        
        \param[in] body orientation
        */
        void set_body_orientation(BodyOrientation bodyOrientation)
        {
            astra_bodystream_set_body_orientation(bodyStream_,
                                                  static_cast<astra_body_orientation_t>(bodyOrientation));
        }

        static const astra_stream_type_t id = ASTRA_STREAM_BODY;

    private:
         astra_bodystream_t bodyStream_{nullptr};
    };
    /** @} */
}

#endif /* ASTRA_BODY_HPP */
