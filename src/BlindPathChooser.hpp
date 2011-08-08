/*
	Copyright 2010 - 2011 Petr Ohlidal

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

#ifndef OgreRails_BlindPathChooser_INCLUDED
#define OgreRails_BlindPathChooser_INCLUDED

#include "path/PathChooser.hpp"

namespace OgreRails {

/** Selects some other path in Endpoint's path list.
*/
class BlindPathChooser: public Paths::PathChooser
{
	public:

	~BlindPathChooser(){}

	Paths::Path * getNextPath(Paths::Endpoint & endpoint, Paths::Path * path ) const {
		unsigned int n = endpoint.getNumPaths();
		if (endpoint.isDeadEnd()) {
			return 0;
		}
		std::list<Paths::Path*>::iterator it = endpoint.getPaths().begin();
		std::list<Paths::Path*>::iterator endIt = endpoint.getPaths().end();
		for(; it != endIt; it++) {
			if (*it == path) {
				std::list<Paths::Path*>::iterator peekIt = it;
				peekIt++;
				if (peekIt == endIt){
					it--;
					return *it;
				} else {
					return *peekIt;
				}
			}
		}
	}
};

} // namespace OgreRails

#endif // Include guard
