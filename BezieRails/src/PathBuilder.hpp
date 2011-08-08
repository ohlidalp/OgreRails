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

#ifndef OgreRails_PathBuilder_INCLUDED
#define OgreRails_PathBuilder_INCLUDED

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

#include "path/Path.hpp"
#include "path/SegmentFactory.hpp"

namespace OgreRails {

/** Builds a single path and places meshes.
*/
class PathBuilder
{
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* mGround;
	Paths::Endpoint* mEntryEndpoint;
	Coords mStartCoords;
	Coords mCurrCoords;
	Paths::Segment::Direction mDir;
	Paths::Path* mPath;

	public:

	PathBuilder(Ogre::SceneManager* sceneMgr, Ogre::SceneNode* ground)
		:mSceneMgr(sceneMgr), mGround(ground), mEntryEndpoint(0), mStartCoords(0u,0u,0u)
	{
	}

	void start (Paths::Endpoint * ep, Coords const & coords, Paths::Segment::Direction dir)
	{
		mEntryEndpoint = ep;
		mStartCoords = coords;
		mCurrCoords = coords;
		mDir = dir;
		mPath = new Paths::Path();
		mPath->setEndpoint(ep, Paths::Path::END_ENTRY);
	}

	Paths::Path* end(Paths::Endpoint * ep)
	{
		mPath->setEndpoint(ep, Paths::Path::END_EXIT);
		return mPath;
	}

	void build(Paths::SegmentFactory* factory, int count = 1)
	{
		using namespace Paths;
		for (int i = 0; i < count; i++) {
			mPath->addSegment(factory->instance(mCurrCoords, mDir), Paths::Path::END_EXIT);
			factory->getPrototype()->advance(mCurrCoords, mDir);
		}
	}
};

} // namespace OgreRails

#endif // Include guard
