class cclass:
    def __init__(self, name, subclass, hitdie, str, dex, con, int, wis, cha, ):
        self.name = name
        self.subclass = subclass
        self.hitdie = hitdie
        self.str = str
        self.dex = dex
        self.con = con
        self.int = int
        self.wis = wis
        self.cha = cha

class race:
    def __init__(self, name, speed, minage, maxage, subrace):
        self.name = name
        self.speed = speed
        self.minage = minage
        self.maxage = maxage
        self.subrace = subrace


class background:
    def __init__(self, name):
        self.name = name