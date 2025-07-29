#include <fmt/base.h>

#include "cxxopts.hpp"
#include "fmt/core.h"
#include "libA/libA.h"

static constexpr auto g_NAME = "Thomas";
int main(int argc, char *argv[]) {
    fmt::println("Hello World {}", g_NAME);
    cxxopts::Options options("Template App", "This is a template app");

    options.add_options()("b,bar", "Param bar", cxxopts::value<std::string>())(
        "d,debug",
        "Enable debugging",
        cxxopts::value<bool>()->default_value("false"))(
        "f,foo", "Param foo", cxxopts::value<int>()->default_value("10"))(
        "h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        fmt::print("{}\n", options.help());
        return 0;
    }
    bool debug = result["debug"].as<bool>();
    std::string bar;
    if (result.count("bar")) {
        bar = result["bar"].as<std::string>();
    }
    int foo = result["foo"].as<int>();

    fmt::print("foo is {}, bar is {}, debug is {}", foo, bar, debug);
    libA::function();
    return 0;
}
