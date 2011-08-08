/*
	Copyright 2010 - 2011 Petr Ohlídal

	This file is a part of OgreRails

	OgreRails is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OgreRails is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with OgreRails.  If not, see <http://www.gnu.org/licenses/>.
*/

/** @file  */

#ifndef OgreRails_Coords_INCLUDED
#define OgreRails_Coords_INCLUDED

#include "OgreVector3.h"
#include "../CodeConfig.hpp"

namespace OgreRails {

/** Integral coordinates, i.e. for snap-grid.
Note: These do not follow OGRE's coordinate system (swapped Y<->Z), but use axes naturally.
*/
class Coords
{
	public:
	unsigned int x;
	unsigned int y;
	unsigned int z;

	Coords(unsigned int x, unsigned int y, unsigned int z = 0u):
		x(x), y(y), z(z)
	{
	}

	Coords():
		x(0u), y(0u), z(0u)
	{}

	Ogre::Vector3 toOgreUnits() const
	{
		return Ogre::Vector3(
			static_cast<float>(x) * SNAPGRID_H_SPACE,
			static_cast<float>(z) * SNAPGRID_H_SPACE,
			static_cast<float>(y) * SNAPGRID_H_SPACE);
	}

};

} // namespace OgreRails

#endif // Include guard
