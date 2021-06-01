import dnd
import random

s1 = dnd.statroll()
s2 = dnd.statroll()
s3 = dnd.statroll()
s4 = dnd.statroll()
s5 = dnd.statroll()
s6 = dnd.statroll()

sl = [s1, s2, s3, s4, s5, s6]

sl.sort()

b = dnd.getbackground()
r = dnd.getrace()
cc = dnd.getclass()

print(r.subrace[random.randrange(0, len(r.subrace))], r.name, b. name, 'aged', random.randrange(r.minage, r.maxage+1))
print(cc.subclass[random.randrange(0, len(cc.subclass))], cc.name)

print(cc.stat1, sl[5])
print(cc.stat2, sl[4])
print(cc.stat3, sl[3])
print(cc.stat4, sl[2])
print(cc.stat5, sl[1])
print(cc.stat6, sl[0])
