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

for j in range(par_i.value):
    print(d[j],"\t")
    if(j%3==0):
        print("\n")


#dll.fin_vect.argtypes = [POINTER(POINTER(c_double))]
#dll.fin_vect.restype = None
#d = POINTER(c_double)()
#d_i = 4
#i_i = 2
#par_d = (c_double*d_i)()
#par_i = (c_int*i_i)()
#for z in range(d_i):
#    par_d[z] = z+1.4
#for z in range(i_i):
#    par_i[z] = z+10
#
#dll.fin_vect(byref(d),par_i,par_d)
#print(d[0],d[1],d[2])


#dll.test_vect.argtypes= [POINTER(c_double)]
#dll.test_vect.restype = None
#i = 3
#data = (c_double*i)()
#dll.test_vect(data)
#print(data[0],data[1],data[2])

#dll.new_mem.argtypes = [POINTER(POINTER(c_int))]
#mem = POINTER(c_int)()
#dll.new_mem(byref(mem))
#print(mem[0][0])
