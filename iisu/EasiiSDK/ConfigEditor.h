/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Adapter around iisu's configuration.
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

#include <Iisu/Handles/IisuHandle.h>

namespace SK {
namespace Easii {
/**
 * \class ConfigEditor ConfigEditor.h EasiiSDK/Iisu.h
 * \brief This class can be used to configure iisu.
 */
class ConfigEditor
{
private:

	ConfigEditor(const ConfigEditor &);
	ConfigEditor &operator = (const ConfigEditor &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Default constructor.
	 */
	ConfigEditor();

	/**
	 * \brief Destructor.
	 */
	virtual ~ConfigEditor();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(SK::IisuHandle &handle);
	// \endcond

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Sets a configuration value.
	 *
	 * \code
	 * Iisu &iisu = Iisu::instance();
	 * ConfigEditor &editor = iisu.getConfigEditor();
	 * editor.setString("/CONFIG/PROCESSING/UM", "1");
	 * \endcode
	 *
	 * \param path the xpath (e.g. /CONFIG/PROCESSING/UM) of the value.
	 * \param value The new value.
	 * \param copyToConfigFile update the internal config file image
	 *        too \see save()
	 * \deprecated
	 * \sa setValue
	 */
	void setString(const char *path,const char *value, bool copyToConfigFile = false);
	// \endcond

	/**
	 * \brief Sets a configuration value.
	 *
	 * \code
	 * Iisu &iisu = Iisu::instance();
	 * ConfigEditor &editor = iisu.getConfigEditor();
	 * editor.setValue("/CONFIG/PROCESSING/UM", "1");
	 * \endcode
	 *
	 * \param path the xpath (e.g. /CONFIG/PROCESSING/UM) of the value.
	 * \param value The new value.
	 * \sa saveValue
	 * \sa getValue
	 */
	virtual void setValue(const char *path, const char *value);

	/**
	 * \brief Sets a configuration value and saves it in the
	 *        configuration file.
	 *
	 * \code
	 * Iisu &iisu = Iisu::instance();
	 * ConfigEditor &editor = iisu.getConfigEditor();
	 * editor.saveValue("/CONFIG/PROCESSING/UM", "1");
	 * \endcode
	 *
	 * \param path the xpath of the value.
	 * \param value The new value.
	 * \sa setValue
	 * \sa getValue
	 */
	virtual void saveValue(const char *path, const char *value);

	/**
	 * \brief Gets a configuration value.
	 *
	 * \param path the xpath of the value.
	 * \return The value of the configuration parameter.
	*/
	virtual SK::String getValue(const char *path) const;

	/**
	 * \brief Gets the number of configuration parameters in order to
	 *        be able to enumerate them.
	 *
	 * \return The number of configuration parameters.
	 * \sa getPath
	 */
	virtual int32_t getPathCount() const;

	/**
	 * \brief Gets the path of the <code>index</code>th configuration parameter.
	 *
	 * \param index of the configuration parameter path.
	 * \return The path to the configuration parameter.
	 * \sa getPathCount
	 * \sa getValue
	 */
	virtual SK::String getPath(int32_t index) const;

	/**
	 * \brief Saves the configuration file.
	 */
	virtual void saveConfigFile();

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
