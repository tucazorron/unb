import User
import Dengue
import Zika
import Chikungunya

# def medExam():

# febre
if Dengue.data["febre_temperatura"][0] <= User.data["temperatura"] <= Dengue.data["febre_temperatura"][1] :
    User.data["porcentagem_dengue"] += 18
if Zika.data["febre_temperatura"][0] <= User.data["temperatura"] <= Zika.data["febre_temperatura"][1] :
    User.data["porcentagem_zika"] += 5
if Chikungunya.data["febre_temperatura"][0] <= User.data["temperatura"] <= Chikungunya.data["febre_temperatura"][1] :
    User.data["porcentagem_chiku"] += 15

# duracao da febre
if Dengue.data["febre_duracao"][0] <= User.data["dias_febre"] <= Dengue.data["febre_duracao"][1] :
    User.data["porcentagem_dengue"] += 7
if Chikungunya.data["febre_duracao"][0] <= User.data["dias_febre"] <= Chikungunya.data["febre_duracao"][1] :
    User.data["porcentagem_chiku"] += 5

# manchas
if User.data["manchas_pele"]:
    User.data["porcentagem_dengue"] += 7
    User.data["porcentagem_zika"] += 18
    User.data["porcentagem_chiku"] += 12

# dor muscular
if Dengue.data["dor_muscular"] == User.data["dor_muscular"]:
    User.data["porcentagem_dengue"] += 16
if Zika.data["dor_muscular"] == User.data["dor_muscular"]:
    User.data["porcentagem_zika"] += 9
if Chikungunya.data["dor_muscular"] == User.data["dor_muscular"]:
    User.data["porcentagem_chiku"] += 5

# dor nas articulacoes (frequencia)
if Dengue.data["dor_articular_frequencia"] == User.data["dor_articular"]:
    User.data["porcentagem_dengue"] += 5
if Zika.data["dor_articular_frequencia"] == User.data["dor_articular"]:
    User.data["porcentagem_zika"] += 9
if Chikungunya.data["dor_articular_frequencia"] == User.data["dor_articular"] :
    User.data["porcentagem_chiku"] += 15

# dor nas articulacoes (intensidade)
if Dengue.data["dor_articular_intensidade"][0] == User.data["dor_articular_intensidade"]:
    User.data["porcentagem_dengue"] += 7
if Zika.data["dor_articular_intensidade"][0] == User.data["dor_articular_intensidade"] or Zika.data["dor_articular_intensidade"][1] == User.data["dor_articular_intensidade"]:
    User.data["porcentagem_zika"] += 7
if Chikungunya.data["dor_articular_intensidade"][0] == User.data["dor_articular_intensidade"] or Chikungunya.data["dor_articular_intensidade"][1] == User.data["dor_articular_intensidade"]:
    User.data["porcentagem_chiku"] += 7

# edema_articular
if User.data["edema_articular"]:
    User.data["porcentagem_dengue"] += 2
    User.data["porcentagem_zika"] += 3
    User.data["porcentagem_chiku"] += 3

# edema_articular_intensidade
if User.data["edema_articular_intensidade"] == Zika.data["edema_articular_intensidade"]:
    User.data["porcentagem_zika"] += 3
if User.data["edema_articular_intensidade"] == Chikungunya.data["edema_articular_intensidade"]:
    User.data["porcentagem_chiku"] += 3

# conjuntivite
if User.data["conjuntivite"]:
    User.data["porcentagem_dengue"] += 3
    User.data["porcentagem_zika"] += 14
    User.data["porcentagem_chiku"] += 6

# dor de cabeca
if User.data["dor_cabeca"]:
    User.data["porcentagem_dengue"] += 5
    User.data["porcentagem_zika"] += 5
    User.data["porcentagem_chiku"] += 5

# dor de cabeca (intensidade)
if User.data["dor_cabeca_intensidade"] == 2:
    User.data["porcentagem_zika"] += 5
    User.data["porcentagem_chiku"] += 5


if User.data["dor_cabeca_intensidade"] == 3:
        User.data["porcentagem_dengue"] += 10

# coceira
if User.data["coceira"] in Dengue.data["coceira"]:
    User.data["porcentagem_dengue"] += 5
if User.data["coceira"] in Zika.data["coceira"]:
    User.data["porcentagem_zika"] += 6
if User.data["coceira"] in Chikungunya.data["coceira"]:
    User.data["porcentagem_chiku"] += 5

# hipertrofia_ganglionar
if User.data["hipertrofia_ganglionar"] == Dengue.data["hipertrofia_ganglionar"]:
    User.data["porcentagem_dengue"] += 6
if User.data["hipertrofia_ganglionar"] == Zika.data["hipertrofia_ganglionar"]:
    User.data["porcentagem_zika"] += 6
if User.data["hipertrofia_ganglionar"] == Chikungunya.data["hipertrofia_ganglionar"]:
    User.data["porcentagem_chiku"] += 6

# discrasia_hemorragica
if User.data["discrasia_hemorragica"] == Dengue.data["discrasia_hemorragica"]:
    User.data["porcentagem_dengue"] += 6
if User.data["discrasia_hemorragica"] == Zika.data["discrasia_hemorragica"]:
    User.data["porcentagem_zika"] += 6
if User.data["discrasia_hemorragica"] == Chikungunya.data["discrasia_hemorragica"]:
    User.data["porcentagem_chiku"] += 6


# acometimento_neurologico
if User.data["acometimento_neurologico"] == Dengue.data["acometimento_neurologico"]:
    User.data["porcentagem_dengue"] += 3
if User.data["acometimento_neurologico"] == Zika.data["acometimento_neurologico"]:
    User.data["porcentagem_zika"] += 4
if User.data["acometimento_neurologico"] == Chikungunya.data["acometimento_neurologico"]:
    User.data["porcentagem_chiku"] += 2
