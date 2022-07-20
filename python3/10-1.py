def read_file():

	file_list = []
	with open("./learning_python.txt") as file_object:
		file_list = file_object.readlines()
		for i in range(3):		
			print(file_list)

def write_file():
	file_name = 'programing.txt'
	with open(file_name, 'w') as file_object:
		file_object.write("I love money\n")
		file_object.write("I love python\n")
	


read_file()
write_file()
