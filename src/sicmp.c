#include "icmp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void usage()
{
  fprintf(stdout, "usage: sicmp -o origin_ip -d destination_ip payload\n");
}

int sendICMP(char *src_ip, char *dest_ip, char *payload)
{
  struct icmp_packet packet;
  int sock_fd;

  strncpy(packet.src_addr, src_ip, strlen(src_ip) + 1);
  strncpy(packet.dest_addr, dest_ip, strlen(dest_ip) + 1);
  set_reply_type(&packet);
  packet.payload = payload;
  packet.payload_size = strlen(packet.payload);

  sock_fd = open_icmp_socket();

  send_icmp_packet(sock_fd, &packet);

  printf("Payload Sent\n");

  close_icmp_socket(sock_fd);

  return EXIT_SUCCESS;
}

int server()
{
  struct icmp_packet packet;
  int sock_fd;
 
  sock_fd = open_icmp_socket();
  bind_icmp_socket(sock_fd);

  printf("server initialized\n");
  while(1)
  {
    receive_icmp_packet(sock_fd, &packet);
    printf("%s\n", packet.src_addr);
    printf("%s\n", packet.dest_addr);
    printf("%d\n", packet.type);
    printf("%s\n", packet.payload);
  }
 
  close_icmp_socket(sock_fd);
}

int main(int argc, char *argv[])
{
  char *src_ip;
  char *dest_ip;
  char *payload;

  if ( argc == 6 ) {
    if ( strncmp(argv[1], "-o", strlen("-o")) == 0 ) {
      src_ip = argv[2];
      // printf("Source IP: ");
      // printf(src_ip);
      // printf("\n");
    }
    else {
      usage();
      exit(EXIT_FAILURE);
    }

    if ( strncmp(argv[3], "-d", strlen("-d")) == 0 ) {
      dest_ip = argv[4];
      // printf("Destination IP: ");
      // printf(dest_ip);
      // printf("\n");
    }
    else {
      usage();
      exit(EXIT_FAILURE);
    }

    payload = argv[5];
    // printf("Payload: \n");
    // printf(payload);
    // printf("\n");
    sendICMP(src_ip, dest_ip, payload);
  }
  else if (argc == 2 ) {
    if ( strncmp(argv[1], "-s", strlen("-s")) == 0 ) {
      server();
    }
    else {
      usage();
      exit(EXIT_FAILURE);
    }
  }
  else {
    usage();
    exit(EXIT_FAILURE);
  }

  
}
