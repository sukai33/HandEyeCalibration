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
#ifndef ASTRA_HAND_HPP
#define ASTRA_HAND_HPP

#include <stdexcept>
#include <cstdint>
#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/hand_capi.h>
#include <astra/Vector.hpp>

namespace astra {

    /*!
      \defgroup cpp_hand_api_ref hand stream apis
      \ingroup cpp_high_api_ref
      @{
     */

    /*!
      \brief Hand Point struct

      \details Hand Point struct
     */
    class HandPoint : public astra_handpoint_t
    {
    public:
        /*! 
        \brief constructs
        
        \param[in] tracking id
        \param[in] status
        \param[in] depth position
        \param[in] world position
        \param[in] world delta position
        */
        HandPoint(std::int32_t trackingId,
                  astra_handstatus_t status,
                  Vector2i depthPosition,
                  Vector3f worldPosition,
                  Vector3f worldDeltaPosition)
        {
            astra_handpoint_t::trackingId = trackingId;
            astra_handpoint_t::status = status;
            astra_handpoint_t::depthPosition = depthPosition;
            astra_handpoint_t::worldPosition = worldPosition;
            astra_handpoint_t::worldDeltaPosition = worldDeltaPosition;
        }

        /*! 
        \brief constructs
        
        \param[in] handPoint
        */
        HandPoint(const astra_handpoint_t& handPoint)
        {
            *this = handPoint;
        }

        /*! 
        \brief copy constructs
        
        \param[in] handPoint
        */
        HandPoint& operator=(const ::astra_handpoint_t& handPoint)
        {
            astra_handpoint_t::trackingId = handPoint.trackingId;
            astra_handpoint_t::status = handPoint.status;
            astra_handpoint_t::depthPosition = handPoint.depthPosition;
            astra_handpoint_t::worldPosition = handPoint.worldPosition;
            astra_handpoint_t::worldDeltaPosition = handPoint.worldDeltaPosition;

            return *this;
        }

        /*! 
        \brief get astra_handpoint_t point
        
        \return astra_handpoint_t point
        */
        inline operator ::astra_handpoint_t*() { return this; }
        
        /*! 
        \brief get astra_handpoint_t point
        
        \return const astra_handpoint_t point
        */
        inline operator const ::astra_handpoint_t*() const { return this; }

        /*! 
        \brief get tracking id
        
        \return tracking_id
        */
        inline std::int32_t tracking_id() const { return astra_handpoint_t::trackingId; }
        
        /*! 
        \brief get status
        
        \return status
        */
        inline astra_handstatus_t status() const { return astra_handpoint_t::status; }
        
        /*! 
        \brief get depth position
        
        \return depth position
        */
        inline Vector2i depth_position() const { return astra_handpoint_t::depthPosition; }
        
        /*! 
        \brief get world position
        
        \return world position
        */
        inline Vector3f world_position() const { return astra_handpoint_t::worldPosition; }
        
        /*! 
        \brief get world delta position
        
        \return world delta position
        */
        inline Vector3f world_delta_position() const { return astra_handpoint_t::worldDeltaPosition; }

    private:
        astra_handpoint_t handPoint_;
        Vector2i depthPosition_;
        Vector3f worldPosition_;
        Vector3f worldDeltaPosition_;
    };

    /*!
      \brief A Hand Stream

      \details A Hand Stream
     */
    class HandStream : public DataStream
    {
    public:
        /*! 
        \brief constructs
        
        \param[in] stream connection
        */
        explicit HandStream(astra_streamconnection_t connection)
            : DataStream(connection),
              handStream_(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_HAND;

        /*! 
        \brief get is include candidate points
        
        \return is include candidate points
        */
        bool get_include_candidate_points() const
        {
            bool includeCandidatePoints;
            astra_handstream_get_include_candidate_points(handStream_, &includeCandidatePoints);
            return includeCandidatePoints;
        }

        /*! 
        \brief set is include candidate points
        
        \param[in] is include candidate points
        */
        void set_include_candidate_points(bool includeCandidatePoints)
        {
            astra_handstream_set_include_candidate_points(handStream_, includeCandidatePoints);
        }
    private:
        astra_handstream_t handStream_;
    };

    /*!
      \brief A Hand Data Frame

      \details A Hand Data Frame
     */
    class HandFrame
    {
    public:
        using HandPointList = std::vector<HandPoint>;

        /*! 
        \brief set is include candidate points
        
        \param[in] is include candidate points
        */
        template<typename TFrameType>
        static TFrameType acquire(astra_reader_frame_t readerFrame,
                                  astra_stream_subtype_t subtype)
        {
            if (readerFrame != nullptr)
            {
                astra_handframe_t handFrame;
                astra_frame_get_handframe_with_subtype(readerFrame, subtype, &handFrame);
                return TFrameType(handFrame);
            }

            return TFrameType(nullptr);
        }

        /*! 
        \brief constructs
        
        \param[in] handFrame
        */
        HandFrame(astra_handframe_t handFrame)
        {
            handFrame_ = handFrame;
            if (handFrame_)
            {
                astra_handframe_get_frameindex(handFrame_, &frameIndex_);

                std::uint32_t maxHandCount;
                astra_handframe_get_hand_count(handFrame_, &maxHandCount);

                handPoints_.reserve(maxHandCount);
            }
        }

        /*! 
        \brief get is valid
        
        \return is valid
        */
        bool is_valid() const { return handFrame_ != nullptr; }
        
        /*! 
        \brief get handle
        
        \return handle
        */
        astra_handframe_t handle() const { return handFrame_; }

        /*! 
        \brief get hand Points count
        
        \return hand Points count
        */
        size_t handpoint_count() const
        {
            throw_if_invalid_frame();
            verify_handpoints();

            return handPoints_.size();
        }

        /*! 
        \brief get hand Points
        
        \return hand Points
        */
        const HandPointList& handpoints() const
        {
            throw_if_invalid_frame();
            verify_handpoints();
            return handPoints_;
        }

        /*! 
        \brief get frame index
        
        \return frame index
        */
        astra_frame_index_t frame_index() const
        {
            throw_if_invalid_frame();
            return frameIndex_;
        }

    private:
        void throw_if_invalid_frame() const
        {
            if (!handFrame_) { throw std::logic_error("Cannot operate on an invalid frame"); }
        }

        void verify_handpoints() const
        {
            if (handPointsInitialized_) { return; }
            handPointsInitialized_ = true;

            astra_handpoint_t* handPtr;
            std::uint32_t maxHandCount;

            astra_handframe_get_shared_hand_array(handFrame_, &handPtr, &maxHandCount);

            for (size_t i = 0; i < maxHandCount; ++i, ++handPtr)
            {
                astra_handpoint_t& p = *handPtr;
                if (p.status != astra_handstatus_t::HAND_STATUS_NOTTRACKING)
                {
                    handPoints_.emplace_back(HandPoint(p));
                }
            }
        }

        // mutable for purposes of lazy computation
        mutable bool handPointsInitialized_{false};
        mutable HandPointList handPoints_;

        astra_handframe_t handFrame_{nullptr};
        astra_frame_index_t frameIndex_;
    };
    /** @} */
}

#endif /* ASTRA_HAND_HPP */
