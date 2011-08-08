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

#ifndef OgreRails_UniqueIdGenerator_INCLUDED
#define OgreRails_UniqueIdGenerator_INCLUDED

#include <string>
#include <cstdio>

namespace OgreRails {

class UniqueIdGenerator
{
	unsigned long int mCounter;
	static UniqueIdGenerator* mInstance;

	UniqueIdGenerator():
		mCounter(0)
		{}

	~UniqueIdGenerator(){
		delete mInstance;
	}

	public:

	static UniqueIdGenerator& getSingleton(){
		if(mInstance == 0){
			mInstance = new UniqueIdGenerator();
		}
		return *mInstance;
	}

	unsigned long int getAsUlong(){
		return mCounter++;
	}

	std::string getAsDecadic(){
		char cstr[50];
		std::sprintf(cstr, "%lu",mCounter++);
		return std::string(cstr);
	}

	std::string getAsHexadecimal(){
		char s[25];
		std::sprintf(s, "%lx", mCounter++);
		return std::string(s);
	}
};

} // namespace OgreRails

#endif // Include guard
