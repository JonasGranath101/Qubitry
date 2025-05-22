# Import the CFFI-generated module and the ffi object
from _default_cffi import ffi, lib

# lib contains the C functions we defined via cdef
# ffi can be used for more advanced cffi features (like 


def mesh(i,y,k,p):

    return lib.mesh(i,y,k,p)

def index(a,b):

    return lib.index(a, b)

def geometrical_output(h):
                			
    return lib.geometrical_output(h,x)

def graph(x):
                                            
    return lib.graph(x)

                                                 