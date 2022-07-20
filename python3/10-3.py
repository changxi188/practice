def guest():
	filename = './guest.txt'
	with open(filename, 'w') as file_object:
		while True:
			name = input("please enter you name\n")

			if name == 'q':
				break
			
			file_object.write(name + '\n')



guest();
