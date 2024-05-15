#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//---------- TCP ----------
int init_tcp() {
  int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in sockaddr = {AF_INET, htons(1800), 0};
  bind(tcp_sock, &sockaddr, sizeof(sockaddr));
  return tcp_sock;
}

void *handle_client(void *arg) {
  int client_sock = *((int *)arg);
  char buffer[256] = {0};
  recv(client_sock, buffer, sizeof(buffer), 0);
  send(client_sock, buffer, sizeof(buffer), 0);
  close(client_sock);
  pthread_exit(NULL);
}

void listen_tcp(int tcp_sock) {
  listen(tcp_sock, 10);
  while (1) {
    // accept all clients
    int client_sock = accept(tcp_sock, 0, 0);
    if (client_sock < 0) {
      perror("accept failed");
      continue;
    }

    // execute thread
    pthread_t thread_id;
    if (pthread_create(&thread_id, 0, handle_client, &client_sock) != 0) {
      perror("pthread_create failed");
      close(client_sock);
      continue;
    }
    pthread_detach(thread_id);
  }
}

//---------- UDP ----------

/* int init_udp() {
  int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in sockaddr = {AF_INET, htons(1800), 0};
  bind(tcp_sock, &sockaddr, sizeof(sockaddr));
  return udp_sock;
} */

int main() {
  int tcp_sock = init_tcp();
  listen_tcp(tcp_sock);
  return 0;
}
