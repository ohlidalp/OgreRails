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

#ifndef OgreRails_Paths_CurveSegmentFactory_INCLUDED
#define OgreRails_Paths_CurveSegmentFactory_INCLUDED

#include "CurveSegmentInstance.hpp"
#include "SegmentFactory.hpp"

namespace OgreRails {

namespace Paths {

/**
*/
class CurveSegmentFactory : public SegmentFactory
{

	std::auto_ptr<CurveSegment> mPrototype;

	public:

	CurveSegmentFactory(CurveSegment * proto)
	{
		mPrototype = std::auto_ptr<CurveSegment>(proto);
	}

	CurveSegmentInstance* instance(Coords const & pos, Segment::Direction dir)
	{
		Segment::Orientation o;
		switch(dir){
			case Segment::DIRECTION_X:
				o = Segment::ORIENTATION_NEG_Y;//X;
				break;
			case Segment::DIRECTION_Y:
				o = Segment::ORIENTATION_POSITIVE;//ORIENTATION_NEGATIVE;
				break;
			case Segment::DIRECTION_NEG_X:
				o = Segment::ORIENTATION_NEG_X;//Y;
				break;
			case Segment::DIRECTION_NEG_Y:
				o = Segment::ORIENTATION_NEGATIVE;//POSITIVE;
				break;
			default:;
		}
		return new CurveSegmentInstance(mPrototype.get(), pos, o);
	}

	virtual Segment * getPrototype()
	{
		return mPrototype.get();
	}
};

} // namespace Paths

} // namespace OgreRails

#endif // Include guard
