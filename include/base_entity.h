#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include <memory>
#include <functional>
#include <list>
#include <map>

namespace Entities {

enum class PossibleEntityEvent
{
	OnDestroyedEvent = 0, // Event that would be called before the entity gets destroyed from map
	OnEatenEvent	 = 1, // Event that would be called when entity is eaten
	OnTouchEvent	 = 2, // Event that would be called when entity moves into direction that is already occupied
	ActEvent		 = 3, // Event that would be called on each start of turn
};
static inline constexpr const size_t POSSIBLE_EVENTS_COUNT = 4;

class IDestructable
{
public:
	/// Will be called to mark entity for destruction
	/// Entity cannot perform any actions after this flag is set
	virtual void Destroy() noexcept
	{
		m_shouldBeDestroyed = true;
	}

	inline bool ShouldBeDestroyed() const noexcept
	{
		return m_shouldBeDestroyed;
	}

private:
	bool m_shouldBeDestroyed{false};
};

class BaseEntity : virtual public IDestructable
{
public:
	using BaseEvent = std::function<void()>;

	virtual void Act() noexcept = 0;

	void CallEvent(PossibleEntityEvent eventToCall) noexcept;
	void AddEvent(PossibleEntityEvent eventToCall, BaseEvent eventToAdd) noexcept;

private:
	std::array<std::list<BaseEvent>, POSSIBLE_EVENTS_COUNT> m_eventsHolder;
};

using PBaseEntity = std::unique_ptr<BaseEntity>;

} // Entities

#endif // BASE_ENTITY_H
