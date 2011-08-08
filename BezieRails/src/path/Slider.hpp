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

#ifndef OgreRails_Paths_Slider_INCLUDED
#define OgreRails_Paths_Slider_INCLUDED

#include "Path.hpp"

namespace OgreRails {

namespace Paths {

/** Moves across one Path
*/
class Slider
{
	Path* mPath; ///< Path this slider is on

	SegmentInstance* mSegment; ///< Segment this slider is on

	float mSegOffset; ///< Position inside the segment

	public:

	Slider(){}

	Slider(const Slider & ps):
		mPath(ps.mPath),
		mSegment(ps.mSegment),
		mSegOffset(ps.mSegOffset){}

	virtual ~Slider(){}

	/**
	 * @param distance The distance to travel. If end of path is hit, this value is set to the remaining distance.
	 * @return True if the move was performed, false if the end of the line was hit.
	 * */
	bool move (float & distance)
	{
		mSegOffset += distance;

		if (distance > 0.0f) {
			// Forward movement
			while (mSegOffset > mSegment->getLength()) {
				mSegOffset -= mSegment->getLength();
				if (mSegment->getNext() == 0) { // End of path
					distance = mSegOffset;
					mSegOffset = mSegment->getLength();
					return false;
				} else {
					mSegment = mSegment->getNext();
					/*
					std::cout << "Slider::move()"
						<< " Seg: " << mSegment
						<< " NextSeg: " << mSegment->getNext()
						<< " PrevSeg: " << mSegment->getPrevious()
						<< " MapPos X:" <<mSegment->getMapPos().x <<" Y:" <<mSegment->getMapPos().y
						<< std::endl;
					*/
				}
			}
			return true;
		} else {
			// Backward movement
			while (mSegOffset < 0.0f) {
				if (mSegment->getPrevious() == 0) {
					distance = mSegOffset;
					mSegOffset = 0.0f;
					return false;
				} else {
					mSegment = mSegment->getPrevious();
					mSegOffset += mSegment->getLength();
				}
			}
			return true;
		}
	}

	void snap(Path* path, Path::End whichEnd)
	{
		mPath = path;
		mSegment = path->getEndSegment(whichEnd);
		/*
		std::cout << "Slider::snap()"
			<< " Seg: " << mSegment
			<< " NextSeg: " << mSegment->getNext()
			<< " PrevSeg: " << mSegment->getPrevious()
			<< " MapPos X:" <<mSegment->getMapPos().x <<" Y:" <<mSegment->getMapPos().y
			<< std::endl;
		*/
		if (whichEnd == Path::END_ENTRY) {
			mSegOffset = 0.0f;
		} else {
			mSegOffset = mSegment->getLength();
		}
	}

	void getPosition(Ogre::Vector3& pos)
	{
		mSegment->computeCoords(pos, mSegOffset);
	}

	Path * getPath()
	{
		return mPath;
	}

	SegmentInstance * getSegment()
	{
		return mSegment;
	}

	float getSegOffset()
	{
		return mSegOffset;
	}
};

} // namespace Path

} // namespace OgreRails

#endif // Include guard
