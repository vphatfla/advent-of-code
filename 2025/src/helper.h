#include <sstream>
#include <string>
#include <vector>

inline auto splitString(const std::string& s, char delimiter) -> std::vector<std::string> {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);

    while (std::getline(ss, token, delimiter)) {
        tokens.emplace_back(token);
    }

    return tokens;
}

auto inline splitStringMultipleWhiteSpace(const std::string& s) -> std::vector<std::string> {
    std::vector<std::string> res;
    std::string token;
    std::istringstream ss(s);

    while (ss >> token) {
        res.emplace_back(token);
    }
    
    return res;
}
