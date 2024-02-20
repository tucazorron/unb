import InitialPopulation
import FitnessFunction
import NewPopulation
import Results

def main():

    population = InitialPopulation.create()

    for x in range(1000):
        fitness_matrix = FitnessFunction.do(population).copy()
        population = NewPopulation.create(fitness_matrix).copy()
        Results.write(fitness_matrix[0], x)

main()