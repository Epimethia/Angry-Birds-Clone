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
	if (contact) {
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
	}
}

void Listener::EndContact(b2Contact * contact) {

}

void Listener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold) {
	
}

void Listener::PostSolve(b2Contact * contact, const b2Manifold * oldManifold) {

}
