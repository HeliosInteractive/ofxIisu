/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates the iisu source (either a camera
//                      or movie).
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

#include "CameraInfo.h"
#include "MovieInfo.h"

namespace SK
{
struct Device;

namespace Easii
{
/**
 * \ingroup SOURCE
 * \class Source Source.h EasiiSDK/Iisu.h
 * \brief This class provides data about a 3D data source (e.g. a
 *        camera).
 *
 * The Source object represents the data source that iisu™ is
 * currently processing. It contains information such as the depth
 * map, the RGB Image (if present), the camera characteristics and
 * filter configuration.
 *
 * You can access the source from the Scene object:
 *
 * \code
 * using namespace SK::Easii;
 *
 * Iisu &iisu = Iisu::instance();
 * Source &source = iisu.getScene().getSource();
 * \endcode
 */
class Source
{
	Source(const Source &);
	Source &operator = (const Source &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Constructor.
	 */
	Source();

	/**
	 * \brief Destructor.
	 */
	virtual ~Source();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(SK::Device &device);
	// \endcond

	/**
	 * \brief Checks whether the current source is a movie.
	 * \return \c true if the current source is a movie.
	 */
	virtual bool isMovie() const;

	/**
	 * \brief Gets a reference to the camera info.
	 * \return A reference to the source's CameraInfo object.
	 */
	virtual SK::Easii::CameraInfo &getCameraInfo();

	/**
	 * \brief Gets a reference to the movie info.
	 * \return A reference to the source's MovieInfo object.
	 * \pre isMovie()
	 */
	virtual SK::Easii::MovieInfo &getMovieInfo();

	/**
	 * \brief Checks if the source is occluded.
	 * \return \c true if the camera is occluded.
	 */
	virtual bool isOccluded() const;

	/**
	 * \brief Checks if the source has a depth image.
	 * \return \c true if the current camera/movie provides a depth
	 *         image.
	 */
	virtual bool hasDepthImage() const;

	/**
	 * \brief Gets the depth image.
	 * \return A reference to the depth image.
	 * \pre hasDepthImage()
	 */
	virtual const SK::Image &getDepthImage() const;

	/**
	 * \brief Checks if the source has a confidence image.
	 * \return \c true if the current camera/movie provides a confidence
	 *         image.
	 */
	virtual bool hasConfidenceImage() const;

	/**
	 * \brief Gets the confidence image.
	 * \return A reference to the confidence image.
	 * \pre hasConfidenceImage()
	 */
	virtual const SK::Image &getConfidenceImage() const;

	/**
	 * \brief Checks if the source has a color image.
	 * \return \c true if the current camera/movie provides a color
	 *         image.
	 */
	virtual bool hasColorImage() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Checks if the source has a color image.
	 * \return \c true if the current camera/movie provides a color
	 *         image.
	 * \deprecated Use hasColorImage
	 * \sa hasColorImage
	 */
	bool hasRGBImage() const;
	// \endcond

	/**
	 * \brief Gets the color image.
	 * \return A reference to the color image.
	 * \pre hasColorImage()
	 */
	virtual const SK::Image &getColorImage() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets the color image.
	 * \return A reference to the color image.
	 * \pre hasColorImage()
	 * \deprecated Use getColorImage.
	 * \sa getColorImage
	 */
	const SK::Image &getRGBImage() const;
	// \endcond

	/**
	 * \brief Gets the index of the current frame.
	 * \return The index of the current frame.
	 */
	virtual int32_t getFrame() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets the index of the current frame.
	 * \return The index of the current frame.
	 * \deprecated Use getFrame
	 * \sa getFrame
	 */
	int32_t getCurrentFrameIndex() const;
	// \endcond

	/**
	 * \brief Enables or disables the confidence threshold filter.
	 * \param enabled Flag to set whether the confidence threshold
	 *        filter is enabled.
	 */
	virtual void enableConfidenceThresholdFilter(bool enabled);

	/**
	 * \brief Checks if the confidence threshold filter is enabled.
	 * \return \c true if the confidence threshold filter is enabled,
	 *         \c false otherwise.
	 */
	virtual bool isConfidenceThresholdFilterEnabled() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * Sets the minimum confidence filter value
	 * \param threshold the value of the minimum confidence value
	 * \deprecated Use setMinimumConfidenceThreshold
	 * \sa setMinimumConfidenceThreshold
	 */
	void setMinConfidenceThreshold(int32_t threshold);
	// \endcond

	/**
	 * \brief Sets the minimum confidence threshold value.
	 *
	 * Any pixels with a confidence value that is below this threshold
	 * is discarded.
	 *
	 * This filter is useful to remove noisy, low-confidence objects
	 * that reflect poorly the IR light emitted by the camera.  Note
	 * that this value is camera specific, default values are set per
	 * camera.
	 *
	 * \param threshold The value of the minimum confidence threshold.
	 */
	virtual void setMinimumConfidenceThreshold(int32_t threshold);

	/**
	 * \brief Gets the minimum confidence threshold.
	 * \return The value of the minimum confidence threshold.
	 */
	virtual int32_t getMinimumConfidenceThreshold() const;

	/**
	 * \brief Enables or disables the reconstruction filter.
	 *
	 * So-called "flying" pixels are pixels located on the edge of
	 * objects.  This threshold value is the maximum depth value
	 * beyond which two pixels are flagged as flying pixels. That is,
	 * when the threshold value is very low, you destroy and
	 * reconstruct partially a lot of pixels (leading potentially to
	 * some loss of information). Conversely, when the threshold value
	 * is too high, an excessive number of flying pixels will remain,
	 * which will degrade the overall tracking quality.
	 *
	 * \param enabled A flag to set whether the reconstruction filter
	 *        is enabled.
	 */
	virtual void enableReconstructionFilter(bool enabled);

	/**
	 * \brief Checks if the reconstruction filter is enabled.
	 * \return \c true if the reconstruction filter is enabled, \c
	 *         false otherwise.
	 * \sa enableReconstructionFilter
	 */
	virtual bool isReconstructionFilterEnabled() const;

	// \cond IGNORE_DOXYGEN
    /**
	 * \brief Sets the maximum reconstruction filter value
	 * \param value the value of the maximum reconstruction filter
	 * \deprecated Use setMaximumReconstructionThreshold
	 * \sa setMaximumReconstructionThreshold
	 */
	void setMaxReconstructionThreshold(float value);
	// \endcond

	/**
	 * \brief Sets the maximum reconstruction threshold.
	 *
	 * \param threshold The value of the maximum reconstruction threshold.
	 * \sa enableReconstructionFilter
	 */
	virtual void setMaximumReconstructionThreshold(float threshold);

	/**
	 * \brief Gets the maximum reconstruction threshold.
	 * \return The value of the maximum reconstruction threshold.
	 * \sa enableReconstructionFilter
	 */
	virtual float getMaximumReconstructionThreshold() const;

	/**
	 * \brief Enables or disables the depth filter.
	 *
	 * This filter removes the pixels outside the [MinDepth;MaxDepth]
	 * interval (in meters).  It makes it possible to remove points
	 * that are at too great a distance from the camera and which are
	 * usually noisy, or points that are too close to the camera.
	 *
	 * \param enabled A flag to set whether the depth filter is
	 *        enabled.
	 */
	virtual void enableDepthFilter(bool enabled);

	/**
	 * \brief Checks if the depth filter is enabled.
	 * \return \c true if the depth filter is enabled, \c false
	 *         otherwise.
	 */
	virtual bool isDepthFilterEnabled() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Sets the minimum depth value.
	 * \param value of the minimum depth.
	 * \deprecated Use setMinimumDepth
	 * \sa setMinimumDepth
	 */
	void setMinDepth(float value);
	// \endcond

	/**
	 * \brief Sets the minimum depth.
	 * \param depth The minimum depth, in meters.
	 * \sa enableDepthFilter
	 */
	virtual void setMinimumDepth(float depth);

	/**
	 * \brief Gets the minimum depth of the scene.
	 * \return The minimum depth, in meters.
	 * \sa enableDepthFilter
	 */
	virtual float getMinimumDepth() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Sets the maximum depth.
	 * \param value of the maximum depth
	 * \deprecated Use setMaximumDepth
	 * \sa setMaximumDepth
	 */
	virtual void setMaxDepth(float value);
	// \endcond

	/**
	 * \brief Sets the maximum depth of the scene.
	 * \param depth The maximum depth of the scene, in meters.
	 * \sa enableDepthFilter
	 */
	virtual void setMaximumDepth(float depth);

	/**
	 * \brief Gets the maximum depth of the scene.
	 * \return The maximum depth of the scene, in meters.
	 * \sa enableDepthFilter
	 */
	virtual float getMaximumDepth() const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
