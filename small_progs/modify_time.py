import os

for i in range(1,4):
    time = os.path.getctime("./"+str(i)+".txt")
    time2 = os.path.getmtime("./"+str(i)+".txt")
    print str(time)+"   :   "+str(time2)


