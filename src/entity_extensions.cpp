#include "entity_extensions.h"

using namespace Extensions;

void ExtensionHolder::AddExtension(PExtension &&extensionToAdd) noexcept {
	if((extensionToAdd->GetName() & m_currentExtensions) == 0) {
		m_extensions.push_back(std::move(extensionToAdd));
	}
}

void ExtensionHolder::RemoveExtension(ExtensionAbility extensionToRemove) noexcept {
	for(auto iter = m_extensions.begin(); 
		iter != m_extensions.end(); iter++) {
		if((iter->get()->GetName() & extensionToRemove) != 0) {
			m_currentExtensions = 
				static_cast<ExtensionAbility>(m_currentExtensions ^ iter->get()->GetName());
			m_extensions.erase(iter);
			break;
		}
	}
}
