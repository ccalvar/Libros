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




def CargarProductos():
    producto = [
        ["001", "Arroz 1kg", "35","10"],
        ["002", "Azucar 1kg", "25","10"],
        ["003", "Harina 1kg", "28","10"],
        ["004", "Aceite 1L", "50","10"],
        ["005", "Leche 1L", "35","10"],
        ["006", "Huevos 12 unidades", "45","10"],
        ["007", "Fideos 500g", "20","10"],
        ["008", "Sal 1kg", "15","10"],
        ["009", "Pasta de tomate 400g", "25","10"],
        ["010", "Atun lata 170g", "35","10"]
    ]
    return producto


def MostrarProducto(vproducto):
    codigo = RellenarEspacios(vproducto[0], 5)
    producto = RellenarEspacios(vproducto[1], 30)
    precio = RellenarEspacios(vproducto[2], 10)
    cantidad = RellenarEspacios(vproducto[3], 10)
    cadena = codigo + producto + precio +cantidad
    return cadena

def MostrarLista(vproductos):
    salida = ""
    for ciclo in range(10):
        vproducto = [vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2],vproductos[ciclo][3]]
        cadena = MostrarProducto(vproducto)
        salida += cadena + "\n"
    return salida

def ExisteProducto(codigo, vproductos): 
    enc = -1
    pos = 0
    for ciclo in range(len(vproductos)):
        if vproductos[ciclo][0].strip() == codigo.strip():
            enc = pos
        pos += 1
    return enc

def ModificarProducto(vproductos):
    codigo = input(MostrarLista(vproductos) + "\nIntroduce el codigo del producto a modificar")
    if codigo:
        posicion = ExisteProducto(codigo, vproductos)
        if posicion > -1:
            vproducto = [vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2],vproductos[posicion][3]]
            precio = input("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ")
            if precio:
                if EvaluarNumerico(precio, 2) or EvaluarNumerico(precio, 1):
                    vproductos[posicion][2] = precio
                else:
                    print("no es un valor numerico")
            else:
                print(" dato nulo")
        else:
            print("no existe el codigo")
    else:
        print(" dato nulo")


def MenuProductos(vproductos):
    datosmenuproductos = ["1.-Modificar ", "2.-Listado ", "3.-Salida"]  
    opcion = "0"
    while opcion != "3":
        opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos) 
        if not opcion in ["1", "2", "3"]:
            print("opcion incorrecta ")
        else:
            if opcion == "1":
                ModificarProducto(vproductos)
            elif opcion == "2":
                print(MostrarLista(vproductos))
            elif opcion == "3":
                print("Salida del Sistema")
            else:
                print("No existe esta opcion")

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



# --- PROCEDIMIENTO ---
# Prop�sito: Gestionar el proceso de agregar stock a un producto existente.
# Par�metro:
#   vproductos (lista): La lista de productos que ser� modificada directamente.
def AgregarStock(vproductos):
    # Llama a la funci�n MostrarLista para obtener el listado de productos y lo guarda.
    info = MostrarLista(vproductos)
    # Muestra la lista y pide al usuario que introduzca el c�digo del producto.
    codigo = Leer(info + "\nIntroduce el codigo del producto a modificar")
    
    # Verifica que el usuario haya introducido un c�digo.
    if codigo:
        # Busca la posici�n (�ndice) del producto en la lista.
        posicion = ExisteProducto(codigo, vproductos)
        
        # Si la posici�n es mayor que -1, el producto fue encontrado.
        if posicion > -1:
            # Crea una lista temporal para mostrarle al usuario el producto que est� modificando.
            # NOTA: Se est� usando el �ndice [3] (cantidad) y poni�ndolo en la posici�n del precio.
            vproducto = [
                vproductos[posicion][0], # C�digo
                vproductos[posicion][1], # Nombre
                vproductos[posicion][3], # Cantidad actual
                ""                       # Se deja un campo vac�o
            ]
            
            # Pide al usuario la cantidad de stock que desea agregar.
            cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar " + MostrarProducto(vproducto) + " ")
            
            # Verifica que el usuario haya introducido una cantidad.
            if cantidad:
                # Valida si la cantidad introducida es un n�mero (entero o decimal).
                if EvaluarNumerico(cantidad, 2) or EvaluarNumerico(cantidad, 1):
                    # Suma la cantidad nueva a la cantidad existente (convirtiendo a entero).
                    nuevacantidad = int(cantidad) + int(vproducto[2]) # vproducto[2] tiene la cantidad original.
                    # Actualiza la cantidad en la lista de productos principal, convirtiendo el resultado a string.
                    vproductos[posicion][3] = str(nuevacantidad)
                else:
                    print("no es un valor numerico")
            else:
                print(" dato nulo")
        else:
            print("no existe el codigo")
    else:
        print(" dato nulo")


# --- PROCEDIMIENTO ---
# Prop�sito: Mostrar el men� de opciones de inventario y ejecutar la acci�n seleccionada.
# Par�metro:
#   vproductos (lista): La lista de productos que ser� gestionada por las opciones del men�.
def MenuInventario(vproductos):
    # Define las opciones del men� de inventarios.
    datosmenuinventarios = ["1. - Listado", "2. - Agregar", "3. - Salida"]
    opcion = "0"
    
    # El bucle se mantiene activo hasta que el usuario elija la opci�n "3" (Salida).
    while opcion != "3":
        # Muestra el men� y obtiene la elecci�n del usuario.
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventarios)
        
        # Valida que la opci�n sea una de las permitidas.
        if opcion not in ["1", "2", "3"]:
            print("Opcion incorrecta")
        else:
            # Si la opci�n es "1", muestra la lista de productos.
            if opcion == "1":
                print(MostrarLista(vproductos))
            # Si la opci�n es "2", llama al procedimiento para agregar stock.
            elif opcion == "2":
                AgregarStock(vproductos)
            # Si la opci�n es "3", imprime el mensaje de salida.
            elif opcion == "3":
                print("Salida de Inventarios")
            else:
                print("No existe esta opcion")
            
# --- PROCEDIMIENTO ---
# Prop�sito: Es el men� principal y punto de navegaci�n de toda la aplicaci�n. Ahora pasa la
#            lista de productos a todos los submen�s que la necesitan.
# Par�metro:
#   vproductos (lista): La lista de productos que ser� pasada a los submen�s.
def MenuPrincipal(vproductos):
    # Define la lista de opciones que se mostrar�n en el men� principal.
    datosmenuprincipal = ["1.-Productos", "2.-Punto de Venta", "3.- Inventarios", "5.- Salida"]
    # Se inicializa la variable 'opcion' para asegurar que el bucle comience.
    opcion = "0"
    # El bucle se repite mientras la opci�n del usuario no sea "5" (Salida).
    while opcion != "5":
        # Muestra el men� y captura la opci�n del usuario.
        opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes", datosmenuprincipal)
        # Verifica si la opci�n ingresada no es una de las opciones v�lidas.
        if opcion not in ["1", "2", "3", "5"]:
            # Informa al usuario que la opci�n es incorrecta.
            print("Opcion incorrecta")
        else:
            # Si la opci�n es "1", navega al men� de productos.
            if opcion == "1":
                # Llama al men� de productos, pasando la lista de productos.
                MenuProductos(vproductos)
            # Si la opci�n es "2", navega al men� de punto de venta.
            elif opcion == "2":
                MenuPuntoVenta("000")
            # Si la opci�n es "3", navega al men� de inventarios.
            elif opcion == "3":
                # Llama al men� de inventario, pasando la lista de productos.
                MenuInventario(vproductos)
            # Si la opci�n es "5", finaliza el programa.
            elif opcion == "5":
                print("Salida del Sistema")

# --- PUNTO DE ENTRADA DEL PROGRAMA ---
# Este bloque de c�digo solo se ejecuta cuando el archivo se corre directamente.
if __name__ == "__main__":
    # Llama a la funci�n CargarProductos() para obtener la lista inicial de productos
    # y la guarda en la variable 'productos'.
    productos = CargarProductos()
    # Llama al procedimiento del men� principal para iniciar la aplicaci�n,
    # pas�ndole la lista de productos reci�n cargada.
    MenuPrincipal(productos)             

