# Boltzmann Wealth Model

Artur Filgueiras Scheiba Zorron - 180013696

## Apresentação

O modelo computacional de riqueza de Boltzmann é um modelo dinâmico de acúmulo e de trocas de riqueza. Sua proposta é que os agentes do modelo randomicamente selecionem com quais outros agentes adjacentes eles irão trocar riqueza. A cada passo na simulação, calcula-se o índice Gini.

O índice Gini é um índice que mensura o quão uma sociedade é economicamente desigual. Ele é inversamente proporcional à desigualdade. Ele varia de 0 a 1. Uma sociedade igualitária tende a 0, uma sociedade desigual tende a 1.

O modelo computacional de riqueza de Boltzmann proposto por mim é um modelo dinâmico de acúmulo e de trocas de riqueza com dois elementos a mais. Neste novo modelo, existe uma probabilidade de doação de riqueza entre os agentes. Caso a doação aconteça em alguma troca monetária, o agente com menos dinheiro recebe metade da diferença monetária entre ele e o agente com mais dinheiro. Em outras palavras, quando uma doação ocorre, os dois agentes terminam com o mesmo montante de dinheiro podendo ter um erro de 1 moeda nesse cálculo caso a somatória dos dois montantes envolvidos na transação seja ímpar. E a cada passo da simulacão, calcula-se o índice Gini com o desvio padrão da riqueza dos agentes.

O desvio padrão é um cáculo estatístico que calcula a variância de uma amostra.

## Hipótese causal

A hipótese causal que quero comprovar é de que quanto maior a cultura de doação em uma sociedade, maior a probabilidade de que a riqueza dos agentes sejam equilibradas levando a uma sociedade menos desigual com um menor índice Gini e um menor desvio padrão da riqueza dos agentes.

## Alterações no código

Adicionei duas variáveis para o modelo: uma independente e uma dependente.

Independente: Probabilidade de doação de riqueza. Varia de 0 a 1, em intervalos de 0.1. Indica a probabilidade de doação de riqueza.

Dependente: Desvio padrão da riqueza dos agentes. Indica o desvio padrão da riqueza dos agentes.

## Como usar o simulador

Instale os pacotes:

- jupyter
- matplotlib
- mesa
- numpy

Execute o comando `make run` para executar o simulador no navegador.

Execute o comando `make batch_run` para executar o simulador em batch mode.
