import random

def do(father_matrix): # crossover funcionando
    # print(father_matrix)

    point = random.randint(0,8)

    son_matrix = [[-1 for x in range(point + 1)] for y in range(2)]

    for x in range(point + 1):
        son_matrix[0][x] = father_matrix[1][x]
        son_matrix[1][x] = father_matrix[0][x]

    # print(son_matrix)

    for x in range(9):
        if father_matrix[0][x] in son_matrix[0]:
            pass
        else:
            son_matrix[0].append(father_matrix[0][x])

        if father_matrix[1][x] in son_matrix[1]:
            pass
        else:
            son_matrix[1].append(father_matrix[1][x])
                    

    # print(son_matrix)

    return son_matrix