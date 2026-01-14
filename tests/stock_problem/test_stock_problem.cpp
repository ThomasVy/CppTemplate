#include "gtest/gtest.h"
#include "stock_problem/stock_problem.h"

using namespace ::testing;
namespace stock_problem::test {
    struct StockProblemParams {
        const std::vector<int> input_prices;
        const stock_problem::Strategy expected_output;
    };

    class TestStockProblem : public TestWithParam<StockProblemParams> {};

    TEST_P(TestStockProblem, DataTests) {
        auto problem = GetParam();

        auto actual = stock_problem::StockProblem(problem.input_prices);
        EXPECT_EQ(actual.buy_date, problem.expected_output.buy_date);
        EXPECT_EQ(actual.sell_date, problem.expected_output.sell_date);
    }

    INSTANTIATE_TEST_CASE_P(
        DataTestProblems,
        TestStockProblem,
        Values(
            StockProblemParams{
                .input_prices = {3, 7, 1, 2},
                .expected_output = {.buy_date = 0, .sell_date = 1}},
            StockProblemParams{
                .input_prices = {7, 1, 5, 3, 6, 4},
                .expected_output = {.buy_date = 1, .sell_date = 4}},
            StockProblemParams{
                .input_prices = {7, 6, 4, 3, 1},
                .expected_output = {.buy_date = 0, .sell_date = 0}},
            StockProblemParams{
                .input_prices = {4, 1, 7, 8, 12},
                .expected_output = {.buy_date = 1, .sell_date = 4}},
            StockProblemParams{
                .input_prices = {3, 2, 1, 4, 5},
                .expected_output = {.buy_date = 2, .sell_date = 4}})

    );
}  // namespace stock_problem::test
