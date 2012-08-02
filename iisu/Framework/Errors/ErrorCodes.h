#pragma once

namespace SK {

	/**
	 * \enum	ErrorCode
	 *
	 * \brief	Values that represent ErrorCode. 
	 */

	enum ErrorCode {

		SUCCESS = 0x0,
		// Low - level codes

		INTERNAL = 0x100,
		MEMORY_ALLOCATION_ERROR = 0x101,
		INVALID_INDEX = 0x102,

		// Licensing
		LICENSE_NOT_FOUND = 0x200,
		INVALID_FEATURE = 0x201,
		INVALID_FEATURE_VERSION = 0x202,
		LICENSE_EXPIRED = 0x203,
		LICENSE_WINDBACK = 0x204,
		LICENSE_ERROR = 0x205,		// Flexera initialization or default error.
		

		// Configuration  Files

		CONFIG_NOT_FOUND = 0x300,
		INVALID_CONFIG = 0x301,
		INVALID_CONFIG_PARAMETER = 0x302,

		// Device based

		INVALID_DEVICE = 0x400,
		IISUDLL_NOT_FOUND = 0x401,
		DEVICE_START_FAILED = 0x402,
		INITIALISATION_FAILED = 0x403,

		// Data, Parameters, Commands, Events

		INVALID_PATH = 0x500,
		REGISTRATION_FAILED = 0x501,
		INVALID_DATA_PATH = 0x502,
		INVALID_DATA_TYPE = 0x503, // FIX THIS
		INVALID_HANDLE = 0x504,
		COMMAND_FAILED = 0x505,
		UPDATE_FRAME_FAILED = 0x506,
		RELEASE_FRAME_FAILED = 0x507,
		INVALID_FRAME = 0x508,
		INVALID_META_ATTRIBUTE = 0x509,

		// File - stream

		INVALID_FILE_FORMAT = 0x600,
		FILE_CREATION_FAILED = 0x601,
		FILE_OPEN_FAILED = 0x602,
		FILE_WRITE_FAILED = 0x603,
		FILE_READ_FAILED = 0x604,
		FILE_NOT_FOUND = 0x605,

		// Network

		CONNECTION_FAILED = 0x700,
		CONNECTION_LOST = 0x701,
		UNKNOWN_MESSAGE = 0x702,
		INVALID_MESSAGE = 0x703,

		// Movies

		INVALID_MOVIE_FORMAT = 0x710,
		INVALID_MOVIE_CONFIGURATION = 0x711,
		MOVIE_DECODING_FAILED = 0x712,
		MOVIE_DLL_NOT_FOUND = 0x713,
		MOVIE_DLL_LOADING_FAILED = 0x714,
		INVALID_MOVIE_INFO = 0x715,

		// Cameras

		CAMERA_UNKNOWN = 0x720,
		INVALID_CAMERA_CONFIGURATION = 0x721,
		CAMERA_NOT_FOUND = 0x722,
		UNSUPPORTED_CAMERA = 0x723,
		UNSUPPORTED_CAMERA_VERSION = 0x724,
		CAMERA_DDL_NOT_FOUND = 0x725,
		CAMERA_DLL_LOADING_FAILED = 0x726,
		CAMERA_INITIALISATION_FAILED = 0x727,
		
		// Execution
		
		PROCESS_PULSE_FRAME_FAILED = 0x800,

		// Iisu connection - loading

		IISU_DLL_LOADING_FAILED = 0x900,
		SERVER_CONNECTION_FAILED = 0x901,
		INCOMPATIBLE_IISU_VERSION = 0x902,	
	};
}
