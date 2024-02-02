#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{

			for (Layer* layer : m_layer_stack)
			{
				layer->onUpdate();
			}

			m_window->onUpdate();
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layer_stack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layer_stack.pushOverlay(overlay);
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); )
		{
			(*--it)->onEvent(e);
			if (e.handled) break;
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		
		return true;
	}

}