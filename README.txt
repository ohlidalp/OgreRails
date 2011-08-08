OgreRails README
________________________________________________________________________________

About
=====

OgreRails is a very simple and minimal train-building strategic game.

You enter a small, flat world with some towns and industries and build your
railroad network.

The purpose of this project is to prototype and test railroad and train
implementation under OGRE engine.

Roadmap
=======
Current version: 0.1

0.1 Working rails and trains
0.2 Direct single-track construction GUI
0.3 Train GUI windows, train reversing, train lifting and placing functionality (LOMO-like)
0.4 Train construction, modification and removal GUI
0.5 Rail crossings
0.6 Rail waypoints and pathfinding
0.7 Rail signals
0.8 High track
0.9 High track bridge graphics
1.0 Final touches

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
+:          Zoom in
-:          Zoom out
R:          Render mode

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

OgreRail's track system is a graph, where vertices are represented by
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
