
// Incluye la librer�a para manejar la entrada y salida de datos est�ndar (Input/Output Stream). 
// Te permite usar 'std::cout' para imprimir en la consola y 'std::cin' para leer desde el teclado.
#include <iostream>

// Incluye la librer�a para trabajar con cadenas de texto. 
// Proporciona la clase `std::string`, que facilita crear y manipular texto.
#include <string>

// Incluye la librer�a de manipuladores de entrada/salida (Input/Output Manipulators). 
// Sirve para formatear la salida, por ejemplo, con `std::setw()` para definir el ancho de un texto 
// o `std::left` para alinearlo, creando columnas ordenadas.
#include <iomanip> 

// Incluye la librer�a para usar flujos de cadenas de texto (String Stream). 
// Es muy �til para construir cadenas complejas, combinando texto y n�meros, 
// como cuando generas el formato de un ticket o una fecha.
#include <sstream> 

// Incluye la librer�a para trabajar con el tiempo (fechas, horas, duraciones). 
// La usas en tu funci�n `Fecha()` para obtener la hora y fecha actuales del sistema.
#include <chrono> 

// Incluye la librer�a para usar 'vectores', que son arreglos que pueden cambiar de tama�o din�micamente.
// Aunque est� incluido en tu proyecto, actualmente no se est� utilizando, ya que usas arreglos de tama�o fijo 
// como `string productos[10][4];`.
#include <vector>


using namespace std;


string MostrarMenu(const string opciones[], int tamano) {
    string cadena = "";
    int i = 0;
    // �ndice para iterar sobre el arreglo
    // Bucle while para recorrer el arreglo de opciones

    while (i < tamano) {
        // Concatena la opci�n actual con su n�mero correspondiente y un salto de l�nea
        cadena += opciones[i] + "\n";
        // Incrementa el �ndice para pasar a la siguiente opci�n
        i++;
    }
    // Retorna la cadena del men� formateado  
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
    // Declara una funci�n que toma una cadena constante como entrada y devuelve una cadena
    // La cadena 'texto' es el mensaje que se mostrar� al usuario

    std::string cadena = ""; // Inicializa una cadena vac�a llamada 'cadena'

    cadena = Dialogo(texto); // Llama a la funci�n Dialogo con el texto dado y asigna el resultado a 'cadena'
    // Dialogo() lee una cadena de texto de la entrada del usuario

    if (!cadena.empty()) {
        // Comprueba si la cadena devuelta por Dialogo() no est� vac�a
        //Nota: se cambio la condici�n if (cadena != null) por if (!cadena.empty()) ya que en c++ null no es una propiedad de los strings

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
            // Si la cadena est� vac�a despu�s de eliminar los espacios en blanco, asigna null a la cadena
            cadena = ""; // En C++, se representa "null" para cadenas vac�as con ""
        }
    }
    else {
        cadena = ""; // Si la cadena original estaba vac�a, asigna null a la cadena
    }

    return cadena; // Devuelve la cadena resultante
}

bool EsNumeroEntero(const string& dato) {
    // Declara un m�todo llamado EsNumeroEntero() que toma un string como par�metro y devuelve un booleano.
    for (char c : dato) {
        // Declara un bucle for que itera sobre los caracteres del string dato.
        if (!isdigit(c)) {
            // Dentro del bucle, se comprueba si el car�cter actual es un d�gito. Si no lo es, se devuelve false.
            return false;
        }
    }
    // Si todos los caracteres son d�gitos, se devuelve true.
    return true;
}


bool EsNumeroDouble(const std::string& dato) {
    // Declara una funci�n que toma una cadena constante como entrada y devuelve un booleano
    // La cadena 'dato' es la cadena que se va a verificar

    bool valido = false; // Inicializa una variable booleana 'valido' a 'false'
    // 'valido' se usar� para rastrear si ya se encontr� un punto decimal

    for (char c : dato) {
        // Itera a trav�s de cada car�cter 'c' en la cadena 'dato'

        if (!std::isdigit(c)) {
            // Verifica si el car�cter actual 'c' NO es un d�gito

            if (c == '.' && !valido) {
                // Si 'c' es un punto decimal Y 'valido' es 'false' (es decir, a�n no se encontr� un punto decimal)
                valido = true; // Establece 'valido' a 'true' para indicar que se encontr� un punto decimal
            }
            else {
                // Si 'c' no es un d�gito y tampoco es un punto decimal v�lido (o ya se encontr� un punto decimal)
                return false; // Retorna 'false' inmediatamente, indicando que 'dato' no es un n�mero double v�lido
            }
        }
    }

    // Si el bucle termina sin retornar 'false', significa que 'dato' contiene solo d�gitos y, como m�ximo, un punto decimal
    return valido; // Retorna el valor actual de 'valido', que ser� 'true' si se encontr� un punto decimal, o 'false' si no se encontr�
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
    // Declara una funci�n que toma una cadena y un entero como entrada y devuelve una cadena
    // 'dato' es la cadena que se va a rellenar con espacios
    // 'tamano' es el tama�o total deseado de la cadena resultante

    std::stringstream ss; // Crea un objeto stringstream para construir la cadena resultante

    ss << std::left << std::setw(tamano) << dato;
    // Utiliza stringstream para formatear la cadena:
    // std::left: Indica que el relleno se har� a la derecha (espacios a la derecha del texto)
    // std::setw(tamano): Especifica el tama�o total de la cadena resultante
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
        if (matriz[i][0] != "") { // Verifica si la primera columna de la fila no est� vac�a
            ultimaPosicion = i;
        }
    }
    return ultimaPosicion;
}
int ObtenerUltimaPosicion5(std::string matriz[][5], int filas) {
    int ultimaPosicion = -1;
    for (int i = 0; i < filas; ++i) {
        if (matriz[i][0] != "") { // Verifica si la primera columna de la fila no est� vac�a
            ultimaPosicion = i;
        }
    }
    return ultimaPosicion;
}

std::string Fecha() {
    // Declara un m�todo est�tico llamado Fecha() que devuelve una cadena.

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
        return ""; // O lanza una excepci�n, dependiendo de tu manejo de errores
    }
}

// TIPO: Procedimiento
// REALIZA: Gestiona el men� del punto de venta para un ticket espec�fico. Permite agregar, eliminar, listar art�culos, pagar y salir.
// PAR�METROS:
//   - std::string idticket: El ID del �ltimo ticket generado, se usa como base para crear el nuevo n�mero de ticket.
// REGRESA: Nada (void).
void MenuPuntoVenta(std::string idticket) {
    // Declara una cadena para almacenar la opci�n del usuario y otra para el encabezado del ticket.
    std::string opcion, membrete;
    // Declara una bandera booleana para verificar si el ticket ha sido pagado, se inicializa en falso.
    bool pago = false;
    // Llama a la funci�n para generar el siguiente n�mero de ticket y lo asigna a la variable.
    idticket = IdTicketSiguiente(idticket);
    // Llama a la funci�n para obtener la fecha actual.
    std::string fechadia = Fecha();
    // Construye el encabezado (membrete) con la fecha y el nuevo n�mero de ticket.
    membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
    // Agrega una l�nea separadora al encabezado para mejorar la presentaci�n.
    membrete += "\n-----------------------------------------------------\n";
    // Define un arreglo constante de cadenas con las opciones del men� de punto de venta.
    const std::string datosmenu[] = { "1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida " };

    // Inicia un bucle do-while que se ejecutar� al menos una vez y continuar� hasta que la opci�n sea "5".
    do {
        // Llama a DesplegarMenu para mostrar el encabezado, el t�tulo del men� y las opciones, y guarda la elecci�n del usuario.
        opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu, 5);
        // Verifica si la cadena de opci�n retornada est� vac�a (p. ej., si el usuario solo presion� Enter).
        if (opcion.empty()) {
            // Si est� vac�a, informa al usuario que el dato es incorrecto.
            std::cout << "dato incorrecto introducido" << std::endl;
        }
        else {
            // Si la opci�n no est� vac�a, la convierte a entero y la usa en una estructura switch.
            switch (std::stoi(opcion)) {
                // Caso para la opci�n 1.
            case 1:
                // Muestra un mensaje indicando la acci�n a realizar.
                std::cout << "Agregar Articulo al Ticket" << std::endl;
                // Termina el caso actual.
                break;
                // Caso para la opci�n 2.
            case 2:
                // Muestra un mensaje indicando la acci�n a realizar.
                std::cout << "Eliminar Articulo del Ticket" << std::endl;
                // Termina el caso actual.
                break;
                // Caso para la opci�n 3.
            case 3:
                // Muestra un mensaje indicando la acci�n a realizar.
                std::cout << "Listado de Articulos del Ticket" << std::endl;
                // Termina el caso actual.
                break;
                // Caso para la opci�n 4.
            case 4:
                // Muestra un mensaje indicando la acci�n a realizar.
                std::cout << "Pagar Ticket y salir" << std::endl;
                // Cambia la variable 'opcion' a "5" para que el bucle do-while termine en la siguiente iteraci�n.
                opcion = "5";
                // Establece la bandera 'pago' a verdadero para registrar que se complet� el pago.
                pago = true;
                // Termina el caso actual.
                break;
                // Caso para la opci�n 5.
            case 5:
                // Muestra un mensaje de salida.
                std::cout << "Salida del Ventas" << std::endl;
                // Verifica si la bandera 'pago' NO es verdadera.
                if (!pago) {
                    // Si no se pag�, informa al usuario.
                    std::cout << "No pago el ticket" << std::endl;
                    // Informa que el ticket actual ser� eliminado (l�gica de cancelaci�n).
                    std::cout << "eliminando ticket " << idticket << std::endl;
                }
                // Termina el caso actual.
                break;
                // Bloque por defecto: se ejecuta si la opci�n no coincide con ning�n caso.
            default:
                // Informa al usuario que la opci�n no es v�lida.
                std::cout << "No existe esta opcion" << std::endl;
                // Termina el caso actual.
                break;
            }
        }
        // La condici�n del bucle: se repite mientras la opci�n del usuario sea diferente de "5".
    } while (opcion != "5");
}

// TIPO: Procedimiento
// REALIZA: Muestra y gestiona las opciones relacionadas con los productos (modificar, listar, salir).
// PAR�METROS: Ninguno.
// REGRESA: Nada (void).
void MenuProductos() {
    // Define un arreglo constante de cadenas con las opciones del men� de productos.
    const std::string datosmenuproductos[] = { "1.-Modificar ", "2.-Listado ", "3.-Salida " };
    // Declara e inicializa la variable 'opcion' para controlar el bucle.
    std::string opcion = "0";
    // Inicia un bucle do-while que se ejecutar� hasta que la opci�n sea "3".
    do {
        // Muestra el men� de productos y captura la elecci�n del usuario.
        opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos, 3);
        // Verifica si la opci�n introducida est� vac�a.
        if (opcion.empty()) {
            // Informa al usuario de la opci�n incorrecta.
            std::cout << "opcion incorrecta " << std::endl;
        }
        else {
            // Si no est� vac�a, convierte la opci�n a entero y la eval�a en un switch.
            switch (std::stoi(opcion)) {
                // Caso para la opci�n 1.
            case 1:
                // Muestra un mensaje de la acci�n correspondiente.
                std::cout << "Modificar Precio Producto" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opci�n 2.
            case 2:
                // Muestra un mensaje de la acci�n correspondiente.
                std::cout << "Listado Producto" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opci�n 3.
            case 3:
                // Muestra un mensaje de salida.
                std::cout << "Salida del Sistema" << std::endl;
                // Termina el caso.
                break;
                // Bloque por defecto para opciones no v�lidas.
            default:
                // Informa al usuario que la opci�n no existe.
                std::cout << "No existe esta opcion" << std::endl;
                // Termina el caso.
                break;
            }
        }
        // El bucle contin�a mientras la opci�n sea diferente de "3".
    } while (opcion != "3");
}

// TIPO: Procedimiento
// REALIZA: Muestra y gestiona las opciones del inventario (listar, agregar, salir).
// PAR�METROS: Ninguno.
// REGRESA: Nada (void).
void MenuInventario() {
    // Define un arreglo constante de cadenas con las opciones del men� de inventario.
    const std::string datosmenuinventario[] = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
    // Declara e inicializa la variable 'opcion' para controlar el bucle.
    std::string opcion = "0";
    // Inicia un bucle do-while que se ejecutar� hasta que la opci�n sea "3".
    do {
        // Muestra el men� de inventarios y captura la elecci�n del usuario.
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario, 3);
        // Verifica si la opci�n introducida est� vac�a.
        if (opcion.empty()) {
            // Informa al usuario de la opci�n incorrecta.
            std::cout << "opcion incorrecta" << std::endl;
        }
        else {
            // Si no est� vac�a, convierte la opci�n a entero y la eval�a en un switch.
            switch (std::stoi(opcion)) {
                // Caso para la opci�n 1.
            case 1:
                // Muestra un mensaje de la acci�n correspondiente.
                std::cout << "Listado de Inventario" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opci�n 2.
            case 2:
                // Muestra un mensaje de la acci�n correspondiente.
                std::cout << "Agregar Inventario" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opci�n 3.
            case 3:
                // Muestra un mensaje de salida.
                std::cout << "Salida del Sistema" << std::endl;
                // Termina el caso.
                break;
                // Bloque por defecto para opciones no v�lidas.
            default:
                // Informa al usuario que la opci�n no existe.
                std::cout << "No existe esta opcion" << std::endl;
                // Termina el caso.
                break;
            }
        }
        // El bucle contin�a mientras la opci�n sea diferente de "3".
    } while (opcion != "3");
}

// TIPO: Procedimiento
// REALIZA: Muestra el men� principal de la aplicaci�n y permite navegar a los diferentes subm�dulos.
// PAR�METROS: Ninguno.
// REGRESA: Nada (void).
void MenuPrincipal() {
    // Declara una variable entera para la opci�n del men�.
    int opcion = 0;
    // Declara una bandera booleana para controlar la salida del men� principal.
    bool salida = false;
    // Define un arreglo constante con las opciones del men� principal.
    static const std::string datosmenuprincipal[] = { "1.-Productos ", "2.-Punto de Venta ", "3.-Inventario ","4.-Ventas ", "5.-Salida " };
    // Inicia un bucle while que se ejecutar� mientras la bandera 'salida' sea falsa.
    while (!salida) {
        // Muestra el men� principal y guarda la opci�n del usuario como una cadena.
        std::string opcionStr = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Peque�a", datosmenuprincipal, 5);

        // Verifica si la opci�n introducida est� vac�a.
        if (opcionStr.empty()) {
            // Informa al usuario de la opci�n incorrecta.
            std::cout << "opcion incorrecta " << std::endl;
        }
        else {
            // Convierte solo el primer car�cter de la cadena a un entero. Esto permite que entradas como "1." o "1-.." funcionen.
            opcion = std::stoi(opcionStr.substr(0, 1));
            // Eval�a la opci�n num�rica en un switch.
            switch (opcion) {
                // Caso para la opci�n 1.
            case 1:
                // Llama al procedimiento que gestiona el men� de productos.
                MenuProductos();
                // Termina el caso.
                break;
                // Caso para la opci�n 2.
            case 2:
                // Llama al procedimiento del punto de venta, iniciando con el ticket "000".
                MenuPuntoVenta("000");
                // Termina el caso.
                break;
                // Caso para la opci�n 3.
            case 3:
                // Llama al procedimiento que gestiona el men� de inventario.
                MenuInventario();
                // Termina el caso.
                break;
                // Caso para la opci�n 4.
            case 4:
                // Muestra un mensaje para la secci�n de ventas.
                std::cout << "Ventas" << std::endl;
                // Termina el caso.
                break;
                // Caso para la opci�n 5.
            case 5:
                // Muestra un mensaje de salida del sistema.
                std::cout << "Salida del Sistema " << std::endl;
                // Cambia la bandera 'salida' a verdadero para terminar el bucle while.
                salida = true;
                // Termina el caso.
                break;
                // Bloque por defecto para opciones no v�lidas.
            default:
                // Informa al usuario que la opci�n no existe.
                std::cout << "No existe esta opcion " << std::endl;
                // Termina el caso.
                break;
            }
        }
    }
}

// TIPO: Funci�n (principal)
// REALIZA: Es el punto de entrada del programa.
// PAR�METROS: Ninguno.
// REGRESA: Un entero (0 si finaliza con �xito).
int main()
{
    // Imprime un mensaje inicial en la consola.
    std::cout << "Principal 3!\n";
    // Llama al procedimiento del men� principal para iniciar la aplicaci�n.
    MenuPrincipal();
}