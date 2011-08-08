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

#ifndef OgreRails_Paths_PathChooser_INCLUDED
#define OgreRails_Paths_PathChooser_INCLUDED

#include "Endpoint.hpp"

namespace OgreRails {

namespace Paths {

/** Abstract class which vehicles use to query routing info.
*/
class PathChooser
{
	public:

	PathChooser(){};

	virtual ~PathChooser(){}

	/** Fetches a path to follow
	* @param endpoint The endpoint to provide route for.
	* @param path Path where the traveller came from.
	*/
	virtual Path * getNextPath(Endpoint & endpoint, Path * path ) const = 0;
};

} // namespace Path

} // namespace OgreRails

#endif // Include guard

