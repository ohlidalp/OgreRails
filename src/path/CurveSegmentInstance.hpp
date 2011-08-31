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

#ifndef OgreRails_Paths_CurveSegmentInstance_INCLUDED
#define OgreRails_Paths_CurveSegmentInstance_INCLUDED

#include <memory>

#include "../CodeConfig.hpp"
#include "../util/Coords.hpp"
#include "CurveSegment.hpp"
#include "SegmentGraphicInstance.hpp"

namespace OgreRails {

namespace Paths {

/** 90 degrees curve segment.
*/
class CurveSegmentInstance: public SegmentInstance
{

	std::auto_ptr<SegmentGraphicInstance> mGraphic;

		public:

	CurveSegmentInstance(
			Segment* proto, OgreRails::Coords const & pos,
			Segment::Orientation o, SegmentGraphicInstance* g):
		SegmentInstance(proto, pos, o), mGraphic(g)
	{
	}

	~CurveSegmentInstance(){}

	float getLength() const {
		return this->mPrototype->getLength();
	}

};

} // Namespace Paths

} // Namespace OgreRails

#endif // Include guard
