import User

print("\n====")
print("\nFormulario de Diagnostico:")

print("\n- Perguntas de Sim/Nao:\n    - Se a resposta for 'Sim' entao responda '1'\n    - Se a resposta for 'Nao' entao responda '0'")
# print("\n- Perguntas de Frequencia:\n    - Se a resposta for 'Raramente' entao responda '1'\n    - Se a respota for 'Moderada' entao responda '2'\n    - Se a resposta for 'Frequentemente' entao responda '3'")
print("\n- Perguntas de Intensidade:\n    - Se a resposta for 'Leve' entao responda '1'\n    - Se a respota for 'Moderada' entao responda '2'\n    - Se a resposta for 'Intensa' entao responda '3'")

User.data["temperatura"] = int(input("\nP: Qual a tua temperatura corporal em graus Celsius?\nR: "))

if User.data["temperatura"] >= 38:
    User.data["dias_febre"] = int(input("\nP: Ha quantos dias consecutivos esta com febre?\nR: "))

User.data["manchas_pele"] = int(input("\nP: Voce possui alguma mancha de pele recente?\nR: "))

User.data["dor_muscular"] = int(input("\nP: Voce sente alguma dor muscular?\nR: "))

if User.data["dor_muscular"] == 1:
    User.data["dor_muscular"] = int(input("\nP: Qual a frequencia das suas dores musculares?\nR: "))

User.data["dor_articular"] = int(input("\nP: Voce possui alguma dor articular?\nR: "))

if User.data["dor_articular"] == 1:
    # User.data["dor_articular_frequencia"] = int(input("\nP: Qual a frequencia da suas dores articulares?\nR: "))
    User.data["dor_articular_intensidade"] = int(input("\nP: Qual a intensidade das suas dores articulares?\nR: "))

User.data["edema_articular"] = int(input("\nP: Voce possui algum edema articular?\nR: "))

if User.data["edema_articular"] == 1:
    # User.data["edema_articular_frequencia"] = int(input("\nP: Qual a frequencia dos seus edemas articulares?\nR: "))
    User.data["edema_articular_intensidade"] = int(input("\nP: Qual a intensidade dos seus edemas articulares?\nR: "))

User.data["conjuntivite"] == int(input("\nP: Voce possui conjuntivite?\nR: "))

User.data["dor_cabeca"] = int(input("\nP: Voce possui dor de cabeca?\nR: "))

if User.data["dor_cabeca"] == 1:
    # User.data["dor_cabeca_frequencia"] = int(input("\nP: Qual a frequencia das suas dores de cabeca?\nR: "))
    User.data["dor_cabeca_intensidade"] = int(input("\nP: Qual a intensidade das suas dores de cabeca?\nR: "))

User.data["coceira"] = int(input("\nP: Voce possui coceira?\nR: "))

if User.data["coceira"] == 1:
    User.data["coceira"] = int(input("\nP: Qual a intensidade da sua coceira?\nR: "))

User.data["hipertrofia_ganglionar"] = int(input("\nP: Voce possui hipertrofia ganglionar?\nR: "))

# # if User.data["hipertrofia_ganglionar"] == 1:
#     User.data["hipertrofia_ganglionar"] = int(input("\nP: Qual a frequencia da sua hipertrofia ganglionar?\nR: "))

User.data["discrasia_hemorragica"] = int(input("\nP: Voce possui discrasia hemorragica?\nR: "))

# if User.data["discrasia_hemorragica"] == 1:
#     User.data["discrasia_hemorragica"] = int(input("\nP: Qual a frequencia da sua discrasia hemorragica?\nR: "))

User.data["acometimento_neurologico"] = int(input("\nP: Voce teve algum acometimento neurologico recente?\nR: "))
