#pragma once

#include "Core/Logger.h"
#include "Core/StringUtils.h"
#include "Resource.h"
#include "Framework/Singleton.h"

#include <map>
#include <memory>
#include <vector>
#include <string>

#define GET_RESOURCE(type, filename, ...) nc::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)
#define GET_RESOURCES(type) nc::ResourceManager::Instance().GetAllOfType<type>()
#define ADD_RESOURCE(name, resource) nc::ResourceManager::Instance().Add(name, resource)

namespace nc {

	class ResourceManager : public Singleton<ResourceManager> {

	public:

		template<typename T>
		bool Add(const std::string& name, res_t<T> resource);

		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);

		template<typename T>
		std::vector<res_t<T>> GetAllOfType();

	private:

		std::map<std::string, res_t<Resource>> m_resources;

	};

	template<typename T>
	inline bool ResourceManager::Add(const std::string& name, res_t<T> resource) {

		std::string lname = ToLower(name);

		if (m_resources.find(lname) != m_resources.end()) {
		
			WARNING_LOG("Resource already exist!: " << lname);
			return false;
		
		}

		resource->name = lname;
		m_resources[lname] = resource;

		return true;

	}

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args) {

		std::string lfilename = ToLower(filename);

		if (m_resources.find(lfilename) != m_resources.end())
			return std::dynamic_pointer_cast<T>(m_resources[lfilename]);

		res_t<T> resource = std::make_shared<T>();
		if (!resource->Create(lfilename, args...)) {

			WARNING_LOG("Could not create resource: " << lfilename);
			return res_t<T>();
		}

		Add(lfilename, resource);

		return resource;
	
	}

	template<typename T>
	inline std::vector<res_t<T>> ResourceManager::GetAllOfType() {

		std::vector<res_t<T>> result;

		for (auto& resource : m_resources) {
			auto res = std::dynamic_pointer_cast<T>(resource.second);
			if (res) result.push_back(res);

		}

		return result;

	}

}