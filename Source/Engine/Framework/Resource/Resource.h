#pragma once
#include <string>
#include <memory>

namespace nc {

	// Resource - Base class for all resources used in the engine (Texture, Models, Audio Clips, ...)
	class Resource {

	public:
		virtual ~Resource() = default;

		virtual bool Create( std::string filename, ... ) = 0;
		
	};

	// resources are stored as shared pointers so they can be shared among different objects
	// res_t is an alias for a std::shared_ptr (res_t<Texture> == std::shared_ptr<Texture>)
	template <typename T>
	using res_t = std::shared_ptr<T>;
}
