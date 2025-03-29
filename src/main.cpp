#include "fmt/core.h"

static constexpr auto g_NAME = "Thomas";
int main(int argc, char* argv[]) {
  fmt::print("Hello World {}", g_NAME);

  return 0;
}
