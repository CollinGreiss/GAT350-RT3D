#pragma once

#include "Framework/Object.h"

#include <string>
#include <memory>

namespace nc {

	class Resource : public Object {

	public:

		virtual ~Resource() = default;

		virtual bool Create( std::string filename, ... ) = 0;

	};

	template <typename T>
	using res_t = std::shared_ptr<T>;

}
