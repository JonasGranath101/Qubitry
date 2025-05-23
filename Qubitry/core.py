# Import the CFFI-generated module and the ffi object
from _func_cffi import ffi, lib

# lib contains the C functions we defined via cdef
# ffi can be used for more advanced cffi features (like 




def geometry(a,b):

    return lib.geometry(a, b)

def output():
                			
    return lib.output()

def graph(x):
                                            
    return lib.graph(x)

                                                 