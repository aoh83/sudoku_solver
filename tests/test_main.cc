#include <gtest/gtest.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

int main(int argc, char **argv) {

  auto console = spdlog::stdout_color_mt("console");
  spdlog::set_default_logger(console);

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
