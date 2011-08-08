/*
	Copyright 2010 - 2011 Petr Ohlidal

	This file is a part of BezieRails

	BezieRails is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	BezieRails is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with BezieRails.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CurveSegment.hpp"

namespace OgreRails {

namespace Paths {

void CurveSegment::computeCoords(Ogre::Vector3& coords, OgreRails::Coords const & snapGridPos, Segment::Orientation orientation, float offset) {
	Ogre::Vector3 rel;
	float phi = (offset/mLength) * Ogre::Math::HALF_PI;

	switch(orientation){
		case Segment::ORIENTATION_NEG_Y: // Direction x
			{ // Block needed for declaring vars
				coords.z = Ogre::Math::Cos(phi) * ((mTurn == Segment::TURN_RIGHT) ? -mRadius : mRadius);
				coords.x = mRadius * Ogre::Math::Sin(phi);

				unsigned int posY = mTurn == Segment::TURN_RIGHT ?
					snapGridPos.y + mSnapGridRadius : snapGridPos.y - mSnapGridRadius;
				coords.x += static_cast<float>(snapGridPos.x) * SNAPGRID_H_SPACE;
				coords.z += static_cast<float>(posY) * SNAPGRID_H_SPACE;
			}
			break;
		case Segment::ORIENTATION_NEG_X: // Direction neg x
			{ // Block needed for declaring vars
				if (mTurn == Segment::TURN_RIGHT) {
					coords.z = Ogre::Math::Cos(phi) * mRadius;
					coords.x = Ogre::Math::Sin(phi) * -mRadius;
				} else {
					coords.z = Ogre::Math::Cos(phi) * -mRadius;
					coords.x = Ogre::Math::Sin(phi) * -mRadius;
/*Tried:
cos+, sin+
cos+, sin-
cos-, sin+
*/
				}

				unsigned int posY = mTurn == Segment::TURN_RIGHT ?
					snapGridPos.y - mSnapGridRadius : snapGridPos.y + mSnapGridRadius;
				coords.x += static_cast<float>(snapGridPos.x) * SNAPGRID_H_SPACE;
				coords.z += static_cast<float>(posY) * SNAPGRID_H_SPACE;
			}
			break;

		case Segment::ORIENTATION_NEGATIVE: // Direction neg y
			{ // Block needed for declaring vars
				if (mTurn == Segment::TURN_RIGHT) {
					coords.x = Ogre::Math::Cos(phi) * -mRadius;
					coords.z = Ogre::Math::Sin(phi) * -mRadius;
				} else {
					coords.x = Ogre::Math::Cos(phi) * mRadius;
					coords.z = Ogre::Math::Sin(phi) * -mRadius;
				}

				unsigned int posX = mTurn == Segment::TURN_RIGHT ?
					snapGridPos.x + mSnapGridRadius : snapGridPos.x - mSnapGridRadius;
				coords.x += static_cast<float>(posX) * SNAPGRID_H_SPACE;
				coords.z += static_cast<float>(snapGridPos.y) * SNAPGRID_H_SPACE;
			}
			break;

		case Segment::ORIENTATION_POSITIVE: // Direction y
			{ // Block needed for declaring vars
				if (mTurn == Segment::TURN_RIGHT) {
					coords.x = Ogre::Math::Cos(phi) * mRadius;
					coords.z = Ogre::Math::Sin(phi) * mRadius;
				} else {
					coords.x = Ogre::Math::Cos(phi) * -mRadius;
					coords.z = Ogre::Math::Sin(phi) * mRadius;

/*						//Tried:
sin-, cos+
sin+, cos-
sin-, cos-
sin+, cos+

cos+, sin+
cos-, sin+

*/
				}

				unsigned int posX = mTurn == Segment::TURN_RIGHT ?
					snapGridPos.x - mSnapGridRadius : snapGridPos.x + mSnapGridRadius;
				coords.x += static_cast<float>(posX) * SNAPGRID_H_SPACE;
				coords.z += static_cast<float>(snapGridPos.y) * SNAPGRID_H_SPACE;
			}
			break;

		default:;
	}

	coords.y = 0.0f;
}

void CurveSegment::advance(Coords & pos, Segment::Direction & dir, Segment::Turn turn) const
{
	switch (dir) {
		case Segment::DIRECTION_X:
			pos.x += mSnapGridRadius;
			if (mTurn == Segment::TURN_RIGHT) {
				dir = Segment::DIRECTION_Y;
				pos.y += mSnapGridRadius;
			} else {
				dir = Segment::DIRECTION_NEG_Y;
				pos.y -= mSnapGridRadius;
			}
			break;
		case Segment::DIRECTION_Y:
			pos.y += mSnapGridRadius;
			if (mTurn == Segment::TURN_RIGHT) {
				dir = Segment::DIRECTION_NEG_X;
				pos.x -= mSnapGridRadius;
			} else {
				dir = Segment::DIRECTION_X;
				pos.x += mSnapGridRadius;
			}
			break;
		case Segment::DIRECTION_NEG_X:
			pos.x -= mSnapGridRadius;
			if (mTurn == Segment::TURN_RIGHT) {
				dir = Segment::DIRECTION_NEG_Y;
				pos.y -= mSnapGridRadius;
			} else {
				dir = Segment::DIRECTION_Y;
				pos.y += mSnapGridRadius;
			}
			break;
		case Segment::DIRECTION_NEG_Y:
			pos.y -= mSnapGridRadius;
			if (mTurn == Segment::TURN_RIGHT) {
				dir = Segment::DIRECTION_X;
				pos.x += mSnapGridRadius;
			} else {
				dir = Segment::DIRECTION_NEG_X;
				pos.x -= mSnapGridRadius;
			}
	}
}

} // namespace Paths

} // namespace OgreRails
