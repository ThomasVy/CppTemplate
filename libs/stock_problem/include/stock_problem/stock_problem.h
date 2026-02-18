#pragma once
#include <expected>
#include <vector>
namespace stock_problem {
    struct Strategy {
        int buy_date;
        int sell_date;

        int Profit() const { return sell_date - buy_date; }
    };

    Strategy StockProblem(const std::vector<int>& prices);

    enum class ParseError { TooLarge };
    std::expected<int, ParseError> Test();
    std::optional<int> OptionalTest();
}  // namespace stock_problem
