/*****************************************************************************
 * client-c.c
 * Name:黄潇颖
 * NetId:2020201622
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define SEND_BUFFER_SIZE 2048

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
  {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

// s is the socket you want to send the data to
// buf is the buffer containing the data
// len is a pointer to an int containing the number of bytes in the buffer
int sendall(int s, char *buf, int *len, int should_len)
{

  int bytesleft = should_len - *len; // how many we have left to send
  int n;

  while (bytesleft > 0)
  {
    n = send(s, buf + *len, bytesleft, 0);
    if (n == -1)
    {
      break;
    }
    *len += n;
    bytesleft -= n;
  }

  return n == -1 ? -1 : 0; // return -1 on failure, 0 on success
}

int readin(char *buf)
{
  int bytes = 0;
  while (!feof(stdin) && bytes < SEND_BUFFER_SIZE)
  {
    bytes += fread(buf + bytes, sizeof(char), SEND_BUFFER_SIZE - bytes, stdin);
  }

  return bytes;
}

/* TODO: client()
 * Open socket and send message from stdin.
 * Return 0 on success, non-zero on failure
 */
int client(char *server_ip, char *server_port)
{
  int sockfd, numbytes;
  char buf[SEND_BUFFER_SIZE];
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((rv = getaddrinfo(server_ip, server_port, &hints, &servinfo)) != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  // loop through all the results and connect to the first we can
  for (p = servinfo; p != NULL; p = p->ai_next)
  {
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
                         p->ai_protocol)) == -1)
    {
      perror("client: socket");
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
    {
      close(sockfd);
      perror("client: connect");
      continue;
    }

    break;
  }

  if (p == NULL)
  {
    fprintf(stderr, "client: failed to connect\n");
    return 2;
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
  // printf("client: connecting to %s\n", s);

  freeaddrinfo(servinfo); // all done with this structure
  while (1)
  {

    int readinsize = readin(buf);
    int bytes_send = send(sockfd, buf, readinsize, 0);

    // sending fail
    if (bytes_send == -1)
    {
      perror("send");
      break;
    }

    // partial send
    // try till success
    if (bytes_send < readinsize)
      if (sendall(sockfd, buf, &bytes_send, readinsize) == -1)
      {
        perror("send");
        break;
      }

    if (readinsize == 0)
      break;
  }

  close(sockfd);

  return 0;
}

/*
 * main()
 * Parse command-line arguments and call client function
 */
int main(int argc, char **argv)
{
  char *server_ip;
  char *server_port;

  if (argc != 3)
  {
    fprintf(stderr, "Usage: ./client-c [server IP] [server port] < [message]\n");
    exit(EXIT_FAILURE);
  }

  server_ip = argv[1];
  server_port = argv[2];
  return client(server_ip, server_port);
}
