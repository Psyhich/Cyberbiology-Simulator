#ifndef ENTITY_EXTENSIONS_H
#define ENTITY_EXTENSIONS_H

#include <optional>
#include <functional>
#include <list>

#include "base_entity.h"

namespace Extensions {

class Extension;
class ExtensionHolder;

enum ExtensionAbility
{
	None = 0,
	AcceptEnergy = 1, // Entity can accept energy from different sources
};

/// Extensions can provide more functionality for any entity
/// They can do this by adding new functions for entities or adding events for BaseEntity
class Extension {
public:
	Extension(ExtensionHolder &owner) : m_owner{owner} {

	}
	virtual ~Extension() = 0;
	virtual ExtensionAbility GetName() const noexcept = 0;

	inline const ExtensionHolder &Owner() const
	{
		return m_owner;
	}

	inline ExtensionHolder &Owner()
	{
		return m_owner;
	}

private:
	ExtensionHolder &m_owner;
};

using PExtension = std::unique_ptr<Extension>;

class ExtensionHolder : virtual public Entities::BaseEntity {
public:
	ExtensionHolder() = default;
	virtual ~ExtensionHolder() = 0;

	/// Adds extension to holder if holder doesn't have the same extension already
	void AddExtension(PExtension &&extensionToAdd) noexcept;
	/// Removes all extension that have given flag
	void RemoveExtension(ExtensionAbility extensionToRemove) noexcept;
	/// Returns extensions with given flag
	std::optional<std::reference_wrapper<Extension>> GetExtension(ExtensionAbility extensionToFind) noexcept;

private:
	std::list<PExtension> m_extensions;
	ExtensionAbility m_currentExtensions;
};


} // Extensions 

#endif // ENERGY_ACCEPTOR_H 
