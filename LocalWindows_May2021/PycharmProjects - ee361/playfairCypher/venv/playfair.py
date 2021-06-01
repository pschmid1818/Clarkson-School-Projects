

def makeKey():
    #change key
    inp = "Sphinx of black quartz judge my vow"
    #get key in lowercase
    inp = inp.casefold()

    #only allow letters
    while inp.replace(' ', '').isalpha() == 'False':
        print("Only letters allowed\n")
        inp = input('Input your key: ')

    #key string to list
    key = list(inp)

    #remove spaces
    for i in range(0, len(key) - 1):
        for j in range(0, len(key) - 1):
            if (key[j] == ' '):
                key.remove(key[j])
                break;

    #remove letters from elphabet that alreasy apper in the key
    test = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z']
    for i in range(0, len(key)):
        for j in range(0, len(test)):
            if (key[i] == test[j]):
                test.remove(test[j])
                break

    #remove diplicate letters
    temp = []
    for i in key:
        if i not in temp:
            temp.append(i)
    key = temp

    #remove j
    for i in range(0, len(key) - 1):
        if (key[i] == 'j'):
            key.remove(key[i])

    #create full key
    key.extend(test)


    #test to be sure it has all letters and it is 25 letters
    if (len(key) != 25 or keyTest(key) == 'false'):
        print("Error in key tests. Using basic key (ai,k-z)")
        key = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
               'v', 'w', 'x', 'y', 'z']

    #turn key into a matrix
    keymtrx = []
    keymtrx.append(key[:5])
    keymtrx.append(key[5:10])
    keymtrx.append(key[10:15])
    keymtrx.append(key[15:20])
    keymtrx.append(key[20:25])

    return keymtrx

def keyTest(key):
    tf = 'false'
    test = ['a','b','c','d','e','f','g','h','i','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','null']

    #if key = test remove it from test
    for i in range(0,len(key)-1):
        for j in range(0,len(test)-1):
            if(key[i] == test[j]):
                item = test[j]
                test.remove(item)
    for j in range(0,len(test)-1):
        if(key[len(key)-1] == test[j]):
            item = test[j]
            test.remove(item)

    #return true if null is the only element
    if(test == ['null']):
        tf = 'true'

    return tf

def encrypt(message):

    #make message into  a lowercase list
    message = message.casefold()
    split = list(message)
    #generate key
    key = makeKey()

    #format split message
    #ss -> sxs, j -> i, adds x at the end if its an odd number of letters
    for i in range(1, len(split) - 1):
        if(split[i - 1] == split[i]):
            split.insert(i, 'x')
        if(split[i-1] == 'j'):
            split[i-1] = 'i'
        if(split[i] == 'j'):
            split[i] = 'i'
    if (len(split) % 2 != 0):
        split.insert(len(split), 'x')

    #creates a list of the coordinates on the matrix
    temp = []
    for c in range(0, len(split)):
        for i in range(0,5):
            for j in range(0,5):
                if(key[i][j] == split[c]):
                    temp.append([i,j])

    #Encryption Process
    #dcp = double check previous, dcc = double check current
    #if the letter needs to shift from 5 -> 1 then dcc and dpp are 5 - i = 4
    en = []
    for i in range (1, len(temp), 2):
        dcp = i
        dcc = i
        #Shift down for vertical line
        if(temp[i][0] == temp[i-1][0]):
            if(temp[i-1][1] == 4):
                dcp = i - 5
            if(temp[i][1] == 4):
                dcc = i - 5
            en.append(key[temp[i-1][0]][temp[dcp-1][1]+1])
            en.append(key[temp[i][0]][temp[dcc][1]+1])

        #shift right for horizontal line
        elif(temp[i][1] == temp[i-1][1]):
            if (temp[i - 1][0] == 4):
                    dcp = i - 5
            if (temp[i][0] == 4):
                    dcc = i - 5
            en.append(key[temp[dcp-1][0]+1][temp[i-1][1]])
            en.append(key[temp[dcc][0]+1][temp[i][1]])

        #Shift across for diagonal
        else:
            en.append(key[temp[i-1][0]][temp[i][1]])
            en.append(key[temp[i][0]][temp[i-1][1]])

    #list -> string
    encrypted = ''.join(en)
    return encrypted

def decrypt(message):
    #message string -> list
    split = list(message)

    #generate key
    key = makeKey()

    #creates coordiantes for the matrix
    temp = []
    for c in range(0, len(split)):
        for i in range(0, 5):
            for j in range(0, 5):
                if (key[i][j] == split[c]):
                    temp.append([i, j])

    #Decryption process
    #dcp and dcc work the same as encryption but for 1 -> 5
    de = []
    for i in range(1, len(temp), 2):
        dcp = i
        dcc = i

        #shift up in vertical line
        if (temp[i][0] == temp[i - 1][0]):
            if (temp[i - 1][1] == -1):
                dcp = i + 5
            if (temp[i][1] - 1 == -1):
                dcc = i + 5
            de.append(key[temp[i - 1][0]][temp[dcp - 1][1] - 1])
            de.append(key[temp[i][0]][temp[dcc][1] - 1])

        #shift left in horizontal line
        elif (temp[i][1] == temp[i - 1][1]):
            dcp = i
            dcc = i
            if (temp[i - 1][0] == -1):
                    dcp = i + 5
            if (temp[i][0] == -1):
                    dcc = i + 5
            de.append(key[temp[dcp - 1][0] - 1][temp[i - 1][1]])
            de.append(key[temp[dcc][0] - 1][temp[i][1]])

        #shift across for diagonal
        else:
            de.append(key[temp[i - 1][0]][temp[i][1]])
            de.append(key[temp[i][0]][temp[i - 1][1]])

    #list -> string
    decrypted = ''.join(de)
    return decrypted

