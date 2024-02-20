import CrossOver
import Mutation

def create(old_population):

    # for x in range(len(old_population)):
    #     print(old_population[x])


    new_population = [[-1 for x in range(9)] for y in range(20)]
    matrix_aux = [[-1 for x in range (9)] for y in range(2)]

    new_population[0] = old_population[0].copy()

    for x in range(5):
        y = x * 2
        matrix_aux[0] = old_population[y].copy()
        matrix_aux[1] = old_population[y + 1].copy()
        matrix_aux = CrossOver.do(matrix_aux).copy()
        new_population[y + 1] = matrix_aux[0].copy()
        new_population[y + 2] = matrix_aux[1].copy()

    for x in range(9):
        y = x + 11
        new_population[y] = Mutation.do(old_population[y]).copy()

    return new_population
