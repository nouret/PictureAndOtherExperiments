file = open("Без имени.bmp", "rb")
s = file.read()
print(len(s))
for elem in s:
	print(hex(elem))
print()
