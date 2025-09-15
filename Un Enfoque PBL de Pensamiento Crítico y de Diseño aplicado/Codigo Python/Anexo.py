# Importa la clase 'datetime' del m�dulo 'datetime', que es fundamental para trabajar con fechas y horas.
from datetime import datetime

# Importa el m�dulo 'os', que permite interactuar con el sistema operativo.
# Es muy �til en aplicaciones de consola para funciones como limpiar la pantalla (os.system('cls' o 'clear')).
import os

# Inicializa una lista de listas (matriz de 10x4) para almacenar los datos de los productos.
# Puede guardar hasta 10 productos, cada uno con 4 atributos (ej: c�digo, nombre, precio, stock).
productos = [["" for _ in range(4)] for _ in range(10)]

# Inicializa una lista de listas (matriz de 100x5) para registrar los detalles de las ventas.
# Puede guardar hasta 100 art�culos vendidos, cada uno con 5 atributos (ej: ticket, c�digo, cant, precio, subtotal).
ventas = [["" for _ in range(5)] for _ in range(100)]

# Define una variable que act�a como �ndice o contador para la lista 'ventas'.
# Comienza en -1 para indicar que la lista est� vac�a. El primer elemento se guardar� en la posici�n 0.
posventas = -1

# Guarda el tama�o m�ximo o capacidad de la lista 'ventas' en una variable.
# Esto hace el c�digo m�s legible y f�cil de modificar en el futuro.
tamventas = 100

# Inicializa una variable para almacenar la fecha de las transacciones.
# Comienza en 'None' porque a�n no se ha establecido ninguna fecha.
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

def CrearVenta():
    venta = [["" for _ in range(5)] for _ in range(tamventas)]
    return venta

def UltimoTicket(pos, mventa):
    idticket = "000"
    if pos > -1:
        idticket = mventa[pos][0]
    return idticket

def CrearTicket():
        return [["" for _ in range(4)] for _ in range(20)]




def ExisteTicketCodigo(mticket, codigo):
    enc = -1
    pos = ObtenerUltimaPosicion(mticket)
    print(f"buscando {codigo} tamano arreglo {pos}")
    for ciclo in range(pos + 1):
        if mticket[ciclo][0].strip() == codigo.strip():
            enc = ciclo
            return enc
    return enc


def InsertarProductoTicket(mticket, datos, tamticket):
    sucedio = True
    posticket = ObtenerUltimaPosicion(mticket)
    enc = ExisteTicketCodigo(mticket, datos[0])
    if posticket < tamticket:
        if enc > -1:
            print("ya existe el producto en el ticket lo incrementare")
            cantidadactual = int(mticket[enc][3])
            mticket[enc][3] = str(cantidadactual + 1)
        else:
            posticket += 1
            mticket[posticket][0] = datos[0]
            mticket[posticket][1] = datos[1]
            mticket[posticket][2] = datos[2]
            mticket[posticket][3] = datos[3]
            print("Insertarndo No existe el producto en el ticket ")
    else:
        sucedio = False
    return sucedio


def TotalProducto(precio, cantidad):
    total = float(precio) * float(cantidad)
    return f"{total:.2f}"

def MostrarProductoTicket(mticket, pos):
    codigo = RellenarEspacios(mticket[pos][0], 5)
    producto = RellenarEspacios(mticket[pos][1], 30)
    precio = RellenarEspacios(mticket[pos][2], 10)
    cantidad = RellenarEspacios(mticket[pos][3], 5)
    totalproducto = RellenarEspacios(TotalProducto(mticket[pos][2], mticket[pos][3]), 10)
    cadena = ''.join([codigo, producto, precio, cantidad, totalproducto])
    return cadena


def MostrarTicket(mticket):
    salida = ""
    pos = ObtenerUltimaPosicion(mticket)
    for ciclo in range(pos + 1):
        salida += MostrarProductoTicket(mticket, ciclo) + "\n"
    return salida

def SubTotalTicket(mticket):
    subtotal = 0
    pos = ObtenerUltimaPosicion(mticket)
    for ciclo in range(pos + 1):
        subtotal += float(TotalProducto(mticket[ciclo][2], mticket[ciclo][3]))
    return subtotal


def IvaTicket(mticket):
    subtotal = SubTotalTicket(mticket)
    if subtotal > 0:
        subtotal = 0.16 * subtotal
    else:
        subtotal = -1
    return subtotal

def TotalTicket(mticket):
    total = SubTotalTicket(mticket)
    if total > 0:
        total = IvaTicket(mticket) + total
    return total

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


def MostrarListaProductosVenta(vproductos):
    salida = ""
    for ciclo in range(10):
        existencia = int(vproductos[ciclo][3])
        if existencia > 0:
            vproducto = vproductos[ciclo][:]  # Clonar el array
            cadena = MostrarProducto(vproducto)
            salida += cadena + "\n"  # Concatenar con nueva linea
    return salida


def CapturaVentaProducto(mticket, mproductos, idticket, tamticket):
    info = MostrarListaProductosVenta(mproductos)
    codigo = Leer(info + "\nIntroduce el codigo del producto")
    if codigo is not None:
        posp = ExisteProducto(codigo.strip(), mproductos)
        if posp > -1:
            if int(mproductos[posp][3]) > 0:
                cant = int(mproductos[posp][3])
                cant=cant-1
                mproductos[posp][3]= str(cant)
                producto = mproductos[posp][:]
                print(MostrarProducto(producto))
                venta = [None] * 4
                venta[0] = mproductos[posp][0]
                venta[1] = mproductos[posp][1]
                venta[2] = mproductos[posp][2]
                venta[3] = "1"
                if not InsertarProductoTicket(mticket, venta, tamticket):
                    print("el Arreglo esta lleno \n")
            else:
                print("no hay productos para venta")
        else:
            print("el codigo no existe no se puede agregar\n")
    else:
        print("dato nulo\n")

def RemoverProductoTicket(mticket, pos):
    tam = ObtenerUltimaPosicion(mticket)
    if tam > pos:
        for i in range(pos, tam):
            mticket[i] = mticket[i + 1]
        mticket[tam][0] = None
    else:
        mticket[pos][0] = None

def EliminarProductoTicket(mticket, pos):
    cantidad = int(mticket[pos][3])
    if cantidad > 1:
        mticket[pos][3] = str(cantidad - 1)
    else:
        RemoverProductoTicket(mticket, pos)

def Eliminar(mticket,mproductos):
    info = MostrarTicket(mticket)
    codigo = Leer(info + "\nIntroduce el codigo del producto")
    if codigo is not None:
        pos = ExisteTicketCodigo(mticket, codigo)
        if pos > -1:
            posproducto = ExisteProducto(codigo, mproductos)
            nuevacantidad = str(int(mproductos[posproducto][3]) + 1)
            mproductos[posproducto][3] = nuevacantidad
            EliminarProductoTicket(mticket, pos)
    else:
        print("dato nulo")



def AgregarProductoAVenta(mticket, mventa, idticket):
    posventas = ObtenerUltimaPosicion(mventa)
    posticket = ObtenerUltimaPosicion(mticket)
    for i in range(posticket + 1):
        if mticket[i][0] is not None:  # Verificar que la fila no est� vacia
            posventas += 1
            mventa[posventas][0] = idticket  # Establecer el ID del ticket
            mventa[posventas][1] = mticket[i][0]  # Codigo del producto
            mventa[posventas][2] = mticket[i][1]  # Nombre del producto
            mventa[posventas][3] = mticket[i][2]  # Precio del producto
            mventa[posventas][4] = mticket[i][3]  # Cantidad del producto

def Pagar(idticket, mventa, mticket):
    posventas = ObtenerUltimaPosicion(mventa)
    post = ObtenerUltimaPosicion(mticket)
    if (posventas + post) < 100:
        AgregarProductoAVenta(mticket, mventa, idticket)
    else:
        print("Desbordamiento de Memoria de ventas")

def DevolucionTicket(mticket, mproductos):
    posmticket = ObtenerUltimaPosicion(mticket)
    for pos in range(posmticket + 1):
        codigo = mticket[pos][0].strip()
        posp = ExisteProducto(codigo, mproductos)

        if posp > -1:
            cant = int(mticket[pos][3]) + int(mproductos[posp][3])
            mproductos[posp][3] = str(cant)

# Se asume la existencia de las siguientes funciones auxiliares:
# IdTicketSiguiente(id_actual): Genera el siguiente ID de ticket.
# Fecha(): Retorna la fecha actual como un string.
# MostrarTicket(ticket): Formatea el contenido de un ticket a string.
# DesplegarMenu(titulo, opciones): Muestra un men� y retorna la opci�n seleccionada.
# CapturaVentaProducto(...): L�gica para agregar un producto al ticket.
# Eliminar(...): L�gica para quitar un producto del ticket.
# ObtenerUltimaPosicion(matriz): Retorna el �ndice de la �ltima fila con datos.
# MostrarTicketVenta(...): Genera el recibo final en formato texto.
# Pagar(...): Registra la venta en la matriz de ventas en memoria.
# GuardarDatosCsvVentaTicket(...): Guarda el detalle de un ticket en un archivo CSV.
# generarCVSFilaTicket(...): Formatea una l�nea de resumen de venta para CSV.
# GuardarDatosCsvVenta(...): Guarda una l�nea en el archivo maestro de ventas.
# DevolucionTicket(...): Devuelve el stock de un ticket cancelado.

# --- PROCEDIMIENTO ---
# Prop�sito: Es el men� principal del punto de venta que controla toda la interacci�n de una
#            sola transacci�n, desde agregar productos hasta pagar y guardar la venta en archivos.
# Par�metros:
#   ventas (lista): La matriz principal de ventas en memoria.
#   idticket (str): El ID del �ltimo ticket, usado para generar el siguiente.
#   productos (lista): La lista de productos, para gestionar el stock.
#   narchivo (str): El nombre del archivo CSV diario donde se guardar�n los detalles del ticket.
def MenuPuntoVenta(ventas, idticket, productos, narchivo):
    # --- Inicializaci�n de variables para la venta actual ---
    opcion = ""
    membrete = ""
    pago = False  # Bandera para saber si el ticket fue pagado.
    tamticket = 50
    # Se crea un ticket temporal vac�o para esta venta espec�fica.
    Vticket = [[None for _ in range(4)] for _ in range(tamticket)]

    # --- Preparaci�n del Ticket ---
    # Se genera el n�mero de ticket para esta nueva venta.
    idticket = IdTicketSiguiente(idticket)
    # Se obtiene la fecha una sola vez para mantener la consistencia.
    fechadia = Fecha()
    
    # --- Bucle Principal de la Venta ---
    # El men� se repite hasta que el usuario elija la opci�n "5" (o pague).
    while opcion != "5":
        # Construye el encabezado que se mostrar� en pantalla.
        membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket
        membrete += "\n-----------------------------------------------------\n"
        # Obtiene el contenido actual del ticket en formato texto.
        Tickettexto = MostrarTicket(Vticket).strip()
        # Solo muestra el contenido del ticket si no est� vac�o.
        if Tickettexto:
            membrete += "\n" + Tickettexto + "\n"
        
        datosmenu = ["1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida "]
        # Muestra el men� y obtiene la opci�n del usuario.
        opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu)

        if opcion is None:
            print("dato incorrecto introducido")
        else:
            if opcion == "1":
                # Llama a la funci�n para agregar un producto al ticket.
                CapturaVentaProducto(Vticket, productos, idticket, tamticket)
            elif opcion == "2":
                # Llama a la funci�n para eliminar un producto.
                # Nota: La funci�n Eliminar podr�a necesitar la lista 'productos' para devolver el stock.
                Eliminar(Vticket, productos)
            elif opcion == "3":
                # Muestra el contenido del ticket si no est� vac�o.
                if ObtenerUltimaPosicion(Vticket) > -1:
                    print(MostrarTicket(Vticket))
            elif opcion == "4": # --- L�gica de Pago y Guardado ---
                # Muestra el recibo final en pantalla.
                print(MostrarTicketVenta(Vticket, idticket, fechadia).strip())
                # Registra la venta en la matriz de ventas en memoria.
                Pagar(idticket, ventas, Vticket)
                
                # Solo guarda en archivo si el ticket tiene productos.
                if (ObtenerUltimaPosicion(Vticket) > -1):
                    # 1. Guarda el DETALLE del ticket en el archivo diario (ej: '2025-09-15.csv').
                    GuardarDatosCsvVentaTicket(Vticket, narchivo, ObtenerUltimaPosicion(Vticket), idticket)
                    # 2. Genera una l�nea de RESUMEN de la venta.
                    cadena = generarCVSFilaTicket(fechadia, idticket, f"{SubTotalTicket(Vticket):.2f}", f"{IvaTicket(Vticket):.2f}", f"{TotalTicket(Vticket):.2f}")
                    # 3. Guarda el RESUMEN en el archivo maestro 'ventas.csv'.
                    GuardarDatosCsvVenta("ventas.csv", cadena)
                
                pago = True # Marca el ticket como pagado.
                opcion = "5" # Fuerza la salida del men� de venta.
            elif opcion == "5": # --- L�gica de Salida / Cancelaci�n ---
                print("Salida del Ventas")
                # Si el usuario sale SIN haber pagado...
                if not pago:
                    # ...devuelve todos los productos del ticket al inventario.
                    DevolucionTicket(Vticket, productos)
                    print("No pago el ticket")
                    print("eliminando ticket " + idticket)
            else:
                print("No existe esta opcion")

def MostrarVenta(venta):
    idticket = RellenarEspacios(venta[0], 6)
    codigo = RellenarEspacios(venta[1], 5)
    producto = RellenarEspacios(venta[2], 30)
    precio = RellenarEspacios(venta[3], 10)
    cantidad = RellenarEspacios(venta[4], 10)
    cadena = idticket + codigo + producto + precio + cantidad
    return cadena

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


# --- PROCEDIMIENTO ---
# Prop�sito: Es el men� principal y punto de navegaci�n de toda la aplicaci�n.
#            Esta versi�n mejorada carga el �ltimo ID de ticket desde un archivo diario
#            para mantener la continuidad entre sesiones.
# Par�metros:
#   vproductos (lista): La lista de productos que ser� pasada a los submen�s.
#   vventas (lista): La lista con los registros de ventas en memoria.
def MenuPrincipal(vproductos, vventas):
    # Define la lista de opciones que se mostrar�n en el men� principal.
    datosmenuprincipal = ["1.-Productos ", "2.-Punto de Venta ", "3.- Inventario", "4.-Ventas", "5.-Salida "]
    opcion = "0"
    
    # --- L�gica de Persistencia ---
    # Crea el nombre del archivo de ventas basado en la fecha actual (ej: '2025-09-15.csv').
    narchivo = Fecha() + ".csv"
    idticket = None
    # Verifica si ya existe un archivo de ventas para el d�a de hoy.
    if ExisteArchivo(narchivo):
        print("Leyendo archivo de ventas de hoy: " + narchivo)
        # Si existe, lee el archivo para obtener el ID del �ltimo ticket guardado.
        idticket = LeerDatosCvs(narchivo)
    
    # El bucle principal del men� se repite hasta que el usuario elija "5" (Salida).
    while opcion != "5":
        # Si no se pudo cargar un ID de ticket desde el archivo (ej: primer uso del d�a),
        # se obtiene de la forma anterior (desde la memoria).
        if not idticket:
            idticket = ObtenerUltimoValorVentas(vventas)
            
        # Muestra el men� principal y captura la opci�n del usuario.
        opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequena", datosmenuprincipal)
        
        # Verifica si la opci�n es nula.
        if opcion is None:
            print("opcion incorrecta ")
        else:
            # Si la opci�n es "1", navega al men� de productos.
            if opcion == "1":
                MenuProductos(vproductos)
            # Si la opci�n es "2", navega al men� de punto de venta.
            elif opcion == "2":
                # Pasa el nombre del archivo diario para que el punto de venta sepa d�nde guardar.
                MenuPuntoVenta(vventas, idticket, vproductos, narchivo)
            # Si la opci�n es "3", navega al men� de inventarios.
            elif opcion == "3":
                MenuInventario(vproductos)
            # Si la opci�n es "4", muestra el reporte de ventas en memoria.
            elif opcion == "4":
                print(MostrarListaVentas(vventas))
            # Si la opci�n es "5", finaliza el programa.
            elif opcion == "5":
                print("Salida del Sistema ")
            else:
                print("No existe esta opcion ")

def ObtenerUltimoValorVentas(ventas):
    ultimoValor = "000"
    ultimaposicion = ObtenerUltimaPosicion(ventas)
    if ultimaposicion >= 0:
            ultimoValor = ventas[ultimaposicion][0]
    return ultimoValor

# Se asume la existencia de las siguientes funciones auxiliares:
# CargarProductos(): Carga la lista inicial de productos.
# CrearVenta(): Crea la matriz vac�a para las ventas.
# MenuPrincipal(productos, ventas): Inicia el men� principal de la aplicaci�n.
# Y el m�dulo 'os' debe estar importado previamente.

# --- FUNCI�N ---
# Prop�sito: Verifica de forma segura si un archivo ya existe en el disco.
# Par�metro:
#   narchivo (str): El nombre o la ruta del archivo a verificar.
# Retorna: True si el archivo existe, False en caso contrario.
def ExisteArchivo(narchivo):
    # Utiliza la funci�n 'exists' del m�dulo 'os.path' para hacer la comprobaci�n.
    return os.path.exists(narchivo)

# --- PROCEDIMIENTO ---
# Prop�sito: Escribe contenido de texto en un archivo. Decide si debe agregar
#            contenido al final ('append') o crear/sobrescribir el archivo ('write').
# Par�metros:
#   archivo (str): El nombre del archivo donde se escribir�.
#   contenido (str): El texto que se va a guardar.
def EscribirArchivoCSV(archivo, contenido):
    try:
        # Se usa un operador ternario para decidir el modo de apertura.
        # Si el archivo ya existe, se abre en modo 'a' (append) para a�adir datos sin borrar.
        # Si no existe, se abre en modo 'w' (write) para crearlo.
        modo = 'a' if ExisteArchivo(archivo) else 'w'
        # El bloque 'with open' asegura que el archivo se cierre autom�ticamente.
        with open(archivo, modo) as escritor:
            escritor.write(contenido)
    except Exception as e:
        # Captura cualquier error que pueda ocurrir durante la escritura.
        print(f"Ocurrio un error al escribir en el archivo: {e}")

# --- FUNCI�N ---
# Prop�sito: Lee un archivo CSV y devuelve el primer dato de la �ltima l�nea v�lida.
#            Nota: Tal como est� escrito, itera por todo el archivo y el valor que
#            finalmente retorna es el de la �ltima l�nea que procesa.
# Par�metro:
#   nombreArchivo (str): El nombre del archivo a leer.
# Retorna: El primer elemento (str) de la �ltima fila, o un string vac�o si hay error.
def LeerDatosCvs(nombreArchivo):
    primerDato = ""
    try:
        # Abre el archivo en modo lectura ('r') con codificaci�n 'utf-8'.
        with open(nombreArchivo, 'r', encoding='utf-8') as lector:
            # Lee todas las l�neas del archivo en una lista.
            lineas = lector.readlines()
            # Itera sobre cada l�nea le�da.
            for linea in lineas:
                # Elimina espacios en blanco al inicio y al final.
                linea = linea.strip()
                # Si la l�nea no est� vac�a...
                if linea:
                    # ...divide la l�nea por comas para obtener los datos.
                    datos = linea.split(',')
                    # Si hay datos, actualiza 'primerDato' con el primer elemento.
                    # Este valor se sobrescribir� hasta llegar a la �ltima l�nea.
                    if len(datos) > 0:
                        primerDato = datos[0]
    except IOError as e:
        print("Error al leer el archivo: " + str(e))
    return primerDato

# --- FUNCI�N ---
# Prop�sito: Formatea una fila de datos para un ticket en formato CSV.
# Par�metros:
#   idticket (str): El ID del ticket.
#   dato1, dato2, dato3, dato4 (str): Los datos del producto en el ticket.
# Retorna: Una cadena de texto (str) con los datos separados por comas.
def generarCVSFilaTicket(idticket, dato1, dato2, dato3, dato4):
    return f"{idticket},{dato1},{dato2},{dato3},{dato4}"

# --- PROCEDIMIENTO ---
# Prop�sito: Guarda todos los productos de un ticket en un archivo CSV.
# Par�metros:
#   matriz (lista): La matriz del ticket con los productos.
#   nombrearchivo (str): El nombre del archivo donde se guardar�n los datos.
#   filas (int): El n�mero de filas a procesar en la matriz.
#   idticket (str): El ID del ticket que se asignar� a cada fila.
def GuardarDatosCsvVentaTicket(matriz, nombrearchivo, filas, idticket):
    cadena = ""
    # Recorre la matriz del ticket hasta el n�mero de filas indicado.
    for fila in range(filas + 1):
        # Genera la cadena CSV para la fila actual.
        cadenafila = generarCVSFilaTicket(idticket, matriz[fila][0], matriz[fila][1], matriz[fila][2], matriz[fila][3])
        # Acumula la fila formateada en la cadena principal, a�adiendo un salto de l�nea.
        cadena += cadenafila + "\n"
    # Escribe la cadena completa en el archivo de una sola vez.
    EscribirArchivoCSV(nombrearchivo, cadena)

# --- FUNCI�N ---
# Prop�sito: Formatea una fila de datos de venta en formato CSV, limpiando espacios.
# Retorna: Una cadena de texto (str) con los datos limpios y separados por comas.
def GenerarCsvFilaVenta(dato1, dato2, dato3, dato4, dato5):
    return f"{dato1.strip()},{dato2.strip()},{dato3.strip()},{dato4.strip()},{dato5.strip()}"

# --- PROCEDIMIENTO ---
# Prop�sito: Guarda contenido en el archivo de ventas. Act�a como un intermediario.
# Par�metros:
#   nombreArchivo (str): El nombre del archivo de ventas.
#   contenido (str): El contenido a guardar.
def GuardarDatosCsvVenta(nombreArchivo, contenido):
    # La comprobaci�n de 'existe' no se utiliza aqu�, pero no afecta la funcionalidad.
    existe = ExisteArchivo(nombreArchivo)
    # Delega la tarea de escritura a la funci�n principal.
    EscribirArchivoCSV(nombreArchivo, contenido)

# --- PROCED-IMIENTO ---
# Prop�sito: Es la funci�n principal que inicializa los datos y arranca la aplicaci�n.
# Par�metros: Ninguno.
def main():
    # Carga la lista de productos en memoria.
    productos = CargarProductos()
    # Crea la estructura vac�a para guardar las ventas.
    ventas = CrearVenta()
    # Lanza el men� principal, pasando las estructuras de datos reci�n creadas.
    MenuPrincipal(productos, ventas)

# --- PUNTO DE ENTRADA DEL PROGRAMA ---
# Este bloque est�ndar de Python se asegura de que el c�digo dentro de �l
# solo se ejecute cuando el script es corrido directamente.
if __name__ == "__main__":
    # Llama a la funci�n 'main' para iniciar la ejecuci�n del programa.
    main()
