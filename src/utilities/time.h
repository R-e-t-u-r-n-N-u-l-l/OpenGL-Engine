#pragma once

#include <chrono>

namespace engine {
	namespace Time {

		static unsigned long timeMillis() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();;
		}
	}
}