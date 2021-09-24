import sys
#C:\\work\\cpp_python\\test\\x64\\Debug\\test.dll
import ctypes

from ctypes import *
dll = cdll.LoadLibrary("dll_for_py//x64//Release//dll_for_py.dll")
dll.work_RK31R.argtypes = [POINTER(POINTER(c_double))]
dll.work_RK31R.restype = None
d = POINTER(c_double)()
d_i= 3
m_i = 2
par_d = (c_double*d_i)()
par_m = (c_double*m_i)()
par_i = (c_int)()
par_d[0] = 1.0
par_d[1] = 7.0
par_d[2] = 0.01
par_m[0] = 10.0
par_m[1] = 1000.0

dll.work_RK31R(byref(d),byref(par_d),byref(par_m),byref(par_i))

j = 1
for j  in range(par_i.value):
    if((j-1)%4==0):
        print("\n")
    print(d[j-1],"\t")


