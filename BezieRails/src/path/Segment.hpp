/*
	Copyright 2010 - 2011 Petr Ohlidal

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

#ifndef OgreRails_Paths_Segment_INCLUDED
#define OgreRails_Paths_Segment_INCLUDED

#include "../util/Coords.hpp"
#include "../CodeConfig.hpp"

namespace OgreRails {

namespace Paths {

/**
*/
class Segment
{

	public:

	enum Orientation {ORIENTATION_POSITIVE, ORIENTATION_NEGATIVE, ORIENTATION_NEG_X, ORIENTATION_NEG_Y};

	enum Direction {DIRECTION_X, DIRECTION_Y, DIRECTION_NEG_X, DIRECTION_NEG_Y};

	enum Turn {TURN_NONE, TURN_LEFT, TURN_RIGHT};

	enum Neighbour {NEIGHBOUR_PREVIOUS, NEIGHBOUR_NEXT};

	virtual ~Segment(){}

	virtual float getLength() const = 0;

	virtual Segment::Turn getTurn() const = 0;

	/** Transforms given coordinates and direction; moves them from beginning of this segment to its end.
	*/
	virtual void advance(Coords & pos, Segment::Direction & dir, Segment::Turn turn = TURN_NONE) const = 0;

	virtual void computeCoords(Ogre::Vector3& coords, OgreRails::Coords const & snapGridPos, Segment::Orientation orientation, float offset) = 0;

	static Segment::Neighbour otherNeighbour(Segment::Neighbour n) {
		return Segment::Neighbour((n+1)%2);
	}
};

} // namespace Paths

} // namespace OgreRails

#endif // Include guard
