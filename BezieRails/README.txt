OgreRails README
________________________________________________________________________________

About
=====

OgreRails is a very simple and minimal train-building strategic game.

You enter a small, flat world with some towns and industries and build your
railroad network.

The purpose of this project is to prototype and test railroad and train
implementation under OGRE engine.

The name originates from Bezier curves, which was the original plan for
implementing tracks. However, this approach was dropped in favor of
"Locomotion"-like track system.

Controls
========

Viewport
--------

W:          Forward
S:          Backward
A:          Step left
D:          Step right
RightArrow: Rotate right
LeftArrow:  Rotate left
PgUp:     Move upwards
PgDown:   Move downwards
F:        Toggle frame rate stats on/off
R:        Render mode
T:        Cycle texture filtering
	   Bilinear, Trilinear, Anisotropic(8)
P:        Toggle on/off display of camera position / orientation
F2:	   Set the main viewport material scheme to default material manager scheme.
F3:	   Set the main viewport material scheme to shader generator default scheme.
F4:	   Toggle default shader generator lighting model from per vertex to per pixel.

Development
===========

Game world
----------

1 Meter of length equals 10 OGRE units (chosen for simplicity)

The map is flat and represented by one 3D plane.
The size of the world is 1000x1000 tiles (4x4 km)
Tile size is 40 OGRE units (4x4 meters)


Track system
------------

BR's track system is a graph, where vertices are represented by
OgreRails::Path::Endpoint and edges are OgreRails::Path::Path

Path consists of a series of segments, each represented by
OgreRails::Path::SegmentInstance. These segments are prefabricated pieces
ob Bezier curves with additional parameters, for instance graphical
representation. These common parameters are stored in
OgreRails::Path::Segment

Segments are snapped to "snapgrid" - a 3D grid (terrain independent)
of points in space. Horizontal space between points is 4 ogre units.

Path movement
-------------

There are two separate operations to movement:
* The movement itself - it's actually just adding/substracting floats and
  swapping pointers. Cheap
* Coordinate updates - may get expensive
