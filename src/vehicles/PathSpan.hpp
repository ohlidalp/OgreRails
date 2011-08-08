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

#ifndef OgreRails_PathSpan_INCLUDED
#define OgreRails_PathSpan_INCLUDED

#include "../path/Slider.hpp"

namespace OgreRails {

typedef std::pair<Paths::Path*, Paths::Path::End> PathSpanElement;

/** Represents a sequence of connected paths, which a Consist spans over.
*/
class PathSpanList: public std::list<PathSpanElement>
{
public:
	void add(Paths::Path* p, Paths::Path::End e)
	{
		this->push_front(std::make_pair<Paths::Path*, Paths::Path::End>(p,e));
	}

};

} // namespace OgreRails

#endif // Include guard
