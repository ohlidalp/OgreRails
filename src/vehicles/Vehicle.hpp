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

#ifndef OgreRails_PathVehicle_INCLUDED
#define OgreRails_PathVehicle_INCLUDED

#include "PathSpan.hpp"

namespace OgreRails {

/** An abstract
*/
class Vehicle
{
	public:

	virtual void updatePosition(Paths::Slider& slider, PathSpanList::iterator & pathSpanIt, PathSpanList::iterator & pathSpanEnd) = 0;

	//virtual void setPosition(Ogre::Vector3 const & pos) = 0;

	virtual float getLength() const = 0;
};

} // namespace OgreRails

#endif // Include guard

