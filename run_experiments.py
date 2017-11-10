
import ctypes
numTrials = 10
numRandNums = 10000000
seed = 10

def main():
    print "Loading in libourprng shared library"

    libourprng = ctypes.CDLL("/Users/Ameha/Desktop/Gifans Stuffs/360_stuff/libourprng.so")

    print "Loading xorshift32 algorithm"
    xorshift32 = libourprng.xorshift32
    xorshift32.restype = ctypes.c_uint32

    print "Testing xorshift32"
    startState = ctypes.c_uint32(seed)
    pStartState = ctypes.pointer(startState)
    print "Start seed is " + str(seed)

    for i in range(numRandNums):
        print "I got the value {0: d}".format(xorshift32(pStartState))


if __name__ == "__main__":
    main()
