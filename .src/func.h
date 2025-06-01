#ifndef FUNC_H
#define FUNC_H

// It's good practice to declare functions that will be part of a public API
// with some form of visibility control if you were building a larger shared library.
// For cffi, just the declarations are often enough.

int graph( char data );
int output();

#endif // FUNC_H