#ifndef ENTITY_EXTENSIONS_H
#define ENTITY_EXTENSIONS_H

#include <optional>
#include <algorithm>
#include <functional>
#include <list>
#include <type_traits>

#include "base_entity.h"

namespace Extensions {

	class Extension;
	class ExtensionHolder;

	/// All extensions work like flags, 
	/// So we should do bitwise OR to add extension 
	/// And bitwise XOR to remove them
	enum ExtensionAbility
	{
		None = 0,
		AcceptEnergy = 1, // Entity can accept energy from different sources
		HasGenome = 2, // Entity has genome and can reproduce itself
	};

	/// Extensions can provide more functionality for any entity
	/// They can do this by adding new functions for entities or adding events for BaseEntity
	class Extension {
	public:
		Extension(ExtensionHolder &owner) : m_owner{owner} {

		}
		virtual ~Extension() {}
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
		virtual ~ExtensionHolder() {}

		/// Adds extension to holder if holder doesn't have the same extension already
		void AddExtension(PExtension &&extensionToAdd) noexcept;
		/// Removes all extension that have given flag
		void RemoveExtension(ExtensionAbility extensionToRemove) noexcept;

		/// Returns extensions with given flag
		template<class Ext> 
		std::optional<std::reference_wrapper<Ext>> GetExtension(ExtensionAbility extensionToFind) noexcept
		{
			static_assert(std::is_base_of_v<Extension, Ext>, "Given class should derive Extension!");

			if((m_currentExtensions & extensionToFind) == extensionToFind) {
				auto extension = std::find_if(m_extensions.begin(), m_extensions.end(), 
					[extensionToFind](auto &ext){ return ext->GetName() == extensionToFind; });

				// If we have flag set, so we know that this extension exists in this holder
				return *dynamic_cast<Ext*>(extension);
			}
			return std::nullopt;
		}

	private:
		std::list<PExtension> m_extensions;
		ExtensionAbility m_currentExtensions;
	};

} // Extensions 

#endif // ENERGY_ACCEPTOR_H 
