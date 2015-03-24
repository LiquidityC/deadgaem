#include "catch.hpp"
#include "EntityImpl.h"
#include "../src/CollisionDetector.h"
#include "../src/EntityProperties.h"
#include "../src/DeltatimeMonitor.h"
#include "../src/EntityContainer.h"
#include "../src/EntityShape.h"

TEST_CASE( "CollisionDetectorTests", "[collision]" )
{
	flat2d::DeltatimeMonitor *dtm;
	flat2d::EntityContainer* container;
	flat2d::CollisionDetector* detector;

	flat2d::Entity* c1;
	flat2d::Entity* c2;
	flat2d::Entity* c3;
	flat2d::Entity* c4;
	flat2d::Entity* c5;


	dtm = new flat2d::DeltatimeMonitor();
	container = new flat2d::EntityContainer(dtm);
	detector = new flat2d::CollisionDetector(container, dtm);

	c1 = new EntityImpl(100, 100);
	c2 = new EntityImpl(200, 100);
	c3 = new EntityImpl(200, 200);
	c4 = new EntityImpl(105, 105);
	c5 = new EntityImpl(115, 115);

	container->registerObject(c1);
	container->registerObject(c2);
	container->registerObject(c3);
	container->registerObject(c4);

	SECTION( "Collision detection", "[collisions]" )
	{
		REQUIRE( detector->hasCollided(c1, c4) );
		REQUIRE( !detector->hasCollided(c1, c2) );
	}

	SECTION( "Multi collisions", "[collisions]" )
	{
		flat2d::Entity* o = detector->checkForCollisions( c4 );
		REQUIRE( o );
		REQUIRE( *c1 == *o );

		REQUIRE( !detector->checkForCollisions( c2 ) );
	}

	SECTION( "Colliders", "[collisions]" )
	{
		flat2d::EntityShape colliderBox = { 0, 0, 1, 1 };
		c1->getEntityProperties().setColliderShape(colliderBox);

		REQUIRE( !detector->hasCollided(c1, c4) );
	}

	SECTION( "Moving object collision", "[collisions]" )
	{
		flat2d::EntityProperties& props = c1->getEntityProperties();
		props.setXvel(10);
		props.setYvel(0);

		// This one should start failing once sweptAABB is back online
		REQUIRE( !detector->hasCollided(c1, c5) );
	}

	delete detector;
	delete container;
	delete dtm;
}

