#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>
#include <functional>

#include "base_entity.h"
#include "entity_extensions.h"
#include "map.h"

namespace Entities {

class Entity;

using PEntity = std::unique_ptr<Entity>;

class Entity : public BaseEntity {
public:

	Entity(Maps::Map &position, 
		Maps::Position entityPosition) :
		m_position{entityPosition},
		m_location{position} {
	}
	virtual ~Entity(){}

	void Act() noexcept override;

protected:
	inline const Maps::TileParams& GetCurrentTile() const noexcept {
		return m_location.GetTile(m_position);
	}

	inline Maps::TileParams& GetCurrentTile() noexcept {
		return m_location.GetTile(m_position);
	}

	inline void RemoveFromHolder() noexcept
	{
		m_location.RemoveEntity(m_position);
	}

private:

	Maps::Position m_position;
	Maps::Map &m_location;
};


}

#endif // ENTITY_H
