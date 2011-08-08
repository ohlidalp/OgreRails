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

#ifndef OgreRails_Paths_Endpoint_INCLUDED
#define OgreRails_Paths_Endpoint_INCLUDED

#include "Path.hpp"

namespace OgreRails {

namespace Paths {

//class Path; // Forward decl.

class Endpoint
{
	std::list<Path*> mPaths;

	public:

	unsigned int getNumPaths() const
	{
		return mPaths.size();
	}

	void addPath(Path* path)
	{
		mPaths.push_back(path);
	}

	bool isDeadEnd() const
	{
		return mPaths.size() <= 1;
	}

	std::list<Path*> & getPaths()
	{
		return mPaths;
	}
};

} // namespace Path

} // namespace OgreRails

#endif // Include guard

