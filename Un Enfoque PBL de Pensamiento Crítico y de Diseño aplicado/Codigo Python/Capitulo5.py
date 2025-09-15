# Importa la clase 'datetime' del m�dulo 'datetime' para poder trabajar con fechas y horas.
from datetime import datetime

# Inicializa una lista de listas (matriz de 10x4) para almacenar los datos de los productos.
# Puede guardar hasta 10 productos, cada uno con 4 atributos (ej: c�digo, nombre, precio, stock).
productos = [["" for _ in range(4)] for _ in range(10)]

def MostrarMenu(opciones):
    cadena = ""
    for info in opciones:
        cadena += info + "\n"
    return cadena

def EsnumeroEntero(dato):
    return dato.isdigit()
 
def EsNumeroDouble(dato):
    valido = False
    for c in dato:
        if not c.isdigit():
            if c == '.' and not valido:
                valido = True
            else:
                return False
    return valido
 
def EvaluarNumerico(dato, tipo):
    if tipo == 1:
        return EsnumeroEntero(dato)
    elif tipo == 2:
        return EsNumeroDouble(dato)
    return False
 
def Dialogo(texto):
    return input(texto + " : ")

def Leer(texto):
    cadena = Dialogo(texto)
    if cadena:
        cadena = cadena.strip()
        if not cadena:
            cadena = None
    return cadena

def DesplegarMenu(titulo, menu):
    cadena = titulo + "\n\n"
    cadena += MostrarMenu(menu)
    cadena += "\n Que opcion deseas"
    return Dialogo(cadena)
    

def RellenarEspacios(dato, tamano):
    return dato.ljust(tamano)

def Fecha():
    return datetime.now().strftime("%d-%m-%Y")

def IdTicketSiguiente(idticket):
    num = int(idticket) + 1
    if num < 10:
        return "00" + str(num).strip()
    elif num < 100:
        return "0" + str(num).strip()
    else:
        return str(num).strip()

# --- FUNCI�N ---
# Prop�sito: Crear y devolver una lista de productos predefinida.
# Par�metros: Ninguno.
# Retorna: Una lista de listas (la base de datos de productos).
def CargarProductos():
    # Se define una lista de listas. Cada lista interna contiene:
    # [c�digo, nombre, precio, cantidad]
    producto = [
        ["001", "Arroz 1kg", "35", "10"],
        ["002", "Azucar 1kg", "25", "10"],
        ["003", "Harina 1kg", "28", "10"],
        ["004", "Aceite 1L", "50", "10"],
        ["005", "Leche 1L", "35", "10"],
        ["006", "Huevos 12 unidades", "45", "10"],
        ["007", "Fideos 500g", "20", "10"],
        ["008", "Sal 1kg", "15", "10"],
        ["009", "Pasta de tomate 400g", "25", "10"],
        ["010", "Atun lata 170g", "35", "10"]
    ]
    # Devuelve la lista completa de productos.
    return producto


# --- FUNCI�N ---
# Prop�sito: Formatear los datos de un solo producto en una cadena de texto alineada.
# Par�metro:
#   vproducto (lista): Una lista con los datos de un producto [c�digo, nombre, precio, cantidad].
# Retorna: Un string (cadena) con los datos del producto formateados.
def MostrarProducto(vproducto):
    # Formatea el c�digo para que ocupe 5 caracteres.
    codigo = RellenarEspacios(vproducto[0], 5)
    # Formatea el nombre del producto para que ocupe 30 caracteres.
    producto = RellenarEspacios(vproducto[1], 30)
    # Formatea el precio para que ocupe 10 caracteres.
    precio = RellenarEspacios(vproducto[2], 10)
    # Formatea la cantidad para que ocupe 10 caracteres.
    cantidad = RellenarEspacios(vproducto[3], 10)
    # Concatena todas las partes en una sola l�nea de texto.
    cadena = codigo + producto + precio + cantidad
    # Devuelve la l�nea de texto formateada.
    return cadena


# --- FUNCI�N ---
# Prop�sito: Crear una cadena de texto con la lista completa y formateada de todos los productos.
# Par�metro:
#   vproductos (lista): La lista que contiene todos los productos.
# Retorna: Un string (salida) con todos los productos, cada uno en una nueva l�nea.
def MostrarLista(vproductos):
    # Inicializa una cadena de texto vac�a para acumular la salida.
    salida = ""
    # Itera 10 veces (nota: ser�a mejor usar 'len(vproductos)' para que sea din�mico).
    for ciclo in range(10):
        # Crea una lista temporal con los datos del producto en la posici�n actual del ciclo.
        vproducto = [vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3]]
        # Llama a MostrarProducto para formatear la l�nea del producto actual.
        cadena = MostrarProducto(vproducto)
        # Agrega la l�nea formateada y un salto de l�nea a la cadena de salida.
        salida += cadena + "\n"
    # Devuelve el string completo con toda la lista.
    return salida


# --- FUNCI�N ---
# Prop�sito: Buscar un producto por su c�digo dentro de la lista de productos.
# Par�metros:
#   codigo (string): El c�digo del producto que se desea encontrar.
#   vproductos (lista): La lista completa de productos donde se buscar�.
# Retorna: Un entero. La posici�n (�ndice) del producto si se encuentra, o -1 si no existe.
def ExisteProducto(codigo, vproductos):
    # Inicializa 'enc' (encontrado) en -1. Este ser� el valor de retorno si no se encuentra el c�digo.
    enc = -1
    # Inicializa 'pos' (posici�n) en 0 para llevar la cuenta del �ndice actual.
    pos = 0
    # Recorre la lista de productos completa.
    for ciclo in range(len(vproductos)):
        # Compara el c�digo del producto actual con el c�digo buscado (quitando espacios en blanco).
        if vproductos[ciclo][0].strip() == codigo.strip():
            # Si coinciden, guarda la posici�n actual en 'enc'.
            enc = pos
        # Incrementa el contador de posici�n.
        pos += 1
    # Devuelve la posici�n donde se encontr� el producto, o -1 si nunca se encontr�.
    return enc


# --- PROCEDIMIENTO ---
# Prop�sito: Gestionar la modificaci�n del precio de un producto.
# Par�metro:
#   vproductos (lista): La lista de productos. Esta lista ser� modificada directamente si la operaci�n es exitosa.
def ModificarProducto(vproductos):
    # Muestra la lista de productos y pide al usuario que introduzca un c�digo.
    codigo = input(MostrarLista(vproductos) + "\nIntroduce el codigo del producto a modificar: ")
    # Verifica que el usuario haya introducido alg�n dato.
    if codigo:
        # Busca la posici�n del producto usando el c�digo introducido.
        posicion = ExisteProducto(codigo, vproductos)
        # Si la posici�n es mayor a -1, significa que el producto fue encontrado.
        if posicion > -1:
            # Crea una lista temporal con los datos del producto encontrado.
            vproducto = [vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2], vproductos[posicion][3]]
            # Muestra los datos del producto y solicita el nuevo precio.
            precio = input("\nIntroduce el precio de " + MostrarProducto(vproducto) + ": ")
            # Verifica que se haya introducido un precio.
            if precio:
                # Eval�a si el precio introducido es un n�mero v�lido (entero o decimal).
                if EvaluarNumerico(precio, 2) or EvaluarNumerico(precio, 1):
                    # Si es v�lido, actualiza el precio en la lista original de productos.
                    vproductos[posicion][2] = precio
                else:
                    print("No es un valor num�rico.")
            else:
                print("Dato nulo.")
        else:
            print("No existe el c�digo.")
    else:
        print("Dato nulo.")


# --- PROCEDIMIENTO ---
# Prop�sito: Mostrar el men� de opciones de productos y ejecutar la acci�n seleccionada.
# Par�metro:
#   vproductos (lista): La lista de productos que ser� gestionada (pasada a otras funciones).
def MenuProductos(vproductos):
    # Define las opciones del men�.
    datosmenuproductos = ["1.-Modificar ", "2.-Listado ", "3.-Salida"]
    # Inicializa la opci�n para entrar al bucle.
    opcion = "0"
    # El bucle se ejecuta mientras la opci�n no sea "3" (Salida).
    while opcion != "3":
        # Muestra el men� y obtiene la opci�n del usuario.
        opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos)
        # Valida si la opci�n no es una de las permitidas.
        if not opcion in ["1", "2", "3"]:
            print("Opci�n incorrecta.")
        else:
            # Si la opci�n es "1", llama al procedimiento para modificar.
            if opcion == "1":
                ModificarProducto(vproductos)
            # Si la opci�n es "2", llama a la funci�n que muestra la lista y la imprime.
            elif opcion == "2":
                print(MostrarLista(vproductos))
            # Si la opci�n es "3", imprime el mensaje de salida.
            elif opcion == "3":
                print("Salida del Sistema")
            # Un control extra por si acaso.
            else:
                print("No existe esta opci�n.")



def MenuPuntoVenta(idticket):
    opcion = None
    membrete = None
    pago = False
    idticket = IdTicketSiguiente(idticket)
    fechadia = Fecha()
    membrete = "Fecha del Dia "+fechadia +" Ticket No "+idticket
    membrete += "\n-------------------------------------------------------\n"
    datosmenu = ["1. - Agregar", "2. - Eliminar", "3. - Listado", "4. - Pagar", "5. - Salida"]
    while opcion != "5":
        opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu)
        if opcion not in ["1", "2", "3", "4", "5"]:
            print("Opcion Incorrecta")
        else:
            if opcion == "1":
                print("Agregar Articulo al Ticket")
            elif opcion == "2":
                print("Eliminar Articulo del Ticket")
            elif opcion == "3":
                print("Listado de Articulos del Ticket")
            elif opcion == "4":
                print("Pagar Ticket y salir")
                opcion = "5"
                pago = True
            elif opcion == "5":
                print("Salida del Ventas")
                if not pago:
                    print("No pago el ticket")
                    print(f"Eliminando ticket {idticket}")

def MenuInventario():
    datosmenuinventarios = ["1. - Listado", "2. - Agregar", "3. - Salida"]
    opcion = "0"
    while opcion != "3":
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventarios)
        if opcion not in ["1", "2", "3"]:
            print("Opcion incorrecta")
        else:
            if opcion == "1":
                print("Listado de Inventario")
            elif opcion == "2":
                print("Agregar Inventario")
            elif opcion == "3":
                print("Salida de Inventarios")
            else:
                print("No existe esta opcion")
            
# --- PROCEDIMIENTO ---
# Prop�sito: Es el men� principal y punto de navegaci�n de toda la aplicaci�n.
# Par�metro:
#   vproductos (lista): La lista de productos que ser� pasada a los submen�s que la necesiten,
#                       como MenuProductos.
def MenuPrincipal(vproductos):
    # Define la lista de opciones que se mostrar�n en el men� principal.
    datosmenuprincipal = ["1.-Productos", "2.-Punto de Venta", "3.- Inventarios", "5.- Salida"]
    # Se inicializa la variable 'opcion' para asegurar que el bucle comience.
    opcion = "0"
    # El bucle se repite mientras la opci�n del usuario no sea "5" (Salida).
    while opcion != "5":
        # Llama a la funci�n 'DesplegarMenu' para mostrar el men� y capturar la opci�n del usuario.
        opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes", datosmenuprincipal)
        # Verifica si la opci�n ingresada no es una de las opciones v�lidas.
        if opcion not in ["1", "2", "3", "5"]:
            # Informa al usuario que la opci�n es incorrecta.
            print("Opcion incorrecta")
        else:
            # Si la opci�n es "1", navega al men� de productos.
            if opcion == "1":
                # Llama al procedimiento del men� de productos, pasando la lista de productos.
                MenuProductos(vproductos)
            # Si la opci�n es "2", navega al men� de punto de venta.
            elif opcion == "2":
                # Llama al procedimiento del punto de venta con un ID de ticket inicial.
                MenuPuntoVenta("000")
            # Si la opci�n es "3", navega al men� de inventarios.
            elif opcion == "3":
                MenuInventario()
            # Si la opci�n es "5", finaliza el programa.
            elif opcion == "5":
                print("Salida del Sistema")


# --- PUNTO DE ENTRADA DEL PROGRAMA ---
# Este bloque de c�digo solo se ejecuta cuando el archivo se corre directamente.
if __name__ == "__main__":
    # Llama a la funci�n CargarProductos() para obtener la lista inicial de productos
    # y la guarda en la variable 'productos'.
    productos = CargarProductos()
    
    # Calcula el n�mero de filas (productos) en la lista.
    num_filas = len(productos)
    # Calcula el n�mero de columnas (datos por producto) tomando la primera fila como referencia.
    num_columnas = len(productos[0])
    
    # Imprime las dimensiones de la lista de productos (�til para depuraci�n).
    print(f"Filas: {num_filas}, Columnas: {num_columnas}")
    
    # Llama al procedimiento del men� principal para iniciar la aplicaci�n,
    # pas�ndole la lista de productos reci�n cargada.
    MenuPrincipal(productos)