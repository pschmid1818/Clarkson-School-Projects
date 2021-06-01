#A practice problem on the use of random to make a dice simulator
import random
mult=input("How many to hit? ")
max=input("How many sides? ")
mod=input("Damage added? ")
rand=random.randint(1,max)
roll=(mult*rand)+mod
print(roll, " Damage Delt")
