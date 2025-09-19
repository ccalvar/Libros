# Importa la clase 'datetime' del módulo 'datetime' para poder trabajar con fechas y horas.
from datetime import datetime

# --- Funciones de Utilidad para Menús y Entradas de Usuario ---

"""
Tipo: Función
Parámetros:
- opciones: Una lista o tupla de cadenas de texto (string).
Propósito: Construir una única cadena de texto que contiene todas las opciones del menú,
           cada una en una nueva línea para una visualización clara.
Devuelve: Una cadena de texto (string) con el menú formateado.
"""
def MostrarMenu(opciones):
    cadena = ""
    # Itera sobre cada elemento (info) en la lista de opciones.
    for info in opciones:
        # Concatena cada opción a la cadena principal, seguida de un salto de línea.
        cadena += info + "\n"
    return cadena

"""
Tipo: Función
Parámetros:
- dato: La cadena de texto (string) que se va a validar.
Propósito: Verificar si una cadena de texto contiene únicamente dígitos numéricos.
Devuelve: Un booleano (bool); True si es un número entero, False en caso contrario.
"""
def EsnumeroEntero(dato):
    # El método isdigit() de las cadenas devuelve True si todos los caracteres son dígitos.
    return dato.isdigit()

"""
Tipo: Función
Parámetros:
- dato: La cadena de texto (string) que se va a validar.
Propósito: Verificar si una cadena representa un número de punto flotante (decimal) válido.
Devuelve: Un booleano (bool); True si es un número decimal válido, False en caso contrario.
"""
def EsNumeroDouble(dato):
    valido = False # Bandera para controlar que solo haya un punto decimal.
    # Itera sobre cada carácter (c) de la cadena de entrada.
    for c in dato:
        # Si el carácter no es un dígito...
        if not c.isdigit():
            # ...comprueba si es un punto y si aún no hemos encontrado otro.
            if c == '.' and not valido:
                # Si es el primer punto, se marca como válido y se continúa.
                valido = True
            else:
                # Si es otro carácter o un segundo punto, la cadena no es válida.
                return False
    # La función devuelve True solo si se encontró al menos un punto decimal.
    return valido

"""
Tipo: Función
Parámetros:
- dato: La cadena de texto (string) a evaluar.
- tipo: Un número entero (int) que indica el tipo de validación (1 para entero, 2 para double).
Propósito: Servir como un selector para llamar a la función de validación numérica correcta.
Devuelve: El resultado booleano (bool) de la función de validación correspondiente.
"""
def EvaluarNumerico(dato, tipo):
    if tipo == 1:
        return EsnumeroEntero(dato)
    elif tipo == 2:
        return EsNumeroDouble(dato)
    return False

"""
Tipo: Función
Parámetros:
- texto: El mensaje o pregunta que se le mostrará al usuario.
Propósito: Mostrar un mensaje en la consola y capturar la entrada del usuario.
           Es una envoltura simple para la función input() de Python.
Devuelve: La cadena de texto (string) que el usuario introdujo.
"""
def Dialogo(texto):
    return input(texto + " : ")

"""
Tipo: Función
Parámetros:
- texto: El mensaje que se mostrará para solicitar la entrada.
Propósito: Obtener una entrada limpia del usuario, eliminando espacios en blanco
           al inicio y al final.
Devuelve: La cadena de texto (string) limpia, o None si la cadena queda vacía.
"""
def Leer(texto):
    cadena = Dialogo(texto)
    # Si el usuario introdujo algo...
    if cadena:
        # ...elimina los espacios en blanco de los extremos.
        cadena = cadena.strip()
        # Si después de limpiar la cadena queda vacía, se considera nula.
        if not cadena:
            cadena = None
    return cadena

"""
Tipo: Función
Parámetros:
- titulo: El título que se mostrará encima del menú.
- menu: La lista de opciones del menú.
Propósito: Construir y mostrar un menú completo con título y opciones, y luego
           solicitar al usuario que elija una.
Devuelve: La cadena de texto (string) con la opción que el usuario seleccionó.
"""
def DesplegarMenu(titulo, menu):
    cadena = titulo + "\n\n"
    cadena += MostrarMenu(menu)
    cadena += "\n Que opcion deseas"
    return Dialogo(cadena)

"""
Tipo: Función
Parámetros:
- dato: La cadena de texto (string) original.
- tamano: La longitud total deseada para la cadena.
Propósito: Rellenar una cadena con espacios al final hasta que alcance un tamaño específico.
           Útil para formatear texto en columnas.
Devuelve: La cadena de texto (string) formateada.
"""
def RellenaEspacios(dato, tamano):
    # ljust() justifica la cadena a la izquierda, rellenando con espacios a la derecha.
    return dato.ljust(tamano)

# --- Funciones Específicas de la Lógica de Negocio ---

"""
Tipo: Función
Parámetros: Ninguno.
Propósito: Obtener la fecha actual del sistema y formatearla.
Devuelve: Una cadena de texto (string) con la fecha en formato "dd-mm-YYYY".
"""
def Fecha():
    # datetime.now() obtiene la fecha y hora actual.
    # strftime() formatea la fecha según el código proporcionado (%d=día, %m=mes, %Y=año).
    return datetime.now().strftime("%d-%m-%Y")

"""
Tipo: Función
Parámetros:
- idticket: El ID del ticket actual como una cadena de texto (ej: "001").
Propósito: Calcular el siguiente número de ticket, manteniendo el formato de 3 dígitos
           con ceros a la izquierda.
Devuelve: Una cadena de texto (string) con el siguiente ID de ticket.
"""
def IdTicketSiguiente(idticket):
    # Convierte la cadena a entero y le suma 1.
    num = int(idticket) + 1
    # Evalúa el rango del nuevo número para aplicar el formato correcto.
    if num < 10:
        # Si es menor que 10, añade dos ceros al principio.
        return "00" + str(num).strip()
    elif num < 100:
        # Si es menor que 100, añade un cero al principio.
        return "0" + str(num).strip()
    else:
        # Si es 100 o más, no necesita ceros adicionales.
        return str(num).strip()