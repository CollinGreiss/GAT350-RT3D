#include "Engine.h"

#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

namespace nc {

	bool Engine::Initialize() {

		m_systems.push_back( std::move( std::make_unique<Renderer>() ) );
		m_systems.push_back( std::move( std::make_unique<InputSystem>() ) );

		for ( auto& system : m_systems )
			system->Initialize();

		GetSystem<Renderer>()->CreateWindow( "GAT350", 800, 600 );

		m_systems.push_back( std::move( std::make_unique<Gui>() ) );
		GetSystem<Gui>()->Initialize();

		return true;
	}

	void Engine::Shutdown() {

		for ( auto& system : m_systems )
			system->Shutdown();

		m_systems.clear();

	}

	void Engine::Update() {

		SDL_Event event;
		SDL_PollEvent( &event );
		GetSystem<Gui>()->ProcessEvent( event );

		m_time.Tick();

		for ( auto& system : m_systems )
			system->Update();

		m_quit = GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_ESCAPE );

	}

}
