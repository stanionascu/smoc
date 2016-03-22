#include <chrono>
#include <iostream>
#include <thread>

#include <zmq.h>

#include "rpc-base.h"

void *rpc_socket = nullptr;

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  auto *context = zmq_ctx_new();
  rpc_socket = zmq_socket(context, ZMQ_PAIR);
  int rc = zmq_connect(rpc_socket, "tcp://127.0.0.1:9999");
  if (rc == 0) {
    std::cout << "Connected to 127.0.0.1:9999" << std::endl;
  }

  while (true) {
    rpc_say("Hello rpc world");
    auto res = rpc_add(5, 8);
    std::cout << "for 5 + 8 server said: " << res << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  zmq_close(rpc_socket);
  zmq_ctx_destroy(context);

  return 0;
}
