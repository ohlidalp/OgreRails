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

#ifndef OgreRails_Consist_INCLUDED
#define OgreRails_Consist_INCLUDED

#include "TwoBogieVehiclePrototype.hpp"
#include "../path/PathChooser.hpp"
#include "../path/Slider.hpp"
#include "../util/DebugConsole.hpp"

namespace OgreRails {

/** A formation of rail vehicles
* Moves along a path with constant gaps between cars.
*/
class Consist
{
	/// Slider of this consist.
	Paths::Slider mSlider;

	/// Object to query route info.
	std::auto_ptr<Paths::PathChooser> mPathChooser;

	/// List of paths this consist spans over (current path not included)
	PathSpanList mPathSpan;

	/// Vehicles in this consist
	std::list<Vehicle*> mVehicles;

	/// Length of this consist
	float mLength;

	public:

	Consist():
		mPathChooser(0),
		mLength(0)
	{}

	virtual ~Consist(){}

	void addVehicle(Vehicle* v)
	{
		mVehicles.push_back(v);
		mLength += v->getLength();
	}

	Paths::Slider const & getSlider() const {
		return mSlider;
	}

	void snap(Paths::Path* path, Paths::Path::End which = Paths::Path::END_ENTRY) {
		mSlider.snap(path, which);
	}

	void turnAround(){
		//mFrontTraveller.turnAround();
	}

	float getLength() const
	{
		return mLength;
	}

	/**
	* @param distance The distance to travel. On failure this variable is set to remaining distance.
	* @return True if move was performed, false if dead end was hit.
	*/
	bool move(float & distance){
		/*
        std::stringstream s;
		s << "Consist::move() segment: " << seg
			<< " seg.len.: " << seg->getLength()
			<< " offset: " << mSlider.getSegOffset()
			<< " distance: " << distance << std::endl;
		DebugConsole::getSingleton().print(s.str());
		*/

		// Move
		while (!mSlider.move(distance)) {
			/*
			std::cout << "Consist::move() Remaining distance: " << distance << std::endl;
			*/
			// Jump to next path
			Paths::Path * currPath = mSlider.getPath();
			Paths::Path::End lastEnd = distance < 0.0f ? Paths::Path::END_ENTRY : Paths::Path::END_EXIT;
			Paths::Endpoint * endpoint = currPath->getEndpoint(lastEnd);
			if (endpoint->isDeadEnd()) {
				return false;
			}
			Paths::Path * nextPath = mPathChooser->getNextPath(*endpoint, currPath);
			mSlider.snap(nextPath, nextPath->whichEndpoint(endpoint));

			// == Update the path span ==
			mPathSpan.add(currPath, lastEnd);
			float chainLength(0.0f);
			PathSpanList::iterator it = mPathSpan.begin();
			PathSpanList::iterator endIt = mPathSpan.end();
			while (chainLength < mLength && it != endIt ) {
				chainLength += (*it).first->getLength();
				it++;
			}
			mPathSpan.erase(it, endIt);
		}
		distance = 0.0f;
		return true;
	}

	void updateCoords()
	{
		Paths::Slider shunter = mSlider;
		PathSpanList::iterator spanIt = mPathSpan.begin();
		PathSpanList::iterator spanEnd = mPathSpan.end();
		for( std::list<Vehicle*>::iterator it = mVehicles.begin();
			it!=mVehicles.end();
			it++){
			(*it)->updatePosition(shunter, spanIt, spanEnd);
			}
	}

	void setPathChooser(Paths::PathChooser* chooser) {
		mPathChooser = std::auto_ptr<Paths::PathChooser>(chooser);
	}

};

} // namespace OgreRails

#endif // Include guard
