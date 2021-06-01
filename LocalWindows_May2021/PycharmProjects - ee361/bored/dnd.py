import random
import values

def statroll():
    r1 = random.randrange(1, 7)
    r2 = random.randrange(1, 7)
    r3 = random.randrange(1, 7)
    r4 = random.randrange(1, 7)

    rl = [r1, r2, r3, r4]
    rl.sort()

    sr1 = int(rl[1])
    sr2 = int(rl[2])
    sr3 = int(rl[3])
    stat = sr1 + sr2 + sr3

    return stat

def getclass():
    r = random.randrange(1, 4)

    if r == 1:
        c = values.cclass('Barbarian', ['Berserker', 'Totem', 'Ancestral Guardian', 'Storm Herald', 'Zealot'], 12, 'Str', 'Con', 'Dex', 'Cha', 'Wis', 'Int')
    if r == 2:
        c = values.cclass('Bard', ['College of Lore', 'College of Valor', 'College of Glamor', 'College of Swords', 'College of Whispers'], 8, 'Cha', 'Dex', 'Con', 'Str', 'Int', 'Wis')
    if r == 3:
        c = values.cclass('Druid', ['Circle of The Land', 'Circle of the Moon', 'Circle of Dreams', 'Circle of the Shepherd'], 8, 'Wis', 'Con', 'Int', 'Str', 'Dex', 'Cha')
    if r == 4:
        c = values.cclass('Fighter', ['Champion', 'Battle Master', 'Eldritch Knight', 'Arcane Archer', 'Cavalier', 'Samurai'], 10, 'Str', 'Dex', 'Con', 'Int', 'Wis', 'Cha')
    if r == 5:
        c = values.cclass('Monk', ['Way of the Open Hand', 'Way of the Four Elements', 'Way of the Drunken Master', 'Way of the Kensei', 'Way of the Sun  Soul'], 8, 'Dex', 'Wis', 'Con', 'Cha', 'Int', 'Str')
    if r == 6:
        c = values.cclass('Paladin', ['Oath of Devotion', 'Oath of the Ancients', 'Oath of Vengeance', 'Oath of Conquest', 'Oath of Redemption'], 10, 'Str', 'Cha', 'Con', 'Wis', 'Dex', 'Int')
    if r == 7:
        c = values.cclass('Ranger', ['Hunter', 'Beast Master', 'Gloom Stalker', 'Horizon Walker', 'Monster Slayer'], 10, 'Dex', 'Wis', 'Con', 'Str', 'Int', 'Cha')
    if r == 8:
        c = values.cclass('Rogue', ['Thief', 'Arcane Trickster', 'Inquisitive', 'Mastermind', 'Swashbuckler'], 8, 'Dex', 'Int', 'Cha', 'Con', 'Str', 'Wis')
    if r == 9:
        c = values.cclass('Sorcerer', ['Draconic Bloodline', 'Wild Magic', 'Divine Soul', 'Shadow Magic', 'Storm'], 6, 'Cha', 'Con', 'Int', 'Wis', 'Dex', 'Str')
    if r == 10:
        c = values.cclass('Warlock', ['Archfey', 'Fiend', 'Great Old One', 'Hexblade', 'Celestial'], 8, 'Cha', 'Con', 'Wis', 'Int', 'Dex', 'Str')
    if r == 11:
        c = values.cclass('Wizard', ['Abjuration', 'Conjuration', 'Divination', 'Enchantment', 'Evocation', 'Illusion', 'Necromancy', 'Transmutation', 'War Magic', ], 6, 'Int', 'Con', 'Dex', 'Wis', 'Cha', 'Str')
    if r == 12:
        c = values.cclass('Cleric', ['Knowledge Domain', 'Life Domain', 'Light Domain', 'Nature Domain', 'Tempest Domain', 'Trickery Domain', 'War Domain', 'Forge Domain', 'Grave Domain'], 8, 'Wis', 'Str', 'Con', 'Int', 'Dex', 'Cha')

    return c

def getrace():
    x = random.randrange(1, 10)

    if x == 1:
        r = values.race('Dwarf', 25, 50, 350, ['Hill', 'Stout'])
    if x == 2:
        r = values.race('Elf', 30, 75, 750, ['High', 'Wood', 'Dark'])
    if x == 3:
        r = values.race('Halfling', 25, 20, 250, ['Stout', 'Lightfoot'])
    if x == 4:
        r = values.race('Human', 30, 18, 70, ['Normal', 'Variant'])
    if x == 5:
        r = values.race('Dragonborn', 30, 15, 80, ['Black', 'Blue', 'Brass', 'Bronze', 'Copper', 'Gold', 'Green', 'Red', 'Silver', 'White'])
    if x == 6:
        r = values.race('Gnome', 25, 30, 400, ['Forest', 'Rock'])
    if x == 7:
        r = values.race('Elf', 30, 20, 180, ['Half', 'Half'])
    if x == 8:
        r = values.race('Orc', 30, 14, 75, ['Half', 'Half'])
    if x == 9:
        r = values.race('Tiefling', 30, 18, 75, ['Red', 'Pink', 'Peach', 'Edgy', 'White', 'Pale', 'Black', 'Brown', 'Purple'])

    return r

def getbackground():
    x = random.randrange(1, 14)

    if x == 1:
        b = values.background('Acolyte')
    if x == 2:
        b = values.background('Charlatan')
    if x == 3:
        b = values.background('Criminal')
    if x == 4:
        b = values.background('Entertainer')
    if x == 5:
        b = values.background('Folk Hero')
    if x == 6:
        b = values.background('Guild Artisan')
    if x == 7:
        b = values.background('Hermit')
    if x == 8:
        b = values.background('Noble')
    if x == 9:
        b = values.background('Outlander')
    if x == 10:
        b = values.background('Sage')
    if x == 11:
        b = values.background('Sailor')
    if x == 12:
        b = values.background('Soldier')
    if x == 13:
        b = values.background('Urchin')

    return b