/**
 * Tipo: Funci�n
 * Par�metros:
 * - opciones: Es un arreglo (Array) de cadenas de texto (string). Cada cadena es una opci�n del men�.
 * Prop�sito: Construir y devolver una �nica cadena de texto que contiene todas las opciones del men�,
 * cada una en una nueva l�nea.
 * Devuelve: Una cadena de texto (string) con el men� formateado.
 */
function MostrarMenu(opciones) {
    // Inicializa una cadena vac�a para almacenar el men�.
    let cadena = "";
    // Itera sobre cada elemento (info) del arreglo 'opciones'.
    for (let info of opciones) {
        // Concatena cada opci�n a la cadena principal, seguida de un salto de l�nea.
        cadena += info + "\n";
    }
    // Retorna la cadena completa con todas las opciones.
    return cadena;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - dato: Una cadena de texto (string) que se desea validar.
 * Prop�sito: Verificar si todos los caracteres de la cadena de entrada son d�gitos num�ricos.
 * Devuelve: Un valor booleano (boolean). Retorna 'true' si la cadena contiene solo n�meros enteros,
 * de lo contrario, retorna 'false'.
 */
function EsNumeroEntero(dato) {
    // Itera sobre cada car�cter (c) de la cadena 'dato'.
    for (let c of dato) {
        // Comprueba si el car�cter actual NO es un d�gito usando una expresi�n regular.
        if (! /\d/.test(c)) {
            // Si encuentra un car�cter que no es un d�gito, retorna 'false' inmediatamente.
            return false;
        }
    }
    // Si el bucle termina sin encontrar caracteres no num�ricos, retorna 'true'.
    return true;
}


/**
 * Tipo: Funci�n
 * Par�metros:
 * - dato: Una cadena de texto (string) que se desea validar.
 * Prop�sito: Comprobar si la cadena de entrada corresponde a un n�mero decimal (de punto flotante),
 * permitiendo un �nico punto como separador decimal.
 * Devuelve: Un valor booleano (boolean). Retorna 'true' si la cadena es un n�mero decimal v�lido
 * (contiene al menos un punto), de lo contrario, retorna 'false'.
 */
function EsNumeroDouble(dato) {
    // Inicializa una bandera para controlar si ya se encontr� un punto decimal.
    let valido = false;
    // Itera sobre cada car�cter (c) de la cadena 'dato'.
    for (let c of dato) {
        // Si el car�cter no es un d�gito...
        if (!/\d/.test(c)) {
            // ...comprueba si es un punto y si a�n no se ha encontrado otro punto.
            if (c === '.' && !valido) {
                // Si es el primer punto, marca la bandera como 'true'.
                valido = true;
            } else {
                // Si es otro car�cter o un segundo punto, la cadena no es v�lida.
                return false;
            }
        }
    }
    // Retorna 'true' solo si se encontr� exactamente un punto decimal entre los d�gitos.
    return valido;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - dato: La cadena de texto (string) a evaluar.
 * - tipo: Un n�mero entero (number) que especifica el tipo de validaci�n.
 * 1 para validar como n�mero entero, 2 para validar como n�mero decimal (double).
 * Prop�sito: Evaluar si una cadena es de un tipo num�rico espec�fico (entero o double)
 * utilizando las funciones correspondientes.
 * Devuelve: Un valor booleano (boolean) que indica el resultado de la validaci�n.
 */
function EvaluarNumerico(dato, tipo) {
    let valido = false;
    // Eval�a el par�metro 'tipo' para decidir qu� validaci�n realizar.
    switch (tipo) {
        case 1:
            // Si tipo es 1, llama a la funci�n para validar enteros.
            valido = esNumeroEntero(dato);
            break;
        case 2:
            // Si tipo es 2, llama a la funci�n para validar decimales.
            valido = esNumeroDouble(dato);
            break;
    }
    // Retorna el resultado de la validaci�n.
    return valido;
}

/**
 * Tipo: Funci�n as�ncrona
 * Par�metros:
 * - texto: La cadena de texto (string) que se mostrar� al usuario como una pregunta en la consola.
 * Prop�sito: Mostrar un mensaje en la consola y esperar a que el usuario introduzca una respuesta
 * y presione Enter.
 * Devuelve: Una Promesa (Promise) que se resuelve con la cadena de texto (string) ingresada por el usuario.
 */
async function Dialogo(texto) {
    // Crea una interfaz de l�nea de comandos para leer la entrada y mostrar la salida en la terminal.
    const readline = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });

    // Retorna una nueva Promesa que encapsula la operaci�n de lectura.
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
 * Tipo: Funci�n as�ncrona
 * Par�metros:
 * - texto: La cadena de texto (string) que se mostrar� al usuario para solicitarle datos.
 * Prop�sito: Leer una entrada del usuario, quitarle los espacios en blanco al inicio y al final,
 * y verificar que no est� vac�a.
 * Devuelve: Una Promesa (Promise) que se resuelve con la cadena (string) ingresada y procesada,
 * o con 'null' si la cadena resultante est� vac�a.
 */
async function Leer(texto) {
    // Espera a que la funci�n Dialogo resuelva la entrada del usuario.
    let cadena = await dialogo(texto);
    // Verifica que la cadena no sea nula.
    if (cadena !== null) {
        // Elimina los espacios en blanco al principio y al final de la cadena.
        cadena = cadena.trim();
        // Comprueba si la cadena qued� vac�a despu�s de limpiarla.
        if (cadena.isEmpty()) {
            // Si est� vac�a, la establece como null.
            cadena = null;
        }
    }
    // Retorna la cadena procesada o null.
    return cadena;
}

/**
 * Tipo: Funci�n as�ncrona
 * Par�metros:
 * - titulo: Cadena de texto (string) que se mostrar� como encabezado del men�.
 * - menu: Un arreglo (Array) con las opciones del men�.
 * Prop�sito: Mostrar un men� completo con t�tulo y opciones, y solicitar al usuario que elija una.
 * Devuelve: Una Promesa (Promise) que se resuelve con la cadena de texto (string) que representa
 * la opci�n seleccionada por el usuario.
 */
async function DesplegarMenu(titulo, menu) {
    // Construye la cabecera del men�.
    let cadena = titulo + "\n\n";
    // Agrega las opciones del men� formateadas por la funci�n mostrarMenu.
    cadena += mostrarMenu(menu);
    // A�ade la pregunta final para el usuario.
    cadena += "\n Que opcion deseas";
    // Muestra todo el texto y espera la respuesta del usuario.
    return await dialogo(cadena);
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - dato: La cadena de texto (string) original.
 * - tamano: Un n�mero entero (number) que indica la longitud final deseada de la cadena.
 * Prop�sito: Asegurar que una cadena tenga una longitud m�nima, a�adiendo espacios al final si es necesario.
 * Devuelve: Una nueva cadena de texto (string) con la longitud especificada.
 */
function RellenaEspacios(dato, tamano) {
    // Utiliza el m�todo padEnd para rellenar la cadena con espacios al final hasta alcanzar el 'tamano'.
    return dato.padEnd(tamano);
}

/**
 * Tipo: Funci�n
 * Par�metros: Ninguno.
 * Prop�sito: Obtener la fecha actual del sistema y formatearla.
 * Devuelve: Una cadena de texto (string) que representa la fecha actual en formato dd/mm/yyyy.
 */
function Fecha() {
    // Crea un objeto Date que representa la fecha y hora actual.
    const date = new Date();

    // Convierte la fecha a una cadena con formato local 'd�a/mes/a�o'.
    return date.toLocaleDateString('en-GB');
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - idticket: Una cadena de texto (string) que representa el n�mero del ticket actual (ej: "009").
 * Prop�sito: Calcular el siguiente n�mero de ticket consecutivo, manteniendo un formato de 3 d�gitos
 * con ceros a la izquierda.
 * Devuelve: Una cadena de texto (string) con el nuevo ID del ticket (ej: "010").
 */
function IdTicketSiguiente(idticket) {
    // Convierte la cadena del ID a n�mero entero y le suma 1.
    let num = parseInt(idticket) + 1;
    // Inicializa la cadena para el nuevo ID.
    let idticketnext = "";
    // Si el n�mero es menor que 10, a�ade dos ceros a la izquierda.
    if (num < 10) {
        idticketnext = "00" + num.toString().trim();
        // Si el n�mero es mayor que 9 y menor que 100, a�ade un cero a la izquierda.
    } else if (num > 9 && num < 100) {
        idticketnext = "0" + num.toString().trim();
    }
    // Si es 100 o m�s, no a�ade ceros.
    else {
        idticketnext = num.toString().trim();
    }
    // Devuelve el nuevo ID formateado como cadena.
    return idticketnext;
}