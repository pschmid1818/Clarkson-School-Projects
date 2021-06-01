import sys
import threading
import time 
import random

n = 0
customers = 0
closing = 0

mutex = threading.Lock()
customerSem = threading.Lock()
barberSem = threading.Lock()
customerDone = threading.Lock()
barberDone = threading.Lock()

def kickOutCustomers():
    for i in customerThreads:
        balk(customerThreads[i])

def cutHair():
    print("Barber is cutting hair...\n")

def getHairCut(self):
    print("Thread " + str(self) + " is getting its hair cut...\n")

def balk(self):
    print("Screw you guys, Thread " + str(self) + " is going home\n")
    mutex.release()
    self.kill()

def barberRunner():
    print("Barber arrived\n")
    start = time.thread_time()
    shift = time.thread_time() - time.thread_time()

    while (shift < 15.0):
        customerSem.acquire()
        barberSem.release()

        cutHair()
        
        customerDone.acquire()
        barberDone.release()

        shift = time.thread_time() - time.thread_time()

    kickOutCustomers()
    closing = 1
    print("Barber is leaving!\n")
    barber.kill()

def customerRunner():
    self = threading.current_thread()

    mutex.acquire()
    if customers >= n:
        balk(self)
    customers += 1
    mutex.release()

    customerSem.release()
    barberSem.acquire()

    getHairCut(self)

    customerDone.release()
    barberDone.acquire()

    mutex.acquire()
    customers -= 1
    mutex.release()

    self.kill()

barber = threading.Thread(target=barberRunner)
customerThreads = []

if __name__ == "__main__":

    if len(sys.argv) != 2:
        sys.exit("./BarbershopP n\nWhere n = number of seats\n")

    n = sys.argv[1]

    barberSem.acquire()
    barberDone.acquire()
    customerSem.acquire()
    customerDone.acquire()

    barber.start()

    while not (closing):
        random.seed(time.time())
        x = random.randint(0,6)

        print("Creating " + str(x) + " threads...\n")

        time.sleep(3)

        for i in range (1, x):
            t = threading.Thread(target=customerRunner)
            customerThreads.append(t)
            t.start()

    barber.join()


    
