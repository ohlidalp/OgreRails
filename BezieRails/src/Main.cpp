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

#include "Application.hpp"

void displayException(const char* text){
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, text, "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else

        std::cerr << "An exception has occured: " << text;
#endif
}

// ----------------------------------------------------------------------------
// Main function, just boots the application object
// ----------------------------------------------------------------------------
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char **argv)
#endif
{
    // Create application object
    OgreRails::Application app;

    try
    {
        app.go();
    }
    catch( Exception& e )
    {
		displayException(e.getFullDescription().c_str());
    }
    catch(std::exception e){
		displayException(e.what());
    }

    return 0;
}
