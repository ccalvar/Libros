// Incluye la librer�a iostream para operaciones de entrada y salida, como std::cout y std::cin.
#include <iostream>
// Incluye la librer�a string para poder utilizar el tipo de dato std::string.
#include <string>
// Incluye la librer�a iomanip para manipuladores de formato de salida, como std::setw y std::left.
#include <iomanip>
// Incluye la librer�a sstream para usar std::stringstream, que permite construir cadenas de texto.
#include <sstream>
// Incluye la librer�a chrono para trabajar con fechas y horas.
#include <chrono>
// Incluye la librer�a vector para usar la estructura de datos std::vector (aunque no se usa en este c�digo).
#include <vector>

// Usa el espacio de nombres est�ndar para no tener que escribir "std::" antes de cada elemento.
using namespace std;

// TIPO: Funci�n
// REALIZA: Construye y formatea una cadena de texto que representa un men� de opciones.
// PAR�METROS:
//   - const string opciones[]: Un arreglo de cadenas de texto, donde cada una es una opci�n del men�.
//   - int tamano: Un entero que indica el n�mero de elementos en el arreglo 'opciones'.
// REGRESA: Una cadena (string) con todas las opciones numeradas y separadas por saltos de l�nea.
string MostrarMenu(const string opciones[], int tamano) {
    // Declara e inicializa una cadena vac�a que acumular� el texto del men�.
    string cadena = "";
    // Declara e inicializa un contador 'i' en 0 para iterar sobre el arreglo.
    int i = 0;

    // Inicia un bucle que se ejecutar� mientras 'i' sea menor que el tama�o del arreglo.
    while (i < tamano) {
        // Concatena a 'cadena' el n�mero de la opci�n (i + 1), un punto, la opci�n del arreglo y un salto de l�nea.
        cadena += to_string(i + 1) + ". " + opciones[i] + "\n";
        // Incrementa el contador para pasar a la siguiente opci�n.
        i++;
    }
    // Devuelve la cadena final con el men� formateado.
    return cadena;
}


// TIPO: Funci�n
// REALIZA: Muestra un texto en la consola y lee una l�nea completa de entrada del usuario.
// PAR�METROS:
//   - const std::string& texto: Una cadena de texto que se mostrar� como un mensaje o pregunta al usuario.
// REGRESA: La cadena de texto (string) que el usuario introdujo.
std::string Dialogo(const std::string& texto) {
    // Declara una cadena de texto vac�a para almacenar la entrada del usuario.
    std::string cadena;
    // Muestra el texto del par�metro seguido de dos puntos y un espacio.
    std::cout << texto << " : ";
    // Lee la l�nea completa de la entrada est�ndar (teclado) y la guarda en 'cadena'.
    std::getline(std::cin, cadena);
    // Devuelve la cadena le�da.
    return cadena;
}


// TIPO: Funci�n
// REALIZA: Muestra un t�tulo, un men� de opciones y solicita al usuario que elija una.
// PAR�METROS:
//   - const std::string& Titulo1: Una cadena con el t�tulo del men�.
//   - const std::string opciones[]: Un arreglo con las opciones del men�.
//   - int tamano: El n�mero de elementos en el arreglo 'opciones'.
// REGRESA: La cadena (string) con la opci�n que el usuario introdujo.
std::string DesplegarMenu(const std::string& Titulo1, const std::string opciones[], int tamano) {
    // Crea una cadena inicial con el t�tulo y dos saltos de l�nea.
    std::string cadena = Titulo1 + "\n\n";
    // Llama a MostrarMenu para generar la lista de opciones y la a�ade a la cadena.
    cadena += MostrarMenu(opciones, tamano);
    // A�ade la pregunta para el usuario a la cadena.
    cadena += "\n Que opcion deseas ";
    // Llama a Dialogo con la cadena completa para mostrar el men� y leer la respuesta del usuario.
    return Dialogo(cadena);
}


// TIPO: Funci�n
// REALIZA: Pide un dato al usuario, lo lee y elimina los espacios en blanco al principio y al final.
// PAR�METROS:
//   - const std::string& texto: El mensaje que se le mostrar� al usuario para pedirle el dato.
// REGRESA: La cadena (string) introducida por el usuario, sin espacios iniciales ni finales. Si la entrada est� vac�a o solo contiene espacios, regresa una cadena vac�a.
std::string Leer(const std::string& texto) {
    // Declara una cadena vac�a para almacenar el resultado.
    std::string cadena = "";
    // Llama a la funci�n Dialogo para mostrar el texto y leer la entrada del usuario.
    cadena = Dialogo(texto);
    // Verifica si la cadena le�da no est� vac�a.
    if (!cadena.empty()) {
        // Busca la posici�n del primer car�cter que no sea un espacio.
        size_t first = cadena.find_first_not_of(' ');
        // Si no se encuentra ning�n car�cter (la cadena solo tiene espacios),
        if (std::string::npos == first) {
            // la cadena resultante se establece como vac�a.
            cadena = "";
        }
        else {
            // Busca la posici�n del �ltimo car�cter que no sea un espacio.
            size_t last = cadena.find_last_not_of(' ');
            // Extrae la subcadena desde el primer hasta el �ltimo car�cter no espacial.
            cadena = cadena.substr(first, (last - first + 1));
        }
    }
    // Devuelve la cadena ya procesada (sin espacios extra).
    return cadena;
}


// TIPO: Funci�n
// REALIZA: Verifica si una cadena de texto contiene �nicamente d�gitos num�ricos.
// PAR�METROS:
//   - const string& dato: La cadena a evaluar.
// REGRESA: Un booleano. 'true' si todos los caracteres son d�gitos, 'false' en caso contrario.
bool EsNumeroEntero(const string& dato) {
    // Itera sobre cada car�cter 'c' en la cadena 'dato'.
    for (char c : dato) {
        // Comprueba si el car�cter actual NO es un d�gito usando la funci�n isdigit().
        if (!isdigit(c)) {
            // Si encuentra un car�cter que no es un d�gito, retorna 'false' inmediatamente.
            return false;
        }
    }
    // Si el bucle termina, significa que todos los caracteres eran d�gitos, por lo que retorna 'true'.
    return true;
}


// TIPO: Funci�n
// REALIZA: Verifica si una cadena de texto representa un n�mero de tipo double (permite un �nico punto decimal).
// PAR�METROS:
//   - const std::string& dato: La cadena a evaluar.
// REGRESA: Un booleano. 'true' si la cadena es un n�mero double v�lido (con punto decimal), 'false' si no lo es.
bool EsNumeroDouble(const std::string& dato) {
    // Inicializa una bandera booleana para rastrear si ya se ha encontrado un punto decimal.
    bool puntoEncontrado = false;
    // Itera sobre cada car�cter 'c' de la cadena 'dato'.
    for (char c : dato) {
        // Verifica si el car�cter actual NO es un d�gito.
        if (!std::isdigit(c)) {
            // Si no es un d�gito, comprueba si es un punto y si a�n no se ha encontrado otro punto.
            if (c == '.' && !puntoEncontrado) {
                // Si es el primer punto, actualiza la bandera a 'true'.
                puntoEncontrado = true;
            }
            else {
                // Si es otro car�cter no num�rico o si ya hab�a un punto, la cadena no es v�lida. Retorna 'false'.
                return false;
            }
        }
    }
    // Retorna el valor de 'puntoEncontrado'. Esto hace que la funci�n solo devuelva 'true' si hab�a exactamente un punto.
    return puntoEncontrado;
}


// TIPO: Funci�n
// REALIZA: Eval�a si una cadena es de un tipo num�rico espec�fico (entero o double).
// PAR�METROS:
//   - const std::string& dato: La cadena a evaluar.
//   - int tipo: Un entero que especifica el tipo de validaci�n (1 para entero, 2 para double).
// REGRESA: Un booleano que indica si la validaci�n fue exitosa.
bool EvaluarNumerico(const std::string& dato, int tipo) {
    // Declara una variable booleana para almacenar el resultado, inicializada en falso.
    bool valido = false;
    // Inicia una estructura switch para seleccionar la validaci�n seg�n el 'tipo'.
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
    // Devuelve el resultado de la validaci�n.
    return valido;
}


// TIPO: Funci�n
// REALIZA: Rellena una cadena con espacios a la derecha hasta que alcance un tama�o espec�fico.
// PAR�METROS:
//   - std::string dato: La cadena original que se va a rellenar.
//   - int tamano: El tama�o total que debe tener la cadena final.
// REGRESA: Una nueva cadena (string) con los espacios a�adidos.
std::string Rellenarespacios(std::string dato, int tamano) {
    // Crea un objeto stringstream para facilitar la construcci�n de la cadena formateada.
    std::stringstream ss;
    // Usa manipuladores de flujo:
    // std::left: alinea el contenido a la izquierda.
    // std::setw(tamano): establece el ancho total del campo a 'tamano'.
    // Los espacios se a�adir�n a la derecha para rellenar el ancho.
    ss << std::left << std::setw(tamano) << dato;
    // Convierte el contenido del stringstream a una cadena y la devuelve.
    return ss.str();
}


// TIPO: Funci�n
// REALIZA: Toma un ID de ticket como cadena, lo incrementa en 1 y lo formatea con ceros a la izquierda para mantener una longitud de 3 d�gitos.
// PAR�METROS:
//   - const std::string& idticket: El ID actual del ticket en formato de cadena.
// REGRESA: El siguiente ID como una cadena (string) formateada.
std::string IdTicketSiguiente(const std::string& idticket) {
    // Declara una cadena para el siguiente ID.
    std::string idticketnext = "";
    // Convierte la cadena 'idticket' a entero, le suma 1 y lo guarda en 'num'.
    int num = std::stoi(idticket) + 1;

    // Si el nuevo n�mero es menor que 10 (un solo d�gito),
    if (num < 10) {
        // usa un stringstream para formatearlo a 3 d�gitos, rellenando con ceros.
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(3) << num; // Ej: 7 -> "007"
        idticketnext = ss.str();
    }
    // Si el nuevo n�mero es menor que 100 (dos d�gitos),
    else if (num < 100) {
        // usa un stringstream para formatearlo a 3 d�gitos.
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(3) << num; // Ej: 15 -> "015"
        idticketnext = ss.str();
    }
    // Si el n�mero tiene 3 o m�s d�gitos,
    else {
        // simplemente lo convierte a cadena sin a�adir ceros.
        idticketnext = std::to_string(num);
    }
    // Devuelve el nuevo ID formateado.
    return idticketnext;
}


// TIPO: Funci�n
// REALIZA: Encuentra el �ndice de la �ltima fila utilizada en una matriz de [N][4], bas�ndose en si la primera columna no est� vac�a.
// PAR�METROS:
//   - std::string matriz[][4]: La matriz de cadenas de 2 dimensiones.
//   - int filas: El n�mero total de filas de la matriz.
// REGRESA: El �ndice (int) de la �ltima fila no vac�a, o -1 si todas est�n vac�as.
int ObtenerUltimaPosicion4(std::string matriz[][4], int filas) {
    // Inicializa la posici�n en -1 (indicando que no se ha encontrado ninguna fila usada).
    int ultimaPosicion = -1;
    // Itera a trav�s de cada fila de la matriz.
    for (int i = 0; i < filas; ++i) {
        // Comprueba si el primer elemento (columna 0) de la fila actual no est� vac�o.
        if (matriz[i][0] != "") {
            // Si no est� vac�o, actualiza 'ultimaPosicion' con el �ndice de esta fila.
            ultimaPosicion = i;
        }
    }
    // Devuelve el �ltimo �ndice encontrado.
    return ultimaPosicion;
}


// TIPO: Funci�n
// REALIZA: Encuentra el �ndice de la �ltima fila utilizada en una matriz de [N][5], bas�ndose en si la primera columna no est� vac�a.
// PAR�METROS:
//   - std::string matriz[][5]: La matriz de cadenas de 2 dimensiones.
//   - int filas: El n�mero total de filas de la matriz.
// REGRESA: El �ndice (int) de la �ltima fila no vac�a, o -1 si todas est�n vac�as.
int ObtenerUltimaPosicion5(std::string matriz[][5], int filas) {
    // Inicializa la posici�n en -1.
    int ultimaPosicion = -1;
    // Itera a trav�s de cada fila de la matriz.
    for (int i = 0; i < filas; ++i) {
        // Comprueba si el primer elemento de la fila actual no est� vac�o.
        if (matriz[i][0] != "") {
            // Si no est� vac�o, actualiza 'ultimaPosicion'.
            ultimaPosicion = i;
        }
    }
    // Devuelve el �ltimo �ndice encontrado.
    return ultimaPosicion;
}


// TIPO: Funci�n
// REALIZA: Obtiene la fecha actual del sistema y la formatea como "dd-MM-yyyy".
// PAR�METROS: Ninguno.
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
        // Si la conversi�n es exitosa, crea un stringstream para formatear la fecha.
        std::stringstream ss;
        // Formatea la fecha en el formato "dd-MM-yyyy", rellenando con ceros si es necesario.
        ss << std::setfill('0') << std::setw(2) << localTime.tm_mday << "-"
            << std::setw(2) << localTime.tm_mon + 1 << "-" // tm_mon es 0-11, por eso se suma 1.
            << localTime.tm_year + 1900; // tm_year es a�os desde 1900.
        // Devuelve la cadena con la fecha formateada.
        return ss.str();
    }
    else {
        // Si la conversi�n de tiempo falla, devuelve una cadena vac�a para indicar un error.
        return "";
    }
}

// TIPO: Funci�n (principal)
// REALIZA: Es el punto de entrada del programa.
// PAR�METROS: Ninguno.
// REGRESA: Un entero (0 si finaliza con �xito).
int main()
{
    // Imprime el mensaje "Principal 3!" en la consola, seguido de un salto de l�nea.
    std::cout << "Principal 3!\n";
}