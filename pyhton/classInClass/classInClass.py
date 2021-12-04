# coding: utf-8

import threading
import queue
import time


class MainClass:
    # class attribute to be used in subClass
    queueTest = None
    queueStopThread = None

    def __init__(self):
        MainClass.queueTest = queue.Queue()
        MainClass.queueStopThread = queue.Queue()

    def __del__(self):
        MainClass.queueTest = None
        MainClass.queueStopThread = None

    class SubClass1(threading.Thread):
        def __init__(self):
            threading.Thread.__init__(self)

        def run(self):

            while MainClass.queueStopThread.empty():
                if not MainClass.queueTest.empty():
                    print("{} - {}".format(threading.currentThread().ident, MainClass.queueTest.get()))
            print("SubClass1: queueStopThread: {}".format(MainClass.queueStopThread.get()))

    class SubClass2(threading.Thread):
        def __init__(self):
            threading.Thread.__init__(self)

        def run(self):
            for i in range(1, 10):
                MainClass.queueTest.put(i)
                time.sleep(0.1)
            MainClass.queueStopThread.put(True)

    @staticmethod
    def run_main():
        p_subclass1 = MainClass.SubClass1()
        p_subclass1.daemon = True
        p_subclass1.start()

        p_subclass2 = MainClass.SubClass2()
        p_subclass2.daemon = True
        p_subclass2.start()

        p_subclass1.join()
        del p_subclass1
        del p_subclass2


if __name__ == "__main__":
    tM1 = MainClass()
    tM2 = MainClass()
    t1 = threading.Thread(target=tM1.run_main())
    t1.daemon = True
    t2 = threading.Thread(target=tM2.run_main())
    t2.daemon = True
    t1.start()
    t2.start()
    main_class_test = MainClass()
    main_class_test.run_main()
