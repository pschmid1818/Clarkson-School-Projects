class cclass:
    def __init__(self, name, subclass, hitdie, stat1, stat2, stat3, stat4, stat5, stat6, ):
        self.name = name
        self.subclass = subclass
        self.hitdie = hitdie
        self.stat1 = stat1
        self.stat2 = stat2
        self.stat3 = stat3
        self.stat4 = stat4
        self.stat5 = stat5
        self.stat6 = stat6


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

class proficencies:
    def __init__(self, acrobatics, animalhandling, arcana, athletics, deception, history, History, insight, intimidation, investivation, medicine, nature, perception, performance, persuasion, religion, sleightofhand, stealth, survival):
        self.acrbatics = acrobatics
        self.animalhandling= animalhandling
        self.arcana = arcana
        self.atheletics = athletics