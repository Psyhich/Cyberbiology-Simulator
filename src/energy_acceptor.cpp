
#include "energy_acceptor.h"
#include "map_tile.h"

using namespace Extensions;

EnergyAcceptor::EnergyAcceptor(ExtensionHolder &owner, const BaseParams &params, TileGetter getter, ConsumptionCalculator calc) :
	Extension(owner),
	m_GetTile{getter},
	m_CalculateConsumption{calc},
	m_sunTreshold{params.sunTreshold},
	m_soilTreshold{params.soilTreshold},
	m_storedEnergy{params.startingEnergy}
	{
	Owner().AddEvent(Entities::PossibleEntityEvent::ActEvent,
		[&] () {
			m_storedEnergy -= m_CalculateConsumption();
			if(m_storedEnergy <= 0) {
				Owner().Destroy();
				return;
			}

			Maps::TileParams &currentTile = m_GetTile();
			AcceptSun(currentTile.GetSunEnergy());
			AcceptSoil(currentTile.GetSoilEnergy());
		});

	Owner().AddEvent(Entities::PossibleEntityEvent::OnDestroyedEvent,
		[&] {
			// Releasing stored energy into soil
			Maps::TileParams &currentTile = m_GetTile();
			currentTile.AddSoilEnergy(m_storedEnergy / 2);
		});
}

void EnergyAcceptor::AcceptSun(double amount) noexcept {
	if(m_sunTreshold <= 100 && amount > m_sunTreshold) {
		Owner().Destroy();
		return;
	}
}

void EnergyAcceptor::AcceptSoil(double amount) noexcept {
	if(m_soilTreshold <= 100 && amount > m_soilTreshold) {
		Owner().Destroy();
		return;
	}
}
