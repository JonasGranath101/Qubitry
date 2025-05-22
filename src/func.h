#ifndef FUNC_H
#define FUNC_H

// It's good practice to declare functions that will be part of a public API
// with some form of visibility control if you were building a larger shared library.
// For cffi, just the declarations are often enough.

int graph(int var_url, int var_host, int var_path, int var_request);
int mesh(const char *input, char *output, const char *key);
int index(int var_a);
int (char var_encrypt);

#endif // FUNC_H