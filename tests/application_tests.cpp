#include <gtest/gtest.h>

#include <smoc/application.hpp>

#include <chrono>
#include <thread>

TEST(application_tests, exec)
{
  smoc::application app;
  app.post([&](){
    app.quit(10);
  });
  EXPECT_EQ(app.exec(), 10);
}
