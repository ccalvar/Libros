// Incluye la librería iostream para operaciones de entrada y salida, como std::cout y std::cin.
#include <iostream>
// Incluye la librería string para poder utilizar el tipo de dato std::string.
#include <string>
// Incluye la librería iomanip para manipuladores de formato de salida, como std::setw y std::left.
#include <iomanip>
// Incluye la librería sstream para usar std::stringstream, que permite construir cadenas de texto.
#include <sstream>
// Incluye la librería chrono para trabajar con fechas y horas.
#include <chrono>
// Incluye la librería vector para usar la estructura de datos std::vector (aunque no se usa en este código).
#include <vector>

// Usa el espacio de nombres estándar para no tener que escribir "std::" antes de cada elemento.
using namespace std;

// TIPO: Función
// REALIZA: Construye y formatea una cadena de texto que representa un menú de opciones.
// PARÁMETROS:
//   - const string opciones[]: Un arreglo de cadenas de texto, donde cada una es una opción del menú.
//   - int tamano: Un entero que indica el número de elementos en el arreglo 'opciones'.
// REGRESA: Una cadena (string) con todas las opciones numeradas y separadas por saltos de línea.
string MostrarMenu(const string opciones[], int tamano) {
    // Declara e inicializa una cadena vacía que acumulará el texto del menú.
    string cadena = "";
    // Declara e inicializa un contador 'i' en 0 para iterar sobre el arreglo.
    int i = 0;

    // Inicia un bucle que se ejecutará mientras 'i' sea menor que el tamaño del arreglo.
    while (i < tamano) {
        // Concatena a 'cadena' el número de la opción (i + 1), un punto, la opción del arreglo y un salto de línea.
        cadena += to_string(i + 1) + ". " + opciones[i] + "\n";
        // Incrementa el contador para pasar a la siguiente opción.
        i++;
    }
    // Devuelve la cadena final con el menú formateado.
    return cadena;
}


// TIPO: Función
// REALIZA: Muestra un texto en la consola y lee una línea completa de entrada del usuario.
// PARÁMETROS:
//   - const std::string& texto: Una cadena de texto que se mostrará como un mensaje o pregunta al usuario.
// REGRESA: La cadena de texto (string) que el usuario introdujo.
std::string Dialogo(const std::string& texto) {
    // Declara una cadena de texto vacía para almacenar la entrada del usuario.
    std::string cadena;
    // Muestra el texto del parámetro seguido de dos puntos y un espacio.
    std::cout << texto << " : ";
    // Lee la línea completa de la entrada estándar (teclado) y la guarda en 'cadena'.
    std::getline(std::cin, cadena);
    // Devuelve la cadena leída.
    return cadena;
}


// TIPO: Función
// REALIZA: Muestra un título, un menú de opciones y solicita al usuario que elija una.
// PARÁMETROS:
//   - const std::string& Titulo1: Una cadena con el título del menú.
//   - const std::string opciones[]: Un arreglo con las opciones del menú.
//   - int tamano: El número de elementos en el arreglo 'opciones'.
// REGRESA: La cadena (string) con la opción que el usuario introdujo.
std::string DesplegarMenu(const std::string& Titulo1, const std::string opciones[], int tamano) {
    // Crea una cadena inicial con el título y dos saltos de línea.
    std::string cadena = Titulo1 + "\n\n";
    // Llama a MostrarMenu para generar la lista de opciones y la añade a la cadena.
    cadena += MostrarMenu(opciones, tamano);
    // Añade la pregunta para el usuario a la cadena.
    cadena += "\n Que opcion deseas ";
    // Llama a Dialogo con la cadena completa para mostrar el menú y leer la respuesta del usuario.
    return Dialogo(cadena);
}


// TIPO: Función
// REALIZA: Pide un dato al usuario, lo lee y elimina los espacios en blanco al principio y al final.
// PARÁMETROS:
//   - const std::string& texto: El mensaje que se le mostrará al usuario para pedirle el dato.
// REGRESA: La cadena (string) introducida por el usuario, sin espacios iniciales ni finales. Si la entrada está vacía o solo contiene espacios, regresa una cadena vacía.
std::string Leer(const std::string& texto) {
    // Declara una cadena vacía para almacenar el resultado.
    std::string cadena = "";
    // Llama a la función Dialogo para mostrar el texto y leer la entrada del usuario.
    cadena = Dialogo(texto);
    // Verifica si la cadena leída no está vacía.
    if (!cadena.empty()) {
        // Busca la posición del primer carácter que no sea un espacio.
        size_t first = cadena.find_first_not_of(' ');
        // Si no se encuentra ningún carácter (la cadena solo tiene espacios),
        if (std::string::npos == first) {
            // la cadena resultante se establece como vacía.
            cadena = "";
        }
        else {
            // Busca la posición del último carácter que no sea un espacio.
            size_t last = cadena.find_last_not_of(' ');
            // Extrae la subcadena desde el primer hasta el último carácter no espacial.
            cadena = cadena.substr(first, (last - first + 1));
        }
    }
    // Devuelve la cadena ya procesada (sin espacios extra).
    return cadena;
}


// TIPO: Función
// REALIZA: Verifica si una cadena de texto contiene únicamente dígitos numéricos.
// PARÁMETROS:
//   - const string& dato: La cadena a evaluar.
// REGRESA: Un booleano. 'true' si todos los caracteres son dígitos, 'false' en caso contrario.
bool EsNumeroEntero(const string& dato) {
    // Itera sobre cada carácter 'c' en la cadena 'dato'.
    for (char c : dato) {
        // Comprueba si el carácter actual NO es un dígito usando la función isdigit().
        if (!isdigit(c)) {
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
//   - const std::string& dato: La cadena a evaluar.
// REGRESA: Un booleano. 'true' si la cadena es un número double válido (con punto decimal), 'false' si no lo es.
bool EsNumeroDouble(const std::string& dato) {
    // Inicializa una bandera booleana para rastrear si ya se ha encontrado un punto decimal.
    bool puntoEncontrado = false;
    // Itera sobre cada carácter 'c' de la cadena 'dato'.
    for (char c : dato) {
        // Verifica si el carácter actual NO es un dígito.
        if (!std::isdigit(c)) {
            // Si no es un dígito, comprueba si es un punto y si aún no se ha encontrado otro punto.
            if (c == '.' && !puntoEncontrado) {
                // Si es el primer punto, actualiza la bandera a 'true'.
                puntoEncontrado = true;
            }
            else {
                // Si es otro carácter no numérico o si ya había un punto, la cadena no es válida. Retorna 'false'.
                return false;
            }
        }
    }
    // Retorna el valor de 'puntoEncontrado'. Esto hace que la función solo devuelva 'true' si había exactamente un punto.
    return puntoEncontrado;
}


// TIPO: Función
// REALIZA: Evalúa si una cadena es de un tipo numérico específico (entero o double).
// PARÁMETROS:
//   - const std::string& dato: La cadena a evaluar.
//   - int tipo: Un entero que especifica el tipo de validación (1 para entero, 2 para double).
// REGRESA: Un booleano que indica si la validación fue exitosa.
bool EvaluarNumerico(const std::string& dato, int tipo) {
    // Declara una variable booleana para almacenar el resultado, inicializada en falso.
    bool valido = false;
    // Inicia una estructura switch para seleccionar la validación según el 'tipo'.
    switch (tipo) {
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
        // Si el tipo no es ni 1 ni 2, no hace nada.
    default:
        break;
    }
    // Devuelve el resultado de la validación.
    return valido;
}


// TIPO: Función
// REALIZA: Rellena una cadena con espacios a la derecha hasta que alcance un tamaño específico.
// PARÁMETROS:
//   - std::string dato: La cadena original que se va a rellenar.
//   - int tamano: El tamaño total que debe tener la cadena final.
// REGRESA: Una nueva cadena (string) con los espacios añadidos.
std::string Rellenarespacios(std::string dato, int tamano) {
    // Crea un objeto stringstream para facilitar la construcción de la cadena formateada.
    std::stringstream ss;
    // Usa manipuladores de flujo:
    // std::left: alinea el contenido a la izquierda.
    // std::setw(tamano): establece el ancho total del campo a 'tamano'.
    // Los espacios se añadirán a la derecha para rellenar el ancho.
    ss << std::left << std::setw(tamano) << dato;
    // Convierte el contenido del stringstream a una cadena y la devuelve.
    return ss.str();
}


// TIPO: Función
// REALIZA: Toma un ID de ticket como cadena, lo incrementa en 1 y lo formatea con ceros a la izquierda para mantener una longitud de 3 dígitos.
// PARÁMETROS:
//   - const std::string& idticket: El ID actual del ticket en formato de cadena.
// REGRESA: El siguiente ID como una cadena (string) formateada.
std::string IdTicketSiguiente(const std::string& idticket) {
    // Declara una cadena para el siguiente ID.
    std::string idticketnext = "";
    // Convierte la cadena 'idticket' a entero, le suma 1 y lo guarda en 'num'.
    int num = std::stoi(idticket) + 1;

    // Si el nuevo número es menor que 10 (un solo dígito),
    if (num < 10) {
        // usa un stringstream para formatearlo a 3 dígitos, rellenando con ceros.
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(3) << num; // Ej: 7 -> "007"
        idticketnext = ss.str();
    }
    // Si el nuevo número es menor que 100 (dos dígitos),
    else if (num < 100) {
        // usa un stringstream para formatearlo a 3 dígitos.
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(3) << num; // Ej: 15 -> "015"
        idticketnext = ss.str();
    }
    // Si el número tiene 3 o más dígitos,
    else {
        // simplemente lo convierte a cadena sin añadir ceros.
        idticketnext = std::to_string(num);
    }
    // Devuelve el nuevo ID formateado.
    return idticketnext;
}


// TIPO: Función
// REALIZA: Encuentra el índice de la última fila utilizada en una matriz de [N][4], basándose en si la primera columna no está vacía.
// PARÁMETROS:
//   - std::string matriz[][4]: La matriz de cadenas de 2 dimensiones.
//   - int filas: El número total de filas de la matriz.
// REGRESA: El índice (int) de la última fila no vacía, o -1 si todas están vacías.
int ObtenerUltimaPosicion4(std::string matriz[][4], int filas) {
    // Inicializa la posición en -1 (indicando que no se ha encontrado ninguna fila usada).
    int ultimaPosicion = -1;
    // Itera a través de cada fila de la matriz.
    for (int i = 0; i < filas; ++i) {
        // Comprueba si el primer elemento (columna 0) de la fila actual no está vacío.
        if (matriz[i][0] != "") {
            // Si no está vacío, actualiza 'ultimaPosicion' con el índice de esta fila.
            ultimaPosicion = i;
        }
    }
    // Devuelve el último índice encontrado.
    return ultimaPosicion;
}


// TIPO: Función
// REALIZA: Encuentra el índice de la última fila utilizada en una matriz de [N][5], basándose en si la primera columna no está vacía.
// PARÁMETROS:
//   - std::string matriz[][5]: La matriz de cadenas de 2 dimensiones.
//   - int filas: El número total de filas de la matriz.
// REGRESA: El índice (int) de la última fila no vacía, o -1 si todas están vacías.
int ObtenerUltimaPosicion5(std::string matriz[][5], int filas) {
    // Inicializa la posición en -1.
    int ultimaPosicion = -1;
    // Itera a través de cada fila de la matriz.
    for (int i = 0; i < filas; ++i) {
        // Comprueba si el primer elemento de la fila actual no está vacío.
        if (matriz[i][0] != "") {
            // Si no está vacío, actualiza 'ultimaPosicion'.
            ultimaPosicion = i;
        }
    }
    // Devuelve el último índice encontrado.
    return ultimaPosicion;
}


// TIPO: Función
// REALIZA: Obtiene la fecha actual del sistema y la formatea como "dd-MM-yyyy".
// PARÁMETROS: Ninguno.
// REGRESA: Una cadena (string) con la fecha formateada.
std::string Fecha() {
    // Obtiene el punto de tiempo actual del reloj del sistema.
    auto now = std::chrono::system_clock::now();
    // Convierte el punto de tiempo a un formato time_t.
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    // Declara una estructura 'tm' para almacenar la fecha y hora desglosadas.
    std::tm localTime;
    // Convierte time_t a tiempo local de forma segura usando localtime_s.
    if (localtime_s(&localTime, &time) == 0) {
        // Si la conversión es exitosa, crea un stringstream para formatear la fecha.
        std::stringstream ss;
        // Formatea la fecha en el formato "dd-MM-yyyy", rellenando con ceros si es necesario.
        ss << std::setfill('0') << std::setw(2) << localTime.tm_mday << "-"
            << std::setw(2) << localTime.tm_mon + 1 << "-" // tm_mon es 0-11, por eso se suma 1.
            << localTime.tm_year + 1900; // tm_year es años desde 1900.
        // Devuelve la cadena con la fecha formateada.
        return ss.str();
    }
    else {
        // Si la conversión de tiempo falla, devuelve una cadena vacía para indicar un error.
        return "";
    }
}

// TIPO: Función (principal)
// REALIZA: Es el punto de entrada del programa.
// PARÁMETROS: Ninguno.
// REGRESA: Un entero (0 si finaliza con éxito).
int main()
{
    // Imprime el mensaje "Principal 3!" en la consola, seguido de un salto de línea.
    std::cout << "Principal 3!\n";
}