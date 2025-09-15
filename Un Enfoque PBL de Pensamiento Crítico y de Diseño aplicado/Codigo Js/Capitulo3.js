/**
 * Tipo: Función
 * Parámetros:
 * - opciones: Es un arreglo (Array) de cadenas de texto (string). Cada cadena es una opción del menú.
 * Propósito: Construir y devolver una única cadena de texto que contiene todas las opciones del menú,
 * cada una en una nueva línea.
 * Devuelve: Una cadena de texto (string) con el menú formateado.
 */
function MostrarMenu(opciones) {
    // Inicializa una cadena vacía para almacenar el menú.
    let cadena = "";
    // Itera sobre cada elemento (info) del arreglo 'opciones'.
    for (let info of opciones) {
        // Concatena cada opción a la cadena principal, seguida de un salto de línea.
        cadena += info + "\n";
    }
    // Retorna la cadena completa con todas las opciones.
    return cadena;
}

/**
 * Tipo: Función
 * Parámetros:
 * - dato: Una cadena de texto (string) que se desea validar.
 * Propósito: Verificar si todos los caracteres de la cadena de entrada son dígitos numéricos.
 * Devuelve: Un valor booleano (boolean). Retorna 'true' si la cadena contiene solo números enteros,
 * de lo contrario, retorna 'false'.
 */
function EsNumeroEntero(dato) {
    // Itera sobre cada carácter (c) de la cadena 'dato'.
    for (let c of dato) {
        // Comprueba si el carácter actual NO es un dígito usando una expresión regular.
        if (! /\d/.test(c)) {
            // Si encuentra un carácter que no es un dígito, retorna 'false' inmediatamente.
            return false;
        }
    }
    // Si el bucle termina sin encontrar caracteres no numéricos, retorna 'true'.
    return true;
}


/**
 * Tipo: Función
 * Parámetros:
 * - dato: Una cadena de texto (string) que se desea validar.
 * Propósito: Comprobar si la cadena de entrada corresponde a un número decimal (de punto flotante),
 * permitiendo un único punto como separador decimal.
 * Devuelve: Un valor booleano (boolean). Retorna 'true' si la cadena es un número decimal válido
 * (contiene al menos un punto), de lo contrario, retorna 'false'.
 */
function EsNumeroDouble(dato) {
    // Inicializa una bandera para controlar si ya se encontró un punto decimal.
    let valido = false;
    // Itera sobre cada carácter (c) de la cadena 'dato'.
    for (let c of dato) {
        // Si el carácter no es un dígito...
        if (!/\d/.test(c)) {
            // ...comprueba si es un punto y si aún no se ha encontrado otro punto.
            if (c === '.' && !valido) {
                // Si es el primer punto, marca la bandera como 'true'.
                valido = true;
            } else {
                // Si es otro carácter o un segundo punto, la cadena no es válida.
                return false;
            }
        }
    }
    // Retorna 'true' solo si se encontró exactamente un punto decimal entre los dígitos.
    return valido;
}

/**
 * Tipo: Función
 * Parámetros:
 * - dato: La cadena de texto (string) a evaluar.
 * - tipo: Un número entero (number) que especifica el tipo de validación.
 * 1 para validar como número entero, 2 para validar como número decimal (double).
 * Propósito: Evaluar si una cadena es de un tipo numérico específico (entero o double)
 * utilizando las funciones correspondientes.
 * Devuelve: Un valor booleano (boolean) que indica el resultado de la validación.
 */
function EvaluarNumerico(dato, tipo) {
    let valido = false;
    // Evalúa el parámetro 'tipo' para decidir qué validación realizar.
    switch (tipo) {
        case 1:
            // Si tipo es 1, llama a la función para validar enteros.
            valido = esNumeroEntero(dato);
            break;
        case 2:
            // Si tipo es 2, llama a la función para validar decimales.
            valido = esNumeroDouble(dato);
            break;
    }
    // Retorna el resultado de la validación.
    return valido;
}

/**
 * Tipo: Función asíncrona
 * Parámetros:
 * - texto: La cadena de texto (string) que se mostrará al usuario como una pregunta en la consola.
 * Propósito: Mostrar un mensaje en la consola y esperar a que el usuario introduzca una respuesta
 * y presione Enter.
 * Devuelve: Una Promesa (Promise) que se resuelve con la cadena de texto (string) ingresada por el usuario.
 */
async function Dialogo(texto) {
    // Crea una interfaz de línea de comandos para leer la entrada y mostrar la salida en la terminal.
    const readline = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });

    // Retorna una nueva Promesa que encapsula la operación de lectura.
    return new Promise(resolve => {
        // Muestra el 'texto' al usuario y espera su respuesta (ans).
        readline.question(texto, ans => {
            // Cierra la interfaz de lectura una vez que se obtiene la respuesta.
            readline.close();
            // Resuelve la promesa, devolviendo la respuesta del usuario.
            resolve(ans);
        });
    });
}

/**
 * Tipo: Función asíncrona
 * Parámetros:
 * - texto: La cadena de texto (string) que se mostrará al usuario para solicitarle datos.
 * Propósito: Leer una entrada del usuario, quitarle los espacios en blanco al inicio y al final,
 * y verificar que no esté vacía.
 * Devuelve: Una Promesa (Promise) que se resuelve con la cadena (string) ingresada y procesada,
 * o con 'null' si la cadena resultante está vacía.
 */
async function Leer(texto) {
    // Espera a que la función Dialogo resuelva la entrada del usuario.
    let cadena = await dialogo(texto);
    // Verifica que la cadena no sea nula.
    if (cadena !== null) {
        // Elimina los espacios en blanco al principio y al final de la cadena.
        cadena = cadena.trim();
        // Comprueba si la cadena quedó vacía después de limpiarla.
        if (cadena.isEmpty()) {
            // Si está vacía, la establece como null.
            cadena = null;
        }
    }
    // Retorna la cadena procesada o null.
    return cadena;
}

/**
 * Tipo: Función asíncrona
 * Parámetros:
 * - titulo: Cadena de texto (string) que se mostrará como encabezado del menú.
 * - menu: Un arreglo (Array) con las opciones del menú.
 * Propósito: Mostrar un menú completo con título y opciones, y solicitar al usuario que elija una.
 * Devuelve: Una Promesa (Promise) que se resuelve con la cadena de texto (string) que representa
 * la opción seleccionada por el usuario.
 */
async function DesplegarMenu(titulo, menu) {
    // Construye la cabecera del menú.
    let cadena = titulo + "\n\n";
    // Agrega las opciones del menú formateadas por la función mostrarMenu.
    cadena += mostrarMenu(menu);
    // Añade la pregunta final para el usuario.
    cadena += "\n Que opcion deseas";
    // Muestra todo el texto y espera la respuesta del usuario.
    return await dialogo(cadena);
}

/**
 * Tipo: Función
 * Parámetros:
 * - dato: La cadena de texto (string) original.
 * - tamano: Un número entero (number) que indica la longitud final deseada de la cadena.
 * Propósito: Asegurar que una cadena tenga una longitud mínima, añadiendo espacios al final si es necesario.
 * Devuelve: Una nueva cadena de texto (string) con la longitud especificada.
 */
function RellenaEspacios(dato, tamano) {
    // Utiliza el método padEnd para rellenar la cadena con espacios al final hasta alcanzar el 'tamano'.
    return dato.padEnd(tamano);
}

/**
 * Tipo: Función
 * Parámetros: Ninguno.
 * Propósito: Obtener la fecha actual del sistema y formatearla.
 * Devuelve: Una cadena de texto (string) que representa la fecha actual en formato dd/mm/yyyy.
 */
function Fecha() {
    // Crea un objeto Date que representa la fecha y hora actual.
    const date = new Date();

    // Convierte la fecha a una cadena con formato local 'día/mes/año'.
    return date.toLocaleDateString('en-GB');
}

/**
 * Tipo: Función
 * Parámetros:
 * - idticket: Una cadena de texto (string) que representa el número del ticket actual (ej: "009").
 * Propósito: Calcular el siguiente número de ticket consecutivo, manteniendo un formato de 3 dígitos
 * con ceros a la izquierda.
 * Devuelve: Una cadena de texto (string) con el nuevo ID del ticket (ej: "010").
 */
function IdTicketSiguiente(idticket) {
    // Convierte la cadena del ID a número entero y le suma 1.
    let num = parseInt(idticket) + 1;
    // Inicializa la cadena para el nuevo ID.
    let idticketnext = "";
    // Si el número es menor que 10, añade dos ceros a la izquierda.
    if (num < 10) {
        idticketnext = "00" + num.toString().trim();
        // Si el número es mayor que 9 y menor que 100, añade un cero a la izquierda.
    } else if (num > 9 && num < 100) {
        idticketnext = "0" + num.toString().trim();
    }
    // Si es 100 o más, no añade ceros.
    else {
        idticketnext = num.toString().trim();
    }
    // Devuelve el nuevo ID formateado como cadena.
    return idticketnext;
}