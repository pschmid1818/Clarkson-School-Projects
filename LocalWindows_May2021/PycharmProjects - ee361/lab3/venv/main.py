import cipher

enc1 = input("Message encrypted using Transposition: ")
print(cipher.scramble2Decrypt(enc1))

enc2 = input("Message encrypted using Substitution: ")
key1 = input("Random key for substitution: ")
print(cipher.substitutionDecrypt(enc2,key1))

enc3 = input("Message encrypted using Substitution: ")
key2 = input("Manual Key for substitution: ")
print(cipher.substitutionDecrypt(enc3,cipher.genKeyFromPass(key2)))

