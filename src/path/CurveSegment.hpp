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

#ifndef OgreRails_Paths_CurveSegment_INCLUDED
#define OgreRails_Paths_CurveSegment_INCLUDED

#include "SegmentInstance.hpp"

namespace OgreRails {

namespace Paths {

/**
 * Full 90 degrees curve prototype.
 */
class CurveSegment: public Segment {

	float mLength; //< OGRE units

	float mRadius; //< OGRE units

	float mCausewayHeight; //< OGRE units

	unsigned int mSnapGridRadius;

	Segment::Turn mTurn;

	public:

	/**
	* @param radius Radius of this curve in snappoints
	* @param turn The side which this curve segment turns
	* @param causewayHeight Height of track above it's snappoint coords
	*/
	CurveSegment(unsigned int radius, Segment::Turn turn, float causewayHeight)
		:mCausewayHeight(causewayHeight), mSnapGridRadius(radius), mTurn(turn)
	{
		mRadius = SNAPGRID_H_SPACE * radius;
		mLength = (Ogre::Math::PI * mRadius) / 2.0f; // Quarter circle

	}

	virtual ~CurveSegment()
	{
	}

	float getLength() const
	{
		return mLength;
	}

	Segment::Turn getTurn() const
	{
		return mTurn;
	}

	/** Computes coordinates of point on this segment
	* @param coords The coordinates to compute
	* @param snapGridPos Snapgrid position of the given segment
	* @param orientation Orientation ot the given segment
	* @param offset Given point's offset from segment's pivot (OGRE units)
	*/
	void computeCoords(
			Ogre::Vector3& coords, OgreRails::Coords const & snapGridPos,
			Segment::Orientation orientation, float offset);

	void advance(Coords & pos, Segment::Direction & dir, Segment::Turn turn = TURN_NONE) const;

};

} // namespace Paths

} // namespace OgreRails

#endif // Include guard
