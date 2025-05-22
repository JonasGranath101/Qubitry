from cffi import FFI

ffibuilder = FFI()

ffibuilder.cdef("""
    int graph(int var_url, int var_host, int var_path, int var_request);
    int index(const char *input, char *output, const char *key);
    int geometrical_output(int var_a);
    int mesh(char var_encrypt);

""")



ffibuilder.set_source("_func_cffi",  # Name of the output C extension module (_my_math_cffi.so or .pyd)
    """
    #include ".src/func.h" // Include your C header
    """,
    sources=['.src/func.c'],   # List of C source files to compile
    # library_dirs=['path/to/libs'],  # Optional: if linking against precompiled libs
    # libraries=['mylib'],            # Optional: e.g., if you had libmylib.so
    include_dirs=['.']             # Directory where my_c_math.h can be found
)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
