#include <iostream>
#include <string>
#include <iomanip> // Para std::setw y std::left
#include <sstream> // Para std::stringstream
#include <chrono> // Para obtener la fecha y hora actuales
#include <iomanip> // Para formatear la fecha
#include <vector>

using namespace std;

string productos[10][4];


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

void CargarProductos(string(*productos)[4]) {
    productos[0][0] = "001"; productos[0][1] = "Arroz 1kg"; productos[0][2] = "35"; productos[0][3] = "10";
    productos[1][0] = "002"; productos[1][1] = "Az�car 1kg"; productos[1][2] = "25"; productos[1][3] = "10";
    productos[2][0] = "003"; productos[2][1] = "Harina 1kg"; productos[2][2] = "28"; productos[2][3] = "10";
    productos[3][0] = "004"; productos[3][1] = "Aceite 1L"; productos[3][2] = "50"; productos[3][3] = "10";
    productos[4][0] = "005"; productos[4][1] = "Leche 1L"; productos[4][2] = "35"; productos[4][3] = "10";
    productos[5][0] = "006"; productos[5][1] = "Huevos 12 unidades"; productos[5][2] = "45"; productos[5][3] = "10";
    productos[6][0] = "007"; productos[6][1] = "Fideos 500g"; productos[6][2] = "20"; productos[6][3] = "10";
    productos[7][0] = "008"; productos[7][1] = "Sal 1kg"; productos[7][2] = "15"; productos[7][3] = "10";
    productos[8][0] = "009"; productos[8][1] = "Pasta de tomate 400g"; productos[8][2] = "25"; productos[8][3] = "10";
    productos[9][0] = "010"; productos[9][1] = "At�n lata 170g"; productos[9][2] = "35"; productos[9][3] = "10";
}

string MostrarProducto(string vproducto[4]) {
    // Recibe los datos del producto en un arreglo
    string codigo = RellenarEspacios(vproducto[0], 5);
    string producto = RellenarEspacios(vproducto[1], 30);
    string precio = RellenarEspacios(vproducto[2], 10);
    string cantidad = RellenarEspacios(vproducto[3], 10);

    // Llamamos al m�todo RellenarEspacios() para rellenar los espacios en blanco
    // de las variables codigo, producto, precio y cantidad.
    string cadena = codigo + producto + precio + cantidad;
    // Crea una cadena que contiene los valores de las variables

    return cadena;
}

string MostrarLista(string vproductos[10][4]) {
    string salida = "";  // Inicializa una cadena vac�a para almacenar el resultado final

    // Recorre cada fila de la matriz producto
    for (int ciclo = 0; ciclo < 10; ciclo++) {
        // Extrae los datos del producto en la fila actual
        string vproducto[4] = { vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3] };

        // Llama al m�todo MostrarProducto para formatear el producto en una cadena
        string cadena = MostrarProducto(vproducto);

        // A�ade la cadena formateada a la salida, seguida de un salto de l�nea
        salida = salida + cadena + "\n";
    }

    // Devuelve la cadena resultante que contiene todos los productos formateados
    return salida;
}

int ExisteProducto(string codigo, string vproductos[10][4]) {
    int enc = -1;   // Inicializa enc con -1, indicando que el producto no se ha encontrado a�n
    int pos = 0;    // Inicializa pos con 0, que ser� la posici�n inicial en la matriz
    int tam = 10;   // Tama�o de la matriz de productos (10 productos)

    // Recorre la matriz de productos
    for (int ciclo = 0; ciclo < tam; ciclo++) {
        // Compara el c�digo del producto actual con el c�digo buscado
        // Si son iguales, asigna la posici�n actual a enc
        if (vproductos[ciclo][0] == codigo) {
            enc = pos;
        }
        // Incrementa la posici�n para la siguiente iteraci�n
        pos++;
    }

    // Devuelve la posici�n del producto encontrado o -1 si no se encontr�
    return enc;
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


void ModificarProducto(std::string vproductos[10][4]) {
    std::string codigo, precio;
    int posicion;

    // Mostrar lista de productos
    std::string info = MostrarLista(vproductos);

    // Pedir el c�digo del producto a modificar
    std::cout << info << "\nIntroduce el c�digo del producto a modificar: ";
    std::getline(std::cin, codigo);

    if (!codigo.empty()) {
        // Buscar la posici�n del producto
        posicion = ExisteProducto(codigo, vproductos);

        // Si el producto existe, modificar precio
        if (posicion > -1) {
            std::string vproducto[4] = { vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2], vproductos[posicion][3] };

            // Pedir el nuevo precio
            std::cout << "\nIntroduce el nuevo precio para " << MostrarProducto(vproducto) << ": ";
            std::getline(std::cin, precio);

            if (!precio.empty()) {
                // Actualizar precio (simple validaci�n de formato num�rico)
                try {
                    std::stod(precio); // Verificar si es un n�mero v�lido
                    vproductos[posicion][2] = precio; // Actualizar el precio
                }
                catch (const std::invalid_argument&) {
                    std::cout << "El precio no es un valor num�rico v�lido.\n";
                }
            }
            else {
                std::cout << "Dato nulo. No se modific� el precio.\n";
            }
        }
        else {
            std::cout << "No existe el c�digo de producto.\n";
        }
    }
    else {
        std::cout << "Dato nulo. No se realiz� ninguna modificaci�n.\n";
    }
}
void MenuProductos(string vproductos[][4]) {
    const std::string datosmenuproductos[] = { "1.-Modificar ", "2.-Listado ", "3.-Salida " };
    std::string opcion = "0";
    do {
        opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos, 3);
        if (opcion.empty()) {
            std::cout << "opcion incorrecta " << std::endl;
        }
        else {
            switch (std::stoi(opcion)) {
            case 1:
                ModificarProducto(vproductos);
                break;
            case 2:
                std::cout << MostrarLista(vproductos) << std::endl;
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


// TIPO: Procedimiento
// REALIZA: Gestiona la interfaz y la l�gica para agregar stock (cantidad de inventario) a un producto existente.
// PAR�METROS:
//   - string vproductos[][4]: La matriz de productos que ser� consultada y modificada.
// REGRESA: Nada (void).
void AgregarStock(string vproductos[][4]) {
    // Declara cadenas para almacenar el c�digo y la cantidad que introducir� el usuario.
    string codigo, cantidad;
    // Declara un entero para almacenar la posici�n (�ndice de la fila) del producto encontrado.
    int posicion;
    // Llama a una funci�n para obtener la lista formateada de todos los productos.
    string info = MostrarLista(vproductos);
    // Muestra la lista y pide al usuario que introduzca un c�digo, usando la funci�n 'Leer' para capturar la entrada.
    codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");

    // Verifica si el usuario introdujo un c�digo (si la cadena no est� vac�a).
    if (!codigo.empty()) {
        // Busca la posici�n del producto usando el c�digo proporcionado.
        posicion = ExisteProducto(codigo, vproductos);
        // Verifica si el producto fue encontrado (si la posici�n es un �ndice v�lido, mayor que -1).
        if (posicion > -1) {
            // Crea un arreglo temporal para mostrar la informaci�n del producto (c�digo, nombre, cantidad actual).
            string vproducto[] = { vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][3], "" };
            // Pide al usuario que introduzca la cantidad de stock que desea agregar, mostrando los datos del producto.
            cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ");

            // Verifica si el usuario introdujo una cantidad.
            if (!cantidad.empty()) {
                // Eval�a si la cantidad introducida es un n�mero entero (tipo 1) o un n�mero con decimales (tipo 2).
                if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1)) {
                    // Convierte la cantidad ingresada y la cantidad existente a enteros, las suma, y convierte el resultado de nuevo a cadena.
                    string nuevacantidad = std::to_string(std::stoi(cantidad) + std::stoi(vproducto[2]));
                    // Actualiza la cantidad en la matriz original de productos (en la columna de stock, que es la 3).
                    vproductos[posicion][3] = nuevacantidad;
                }
                // Si la cantidad introducida no es un n�mero,
                else {
                    // informa al usuario del error.
                    std::cout << "no es un valor numerico" << std::endl;
                }
            }
            // Si el usuario no introdujo una cantidad,
            else {
                // informa que el dato es nulo.
                std::cout << "dato nulo" << std::endl;
            }
        }
        // Si el producto no fue encontrado,
        else {
            // informa que el c�digo no existe.
            std::cout << "no existe el codigo" << std::endl;
        }
    }
    // Si el usuario no introdujo un c�digo,
    else {
        // informa que el dato es nulo.
        std::cout << "dato nulo" << std::endl;
    }
}

// TIPO: Procedimiento
// REALIZA: Muestra el men� de opciones para la gesti�n del inventario y maneja la selecci�n del usuario.
// PAR�METROS:
//   - string vproductos[][4]: La matriz de productos, que se pasar� a las funciones de listado y modificaci�n de stock.
// REGRESA: Nada (void).
void MenuInventario(string vproductos[][4]) {
    // Define un arreglo constante con las opciones de texto que se mostrar�n en el men�.
    const std::string datosmenuinventario[] = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
    // Declara una cadena para almacenar la opci�n del usuario, inicializada para que el bucle comience.
    std::string opcion = "0";
    // Inicia un bucle do-while que se ejecutar� al menos una vez y continuar� hasta que el usuario elija salir (opci�n "3").
    do {
        // Llama a una funci�n para mostrar el men� y capturar la respuesta del usuario.
        opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario, 3);
        // Verifica si la opci�n ingresada por el usuario est� vac�a.
        if (opcion.empty()) {
            // Si est� vac�a, muestra un mensaje de error.
            std::cout << "opcion incorrecta" << std::endl;
        }
        else {
            // Si no est� vac�a, eval�a la opci�n del usuario con una estructura switch.
            switch (std::stoi(opcion)) {
                // Si la opci�n es 1 (Listado),
            case 1:
                // llama a la funci�n que muestra la lista de productos y la imprime en la consola.
                std::cout << MostrarLista(vproductos) << std::endl;
                // Termina este caso.
                break;
                // Si la opci�n es 2 (Agregar),
            case 2:
                // llama al procedimiento para agregar stock a un producto.
                AgregarStock(vproductos);
                // Termina este caso.
                break;
                // Si la opci�n es 3 (Salida),
            case 3:
                // muestra un mensaje de despedida. El bucle terminar� debido a la condici�n del 'while'.
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
        // El bucle se repite mientras la opci�n seleccionada por el usuario no sea "3".
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
                MenuProductos(vproductos);
                break;
            case 2:
                MenuPuntoVenta("000");
                break;
            case 3:
                MenuInventario(vproductos);
                // Llama al procedimiento del men� de inventario, pas�ndole la base de datos de productos para que pueda gestionarla.
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
    CargarProductos(productos);
    MenuPrincipal(productos);
}


