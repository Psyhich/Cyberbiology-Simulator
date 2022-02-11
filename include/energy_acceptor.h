#ifndef ENERGY_EXTENSION_H
#define ENERGY_EXTENSION_H

#include "entity_extensions.h"
#include "map_tile.h"

namespace Extensions {

class EnergyAcceptor : public Extension {
public:
	using TileGetter = std::function<Maps::TileParams&()>;

	EnergyAcceptor(ExtensionHolder &owner, TileGetter getter);
	~EnergyAcceptor() override {}

	virtual double CalculateConsumption() noexcept = 0;
	static constexpr const ExtensionAbility NAME{AcceptEnergy};

protected:
	inline double GetEnergyStored() const noexcept {
		return m_storedEnergy;
	}
private:
	TileGetter m_GetTile;

	void AcceptSun(double amount) noexcept;
	void AcceptSoil(double amount) noexcept;
	
	// Max amount the creature can recieve(but not hold) before dying
	double m_sunTreshold; 
	double m_soilTreshold; 

	double m_storedEnergy;

	// Amount of energy would be removed at each turn
	double m_energyConsumption;
};

} // Extension

#endif // ENERGY_EXTENSION_H
