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

#include "OgreOverlayElementFactory.h"

#include "Application.hpp"
#include "path/StraightSegment.hpp"
#include "path/CurveSegment.hpp"
#include "path/Endpoint.hpp"
#include "BlindPathChooser.hpp"
#include "PathBuilder.hpp"

void OgreRails::Application::customizeScene(){
	using namespace Ogre;
	// Create frame listener
	this->createFrameListener_Custom();

	Vector3 camInitPos(5 * SNAPGRID_H_SPACE, 1000, 5 * SNAPGRID_H_SPACE);
	Vector3 camLookVec(15 * SNAPGRID_H_SPACE, -1000, 15 * SNAPGRID_H_SPACE);
	mCamera->setPosition(camInitPos);
	mCamera->lookAt(camInitPos + camLookVec);
	mCamera->setPosition(Vector3(281, 1733, 312));

	mDebugConsole = std::auto_ptr<OgreRails::DebugConsole>(new OgreRails::DebugConsole());
	DebugConsole::getSingleton().setPos(0.005f,0.005f);        // Text position, using relative co-ordinates
	DebugConsole::getSingleton().setCol(0.0f,0.0f,0.0f,1.0f); // Text colour (Red, Green, Blue, Alpha)

	Coords worldSize(100u, 100u);
	Vector3 worldSizeF = worldSize.toOgreUnits();
	mGroundNode = mSceneMgr->getRootSceneNode();
	//mFakeGround = mSceneMgr->createSceneNode();
	// create a floor mesh resource
	MeshManager::getSingleton().createPlane(
		"FlatGroundPlane",          // const String & name,
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, // The name of the resource group to assign the mesh to
		Plane(Vector3::UNIT_Y, 0), // The orientation of the plane and distance from the origin
		worldSizeF.x, // Real width, The width of the plane in world coordinates
		worldSizeF.z,
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
		Vector3(worldSizeF.x/2, 0.0f, worldSizeF.z/2));
	floorNode->attachObject(floorEntity);

	using namespace OgreRails::Paths;

	// Prepare track segments
	mStraightSF = std::auto_ptr<StraightSegmentFactory>(
		new StraightSegmentFactory(
			new StraightSegment(1u, Ogre::Vector3(SNAPGRID_H_SPACE, 0.0f, 0.0f), 5.0f),
			new SegmentGraphicFactory(
				mGroundNode,
				mSceneMgr->createEntity("An00biS_Rails_StraightSegment.mesh"),
				Ogre::Vector3::ZERO
			)
		)
	);
	mRight6SF = std::auto_ptr<CurveSegmentFactory>(
		new CurveSegmentFactory(
			new CurveSegment(6u, Segment::TURN_RIGHT, 5.0f),
			new SegmentGraphicFactory(
				mGroundNode,
				mSceneMgr->createEntity("An00biS_Rails_CurveSegment6.mesh"),
				Ogre::Vector3(-6.0f * SNAPGRID_H_SPACE, 0.0f, 6.0f * SNAPGRID_H_SPACE),
				Ogre::Vector3(0.0f, Ogre::Math::HALF_PI, 0.0f)
			)
		)
	);
	mLeft6SF = std::auto_ptr<CurveSegmentFactory>(new CurveSegmentFactory(
			new CurveSegment(6u, Segment::TURN_LEFT, 5.0f),
			new SegmentGraphicFactory(
				mGroundNode,
				mSceneMgr->createEntity("An00biS_Rails_CurveSegment6.mesh"),
				Ogre::Vector3::ZERO
			)
		)
	);
	// == Build the track ==
	std::auto_ptr<PathBuilder> builder(new PathBuilder(mSceneMgr, floorNode));


	Endpoint* endpoint = new Endpoint();
	mEndpoints.push_back(endpoint);
	const int T(5); // Thickness

	builder->start(endpoint, Coords(15u, 95u), Segment::DIRECTION_X);
	builder->build(mStraightSF.get(), 40-24-T); // Start from bottom left corner, inner level, bottom
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 90-12); // right
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 40-24); // top
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 90-12-T); // left, end at inner level
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 40-24-T); // bottom inner
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 90-12-T*2); // right inner
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 40-24-T*2); // top
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 90-12-T); // left, end at baseline
	builder->build(mLeft6SF.get());
	Paths::Path* letterOPath = builder->end(endpoint);
	mPaths.push_back(letterOPath);

	endpoint = new Endpoint();
	mEndpoints.push_back(endpoint);
	builder->start(endpoint, Coords(45u, 85u), Segment::DIRECTION_X);
	builder->build(mStraightSF.get(), 20-12); // bottom
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 85-12-15); // up
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 10); // left
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 20);  // down
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 15); // left
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 25); // up
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 20); // right
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 30);  // down
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 25 - 15); // right
	builder->build(mLeft6SF.get());
	//builder->build(mStraightSF.get(), (85-12-15-30-6)-30); // down
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 100-55-12 - 15); // right
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 30-12-1); // down
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 55-12+5);
	builder->build(mRight6SF.get());
	builder->build(mRight6SF.get());
	builder->build(mStraightSF.get(), 5);
	builder->build(mLeft6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mLeft6SF.get());
	builder->build(mStraightSF.get(), 4);
	builder->build(mLeft6SF.get());
	Paths::Path* track8Path = builder->end(endpoint);
	mPaths.push_back(track8Path);

	using namespace Ogre;

	// Hardcoded 3d model properties.
	// Temporary.
	float mod = 0.7f;

	const float LOCO363_SCALE_S(5.23796113 * mod);
	const Ogre::Vector3 LOCO363_SCALE_V(LOCO363_SCALE_S,LOCO363_SCALE_S,LOCO363_SCALE_S);
	const float LOCO363_BOGIE_2_NOSE_DISTANCE(41.95390595 * mod);
	const float LOCO363_LENGTH(167.4 * mod);
	const float LOCO363_BOGIE_HEIGHT(9.30261896 * mod);
	const float LOCO363_GAP_SIZE(10.0f * mod);

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
			LOCO363_GAP_SIZE)); // gap size

	const float CAR_BOGIE2NOSE(32.075f * mod);
	const float CAR_LEN(245.0f * mod);
	const Ogre::Vector3 CAR_SCALE_V(10 * mod,10 * mod,10 * mod);
	const float CAR_BOGIE_HEIGHT(8.09f * mod);
	const float CAR_GAP_SIZE(10.0f * mod);

	Entity* coach = mSceneMgr->createEntity("passenger-car", "An00biS_PassengerCarBdmtee.mesh");
	Entity* coachBogie = mSceneMgr->createEntity("passenger-bogie", "An00biS_PassengerCarBdmtee_Bogie.mesh");
	mCoachPrototype = std::auto_ptr<TwoBogieVehiclePrototype> (new TwoBogieVehiclePrototype(
			mGroundNode,
			std::string("passenger-car-front-bogie"),
			std::string("passenger-car-rear-bogie"),
			std::string("passenger-car-body"),
			coachBogie,
			coachBogie,
			coach,
			CAR_SCALE_V,
			CAR_SCALE_V,
			CAR_SCALE_V,
			CAR_LEN,
			CAR_BOGIE2NOSE, // bogie to nose distance
			CAR_LEN-CAR_BOGIE2NOSE,
			CAR_BOGIE_HEIGHT, // bogie height
			CAR_GAP_SIZE));

	OgreRails::MovingConsist* consist = 0;
	{ // letter O consist
		consist = new OgreRails::MovingConsist();
		consist->setPathChooser(new OgreRails::BlindPathChooser());
		consist->addVehicle(mLocoPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->snap(letterOPath);
		float l = letterOPath->getLength() * 0.13;
		consist->move(l);
		consist->setSpeed(200.0f);
		mFrameListener->addConsist(consist);
		consist = 0;
	}

	{ // letter O consist 2
		consist = new OgreRails::MovingConsist();
		consist->setPathChooser(new OgreRails::BlindPathChooser());
		consist->addVehicle(mLocoPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->snap(letterOPath);
		float l = letterOPath->getLength() * 0.6;
		consist->move(l);
		consist->setSpeed(200.0f);
		mFrameListener->addConsist(consist);
		consist = 0;
	}

	{ // track8 consist
		consist = new OgreRails::MovingConsist();
		consist->setPathChooser(new OgreRails::BlindPathChooser());
		consist->addVehicle(mLocoPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->snap(track8Path);
		float l = track8Path->getLength() * 0.99;
		consist->move(l);
		consist->setSpeed(200.0f);
		mFrameListener->addConsist(consist);
		consist = 0;
	}

	{ // track8 consist 2
		consist = new OgreRails::MovingConsist();
		consist->setPathChooser(new OgreRails::BlindPathChooser());
		consist->addVehicle(mLocoPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->snap(track8Path);
		float l = track8Path->getLength() * 0.11;
		consist->move(l);
		consist->setSpeed(200.0f);
		mFrameListener->addConsist(consist);
		consist = 0;
	}

	{ // track8 consist 3
		consist = new OgreRails::MovingConsist();
		consist->setPathChooser(new OgreRails::BlindPathChooser());
		consist->addVehicle(mLocoPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->addVehicle(mCoachPrototype->instance());
		consist->snap(track8Path);
		float l = track8Path->getLength() * 0.5;
		consist->move(l);
		consist->setSpeed(200.0f);
		mFrameListener->addConsist(consist);
		consist = 0;
	}

}

// Just override the mandatory create scene method
void OgreRails::Application::createScene(void)
{
	using namespace Ogre;
	// Create the SkyBox
	mSceneMgr->setSkyBox(true, "OgreRails/CloudyNoonSkyBox");

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
