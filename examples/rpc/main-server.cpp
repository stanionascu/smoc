#include <iostream>

#include <msgpack.hpp>
#include <zmq.h>

#include "rpc-server.hpp"
#include "rpc-base.h"
#include "rpc-pack.hpp"

void *rpc_socket = nullptr;

void rpc_say(const std::string &what) {
  std::cout << "SERVER must say: " << what << std::endl;
}

int rpc_add(int x, int y) {
  std::cout << "SERVER must add: " << x << " + " << y << std::endl;
  return x + y;
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  auto *context = zmq_ctx_new();
  rpc_socket = zmq_socket(context, ZMQ_PAIR);

  int rc = zmq_bind(rpc_socket, "tcp://127.0.0.1:9999");
  if (rc == 0) {
    std::cout << "Listening on: 127.0.0.1:9999" << std::endl;
  }

  while (true) {
    zmq_msg_t header_zmsg;
    zmq_msg_init(&header_zmsg);
    zmq_recvmsg(rpc_socket, &header_zmsg, 0);

    messages::header header;
    msgpack::unpacked header_unpacked;
    msgpack::unpack(&header_unpacked,
                    static_cast<char *>(zmq_msg_data(&header_zmsg)),
                    zmq_msg_size(&header_zmsg));

    header_unpacked.get().convert(header);

    zmq_msg_t body_zmsg;
    zmq_msg_init(&body_zmsg);
    zmq_recvmsg(rpc_socket, &body_zmsg, 0);

    msgpack::unpacked body_unpacked;
    msgpack::unpack(&body_unpacked,
                    static_cast<char *>(zmq_msg_data(&body_zmsg)),
                    zmq_msg_size(&body_zmsg));

    execute_rpc_request(static_cast<rpc_call_name>(header.get<0>()),
                        body_unpacked.get());

    zmq_msg_close(&header_zmsg);
    zmq_msg_close(&body_zmsg);
  }

  zmq_close(rpc_socket);
  zmq_ctx_destroy(context);

  return 0;
}
