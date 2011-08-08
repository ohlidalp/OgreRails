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

#include "OgreSceneNode.h"
#include "OgreMath.h"
#include "OgreVector3.h"
#include "OgreMatrix3.h"
#include "OgreEntity.h"

#include "SegmentGraphicFactory.hpp"
#include "Segment.hpp"
#include "../util/UniqueIdGenerator.hpp"

namespace OgreRails {

namespace Paths {

SegmentGraphicInstance* SegmentGraphicFactory::instance(OgreRails::Coords const & pos, Segment::Direction dir)
{
	Ogre::Entity* ent = mGraphic->clone(
		mGraphic->getName() + UniqueIdGenerator::getSingleton().getAsHexadecimal());
	Ogre::SceneNode* node = mGround->createChildSceneNode(pos.toOgreUnits());
	node->attachObject(ent);
	switch (dir) {
		case Segment::DIRECTION_Y:
			node->yaw(Ogre::Radian(-Ogre::Math::HALF_PI));
			break;
		case Segment::DIRECTION_NEG_X:
			node->yaw(Ogre::Radian(Ogre::Math::PI));
			break;
		case Segment::DIRECTION_NEG_Y:
			node->yaw(Ogre::Radian(Ogre::Math::HALF_PI));
			break;
		default:;
	}
	if (mRotate != Ogre::Vector3::ZERO) {
		node->yaw(Ogre::Radian(mRotate.y));
		node->roll(Ogre::Radian(mRotate.z));
		node->pitch(Ogre::Radian(mRotate.x));
	}
	node->translate(Ogre::Matrix3::IDENTITY, mOffset.x, mOffset.y, mOffset.z, Ogre::SceneNode::TS_LOCAL);
	return new SegmentGraphicInstance(ent, node);
}

} // Namespace Path

} // Namespace OgreRails
