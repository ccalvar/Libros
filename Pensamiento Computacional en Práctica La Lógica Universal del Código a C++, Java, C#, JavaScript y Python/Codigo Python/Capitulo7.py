# Importa la clase 'datetime' del módulo 'datetime' para poder trabajar con fechas y horas.
from datetime import datetime

# Inicializa una lista de listas (matriz de 10x4) para almacenar los datos de los productos.
# Puede guardar hasta 10 productos, cada uno con 4 atributos (ej: código, nombre, precio, stock).
productos = [["" for _ in range(4)] for _ in range(10)]

# Inicializa una lista de listas (matriz de 100x5) para registrar los detalles de las ventas.
# Puede guardar hasta 100 artículos vendidos, cada uno con 5 atributos (ej: ticket, código, cant, precio, subtotal).
ventas = [["" for _ in range(5)] for _ in range(100)]

# Define una variable que actúa como índice o contador para la lista 'ventas'.
# Comienza en -1 para indicar que la lista está vacía. El primer elemento se guardará en la posición 0.
posventas = -1

# Guarda el tamaño máximo o capacidad de la lista 'ventas' en una variable.
# Esto hace el código más legible y fácil de modificar en el futuro.
tamventas = 100

# Inicializa una variable para almacenar la fecha de las transacciones.
# Comienza en 'None' porque aún no se ha establecido ninguna fecha.
fecha = None

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

def ObtenerUltimaPosicion(matriz):
    ultima_posicion = -1
    for i in range(len(matriz)):
        if matriz[i][0] is not None and matriz[i][0] != '':
            ultima_posicion = i
    return ultima_posicion


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
    cadena = codigo + producto + precio + cantidad
    return cadena



def MostrarLista(vproductos):
    salida = ""
    for ciclo in range(10):
        vproducto = [vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3]]
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
            vproducto = [vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2]]
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

# Se asume la existencia de las siguientes funciones auxiliares:
# ObtenerUltimaPosicion(matriz): Retorna el índice de la última fila con datos.
# RellenarEspacios(texto, longitud): Ajusta un texto a una longitud fija.
# Leer(mensaje): Muestra un mensaje y captura la entrada del usuario.
# ExisteProducto(codigo, lista): Busca un producto en la lista de productos y retorna su índice.
# IdTicketSiguiente(id_actual): Genera el siguiente ID de ticket.
# Fecha(): Retorna la fecha actual como un string.
# DesplegarMenu(titulo, opciones): Muestra un menú y retorna la opción seleccionada.
# MostrarProducto(producto): Formatea una lista de producto a string.

# --- FUNCIÓN ---
# Propósito: Crea una matriz vacía para almacenar todos los registros de ventas.
# Parámetros: Ninguno.
# Retorna: Una lista de listas (matriz) vacía, dimensionada por 'tamventas'.
def CrearVenta():
    venta = [["" for _ in range(5)] for _ in range(tamventas)]
    return venta

# --- FUNCIÓN ---
# Propósito: Obtiene el número de ticket de la última venta registrada.
# Parámetros:
#   pos (int): La posición del último registro en la matriz de ventas.
#   mventa (lista): La matriz que contiene todos los registros de ventas.
# Retorna: El ID del último ticket (str) o "000" si no hay ventas.
def UltimoTicket(pos, mventa):
    idticket = "000"
    # Si la posición es válida (mayor a -1), se obtiene el ID del ticket.
    if pos > -1:
        idticket = mventa[pos][0]
    return idticket

# --- FUNCIÓN ---
# Propósito: Crea una matriz vacía para un nuevo ticket temporal.
# Parámetros: Ninguno.
# Retorna: Una lista de listas (matriz) de 20x4 para el ticket actual.
def CrearTicket():
    return [["" for _ in range(4)] for _ in range(20)]

# --- FUNCIÓN ---
# Propósito: Busca si un producto (por su código) ya existe dentro de un ticket.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
#   codigo (str): El código del producto a buscar.
# Retorna: El índice (int) del producto si se encuentra, de lo contrario -1.
def ExisteTicketCodigo(mticket, codigo):
    enc = -1
    # Obtiene la última fila con datos para no recorrer toda la matriz.
    pos = ObtenerUltimaPosicion(mticket)
    print(f"buscando {codigo} tamano arreglo {pos}")
    # Recorre el ticket hasta la última posición con datos.
    for ciclo in range(pos + 1):
        # Compara los códigos, quitando espacios en blanco.
        if mticket[ciclo][0].strip() == codigo.strip():
            enc = ciclo
            return enc
    return enc

# --- FUNCIÓN ---
# Propósito: Inserta un producto en el ticket. Si ya existe, incrementa su cantidad.
# Parámetros:
#   mticket (lista): La matriz del ticket actual que será modificada.
#   datos (lista): Una lista con los datos del producto a insertar.
#   tamticket (int): El tamaño máximo del ticket.
# Retorna: True si la operación fue exitosa, False si el ticket está lleno.
def InsertarProductoTicket(mticket, datos, tamticket):
    sucedio = True
    posticket = ObtenerUltimaPosicion(mticket)
    # Verifica si el producto ya está en el ticket.
    enc = ExisteTicketCodigo(mticket, datos[0])
    # Verifica si hay espacio en el ticket.
    if posticket < tamticket:
        # Si el producto ya existe (enc > -1), incrementa la cantidad.
        if enc > -1:
            print("ya existe el producto en el ticket lo incrementare")
            cantidadactual = int(mticket[enc][3])
            mticket[enc][3] = str(cantidadactual + 1)
        # Si es un producto nuevo, lo agrega en la siguiente posición libre.
        else:
            posticket += 1
            mticket[posticket][0] = datos[0] # Código
            mticket[posticket][1] = datos[1] # Nombre
            mticket[posticket][2] = datos[2] # Precio
            mticket[posticket][3] = datos[3] # Cantidad
            print("Insertarndo No existe el producto en el ticket ")
    else:
        # Si no hay espacio, la operación falla.
        sucedio = False
    return sucedio

# --- FUNCIÓN ---
# Propósito: Calcula el total para una línea de producto (precio * cantidad).
# Parámetros:
#   precio (str): El precio unitario del producto.
#   cantidad (str): La cantidad de productos.
# Retorna: Un string formateado a dos decimales con el total.
def TotalProducto(precio, cantidad):
    total = float(precio) * float(cantidad)
    return f"{total:.2f}"

# --- FUNCIÓN ---
# Propósito: Formatea una línea de producto del ticket para su visualización.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
#   pos (int): La posición (fila) del producto a formatear.
# Retorna: Una cadena de texto (str) con la línea del producto formateada y alineada.
def MostrarProductoTicket(mticket, pos):
    codigo = RellenarEspacios(mticket[pos][0], 5)
    producto = RellenarEspacios(mticket[pos][1], 30)
    precio = RellenarEspacios(mticket[pos][2], 10)
    cantidad = RellenarEspacios(mticket[pos][3], 5)
    totalproducto = RellenarEspacios(TotalProducto(mticket[pos][2], mticket[pos][3]), 10)
    cadena = ''.join([codigo, producto, precio, cantidad, totalproducto])
    return cadena

# --- FUNCIÓN ---
# Propósito: Construye una representación en texto de todo el ticket.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
# Retorna: Un string (str) con todos los productos del ticket formateados.
def MostrarTicket(mticket):
    salida = ""
    pos = ObtenerUltimaPosicion(mticket)
    # Itera sobre cada producto en el ticket y lo formatea.
    for ciclo in range(pos + 1):
        salida += MostrarProductoTicket(mticket, ciclo) + "\n"
    return salida

# --- FUNCIÓN ---
# Propósito: Calcula la suma de los totales de todos los productos en el ticket (Subtotal).
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
# Retorna: El valor del subtotal (float).
def SubTotalTicket(mticket):
    subtotal = 0
    pos = ObtenerUltimaPosicion(mticket)
    for ciclo in range(pos + 1):
        subtotal += float(TotalProducto(mticket[ciclo][2], mticket[ciclo][3]))
    return subtotal

# --- FUNCIÓN ---
# Propósito: Calcula el impuesto (IVA) del 16% sobre el subtotal.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
# Retorna: El valor del IVA (float), o -1 si no hay subtotal.
def IvaTicket(mticket):
    subtotal = SubTotalTicket(mticket)
    if subtotal > 0:
        subtotal = 0.16 * subtotal
    else:
        subtotal = -1
    return subtotal

# --- FUNCIÓN ---
# Propósito: Calcula el total final de la venta (Subtotal + IVA).
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
# Retorna: El valor del total (float).
def TotalTicket(mticket):
    total = SubTotalTicket(mticket)
    if total > 0:
        total = IvaTicket(mticket) + total
    return total

# --- FUNCIÓN ---
# Propósito: Genera el recibo final de la venta en formato de texto.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
#   idticket (str): El ID del ticket.
#   fecha (str): La fecha de la venta.
# Retorna: Un string (str) con el recibo completo y formateado.
def MostrarTicketVenta(mticket, idticket, fecha):
    salida = ""
    subtotal = "{:.2f}".format(SubTotalTicket(mticket))
    iva = "{:.2f}".format(IvaTicket(mticket))
    total = "{:.2f}".format(TotalTicket(mticket))
    salida = "Fecha " + fecha + " Ticket No." + idticket
    salida += "\n" + MostrarTicket(mticket)
    salida += "\n\n El total sin iva " + subtotal
    salida += "\n el iva total es " + iva
    salida += "\n el total de la venta fue " + total
    return salida

# --- FUNCIÓN ---
# Propósito: Muestra la lista de productos disponibles para la venta (con stock > 0).
# Parámetros:
#   vproductos (lista): La lista de todos los productos.
# Retorna: Un string (str) con la lista de productos formateada.
def MostrarListaProductosVenta(vproductos):
    salida = ""
    for ciclo in range(10):
        existencia = int(vproductos[ciclo][3])
        if existencia > 0:
            vproducto = vproductos[ciclo][:]
            cadena = MostrarProducto(vproducto)
            salida += cadena + "\n"
    return salida

# --- PROCEDIMIENTO ---
# Propósito: Gestiona el proceso de agregar un producto a la venta.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
#   mproductos (lista): La lista de productos (para descontar stock).
#   idticket (str): El ID del ticket actual.
#   tamticket (int): El tamaño máximo del ticket.
def CapturaVentaProducto(mticket, mproductos, idticket, tamticket):
    info = MostrarListaProductosVenta(mproductos)
    codigo = Leer(info + "\nIntroduce el codigo del producto")
    if codigo is not None:
        # Busca el producto en la lista de productos.
        posp = ExisteProducto(codigo.strip(), mproductos)
        if posp > -1:
            # Verifica si hay stock.
            if int(mproductos[posp][3]) > 0:
                # Disminuye el stock en 1.
                cant = int(mproductos[posp][3])
                cant = cant - 1
                mproductos[posp][3] = str(cant)
                # Prepara los datos para insertar en el ticket.
                producto = mproductos[posp][:]
                print(MostrarProducto(producto))
                venta = [None] * 4
                venta[0] = mproductos[posp][0]
                venta[1] = mproductos[posp][1]
                venta[2] = mproductos[posp][2]
                venta[3] = "1"
                # Inserta el producto en el ticket.
                if not InsertarProductoTicket(mticket, venta, tamticket):
                    print("el Arreglo esta lleno \n")
            else:
                print("no hay productos para venta")
        else:
            print("el codigo no existe no se puede agregar\n")
    else:
        print("dato nulo\n")

# --- PROCEDIMIENTO ---
# Propósito: Remueve físicamente una fila de un producto en el ticket.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
#   pos (int): La posición (fila) a remover.
def RemoverProductoTicket(mticket, pos):
    tam = ObtenerUltimaPosicion(mticket)
    # Si no es la última fila, desplaza las filas de abajo hacia arriba.
    if tam > pos:
        for i in range(pos, tam):
            mticket[i] = mticket[i + 1]
    # Limpia la última fila.
    mticket[tam][0] = None

# --- PROCEDIMIENTO ---
# Propósito: Lógica para eliminar un producto: si la cantidad es > 1, la disminuye. Si es 1, lo remueve.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
#   pos (int): La posición del producto a eliminar.
def EliminarProductoTicket(mticket, pos):
    cantidad = int(mticket[pos][3])
    if cantidad > 1:
        mticket[pos][3] = str(cantidad - 1)
    else:
        RemoverProductoTicket(mticket, pos)

# --- PROCEDIMIENTO ---
# Propósito: Gestiona la eliminación de un producto del ticket, devolviendo el stock.
# Parámetros:
#   mticket (lista): La matriz del ticket actual.
#   mproductos (lista): La lista de productos (para devolver stock).
def Eliminar(mticket, mproductos):
    info = MostrarTicket(mticket)
    codigo = Leer(info + "\nIntroduce el codigo del producto")
    if codigo is not None:
        # Busca el producto en el ticket.
        pos = ExisteTicketCodigo(mticket, codigo)
        if pos > -1:
            # Busca el producto en la lista general de productos.
            posproducto = ExisteProducto(codigo, mproductos)
            # Incrementa el stock del producto en 1.
            nuevacantidad = str(int(mproductos[posproducto][3]) + 1)
            mproductos[posproducto][3] = nuevacantidad
            # Elimina el producto del ticket.
            EliminarProductoTicket(mticket, pos)
    else:
        print("dato nulo")

# --- PROCEDIMIENTO ---
# Propósito: Copia los productos de un ticket finalizado al registro global de ventas.
# Parámetros:
#   mticket (lista): La matriz del ticket pagado.
#   mventa (lista): La matriz de ventas donde se registrará la información.
#   idticket (str): El ID del ticket.
def AgregarProductoAVenta(mticket, mventa, idticket):
    posventas = ObtenerUltimaPosicion(mventa)
    posticket = ObtenerUltimaPosicion(mticket)
    for i in range(posticket + 1):
        if mticket[i][0] is not None:
            posventas += 1
            mventa[posventas][0] = idticket       # ID del ticket
            mventa[posventas][1] = mticket[i][0]  # Código del producto
            mventa[posventas][2] = mticket[i][1]  # Nombre del producto
            mventa[posventas][3] = mticket[i][2]  # Precio del producto
            mventa[posventas][4] = mticket[i][3]  # Cantidad del producto

# --- PROCEDIMIENTO ---
# Propósito: Gestiona el pago de un ticket.
# Parámetros:
#   idticket (str): El ID del ticket a pagar.
#   mventa (lista): La matriz de ventas.
#   mticket (lista): La matriz del ticket actual.
def Pagar(idticket, mventa, mticket):
    posventas = ObtenerUltimaPosicion(mventa)
    post = ObtenerUltimaPosicion(mticket)
    # Verifica que haya espacio en el registro de ventas.
    if (posventas + post) < 100:
        AgregarProductoAVenta(mticket, mventa, idticket)
    else:
        print("Desbordamiento de Memoria de ventas")

# --- PROCEDIMIENTO ---
# Propósito: Devuelve el stock de todos los productos de un ticket cancelado.
# Parámetros:
#   mticket (lista): La matriz del ticket cancelado.
#   mproductos (lista): La lista de productos donde se devolverá el stock.
def DevolucionTicket(mticket, mproductos):
    posmticket = ObtenerUltimaPosicion(mticket)
    for pos in range(posmticket + 1):
        codigo = mticket[pos][0].strip()
        posp = ExisteProducto(codigo, mproductos)
        if posp > -1:
            cant = int(mticket[pos][3]) + int(mproductos[posp][3])
            mproductos[posp][3] = str(cant)

# --- PROCEDIMIENTO ---
# Propósito: Es el menú principal del punto de venta que controla toda la interacción.
# Parámetros:
#   ventas (lista): La matriz de ventas.
#   idticket (str): El ID del último ticket.
#   productos (lista): La lista de productos.
def MenuPuntoVenta(ventas, idticket, productos):
    opcion = ""
    membrete = ""
    pago = False
    tamticket = 50
    Vticket = [[None for _ in range(4)] for _ in range(tamticket)]
    # Genera el siguiente ID de ticket y obtiene la fecha.
    idticket = IdTicketSiguiente(idticket)
    fechadia = Fecha()
    # Bucle principal del menú.
    while opcion != "5":
        membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket
        membrete += "\n-----------------------------------------------------\n"
        Tickettexto = MostrarTicket(Vticket).strip()
        if Tickettexto.strip():
            membrete += "\n" + Tickettexto + "\n"
        datosmenu = ["1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida "]
        opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu)
        if opcion is None:
            print("dato incorrecto introducido")
        else:
            if opcion == "1":
                CapturaVentaProducto(Vticket, productos, idticket, tamticket)
            elif opcion == "2":
                Eliminar(Vticket, productos) # Se debe pasar 'productos' para devolver stock.
            elif opcion == "3":
                if ObtenerUltimaPosicion(Vticket) > -1:
                    print(MostrarTicket(Vticket))
            elif opcion == "4":
                print(MostrarTicketVenta(Vticket, idticket, fechadia).strip())
                Pagar(idticket, ventas, Vticket)
                pago = True
                opcion = "5" # Salir automáticamente después de pagar.
            elif opcion == "5":
                print("Salida del Ventas")
                # Si sale sin pagar, devuelve los productos al inventario.
                if not pago:
                    DevolucionTicket(Vticket, productos)
                    print("No pago el ticket")
                    print("eliminando ticket " + idticket)
            else:
                print("No existe esta opcion")

# --- FUNCIÓN ---
# Propósito: Formatea una línea del registro de ventas para su visualización.
# Parámetros:
#   venta (lista): Una fila del registro de ventas.
# Retorna: Un string (str) con la línea de venta formateada.
def MostrarVenta(venta):
    idticket = RellenarEspacios(venta[0], 6)
    codigo = RellenarEspacios(venta[1], 5)
    producto = RellenarEspacios(venta[2], 30)
    precio = RellenarEspacios(venta[3], 10)
    cantidad = RellenarEspacios(venta[4], 10)
    cadena = idticket + codigo + producto + precio + cantidad
    return cadena

# --- FUNCIÓN ---
# Propósito: Genera un reporte de texto con todas las ventas del día.
# Parámetros:
#   ventas (lista): La matriz con todos los registros de ventas.
# Retorna: Un string (str) con el reporte de ventas completo.
def MostrarListaVentas(ventas):
    posventas = ObtenerUltimaPosicion(ventas)
    salida = ""
    for ciclo in range(posventas + 1):
        venta = [ventas[ciclo][0], ventas[ciclo][1], ventas[ciclo][2], ventas[ciclo][3], ventas[ciclo][4]]
        cadena = MostrarVenta(venta)
        salida += cadena + "\n"
    return salida

def AgregarStock(vproductos):
    info = MostrarLista(vproductos)
    codigo = Leer(info + "\nIntroduce el codigo del producto a modificar")
    if codigo is not None:
        posicion = ExisteProducto(codigo, vproductos)
        if posicion > -1:
            vproducto = [vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][3], ""]
            cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ")
            if cantidad is not None:
                if EvaluarNumerico(cantidad, 2) or EvaluarNumerico(cantidad, 1):
                    nuevacantidad = str(int(cantidad) + int(vproducto[2]))
                    vproductos[posicion][3] = nuevacantidad
                else:
                    print("no es un valor numerico")
            else:
                print("dato nulo")
        else:
            print("no existe el codigo")
    else:
        print("dato nulo")

def MenuInventario(vproductos):
    datosmenuinventario = ["1.-Listado ", "2.-Agregar ", "3.-Salida "]
    opcion = "0"
    while opcion != "3":
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario)
        if opcion is None:
            print("opcion incorrecta ")
        else:
            if opcion == "1":
                print(MostrarLista(vproductos))
            elif opcion == "2":
                AgregarStock(vproductos)
            elif opcion == "3":
                print("Salida del Sistema ")
            else:
                print("No existe esta opcion ")

# Se asume la existencia de las siguientes funciones auxiliares:
# ObtenerUltimaPosicion(matriz): Retorna el índice de la última fila con datos.
# DesplegarMenu(titulo, opciones): Muestra un menú y retorna la opción seleccionada.
# CargarProductos(): Carga la lista inicial de productos.
# CrearVenta(): Crea la matriz vacía para las ventas.
# MenuProductos(productos): Inicia el submenú de gestión de productos.
# MenuPuntoVenta(ventas, idticket, productos): Inicia el submenú del punto de venta.
# MenuInventario(productos): Inicia el submenú de gestión de inventario.
# MostrarListaVentas(ventas): Genera un reporte en texto de todas las ventas.

# --- PROCEDIMIENTO ---
# Propósito: Es el menú principal y punto de navegación de toda la aplicación.
#            Orquesta las llamadas a los diferentes submenús (Productos, Ventas, etc.).
# Parámetros:
#   vproductos (lista): La lista de productos que será pasada a los submenús.
#   vventas (lista): La lista con los registros de ventas.
def MenuPrincipal(vproductos, vventas):
    # Define la lista de opciones que se mostrarán en el menú principal.
    datosmenuprincipal = ["1.-Productos ", "2.-Punto de Venta ", "3.- Inventario", "4.-Ventas", "5.-Salida "]
    opcion = "0"
    # El bucle se repite mientras la opción del usuario no sea "5" (Salida).
    while opcion != "5":
        # Antes de mostrar el menú, obtiene el ID del último ticket para pasarlo al punto de venta.
        idticket = ObtenerUltimoValorVentas(vventas)
        # Muestra el menú y captura la opción del usuario.
        opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequena", datosmenuprincipal)
        
        # Verifica si la opción es nula (posiblemente por una entrada inválida).
        if opcion is None:
            print("opcion incorrecta ")
        else:
            # Si la opción es "1", navega al menú de productos.
            if opcion == "1":
                MenuProductos(vproductos)
            # Si la opción es "2", navega al menú de punto de venta.
            elif opcion == "2":
                MenuPuntoVenta(vventas, idticket, vproductos)
            # Si la opción es "3", navega al menú de inventarios.
            elif opcion == "3":
                MenuInventario(vproductos)
            # Si la opción es "4", muestra el reporte de ventas.
            elif opcion == "4":
                print(MostrarListaVentas(vventas))
            # Si la opción es "5", finaliza el programa.
            elif opcion == "5":
                print("Salida del Sistema ")
            else:
                print("No existe esta opcion ")

# --- FUNCIÓN ---
# Propósito: Encuentra y devuelve el ID del ticket de la última venta registrada.
# Parámetros:
#   ventas (lista): La matriz que contiene todos los registros de ventas.
# Retorna: El ID del último ticket (str) o "000" si no hay ninguna venta.
def ObtenerUltimoValorVentas(ventas):
    # Define un valor por defecto en caso de que no haya ventas.
    ultimoValor = "000"
    # Obtiene el índice de la última fila que contiene datos.
    ultimaposicion = ObtenerUltimaPosicion(ventas)
    # Si se encontró una fila válida (índice >= 0)...
    if ultimaposicion >= 0:
        # ...obtiene el valor de la primera columna (el ID del ticket) de esa fila.
        ultimoValor = ventas[ultimaposicion][0]
    return ultimoValor

# --- PROCEDIMIENTO ---
# Propósito: Es la función principal que inicializa los datos y arranca la aplicación.
# Parámetros: Ninguno.
def main():
    # Carga la lista de productos en memoria.
    productos = CargarProductos()
    # Crea la estructura vacía para guardar las ventas.
    ventas = CrearVenta()
    # Lanza el menú principal, pasando las estructuras de datos recién creadas.
    MenuPrincipal(productos, ventas)

# --- PUNTO DE ENTRADA DEL PROGRAMA ---
# Este bloque estándar de Python se asegura de que el código dentro de él
# solo se ejecute cuando el script es corrido directamente.
if __name__ == "__main__":
    # Llama a la función 'main' para iniciar la ejecución del programa.
    main()