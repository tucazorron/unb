import CitysList
import FitnessFunction
import Matrix

def write(path_list, x):

    matrix = Matrix.create()
    citys_list = CitysList.create()

    print()
    print("Geracao: {}".format(x))
    print()
    print("Distancia em 100km: {}".format(FitnessFunction.calculate(path_list, matrix)))
    print()
    print("Brasilia => ", end='')
    for y in range(9):
        print("{} => ".format(citys_list[path_list[y]]), end='')
    print("Brasilia")