#include "stock_problem/stock_problem.h"

#include <vector>


namespace stock_problem {

    Strategy StockProblem(const std::vector<int>& prices) {
        Strategy strategy = {.buy_date = 0, .sell_date = 0};
        if (prices.size() == 0) {
            return strategy;
        }

        int potential_buy = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < prices[potential_buy]) {
                potential_buy = i;
            }
            if (strategy.Profit() < prices[i] - prices[potential_buy]) {
                strategy = {.buy_date = potential_buy, .sell_date = i};
            }
        }
        return strategy;
    }
    static std::expected<int, ParseError> _AddTwo(int value) {
        if (value > 100) {
            return std::unexpected{ParseError::TooLarge};
        }
        return value + 2;
    }
    static std::expected<int, ParseError> _MultiplyByTwo(int value){
        if (value > 100) {
            return std::unexpected{ParseError::TooLarge};
        }
        return value * 2;
    }
    static std::expected<int, ParseError> Init() {
        return 50;
    }

    std::expected<int, ParseError> Test() {
        return Init()
            .and_then(_AddTwo)
            .and_then(_MultiplyByTwo);
    }
}  // namespace stock_problem
