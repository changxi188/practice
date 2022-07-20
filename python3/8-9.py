magicians = ['a', 'b', 'c']


def show_magicians(magicians):
	for i in range(0,len(magicians)):
		magicians[i] += " the great"

	return magicians



b = show_magicians(magicians[:])

print(magicians)
print(b)
