def print_lol(List):
	for each in List:
		if isinstance(each,list):
			print_lol(each)
		else:
			print(each)

movies=['Star Wars','Argo','Ice World',["subclass:",'test1']]

print_lol(movies)

	
