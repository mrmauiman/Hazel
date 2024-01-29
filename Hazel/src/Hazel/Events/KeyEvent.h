#pragma once

#include "Event.h"

namespace Hazel {

	class HAZEL_API KeyEvent : public Event
	{
		inline int getKeyCode() const { return m_key_code; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_key_code(keycode) {}

		int m_key_code;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeat_count)
			: KeyEvent(keycode), m_repeat_count(repeat_count) {}

		inline int getRepeatCount() const { return m_repeat_count; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_key_code << "(" << m_repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_repeat_count;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_key_code;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}