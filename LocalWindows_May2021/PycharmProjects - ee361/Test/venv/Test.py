def factorial(x):
    fact=1
    for c in range(1,n+1):
        fact=c*fact
    print("The factorial is",fact)
    return;

def factors(x):
    temp=0
    print("Factors of ",x," are: ")
    for c in range(1,n+1):
        temp=n%c
        if temp==0:
            print(c)
    return;

n=input("Input a number: ")
n=int(n)
factorial(n)
factors(n)
