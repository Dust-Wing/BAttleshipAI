#ifndef BATTLESHIP_EXTRASTRINGMETHODS_H
#define BATTLESHIP_EXTRASTRINGMETHODS_H

#include <ostream>
#include <ranges>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vector) {
    if (!vector.empty()) {
        out << '{';
        for (const auto& value : vector
            | std::ranges::views::take(vector.size() - 1)) {
            out << value << ", ";
        }
        out << vector.back() << '}';
    }
    return out;
}

//left and right strip
std::string strip(const std::string& str, const std::string& trimCharacters);


//left strip
std::string lstrip(const std::string& str, const std::string& trimCharacters);


//right strip
std::string rstrip(const std::string& str, const std::string& trimCharacters);

//make string lower case
std::string lower(const std::string& str);


#endif //TOPCOMMONWORDS_EXTRASTRINGMETHODS_H
