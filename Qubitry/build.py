from cffi import FFI

ffibuilder = FFI()

ffibuilder.cdef("""
    int graph( char data );
    int index( char str );
    int output();

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
