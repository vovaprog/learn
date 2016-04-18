#!/usr/bin/python

from Tkinter import *
from datetime import datetime, timedelta
import tkMessageBox

main_window = Tk()
main_window.title("wd")
main_window.geometry('400x300')

def center(toplevel):
    toplevel.update_idletasks()
    w = toplevel.winfo_screenwidth()
    h = toplevel.winfo_screenheight()
    size = tuple(int(_) for _ in toplevel.geometry().split('+')[0].split('x'))
    x = w/2 - size[0]/2
    y = h/2 - size[1]/2
    toplevel.geometry("%dx%d+%d+%d" % (size + (x, y)))

def show_alarm():
    tkMessageBox.showinfo("!", "!")

def start_timer(value):
    global start_time
    start_time = datetime.now()
    end_time = start_time + timedelta(minutes = value)
    
    entry_started.config(state = NORMAL)
    entry_started.delete(0, END)
    entry_started.insert(0, datetime.strftime(start_time,'%H:%M'))
    entry_started.config(state = "readonly")
    
    entry_finish.config(state = NORMAL)
    entry_finish.delete(0, END)
    entry_finish.insert(0, datetime.strftime(end_time,'%H:%M'))
    entry_finish.config(state = "readonly")
    
    main_window.after(value * 60 * 1000, show_alarm)

def button_10_clicked():
    start_timer(10)

def button_20_clicked():
    start_timer(20)

def button_30_clicked():
    start_timer(30)

def button_40_clicked():
    start_timer(40)

def button_stop_clicked():
    if start_time is not None:
        main_window.after_cancel(show_alarm)
        tkMessageBox.showinfo("stopped", "minutes passed: " + str((datetime.now() - start_time).seconds / 60))

def close():
    main_window.destroy()
    main_window.quit()

center(main_window)

start_time = None

root = Frame(main_window)
root.pack(expand=True)

row = 1

Button(root, text="10", background="green", command=button_10_clicked).grid(row=row,column=1)
Button(root, text="20", background="orange", command=button_20_clicked).grid(row=row,column=2)
Button(root, text="30", background="green", command=button_30_clicked).grid(row=row,column=3)
Button(root, text="40", background="orange", command=button_40_clicked).grid(row=row,column=4)

row += 1 #----------------------------------------------------

Frame(root,height=20).grid(row=row,column=1)

row += 1 #----------------------------------------------------

Label(root, text="started:").grid(row=row,column=1)
entry_started = Entry(root, state="readonly")
entry_started.grid(row=row,column=2, columnspan=3)

row += 1 #----------------------------------------------------

Label(root, text="finish:").grid(row=row,column=1)
entry_finish = Entry(root, state="readonly")
entry_finish.grid(row=row,column=2, columnspan=3)

row += 1 #----------------------------------------------------

Frame(root,height=20).grid(row=row,column=1)

row += 1 #----------------------------------------------------

Button(root, text="stop", background="pink", command=button_stop_clicked).grid(row=row,column=2,columnspan=2)


main_window.mainloop()

