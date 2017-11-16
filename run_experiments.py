import ctypes
import difflib
import sys
from pprint import pprint

def main():
    numTrials = 10
    numRandNumsList = [2 ** 1, 2 ** 2, 2 ** 3, 2 ** 4, 2 ** 5, 2 ** 6,
                       2 ** 7, 2 ** 8, 2 ** 9, 2 ** 10, 2 ** 11, 2 ** 12,
                       2 ** 13, 2 ** 14, 2 ** 15, 2 ** 16]
    seed = 1000
    testing = True

    # Load libourprng shared library/dll
    libourprng = ctypes.CDLL("libourprng.so")

    # Load prng functions and set their return types
    xorshift32 = libourprng.xorshift32
    xorshift32.restype = ctypes.c_uint32
    prngList = [xorshift32]

    # Set start state
    seed = ctypes.c_uint32(seed)
    seedPtr = ctypes.pointer(seed)

    if testing:
        testPRNGs(prngList, seedPtr, numRandNums[16])
    else:
        print "Need to implement timing"


def testPRNGs(prngList, seed, numRandNums):
    # For all prng functions in prngList, generate numRandNums random
    # numbers given seed. Print these numbers to a file
    for prng in prngList:
        # Open python out file for writing
        filename = "output_files/py_" + prng.__name__ + "_out.txt"
        pyOutFile = open(filename, "w")

        # Write values
        writeValues(pyOutFile, prng, seed, numRandNums)

        # Open out files for reading
        cFilename = "output_files/c_" + prng.__name__ + "_out.txt"
        cOutFile = open(cFilename, "r")
        pyOutFile = open(filename, "r")

        # Diff the output files
        diff(cOutFile, filename, pyOutFile, cFilename)

        # Close files
        pyOutFile.close()
        cOutFile.close()

# Generates numRandNums random numbers using prng given seed, and
# writes the values to file
def writeValues(file, prng, seed, numRandNums):
    for j in range(numRandNums):
        file.write("{0:d}\n".format(prng(seed)))

# Checks each line of file1 and file2 and determines if they are different.
# If so, it gives an error with the line number of the difference (starting)
# at 1, and closes the files and exits.
def diff(file1, file1Name, file2, file2Name):
    differ = difflib.Differ()
    file1Lines = file1.readlines()
    file2Lines = file2.readlines()
    buf1 = []
    buf2 = []

    # Check if number of lines differ
    if len(file2Lines) != len(file1Lines):
        print "Test Error: " + file1Name + " and " + file2Name + "differ in length."
        file2.close()
        file1.close()
        sys.exit()

    # Check if lines differ per 100 lines
    for n, lines in enumerate(zip(file2Lines, file1Lines)):
        # Keep adding until there are 100 elements in buf1 and buf2
        if not (n % 100 == 0):
            buf1.append(lines[0])
            buf2.append(lines[1])
        elif n != 0:
            diff = list(differ.compare(buf1, buf2))
            buf1 = []
            buf2 = []
            diffIndex = checkDiff(diff)

            if diffIndex >= 0:
                print "Test Error: " + file1Name + " and " + file2Name + "differ starting at line " + repr(n-100 + diffIndex + 1)
                file2.close()
                file1.close()
                sys.exit()
        # Handle special case with diff at n = 0
        else:
            buf1.append(lines[0])
            buf2.append(lines[1])
            diff = list(differ.compare(buf1, buf2))
            diffIndex = checkDiff(diff)

            if diffIndex >= 0:
                print "Test Error: " + file1Name + " and " + file2Name + "differ starting at line 1"
                file2.close()
                file1.close()
                sys.exit()

    # Check diff of remaining if last chunk does not have 100 lines
    diff = list(differ.compare(buf1, buf2))
    diffIndex = checkDiff(diff)

    if diffIndex >= 0:
        print "Test Error: " + file1Name + " and " + file2Name + "differ starting at line " + repr(n - 100 + diffIndex)
        file1.close()
        file2.close()
        sys.exit()

# difflib compare function has a particular output, that also says whether
# 2 lines are the same, rather than just saying if 2 lines are different.
# So return that there is a difference, if it is the case that we don't
# get two lines being the same
def checkDiff(diff):
    for i, diffLine in enumerate(diff):
        if diffLine[:2] != "  ":
            return(i)
    return(-1)

if __name__ == "__main__":
    main()
