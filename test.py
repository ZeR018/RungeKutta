import ctypes
from enum import Enum
from ctypes import *




#подрубаем dll
dll = cdll.LoadLibrary("dll_for_py//x64//Release//dll_for_py.dll")
#вроде нужно чтобы работало
dll.work_RK31R.argtypes = [POINTER(POINTER(c_double))]
dll.work_RK31R.restype = None

#для ракрытия массива
p = {'x': 0,'v1': 1,'e': 2,'h': 3,'k':4}

#главный массив
d = POINTER(c_double)()

#размеры массивов с параметрами
d_i= 3
m_i = 2
par_d = (c_double*d_i)()
par_m = (c_double*m_i)()

#количество эл в массиве
_i = (c_int)()

#тестовые параметры
par_d[0] = 1.0
par_d[1] = 7.0
par_d[2] = 0.01
par_m[0] = 10.0
par_m[1] = 1000.0

#работа
dll.work_RK31R(byref(d),byref(par_d),byref(par_m),byref(_i))





for z in range(int(_i.value/4)):
    print("i: ",z,"\tx: ",d[p['x']+z*p['k']],"\tv: ",d[p['v1']+z*p['k']],"\te: ",d[p['e']+z*p['k']],"\th: ",d[p['h']+z*p['k']],"\n")


#из массива берем переменную x      далее берем строку          и умножаем ее на кратность массива
#d[p['x']                           +z                          *p['k']]