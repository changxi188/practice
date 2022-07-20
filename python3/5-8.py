current_users = ['a1', 'b1', 'c1', 'd1']
new_users = ['a1', 'b1', 'a2', 'b2', 'c2', 'd2']

for user in new_users:
	if user in current_users:
		print("can't use users")
	else:
		print("hello " + user)

