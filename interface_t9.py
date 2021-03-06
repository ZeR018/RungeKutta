import tkinter as tk
from ctypes import *
import ctypes
import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from tkinter import ttk

class Interface:
    def __init__(self, master):
        self.master = master  # инициализируем основное окно
        self.photo = tk.PhotoImage(file='logo.png')  # загрузка иконки приложения
        master.iconphoto(False, self.photo)  # установка иконки
        master.title('Задача Коши для ОДУ')  # заголовок
        master.configure(bg='#ececec')  # фон
        master.minsize(1110, 700)  # минимальный размер окна

        self.x0 = tk.DoubleVar(master, 1)  # x0
        self.u0 = tk.DoubleVar(master, 2)  # u0
        self.a1 = tk.DoubleVar(master, 12)  # a1
        self.a3 = tk.DoubleVar(master, 21)  # a3
        self.m = tk.DoubleVar(master, 123)  # m
        self.accuracy = tk.DoubleVar(master, 10.0)  # точность выхода на границу
        self.error = tk.DoubleVar(master, 0.001)  # контроль лок. поргрешности
        self.max_step = tk.DoubleVar(master, 10000000)  # макс. число шагов
        self.step = tk.DoubleVar(master, 0.01)  # начальный шаг
        self.rb_var = tk.IntVar(master)  # хранит 0 или 1 (выход на границу x или u)
        self.rb_var.set(0)  # значение по умолчанию
        self.cb_var = tk.BooleanVar(master)  # хранит True или False (включен ли контроль погр-ти)
        self.cb_var.set(1)  # значение по умолчанию

        self.create_widgets()  # создание виджетов

    def create_widgets(self):
        # место для задачи (открытие по кнопке)
        exec_b = tk.Button(text='Задача', bg='#ececec', highlightbackground='#ececec', command=self.execute).grid(
            row=0, column=0, columnspan=2, padx=10, pady=(10, 0), sticky='we')

        # начальные условия
        cond_l = tk.Label(text='Начальные условия', bg='#ececec').grid(row=1, column=0, columnspan=2)
        cond_xl = tk.Label(text='x0', bg='#ececec').grid(row=2, column=0, padx=(10, 0), sticky='w')
        cond_xe = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.x0).grid(row=2, column=1, padx=(0, 10))
        cond_ul = tk.Label(text='u0', bg='#ececec').grid(row=3, column=0, padx=(10, 0), sticky='w')
        cond_ue = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.u0).grid(row=3, column=1, padx=(0, 10))
        cond_a1l = tk.Label(text='a1', bg='#ececec').grid(row=5, column=0, padx=(10, 0), sticky='w')
        cond_a1e = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.a1).grid(row=5, column=1, padx=(0, 10))
        cond_a3l = tk.Label(text='a3', bg='#ececec').grid(row=6, column=0, padx=(10, 0), sticky='w')
        cond_a3e = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.a3).grid(row=6, column=1, padx=(0, 10))
        cond_ml = tk.Label(text='m', bg='#ececec').grid(row=7, column=0, padx=(10, 0), sticky='w')
        cond_me = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.m).grid(row=7, column=1, padx=(0, 10))

        # график
        self.canvas = tk.Canvas()
        

        # кнопка Вычислить
        exec_b = tk.Button(text='Вычислить', bg='#ececec', highlightbackground='#ececec', command=self.execute).grid(
            row=8, column=0, columnspan=5, padx=10, pady=10, sticky='we')

        # параметры програмы
        accuracy_l = tk.Label(text='Точность выхода на границу', bg='#ececec').grid(row=0, column=2, padx=10,
                                                                                    pady=(10, 0), sticky='w')
        rb1 = tk.Radiobutton(text='x', variable=self.rb_var, value=0, bg='#ececec').grid(row=0, column=3, pady=(10, 0),
                                                                                         sticky='e')
        rb2 = tk.Radiobutton(text='u', variable=self.rb_var, value=1, bg='#ececec').grid(row=0, column=4, pady=(10, 0),
                                                                                         sticky='e')
        accuracy_e = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.accuracy).grid(row=1, column=2,
                                                                                              columnspan=3,
                                                                                              padx=(10, 0), sticky='we')
        error_cb = tk.Checkbutton(bg='#ececec', variable=self.cb_var).grid(row=2, column=3, columnspan=2)
        error_l = tk.Label(text='Контроль лок. погрешности', bg='#ececec').grid(row=2, column=2, padx=10, sticky='w')
        error_e = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.error).grid(row=3, column=2, columnspan=3,
                                                                                        padx=(10, 0), sticky='we')
        max_steps_l = tk.Label(text='Максимальное число шагов', bg='#ececec').grid(row=4, column=2, padx=10, sticky='w')
        max_steps_e = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.max_step).grid(row=5, column=2,
                                                                                               columnspan=3,
                                                                                               padx=(10, 0),
                                                                                               sticky='we')
        step_l = tk.Label(text='Начальный шаг', bg='#ececec').grid(row=6, column=2, padx=10, sticky='w')
        step_e = tk.Entry(highlightbackground='#cbcbcb', textvariable=self.step).grid(row=7, column=2, columnspan=3,
                                                                                      padx=(10, 0), sticky='we')

        # справка (реализовать заполнение в функции execute)
        reference_l = tk.Label(text='Справка', bg='#ececec').grid(row=0, column=5, pady=10, sticky='we')
        reference_t = tk.Text(height=14, highlightbackground='#cbcbcb').grid(row=1, column=5, rowspan=7, padx=(10, 10),
                                                                             sticky='we')

        # таблица
    def tables (self, p, _i, d):
        heads = ['k', 'x', 'V', 'e', 'h', 'U' , 'E','C1', 'C2']
        self.table = ttk.Treeview(self.master, show='headings')
        self.table['columns']=heads
        self.table.grid(row=9, column=5, columnspan=1, rowspan=10, padx=10, sticky = tk.NSEW)
        for header in heads:
            self.table.heading(header,text=header, anchor='center')
            self.table.column(header,anchor='center')
            self.table.column(header,width=73)
        
        for z in range(int(_i.value/p['k'])):
            self.table.insert('', tk.END, values=(z, (d[p['x']+z*p['k']]),(d[p['V']+z*p['k']]),d[p['e']+z*p['k']], d[p['h']+z*p['k']], d[p['U']+z*p['k']], d[p['E']+z*p['k']], d[p['c1']+z*p['k']], d[p['c2']+z*p['k']]))
                        
 
        # график
    def plotOnPlane(self, X, Y):
        plt.close()
        f=plt.figure(num=2,figsize=(7,5),dpi=80)
        fig=plt.subplot(1,1,1)
        fig.set_title ('График')
        fig.set_xlabel ('x')
        fig.set_ylabel ('U(x)')
        fig.plot (X, Y, '-k')
        return f

    def create_form_graph(self,figure):
        self.canvas=FigureCanvasTkAgg(figure,self.master)
        self.canvas.get_tk_widget().grid(row=9,column=1,columnspan=4,rowspan=1)
        self.canvas.draw ()

    #  выполняется при нажатии кнопки "Вычислить"
    def execute(self):
        # записываем начальные условия задачи
        init_params = (c_double*9)()
        init_params[0] = self.x0.get()
        init_params[1] = self.u0.get()
        init_params[2] = self.step.get()
        init_params[3] = self.a1.get()
        init_params[4] = self.a3.get()
        init_params[5] = self.m.get()
        init_params[6] = self.error.get()
        init_params[7] = self.max_step.get()
        init_params[8] = self.accuracy.get()    # точность выхода на границу
        # записываем параметры чм
        #method_params = (c_double*2)()
        #method_params[0] = self.accuracy.get()  # точность выхода на границу
        #method_params[1] = self.error.get()  # контроль погрешности
        # записываем данные с кнопок (выбор границы / контроль лп)
        button_data = (c_int*2)()
        button_data[0] = self.rb_var.get()      # выбор границы 0 - x, 1 - u
        button_data[1] = self.cb_var.get()      # контроль ЛП True/False
        
        
        #подрубаем dll
        dll = cdll.LoadLibrary("dll_for_py//x64//Release//dll_for_py.dll")
        #вроде нужно чтобы работало
        dll.work_RK31R.argtypes = [POINTER(POINTER(c_double))]
        dll.work_RK31R.restype = None
        #---------------------------------------------------------
        dll.del_mem.argtypes = [POINTER(POINTER(c_double))]
        dll.work_RK31R.restype = None

        #для ракрытия массива
        p = {'k':8,'x': 0,'V': 1,'e': 2,'h': 3,'U':4,'E':5,'c1':6,'c2':7}

        #главный массив
        d = POINTER(c_double)()

        #количество эл в массиве
        _i = (c_int)()

        #работа
        dll.work_RK31R(byref(d),byref(init_params),byref(button_data),byref(_i))

        #-------------------------------------------------ИНСТРУКЦИЯ---------------------------------------------------------------------------#
        #--------------------------------------------------------------------------------------------------------------------------------------#
        # #из массива берем переменную x      далее берем строку          и умножаем ее на кратность массива
        #           d[p['x']                           +z                          *p['k']]

        
        #for z in range(int(_i.value/p['k'])):
            #use_it.append(d[p['x']+z*p['k']])
            #use_it.append(d[p['v1']+z*p['k']])
        
        #print(use_it) # проверка

        # for z in range(int(_i.value/p['k'])):
        #     print("i: ",z,"\tx: ",d[p['x']+z*p['k']],"\tv: ",d[p['v1']+z*p['k']],"\te: ",d[p['e']+z*p['k']],"\th: ",d[p['h']+z*p['k']],"\tu: ",d[p['u']+z*p['k']],"\tE: ",d[p['E']+z*p['k']],"\tC1: ",d[p['c1']+z*p['k']],"\tC2: ",d[p['c2']+z*p['k']],"\n")

        X = []
        for z in range(int(_i.value/p['k'])):
           X.append(d[p['x']+z*p['k']])
        Y = []
        for z in range(int(_i.value/p['k'])):
            Y.append(d[p['V']+z*p['k']])

        self.figure = self.plotOnPlane (X, Y)
        self.create_form_graph (self.figure)  #график

        self.tables (p, _i, d) #таблица


        #удаляем память
        dll.del_mem(byref(d))
        

root = tk.Tk()
gui = Interface(root)
root.mainloop()
