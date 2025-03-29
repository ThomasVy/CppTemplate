#include "fmt/format.h"

static constexpr auto g_NAME = "Thomas";
int main(int argc, char* argv[]) {
  fmt::println("Hello World {}", g_NAME);

  return 0;
}
