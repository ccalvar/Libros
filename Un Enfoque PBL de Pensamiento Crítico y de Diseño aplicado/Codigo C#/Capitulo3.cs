using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibroFundamentos.Capitulo3
{
    internal class Capitulo3
    {
        // TIPO: Función
        // REALIZA: Construye una sola cadena de texto a partir de un arreglo de opciones, añadiendo un salto de línea después de cada una.
        // PARÁMETROS:
        //   - string[] opciones: Un arreglo de cadenas, donde cada elemento es una opción del menú.
        // REGRESA: Una cadena (string) con todas las opciones concatenadas y separadas por saltos de línea.
        public static string MostrarMenu(string[] opciones)
        {
            // Inicializa una cadena vacía para acumular el resultado.
            string cadena = "";
            // Inicia un bucle 'foreach' que recorre cada elemento del arreglo 'opciones'.
            foreach (string info in opciones)
            {
                // Concatena la opción actual y un salto de línea a la cadena principal.
                cadena += info + "\n";
            }
            // Devuelve la cadena final con el menú completo.
            return cadena;
        }

        // TIPO: Función
        // REALIZA: Verifica si una cadena de texto contiene únicamente dígitos numéricos.
        // PARÁMETROS:
        //   - string dato: La cadena que se va a evaluar.
        // REGRESA: Un booleano. 'true' si todos los caracteres son dígitos, 'false' en caso contrario.
        public static bool EsNumeroEntero(string dato)
        {
            // Recorre cada carácter 'c' dentro de la cadena 'dato'.
            foreach (char c in dato)
            {
                // Comprueba si el carácter actual NO es un dígito.
                if (!char.IsDigit(c))
                {
                    // Si encuentra un carácter que no es un dígito, retorna 'false' inmediatamente.
                    return false;
                }
            }
            // Si el bucle termina, significa que todos los caracteres eran dígitos, por lo que retorna 'true'.
            return true;
        }

        // TIPO: Función
        // REALIZA: Verifica si una cadena de texto representa un número de tipo double (permite un único punto decimal).
        // PARÁMETROS:
        //   - string dato: La cadena a evaluar.
        // REGRESA: Un booleano. 'true' si la cadena es un número double válido (con punto decimal), 'false' si no lo es.
        public static bool EsNumeroDouble(string dato)
        {
            // Inicializa una bandera para rastrear si ya se ha encontrado un punto decimal.
            bool valido = false;
            // Recorre cada carácter 'c' en la cadena 'dato'.
            foreach (char c in dato)
            {
                // Verifica si el carácter actual NO es un dígito.
                if (!char.IsDigit(c))
                {
                    // Si no es un dígito, comprueba si es un punto y si aún no se ha encontrado otro punto.
                    if (c == '.' && !valido)
                    {
                        // Si es el primer punto, actualiza la bandera a 'true'.
                        valido = true;
                    }
                    else
                    {
                        // Si es otro carácter no numérico o si ya había un punto, la cadena no es válida. Retorna 'false'.
                        return false;
                    }
                }
            }
            // Retorna 'true' solo si se encontró un punto decimal y el resto eran dígitos.
            return valido;
        }

        // TIPO: Función
        // REALIZA: Evalúa si una cadena es de un tipo numérico específico (entero o double).
        // PARÁMETROS:
        //   - string dato: La cadena a evaluar.
        //   - int tipo: Un entero que especifica el tipo de validación (1 para entero, 2 para double).
        // REGRESA: Un booleano que indica si la validación fue exitosa.
        public static bool EvaluarNumerico(string dato, int tipo)
        {
            // Declara una variable booleana para almacenar el resultado, inicializada en falso.
            bool valido = false;
            // Inicia una estructura switch para seleccionar la validación según el 'tipo'.
            switch (tipo)
            {
                // Si el tipo es 1,
                case 1:
                    // llama a EsNumeroEntero y guarda el resultado en 'valido'.
                    valido = EsNumeroEntero(dato);
                    // Termina el caso.
                    break;
                // Si el tipo es 2,
                case 2:
                    // llama a EsNumeroDouble y guarda el resultado en 'valido'.
                    valido = EsNumeroDouble(dato);
                    // Termina el caso.
                    break;
            }
            // Devuelve el resultado de la validación.
            return valido;
        }

        // TIPO: Función
        // REALIZA: Muestra un texto en la consola y lee una línea completa de entrada del usuario.
        // PARÁMETROS:
        //   - string texto: Una cadena de texto que se mostrará como un mensaje o pregunta al usuario.
        // REGRESA: La cadena de texto (string) que el usuario introdujo.
        public static string Dialogo(string texto)
        {
            // Muestra el texto del parámetro seguido de dos puntos y un espacio, sin agregar un salto de línea al final.
            Console.Write(texto + " : ");
            // Lee la línea completa de la entrada estándar (teclado) y la devuelve.
            return Console.ReadLine();
        }

        // TIPO: Función
        // REALIZA: Pide un dato al usuario, lo lee y elimina los espacios en blanco al principio y al final.
        // PARÁMETROS:
        //   - string texto: El mensaje que se le mostrará al usuario para pedirle el dato.
        // REGRESA: La cadena (string) introducida por el usuario, sin espacios. Si la entrada está vacía, regresa 'null'.
        public static string Leer(string texto)
        {
            // Declara una cadena vacía para almacenar el resultado.
            string cadena = "";
            // Llama a la función Dialogo para mostrar el texto y leer la entrada del usuario.
            cadena = Dialogo(texto);
            // Verifica si la cadena leída no es nula ni está vacía.
            if (!string.IsNullOrEmpty(cadena))
            {
                // Elimina los espacios en blanco al principio y al final de la cadena.
                cadena = cadena.Trim();
                // Si después de quitar los espacios la cadena queda vacía,
                if (string.IsNullOrEmpty(cadena))
                    // se le asigna el valor 'null'.
                    cadena = null;
            }
            // Devuelve la cadena ya procesada.
            return cadena;
        }

        // TIPO: Función
        // REALIZA: Muestra un título, un menú de opciones y solicita al usuario que elija una.
        // PARÁMETROS:
        //   - string Titulo1: Una cadena con el título del menú.
        //   - string[] menu: Un arreglo con las opciones del menú.
        // REGRESA: La cadena (string) con la opción que el usuario introdujo.
        public static string DesplegarMenu(string Titulo1, string[] menu)
        {
            // Construye la cadena completa del menú (título + opciones + pregunta).
            string cadena = Titulo1 + "\n\n" + MostrarMenu(menu) + "\nQue opcion deseas ";
            // Llama a Dialogo para mostrar el menú y leer la respuesta del usuario.
            return Dialogo(cadena);
        }

        // TIPO: Función
        // REALIZA: Rellena una cadena con espacios a la izquierda hasta que alcance un tamaño específico.
        // PARÁMETROS:
        //   - string dato: La cadena original que se va a rellenar.
        //   - int tamano: El tamaño total que debe tener la cadena final.
        // REGRESA: Una nueva cadena (string) con los espacios añadidos a la izquierda.
        public static string RellenarEspacios(string dato, int tamano)
        {
            // Utiliza el método incorporado de C# 'PadLeft' para añadir espacios a la izquierda.
            return dato.PadLeft(tamano);
        }

        // TIPO: Función
        // REALIZA: Obtiene la fecha actual del sistema y la formatea como "dd-MM-yyyy".
        // PARÁMETROS: Ninguno.
        // REGRESA: Una cadena (string) con la fecha formateada.
        public static string Fecha()
        {
            // Obtiene la fecha y hora actuales del sistema.
            DateTime fecha = DateTime.Now;
            // Convierte la fecha a una cadena con el formato especificado.
            return fecha.ToString("dd-MM-yyyy");
        }

        // TIPO: Función
        // REALIZA: Toma un ID de ticket como cadena, lo incrementa en 1 y lo formatea con ceros a la izquierda para mantener una longitud de 3 dígitos.
        // PARÁMETROS:
        //   - string idTicket: El ID actual del ticket en formato de cadena.
        // REGRESA: El siguiente ID como una cadena (string) formateada.
        public static string IdTicketSiguiente(string idTicket)
        {
            // Declara una cadena para el siguiente ID.
            string idTicketNext = "";
            // Convierte la cadena 'idTicket' a entero, le suma 1 y lo guarda en 'num'.
            int num = int.Parse(idTicket) + 1;

            // Si el nuevo número es menor que 10 (un solo dígito),
            if (num < 10)
            {
                // le añade dos ceros a la izquierda.
                idTicketNext = "00" + num.ToString().Trim();
            }
            // Si el nuevo número está entre 10 y 99 (dos dígitos),
            else if (num > 9 && num < 100)
            {
                // le añade un cero a la izquierda.
                idTicketNext = "0" + num.ToString().Trim();
            }
            // Si el número tiene 3 o más dígitos,
            else
            {
                // simplemente lo convierte a cadena.
                idTicketNext = num.ToString().Trim();
            }
            // Devuelve el nuevo ID formateado.
            return idTicketNext;
        }
    }

}
