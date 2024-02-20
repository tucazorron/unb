# Grade Horária

O SIGAA é legal, mas poderia ser melhor! E se algumas funcionalidades fossem integradas? Poder gerenciar sua grade horária ou a alocação de salas tornariam a experiência com o sistema muito melhor. Capaz de atender esta demanda, a turma de APC resolveu implementar o vulgarmente conhecido como SAD (☹️) - Sistema de Apoio ao Discente, uma plataforma flexível que proverá soluções para todos!

A primeira funcionalidade a ser criada é a de gerenciamento de grade horária, de modo que a matrícula no próximo semestre ocorra de forma mais fluida. Implemente as seguintes funcionalidades para os comandos indicados:

```
+ COD DTH1 ... DTHn acrescenta a disciplina 𝐶𝑂𝐷 nos horários 𝐷𝑇𝐻1,𝐷𝑇𝐻2,…𝐷𝑇𝐻𝑛. Há um espaço entre cada elemento do comando.

- COD DTH1 ... DTHn retira a disciplina 𝐶𝑂𝐷 dos horários 𝐷𝑇𝐻1,𝐷𝑇𝐻2,…𝐷𝑇𝐻𝑛. Há um espaço entre cada elemento do comando.

? mostra a grade horária semanal.

Hasta la vista, beibe! interrompe a execução do programa.
````

Todo COD tem o formato XXX####Y, onde XXX identifica a unidade responsável pela oferta, #### o código da disciplina e Y a turma ofertada no horário. Por exemplo, CIC0004B é a turma B disciplina Algoritmos e Programação de Computadores, que é ofertada pelo Departamento de Ciência da Computação. Cada turma é ofertada em horários específicos no formato 𝐷𝑇𝐻, onde 𝐷 define o(s) dia(s) da semana, 𝑇 o turno e 𝐻 a(s) hora(s) da(s) aula(s). Por exemplo, 35𝑀12 são aulas as terças (3) e quintas (5), no período da manhã (𝑀), nos horários 1 e 2. A UnB atua nos três turnos: matutino (𝑀), vespertino (𝑇) e noturno (𝑁) - você pode ver mais detalhes no sítio da instituição.

A exibição da grade deve seguir um formato específico de tabela, que apresenta todos os dias da semana, mas somente os horários com matricula registrada. As linhas horizontais são compostas pelo caractere '-'; as verticais pelo '|' e as interseções pelo '+'. A primeira informação apresenta os dias úteis da semana, representados pelas siglas Seg, Ter, Qua, Qui, Sex e Sab, nesta ordem. As demais informações apresentam, cada uma, um dos horários previstos para aula. A primeira coluna apresenta a duração da aula, e as demais os códigos das disciplinas, se houver a matrícula nesse horário. Sempre há pelo menos um espaço entre os caracteres de linha vertical e o conteúdo.

É garantido que o conjunto de instruções fornecidos é sintaticamente correto. Caso não seja possível atualizar a grade, apresente a mensagem: '!(instr)', onde instr é a instrução fornecida. Exemplos de atualizações não permitidas são a adição de disciplinas com choque de horário e a remoção de uma disciplina que não está na grade.

## Entrada

A entrada consiste de uma quantidade indeterminada de instruções, dentre as 3 primeiras descritas acima, apresentadas uma por linha, seguidas da instrução de finalização do processamento.

## Saída

A saída consiste na apresentação das informações, quando solicitadas/necessárias.

## Observações

Nos turnos diurnos, cada horário 𝐻 representa um crédito, ou seja, 55 minutos de aula (e consideram-se 10 minutos de intervalo a cada 2 horários) - são 5 horários possíveis de manhã e 6 a tarde. Já no noturno, cada crédito tem 50 minutos (também consideram-se 10 minutos de intervalo a cada 2 horários) - são 4 horários possíveis.