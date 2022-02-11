#ifndef BASE_MAP_H
#define BASE_MAP_H

#include <tuple>

namespace Maps {

using Position = std::pair<unsigned, unsigned>;

struct TileParams {
	inline double GetSunEnergy() const noexcept {
		return sunCount;
	}

	inline void SetSunEnergy(double valueToSet) noexcept {
		sunCount = valueToSet;
	}

	inline double GetSoilEnergy() noexcept {
		double gotEnergy = soilCount * 0.1;
		soilCount -= gotEnergy;
		return gotEnergy;
	}
	inline void AddSoilEnergy(double energyToAdd) noexcept {
		soilCount += energyToAdd / 2;
	}
private:
	// Sun energy is not remove from tile
	double sunCount; 

	// Soil is removed
	double soilCount;
};

} // Maps 

#endif // BASE_MAP_H
