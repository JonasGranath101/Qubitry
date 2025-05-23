# Import the CFFI-generated module and the ffi object
from _default_cffi import ffi, lib

# lib contains the C functions we defined via cdef
# ffi can be used for more advanced cffi features (like 




def index(a,b):

    return lib.index(a, b)

def output():
                			
    return lib.geometrical_output()

def graph(x):
                                            
    return lib.graph(x)

                                                 