#ifndef DEFAULT_H
#define DEFAULT_H

// It's good practice to declare functions that will be part of a public API
// with some form of visibility control if you were building a larger shared library.
// For cffi, just the declarations are often enough.

int httpSearch(int var_url, int var_host, int var_path, int var_request);
int xordecrypt(const char *input, char *output, const char *key);
int data_lambda(int var_a);
int decrypt_lambda(char var_encrypt);

#endif // DEFAULT_H