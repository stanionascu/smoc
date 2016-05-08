#include <gtest/gtest.h>

#include <smoc/event_loop.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <cmath>

TEST(event_loop_test, run)
{
  smoc::event_loop el;
  el.post([&el]{ el.quit(); });
  el.run();
}

TEST(event_loop_test, 100_msec_run)
{
  using namespace std::chrono;
  auto now = steady_clock::now();
  smoc::event_loop el;
  boost::asio::steady_timer t(el.service(), std::chrono::milliseconds(100));
  t.async_wait(std::bind(&smoc::event_loop::quit, std::ref(el)));
  el.run();
  auto duration = round(duration_cast<milliseconds>(steady_clock::now() - now).count() / 100.0);
  EXPECT_EQ(duration, 1.0);
}