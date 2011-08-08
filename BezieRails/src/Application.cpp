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
#include "path/StraightSegment.hpp"
#include "path/CurveSegment.hpp"
#include "path/Endpoint.hpp"
#include "BlindPathChooser.hpp"
#include "OgreOverlayElementFactory.h"
#include "PathBuilder.hpp"

void OgreRails::Application::customizeScene(){
	using namespace Ogre;
	// Create frame listener
	this->createFrameListener_Custom();

	Vector3 camInitPos(-5 * SNAPGRID_H_SPACE, 2000.0f, -5 * SNAPGRID_H_SPACE);
	Vector3 camLookVec(40.0f * SNAPGRID_H_SPACE, -2000.0f, 40.0f * SNAPGRID_H_SPACE);
	mCamera->setPosition(camInitPos);
	mCamera->lookAt(camInitPos + camLookVec);

	mDebugConsole = std::auto_ptr<OgreRails::DebugConsole>(new OgreRails::DebugConsole());
	DebugConsole::getSingleton().setPos(0.005f,0.005f);        // Text position, using relative co-ordinates
	DebugConsole::getSingleton().setCol(0.0f,0.0f,0.0f,1.0f); // Text colour (Red, Green, Blue, Alpha)

	mGroundNode = mSceneMgr->getRootSceneNode();
	//mFakeGround = mSceneMgr->createSceneNode();
	// create a floor mesh resource
	MeshManager::getSingleton().createPlane(
		"FlatGroundPlane",          // const String & name,
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, // The name of the resource group to assign the mesh to
		Plane(Vector3::UNIT_Y, 0), // The orientation of the plane and distance from the origin
		1000.0f * SNAPGRID_H_SPACE, // Real width, The width of the plane in world coordinates
		1000.0f * SNAPGRID_H_SPACE,
		20,     // int xsegments = 1, The number of segments to the plane in the x direction
		20,
		true,  // normals If true, normals are created perpendicular to the plane
		1,     // unsigned short numTexCoordSets = 1,
		       // The number of 2D texture coordinate sets created - by default the corners are created to be the corner of the texture.
		100,     //  Real uTile = 1.0f, The number of times the texture should be repeated in the u direction
		100,
		Vector3::UNIT_Z); // upVector 	The 'Up' direction of the plane.

	// create a ground entity, give it a material, and place it at the origin
	Entity* floorEntity = mSceneMgr->createEntity("Ground", "FlatGroundPlane");
	floorEntity->setMaterialName("OgreRails/GrassTile");
	floorEntity->setCastShadows(false);
	SceneNode* floorNode = mGroundNode->createChildSceneNode(
		Vector3(500.0f * SNAPGRID_H_SPACE, 0.0f, 500.0f * SNAPGRID_H_SPACE));
	floorNode->attachObject(floorEntity);

	using namespace OgreRails::Paths;

	// Prepare track segments
	mStraightSF = std::auto_ptr<StraightSegmentFactory> (
		new StraightSegmentFactory(
			new StraightSegment(1u, Ogre::Vector3(SNAPGRID_H_SPACE, 0.0f, 0.0f))));
	mRight6SF = std::auto_ptr<CurveSegmentFactory>(
		new CurveSegmentFactory(new CurveSegment(6u, Segment::TURN_RIGHT)));
	mLeft6SF = std::auto_ptr<CurveSegmentFactory>(
		new CurveSegmentFactory(new CurveSegment(6u, Segment::TURN_LEFT)));

	// Build the track
	std::auto_ptr<PathBuilder> builder(new PathBuilder(mSceneMgr, floorNode));
	Endpoint* endpoint = new Endpoint();
	mEndpoints.push_back(endpoint);

	builder->start(endpoint, Coords(45u, 45u), Segment::DIRECTION_Y);

	// x
	builder->build(mRight6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mRight6SF.get());

	builder->build(mLeft6SF.get());

	// neg y
	builder->build(mRight6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mRight6SF.get());

	builder->build(mLeft6SF.get());

	// neg x
	builder->build(mRight6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mRight6SF.get());

	builder->build(mLeft6SF.get());

	// y
	builder->build(mRight6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mRight6SF.get());

	builder->build(mLeft6SF.get());

	mPaths.push_back(builder->end(endpoint));

	using namespace Ogre;

	// Hardcoded 3d model properties.
	// Temporary.
	const float LOCO363_SCALE_S(5.23796113);
	const Ogre::Vector3 LOCO363_SCALE_V(LOCO363_SCALE_S,LOCO363_SCALE_S,LOCO363_SCALE_S);
	const float LOCO363_BOGIE_2_NOSE_DISTANCE(41.95390595);
	const float LOCO363_LENGTH(167.4);
	const float LOCO363_BOGIE_HEIGHT(9.30261896);
	const float CAR_BOGIE2NOSE(32.075f);
	const float CAR_LEN(245.0f);
	const Ogre::Vector3 CAR_SCALE_V(10,10,10);

	// Create vehicle prototypes
	Entity* loco = mSceneMgr->createEntity("loco363", "An00biS_Loco363.mesh");
	Entity* bogie = mSceneMgr->createEntity("loco363-bogie", "An00biS_Loco363_Bogie.mesh");
	mLocoPrototype = std::auto_ptr<TwoBogieVehiclePrototype> (new TwoBogieVehiclePrototype(
			mGroundNode,
			std::string("loco363-front-bogie"),
			std::string("loco363-rear-bogie"),
			std::string("loco363-body"),
			bogie,
			bogie,
			loco,
			LOCO363_SCALE_V,
			LOCO363_SCALE_V,
			LOCO363_SCALE_V,
			LOCO363_LENGTH,
			LOCO363_BOGIE_2_NOSE_DISTANCE,
			LOCO363_LENGTH-LOCO363_BOGIE_2_NOSE_DISTANCE,
			LOCO363_BOGIE_HEIGHT,
			10)); // gap size
	//mLocoPrototype->setBodyRotate(Ogre::Vector3(Ogre::Real(0), Ogre::Real(0), -Ogre::Math::HALF_PI));

	Entity* wagon = mSceneMgr->createEntity("passenger-car", "An00biS_PassengerCarBdmtee.mesh");
	Entity* wagonBogie = mSceneMgr->createEntity("passenger-bogie", "An00biS_PassengerCarBdmtee_Bogie.mesh");
	mWagonPrototype = std::auto_ptr<TwoBogieVehiclePrototype> (new TwoBogieVehiclePrototype(
			mGroundNode,
			std::string("passenger-car-front-bogie"),
			std::string("passenger-car-rear-bogie"),
			std::string("passenger-car-body"),
			wagonBogie,
			wagonBogie,
			wagon,
			CAR_SCALE_V,
			CAR_SCALE_V,
			CAR_SCALE_V,
			CAR_LEN,
			CAR_BOGIE2NOSE, // bogie to nose distance
			CAR_LEN-CAR_BOGIE2NOSE,
			8.09f, // bogie height
			10.0f));
	//mWagonPrototype->setBodyRotate(Ogre::Vector3(Ogre::Real(0), Ogre::Math::PI, Ogre::Real(0)));

	OgreRails::MovingConsist* consist = 0;
	OgreRails::TwoBogieVehiclePrototype* locoProto = 0;
	mConsist = std::auto_ptr<MovingConsist> (new OgreRails::MovingConsist());
	consist = mConsist.get();
	locoProto = mLocoPrototype.get();
	consist->addVehicle(locoProto->instance());
	mConsist->addVehicle(mWagonPrototype->instance());
	mConsist->addVehicle(mWagonPrototype->instance());
	mConsist->snap(mPaths.front());
	mConsist->setSpeed(150.0f);
	mPathChooser = std::auto_ptr<OgreRails::BlindPathChooser>(new OgreRails::BlindPathChooser());
	mConsist->setPathChooser(mPathChooser.get());

	mFrameListener->setConsist(mConsist.get());
}

// Just override the mandatory create scene method
void OgreRails::Application::createScene(void)
{
	using namespace Ogre;
	// Create the SkyBox
	mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");

	// Create a light
	Light* myLight = mSceneMgr->createLight("OgreRails-Sun");
	myLight->setType(Light::LT_POINT);
	myLight->setPosition(0, 40, 0);
	myLight->setDiffuseColour(1, 1, 1);
	myLight->setSpecularColour(1, 1, 1);

	this->customizeScene();
}

void OgreRails::Application::destroyScene() {

}


