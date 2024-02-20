areas = {}
cardapio = {}
estoque = {}
historico = []
mesas = {}
pedidos = {}


def fechar_restaurante():
    if historico:
        for indice in range(len(historico)):
            mesa = historico[indice][0]
            item = historico[indice][1]
            print(f'{indice + 1}. mesa {mesa} pediu {item}')
    else:
        print('- historico vazio')
    print('=> restaurante fechado')


def relatorio_pedidos():
    if pedidos:
        for mesa in pedidos:
            print(f'mesa: {mesa}')
            pedidos[mesa].sort()
            for pedido in pedidos[mesa]:
                print(f'- {pedido}')
    else:
        print('- nenhum pedido foi realizado')


def remove_do_estoque(item):
    for ingrediente in cardapio[item]:
        estoque[ingrediente] -= cardapio[item][ingrediente]
        if estoque[ingrediente] == 0:
            del estoque[ingrediente]


def atualiza_historico(mesa, item):
    historico.append([mesa, item])


def atualiza_pedidos(mesa, item):
    if mesa not in pedidos:
        pedidos[mesa] = []
    pedidos[mesa].append(item)
    sorted(pedidos)


def existem_ingredientes(item):
    for ingrediente in cardapio[item]:
        if ingrediente not in estoque or cardapio[item][ingrediente] > estoque[ingrediente]:
            print(f'erro >> ingredientes insuficientes para produzir {item}')
            return False
    return True


def item_existe(item):
    if item in cardapio:
        return True
    print(f'erro >> item {item} nao existe no cardapio')
    return False


def mesa_ocupada(mesa):
    if mesas[mesa]:
        return True
    print(f'erro >> mesa {mesa} desocupada')
    return False


def mesa_existe(mesa):
    if mesa in mesas:
        return True
    print(f'erro >> mesa {mesa} inexistente')
    return False


def fazer_pedido():
    mesa, item = input().split(', ')
    mesa = int(mesa)
    if mesa_existe(mesa):
        if mesa_ocupada(mesa):
            if item_existe(item):
                if existem_ingredientes(item):
                    print(
                        f'sucesso >> pedido {item} para mesa {mesa} realizado')
                    atualiza_pedidos(mesa, item)
                    atualiza_historico(mesa, item)
                    remove_do_estoque(item)


def relatorio_estoque():
    if estoque:
        for ingrediente in estoque:
            print(f'{ingrediente}: {estoque[ingrediente]}')
    else:
        print('- estoque vazio')


def relatorio_cardapio():
    if cardapio:
        for item in sorted(cardapio):
            print(f'item: {item}')
            for ingrediente in sorted(cardapio[item]):
                print(f'- {ingrediente}: {cardapio[item][ingrediente]}')
    else:
        print('- cardapio vazio')


def relatorio_mesas():
    if mesas:
        for area in mesas:
            print(f'area: {area}')
            if areas[area]:
                areas[area].sort()
                for mesa in areas[area]:
                    print(
                        f'- mesa: {mesa}, status: {"ocupada" if mesas[mesa] else "livre"}')
            else:
                print('- area sem mesas')
    else:
        print('- restaurante sem mesas')


def atualizar_estoque():
    arquivo = open(input(), 'r')
    lista_estoque = arquivo.readlines()
    for linha in lista_estoque:
        ingrediente, quantidade = linha.replace('\n', '').split(', ')
        quantidade = int(quantidade)
        if ingrediente not in estoque:
            estoque[ingrediente] = 0
        estoque[ingrediente] += quantidade
    sorted(estoque)
    arquivo.close()


def atualizar_cardapio():
    arquivo = open(input(), 'r')
    lista_cardapio = arquivo.readlines()
    for linha in lista_cardapio:
        receita = linha.replace('\n', '').split(', ')
        item = receita[0]
        cardapio[item] = {}
        receita.pop(0)
        for ingrediente in receita:
            if ingrediente not in cardapio[item]:
                cardapio[item][ingrediente] = 0
            cardapio[item][ingrediente] += 1
    sorted(cardapio)
    arquivo.close()


def atualizar_mesas():
    arquivo = open(input(), 'r')
    lista_mesas = arquivo.readlines()
    for linha in lista_mesas:
        numero, area, estado = linha.replace('\n', '').split(', ')
        numero = int(numero)
        mesas[numero] = estado == 'ocupada'
        if area not in areas:
            areas[area] = []
        for area_aux in areas:
            if numero in areas[area_aux]:
                areas[area_aux].pop(areas[area_aux].index(numero))
        areas[area].append(numero)
    arquivo.close()


def abre_restaurante():
    print('=> restaurante aberto')
    while True:
        comando = input()
        if comando == '+ atualizar mesas':
            atualizar_mesas()
        elif comando == '+ atualizar cardapio':
            atualizar_cardapio()
        elif comando == '+ atualizar estoque':
            atualizar_estoque()
        elif comando == '+ relatorio mesas':
            relatorio_mesas()
        elif comando == '+ relatorio cardapio':
            relatorio_cardapio()
        elif comando == '+ relatorio estoque':
            relatorio_estoque()
        elif comando == '+ fazer pedido':
            fazer_pedido()
        elif comando == '+ relatorio pedidos':
            relatorio_pedidos()
        elif comando == '+ fechar restaurante':
            fechar_restaurante()
            break
        else:
            print('erro >> comando inexistente')


abre_restaurante()
