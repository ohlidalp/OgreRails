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

#ifndef OgreRails_TwoBogieVehicle_INCLUDED
#define OgreRails_TwoBogieVehicle_INCLUDED

#include "../util/UniqueIdGenerator.hpp"
#include "../path/Slider.hpp"
#include "Vehicle.hpp"
#include "../util/DebugConsole.hpp"
#include <sstream> // Debug
#include <iomanip> // Debug


namespace OgreRails {

class TwoBogieVehiclePrototype; // Forward decl.

class TwoBogieVehicle: public Vehicle
{
	friend class TwoBogieVehiclePrototype;


	Ogre::SceneNode* mFrontBogieNode; //< Child of ground node
	Ogre::Entity* mFrontBogie;
	Ogre::SceneNode* mRearBogieNode; //< Child of ground node
	Ogre::Entity* mRearBogie;
	Ogre::SceneNode* mBodyNode; //< Child of front bogie node
	Ogre::Entity* mBody;
	float mLength; //< Vehicle's length (OGRE units)
	float mFrontBogieOffset; //< Front bogie's offset from vehicle's front (OGRE units)
	float mRearBogieOffset; //< Rear bogie's offset from vehicle's front (OGRE units)
	float mBogieHeight; //< (OGRE units)
	float mGapSize; //< Length of gap between vehicles (OGRE units)

	TwoBogieVehicle(
			Ogre::SceneNode* frontBogieNode,
			Ogre::Entity* frontBogie,
			Ogre::SceneNode* rearBogieNode,
			Ogre::Entity* rearBogie,
			Ogre::SceneNode* bodyNode,
			Ogre::Entity* body,
			float gapSize,
			float len,
			float fbOffs,
			float rbOffs,
			float bogieH  ):

			mFrontBogieNode(frontBogieNode),
			mFrontBogie(frontBogie),
			mRearBogieNode(rearBogieNode),
			mRearBogie(rearBogie),
			mBodyNode(bodyNode),
			mBody(body),
			mLength(len),

			mFrontBogieOffset(fbOffs),
			mRearBogieOffset(rbOffs),

			mBogieHeight(bogieH),
			mGapSize(gapSize)
			{
	}

	public:

	/** Updates position of meshes representing this vehicle.
	* @param slider The slider showing the position of vehicle's front.
	* When done, it's moved to vehicle's back.
	*/
	void updatePosition(Paths::Slider& slider, PathSpanList::iterator & pathSpanIt, PathSpanList::iterator & pathSpanEnd)
	{
		Ogre::Vector3 oldPos;
		Ogre::Vector3 newPos;

		// Debug
		slider.getPosition(newPos); // Prints debug info

		// Front bogie
		float distance = -mFrontBogieOffset;
		while ( !slider.move(distance) ) {
			if (pathSpanIt == pathSpanEnd) {
				return;
			}
			slider.snap((*pathSpanIt).first, (*pathSpanIt).second );
			pathSpanIt--;
		}
		slider.getPosition(newPos);
		oldPos = mFrontBogieNode->getPosition();
		mFrontBogieNode->setPosition(newPos);
		mFrontBogieNode->lookAt(oldPos, Ogre::Node::TS_WORLD, Ogre::Vector3::NEGATIVE_UNIT_X);
		//std::cout<<"TwoBogieVehicle::updatePosition() \n\tfront bogie new: "<<printVector(newPos)<<" (old: "<<printVector(oldPos)<<")";
		// Body position
		newPos.y += mBogieHeight;
		mBodyNode->setPosition(newPos);
		// Rear bogie
		distance = -(mRearBogieOffset-mFrontBogieOffset);
		while ( !slider.move(distance) ) {
			if (pathSpanIt == pathSpanEnd) {
				return;
			}
			slider.snap((*pathSpanIt).first, (*pathSpanIt).second );
			pathSpanIt--;
		}
		oldPos = mRearBogieNode->getPosition();
		slider.getPosition(newPos);
		mRearBogieNode->setPosition(newPos);
		mRearBogieNode->lookAt(oldPos, Ogre::Node::TS_WORLD, Ogre::Vector3::NEGATIVE_UNIT_X);
		// Body orientation
		newPos.y += mBogieHeight;
		mBodyNode->lookAt(newPos, Ogre::Node::TS_PARENT, Ogre::Vector3::NEGATIVE_UNIT_X);
		distance = -((mLength-mRearBogieOffset)+mGapSize);
		while ( !slider.move(distance) ) {
			if (pathSpanIt == pathSpanEnd) {
				return;
			}
			slider.snap((*pathSpanIt).first, (*pathSpanIt).second );
			pathSpanIt--;
		}
	}

	void setGapSize(float gapSize)
	{
		mGapSize=gapSize;
	}

	/*void setPosition(Ogre::Vector3 const & pos)
	{
		mBodyNode->setPosition(pos);
	}*/

	float getLength() const
	{
		return mLength;
	}

};

} // namespace OgreRails

#endif // Include guard
