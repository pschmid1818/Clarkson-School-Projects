import playfair

plaintext = 'Kiss my ass'

encrypted = playfair.encrypt(plaintext)

decrypted = playfair.decrypt(encrypted)

print("Key:\n", playfair.makeKey(), "\nOriginal Message:  ", plaintext, "\nEncrypted Message: ", encrypted, "\nDecrypted Message: ", decrypted)

