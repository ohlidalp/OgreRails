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

#ifndef OgreRails_Paths_SegmentInstance_INCLUDED
#define OgreRails_Paths_SegmentInstance_INCLUDED

#include "Segment.hpp"

namespace OgreRails {

namespace Paths {

/** An abstract path segment.
*/
class SegmentInstance
{
		protected:

	Segment* mPrototype;

	Coords mMapPos; ///< Snap-point coordinates

	SegmentInstance* mNeighbours[2];

	Segment::Orientation mOrientation;

		public:

	/** Constructor
	*/
	SegmentInstance(Segment* proto, Coords const& pos, Segment::Orientation o):
		mPrototype(proto), mMapPos(pos), mOrientation(o) {}

	virtual ~SegmentInstance(){}

	/** Length in ogre units
	*/
	virtual float getLength() const = 0;

	SegmentInstance* getNext() const
	{
		return mNeighbours[Segment::NEIGHBOUR_NEXT];
	}

	SegmentInstance* getPrevious() const
	{
		return mNeighbours[Segment::NEIGHBOUR_PREVIOUS];
	}

	SegmentInstance* getNeighbour(Segment::Neighbour which) const
	{
		return mNeighbours[which];
	}

	void setNext(SegmentInstance * seg)
	{
		mNeighbours[Segment::NEIGHBOUR_NEXT] = seg;
	}

	void setPrevious(SegmentInstance * seg)
	{
		mNeighbours[Segment::NEIGHBOUR_PREVIOUS] = seg;
	}

	void setNeighbour(SegmentInstance * seg, Segment::Neighbour which)
	{
		mNeighbours[which] = seg;
	}

	/** Computes coordinates of a point on the segment
	* @param offset Point's absolute position inside the segment (in OGRE units)
	* @param coords The final point in world coordinates
	*/
	void computeCoords( Ogre::Vector3& coords, float offset) const
	{
		mPrototype->computeCoords(coords, mMapPos, mOrientation, offset);
	}

	Coords const & getMapPos() const
	{
		return mMapPos;
	}
};

} // Namespace Path

} // Namespace OgreRails

#endif // Include guard
