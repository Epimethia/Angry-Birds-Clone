#include "ContactListener.h"
#include "Box2D/Box2D.h"
#include "EntityData.h"
#include <string>
#include <iostream>

#include "BirdEntity.h"


Listener::Listener() {

}

Listener::~Listener() {

}

void Listener::BeginContact(b2Contact * contact) {
	/*if (contact) {
		auto bodyUserDataA = static_cast<EntityData*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto bodyUserDataB = static_cast<EntityData*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (bodyUserDataA && bodyUserDataB) {
			if (bodyUserDataA->EntityType == "Bird") {
				if (bodyUserDataB->EntityType == "GlassBlock") {
					bodyUserDataB->MarkForDestruction();
					std::cout << "Contact Glass\n";
				}
			}

			else if (bodyUserDataA->EntityType == "GlassBlock") {
				if (bodyUserDataB->EntityType == "Bird") {
					std::cout << "Contact Glass\n";
					bodyUserDataA->MarkForDestruction();
				}
			}
		}
	}*/
}

void Listener::EndContact(b2Contact * contact) {

}

void Listener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold) {
	if (contact) {
		auto bodyUserDataA = static_cast<EntityData*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto bodyUserDataB = static_cast<EntityData*>(contact->GetFixtureB()->GetBody()->GetUserData());

		//getting the force of the contact
		float force = oldManifold->points[0].normalImpulse;

		//checking force of collisions against glass blocks
		if (force > 0.9f) {
			if (bodyUserDataA && bodyUserDataB) {
				if (bodyUserDataA->EntityType == "GlassBlock") {
					std::cout << "Contact Glass\n";
					bodyUserDataA->MarkForDestruction();
				}

				else if (bodyUserDataB->EntityType == "GlassBlock") {
					std::cout << "Contact Glass\n";
					bodyUserDataB->MarkForDestruction();
				}
			}
		}

		//checking force of collisions against pigs
		if (force > 0.6f) {
			if (bodyUserDataA && bodyUserDataB) {
				if (bodyUserDataA->EntityType == "Pig") {
					std::cout << "Contact Pig\n";
					bodyUserDataA->MarkForDestruction();
				}

				else if (bodyUserDataB->EntityType == "Pig") {
					std::cout << "Contact Pig\n";
					bodyUserDataB->MarkForDestruction();
				}
			}
		}
	}
}

void Listener::PostSolve(b2Contact * contact, const b2Manifold * oldManifold) {

}
