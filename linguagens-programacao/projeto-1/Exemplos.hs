module Exemplos where

import ModeloDados
  ( Cuidado (Comprar, Medicar),
    EstoqueMedicamentos,
    Medicamento,
    PlanoMedicamento,
    Plantao,
    Receituario,
  )
import UnBCare
  ( comprarMedicamento,
    consultarMedicamento,
    demandaMedicamentos,
    executaPlantao,
    geraPlanoReceituario,
    geraReceituarioPlano,
    plantaoCorreto,
    plantaoValido,
    satisfaz,
    tomarMedicamento,
  )

m1 :: Medicamento
m1 = "Lactulona"

m2 :: Medicamento
m2 = "Pantoprazol"

m3 :: Medicamento
m3 = "Patz"

m4 :: Medicamento
m4 = "Quetiapina"

m5 :: Medicamento
m5 = "Mirtazapina"

m6 :: Medicamento
m6 = "Adera"

m7 :: Medicamento
m7 = "Donepezila"

m8 :: Medicamento
m8 = "Xarelto"

m9 :: Medicamento
m9 = "Alprazolam"

estoque1 :: EstoqueMedicamentos
estoque1 = [(m1, 10), (m2, 5), (m3, 0)]

estoque2 :: EstoqueMedicamentos
estoque2 = [(m1, 10), (m2, 5), (m3, 10)]

estoque3 :: EstoqueMedicamentos
estoque3 = [(m1, 10), (m2, 50), (m3, 10), (m4, 20)]

receituario1 :: Receituario
receituario1 = [(m1, [8, 17]), (m2, [6]), (m3, [22])]

receituario2 :: Receituario
receituario2 = [(m1, [8, 17]), (m2, [6]), (m3, [22]), (m4, [8, 22, 23])]

plano1 :: PlanoMedicamento
plano1 = [(6, [m2]), (8, [m1]), (17, [m1]), (22, [m3])]

plano2 :: PlanoMedicamento
plano2 = [(6, [m2]), (8, [m1, m4]), (17, [m1]), (22, [m3, m4]), (23, [m4])] :: [(Int, [String])]

plantao1 :: Plantao
plantao1 =
  [ (6, [Medicar m2]),
    (8, [Medicar m1]),
    (17, [Medicar m1]),
    (22, [Medicar m3])
  ]

plantao2 :: Plantao
plantao2 =
  [ (6, [Medicar m2]),
    (8, [Medicar m1]),
    (17, [Medicar m1, Comprar m3 30]),
    (22, [Medicar m3])
  ]

plantaoValido0 :: Plantao
plantaoValido0 =
  [ (6, [Medicar m2, Medicar m8]),
    (8, [Medicar m9, Medicar m1]),
    (17, [Medicar m1, Comprar m3 30]),
    (22, [Medicar m3])
  ]

plantaoInvalido1 :: Plantao
plantaoInvalido1 =
  [ (6, [Medicar m2, Medicar m8]),
    (8, [Medicar m9, Medicar m1]),
    (22, [Medicar m3]),
    (17, [Medicar m1, Comprar m3 30])
  ]

plantaoInvalido2 :: Plantao
plantaoInvalido2 =
  [ (6, [Medicar m2, Medicar m8]),
    (8, [Medicar m9, Medicar m1]),
    (17, [Medicar m1, Comprar m1 30]),
    (22, [Medicar m3])
  ]

plantaoInvalido3 :: Plantao
plantaoInvalido3 =
  [ (6, [Medicar m8, Medicar m2]),
    (8, [Medicar m9, Medicar m1]),
    (17, [Medicar m1, Comprar m1 30]),
    (22, [Medicar m3])
  ]

plantaoInvalido4 :: Plantao
plantaoInvalido4 =
  [ (6, [Medicar m2]),
    (8, [Comprar m1 20, Medicar m1, Medicar m4]),
    (17, [Medicar m1]),
    (22, [Medicar m3, Medicar m4]),
    (23, [Medicar m4])
  ]

casoTeste1_1 :: Bool
casoTeste1_1 = comprarMedicamento m3 30 estoque1 == [(m1, 10), (m2, 5), (m3, 30)]

casoTeste1_2 :: Bool
casoTeste1_2 = comprarMedicamento m6 20 estoque1 == [(m6, 20), (m1, 10), (m2, 5), (m3, 0)]

casoTeste1_3 :: Bool
casoTeste1_3 = comprarMedicamento m2 2 estoque1 == [(m1, 10), (m2, 7), (m3, 0)]

casoTeste1_4 :: Bool
casoTeste1_4 = comprarMedicamento m8 20 [] == [(m8, 20)]

conjuntoCasosTeste1 :: Bool
conjuntoCasosTeste1 = and [casoTeste1_1, casoTeste1_2, casoTeste1_3, casoTeste1_4]

casoTeste2_1 :: Bool
casoTeste2_1 = tomarMedicamento m1 estoque1 == Just [(m1, 9), (m2, 5), (m3, 0)]

casoTeste2_2 :: t
casoTeste2_2 = isNothing1 (tomarMedicamento m3 estoque1)

isNothing1 :: Maybe EstoqueMedicamentos -> t
isNothing1 = error "not implemented"

conjuntoCasosTeste2 :: Bool
conjuntoCasosTeste2 = casoTeste2_1 && casoTeste2_2

casoTeste3_1 :: Bool
casoTeste3_1 = consultarMedicamento m2 estoque1 == 5

casoTeste3_2 :: Bool
casoTeste3_2 = consultarMedicamento "Aas" estoque1 == 0

conjuntoCasosTeste3 :: Bool
conjuntoCasosTeste3 = casoTeste3_1 && casoTeste3_2

casoTeste4_1 :: Bool
casoTeste4_1 = demandaMedicamentos receituario1 == [(m1, 2), (m2, 1), (m3, 1)]

conjuntoCasosTeste4 :: Bool
conjuntoCasosTeste4 = casoTeste4_1

casoTeste5_1 :: Bool
casoTeste5_1 = geraPlanoReceituario receituario1 == [(6, [m2]), (8, [m1]), (17, [m1]), (22, [m3])]

casoTeste5_2 :: Bool
casoTeste5_2 = geraPlanoReceituario receituario2 == [(6, [m2]), (8, [m1, m4]), (17, [m1]), (22, [m3, m4]), (23, [m4])]

conjuntoCasosTeste5 :: Bool
conjuntoCasosTeste5 = casoTeste5_1 && casoTeste5_2

casoTeste6_1 :: Bool
casoTeste6_1 = geraReceituarioPlano (geraPlanoReceituario receituario1) == receituario1

casoTeste6_2 :: Bool
casoTeste6_2 = geraReceituarioPlano (geraPlanoReceituario receituario2) == receituario2

conjuntoCasosTeste6 :: Bool
conjuntoCasosTeste6 = casoTeste6_1 && casoTeste6_2

casoTeste7_1 :: Bool
casoTeste7_1 = isNothing2 (executaPlantao plantao1 estoque1)

isNothing2 :: Maybe EstoqueMedicamentos -> Bool
isNothing2 = error "not implemented"

casoTeste7_2 :: Bool
casoTeste7_2 = executaPlantao plantao1 estoque2 == Just [(m1, 8), (m2, 4), (m3, 9)]

casoTeste7_3 :: Bool
casoTeste7_3 = executaPlantao plantao2 estoque1 == Just [(m1, 8), (m2, 4), (m3, 29)]

conjuntoCasosTeste7 :: Bool
conjuntoCasosTeste7 = casoTeste7_1 && casoTeste7_2 && casoTeste7_3

casoTeste8_1 :: Bool
casoTeste8_1 = not (satisfaz plantao1 plano1 estoque1)

casoTeste8_2 :: Bool
casoTeste8_2 = satisfaz plantao1 plano1 estoque2

casoTeste8_3 :: Bool
casoTeste8_3 = satisfaz plantao2 plano1 estoque1

conjuntoCasosTeste8 :: Bool
conjuntoCasosTeste8 = casoTeste8_1 && casoTeste8_2 && casoTeste8_3

casoTeste9_1 :: Bool
casoTeste9_1 = satisfaz plantao plano1 estoque1
  where
    plantao = plantaoCorreto plano1 estoque1

conjuntoCasosTeste9 :: Bool
conjuntoCasosTeste9 = casoTeste9_1

conjuntoCasosTestePlantaoValido =
  and
    [ plantaoValido plantao1,
      plantaoValido plantao2,
      plantaoValido plantaoValido0,
      not (plantaoValido plantaoInvalido1),
      not (plantaoValido plantaoInvalido2),
      not (plantaoValido plantaoInvalido3)
    ]

resultadoGlobalTestes :: Bool
resultadoGlobalTestes =
  and
    [ conjuntoCasosTeste1,
      conjuntoCasosTeste2,
      conjuntoCasosTeste3,
      conjuntoCasosTeste4,
      conjuntoCasosTeste5,
      conjuntoCasosTeste6,
      conjuntoCasosTeste7,
      conjuntoCasosTeste8,
      conjuntoCasosTeste9,
      conjuntoCasosTestePlantaoValido
    ]
