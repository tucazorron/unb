import User

res = max(User.data["porcentagem_dengue"], User.data["porcentagem_zika"], User.data["porcentagem_chiku"])
if res < 30:
    print("\nO paciente nao foi diagnosticado com Dengue, Zika ou Chikungunya.")
else:
    if res == User.data["porcentagem_dengue"]:
        print("\nO paciente foi diagnosticado com Dengue.")
    if res == User.data["porcentagem_zika"]:
        print("\nO paciente foi diagnosticado com Zika.")
    if res == User.data["porcentagem_chiku"]:
        print("\nO paciente foi diagnosticado com Chikungunya.")

print("\n====\n")