
// Incluye la librería para manejar la entrada y salida de datos estándar (Input/Output Stream). 
// Te permite usar 'std::cout' para imprimir en la consola y 'std::cin' para leer desde el teclado.
#include <iostream>

// Incluye la librería para trabajar con cadenas de texto. 
// Proporciona la clase `std::string`, que facilita crear y manipular texto.
#include <string>

// Incluye la librería de manipuladores de entrada/salida (Input/Output Manipulators). 
// Sirve para formatear la salida, por ejemplo, con `std::setw()` para definir el ancho de un texto 
// o `std::left` para alinearlo, creando columnas ordenadas.
#include <iomanip> 

// Incluye la librería para usar flujos de cadenas de texto (String Stream). 
// Es muy útil para construir cadenas complejas, combinando texto y números, 
// como cuando generas el formato de un ticket o una fecha.
#include <sstream> 

// Incluye la librería para trabajar con el tiempo (fechas, horas, duraciones). 
// La usas en tu función `Fecha()` para obtener la hora y fecha actuales del sistema.
#include <chrono> 

// Incluye la librería para usar 'vectores', que son arreglos que pueden cambiar de tamaño dinámicamente.
// Aunque está incluido en tu proyecto, actualmente no se está utilizando, ya que usas arreglos de tamaño fijo 
// como `string productos[10][4];`.
#include <vector>


using namespace std;


string MostrarMenu(const string opciones[], int tamano) {
    string cadena = "";
    int i = 0;
    // Índice para iterar sobre el arreglo
    // Bucle while para recorrer el arreglo de opciones

    while (i < tamano) {
        // Concatena la opción actual con su número correspondiente y un salto de línea
        cadena += opciones[i] + "\n";
        // Incrementa el índice para pasar a la siguiente opción
        i++;
    }
    // Retorna la cadena del menú formateado  
    return cadena;
}

std::string Dialogo(const std::string& texto) {
    std::string cadena;
    std::cout << texto << " : ";
    std::getline(std::cin, cadena);
    return cadena;
}

string DesplegarMenu(const string& Titulo1, const string opciones[], int tamano) {
    string cadena;
    cadena = Titulo1 + "\n" + "\n";
    cadena += MostrarMenu(opciones, tamano);
    cadena += "\n Que opcion deseas ";
    cadena = Dialogo(cadena);
    return cadena;
}


std::string Leer(const std::string& texto) {
    // Declara una función que toma una cadena constante como entrada y devuelve una cadena
    // La cadena 'texto' es el mensaje que se mostrará al usuario

    std::string cadena = ""; // Inicializa una cadena vacía llamada 'cadena'

    cadena = Dialogo(texto); // Llama a la función Dialogo con el texto dado y asigna el resultado a 'cadena'
    // Dialogo() lee una cadena de texto de la entrada del usuario

    if (!cadena.empty()) {
        // Comprueba si la cadena devuelta por Dialogo() no está vacía
        //Nota: se cambio la condición if (cadena != null) por if (!cadena.empty()) ya que en c++ null no es una propiedad de los strings

        // Elimina el espacio en blanco del principio y del final de la cadena
        size_t first = cadena.find_first_not_of(' ');
        if (std::string::npos == first) {
            cadena = "";
        }
        else {
            size_t last = cadena.find_last_not_of(' ');
            cadena = cadena.substr(first, (last - first + 1));
        }

        if (cadena.empty()) {
            // Si la cadena está vacía después de eliminar los espacios en blanco, asigna null a la cadena
            cadena = ""; // En C++, se representa "null" para cadenas vacías con ""
        }
    }
    else {
        cadena = ""; // Si la cadena original estaba vacía, asigna null a la cadena
    }

    return cadena; // Devuelve la cadena resultante
}

bool EsNumeroEntero(const string& dato) {
    // Declara un método llamado EsNumeroEntero() que toma un string como parámetro y devuelve un booleano.
    for (char c : dato) {
        // Declara un bucle for que itera sobre los caracteres del string dato.
        if (!isdigit(c)) {
            // Dentro del bucle, se comprueba si el carácter actual es un dígito. Si no lo es, se devuelve false.
            return false;
        }
    }
    // Si todos los caracteres son dígitos, se devuelve true.
    return true;
}


bool EsNumeroDouble(const std::string& dato) {
    // Declara una función que toma una cadena constante como entrada y devuelve un booleano
    // La cadena 'dato' es la cadena que se va a verificar

    bool valido = false; // Inicializa una variable booleana 'valido' a 'false'
    // 'valido' se usará para rastrear si ya se encontró un punto decimal

    for (char c : dato) {
        // Itera a través de cada carácter 'c' en la cadena 'dato'

        if (!std::isdigit(c)) {
            // Verifica si el carácter actual 'c' NO es un dígito

            if (c == '.' && !valido) {
                // Si 'c' es un punto decimal Y 'valido' es 'false' (es decir, aún no se encontró un punto decimal)
                valido = true; // Establece 'valido' a 'true' para indicar que se encontró un punto decimal
            }
            else {
                // Si 'c' no es un dígito y tampoco es un punto decimal válido (o ya se encontró un punto decimal)
                return false; // Retorna 'false' inmediatamente, indicando que 'dato' no es un número double válido
            }
        }
    }

    // Si el bucle termina sin retornar 'false', significa que 'dato' contiene solo dígitos y, como máximo, un punto decimal
    return valido; // Retorna el valor actual de 'valido', que será 'true' si se encontró un punto decimal, o 'false' si no se encontró
}

bool EvaluarNumerico(const std::string& dato, int tipo) {
    bool valido = false;
    switch (tipo) {
    case 1:
        valido = EsNumeroEntero(dato);
        break;
    case 2:
        valido = EsNumeroDouble(dato);
        break;
    default:
        break;
    }
    return valido;
}

std::string Rellenarespacios(std::string dato, int tamano) {
    // Declara una función que toma una cadena y un entero como entrada y devuelve una cadena
    // 'dato' es la cadena que se va a rellenar con espacios
    // 'tamano' es el tamaño total deseado de la cadena resultante

    std::stringstream ss; // Crea un objeto stringstream para construir la cadena resultante

    ss << std::left << std::setw(tamano) << dato;
    // Utiliza stringstream para formatear la cadena:
    // std::left: Indica que el relleno se hará a la derecha (espacios a la derecha del texto)
    // std::setw(tamano): Especifica el tamaño total de la cadena resultante
    // dato: La cadena que se va a formatear

    return ss.str(); // Devuelve la cadena formateada como un objeto string
}

std::string IdTicketSiguiente(const std::string& idticket) {
    std::string idticketnext = "";
    int num = std::stoi(idticket) + 1;

    if (num < 10) {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(3) << num; // Agrega "00"
        idticketnext = ss.str();
    }
    else if (num < 100) {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << num; // Agrega "0"
        idticketnext = ss.str();
    }
    else {
        idticketnext = std::to_string(num); // No agrega ceros
    }
    return idticketnext;
}

int ObtenerUltimaPosicion4(std::string matriz[][4], int filas) {
    int ultimaPosicion = -1;
    for (int i = 0; i < filas; ++i) {
        if (matriz[i][0] != "") { // Verifica si la primera columna de la fila no está vacía
            ultimaPosicion = i;
        }
    }
    return ultimaPosicion;
}
int ObtenerUltimaPosicion5(std::string matriz[][5], int filas) {
    int ultimaPosicion = -1;
    for (int i = 0; i < filas; ++i) {
        if (matriz[i][0] != "") { // Verifica si la primera columna de la fila no está vacía
            ultimaPosicion = i;
        }
    }
    return ultimaPosicion;
}

std::string Fecha() {
    // Declara un método estático llamado Fecha() que devuelve una cadena.

    auto now = std::chrono::system_clock::now(); // Obtiene la fecha y hora actuales

    std::time_t time = std::chrono::system_clock::to_time_t(now); // Convierte a time_t

    std::tm localTime; // Declara un objeto tm para localtime_s

    if (localtime_s(&localTime, &time) == 0) { // Convierte a tm usando localtime_s
        std::stringstream ss; // Crea un stringstream para formatear la fecha

        ss << std::setfill('0') << std::setw(2) << localTime.tm_mday << "-"
            << std::setw(2) << localTime.tm_mon + 1 << "-"
            << localTime.tm_year + 1900;
        // Formatea la fecha en el formato dd-MM-yyyy

        return ss.str(); // Devuelve la fecha formateada como una cadena
    }
    else {
        // Manejar el error si localtime_s falla
        return ""; // O lanza una excepción, dependiendo de tu manejo de errores
    }
}

// TIPO: Procedimiento
// REALIZA: Gestiona el menú del punto de venta para un ticket específico. Permite agregar, eliminar, listar artículos, pagar y salir.
// PARÁMETROS:
//   - std::string idticket: El ID del último ticket generado, se usa como base para crear el nuevo número de ticket.
// REGRESA: Nada (void).
void MenuPuntoVenta(std::string idticket) {
    // Declara una cadena para almacenar la opción del usuario y otra para el encabezado del ticket.
    std::string opcion, membrete;
    // Declara una bandera booleana para verificar si el ticket ha sido pagado, se inicializa en falso.
    bool pago = false;
    // Llama a la función para generar el siguiente número de ticket y lo asigna a la variable.
    idticket = IdTicketSiguiente(idticket);
    // Llama a la función para obtener la fecha actual.
    std::string fechadia = Fecha();
    // Construye el encabezado (membrete) con la fecha y el nuevo número de ticket.
    membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
    // Agrega una línea separadora al encabezado para mejorar la presentación.
    membrete += "\n-----------------------------------------------------\n";
    // Define un arreglo constante de cadenas con las opciones del menú de punto de venta.
    const std::string datosmenu[] = { "1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida " };

    // Inicia un bucle do-while que se ejecutará al menos una vez y continuará hasta que la opción sea "5".
    do {
        // Llama a DesplegarMenu para mostrar el encabezado, el título del menú y las opciones, y guarda la elección del usuario.
        opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu, 5);
        // Verifica si la cadena de opción retornada está vacía (p. ej., si el usuario solo presionó Enter).
        if (opcion.empty()) {
            // Si está vacía, informa al usuario que el dato es incorrecto.
            std::cout << "dato incorrecto introducido" << std::endl;
        }
        else {
            // Si la opción no está vacía, la convierte a entero y la usa en una estructura switch.
            switch (std::stoi(opcion)) {
                // Caso para la opción 1.
            case 1:
                // Muestra un mensaje indicando la acción a realizar.
                std::cout << "Agregar Articulo al Ticket" << std::endl;
                // Termina el caso actual.
                break;
                // Caso para la opción 2.
            case 2:
                // Muestra un mensaje indicando la acción a realizar.
                std::cout << "Eliminar Articulo del Ticket" << std::endl;
                // Termina el caso actual.
                break;
                // Caso para la opción 3.
            case 3:
                // Muestra un mensaje indicando la acción a realizar.
                std::cout << "Listado de Articulos del Ticket" << std::endl;
                // Termina el caso actual.
                break;
                // Caso para la opción 4.
            case 4:
                // Muestra un mensaje indicando la acción a realizar.
                std::cout << "Pagar Ticket y salir" << std::endl;
                // Cambia la variable 'opcion' a "5" para que el bucle do-while termine en la siguiente iteración.
                opcion = "5";
                // Establece la bandera 'pago' a verdadero para registrar que se completó el pago.
                pago = true;
                // Termina el caso actual.
                break;
                // Caso para la opción 5.
            case 5:
                // Muestra un mensaje de salida.
                std::cout << "Salida del Ventas" << std::endl;
                // Verifica si la bandera 'pago' NO es verdadera.
                if (!pago) {
                    // Si no se pagó, informa al usuario.
                    std::cout << "No pago el ticket" << std::endl;
                    // Informa que el ticket actual será eliminado (lógica de cancelación).
                    std::cout << "eliminando ticket " << idticket << std::endl;
                }
                // Termina el caso actual.
                break;
                // Bloque por defecto: se ejecuta si la opción no coincide con ningún caso.
            default:
                // Informa al usuario que la opción no es válida.
                std::cout << "No existe esta opcion" << std::endl;
                // Termina el caso actual.
                break;
            }
        }
        // La condición del bucle: se repite mientras la opción del usuario sea diferente de "5".
    } while (opcion != "5");
}

// TIPO: Procedimiento
// REALIZA: Muestra y gestiona las opciones relacionadas con los productos (modificar, listar, salir).
// PARÁMETROS: Ninguno.
// REGRESA: Nada (void).
void MenuProductos() {
    // Define un arreglo constante de cadenas con las opciones del menú de productos.
    const std::string datosmenuproductos[] = { "1.-Modificar ", "2.-Listado ", "3.-Salida " };
    // Declara e inicializa la variable 'opcion' para controlar el bucle.
    std::string opcion = "0";
    // Inicia un bucle do-while que se ejecutará hasta que la opción sea "3".
    do {
        // Muestra el menú de productos y captura la elección del usuario.
        opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos, 3);
        // Verifica si la opción introducida está vacía.
        if (opcion.empty()) {
            // Informa al usuario de la opción incorrecta.
            std::cout << "opcion incorrecta " << std::endl;
        }
        else {
            // Si no está vacía, convierte la opción a entero y la evalúa en un switch.
            switch (std::stoi(opcion)) {
                // Caso para la opción 1.
            case 1:
                // Muestra un mensaje de la acción correspondiente.
                std::cout << "Modificar Precio Producto" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opción 2.
            case 2:
                // Muestra un mensaje de la acción correspondiente.
                std::cout << "Listado Producto" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opción 3.
            case 3:
                // Muestra un mensaje de salida.
                std::cout << "Salida del Sistema" << std::endl;
                // Termina el caso.
                break;
                // Bloque por defecto para opciones no válidas.
            default:
                // Informa al usuario que la opción no existe.
                std::cout << "No existe esta opcion" << std::endl;
                // Termina el caso.
                break;
            }
        }
        // El bucle continúa mientras la opción sea diferente de "3".
    } while (opcion != "3");
}

// TIPO: Procedimiento
// REALIZA: Muestra y gestiona las opciones del inventario (listar, agregar, salir).
// PARÁMETROS: Ninguno.
// REGRESA: Nada (void).
void MenuInventario() {
    // Define un arreglo constante de cadenas con las opciones del menú de inventario.
    const std::string datosmenuinventario[] = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
    // Declara e inicializa la variable 'opcion' para controlar el bucle.
    std::string opcion = "0";
    // Inicia un bucle do-while que se ejecutará hasta que la opción sea "3".
    do {
        // Muestra el menú de inventarios y captura la elección del usuario.
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario, 3);
        // Verifica si la opción introducida está vacía.
        if (opcion.empty()) {
            // Informa al usuario de la opción incorrecta.
            std::cout << "opcion incorrecta" << std::endl;
        }
        else {
            // Si no está vacía, convierte la opción a entero y la evalúa en un switch.
            switch (std::stoi(opcion)) {
                // Caso para la opción 1.
            case 1:
                // Muestra un mensaje de la acción correspondiente.
                std::cout << "Listado de Inventario" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opción 2.
            case 2:
                // Muestra un mensaje de la acción correspondiente.
                std::cout << "Agregar Inventario" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opción 3.
            case 3:
                // Muestra un mensaje de salida.
                std::cout << "Salida del Sistema" << std::endl;
                // Termina el caso.
                break;
                // Bloque por defecto para opciones no válidas.
            default:
                // Informa al usuario que la opción no existe.
                std::cout << "No existe esta opcion" << std::endl;
                // Termina el caso.
                break;
            }
        }
        // El bucle continúa mientras la opción sea diferente de "3".
    } while (opcion != "3");
}

// TIPO: Procedimiento
// REALIZA: Muestra el menú principal de la aplicación y permite navegar a los diferentes submódulos.
// PARÁMETROS: Ninguno.
// REGRESA: Nada (void).
void MenuPrincipal() {
    // Declara una variable entera para la opción del menú.
    int opcion = 0;
    // Declara una bandera booleana para controlar la salida del menú principal.
    bool salida = false;
    // Define un arreglo constante con las opciones del menú principal.
    static const std::string datosmenuprincipal[] = { "1.-Productos ", "2.-Punto de Venta ", "3.-Inventario ","4.-Ventas ", "5.-Salida " };
    // Inicia un bucle while que se ejecutará mientras la bandera 'salida' sea falsa.
    while (!salida) {
        // Muestra el menú principal y guarda la opción del usuario como una cadena.
        std::string opcionStr = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña", datosmenuprincipal, 5);

        // Verifica si la opción introducida está vacía.
        if (opcionStr.empty()) {
            // Informa al usuario de la opción incorrecta.
            std::cout << "opcion incorrecta " << std::endl;
        }
        else {
            // Convierte solo el primer carácter de la cadena a un entero. Esto permite que entradas como "1." o "1-.." funcionen.
            opcion = std::stoi(opcionStr.substr(0, 1));
            // Evalúa la opción numérica en un switch.
            switch (opcion) {
                // Caso para la opción 1.
            case 1:
                // Llama al procedimiento que gestiona el menú de productos.
                MenuProductos();
                // Termina el caso.
                break;
                // Caso para la opción 2.
            case 2:
                // Llama al procedimiento del punto de venta, iniciando con el ticket "000".
                MenuPuntoVenta("000");
                // Termina el caso.
                break;
                // Caso para la opción 3.
            case 3:
                // Llama al procedimiento que gestiona el menú de inventario.
                MenuInventario();
                // Termina el caso.
                break;
                // Caso para la opción 4.
            case 4:
                // Muestra un mensaje para la sección de ventas.
                std::cout << "Ventas" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opción 5.
            case 5:
                // Muestra un mensaje de salida del sistema.
                std::cout << "Salida del Sistema " << std::endl;
                // Cambia la bandera 'salida' a verdadero para terminar el bucle while.
                salida = true;
                // Termina el caso.
                break;
                // Bloque por defecto para opciones no válidas.
            default:
                // Informa al usuario que la opción no existe.
                std::cout << "No existe esta opcion " << std::endl;
                // Termina el caso.
                break;
            }
        }
    }
}

// TIPO: Función (principal)
// REALIZA: Es el punto de entrada del programa.
// PARÁMETROS: Ninguno.
// REGRESA: Un entero (0 si finaliza con éxito).
int main()
{
    // Imprime un mensaje inicial en la consola.
    std::cout << "Principal 3!\n";
    // Llama al procedimiento del menú principal para iniciar la aplicación.
    MenuPrincipal();
}