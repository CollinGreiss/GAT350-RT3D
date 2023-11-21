#pragma once

#include "Actor.h"
#include "Components/LightComponent.h"

#include <list>
#include <vector>

namespace nc {

	class Renderer;

	class Scene {

	public:

		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);
		void Remove(Actor* actor);

		bool Load(const std::string& filename);
		void Read(const json_t& value);
		void ProcessGui();

		template<typename T>
		T* GetActor();
		template<typename T = Actor>
		T* GetActorByName(const std::string& name);


		template<typename T>
		std::vector<T*> GetComponents();

		void SetGame(World* game) { m_game = game; }

		friend class Actor;
		friend class Editor;

	public:

		glm::vec3 ambientColor = glm::vec3{ 0.1 };
		std::string jsonFile;

	private:

		float m_dt = 0;
		float m_fps = 0;

		World* m_game = nullptr;
		std::list<std::unique_ptr<Actor>> m_actors;

	};

	template<typename T>
	inline T* Scene::GetActor() {
		for (auto& actor : m_actors) {
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name) {
		for (auto& actor : m_actors) {
			if (actor->name == name) {
				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetComponents() {

		std::vector<T*> components;

		for (auto& actor : m_actors) {

			if (!actor->active) continue;

			auto component = actor->GetComponent<T>();

			if (component) components.push_back(component);


		}

		return components;
	
	}


}