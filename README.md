# RSA-encryption

This project makes use of the RSA encryption algorithm to both encrypt and decrypt a text file.  The program takes a file as a command line argument and automatically encrypts or decrypts the file based on the file extension. If a text file with the .txt extension is inputted, the program will encrypt the file and create a new file with the .rsa extension. If the file with the .rsa extension is inputted, the program will decrypt the file and create a new file with the .decrypted extension. This program never deletes the old files, so the original, cipher text, and decrypted files can always be examined. The program prints out error messages if no command line argument is detected or if the file does not have the proper file extensions. The makefile was edited so that ‘make clean’ deletes .rsa and .decrypted files but does not delete .txt files.

The MakeFile and GMPStringUtilities.h were provided by instructor but slightly edited.

Known issues: 
  Only works on very small text files (less than 75 characters), a block system could probably be implemented to handle this.
  Due to issues with decryption, the cipher is not scrambeled text but the integer after being manipulated by the RSA algorithm.
