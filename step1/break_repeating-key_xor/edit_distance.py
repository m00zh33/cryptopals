def string2bits(string):
    bits = list()
    for x in string:
        bits.append(format(ord(x),"08b"))

    return bits

string1 = "this is a test"
string2 = "wokka wokka!!!"

list1 = string2bits(string1)
list2 = string2bits(string2)

diferences = 0
for x in range(len(list1)):
    for y in range(8):
        if list1[x][y] != list2[x][y]:
            diferences += 1

print diferences

#print list1
#print list2
