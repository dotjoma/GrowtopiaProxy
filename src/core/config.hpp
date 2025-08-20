#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include <type_traits>
#include <vector>

namespace core {
using ConfigStorage = std::variant<int, unsigned int, std::string, bool, std::vector<std::string>>;

class Config {
public:
    Config();
    ~Config() = default;

    template <typename T = std::string>
    [[nodiscard]] T get(const std::string& key) const
    {
        try {
            // Try direct get first
            if constexpr (std::is_same_v<T, unsigned int>) {
                const auto &value = config_.at(key);
                if (std::holds_alternative<unsigned int>(value)) {
                    return std::get<unsigned int>(value);
                }
                if (std::holds_alternative<int>(value)) {
                    return static_cast<unsigned int>(std::get<int>(value));
                }
            }
            return std::get<T>(config_.at(key));
        }
        catch (const std::exception&) {
            return T{}; // or some other default value
        }
    }

private:
    std::unordered_map<std::string, ConfigStorage> config_;
};
}
