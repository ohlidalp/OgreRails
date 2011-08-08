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

#ifndef OgreRails_Paths_Path_INCLUDED
#define OgreRails_Paths_Path_INCLUDED

#include "SegmentInstance.hpp"

namespace OgreRails {

namespace Paths {

class Endpoint; // Forward decl.

/**
 * A sequence of path segments, connecting two endpoints
*/
class Path
{
	Endpoint* mEndpoints[2];

	/// Ends of doubly-linked-list
	SegmentInstance* mEndSegments[2];

	float mLength;

		public:

	Path() {
		mEndpoints[0] = 0;
		mEndpoints[1] = 0;
		mEndSegments[0] = 0;
		mEndSegments[1] = 0;
	}

	virtual ~Path() {
		// Delete segments TODO
	}

	enum End {END_ENTRY, END_EXIT};

	void addSegment(SegmentInstance * seg, Path::End end = Path::END_EXIT) {
		Segment::Neighbour endSide = (end == Path::END_EXIT) ? Segment::NEIGHBOUR_NEXT : Segment::NEIGHBOUR_PREVIOUS;
		Path::End otherEnd = Path::otherEnd(end);

		// Add segment to linked list
		seg->setNeighbour(0, endSide);
		if (this->isEmpty()) {
			seg->setNeighbour(0, Segment::otherNeighbour(endSide));
			mEndSegments[Path::END_ENTRY] = seg;
			mEndSegments[Path::END_EXIT] = seg;
		} else {
			mEndSegments[end]->setNeighbour(seg, endSide);
			seg->setNeighbour(mEndSegments[end], Segment::otherNeighbour(endSide));
			mEndSegments[end] = seg;
		}

		// Update path length
		mLength += seg->getLength();
	}

	SegmentInstance * getEndSegment(Path::End which) const {
		return mEndSegments[which];
	}

	float getLength() const {
		return mLength;
	}

	Endpoint * getEndpoint(Path::End which) const {
		return mEndpoints[which];
	}

	Path::End whichEndpoint(Endpoint * e) const{
		return (e == mEndpoints[Path::END_ENTRY]) ? Path::END_ENTRY : Path::END_EXIT;
	}

	void setEndpoint(Endpoint * endpoint, Path::End end)
	{
		mEndpoints[end] = endpoint;
	}

	bool isEmpty() const
	{
		// The first segment is attached to both ends.
		// To test emptiness, testing one end suffices.
		return mEndSegments[0] == 0;
	}

	/** Returns the inverse value of Path::Endpoint
	*/
	static Path::End otherEnd(Path::End e){
		return Path::End( (e+1)%2 );
	}

};

} // namespace Paths

} // namespace OgreRails

#endif // Include guard
