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
	along with OgreRails. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OgreRails_Application_INCLUDED
#define OgreRails_Application_INCLUDED

#include "OgreTextAreaOverlayElement.h"
#include <memory>

#include "FrameListener.hpp"
#include "CodeConfig.hpp"
#include "path/CurveSegmentFactory.hpp"
#include "path/StraightSegmentFactory.hpp"
#include "vehicles/MovingConsist.hpp"
#include "util/DebugConsole.hpp"

namespace OgreRails {

class Application : public ExampleApplication
{
	SceneNode* mGroundNode;
	FrameListener* mFrameListener;
    //SceneNode* mFakeGround; //< For storing cloneable instances of stuff.

	std::auto_ptr<Paths::StraightSegmentFactory> mStraightSF;
	std::auto_ptr<Paths::CurveSegmentFactory> mRight6SF;
	std::auto_ptr<Paths::CurveSegmentFactory> mLeft6SF;

	std::auto_ptr<TwoBogieVehiclePrototype> mLocoPrototype;
	std::auto_ptr<TwoBogieVehiclePrototype> mWagonPrototype;
	std::auto_ptr<MovingConsist> mConsist;
	std::auto_ptr<Paths::PathChooser> mPathChooser;

	std::list<Paths::Path*> mPaths;
	std::list<Paths::Endpoint*> mEndpoints;

	//std::auto_ptr<Ogre::TextAreaOverlayElement> mDebugTextArea;
	std::auto_ptr<DebugConsole> mDebugConsole;

public:
    // Basic constructor
	Application():
		mGroundNode(0),
		mFrameListener(0){}

protected:

    // Just override the mandatory create scene method
    void createScene(void);

	// Overrides ExampleApplication method.
	// called after createscene, but I need it made earlier
    void createFrameListener(){}

	// Creates frame listener when I want it.
    void createFrameListener_Custom()
    {
        mFrameListener = new FrameListener(mWindow, mCamera);
        mFrameListener->showDebugOverlay(true);
        mRoot->addFrameListener(mFrameListener);
    }

    void customizeScene();

	void destroyScene();

};

} // namespace

#endif // Include guard
