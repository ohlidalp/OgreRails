/*
	Copyright (c) 2000-2009 Torus Knot Software Ltd
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

/** @file This class is a modified ExampleFrameListener from OGRE */

#ifndef OgreRails_FrameListener_INCLUDED
#define OgreRails_FrameListener_INCLUDED

#include <Ogre.h>
#include "OgreStringConverter.h"
#include "OgreException.h"
#include <ExampleApplication.h>

//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

#ifdef USE_RTSHADER_SYSTEM
#include "OgreRTShaderSystem.h"
#endif

#include "CodeConfig.hpp"
#include "vehicles/MovingConsist.hpp"
#include "util/DebugConsole.hpp"
#include <sstream>

namespace OgreRails {

class FrameListener: public Ogre::FrameListener, public Ogre::WindowEventListener
{

protected:
	// OgreRails properties
	OgreRails::MovingConsist* mConsist;

	// Example application
	Camera* mCamera;

	Vector3 mTranslateVector;
	Vector3 mAbsTranslateVector;
	Real mCurrentSpeed;
	Real mCurrentSpeedAbs;
	RenderWindow* mWindow;
	bool mStatsOn;

	String mDebugText;

	unsigned int mNumScreenShots;
	float mMoveScale;
	Degree mRotScale;
	// just to stop toggles flipping too fast
	Real mTimeUntilNextToggle ;
	Radian mRotX, mRotY;
	TextureFilterOptions mFiltering;
	int mAniso;

	int mSceneDetailIndex ;
	Real mScrollSpeed; // Casmera scroll speed (right/left/zoom)
	Real mScrollSpeedAbs; // Camera scroll speed (forward/backward)
	Degree mRotateSpeed;
	Overlay* mDebugOverlay;

	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
	OIS::JoyStick* mJoy;



public:
	// Constructor takes a RenderWindow because it uses that to determine input context
	FrameListener(RenderWindow* win, Camera* cam, bool bufferedKeys = false, bool bufferedMouse = false,
			     bool bufferedJoy = false ) :
		mCamera(cam),
		mTranslateVector(Vector3::ZERO),
		mAbsTranslateVector(Vector3::ZERO),
		mCurrentSpeed(0),
		mWindow(win),
		mStatsOn(true),
		mNumScreenShots(0),
		mMoveScale(0.0f),
		mRotScale(0.0f),
		mTimeUntilNextToggle(0),
		mFiltering(TFO_BILINEAR),
		mAniso(1),
		mSceneDetailIndex(0),
		mScrollSpeed(250),
		mScrollSpeedAbs(250),
		mRotateSpeed(36),
		mDebugOverlay(0),
		mInputManager(0),
		mMouse(0),
		mKeyboard(0),
		mJoy(0)
	{
using namespace Ogre;
		mDebugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");

		LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
		OIS::ParamList paramList;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;

		win->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		paramList.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		//*****************************************
		//Prevent trapping mouse cursor
		//*****************************************
		#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		#else // Linux

		// Option: trap cursor in window
		paramList.insert(std::make_pair(std::string("x11_mouse_grab"),std::string(TRAP_CURSOR?"true":"false")));
		// Option: hide hardware cursor
		paramList.insert(std::make_pair(std::string("x11_mouse_hide"),std::string("false")));
		#endif

		mInputManager = OIS::InputManager::createInputSystem( paramList );

		//Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, bufferedKeys ));
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, bufferedMouse ));
		try {
			mJoy = static_cast<OIS::JoyStick*>(mInputManager->createInputObject( OIS::OISJoyStick, bufferedJoy ));
		}
		catch(...) {
			mJoy = 0;
		}

		//Set initial mouse clipping size
		windowResized(mWindow);

		showDebugOverlay(true);

		//Register as a Window listener
		WindowEventUtilities::addWindowEventListener(mWindow, this);
	}

	void setConsist(OgreRails::MovingConsist* mc){
			mConsist = mc;
	}


#ifdef USE_RTSHADER_SYSTEM
	virtual void processShaderGeneratorInput()
	{
		// Switch to default scheme.
		if (mKeyboard->isKeyDown(OIS::KC_F2))
		{
			mCamera->getViewport()->setMaterialScheme(MaterialManager::DEFAULT_SCHEME_NAME);
			mDebugText = "Active Viewport Scheme: ";
			mDebugText += MaterialManager::DEFAULT_SCHEME_NAME;
		}

		// Switch to shader generator scheme.
		if (mKeyboard->isKeyDown(OIS::KC_F3))
		{
			mCamera->getViewport()->setMaterialScheme(RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
			mDebugText = "Active Viewport Scheme: ";
			mDebugText += RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME;
		}

		// Toggles per pixel per light model.
		if (mKeyboard->isKeyDown(OIS::KC_F4) && mTimeUntilNextToggle <= 0)
		{
			mTimeUntilNextToggle = 1.0;

			static bool userPerPixelLightModel = true;
			RTShader::ShaderGenerator* shaderGenerator = RTShader::ShaderGenerator::getSingletonPtr();
			RTShader::RenderState* renderState = shaderGenerator->getRenderState(RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

			// Remove all global sub render states.
			renderState->reset();

			// Add per pixel lighting sub render state to the global scheme render state.
			// It will override the default FFP lighting sub render state.
			if (userPerPixelLightModel)
			{
				RTShader::SubRenderState* perPixelLightModel = shaderGenerator->createSubRenderState(RTShader::PerPixelLighting::Type);
				renderState->addSubRenderState(perPixelLightModel);

				mDebugText = "Per pixel lighting model applied to shader generator default scheme";
			}
			else
			{
				mDebugText = "Per vertex lighting model applied to shader generator default scheme";
			}

			// Invalidate the scheme in order to re-generate all shaders based technique related to this scheme.
			shaderGenerator->invalidateScheme(RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

			userPerPixelLightModel = !userPerPixelLightModel;
		}

	}

#endif

	//Adjust mouse clipping area
	virtual void windowResized(RenderWindow* rw)
	{
		unsigned int width, height, depth;
		int left, top;
		rw->getMetrics(width, height, depth, left, top);

		const OIS::MouseState &ms = mMouse->getMouseState();
		ms.width = width;
		ms.height = height;
	}

	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(RenderWindow* rw)
	{
		//Only close for window that created OIS (the main window in these demos)
		if( rw == mWindow )
		{
			if( mInputManager )
			{
				mInputManager->destroyInputObject( mMouse );
				mInputManager->destroyInputObject( mKeyboard );
				mInputManager->destroyInputObject( mJoy );

				OIS::InputManager::destroyInputSystem(mInputManager);
				mInputManager = 0;
			}
		}
	}

	virtual ~FrameListener()
	{
		//Remove ourself as a Window listener
		WindowEventUtilities::removeWindowEventListener(mWindow, this);
		windowClosed(mWindow);
	}

	virtual bool processUnbufferedKeyInput(const FrameEvent& evt)
	{
		Real moveScale = mMoveScale;
		Real absMoveScale = mMoveScale;

		if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			moveScale *= 10;

		if(mKeyboard->isKeyDown(OIS::KC_A))
			mTranslateVector.x = -moveScale; // Move camera left

		if(mKeyboard->isKeyDown(OIS::KC_D))
			mTranslateVector.x = moveScale;	// Move camera RIGHT

		if(mKeyboard->isKeyDown(OIS::KC_W) ) {
			// Move camera forward
			Vector3 dir = mCamera->getDirection();
			mAbsTranslateVector.z = absMoveScale * dir.z;
			mAbsTranslateVector.x = absMoveScale * dir.x;
		}
		if(mKeyboard->isKeyDown(OIS::KC_S) ) {
			// Move camera backward
			Vector3 dir = mCamera->getDirection();
			mAbsTranslateVector.z = -absMoveScale * dir.z;
			mAbsTranslateVector.x = -absMoveScale * dir.x;
		}
		if(mKeyboard->isKeyDown(OIS::KC_ADD) ) {
			mTranslateVector.z = -moveScale;	// Zoom in
		}
		if(mKeyboard->isKeyDown(OIS::KC_SUBTRACT) ) {
			mTranslateVector.z = moveScale;	// Zoom out
		}
		/*if(mKeyboard->isKeyDown(OIS::KC_PGUP))
			mTranslateVector.y = moveScale;	// Move camera up

		if(mKeyboard->isKeyDown(OIS::KC_PGDOWN))
			mTranslateVector.y = -moveScale;	// Move camera down*/

		if(mKeyboard->isKeyDown(OIS::KC_RIGHT))
			mCamera->yaw(-mRotScale);

		if(mKeyboard->isKeyDown(OIS::KC_LEFT))
			mCamera->yaw(mRotScale);

		if( mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q) )
			return false;

       	if( mKeyboard->isKeyDown(OIS::KC_F) && mTimeUntilNextToggle <= 0 )
		{
			mStatsOn = !mStatsOn;
			showDebugOverlay(mStatsOn);
			mTimeUntilNextToggle = 1;
		}

		if( mKeyboard->isKeyDown(OIS::KC_T) && mTimeUntilNextToggle <= 0 )
		{
			switch(mFiltering)
			{
			case TFO_BILINEAR:
				mFiltering = TFO_TRILINEAR;
				mAniso = 1;
				break;
			case TFO_TRILINEAR:
				mFiltering = TFO_ANISOTROPIC;
				mAniso = 8;
				break;
			case TFO_ANISOTROPIC:
				mFiltering = TFO_BILINEAR;
				mAniso = 1;
				break;
			default: break;
			}
			MaterialManager::getSingleton().setDefaultTextureFiltering(mFiltering);
			MaterialManager::getSingleton().setDefaultAnisotropy(mAniso);

			showDebugOverlay(mStatsOn);
			mTimeUntilNextToggle = 1;
		}

		if(mKeyboard->isKeyDown(OIS::KC_SYSRQ) && mTimeUntilNextToggle <= 0)
		{
			std::ostringstream ss;
			ss << "screenshot_" << ++mNumScreenShots << ".png";
			mWindow->writeContentsToFile(ss.str());
			mTimeUntilNextToggle = 0.5;
			mDebugText = "Saved: " + ss.str();
		}

		if(mKeyboard->isKeyDown(OIS::KC_R) && mTimeUntilNextToggle <=0)
		{
			mSceneDetailIndex = (mSceneDetailIndex+1)%3 ;
			switch(mSceneDetailIndex) {
				case 0 : mCamera->setPolygonMode(PM_SOLID); break;
				case 1 : mCamera->setPolygonMode(PM_WIREFRAME); break;
				case 2 : mCamera->setPolygonMode(PM_POINTS); break;
			}
			mTimeUntilNextToggle = 0.5;
		}

		static bool displayCameraDetails = false;
		if(mKeyboard->isKeyDown(OIS::KC_P) && mTimeUntilNextToggle <= 0)
		{
			displayCameraDetails = !displayCameraDetails;
			mTimeUntilNextToggle = 0.5;
			if (!displayCameraDetails)
				mDebugText = "";
		}

		// Print camera details
		if(displayCameraDetails)
			mDebugText = "P: " + StringConverter::toString(mCamera->getDerivedPosition()) +
						 " " + "O: " + StringConverter::toString(mCamera->getDerivedOrientation());

		// Return true to continue rendering
		return true;
	}

	virtual bool processUnbufferedMouseInput(const FrameEvent& evt)
	{
/*
		// Rotation factors, may not be used if the second mouse button is pressed
		// 2nd mouse button - slide, otherwise rotate
		const OIS::MouseState &ms = mMouse->getMouseState();
		if( ms.buttonDown( OIS::MB_Right ) )
		{
			mTranslateVector.x += ms.X.rel * 0.13;
			mTranslateVector.y -= ms.Y.rel * 0.13;
		}
		else
		{
			mRotX = Degree(-ms.X.rel * 0.13);
			mRotY = Degree(-ms.Y.rel * 0.13);
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
            // Adjust the input depending upon viewport orientation
            Radian origRotY, origRotX;
            switch(mCamera->getViewport()->getOrientation())
            {
                case Viewport::OR_LANDSCAPELEFT:
                    origRotY = mRotY;
                    origRotX = mRotX;
                    mRotX = origRotY;
                    mRotY = -origRotX;
                    break;
                case Viewport::OR_LANDSCAPERIGHT:
                    origRotY = mRotY;
                    origRotX = mRotX;
                    mRotX = -origRotY;
                    mRotY = origRotX;
                    break;

                // Portrait doesn't need any change
                case Viewport::OR_PORTRAIT:
                default:
                    break;
            }
#endif
		}
*/
		return true;
	}

	virtual void moveCamera()
	{
		// Make all the changes to the camera
		// Note that YAW direction is around a fixed axis (freelook style) rather than a natural YAW
		//(e.g. airplane)
		mCamera->yaw(mRotX);
		mCamera->pitch(mRotY);
		mCamera->moveRelative(mTranslateVector);
		mCamera->move(mAbsTranslateVector);
	}

	virtual void showDebugOverlay(bool show)
	{
		if (mDebugOverlay)
		{
			if (show)
				mDebugOverlay->show();
			else
				mDebugOverlay->hide();
		}
	}

	// Override frameRenderingQueued event to process that (don't care about frameEnded)
	bool frameRenderingQueued(const FrameEvent& evt)
	{

		DebugConsole::getSingleton().reset();

		if(mWindow->isClosed())	return false;

		//Need to capture/update each device
		mKeyboard->capture();
		mMouse->capture();
		if( mJoy ) mJoy->capture();

		bool buffJ = (mJoy) ? mJoy->buffered() : true;

    	Ogre::Vector3 lastMotion = mTranslateVector;
		Ogre::Vector3 lastAbsMotion = mAbsTranslateVector;

		//Check if one of the devices is not buffered
		if( !mMouse->buffered() || !mKeyboard->buffered() || !buffJ )
		{
			// one of the input modes is immediate, so setup what is needed for immediate movement
			if (mTimeUntilNextToggle >= 0)
				mTimeUntilNextToggle -= evt.timeSinceLastFrame;

			// Move about 100 units per second
			mMoveScale = mScrollSpeed * evt.timeSinceLastFrame;
			// Take about 10 seconds for full rotation
			mRotScale = mRotateSpeed * evt.timeSinceLastFrame;

			mRotX = 0;
			mRotY = 0;
			mTranslateVector = Ogre::Vector3::ZERO;
			mAbsTranslateVector = Ogre::Vector3::ZERO;

		}

		//Check to see which device is not buffered, and handle it
#if OGRE_PLATFORM != OGRE_PLATFORM_IPHONE
		if( !mKeyboard->buffered() )
			if( processUnbufferedKeyInput(evt) == false )
				return false;

#ifdef USE_RTSHADER_SYSTEM
		processShaderGeneratorInput();
#endif

#endif
		if( !mMouse->buffered() )
			if( processUnbufferedMouseInput(evt) == false )
				return false;

		// Side scroll / zoom speed
    	if (mTranslateVector == Ogre::Vector3::ZERO) {
			mCurrentSpeed = 0.0f;
		}
		else {
			mCurrentSpeed  = mScrollSpeed;
		}

		// Abs scroll speed
		if (mAbsTranslateVector == Ogre::Vector3::ZERO) {
			mCurrentSpeedAbs = 0.0f;
		} else {
			mCurrentSpeedAbs = mScrollSpeedAbs;
		}


		mTranslateVector *= mCurrentSpeed * evt.timeSinceLastFrame;
		mAbsTranslateVector *= mCurrentSpeedAbs * evt.timeSinceLastFrame;


		if( !mMouse->buffered() || !mKeyboard->buffered() || !buffJ )
			moveCamera();

		updateConsists(evt);

		return true;
	}

	bool frameEnded(const FrameEvent& evt)
	{
		updateStats();
		return true;
	}

	void updateConsists(const FrameEvent& evt)
	{
		mConsist->update(evt.timeSinceLastFrame);
		mConsist->updateCoords();
	}

	protected:
	virtual void updateStats(void)
	{
		using namespace Ogre;
		static String currFps = "Current FPS: ";
		static String avgFps = "Average FPS: ";
		static String bestFps = "Best FPS: ";
		static String worstFps = "Worst FPS: ";
		static String tris = "Triangle Count: ";
		static String batches = "Batch Count: ";

		// update stats when necessary
		try {
			OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
			OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
			OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
			OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

			const RenderTarget::FrameStats& stats = mWindow->getStatistics();
			guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
			guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
			guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS)
				+" "+StringConverter::toString(stats.bestFrameTime)+" ms");
			guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)
				+" "+StringConverter::toString(stats.worstFrameTime)+" ms");

			OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
			guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));

			OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
			guiBatches->setCaption(batches + StringConverter::toString(stats.batchCount));

			OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
			guiDbg->setCaption(mDebugText);
		}
		catch(...) { /* ignore */ }
	}

};

} // Namespace OgreRails

#endif // Include guard
