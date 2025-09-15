
# Importa la clase 'datetime' del módulo 'datetime' para poder trabajar con fechas y horas.
from datetime import datetime

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
    
def RellenaEspacios(dato, tamano):
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


# --- PROCEDIMIENTO ---
# Gestiona las opciones relacionadas con los productos.
def MenuProductos():
    # Se crea una lista con las opciones de texto que se mostrarán en el menú.
    datosmenuproductos = ["1.-Modificar ", "2.-Listado ", "3.-Salida"]
    # Se inicializa la variable 'opcion' con "0" para asegurar que el bucle while se inicie.
    opcion = "0"
    # Se inicia un bucle que se repetirá mientras la opción elegida no sea "3" (Salida).
    while opcion != "3":
        # Llama a la función 'DesplegarMenu' para mostrar las opciones y capturar la elección del usuario.
        opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos)
        # Comprueba si la función 'DesplegarMenu' no devolvió un valor (posiblemente por una entrada inválida).
        if not opcion:
            # Informa al usuario que la opción es incorrecta.
            print("opción incorrecta ")
        # Si se recibió una opción válida, se procesa.
        else:
            # Si el usuario eligió la opción "1".
            if opcion == "1":
                # Imprime el mensaje para modificar el precio de un producto.
                print("Modificar Precio Producto")
            # Si el usuario eligió la opción "2".
            elif opcion == "2":
                # Imprime el mensaje para mostrar el listado de productos.
                print("Listado Producto")
            # Si el usuario eligió la opción "3".
            elif opcion == "3":
                # Imprime el mensaje de salida del submenú.
                print("Salida del Sistema")
            # Si la opción ingresada no es 1, 2 ni 3.
            else:
                # Informa al usuario que la opción no existe.
                print("No existe esta opción")

# --- PROCEDIMIENTO ---
# Gestiona las operaciones de una venta (agregar, eliminar, pagar).
# Parámetro:
#   idticket (string): Recibe el ID del último ticket para generar el siguiente.
def MenuPuntoVenta(idticket):
    # Se inicializa la variable 'opcion' como None.
    opcion = None
    # Se inicializa la variable 'membrete' como None.
    membrete = None
    # Se inicializa la variable 'pago' en False, indicando que el ticket aún no se ha pagado.
    pago = False
    # Llama a la función 'IdTicketSiguiente' para obtener el número del nuevo ticket.
    idticket = IdTicketSiguiente(idticket)
    # Llama a la función 'Fecha' para obtener la fecha actual.
    fechadia = Fecha()
    # Se construye el encabezado del menú con la fecha y el número de ticket.
    membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket
    # Se añade una línea separadora al encabezado para mejorar la presentación.
    membrete += "\n-------------------------------------------------------\n"
    # Se define una lista con las opciones del menú de punto de venta.
    datosmenu = ["1. - Agregar", "2. - Eliminar", "3. - Listado", "4. - Pagar", "5. - Salida"]
    # Bucle que se ejecuta mientras la opción no sea "5" (Salida).
    while opcion != "5":
        # Muestra el menú con el encabezado y las opciones, y captura la elección del usuario.
        opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu)
        # Verifica si la opción ingresada no es una de las válidas.
        if opcion not in ["1", "2", "3", "4", "5"]:
            # Informa al usuario que la opción es incorrecta.
            print("Opción Incorrecta")
        # Si la opción es válida, se procesa.
        else:
            # Si la opción es "1".
            if opcion == "1":
                # Imprime el mensaje para agregar un artículo.
                print("Agregar Artículo al Ticket")
            # Si la opción es "2".
            elif opcion == "2":
                # Imprime el mensaje para eliminar un artículo.
                print("Eliminar Artículo del Ticket")
            # Si la opción es "3".
            elif opcion == "3":
                # Imprime el mensaje para listar los artículos del ticket.
                print("Listado de Artículos del Ticket")
            # Si la opción es "4".
            elif opcion == "4":
                # Imprime el mensaje para pagar el ticket.
                print("Pagar Ticket y salir")
                # Se fuerza la 'opcion' a "5" para que el bucle while termine.
                opcion = "5"
                # Se cambia el estado de 'pago' a True, indicando que el ticket se pagó.
                pago = True
            # Si la opción es "5".
            elif opcion == "5":
                # Imprime el mensaje de salida del menú de ventas.
                print("Salida del Ventas")
                # Verifica si el ticket no fue pagado.
                if not pago:
                    # Informa al usuario que el ticket no se pagó.
                    print("No pagó el ticket")
                    # Informa al usuario que el ticket actual será eliminado.
                    print(f"Eliminando ticket {idticket}")

# --- PROCEDIMIENTO ---
# Gestiona las opciones de inventario (listar, agregar).
def MenuInventario():
    # Se crea una lista con las opciones de texto para el menú de inventarios.
    datosmenuinventarios = ["1. - Listado", "2. - Agregar", "3. - Salida"]
    # Se inicializa la variable 'opcion' para asegurar el inicio del bucle.
    opcion = "0"
    # Bucle que se repite mientras la opción del usuario no sea "3".
    while opcion != "3":
        # Llama a la función 'DesplegarMenu' para mostrar el menú y obtener la opción del usuario.
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventarios)
        # Verifica si la opción ingresada no es una de las válidas ("1", "2", "3").
        if opcion not in ["1", "2", "3"]:
            # Informa al usuario que la opción es incorrecta.
            print("Opción incorrecta")
        # Si la opción es válida, se procesa.
        else:
            # Si la opción es "1".
            if opcion == "1":
                # Imprime el mensaje para el listado de inventario.
                print("Listado de Inventario")
            # Si la opción es "2".
            elif opcion == "2":
                # Imprime el mensaje para agregar un producto al inventario.
                print("Agregar Inventario")
            # Si la opción es "3".
            elif opcion == "3":
                # Imprime el mensaje de salida del menú de inventarios.
                print("Salida de Inventarios")
            # Si la opción es válida pero no corresponde a ninguna acción definida.
            else:
                # Informa al usuario que la opción no existe.
                print("No existe esta opción")

# --- PROCEDIMIENTO ---
# Es el punto de entrada que controla la navegación principal del programa.
def MenuPrincipal():
    # Se define una lista con las opciones del menú principal.
    datosmenuprincipal = ["1.-Productos", "2.-Punto de Venta", "3.- Inventarios", "5.- Salida"]
    # Se inicializa la variable 'opcion' para asegurar que el bucle comience.
    opcion = "0"
    # Bucle principal que se ejecuta mientras la opción no sea "5" (Salida).
    while opcion != "5":
        # Muestra el menú principal y obtiene la selección del usuario.
        opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes", datosmenuprincipal)
        # Verifica si la opción ingresada no es una de las opciones válidas.
        if opcion not in ["1", "2", "3", "5"]:
            # Informa al usuario que la opción es incorrecta.
            print("Opción incorrecta")
        # Si la opción es válida, se procesa.
        else:
            # Si la opción es "1".
            if opcion == "1":
                # Llama al procedimiento MenuProductos para manejar las opciones de productos.
                MenuProductos()
            # Si la opción es "2".
            elif opcion == "2":
                # Llama al procedimiento MenuPuntoVenta, pasándole "000" como id de ticket inicial.
                MenuPuntoVenta("000")
            # Si la opción es "3".
            elif opcion == "3":
                # Llama al procedimiento MenuInventario para gestionar el inventario.
                MenuInventario()
            # Si la opción es "5".
            elif opcion == "5":
                # Imprime el mensaje final de salida del sistema.
                print("Salida del Sistema")

# Esta construcción estándar en Python verifica si el script se está ejecutando directamente.
if __name__ == "__main__":
    # Llama a MenuPrincipal() para iniciar la aplicación.
    MenuPrincipal()