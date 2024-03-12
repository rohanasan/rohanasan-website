// Copyright (c) Rohan Vashisht
// You can check LICENSE file for more details

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define STATIC_FOLDER "static/"
#define GET "GET"
#define POST "POST"
#define error404header "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n"
#define default_html_header "HTTP/1.1 200 OK\nContent-Type: text/html\n\n"
#define default_any_text_content_header "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n"

extern inline bool eql(const char *x, const char *y) {
  if (strcmp(x, y) == 0) {
    return true;
  } else {
    return false;
  }
}

extern inline char *send_http_response(const char *header, const char *content) {
  // Get the lengths of s1 and s2
  size_t s1_len = snprintf(NULL, 0, "%s", header);
  size_t s2_len = snprintf(NULL, 0, "%s", content);

  // Allocate memory for the concatenated string
  char *result = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));

  // Check if allocation failed
  if (result == NULL) {
    return NULL;
  }

  // Concatenate s1 and s2
  snprintf(result, s1_len + s2_len + 1, "%s%s", header, content);

  return result;
}

extern inline char* send_file(const char*header,const char* filePath) {
    FILE* file = fopen(filePath, "r"); // Open file for reading [[1]]
    if (file == NULL) {
        // Error handling for failed file open
        return NULL;
    }

    // Get file size
    fseek(file, 0, SEEK_END); // Seek to end of file [[1]]
    long fileSize = ftell(file); // Get current position (file size) [[1]]
    rewind(file); // Seek back to start of file [[1]]

    char* buffer = (char*)malloc(fileSize + 1); // Allocate buffer for file contents
    if (buffer == NULL) {
        // Error handling for failed memory allocation
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file); // Read file into buffer [[4]]
    if (bytesRead < fileSize) {
        // Error handling for incomplete read
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[bytesRead] = '\0'; // Null-terminate the string [[1]]
    fclose(file); // Close the file [[2]]

    return send_http_response(header, buffer);
}

extern inline const char* send_404(){
    return "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n<html><head><title>404 error: Not found</title></head><body><h1>404 error (Not found)</h1><h4>Looks like we can't find what you are looking for.</h4><h2><a href='/'>Click here to return to home.</a></h2></body></html>";
}