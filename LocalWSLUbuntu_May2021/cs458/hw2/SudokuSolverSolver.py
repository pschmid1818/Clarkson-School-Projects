import math

def main():

#switch commented and non commented code for input
#    n = input('Size of board (give n as in nxn): ')
    n = 4
    root = int(math.sqrt(n))

#    givlen = input('How many givens? ')
    givlen= 7
#    given = []
#    if givlen != 0:
#        for i in range(givlen):
#            x = input('What is the x? ')
#            y = input('What is the y? ')
#            v = input('What is the value? ')
#            given.append("p" + str(x) + str(y) + str(v))

    given = ["p121", "p133", "p212", "p343", "p422", "p431", "p444"]

    f = open("SudokuSolver" + str(n) + "x" + str(n) + ".txt", "w")
    f.write(";Compiling with rise4fun.com for z3\n;Written by Paul Schmid with help from Dr. Lynch\n\n")


    f.write(";Variable declaration\n;p is filler, x = 1, y = j, value = k\n")
    #Variable declaration
    for i in range(1, n+1):
        for j in range(1, n+1):
            for k in range(1, n+1):
                s = "(declare-const p" + str(i) + str(j) + str(k) + " Bool)\n"
                f.write(s)

    f.write("\n")

    f.write(";Rule 1 - cant have the same number in the same row\n")
    for i in range(1, n+1):
        for j in range(1, n+1):
            for k in range(1, n+1):
                if (j+1 <= n):
                    s = "(assert (not (and p" + str(i) + str(j) + str(k) + " p" + str(i) + str(j+1) + str(k) + ")))\n"
                    f.write(s)

    f.write("\n")

    f.write(";Rule 2 - cant have the same number in the same column\n")
    for i in range(1, n+1):
        for j in range(1, n+1):
            for k in range(1, n+1):
                if (i+1 <= n):
                    s = "(assert (not (and p" + str(i) + str(j) + str(k) + " p" + str(i+1) + str(j) + str(k) + ")))\n"
                    f.write(s)

    f.write("\n")

#        -root-> -root-> -root->
#        ----------n---------> i
#   |  | = = = | = = = | = = =
# root | = = = | = = = | = = =
#   |  | = = = | = = = | = = = 
#   V  | ------+-------+------
#   |  | = = = | = = = | = = =
# root n = = = | = = = | = = =
#   |  | = = = | = = = | = = = 
#   V  | ------+-------+------
#   |  | = = = | = = = | = = =
# root | = = = | = = = | = = =
#   |  | = = = | = = = | = = = 
#   V  V ------+-------+------
#      j

    # imod and jmod give an offset of root so imod = 2 means 2 root distances
    f.write(";Rule 3 - each box of sqrt(n) cant contain the same number\n")
    for imod in range(0, root):             
        for jmod in range(0, root):
            for k in range(1, n+1):
                s = "(assert (xor "
                for i in range((imod * root)+1, (imod * root) + int(root) + 1):
                    for j in range((jmod * root)+1, (jmod * root) + int(root) + 1):
                        s = s + "p" + str(i) + str(j) + str(k) + " "
                s = s.rstrip() +  "))\n"
                f.write(s)        

    f.write("\n")

    f.write(";Rule 4 - each cell must have a number\n")
    for i in range(1, n+1):
        for j in range(1, n+1):
            s = "(assert (or "
            for k in range(1, n):
                s = s + "p" + str(i) + str(j) + str(k) + " "
            s = s + "p" + str(i) + str(j) + str(n) + "))\n"
            f.write(s)

    f.write("\n")

    f.write(";Rule 5 - No cell contains 2 digits (unnecessary)\n")

    f.write("\n")

    string = ";Inital Configuration with given:\n;"
    if givlen != 0:
        for i in given:
            string = string + str(i) + " "
        f.write(string + "\n")

        #s = "(assert (not (or "
        for i in range(1, n+1):
            for j in range(1, n+1):
                for k in range(1, n+1):
                    for y in given:
                        giv = "p" + str(i) + str(j) + str(k)
                        if y == giv:
                            for z in range(1, n+1):
                                cur = "p" + str(i) + str(j) + str(z)
                                if giv != cur:
                                    s = "(assert (not " + cur + "))\n"
                                    f.write(s)
        #s = s.rstrip() + ")))\n"
        #f.write(s)
    else:
        string = string + "No given values input"
        f.write(string + "\n")

    f.write("\n")

    f.write("(check-sat)\n(exit)")

    f.close()

#def squaretest(imod, jmod, n, root):

if __name__ == "__main__":
    main()