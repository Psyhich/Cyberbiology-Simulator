#ifndef MAP_H
#define MAP_H 

#include <vector>

#include "map_tile.h"
#include "base_entity.h"

namespace Maps {

class Map {
public:
	Map(unsigned width, unsigned height) : 
		m_width{width}, m_height{height} {
		m_allEntities.resize(m_height * m_width);
	}

	void RemoveEntity(Position entityPosition) noexcept;

	// Various getters and setters
	inline const Entities::BaseEntity *GetEntity(Position entityPosition) const {
		return m_allEntities[CalculatePos(entityPosition)].get();
	}

	inline Entities::BaseEntity *GetEntity(Position entityPosition) {
		return m_allEntities[CalculatePos(entityPosition)].get();
	}

	inline const TileParams& GetTile(Position entityPosition) const noexcept {
		return m_allTiles[CalculatePos(entityPosition)];
	}

	inline TileParams& GetTile(Position entityPosition) noexcept {
		return m_allTiles[CalculatePos(entityPosition)];
	}

	inline const unsigned GetWidth() const noexcept {
		return m_width;
	}

	inline const unsigned GetHeight() const noexcept {
		return m_height;
	}

private:
	inline size_t CalculatePos(const Position &pos) const noexcept{
		return pos.second * m_height + pos.first;
	}

	std::vector<Entities::PBaseEntity> m_allEntities;
	std::vector<TileParams> m_allTiles;

	unsigned m_width;
	unsigned m_height;

};

} // Maps 

#endif // MAP_H
