#include "stock_problem/stock_problem.h"

#include <cstdint>
#include <vector>

namespace stock_problem {
    namespace {
        constexpr int kAddTwoLimit = 100;
        constexpr int kMultiplyTwoLimit = 100;
        constexpr int kInitValue = 50;
    }  // namespace

    Strategy StockProblem(const std::vector<int>& prices) {
        Strategy strategy = {.buy_date = 0, .sell_date = 0};
        if (prices.empty()) {
            return strategy;
        }

        int potential_buy = 0;
        for (int i = 1; i < static_cast<int>(prices.size()); i++) {
            if (prices.at(i) < prices.at(potential_buy)) {
                potential_buy = i;
            }
            if (strategy.Profit() < prices.at(i) - prices.at(potential_buy)) {
                strategy = {.buy_date = potential_buy, .sell_date = i};
            }
        }
        return strategy;
    }

    static std::expected<int, ParseError> add_two(int value) {
        if (value > kAddTwoLimit) {
            return std::unexpected{ParseError::TooLarge};
        }
        return value + 2;
    }

    static std::expected<int, ParseError> multiply_by_two(int value) {
        if (value > kMultiplyTwoLimit) {
            return std::unexpected{ParseError::TooLarge};
        }
        return value * 2;
    }

    static std::expected<int, ParseError> Init() { return kInitValue; }

    std::expected<int, ParseError> Test() {
        return Init().and_then(add_two).and_then(multiply_by_two);
    }
}  // namespace stock_problem
