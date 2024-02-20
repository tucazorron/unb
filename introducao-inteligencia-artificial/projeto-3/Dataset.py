import pandas as pd

matrix = pd.read_excel('Dataset.xlsx') # inicializa matriz com valores do Dataset.xlsx
matrix = matrix.fillna(0)
