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

/** @file  */

#ifndef OgreRails_Paths_StraightSegmentFactory_INCLUDED
#define OgreRails_Paths_StraightSegmentFactory_INCLUDED

#include "StraightSegmentInstance.hpp"
#include "SegmentFactory.hpp"

namespace OgreRails {

namespace Paths {

/**
*/
class StraightSegmentFactory : public SegmentFactory
{

	std::auto_ptr<StraightSegment> mPrototype;

	public:

	StraightSegmentFactory(StraightSegment * proto)
	{
		mPrototype = std::auto_ptr<StraightSegment>(proto);
	}

	SegmentInstance* instance(Coords const & pos, Segment::Direction dir)
	{
		Segment::Orientation o;
		switch(dir){
			case Segment::DIRECTION_X:
				o = Segment::ORIENTATION_POSITIVE;
				break;
			case Segment::DIRECTION_Y:
				o = Segment::ORIENTATION_NEG_X;
				break;
			case Segment::DIRECTION_NEG_X:
				o = Segment::ORIENTATION_NEGATIVE;
				break;
			case Segment::DIRECTION_NEG_Y:
				o = Segment::ORIENTATION_NEG_Y;
				break;
			default:;
		}
		return new StraightSegmentInstance(mPrototype.get(), pos, o);
	}

	virtual Segment * getPrototype()
	{
		return mPrototype.get();
	}
};

} // namespace Paths

} // namespace OgreRails

#endif // Include guard
