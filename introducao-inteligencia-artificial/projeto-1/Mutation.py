import random

def do(list): # essa funcao esta funcioonando

    first = random.randint(0,8)
    second = random.randint(0,8)

    if first != second:
        aux = list[first]
        list[first] = list[second]
        list[second] = aux

    return list 