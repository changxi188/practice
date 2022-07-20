def make_shirt(size = 'x', word = 'i love python'):
	print("the shirt size : " + size + ", the word on the shirt" + word)


make_shirt()
make_shirt('xl', 'i i i')


def make_album(singer, cd):
	return {singer : cd}


cd1 = make_album('a', 'cda')
print(cd1)
cd2 = make_album('b', 'cdb')
print(cd2)

while True:
	singer = input("singer name : ")
	print(singer)
	if singer == 'q':
		break;
	cd = input("cd name : ")
	if cd == 'q':
		break;
	print(make_album(singer, cd))
	

