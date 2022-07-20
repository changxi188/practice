person1 = {"first_name" : "cheng", "last_name" : "changxi", "age" : "10", "city" : "zj"}

person_list = []

first_names = ["cheng", "li", "zhou"]

last_names = ["changxi", "lin", "yue"] 

ages = ["25", "26", "27"]

citys = ["js", "gz", "zj"]

for i in range(0, 3):
	person_list.append({"first_name" : first_names[i], "last_name" : last_names[i], "age" : ages[i], "city" : citys[i]})


for person in person_list:
	print(person)


beauties = ['a', 'b']

print(beauties)

traveler = {
	"li" : ['sh', 'bj', 'gz', 'sz'],
	"wang" : ['zj', 'gd', 'bj'],
	"qian" : ['nj', 'fj', 'xm']
}

print(traveler)


for k, v in traveler.items():
	print(v)


a = '1'
print(a)
