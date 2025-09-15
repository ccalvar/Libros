
# Importa la clase 'datetime' del m�dulo 'datetime' para poder trabajar con fechas y horas.
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
    # Se crea una lista con las opciones de texto que se mostrar�n en el men�.
    datosmenuproductos = ["1.-Modificar ", "2.-Listado ", "3.-Salida"]
    # Se inicializa la variable 'opcion' con "0" para asegurar que el bucle while se inicie.
    opcion = "0"
    # Se inicia un bucle que se repetir� mientras la opci�n elegida no sea "3" (Salida).
    while opcion != "3":
        # Llama a la funci�n 'DesplegarMenu' para mostrar las opciones y capturar la elecci�n del usuario.
        opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos)
        # Comprueba si la funci�n 'DesplegarMenu' no devolvi� un valor (posiblemente por una entrada inv�lida).
        if not opcion:
            # Informa al usuario que la opci�n es incorrecta.
            print("opci�n incorrecta ")
        # Si se recibi� una opci�n v�lida, se procesa.
        else:
            # Si el usuario eligi� la opci�n "1".
            if opcion == "1":
                # Imprime el mensaje para modificar el precio de un producto.
                print("Modificar Precio Producto")
            # Si el usuario eligi� la opci�n "2".
            elif opcion == "2":
                # Imprime el mensaje para mostrar el listado de productos.
                print("Listado Producto")
            # Si el usuario eligi� la opci�n "3".
            elif opcion == "3":
                # Imprime el mensaje de salida del submen�.
                print("Salida del Sistema")
            # Si la opci�n ingresada no es 1, 2 ni 3.
            else:
                # Informa al usuario que la opci�n no existe.
                print("No existe esta opci�n")

# --- PROCEDIMIENTO ---
# Gestiona las operaciones de una venta (agregar, eliminar, pagar).
# Par�metro:
#   idticket (string): Recibe el ID del �ltimo ticket para generar el siguiente.
def MenuPuntoVenta(idticket):
    # Se inicializa la variable 'opcion' como None.
    opcion = None
    # Se inicializa la variable 'membrete' como None.
    membrete = None
    # Se inicializa la variable 'pago' en False, indicando que el ticket a�n no se ha pagado.
    pago = False
    # Llama a la funci�n 'IdTicketSiguiente' para obtener el n�mero del nuevo ticket.
    idticket = IdTicketSiguiente(idticket)
    # Llama a la funci�n 'Fecha' para obtener la fecha actual.
    fechadia = Fecha()
    # Se construye el encabezado del men� con la fecha y el n�mero de ticket.
    membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket
    # Se a�ade una l�nea separadora al encabezado para mejorar la presentaci�n.
    membrete += "\n-------------------------------------------------------\n"
    # Se define una lista con las opciones del men� de punto de venta.
    datosmenu = ["1. - Agregar", "2. - Eliminar", "3. - Listado", "4. - Pagar", "5. - Salida"]
    # Bucle que se ejecuta mientras la opci�n no sea "5" (Salida).
    while opcion != "5":
        # Muestra el men� con el encabezado y las opciones, y captura la elecci�n del usuario.
        opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu)
        # Verifica si la opci�n ingresada no es una de las v�lidas.
        if opcion not in ["1", "2", "3", "4", "5"]:
            # Informa al usuario que la opci�n es incorrecta.
            print("Opci�n Incorrecta")
        # Si la opci�n es v�lida, se procesa.
        else:
            # Si la opci�n es "1".
            if opcion == "1":
                # Imprime el mensaje para agregar un art�culo.
                print("Agregar Art�culo al Ticket")
            # Si la opci�n es "2".
            elif opcion == "2":
                # Imprime el mensaje para eliminar un art�culo.
                print("Eliminar Art�culo del Ticket")
            # Si la opci�n es "3".
            elif opcion == "3":
                # Imprime el mensaje para listar los art�culos del ticket.
                print("Listado de Art�culos del Ticket")
            # Si la opci�n es "4".
            elif opcion == "4":
                # Imprime el mensaje para pagar el ticket.
                print("Pagar Ticket y salir")
                # Se fuerza la 'opcion' a "5" para que el bucle while termine.
                opcion = "5"
                # Se cambia el estado de 'pago' a True, indicando que el ticket se pag�.
                pago = True
            # Si la opci�n es "5".
            elif opcion == "5":
                # Imprime el mensaje de salida del men� de ventas.
                print("Salida del Ventas")
                # Verifica si el ticket no fue pagado.
                if not pago:
                    # Informa al usuario que el ticket no se pag�.
                    print("No pag� el ticket")
                    # Informa al usuario que el ticket actual ser� eliminado.
                    print(f"Eliminando ticket {idticket}")

# --- PROCEDIMIENTO ---
# Gestiona las opciones de inventario (listar, agregar).
def MenuInventario():
    # Se crea una lista con las opciones de texto para el men� de inventarios.
    datosmenuinventarios = ["1. - Listado", "2. - Agregar", "3. - Salida"]
    # Se inicializa la variable 'opcion' para asegurar el inicio del bucle.
    opcion = "0"
    # Bucle que se repite mientras la opci�n del usuario no sea "3".
    while opcion != "3":
        # Llama a la funci�n 'DesplegarMenu' para mostrar el men� y obtener la opci�n del usuario.
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventarios)
        # Verifica si la opci�n ingresada no es una de las v�lidas ("1", "2", "3").
        if opcion not in ["1", "2", "3"]:
            # Informa al usuario que la opci�n es incorrecta.
            print("Opci�n incorrecta")
        # Si la opci�n es v�lida, se procesa.
        else:
            # Si la opci�n es "1".
            if opcion == "1":
                # Imprime el mensaje para el listado de inventario.
                print("Listado de Inventario")
            # Si la opci�n es "2".
            elif opcion == "2":
                # Imprime el mensaje para agregar un producto al inventario.
                print("Agregar Inventario")
            # Si la opci�n es "3".
            elif opcion == "3":
                # Imprime el mensaje de salida del men� de inventarios.
                print("Salida de Inventarios")
            # Si la opci�n es v�lida pero no corresponde a ninguna acci�n definida.
            else:
                # Informa al usuario que la opci�n no existe.
                print("No existe esta opci�n")

# --- PROCEDIMIENTO ---
# Es el punto de entrada que controla la navegaci�n principal del programa.
def MenuPrincipal():
    # Se define una lista con las opciones del men� principal.
    datosmenuprincipal = ["1.-Productos", "2.-Punto de Venta", "3.- Inventarios", "5.- Salida"]
    # Se inicializa la variable 'opcion' para asegurar que el bucle comience.
    opcion = "0"
    # Bucle principal que se ejecuta mientras la opci�n no sea "5" (Salida).
    while opcion != "5":
        # Muestra el men� principal y obtiene la selecci�n del usuario.
        opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes", datosmenuprincipal)
        # Verifica si la opci�n ingresada no es una de las opciones v�lidas.
        if opcion not in ["1", "2", "3", "5"]:
            # Informa al usuario que la opci�n es incorrecta.
            print("Opci�n incorrecta")
        # Si la opci�n es v�lida, se procesa.
        else:
            # Si la opci�n es "1".
            if opcion == "1":
                # Llama al procedimiento MenuProductos para manejar las opciones de productos.
                MenuProductos()
            # Si la opci�n es "2".
            elif opcion == "2":
                # Llama al procedimiento MenuPuntoVenta, pas�ndole "000" como id de ticket inicial.
                MenuPuntoVenta("000")
            # Si la opci�n es "3".
            elif opcion == "3":
                # Llama al procedimiento MenuInventario para gestionar el inventario.
                MenuInventario()
            # Si la opci�n es "5".
            elif opcion == "5":
                # Imprime el mensaje final de salida del sistema.
                print("Salida del Sistema")

# Esta construcci�n est�ndar en Python verifica si el script se est� ejecutando directamente.
if __name__ == "__main__":
    # Llama a MenuPrincipal() para iniciar la aplicaci�n.
    MenuPrincipal()