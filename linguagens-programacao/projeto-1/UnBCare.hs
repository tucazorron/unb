{-# LANGUAGE TupleSections #-}

module UnBCare where

import Data.Bifunctor (Bifunctor (second))
import Data.List (intersect, sort)
import Data.Maybe (isJust)
import ModeloDados

{-

██╗░░░██╗███╗░░██╗██████╗░  ░█████╗░░█████╗░██████╗░██████╗
██║░░░██║████╗░██║██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗██╔════╝
██║░░░██║██╔██╗██║██████╦╝  ██║░░╚═╝███████║██████╔╝█████╗░░
██║░░░██║██║╚████║██╔══██╗  ██║░░██╗██╔══██║██╔══██╗██╔══╝░░
╚██████╔╝██║░╚███║██████╦╝  ╚█████╔╝██║░░██║██║░░██║███████╗
░╚═════╝░╚═╝░░╚══╝╚═════╝░  ░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝

O objetivo desse trabalho é fornecer apoio ao gerenciamento de cuidados a serem prestados a um paciente.
O paciente tem um receituario médico, que indica os medicamentos a serem tomados com seus respectivos horários durante um dia.
Esse receituário é organizado em um plano de medicamentos que estabelece, por horário, quais são os remédios a serem
tomados. Cada medicamento tem um nome e uma quantidade de comprimidos que deve ser ministrada.
Um cuidador de plantão é responsável por ministrar os cuidados ao paciente, seja ministrar medicamento, seja comprar medicamento.
Eventualmente, o cuidador precisará comprar medicamentos para cumprir o plano.
O modelo de dados do problema (definições de tipo) está disponível no arquivo ModeloDados.hs
Defina funções que simulem o comportamento descrito acima e que estejam de acordo com o referido
modelo de dados.

-}

{-

QUESTÃO 1, VALOR: 1,0 ponto

Defina a função "comprarMedicamento", cujo tipo é dado abaixo e que, a partir de um medicamento, uma quantidade e um
estoque inicial de medicamentos, retorne um novo estoque de medicamentos contendo o medicamento adicionado da referida
quantidade. Se o medicamento já existir na lista de medicamentos, então a sua quantidade deve ser atualizada no novo estoque.
Caso o remédio ainda não exista no estoque, o novo estoque a ser retornado deve ter o remédio e sua quantidade como cabeça.

-}

comprarMedicamento :: Medicamento -> Quantidade -> EstoqueMedicamentos -> EstoqueMedicamentos
comprarMedicamento med qtd xs =
  if any (\(x, _) -> x == med) xs
    then atualizarEstoque med qtd xs
    else (med, qtd) : xs

atualizarEstoque :: (Eq a, Num b) => a -> b -> [(a, b)] -> [(a, b)]
atualizarEstoque _ _ [] = error "ERRO: lista vazia"
atualizarEstoque x y ((x', y') : xs)
  | x == x' = (x, y + y') : xs
  | otherwise = (x', y') : atualizarEstoque x y xs

{-

QUESTÃO 2, VALOR: 1,0 ponto

Defina a função "tomarMedicamento", cujo tipo é dado abaixo e que, a partir de um medicamento e de um estoque de medicamentos,
retorna um novo estoque de medicamentos, resultante de 1 comprimido do medicamento ser ministrado ao paciente.
Se o medicamento não existir no estoque, Nothing deve ser retornado. Caso contrário, deve se retornar Just v,
onde v é o novo estoque.

-}

tomarMedicamento :: Medicamento -> EstoqueMedicamentos -> Maybe EstoqueMedicamentos
tomarMedicamento _ [] = Nothing
tomarMedicamento med (all@(med', qtd) : xs)
  | med == med' && qtd > 0 = Just $ (med', qtd -1) : xs
  | med == med' && qtd <= 0 = Nothing
  | otherwise = (all :) <$> tomarMedicamento med xs

{-

QUESTÃO 3  VALOR: 1,0 ponto

Defina a função "consultarMedicamento", cujo tipo é dado abaixo e que, a partir de um medicamento e de um estoque de
medicamentos, retorne a quantidade desse medicamento no estoque.
Se o medicamento não existir, retorne 0.

-}

consultarMedicamento :: Medicamento -> EstoqueMedicamentos -> Quantidade
consultarMedicamento med [] = 0
consultarMedicamento med (all@(med', qtd) : xs)
  | med == med' = qtd
  | otherwise = consultarMedicamento med xs

{-

QUESTÃO 4  VALOR: 1,0 ponto

Defina a função "demandaMedicamentos", cujo tipo é dado abaixo e que computa a demanda de todos os medicamentos
por um dia a partir do receituario. O retorno é do tipo EstoqueMedicamentos e deve ser ordenado lexicograficamente
pelo nome do medicamento.

Dica: Observe que o receituario lista cada remédio e os horários em que ele deve ser tomado no dia.
Assim, a demanda de cada remédio já está latente no receituario, bastando contar a quantidade de vezes que cada remédio
é tomado.

-}

quickSort :: Ord a => [a] -> [a]
quickSort [] = []
quickSort (x : xs) = quickSort (filter (<= x) xs) ++ [x] ++ quickSort (filter (> x) xs)

demandaMedicamentos :: Receituario -> EstoqueMedicamentos
demandaMedicamentos = quickSort . map (Data.Bifunctor.second length)

{-

QUESTÃO 5  VALOR: 1,0 ponto, sendo 0,5 para cada função.

Um receituário é válido se, e somente se, todo os medicamentos são distintos e estão ordenados lexicograficamente e,
para cada medicamento, seus horários também estão ordenados e são distintos.

Inversamente, um plano de medicamentos é válido se, e somente se, todos seus horários também estão ordenados e são distintos,
e para cada horário, os medicamentos são distintos e são ordenados lexicograficamente.

Defina as funções "receituarioValido" e "planoValido" que verifiquem as propriedades acima e cujos tipos são dados abaixo:

-}

verificaOrdenacao :: Ord a => [a] -> Bool
verificaOrdenacao [] = True
verificaOrdenacao [x] = True
verificaOrdenacao (x : y : xs) = x < y && verificaOrdenacao (y : xs)

receituarioValido :: Receituario -> Bool
receituarioValido rec = verificaOrdenacao names && all verificaOrdenacao times
  where
    names = map fst rec
    times = map snd rec

planoValido :: PlanoMedicamento -> Bool
planoValido plan = verificaOrdenacao times && all verificaOrdenacao meds
  where
    times = map fst plan
    meds = map snd plan

{-

QUESTÃO 6  VALOR: 1,0 ponto,

Um plantão é válido se, e somente se, todas as seguintes condições são satisfeitas:

1. Os horários da lista são distintos e estão em ordem crescente;
2. Não há, em um mesmo horário, ocorrência de compra e medicagem de um mesmo medicamento (e.g. `[Comprar m1, Medicar m1 x]`);
3. Para cada horário, as ocorrências de Medicar estão ordenadas lexicograficamente.

Defina a função "plantaoValido" que verifica as propriedades acima e cujo tipo é dado abaixo:

-}

plantaoValido :: Plantao -> Bool
plantaoValido p = verificaOrdenacao times && all verificaOrdenacao meds' && valid
  where
    times = map fst p
    cs = map snd p
    meds = map (filter medicar) cs

    compras = map (filter comprar) cs

    medicar (Medicar _) = True
    medicar _ = False

    comprar (Comprar _ _) = True
    comprar _ = False

    meds' = map (map (\(Medicar m) -> m)) meds
    compras' = map (map (\(Comprar m _) -> m)) compras

    valid = all null $ zipWith Data.List.intersect meds' compras'

{-

QUESTÃO 7  VALOR: 1,0 ponto

Defina a função "geraPlanoReceituario", cujo tipo é dado abaixo e que, a partir de um receituario válido,
retorne um plano de medicamento válido.

Dica: enquanto o receituário lista os horários que cada remédio deve ser tomado, o plano de medicamentos  é uma
disposição ordenada por horário de todos os remédios que devem ser tomados pelo paciente em um certo horário.

-}

geraPlanoReceituario :: Receituario -> PlanoMedicamento
geraPlanoReceituario = agrupaElementos . quickSort . inverteLista

inverteLista :: [(a, [b])] -> [(b, a)]
inverteLista = concatMap (\(x, ys) -> map (,x) ys)

agrupaElementos :: Eq a => [(a, b)] -> [(a, [b])]
agrupaElementos [] = []
agrupaElementos (x : xs) = g : agrupaElementos ys
  where
    f p = fst x == fst p
    g = (fst x, snd x : map snd (takeWhile f xs))
    ys = dropWhile f xs

{-

QUESTÃO 8  VALOR: 1,0 ponto

Defina a função "geraReceituarioPlano", cujo tipo é dado abaixo e que retorna um receituário válido a partir de um
plano de medicamentos válido.
Dica: Existe alguma relação de simetria entre o receituário e o plano de medicamentos? Caso exista, essa simetria permite
compararmos a função geraReceituarioPlano com a função geraPlanoReceituario ? Em outras palavras, podemos definir
geraReceituarioPlano com base em geraPlanoReceituario ?

-}

geraReceituarioPlano :: PlanoMedicamento -> Receituario
geraReceituarioPlano = agrupaElementos . quickSort . inverteLista

{-

QUESTÃO 9 VALOR: 1,0 ponto

Defina a função "executaPlantao", cujo tipo é dado abaixo e que executa um plantão válido a partir de um estoque de medicamentos,
resultando em novo estoque. A execução consiste em desempenhar, sequencialmente, todos os cuidados para cada horário do plantão.
Caso o estoque acabe antes de terminar a execução do plantão, o resultado da função deve ser Nothing. Caso contrário, o resultado
deve ser Just v, onde v é o valor final do estoque de medicamentos

-}

executaPlantao :: Plantao -> EstoqueMedicamentos -> Maybe EstoqueMedicamentos
executaPlantao [] e = Just e
executaPlantao ((h, cs) : ps) e = do
  e' <- go cs e
  executaPlantao ps e'
  where
    go :: [Cuidado] -> EstoqueMedicamentos -> Maybe EstoqueMedicamentos
    go [] e = Just e
    go (c : cs) e = do
      e' <- executaCuidado c e
      go cs e'

executaCuidado :: Cuidado -> EstoqueMedicamentos -> Maybe EstoqueMedicamentos
executaCuidado (Comprar med qtd) e = Just $ comprarMedicamento med qtd e
executaCuidado (Medicar med) e = tomarMedicamento med e

{-

QUESTÃO 10 VALOR: 1,0 ponto

Defina uma função "satisfaz", cujo tipo é dado abaixo e que verifica se um plantão válido satisfaz um plano
de medicamento válido para um certo estoque, ou seja, a função "satisfaz" deve verificar se a execução do plantão
implica terminar com estoque diferente de Nothing e administrar os medicamentos prescritos no plano.
Dica: fazer correspondencia entre os remédios previstos no plano e os ministrados pela execução do plantão.
Note que alguns cuidados podem ser comprar medicamento e que eles podem ocorrer sozinhos em certo horário ou
juntamente com ministrar medicamento.

-}

satisfaz :: Plantao -> PlanoMedicamento -> EstoqueMedicamentos -> Bool
satisfaz ps plan e = plantaoValido ps && plantao2plano ps == plan && Data.Maybe.isJust (executaPlantao ps e)

plantao2plano :: Plantao -> PlanoMedicamento
plantao2plano [] = []
plantao2plano p = filter (not . null . snd) $ map f p
  where
    f (h, cs) = (h, quickSort $ g cs)
    g [] = []
    g ((Medicar m) : cs) = m : g cs
    g ((Comprar _ _) : cs) = g cs

{-

QUESTÃO 11 (EXTRA) VALOR: 1,0 ponto

Defina a função "plantaoCorreto", cujo tipo é dado abaixo e que gera um plantão válido que satisfaz um plano de
medicamentos válido e um estoque de medicamentos.
Dica: a execução do plantão deve atender ao plano de medicamentos e ao estoque.

-}

horarioBase :: PlanoMedicamento -> Horario
horarioBase [] = 0
horarioBase ((h, _) : _) = h - 1

plantaoCorreto :: PlanoMedicamento -> EstoqueMedicamentos -> Plantao
plantaoCorreto plano e = cuidadoCompras : plano2plantao plano
  where
    estoqueNecessario = obterMedicamentos plano
    dif = diferencaEstoque estoqueNecessario e
    compras = map (uncurry Comprar) dif
    cuidadoCompras = (h, compras)
    h = horarioBase plano

plano2plantao :: PlanoMedicamento -> Plantao
plano2plantao = map (second (map Medicar))

obterMedicamentos :: PlanoMedicamento -> EstoqueMedicamentos
obterMedicamentos plano =
  map (second length)
    . agrupaElementos
    $ zip (quickSort $ concatMap snd plano) (repeat 1)

diferencaEstoque :: EstoqueMedicamentos -> EstoqueMedicamentos -> EstoqueMedicamentos
diferencaEstoque e1 e2 = filter (\(m, q) -> q /= 0) $ map (`quantidadeNecessaria` e2) e1

quantidadeNecessaria :: (Medicamento, Quantidade) -> EstoqueMedicamentos -> (Medicamento, Quantidade)
quantidadeNecessaria (m, q) e =
  let q' = consultarMedicamento m e
   in if q' < q
        then (m, q - q')
        else (m, 0)