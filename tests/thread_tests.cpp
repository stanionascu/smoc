#include <gtest/gtest.h>

#include <smoc/thread.hpp>

TEST(thread_tests, start_quit)
{
  smoc::thread t;
  t.start();
  EXPECT_TRUE(t.is_running());
  t.quit();
  t.wait();
  EXPECT_FALSE(t.is_running());
}

TEST(thread_tests, execution_thread_id)
{
  smoc::thread t;
  t.start();
  EXPECT_TRUE(t.is_running());

  std::thread::id main_id = std::this_thread::get_id();
  std::thread::id new_id = t.id();
  std::thread::id exec_id;
  t.post([&exec_id]{
    exec_id = std::this_thread::get_id();
  });

  t.quit();
  t.wait();

  EXPECT_EQ(new_id, exec_id);
  EXPECT_NE(main_id, new_id);
  EXPECT_NE(exec_id, main_id);
}


TEST(thread_tests, custom_thread)
{
  class my_thread : public smoc::thread {
    void run() override {
      exec_tid_ = std::this_thread::get_id();
    }
  public:
    std::thread::id exec_tid_;
  };

  my_thread t;
  t.start();
  auto new_id = t.id();
  t.wait();
  EXPECT_EQ(new_id, t.exec_tid_);
}