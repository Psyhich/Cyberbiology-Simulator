
#include "energy_acceptor.h"
#include "map_tile.h"

using namespace Extensions;

EnergyAcceptor::EnergyAcceptor(ExtensionHolder &owner, TileGetter getter) : 
	Extension(owner),
	m_GetTile{getter}
	{
	Owner().AddEvent(Entities::PossibleEntityEvent::ActEvent,
		[&] () {
			m_storedEnergy -= CalculateConsumption();
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
	if(amount > m_sunTreshold) {
		Owner().Destroy();
		return;
	}
}

void EnergyAcceptor::AcceptSoil(double amount) noexcept {
	if(amount > m_soilTreshold) {
		Owner().Destroy();
		return;
	}
}
