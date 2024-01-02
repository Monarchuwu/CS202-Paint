#include <sstream>

template<typename T>
std::string toString(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<typename T>
std::string toStringHexaDecimal(T value) {
    std::stringstream ss;
	ss << std::hex << value;
	return ss.str();
}
