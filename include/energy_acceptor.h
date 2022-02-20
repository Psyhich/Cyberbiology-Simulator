#ifndef ENERGY_EXTENSION_H
#define ENERGY_EXTENSION_H

#include "entity_extensions.h"
#include "map_tile.h"

namespace Extensions {

	class EnergyAcceptor : public Extension {
	public:
		struct BaseParams
		{
			double sunTreshold{0};
			double soilTreshold{0};
			double startingEnergy{0};
		};

		using TileGetter = std::function<Maps::TileParams&()>;
		using ConsumptionCalculator = std::function<double()>;

		EnergyAcceptor(ExtensionHolder &owner, const BaseParams &params, TileGetter getter, ConsumptionCalculator calc);
		~EnergyAcceptor() override {}

		inline ExtensionAbility GetName() const noexcept override
		{
			return AcceptEnergy;
		}

	protected:
		inline double GetEnergyStored() const noexcept {
			return m_storedEnergy;
		}
	private:
		void AcceptSun(double amount) noexcept;
		void AcceptSoil(double amount) noexcept;

	private:
		TileGetter m_GetTile;
		ConsumptionCalculator m_CalculateConsumption;
		
		// Max amount the creature can recieve(but not hold) before dying
		// Treshold value varies in range [0;100], where values bigger than 100 means full immunity
		double m_sunTreshold; 
		double m_soilTreshold; 

		double m_storedEnergy;

		// Amount of energy would be removed at each turn
		double m_energyConsumption;
	};

} // Extension

#endif // ENERGY_EXTENSION_H
