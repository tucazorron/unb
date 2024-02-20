import Matrix

def calculate(list, matrix):
    distance = matrix[9][list[0]]
    for x in list:
        if x != 8:
            distance += matrix[list[x]][list[x+1]]
        else:
            distance += matrix[list[x]][9]
    return distance

def do(population):

    fitness_matrix = [[-1 for x in range(9)] for y in range(20)]
    matrix = Matrix.create()
    distance_list = [0 for x in range(20)]

    for x in range(len(population)):
        distance_list[x] = calculate(population[x], matrix)

    aux_list = distance_list.copy()
    aux_list.sort()

    for x in range(20):
        aux = distance_list.index(aux_list[x])
        fitness_matrix[x] = population[aux].copy()
        distance_list.pop(aux)
        
    return fitness_matrix