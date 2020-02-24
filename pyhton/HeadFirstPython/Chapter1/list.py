moves = ["Argo","the war of word III","Mr. Gump"]

print(moves[0])
print(moves[1])
print(moves[2])

print(len(moves))

moves.append("the war of the star")
print(moves)

moves.pop()
print(moves)

moves.extend(["unchained jaogo","spy in spy"])
print(moves)

moves.remove("Argo")
print(moves)

moves.insert(1,1865)
moves.insert(3,1900)
moves.insert(5,2011)
moves.insert(7,2015)
print(moves)

count=0
while count<len(moves):
    print(moves[count])
    count+=1

for each_move in moves:
    print(each_move)

#print(moves[10])

movies = ["The Holy Grail", 1975, "Terry Jones & Terry Gilliam", 91,
          ["Graham Chapman", ["Michael Palin", "John Cleese",
                              "Terry Gilliam", "Eric Idle", "Terry Jones"]]]
print(movies)