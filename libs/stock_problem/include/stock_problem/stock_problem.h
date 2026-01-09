#pragma once
#include <vector>

namespace stock_problem {
    struct Strategy {
        int buy_date;
        int sell_date;

        int Profit() const { return sell_date - buy_date; }
    };

    Strategy StockProblem(const std::vector<int>& prices);

}  // namespace stock_problem
