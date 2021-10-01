import ctypes
from enum import Enum
from ctypes import *

#тип для вывода 
def _p(array,perem,stroka):
    return array[perem+stroka*p['k']]


#подрубаем dll
dll = cdll.LoadLibrary("dll_for_py//x64//Release//dll_for_py.dll")
#вроде нужно чтобы работало
dll.work_RK31R.argtypes = [POINTER(POINTER(c_double))]
dll.work_RK31R.restype = None
#---------------------------------------------------------
dll.del_mem.argtypes = [POINTER(POINTER(c_double))]
dll.work_RK31R.restype = None

#для ракрытия массива
p = {'k':8,'x': 0,'v1': 1,'e': 2,'h': 3,'u':4,'E':5,'c1':6,'c2':7}

#главный массив
d = POINTER(c_double)()
#количество эл в массиве
_i = (c_int)()

#размеры массивов с параметрами
d_i= 6
m_i = 3
par_d = (c_double*d_i)()
par_m = (c_double*m_i)()


#тестовые параметры
par_d[0] = 1.0  # - x0
par_d[1] = 7.0  # - v0
par_d[2] = 0.01 # - h0
par_d[3] = 1    # - a1 -------------
par_d[4] = 1    # - a3 - параметры -
par_d[5] = 1    # - m  -------------

par_m[0] = 100.0
par_m[1] = -1000.0
par_m[2] = 1000.0

#работа
dll.work_RK31R(byref(d),byref(par_d),byref(par_m),byref(_i),0)

#-------------------------------------------------ИНСТРУКЦИЯ---------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------------------------------------------------------#
# #из массива берем переменную x      далее берем строку          и умножаем ее на кратность массива
#           d[p['x']                           +z                          *p['k']]\

#типо все вывод
for z in range(int(_i.value/p['k'])):
    print("i: ",z,"\tx: ",d[p['x']+z*p['k']],"\tv: ",d[p['v1']+z*p['k']],"\te: ",d[p['e']+z*p['k']],"\th: ",d[p['h']+z*p['k']],"\tu: ",d[p['u']+z*p['k']],"\tE: ",d[p['E']+z*p['k']],"\tC1: ",d[p['c1']+z*p['k']],"\tC2: ",d[p['c2']+z*p['k']],"\n")
# d[p['x']+z*p['k']]
print("________________________________________________________________________________________________________________")
#print(_p(d,p['v1'],10))


#удаляем память
dll.del_mem(byref(d))





