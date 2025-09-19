# Importa la clase 'datetime' del m�dulo 'datetime' para poder trabajar con fechas y horas.
from datetime import datetime

# --- Funciones de Utilidad para Men�s y Entradas de Usuario ---

"""
Tipo: Funci�n
Par�metros:
- opciones: Una lista o tupla de cadenas de texto (string).
Prop�sito: Construir una �nica cadena de texto que contiene todas las opciones del men�,
           cada una en una nueva l�nea para una visualizaci�n clara.
Devuelve: Una cadena de texto (string) con el men� formateado.
"""
def MostrarMenu(opciones):
    cadena = ""
    # Itera sobre cada elemento (info) en la lista de opciones.
    for info in opciones:
        # Concatena cada opci�n a la cadena principal, seguida de un salto de l�nea.
        cadena += info + "\n"
    return cadena

"""
Tipo: Funci�n
Par�metros:
- dato: La cadena de texto (string) que se va a validar.
Prop�sito: Verificar si una cadena de texto contiene �nicamente d�gitos num�ricos.
Devuelve: Un booleano (bool); True si es un n�mero entero, False en caso contrario.
"""
def EsnumeroEntero(dato):
    # El m�todo isdigit() de las cadenas devuelve True si todos los caracteres son d�gitos.
    return dato.isdigit()

"""
Tipo: Funci�n
Par�metros:
- dato: La cadena de texto (string) que se va a validar.
Prop�sito: Verificar si una cadena representa un n�mero de punto flotante (decimal) v�lido.
Devuelve: Un booleano (bool); True si es un n�mero decimal v�lido, False en caso contrario.
"""
def EsNumeroDouble(dato):
    valido = False # Bandera para controlar que solo haya un punto decimal.
    # Itera sobre cada car�cter (c) de la cadena de entrada.
    for c in dato:
        # Si el car�cter no es un d�gito...
        if not c.isdigit():
            # ...comprueba si es un punto y si a�n no hemos encontrado otro.
            if c == '.' and not valido:
                # Si es el primer punto, se marca como v�lido y se contin�a.
                valido = True
            else:
                # Si es otro car�cter o un segundo punto, la cadena no es v�lida.
                return False
    # La funci�n devuelve True solo si se encontr� al menos un punto decimal.
    return valido

"""
Tipo: Funci�n
Par�metros:
- dato: La cadena de texto (string) a evaluar.
- tipo: Un n�mero entero (int) que indica el tipo de validaci�n (1 para entero, 2 para double).
Prop�sito: Servir como un selector para llamar a la funci�n de validaci�n num�rica correcta.
Devuelve: El resultado booleano (bool) de la funci�n de validaci�n correspondiente.
"""
def EvaluarNumerico(dato, tipo):
    if tipo == 1:
        return EsnumeroEntero(dato)
    elif tipo == 2:
        return EsNumeroDouble(dato)
    return False

"""
Tipo: Funci�n
Par�metros:
- texto: El mensaje o pregunta que se le mostrar� al usuario.
Prop�sito: Mostrar un mensaje en la consola y capturar la entrada del usuario.
           Es una envoltura simple para la funci�n input() de Python.
Devuelve: La cadena de texto (string) que el usuario introdujo.
"""
def Dialogo(texto):
    return input(texto + " : ")

"""
Tipo: Funci�n
Par�metros:
- texto: El mensaje que se mostrar� para solicitar la entrada.
Prop�sito: Obtener una entrada limpia del usuario, eliminando espacios en blanco
           al inicio y al final.
Devuelve: La cadena de texto (string) limpia, o None si la cadena queda vac�a.
"""
def Leer(texto):
    cadena = Dialogo(texto)
    # Si el usuario introdujo algo...
    if cadena:
        # ...elimina los espacios en blanco de los extremos.
        cadena = cadena.strip()
        # Si despu�s de limpiar la cadena queda vac�a, se considera nula.
        if not cadena:
            cadena = None
    return cadena

"""
Tipo: Funci�n
Par�metros:
- titulo: El t�tulo que se mostrar� encima del men�.
- menu: La lista de opciones del men�.
Prop�sito: Construir y mostrar un men� completo con t�tulo y opciones, y luego
           solicitar al usuario que elija una.
Devuelve: La cadena de texto (string) con la opci�n que el usuario seleccion�.
"""
def DesplegarMenu(titulo, menu):
    cadena = titulo + "\n\n"
    cadena += MostrarMenu(menu)
    cadena += "\n Que opcion deseas"
    return Dialogo(cadena)

"""
Tipo: Funci�n
Par�metros:
- dato: La cadena de texto (string) original.
- tamano: La longitud total deseada para la cadena.
Prop�sito: Rellenar una cadena con espacios al final hasta que alcance un tama�o espec�fico.
           �til para formatear texto en columnas.
Devuelve: La cadena de texto (string) formateada.
"""
def RellenaEspacios(dato, tamano):
    # ljust() justifica la cadena a la izquierda, rellenando con espacios a la derecha.
    return dato.ljust(tamano)

# --- Funciones Espec�ficas de la L�gica de Negocio ---

"""
Tipo: Funci�n
Par�metros: Ninguno.
Prop�sito: Obtener la fecha actual del sistema y formatearla.
Devuelve: Una cadena de texto (string) con la fecha en formato "dd-mm-YYYY".
"""
def Fecha():
    # datetime.now() obtiene la fecha y hora actual.
    # strftime() formatea la fecha seg�n el c�digo proporcionado (%d=d�a, %m=mes, %Y=a�o).
    return datetime.now().strftime("%d-%m-%Y")

"""
Tipo: Funci�n
Par�metros:
- idticket: El ID del ticket actual como una cadena de texto (ej: "001").
Prop�sito: Calcular el siguiente n�mero de ticket, manteniendo el formato de 3 d�gitos
           con ceros a la izquierda.
Devuelve: Una cadena de texto (string) con el siguiente ID de ticket.
"""
def IdTicketSiguiente(idticket):
    # Convierte la cadena a entero y le suma 1.
    num = int(idticket) + 1
    # Eval�a el rango del nuevo n�mero para aplicar el formato correcto.
    if num < 10:
        # Si es menor que 10, a�ade dos ceros al principio.
        return "00" + str(num).strip()
    elif num < 100:
        # Si es menor que 100, a�ade un cero al principio.
        return "0" + str(num).strip()
    else:
        # Si es 100 o m�s, no necesita ceros adicionales.
        return str(num).strip()