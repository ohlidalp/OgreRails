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

#ifndef OgreRails_CodeConfig_INCLUDED
#define OgreRails_CodeConfig_INCLUDED

/** @file Compiler macros and constants */

namespace OgreRails {

/** This program measures length of bezier curves by splitting them
* into strip of lines and measuring those lines.
* This macro defines the relative length of one line.
*/
const float BCURVE_DEFAULT_MEASURING_STEP(0.01f);

/** Max length of TrailSegment's curve sample (OGRE units)
*
*/
const float TRAIL_SAMPLE_MAX_LEN(0.5);
const int TRAIL_MIN_SAMPLES(10);

// Trap mouse cursor in window?
const bool TRAP_CURSOR(false);

const float SNAPGRID_H_SPACE(40.0f);

const int VERSION_MAJOR(0);
const int VERSION_MINOR(1);

} // namespace OgreRails

#endif // Include guard
