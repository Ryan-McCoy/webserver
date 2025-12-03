#include <ctype.h>
#include <sys/types.h>
#ifndef _WIN32
#include <sys/select.h>
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/main.h"

#define PORT 8888

enum MHD_Result answer_to_connection(void *cls,
                                     struct MHD_Connection *connection,
                                     const char *url, const char *method,
                                     const char *version,
                                     const char *upload_data,
                                     size_t *upload_data_size, void **req_cls) {

  
  char processedurl[256] = {};
  strcat(processedurl, ".");
  strcat(processedurl, url);
  unsigned long i = strlen(processedurl);
  // while (isspace(processedurl[i])) {
  //   i--;
  // }
  i -= 1;
  char slash = '/';
  if (processedurl[i] == slash) {
    char index[11] = "index.html";
    strcat(processedurl, index);
  }
  printf("Processed URL: %s\n", processedurl);
  printf("Last char: %c\n", processedurl[i]);

  const char *page = read_file(processedurl);
  struct MHD_Response *response;
  enum MHD_Result ret;
  (void)cls;              /* Unused. Silent compiler warning. */
  (void)url;              /* Unused. Silent compiler warning. */
  (void)method;           /* Unused. Silent compiler warning. */
  (void)version;          /* Unused. Silent compiler warning. */
  (void)upload_data;      /* Unused. Silent compiler warning. */
  (void)upload_data_size; /* Unused. Silent compiler warning. */
  (void)req_cls;          /* Unused. Silent compiler warning. */

  response = MHD_create_response_from_buffer_static(strlen(page), page);
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);
  return ret;
}

int main(void) {
  struct MHD_Daemon *daemon;

  daemon =
      MHD_start_daemon(MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD, PORT,
                       NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
  if (NULL == daemon)
    return 1;

  (void)getchar();

  MHD_stop_daemon(daemon);
  return 0;
}

char* read_file(const char url[]) {
  printf("%s\n", url);
  FILE *file = fopen(url, "r");
  if (!file) {
    return "Unknown error";
  }
  fseek(file, 0L, SEEK_END);
  int size = ftell(file);

  rewind(file);
  char *data = malloc(size + 1);

  fread(data, size + 1, size, file);
  fclose(file);
  return data;
}