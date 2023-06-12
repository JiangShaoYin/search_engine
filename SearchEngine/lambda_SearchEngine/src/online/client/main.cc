#include "../../../include/Client.h"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <ip> <port>\n", argv[0]);
    return -1;
  }
  Client client(argv[1], atoi(argv[2]));
  client.start();
  return 0;
}
