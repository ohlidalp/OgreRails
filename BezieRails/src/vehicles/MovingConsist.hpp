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

#ifndef OgreRails_MovingConsist_INCLUDED
#define OgreRails_MovingConsist_INCLUDED

#include "Consist.hpp"

namespace OgreRails {

/** A formation of rail vehicles
* Moves along a path at constant speed and with constant gaps between cars.
*/
class MovingConsist: public Consist
{
	float mSpeed; //< OGRE units per second.

	public:
	MovingConsist()
		:mSpeed(0.0f)
		{}

	void update(float secondsElapsed){
		float distance = mSpeed*secondsElapsed;
		this->move(distance);
	}

	void setSpeed(float speed){
		mSpeed=speed;
	}

	float getSpeed(){
		return mSpeed;
	}

	/** Moves consist. Stops consist on dead end.
	* @param distance The distance to travel (OGRE units).
		On failure this variable is set to remaining distance.
	* @return True if move was performed, false if dead end was hit.
	*/
	bool move(float & distance)
	{
		if(!Consist::move(distance)) {
			mSpeed = 0.0f;
			return false;
		} else {
			return true;
		}
	}
};

} // namespace OgreRails

#endif // Include guard

