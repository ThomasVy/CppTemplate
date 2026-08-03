#pragma once
#include <cstdint>
#include <expected>
#include <optional>
#include <vector>
namespace stock_problem {
    struct Strategy {
        int buy_date;
        int sell_date;

        [[nodiscard]] int Profit() const { return sell_date - buy_date; }
    };

    Strategy StockProblem(const std::vector<int>& prices);

    enum class ParseError : std::uint8_t { TooLarge };
    std::expected<int, ParseError> Test();
    std::optional<int> OptionalTest();
}  // namespace stock_problem
