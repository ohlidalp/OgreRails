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

//-----------------------------------------------------------------------------
// Original file obtained from Ogre wiki.
// Author: Lonewolff
//-----------------------------------------------------------------------------

#ifndef OgreRails_Util_DebugConsole_INCLUDED
#define OgreRails_Util_DebugConsole_INCLUDED

#include "../CodeConfig.hpp"
#include "OgreTextAreaOverlayElement.h"
#include "OgreStringConverter.h"
#include "OgreSingleton.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"

namespace OgreRails {

class DebugConsole : public Ogre::Singleton<DebugConsole>
{
public:
	DebugConsole()
	{
		using namespace Ogre;
		olm=OverlayManager::getSingletonPtr();

		panel=static_cast<OverlayContainer*>(olm->createOverlayElement("Panel","GUI"));
		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(0,0);
		panel->setDimensions(1.0f,1.0f);
		overlay=olm->create("GUI_OVERLAY");
		overlay->add2D(panel);
		szElement="DebugConsole";
		overlay=olm->getByName("GUI_OVERLAY");
		panel=static_cast<OverlayContainer*>(olm->getOverlayElement("GUI"));
		mTextArea=static_cast<TextAreaOverlayElement*>(olm->createOverlayElement("TextArea",szElement));
		panel->addChild(mTextArea);
		overlay->show();
		mTextArea->setFontName("DebugTextAreaFont");
		mTextArea->setDimensions(1.0f,1.0f);
		mTextArea->setMetricsMode(Ogre::GMM_RELATIVE);
		mTextArea->setCharHeight(0.03f);
	}
	~DebugConsole()
	{
		szElement="DebugConsole";
		olm->destroyOverlayElement(szElement);
		olm->destroyOverlayElement("GUI");
		olm->destroy("GUI_OVERLAY");
	}

	void print(Ogre::String s)
	{
		mTextArea->setCaption(mTextArea->getCaption() + s);
	}

	void reset()
	{
		mTextArea->setCaption(Ogre::String());
	}

	void setPos(float x,float y)
	{
		mTextArea->setPosition(x,y);
	}

	void setCol(float R,float G,float B,float I)
	{
		mTextArea->setColour(Ogre::ColourValue(R,G,B,I));
	}

private:
	Ogre::OverlayManager *olm;
	Ogre::OverlayContainer *panel ;
	Ogre::Overlay *overlay;
	Ogre::TextAreaOverlayElement *mTextArea;
	Ogre::String szElement;
};

} // namespace

#endif // Include guard





