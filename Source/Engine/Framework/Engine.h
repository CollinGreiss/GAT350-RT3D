#pragma once
#include "Core/Time.h"

#include "System.h"
#include "Singleton.h"
#include <vector>
#include <memory>

#define ENGINE nc::Engine::Instance()

namespace nc {

	class Engine : public Singleton<Engine> {
	public:
		bool Initialize();
		void Shutdown();

		void Update();

		bool IsQuit() { return m_quit; }

		friend class Singleton;

		template <typename T>
		T* GetSystem();

		Time& GetTime() { return m_time; }

	private:

		Engine() {}

	private:

		bool m_quit = false;
		std::vector<std::unique_ptr<ISystem>> m_systems;
		Time m_time;

	};

	template<typename T>
	inline T* Engine::GetSystem() {

		for ( auto& system : m_systems ) {

			T* s = dynamic_cast<T*>( system.get() );
			if ( s ) return s;

		}

		return nullptr;

	}

}