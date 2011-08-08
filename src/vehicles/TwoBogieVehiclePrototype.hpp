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

#ifndef OgreRails_TwoBogieVehiclePrototype
#define OgreRails_TwoBogieVehiclePrototype

#include "../util/UniqueIdGenerator.hpp"
#include "TwoBogieVehicle.hpp"

namespace OgreRails {

class TwoBogieVehiclePrototype
{
	Ogre::SceneNode* mTargetGround; //< A parent node for creating bogie nodes.
	std::string mFrontBogieEntityName;
	std::string mRearBogieEntityName;
	std::string mBodyEntityName;
	Ogre::Entity* mFrontBogie;
	Ogre::Entity* mRearBogie;
	Ogre::Entity* mBody;
	Ogre::Vector3 mFrontBogieScale;
	Ogre::Vector3 mRearBogieScale;
	Ogre::Vector3 mBodyScale;
	float mLength; //< Vehicle's length (OGRE units)
	float mFrontBogieOffset; //< Front bogie's offset from vehicle's front (OGRE units)
	float mRearBogieOffset; //< Rear bogie's offset from vehicle's front (OGRE units)
	float mBogieHeight; //< (OGRE units)
	float mFrontGapSize; //< Default length of gap between vehicles (OGRE units) Unused
	float mRearGapSize; //< Default length of gap between vehicles (OGRE units) Unused
	float mGapSize;
	Ogre::Vector3 mBodyRotate; //< Initial rotation of a body instance

	public:

	TwoBogieVehiclePrototype(
			Ogre::SceneNode* targetGround,
			const std::string& frontBogieEntityName,
			const std::string& rearBogieEntityName,
			const std::string& bodyEntityName,
			Ogre::Entity* frontBogie,
			Ogre::Entity* rearBogie,
			Ogre::Entity* body,
			const Ogre::Vector3& frontBogieScale,
			const Ogre::Vector3& rearBogieScale,
			const Ogre::Vector3& bodyScale,
			float length,
			float frontBogieOffset,
			float rearBogieOffset,
			float bogieHeight,
			float gapSize):

			mTargetGround(targetGround),
			mFrontBogieEntityName(frontBogieEntityName),
			mRearBogieEntityName(rearBogieEntityName),
			mBodyEntityName(bodyEntityName),
			mFrontBogie(frontBogie),
			mRearBogie(rearBogie),
			mBody(body),
			mFrontBogieScale(frontBogieScale),
			mRearBogieScale(rearBogieScale),
			mBodyScale(bodyScale),
			mLength(length),
			mFrontBogieOffset(frontBogieOffset),
			mRearBogieOffset(rearBogieOffset),
			mBogieHeight(bogieHeight),
			mGapSize(gapSize),
			mBodyRotate(0,0,0)
			{
	}

	TwoBogieVehicle* instance(){
		UniqueIdGenerator& gen = UniqueIdGenerator::getSingleton();
		Entity* fBogie = mFrontBogie->clone(mFrontBogieEntityName+gen.getAsHexadecimal());
		SceneNode* fBogieN = mTargetGround->createChildSceneNode();
        fBogieN->attachObject(fBogie);
        fBogieN->setScale(mFrontBogieScale);

        Entity* rBogie = mRearBogie->clone(mRearBogieEntityName+gen.getAsHexadecimal());
        SceneNode* rBogieN = mTargetGround->createChildSceneNode();
        rBogieN->attachObject(rBogie);
		rBogieN->setScale(mRearBogieScale);

        Entity* body = mBody->clone(mBodyEntityName+gen.getAsHexadecimal());
        SceneNode* bodyN = mTargetGround->createChildSceneNode(Ogre::Vector3(0.0f,1,0.0f));
        bodyN->setScale(mBodyScale);
        bodyN->attachObject(body);
		// Initial body rotation
		//bodyN->roll(Ogre::Radian(-Ogre::Math::HALF_PI));

		if (mBodyRotate.x) {
			bodyN->rotate(Ogre::Vector3::UNIT_X, Ogre::Radian(mBodyRotate.x));
		}
		if (mBodyRotate.y) {
			bodyN->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(mBodyRotate.y));
		}
		if (mBodyRotate.z) {
			bodyN->rotate(Ogre::Vector3::UNIT_Z, Ogre::Radian(mBodyRotate.z));
		}

		return new TwoBogieVehicle(	fBogieN,fBogie,rBogieN,rBogie,bodyN,body,mGapSize,mLength,mFrontBogieOffset,mRearBogieOffset,mBogieHeight );
	}

	float getLength(){
		return mLength;
	}

	float getBogiesDistance(){
		return mRearBogieOffset-mFrontBogieOffset;
	}

	float getRearBogieInvertedOffset(){
		return mLength-mRearBogieOffset;
	}

	float getFrontBogieOffset(){
		return mFrontBogieOffset;
	}

	/** Set initial rotation of a body instance
	*/
	void setBodyRotate(Ogre::Vector3 const & rot)
	{
		mBodyRotate = rot;
	}
};

} // namespace OgreRails

#endif // Include guard
