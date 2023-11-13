#pragma once

#include <string>

namespace nc {

	std::string ToUpper(std::string string);
	std::string ToLower(std::string string);
	std::string CreateUnique(std::string string);
		
	bool IsEqualIgnoreCase(std::string string1, std::string string2);

}