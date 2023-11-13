#include "StringUtils.h"

namespace nc {

	std::string ToUpper(std::string string) {

		for (auto& letter : string)
			letter = std::toupper(letter);

		return string;
	
	}

	std::string ToLower(std::string string) {

		for (auto& letter : string)
			letter = std::tolower(letter);

		return string;
	
	}

	std::string CreateUnique(std::string string) {

		static unsigned int count = 0;

		return string + std::to_string(count++);
	
	}

	bool IsEqualIgnoreCase(std::string string1, std::string string2) {

		return (ToLower(string1) == ToLower(string2));
	
	}

}