file = open("output.txt", "w")
for i in range (40):
	#print('\tMyPictureFile OutFile' + str(i) + ';', file = file)
	#print('\tOutFile' + str(i) + '.type = 2;', file = file)
	#print('\tFILE * File' + str(i) + ' = fopen("out' + str(i) + '.bmp", "w");', file = file)
	#print('\tOutFile' + str(i) + '.outfile = File' + str(i) + ';', file = file)
	print('\tNewPicture[' + str(i) + '].out(OutFile' + str(i) + ');', file = file)