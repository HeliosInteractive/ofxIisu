/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.5
//  Date              : 2012/02/20
//  Module Name       : Easii
//  Description       : Encapsulates the data to model a hand in near mode.
//
// COPYRIGHT AND CONFIDENTIALITY NOTICE - SOFTKINETIC CONFIDENTIAL
// INFORMATION All rights reserved to SOFTKINETIC SOFTWARE SA (a
// company incorporated and existing under the laws of Belgium, with
// its principal place of business at Boulevard de la Plainelaan 15,
// 1050 Brussels (Belgium), registered with the Crossroads bank for
// enterprises under company number 0890 705 864 - "Softkinetic
// Software")
//
// The source code of the SoftKinetic iisu SDK is proprietary and
// confidential information of Softkinetic Software SA
// For any question about terms and conditions, please contact: info@softkinetic.com
// Copyright (c) 2002-2012 Softkinetic Software SA
/****************************************************************************************/

#pragma once

#include <Iisu/Devices/Device.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Foundation/DataTypes/Geometry/Vector3i.h>

namespace SK {
namespace Easii {
class HandController;

/**
 * \ingroup CI
 * \class Hand Hand.h EasiiSDK/Iisu.h
 * \brief Provides an interface to access data generated in Near Mode
 *        (CI).
 */
class Hand
{
	Hand(const Hand &);
	Hand &operator = (const Hand &);

public:

	// \cond IGNORE_DOXYGEN
	Hand();

	virtual ~Hand();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(int index, SK::Device &device);
	// \endcond

	/**
	 * \brief Returns the hand status.
	 *
	 * <table>
	 * <tr><th>Status</th><th>Description</th></tr>
	 * <tr><td>0</td><td><em>Inactive</em></td></tr>
	 * <tr><td>1</td><td><em>Detected</em> at the current
	 *                   frame</td></tr>
	 * <tr><td>2</td><td><em>Tracked</em> at the current frame and has
	 *                   temporal coherence with the same data at the
	 *                   previous frame.</td></tr>
	 * <tr><td>3</td><td><em>Extrapolated</em> Not detected at the
	 *                   current frame, but has temporal coherence
	 *                   with the same data at the  previous
	 *                   frame.</td></tr>
	 * </table>
	 *
	 * \return 0, 1, 2 or 3.
	 */
	virtual int32_t getStatus() const;

	/**
	 * \brief Checks whether this hand is part of a group of touching
	 *        hands.
	 *
	 * \return \c true if this hand is grouped, \c false otherwise.
	 */
	virtual bool isGroup() const;

	/**
	 * \brief Checks whether this hand is open.
	 *
	 * \return \c true if the hand is open, \c false otherwise.
	 */
	virtual bool isOpen() const;

	/**
	 * \brief The label in the CI.SceneLabelImage image which is
	 *        assigned to pixels belonging to this hand.
	 *
	 * \return The ID.
	 */
	virtual int32_t getLabelID() const;

	/**
	 * \brief Checks if the hand is intersecting the upper image
	 *        boundary.
	 *
	 * \return \c true if this hand intersects the upper image
	 *          boundary, \c false otherwise.
	 */
	virtual bool isIntersectingUpperImageBoundary() const;

	/**
	 * \brief Checks if the hand is intersecting the lower image
	 *        boundary.
	 *
	 * \return \c true if this hand intersects the lower image
	 *          boundary, \c false otherwise.
	 */
	virtual bool isIntersectingLowerImageBoundary() const;

	/**
	 * \brief Checks if the hand is intersecting the left image
	 *        boundary.
	 *
	 * \return \c true if this hand intersects the left image
	 *          boundary, \c false otherwise.
	 */
	virtual bool isIntersectingLeftImageBoundary() const;

	/**
	 * \brief Checks if the hand is intersecting the right image
	 *        boundary.
	 *
	 * \return \c true if this hand intersects the right image
	 *          boundary, \c false otherwise.
	 */
	virtual bool isIntersectingRightImageBoundary() const;

	/**
	 * \brief Gets the position of the center of the palm in the
	 *        coordinates of the depth map.
	 *
	 * \return The palm position in 2D coordinates.
	 */
	virtual SK::Vector2 getPalmPosition2D() const;

	/**
	 * \brief Gets the position of the center of the palm in world
	 *        coordinates.
	 *
	 * \return The palm position in 3D coordinates.
	 */
	virtual SK::Vector3 getPalmPosition3D() const;

	/**
	 * \brief Gets the position of the hand tip in the coordinates of
	 *        the depth map.
	 *
	 * \return The hand tip position in 2D coordinates.
	 */
	virtual SK::Vector2 getTipPosition2D() const;

	/**
	 * \brief Gets the position of the hand tip in world coordinates.
	 *
	 * \return The hand tip position in 3D coordinates.
	 */
	virtual SK::Vector3 getTipPosition3D() const;

	/**
	 * \brief Gets the position of the forearm in the in the
	 *        coordinates of the depth map.
	 *
	 * \return The forearm position in 2D coordinates.
	 */
	virtual SK::Vector2 getForearmPosition2D() const;

	/**
	 * \brief Gets the position of the forearm in world coordinates.
	 *
	 * \return The forearm position in 3D coordinates.
	 */
	virtual SK::Vector3 getForearmPosition3D() const;

	/**
	 * \brief Gets the normal vector of the palm.
	 *
	 * the normal vector does not necessarily points towards the
	 * interior of the hand. Iff this vector points too far backward
	 * then it is flipped in order to point towards the camera.
	 *
	 * \return The 3D normal vector of the palm.
	 */
	virtual SK::Vector3 getPalmNormal3D() const;

	/**
	 * \brief Gets the radius of the palm.
	 *
	 * \return The palm radius.
	 */
	virtual float getPalmRadius() const;

	/**
	 * \brief Gets a list of the centroid positions.
	 *
	 * \return A list of 3D vectors indicating the position of each
	 *         centroid.
	 */
	virtual const SK::Array<SK::Vector3> &getCentroids() const;

	/**
	 * \brief Gets a list of statuses indicating the temporal
	 *        coherence of each centroid.
	 *
	 * The status at each index corresponds to the centroid at the
	 * same index.
	 *
	 * \return A list of status values.
	 */
	virtual const SK::Array<int32_t> &getJumpStatuses() const;

	/**
	 * \brief Gets the number of detected fingers.
	 *
	 * \return A value between 0 and 5.
	 */
	virtual int getFingerCount() const;

	/**
	 * \brief Returns an array giving the status of each detected
	 *        finger.
	 *
	 * <table>
	 * <tr><th>Status</th><th>Description</th></tr>
	 * <tr><td>0</td><td><em>Inactive</em></td></tr>
	 * <tr><td>1</td><td><em>Detected</em> at the current
	 *                   frame</td></tr>
	 * <tr><td>2</td><td><em>Tracked</em> at the current frame and has
	 *                   temporal coherence with the same data at the
	 *                   previous frame.</td></tr>
	 * <tr><td>3</td><td><em>Extrapolated</em> Not detected at the
	 *                   current frame, but has temporal coherence
	 *                   with the same data at the  previous
	 *                   frame.</td></tr>
	 * </table>
	 *
	 * \return An array of statuses.
	 */
	virtual const SK::Array<int32_t> &getFingerStatuses() const;

	// \cond IGNORE_DOXYGEN
	int32_t getFingerStatus(int index) const;
	// \endcond

	/**
	 * \brief Gets the 2D coordinates of each fingertip.
	 *
	 * \return An array of 2D vectors.
	 */
	virtual const SK::Array<SK::Vector2> &getFingerTipPositions2D() const;

	// \cond IGNORE_DOXYGEN
	SK::Vector2 getFingerTipPosition2D(int index) const;
	// \endcond

	/**
	 * \brief Gets the 3D coordinates of each fingertip.
	 *
	 * \return An array of 3D vectors.
	 */
	virtual const SK::Array<SK::Vector3> &getFingerTipPositions3D() const;

	// \cond IGNORE_DOXYGEN
	SK::Vector3 getFingerTipPosition3D(int index) const;
	// \endcond

	/**
	 * \brief Gets the hand mesh in 2D coordinates.
	 *
	 * \return An array of 2D vectors.
	 */
	virtual const SK::Array<SK::Vector2> &getMeshPoints2D() const;

	/**
	 * \brief Gets the hand mesh in 3D coordinates.
	 *
	 * \return An array of 3D vectors.
	 */
	virtual const SK::Array<SK::Vector3> &getMeshPoints3D() const;

	/**
	 * \brief Gets the hand mesh normals.
	 *
	 * \return An array of 3D vectors.
	 */
	virtual const SK::Array<SK::Vector3> &getMeshNormals() const;

	/**
	 * \brief Gets the hand mesh intensities.
	 *
	 * This corresponds to the confidence levels at the different
	 * points of the mesh.
	 *
	 * \return An array of floats between 0.f and 1.f.
	 */
	virtual const SK::Array<float> &getMeshIntensities() const;

	/**
	 * \brief Returns the mesh triangles.
	 *
	 * \return An array of vectors of indices indicating the mesh
	 *         triangles.
	 */
	virtual const SK::Array<SK::Vector3i> &getMeshTriangles() const;

	/**
	 * \brief Returns the contour of the mesh.
	 *
	 * This corresponds to the outline of the hand.
	 *
	 * \return An array of indices indicating the contour of the mesh.
	 */
	virtual const SK::Array<int32_t> &getMeshContour() const;

	/**
	 * \brief Gets a reference to the Hand's controller.
	 * \return A controller based on the hand detection.
	 */
	virtual HandController &getController();

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
