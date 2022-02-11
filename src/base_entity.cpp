#include "base_entity.h"


void Entities::BaseEntity::CallEvent(PossibleEntityEvent eventToCall) noexcept 
{
	if(!ShouldBeDestroyed() || eventToCall == PossibleEntityEvent::OnDestroyedEvent)
	{
		for(auto &event : m_eventsHolder[static_cast<int>(eventToCall)])
		{
			event();
			if(ShouldBeDestroyed())
			{
				break;
			}
		}
	}
}

void Entities::BaseEntity::AddEvent(PossibleEntityEvent eventToCall, BaseEvent eventToAdd) noexcept 
{
	if(!ShouldBeDestroyed())
	{
		m_eventsHolder[static_cast<int>(eventToCall)].push_back(eventToAdd);
	}
}
