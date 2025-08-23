list = {}
while True:
    try:
        inp = input()
        inp = inp.upper()
        if inp in list:
            list[inp] += 1
        else:
            list[inp] = 1

    except  EOFError :
        break
    except KeyError:   
        pass
sorted(list)
for i in list.keys():
    print(f"{list[i]} {i}")