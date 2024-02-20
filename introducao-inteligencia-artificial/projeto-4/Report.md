# IIA - Projeto 4

## Alunos

- Artur Filgueiras Scheiba Zorron (180013696)
- Lucas Vinicius Magalhães Pinheiro (170061001)

## Introdução

O intuito deste projeto é criar uma rede neural para poder reconhecer números a partir de um conjunto de treinamento de imagens.

## Ferramental

Foi utilizado o módulo Keras para aprendizado de máquinas, a linguagem Python para desenvolver o programa, imagens do MNIST para treinamento e validação.

## Desafio

Criar o programa e testar diferentes configurações:
1. Dados Normalizados
1. Dados Não Normalizados
1. 70% treinamento, 30% validação
1. 90% treinamento, 10% validação
1. 1 camada convolucional
1. 2 camadas convolucionais
1. 3 camadas convolucionais

## Dados Normalizados X Dados Não Normalizados

Ao não se normalizar os dados, temos diferentes variáveis com diferentes desvios totais, dando assim peso diferente a elas. Neste caso espeífico, é necessário normalizar os dados a fim de ter uma melhor perfomance da rede neural.

## [70% com 30%] x [90% com 10%]

Com diferentes valores para treinamento e para validação, obtivemos diferentes resultados finais de aprendizado da nossa máquina. Conseguimos um melhor número de acertos com 70% de treinamento e 30% de validação. Apesar de treinarmos menos os nossos dados, com mais validações conseguimos entender melhor como adequar as variáveis.

## Número de Camadas Convolucionais

As camadas convolucionais auxiliam na filtragem das imagens para conseguir montar padrões de reconhecimento dos números mostrados. Dentro do nosso programa, obtivemos mais sucesso com mais filtros (3 camadas convolucionais) pois conseguiu com mais sucesso reconhecer os números aumentado o número de acertos e diminuindo a função de perda.