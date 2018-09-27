#pragma once

#include <string>
struct EntityData {
	std::string EntityType;
	bool m_bIsMarkedForDestruction = false;

	void MarkForDestruction() {
		m_bIsMarkedForDestruction = true;
	}
};