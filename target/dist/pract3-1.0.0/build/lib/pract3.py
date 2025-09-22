import os

ALFABETO_27 = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ " 
ALFABETO_191 = ''.join(chr(i) for i in range(32, 223))  

def vigenere(texto, clave, modulo, alfabeto):
    cifrado = []
    clave = clave.upper()
    for i, char in enumerate(texto):
        if char not in alfabeto:
            cifrado.append(char)
            continue
        idx_texto = alfabeto.index(char)
        idx_clave = alfabeto.index(clave[i % len(clave)])
        nuevo_idx = (idx_texto + idx_clave) % modulo
        cifrado.append(alfabeto[nuevo_idx])
    return ''.join(cifrado)

def main():
    print("=== CIFRADOR DE VIGENERE ===")
    print("1. Usar módulo 27")
    print("2. Usar módulo 191")

    opcion = input("Seleccione opción (1/2): ").strip()

    if opcion == "1":
        modulo = 27
        alfabeto = ALFABETO_27
    elif opcion == "2":
        modulo = 191
        alfabeto = ALFABETO_191
    else:
        print("Opción invalida")
        return

    clave = input("Ingrese la clave: ").upper()

    modo = input("(1) archivo o (2) manualmente: ").strip()

    if modo == "1":
        nombre_archivo = input("Ingrese el nombre del archivo: ").strip()
        if not os.path.exists(nombre_archivo):
            print("Archivo no encontrado")
            return
        with open(nombre_archivo, "r", encoding="utf-8") as f:
            texto_claro = f.read().upper()
    else:
        texto_claro = input("Ingrese el texto claro: ").upper()

    texto_cifrado = vigenere(texto_claro, clave, modulo, alfabeto)

    print("\nTexto cifrado:\n", texto_cifrado)

    with open("cifrado.txt", "w", encoding="utf-8") as f:
        f.write(texto_cifrado)

    print("\nTexto cifrado guardado en 'cifrado.txt'")

if __name__ == "__main__":
    main()
