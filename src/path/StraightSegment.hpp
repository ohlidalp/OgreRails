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

#ifndef OgreRails_Paths_StraightSegment_INCLUDED
#define OgreRails_Paths_StraightSegment_INCLUDED

#include "SegmentInstance.hpp"
#include <iomanip> // Debug

namespace OgreRails {

namespace Paths {

/**
 * Segment which leads straight across an axis.
 */
class StraightSegment: public Segment {

	float mLength; //< OGRE units

	float mCausewayHeight; //< OGRE units

	Ogre::Vector3 mVector;

	unsigned int mSnapGridLength;

	public:

	StraightSegment(unsigned int snapGridLen, Ogre::Vector3 const & vec, float causewayHeight):
		mCausewayHeight(causewayHeight), mVector(vec), mSnapGridLength(snapGridLen)
	{
		mLength = static_cast<float>(snapGridLen) * SNAPGRID_H_SPACE;
	}

	virtual ~StraightSegment(){}

	float getLength() const {
		return mLength;
	}

	/**
	* @param mapPos Endpoint position on map
	*/
	void computeCoords(Ogre::Vector3& coords, OgreRails::Coords const & snapGridPos, Segment::Orientation orientation, float offset) {
		Ogre::Vector3 rel;
		float relPos = offset/mLength;
		rel.x = mVector.x * relPos;
		rel.z = mVector.z * relPos;
		rel.y = 0.0f;
		//Segment::orientVector(coords, orientation);
		switch (orientation) {
			case Segment::ORIENTATION_NEG_X:
				coords.z = rel.x;
				coords.x = -rel.z;
				coords.y = rel.y;
				break;
			case Segment::ORIENTATION_NEG_Y:
				coords.z = -rel.x;
				coords.x = rel.z;
				coords.y = rel.y;
				break;
			case Segment::ORIENTATION_NEGATIVE:
				coords.x = -rel.x;
				coords.z = -rel.z;
				coords.y = rel.y;
				break;
			default:
				coords.x = rel.x;
				coords.y = rel.y;
				coords.z = rel.z;
		}
		coords.x += static_cast<float>(snapGridPos.x) * SNAPGRID_H_SPACE;
		coords.z += static_cast<float>(snapGridPos.y) * SNAPGRID_H_SPACE;
		coords.y = static_cast<float>(snapGridPos.z) + mCausewayHeight;
		/*
		std::stringstream s;
		s.precision(2);
		s << "StraightSegment::computeCoords()\n"
			<< "offset:" << std::fixed << offset
			<< " X:" << coords.x << " z(Y):" << coords.z << " y(Z):" << coords.y
			<< "\n    SnapGridPos X:" << snapGridPos.x << " Y:" << snapGridPos.y
			<< "Orientation: " << ((orientation == Segment::ORIENTATION_NEG_X)
				? "NEG_X"
				: (orientation == Segment::ORIENTATION_POSITIVE)
					? "POSITIVE"
					: "OTHER")
			<< std::endl;
		DebugConsole::getSingleton().print(s.str());
		*/
	}

	Segment::Turn getTurn() const
	{
		return Segment::TURN_NONE;
	}

	void advance(Coords & pos, Segment::Direction & dir, Segment::Turn turn = TURN_NONE) const
	{
		switch (dir) {
			case Segment::DIRECTION_X:
				pos.x += mSnapGridLength;
				break;
			case Segment::DIRECTION_Y:
				pos.y += mSnapGridLength;
				break;
			case Segment::DIRECTION_NEG_X:
				pos.x -= mSnapGridLength;
				break;
			case Segment::DIRECTION_NEG_Y:
				pos.y -= mSnapGridLength;
				break;
			default:;
		}
	}

};

} // namespace Paths

} // namespace OgreRails

#endif // Include guard
