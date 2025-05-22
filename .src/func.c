#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <netdb.h>
#include <arpa/inet.h> 

#include <stdbool.h> // For bool type
#include <stdio.h>

#include <stddef.h> // For size_t

void xor_decrypt(unsigned char* data, size_t data_len, const unsigned char* key, size_t key_len) {
        for (size_t i = 0; i < data_len; i++) {
                    data[i] = data[i] ^ key[i % key_len];
        }
}

int decrypt_lambda(char var_encrypt) {
        // 1. Correctly initialize encrypted_data as a single character array
            unsigned char encrypted_data[1]; 
                encrypted_data[0] = (unsigned char)var_encrypt; 

                    unsigned char key[] = {'K'}; // Simple key
                        size_t data_len = 1; // It's a single character
                            size_t key_len = sizeof(key);

                                printf("Original encrypted data (hex): ");
                                    printf("%02x ", encrypted_data[0]); // Print the single character in hex
                                        printf("\n");

                                            xor_decrypt(encrypted_data, data_len, key, key_len);

                                                printf("Decrypted data: %c\n", encrypted_data[0]); // Print as a character

                                                    return 0;
}

// Define a function to be used as a callback
double times_two(double x) { return x * 2; }

// Use the function pointer
double apply(double (*func)(double), double value) {
        return func(value);
}

int data_lambda(int v) {
        // Fix: Remove 'int' when passing 'v' to the apply function
            double result = apply(times_two, (double)v); // Cast v to double
                // Now you can use 'result' for something, e.g., print it or return it.
                    // For example, to print:
                        printf("Result of applying times_two to %d: %f\n", v, result);

                            // If you want to return a value from data_lambda, you need to specify it.
                                // For now, let's just return 0 as it's an int function.
                                    return 0;
}



// XOR decrypts (and encrypts) the data with the given key
void xordecrypt(const char *input, char *output, const char *key) {
        size_t len = strlen(input);
            size_t keylen = strlen(key);
                for (size_t i = 0; i < len; i++) {
                            output[i] = input[i] ^ key[i % keylen];
                }
                    output[len] = '\0';
}





#define BUFFER_SIZE 8192

// Extracts host and path from a URL of the form http://host/path
void parse_url(const char *url, char *host, size_t host_sz, char *path, size_t path_sz) {
        const char *p = url;
            if (strncmp(url, "http://", 7) == 0) {
                        p += 7;
            }
                const char *slash = strchr(p, '/');
                    if (slash) {
                                size_t hlen = slash - p;
                                        if (hlen >= host_sz) hlen = host_sz - 1;
                                                strncpy(host, p, hlen);
                                                        host[hlen] = '\0';
                                                                strncpy(path, slash, path_sz - 1);
                                                                        path[path_sz - 1] = '\0';
                    } else {
                                strncpy(host, p, host_sz - 1);
                                        host[host_sz - 1] = '\0';
                                                strcpy(path, "/");
                    }
}

// Writes HTTP body to file, skipping headers
int save_http_response(int sockfd, const char *filename) {
        FILE *fp = fopen(filename, "wb");
            if (!fp) {
                        perror("fopen");
                                return -1;
            }

                char buffer[BUFFER_SIZE + 1];
                    int header_ended = 0;
                        size_t total_written = 0;
                            ssize_t n;

                                printf("\n");

                                    while ((n = read(sockfd, buffer, BUFFER_SIZE)) > 0) {
                                                buffer[n] = '\0';
                                                        char *body = buffer;
                                                                if (!header_ended) {
                                                                                char *header_end = strstr(buffer, "\r\n\r\n");
                                                                                            if (header_end) {
                                                                                                                header_ended = 1;
                                                                                                                                body = header_end + 4;
                                                                                                                                                n -= (body - buffer);
                                                                                            } else {
                                                                                                                // Still in headers, skip this chunk
                                                                                                                                continue;
                                                                                            }
                                                                }
                                                                        if (header_ended && n > 0) {
                                                                                        size_t written = fwrite(body, 1, n, fp);
                                                                                                    if (written != (size_t)n) {
                                                                                                                        perror("fwrite");
                                                                                                                                        fclose(fp);
                                                                                                                                                        return -1;
                                                                                                    }
                                                                                                                total_written += written;
                                                                        }
                                                                                printf(body);
                                    }

                                        printf("\n");

                                            fclose(fp);
                                                return total_written;
}

int httpSearch(int var_url, int var_host, int var_path, int var_request) {
        // Use fixed-size arrays for safety and portability
            size_t url_len = (var_url > 0) ? var_url : 1024;
                size_t host_len = (var_host > 0) ? var_host : 512;
                    size_t path_len = (var_path > 0) ? var_path : 512;
                        size_t req_len  = (var_request > 0) ? var_request : 2048;

                            char url[url_len];
                                char host[host_len];
                                    char path[path_len];
                                        char request[req_len];

                                            // Prompt user for URL
                                                printf("Enter URL to scrape (e.g., http://example.com/path): ");
                                                    if (!fgets(url, url_len, stdin)) {
                                                                fprintf(stderr, "Failed to read URL\n");
                                                                        return 1;
                                                    }
                                                        // Remove newline
                                                            url[strcspn(url, "\r\n")] = 0;

                                                                // Parse URL into host and path
                                                                    parse_url(url, host, host_len, path, path_len);
                                                                        if (strlen(host) == 0) {
                                                                                    fprintf(stderr, "Invalid URL format.\n");
                                                                                            return 1;
                                                                        }

                                                                            // DNS lookup
                                                                                struct hostent *server = gethostbyname(host);
                                                                                    if (!server) {
                                                                                                fprintf(stderr, "No such host: %s\n", host);
                                                                                                        return 1;
                                                                                    }

                                                                                        // Create socket
                                                                                            int sockfd = socket(AF_INET, SOCK_STREAM, 0);
                                                                                                if (sockfd < 0) {
                                                                                                            perror("socket");
                                                                                                                    return 1;
                                                                                                }

                                                                                                    // Build server address
                                                                                                        struct sockaddr_in serv_addr;
                                                                                                            memset(&serv_addr, 0, sizeof(serv_addr));
                                                                                                                serv_addr.sin_family = AF_INET;
                                                                                                                    serv_addr.sin_port = htons(80);
                                                                                                                        memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

                                                                                                                            // Connect to server
                                                                                                                                if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
                                                                                                                                            perror("connect");
                                                                                                                                                    close(sockfd);
                                                                                                                                                            return 1;
                                                                                                                                }

                                                                                                                                    // Prepare HTTP GET request
                                                                                                                                        snprintf(request, req_len,
                                                                                                                                                "GET %s HTTP/1.0\r\n"
                                                                                                                                                        "Host: %s\r\n"
                                                                                                                                                                "User-Agent: SimpleScraper/1.0\r\n"
                                                                                                                                                                        "Connection: close\r\n"
                                                                                                                                                                                "\r\n", path, host);

                                                                                                                                                                                    // Send request
                                                                                                                                                                                        if (write(sockfd, request, strlen(request)) < 0) {
                                                                                                                                                                                                    perror("write");
                                                                                                                                                                                                            close(sockfd);
                                                                                                                                                                                                                    return 1;
                                                                                                                                                                                        }

                                                                                                                                                                                            // Ensure .data directory exists
                                                                                                                                                                                                struct stat st = {0};
                                                                                                                                                                                                    if (stat(".data", &st) == -1) {
                                                                                                                                                                                                                if (mkdir(".data", 0700) < 0) {
                                                                                                                                                                                                                                perror("mkdir");
                                                                                                                                                                                                                                            close(sockfd);
                                                                                                                                                                                                                                                        return 1;
                                                                                                                                                                                                                }
                                                                                                                                                                                                    }

                                                                                                                                                                                                        // Save response to .data/Curl_ResultLog.txt
                                                                                                                                                                                                            const char *filename = ".data/Curl_ResultLog.txt";
                                                                                                                                                                                                                printf("Saving scraped content to %s ...\n", filename);
                                                                                                                                                                                                                    int bytes = save_http_response(sockfd, filename);
                                                                                                                                                                                                                        if (bytes < 0) {
                                                                                                                                                                                                                                    fprintf(stderr, "Failed to save HTTP response.\n");
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                    printf("Done! %d bytes written.\n", bytes);
                                                                                                                                                                                                                        }

                                                                                                                                                                                                                            close(sockfd);
                                                                                                                                                                                                                                return 0;
}
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                }
                                                                                                                                                                                                    }
                                                                                                                                                                                        }
                                                                                                                                }
                                                                                                }
                                                                                    }
                                                                        }
                                                    }
}
                                                                                                    }
                                                                        }
                                                                                            }
                                                                                            }
                                                                }
                                    }
            }
}
                    }
                    }
            }
}
                }
}
}
}
}
        }
}