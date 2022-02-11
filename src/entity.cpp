#include "entity.h"

void Entities::Entity::Act() noexcept
{
	CallEvent(PossibleEntityEvent::ActEvent);
	if(ShouldBeDestroyed())
	{
		CallEvent(PossibleEntityEvent::OnDestroyedEvent);
		RemoveFromHolder();
	}
}
