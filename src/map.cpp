#include "map.h"


void Maps::Map::RemoveEntity(Position entityPosition) noexcept 
{
	m_allEntities[CalculatePos(entityPosition)].reset(nullptr);
}
