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

#ifndef OgreRails_Paths_SegmentGraphicFactory_INCLUDED
#define OgreRails_Paths_SegmentGraphicFactory_INCLUDED

#include <memory>
#include "OgreVector3.h"

#include "SegmentGraphicInstance.hpp"
#include "../util/Coords.hpp"
#include "Segment.hpp"

namespace OgreRails {

namespace Paths {

/** Factory for graphical representations of path segments.
*/
class SegmentGraphicFactory
{
	std::auto_ptr<Ogre::Entity> mGraphic;
	Ogre::Vector3 mOffset;
	Ogre::Vector3 mRotate;
	Ogre::SceneNode* mGround;

	public:

	virtual ~SegmentGraphicFactory(){}

	/**
	* @param graphic The Entity to be reproduced. This class takes ownership.
	* @param offset Relative position to segment's pivot
	* @param rotate Initial rotation of the produced SceneNode. Default = zero vector.
	*/
	SegmentGraphicFactory(
			Ogre::SceneNode* ground, Ogre::Entity* graphic,
			Ogre::Vector3 const & offset, Ogre::Vector3 rotate = Ogre::Vector3::ZERO) :
		mGraphic(graphic), mOffset(offset), mRotate(rotate), mGround(ground)
	{
	}

	/** Create and place new segment graphic.
	* @param pos Segment's snapgrid position
	* @param dir Segment's direction
	*/
	SegmentGraphicInstance* instance(Coords const & pos, Segment::Direction dir);

};

} // namespace Paths

} // namespace OgreRails

#endif // Include guard
