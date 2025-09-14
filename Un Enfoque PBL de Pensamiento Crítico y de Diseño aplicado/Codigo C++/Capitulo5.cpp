
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

string productos[10][4];
// Declara una matriz global para almacenar hasta 10 productos, con 4 atributos para cada uno (ej: C�digo, Nombre, Precio, Cantidad).


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

std::string Dialogo(const std::string texto) {
    std::string cadena;
    std::cout << texto << " : ";
    std::getline(std::cin, cadena);
    return cadena;
}

string DesplegarMenu(const string Titulo1, const string opciones[], int tamano) {
    string cadena;
    cadena = Titulo1 + "\n" + "\n";
    cadena += MostrarMenu(opciones, tamano);
    cadena += "\n Que opcion deseas ";
    cadena = Dialogo(cadena);
    return cadena;
}


std::string Leer(const std::string texto) {
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

bool EsNumeroEntero(const string dato) {
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


bool EsNumeroDouble(const std::string dato) {
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

bool EvaluarNumerico(const std::string dato, int tipo) {
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

std::string RellenarEspacios(std::string dato, int tamano) {
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

std::string IdTicketSiguiente(const std::string idticket) {
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



int ObtenerUltimaPosicion(const std::string matriz[][5], int filas) {
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
// REALIZA: Inicializa o "carga" una matriz de productos con datos predefinidos (hardcodeados).
// PAR�METROS:
//   - string(*productos)[4]: Es un puntero a un arreglo de 4 strings. En la pr�ctica, permite pasar la matriz 'productos' para que esta funci�n la modifique directamente.
// REGRESA: Nada (void).
void CargarProductos(string(*productos)[4]) {
    // Asigna los datos para el primer producto (fila 0) en sus respectivas columnas (0:c�digo, 1:nombre, 2:precio, 3:cantidad).
    productos[0][0] = "001"; productos[0][1] = "Arroz 1kg"; productos[0][2] = "35"; productos[0][3] = "10";
    // Asigna los datos para el segundo producto (fila 1).
    productos[1][0] = "002"; productos[1][1] = "Az�car 1kg"; productos[1][2] = "25"; productos[1][3] = "10";
    // Asigna los datos para el tercer producto (fila 2).
    productos[2][0] = "003"; productos[2][1] = "Harina 1kg"; productos[2][2] = "28"; productos[2][3] = "10";
    // Asigna los datos para el cuarto producto (fila 3).
    productos[3][0] = "004"; productos[3][1] = "Aceite 1L"; productos[3][2] = "50"; productos[3][3] = "10";
    // Asigna los datos para el quinto producto (fila 4).
    productos[4][0] = "005"; productos[4][1] = "Leche 1L"; productos[4][2] = "35"; productos[4][3] = "10";
    // Asigna los datos para el sexto producto (fila 5).
    productos[5][0] = "006"; productos[5][1] = "Huevos 12 unidades"; productos[5][2] = "45"; productos[5][3] = "10";
    // Asigna los datos para el s�ptimo producto (fila 6).
    productos[6][0] = "007"; productos[6][1] = "Fideos 500g"; productos[6][2] = "20"; productos[6][3] = "10";
    // Asigna los datos para el octavo producto (fila 7).
    productos[7][0] = "008"; productos[7][1] = "Sal 1kg"; productos[7][2] = "15"; productos[7][3] = "10";
    // Asigna los datos para el noveno producto (fila 8).
    productos[8][0] = "009"; productos[8][1] = "Pasta de tomate 400g"; productos[8][2] = "25"; productos[8][3] = "10";
    // Asigna los datos para el d�cimo producto (fila 9).
    productos[9][0] = "010"; productos[9][1] = "At�n lata 170g"; productos[9][2] = "35"; productos[9][3] = "10";
}

// TIPO: Funci�n
// REALIZA: Formatea los datos de un �nico producto en una sola cadena de texto con espacios de relleno para lograr una alineaci�n de columnas.
// PAR�METROS:
//   - string vproducto[4]: Un arreglo que contiene los 4 atributos (c�digo, nombre, precio, cantidad) de un solo producto.
// REGRESA: Una cadena de texto (string) con la informaci�n del producto formateada en una sola l�nea.
string MostrarProducto(string vproducto[4]) {
    // Llama a una funci�n 'RellenarEspacios' para formatear el c�digo del producto a un ancho de 5 caracteres.
    string codigo = RellenarEspacios(vproducto[0], 5);
    // Formatea el nombre del producto a un ancho de 30 caracteres.
    string producto = RellenarEspacios(vproducto[1], 30);
    // Formatea el precio del producto a un ancho de 10 caracteres.
    string precio = RellenarEspacios(vproducto[2], 10);
    // Formatea la cantidad del producto a un ancho de 10 caracteres.
    string cantidad = RellenarEspacios(vproducto[3], 10);

    // Concatena (une) todas las cadenas formateadas en una sola.
    string cadena = codigo + producto + precio + cantidad;
    // Devuelve la cadena final con el producto formateado.
    return cadena;
}

// TIPO: Funci�n
// REALIZA: Genera una lista completa y formateada de todos los productos de la matriz.
// PAR�METROS:
//   - string vproductos[10][4]: La matriz que contiene los datos de los 10 productos.
// REGRESA: Una cadena de texto (string) que contiene la lista de todos los productos, cada uno en una nueva l�nea.
string MostrarLista(string vproductos[10][4]) {
    // Inicializa una cadena vac�a que acumular� la lista completa.
    string salida = "";
    // Inicia un bucle 'for' que se repetir� 10 veces (para cada producto, de la fila 0 a la 9).
    for (int ciclo = 0; ciclo < 10; ciclo++) {
        // Crea un arreglo temporal 'vproducto' para almacenar los datos de la fila actual.
        string vproducto[4] = { vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3] };

        // Llama a la funci�n 'MostrarProducto' para formatear los datos del producto actual en una sola l�nea.
        string cadena = MostrarProducto(vproducto);

        // Agrega la l�nea del producto formateado a la cadena 'salida', seguida de un salto de l�nea (\n).
        salida = salida + cadena + "\n";
    }

    // Devuelve la cadena 'salida' que ahora contiene la lista completa y formateada.
    return salida;
}

void MenuPuntoVenta(std::string idticket) {
    std::string opcion, membrete;
    bool pago = false;
    idticket = IdTicketSiguiente(idticket);
    std::string fechadia = Fecha();
    membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
    membrete += "\n-----------------------------------------------------\n";
    const std::string datosmenu[] = { "1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida " };

    do {
        opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu, 5);
        if (opcion.empty()) {
            std::cout << "dato incorrecto introducido" << std::endl;
        }
        else {
            switch (std::stoi(opcion)) {
            case 1:
                std::cout << "Agregar Articulo al Ticket" << std::endl;
                break;
            case 2:
                std::cout << "Eliminar Articulo del Ticket" << std::endl;
                break;
            case 3:
                std::cout << "Listado de Articulos del Ticket" << std::endl;
                break;
            case 4:
                std::cout << "Pagar Ticket y salir" << std::endl;
                opcion = "5";
                pago = true;
                break;
            case 5:
                std::cout << "Salida del Ventas" << std::endl;
                if (!pago) {
                    std::cout << "No pago el ticket" << std::endl;
                    std::cout << "eliminando ticket " << idticket << std::endl;
                }
                break;
            default:
                std::cout << "No existe esta opcion" << std::endl;
                break;
            }
        }
    } while (opcion != "5");
}

// TIPO: Funci�n
// REALIZA: Busca un producto en la matriz por su c�digo.
// PAR�METROS:
//   - string codigo: El c�digo del producto que se desea encontrar.
//   - string vproductos[10][4]: La matriz que contiene todos los productos.
// REGRESA: Un entero (int). Devuelve el �ndice (la posici�n o fila) del producto si lo encuentra; de lo contrario, devuelve -1.
int ExisteProducto(string codigo, string vproductos[10][4]) {
    // Inicializa 'enc' en -1. Este ser� el valor de retorno si no se encuentra el producto.
    int enc = -1;
    // Inicializa 'pos' en 0 para llevar la cuenta de la fila actual (�ndice).
    int pos = 0;
    // Define el tama�o de la matriz para controlar el bucle.
    int tam = 10;

    // Inicia un bucle 'for' que recorrer� cada fila de la matriz de productos.
    for (int ciclo = 0; ciclo < tam; ciclo++) {
        // Compara el c�digo del producto en la fila actual (columna 0) con el c�digo buscado.
        if (vproductos[ciclo][0] == codigo) {
            // Si los c�digos coinciden, asigna la posici�n actual (el valor de 'pos') a 'enc'.
            enc = pos;
        }
        // Incrementa el contador de posici�n para la siguiente fila.
        pos++;
    }

    // Devuelve 'enc', que contendr� el �ndice del producto si fue encontrado, o -1 si no.
    return enc;
}

// TIPO: Procedimiento
// REALIZA: Gestiona la interfaz y la l�gica para modificar el precio de un producto.
// PAR�METROS:
//   - std::string vproductos[10][4]: La matriz de productos que ser� consultada y potencialmente modificada.
// REGRESA: Nada (void).
void ModificarProducto(std::string vproductos[10][4]) {
    // Declara cadenas para almacenar el c�digo y el nuevo precio que introducir� el usuario.
    std::string codigo, precio;
    // Declara un entero para almacenar la posici�n (�ndice) del producto encontrado.
    int posicion;

    // Llama a la funci�n 'MostrarLista' para obtener la lista formateada de todos los productos.
    std::string info = MostrarLista(vproductos);

    // Muestra la lista de productos y solicita al usuario que ingrese el c�digo a modificar.
    std::cout << info << "\nIntroduce el c�digo del producto a modificar: ";
    // Lee la l�nea completa introducida por el usuario y la guarda en 'codigo'.
    std::getline(std::cin, codigo);

    // Comprueba si el usuario introdujo alg�n dato.
    if (!codigo.empty()) {
        // Llama a 'ExisteProducto' para buscar la posici�n del c�digo introducido.
        posicion = ExisteProducto(codigo, vproductos);

        // Comprueba si el producto fue encontrado (si la posici�n es mayor que -1).
        if (posicion > -1) {
            // Crea un arreglo temporal con los datos del producto encontrado para mostrarlo f�cilmente.
            std::string vproducto[4] = { vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2], vproductos[posicion][3] };

            // Pide al usuario que introduzca el nuevo precio para el producto seleccionado.
            std::cout << "\nIntroduce el nuevo precio para " << MostrarProducto(vproducto) << ": ";
            // Lee el nuevo precio introducido por el usuario.
            std::getline(std::cin, precio);

            // Comprueba si el usuario introdujo un precio.
            if (!precio.empty()) {
                // Inicia un bloque try-catch para validar que el precio sea un n�mero.
                try {
                    // Intenta convertir la cadena 'precio' a un n�mero de tipo double. Si falla, lanzar� una excepci�n.
                    std::stod(precio);
                    // Si la conversi�n fue exitosa, actualiza el precio en la matriz original (en la columna 2).
                    vproductos[posicion][2] = precio;
                }
                // Si ocurre una excepci�n de tipo 'invalid_argument' (el texto no era un n�mero),
                catch (const std::invalid_argument&) {
                    // informa al usuario que el valor no es v�lido.
                    std::cout << "El precio no es un valor num�rico v�lido.\n";
                }
            }
            // Si el campo de precio se dej� vac�o,
            else {
                // informa al usuario que no se realiz� ninguna modificaci�n.
                std::cout << "Dato nulo. No se modific� el precio.\n";
            }
        }
        // Si 'ExisteProducto' devolvi� -1,
        else {
            // informa al usuario que el c�digo no se encontr�.
            std::cout << "No existe el c�digo de producto.\n";
        }
    }
    // Si el campo de c�digo se dej� vac�o,
    else {
        // informa al usuario que no se realiz� ninguna acci�n.
        std::cout << "Dato nulo. No se realiz� ninguna modificaci�n.\n";
    }
}

// TIPO: Procedimiento
// REALIZA: Muestra el men� de opciones para la gesti�n de productos y maneja la selecci�n del usuario.
// PAR�METROS:
//   - string vproductos[][4]: La matriz de productos, que se pasar� a otras funciones como ModificarProducto y MostrarLista.
// REGRESA: Nada (void).
void MenuProductos(string vproductos[][4]) {
    // Define un arreglo constante con las opciones que se mostrar�n en el men�.
    const std::string datosmenuproductos[] = { "1.-Modificar ", "2.-Listado ", "3.-Salida " };
    // Declara una cadena para almacenar la opci�n del usuario, inicializada para que el bucle comience.
    std::string opcion = "0";
    // Inicia un bucle do-while que se ejecutar� al menos una vez y continuar� hasta que el usuario elija salir.
    do {
        // Llama a 'DesplegarMenu' para mostrar las opciones y capturar la respuesta del usuario.
        opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos, 3);
        // Verifica si la opci�n ingresada est� vac�a.
        if (opcion.empty()) {
            // Si est� vac�a, muestra un mensaje de error.
            std::cout << "opcion incorrecta " << std::endl;
        }
        else {
            // Si no est� vac�a, eval�a la opci�n del usuario con una estructura switch.
            switch (std::stoi(opcion)) {
                // Si la opci�n es 1,
            case 1:
                // llama a la funci�n para modificar un producto.
                ModificarProducto(vproductos);
                // Termina este caso.
                break;
                // Si la opci�n es 2,
            case 2:
                // llama a la funci�n que muestra la lista de productos y la imprime en la consola.
                std::cout << MostrarLista(vproductos) << std::endl;
                // Termina este caso.
                break;
                // Si la opci�n es 3,
            case 3:
                // muestra un mensaje de despedida. La condici�n del bucle while se encargar� de terminar.
                std::cout << "Salida del Sistema" << std::endl;
                // Termina este caso.
                break;
                // Si la opci�n no es ninguna de las anteriores,
            default:
                // informa al usuario que la opci�n no es v�lida.
                std::cout << "No existe esta opcion" << std::endl;
                // Termina este caso.
                break;
            }
        }
        // El bucle se repite mientras la opci�n seleccionada no sea "3".
    } while (opcion != "3");
}


void MenuInventario() {
    const std::string datosmenuinventario[] = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
    std::string opcion = "0";
    do {
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario, 3);
        if (opcion.empty()) {
            std::cout << "opcion incorrecta" << std::endl;
        }
        else {
            switch (std::stoi(opcion)) {
            case 1:
                std::cout << "Listado de Inventario" << std::endl;
                break;
            case 2:
                std::cout << "Agregar Inventario" << std::endl;
                break;
            case 3:
                std::cout << "Salida del Sistema" << std::endl;
                break;
            default:
                std::cout << "No existe esta opcion" << std::endl;
                break;
            }
        }
    } while (opcion != "3");
}

void MenuPrincipal(string vproductos[][4]) {
    int opcion = 0;
    bool salida = false;
    static const std::string datosmenuprincipal[] = { "1.-Productos ", "2.-Punto de Venta ", "3.-Inventario ","4.-Ventas ", "5.-Salida " };
    while (!salida) {
        std::string opcionStr = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Peque�a", datosmenuprincipal, 5);

        if (opcionStr.empty()) {
            std::cout << "opcion incorrecta " << std::endl;
        }
        else {
            opcion = std::stoi(opcionStr.substr(0, 1)); // Obtener el primer d�gito como entero
            switch (opcion) {
            case 1:
                // Llama al procedimiento que gestiona el men� de productos, pas�ndole la base de datos de productos.
                MenuProductos(vproductos);
                break;
            case 2:
                MenuPuntoVenta("000");
                break;
            case 3:
                MenuInventario();
                break;
            case 4:
                std::cout << "Ventas" << std::endl;
                break;
            case 5:
                std::cout << "Salida del Sistema " << std::endl;
                salida = true;
                break;
            default:
                std::cout << "No existe esta opcion " << std::endl;
                break;
            }
        }
    }
}


int main()
{
    // Inicializa la matriz 'productos' con los datos predefinidos antes de empezar.
    CargarProductos(productos);
    // Inicia el men� principal de la aplicaci�n, d�ndole acceso a la base de datos de productos ya cargada.
    MenuPrincipal(productos);
}

