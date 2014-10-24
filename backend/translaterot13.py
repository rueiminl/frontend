import string 

rot13 = string.maketrans( 
    "ABCDEFGHIJKLMabcdefghijklmNOPQRSTUVWXYZnopqrstuvwxyz", 
    "NOPQRSTUVWXYZnopqrstuvwxyzABCDEFGHIJKLMabcdefghijklm")

file = open('banned.txt', 'r')
out = open('bannedrot13.txt', 'w')


for line in file:
	out.write(string.translate(line, rot13))
