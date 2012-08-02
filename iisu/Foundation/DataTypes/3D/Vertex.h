#pragma once
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Foundation/DataTypes/Color/Color.h>

namespace SK 
{	
	/**
	 * \class	Vertex
	 *
	 * \brief	Struct representing a vertex. 
	 */

	class Vertex
	{
	public:

		/**
		 * \fn	Vertex::Vertex()
		 *
		 * \brief	Default constructor.
		 *		   
		 * Initialize the coordinates x, y and z  to 0.0
		 * Initialize the colors r, g, b and a  to 0
		 * Initialize usX, usY to 0
		*/

		Vertex()
		{
			usX = usY = 0;
		}

		//! 3D position
		Vector3 position;
		//! Color
		Color4c color;
		//! 2D coordinate in depth image space
		uint16_t usX, usY;
	};

}
