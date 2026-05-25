//
// Created by mfbut on 3/28/2019.
//

#include "ExtraStringMethods.h"
#include <cctype>
#include <string>

#include <functional>
#include <ranges>

namespace r = std::ranges;
namespace rv = r::views;


std::string strip(const std::string& str, const std::string& trimCharacters) {
    return rstrip(lstrip(str,trimCharacters),trimCharacters);
}


std::string lstrip(const std::string& str, const std::string& trimCharacters) {
    auto is_trim_character = [&trimCharacters](const char c) {
        return trimCharacters.contains(c);
    };

    return str
           | rv::drop_while(is_trim_character)
           | r::to<std::string>();
}


std::string rstrip(const std::string& str, const std::string& trimCharacters) {
    auto is_trim_character = [&trimCharacters](const char c) {
        return trimCharacters.contains(c);
    };
    return str
           | rv::reverse
           | rv::drop_while(is_trim_character)
           | rv::reverse
           | r::to<std::string>();
}


std::string lower(const std::string& str) {
    return str
           | std::ranges::views::transform([](const char c) { return tolower(c); })
           | std::ranges::to<std::string>();
}
