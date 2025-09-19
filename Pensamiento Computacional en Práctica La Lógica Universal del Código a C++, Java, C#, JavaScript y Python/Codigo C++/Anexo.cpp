// Incluye la librer�a para manejar la entrada y salida de datos est�ndar (Input/Output Stream).
// Te permite usar 'std::cout' para imprimir en la consola y 'std::cin' para leer desde el teclado.
#include <iostream>

// Incluye la librer�a para trabajar con cadenas de texto.
// Proporciona la clase `std::string`, que es fundamental para manipular casi todos los datos del programa.
#include <string>

// Incluye la librer�a de manipuladores de entrada/salida (Input/Output Manipulators).
// Sirve para formatear la salida, por ejemplo, con `std::setw()` para definir el ancho de un texto
// o `std::left` para alinearlo, creando columnas ordenadas en los listados.
#include <iomanip>

// Incluye la librer�a para usar flujos de cadenas de texto (String Stream).
// Es muy �til para construir cadenas complejas combinando texto y n�meros,
// como cuando generas el formato de un ticket o una fecha.
#include <sstream>

// Incluye la librer�a para trabajar con el tiempo (fechas, horas, duraciones).
// La usas en tu funci�n `Fecha()` para obtener la hora y fecha actuales del sistema.
#include <chrono>

// Incluye la librer�a para usar 'vectores', que son arreglos que pueden cambiar de tama�o din�micamente.
// Aunque est� incluido, tu c�digo actual utiliza principalmente arreglos de tama�o fijo (ej: `string productos[10][4]`).
#include <vector>

// Incluye la librer�a para manejar archivos (File Stream).
// Permite leer datos desde archivos (`ifstream`) y escribir datos en archivos (`ofstream`),
// lo cual es fundamental para guardar y cargar el inventario o el historial de ventas.
#include <fstream>


using namespace std;

string productos[10][4];

const int tamventas = 100;
int posventas = -1;
string ventas[tamventas][5];
string fechas;


std::string MostrarMenu(const string opciones[], int tamano) {
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


string UltimoTicket(int pos, string mventa[][5]) {
    string idticket = "000";
    if (pos > -1) {
        idticket = mventa[pos][0];
    }
    return idticket;
}




void CrearTicket(std::string(*ticket)[4]) {
    // Inicializar la matriz con cadenas vac�as
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 4; ++j) {
            ticket[i][j] = "";
        }
    }
}

int ExisteTicketCodigo(std::string mticket[][4], std::string codigo, int filas) {
    int enc = -1;
    int pos = ObtenerUltimaPosicion4(mticket, filas);
    std::cout << "buscando " << codigo << " tama�o arreglo " << pos << std::endl;
    for (int ciclo = 0; ciclo <= pos; ciclo++) {
        if (mticket[ciclo][0].compare(codigo) == 0) {
            enc = ciclo;
            return enc;
        }
    }
    return enc;
}

bool InsertarProductoTicket(string mticket[][4], string datos[4], int tamticket) {
    bool sucedio = true;
    int posticket = ObtenerUltimaPosicion4(mticket, tamticket);
    int enc = ExisteTicketCodigo(mticket, datos[0], tamticket);
    if (posticket < tamticket) {
        if (enc > -1) {
            cout << "Ya existe el producto en el ticket, lo incrementare" << endl;
            int cantidadactual = stoi(mticket[enc][3]);
            mticket[enc][3] = to_string(cantidadactual + 1);
        }
        else {
            posticket++;
            mticket[posticket][0] = datos[0];
            mticket[posticket][1] = datos[1];
            mticket[posticket][2] = datos[2];
            mticket[posticket][3] = datos[3];
            cout << "Insertando, no existe el producto en el ticket" << endl;
        }
    }
    else {
        sucedio = false;
    }
    return sucedio;
}

string TotalProducto(string precio, string cantidad) {
    double total = stod(precio) * stod(cantidad);
    stringstream stream;
    stream << fixed << setprecision(2) << total;
    return stream.str();
}

string MostrarProductoTicket(string mticket[][4], int pos) {
    string codigo = RellenarEspacios(mticket[pos][0], 5);
    string producto = RellenarEspacios(mticket[pos][1], 30);
    string precio = RellenarEspacios(mticket[pos][2], 10);
    string cantidad = RellenarEspacios(mticket[pos][3], 5);
    string totalproducto = RellenarEspacios(TotalProducto(mticket[pos][2], mticket[pos][3]), 10);
    string cadena = codigo + producto + precio + cantidad + totalproducto;
    return cadena;
}

std::string MostrarTicket(std::string mticket[][4], int filas) {
    std::string salida = "";
    int pos = ObtenerUltimaPosicion4(mticket, filas);
    for (int ciclo = 0; ciclo <= pos; ciclo++) {
        salida += MostrarProductoTicket(mticket, ciclo) + "\n";
    }
    return salida;
}

double SubTotalTicket(std::string mticket[][4], int filas) {
    double subtotal = 0;
    double valor;
    int pos = ObtenerUltimaPosicion4(mticket, filas);
    for (int ciclo = 0; ciclo <= pos; ciclo++) {
        double valor;
        std::istringstream(TotalProducto(mticket[ciclo][2], mticket[ciclo][3])) >> valor;
        subtotal = subtotal + valor;
    }
    return subtotal;
}

double IvaTicket(std::string mticket[][4], int filas) {
    double subtotal = SubTotalTicket(mticket, filas);
    if (subtotal > 0)
        subtotal = 0.16 * subtotal;
    else
        subtotal = -1;
    return subtotal;
}

double TotalTicket(std::string mticket[][4], int filas) {
    double total = SubTotalTicket(mticket, filas);
    if (total > 0)
        total = IvaTicket(mticket, filas) + total;
    return total;
}

std::string MostrarTicketVenta(std::string mticket[][4], std::string idticket, const std::string fecha, int fila) {
    std::ostringstream salida;
    std::ostringstream subtotalStream, ivaStream, totalStream;

    subtotalStream << std::fixed << std::setprecision(2) << SubTotalTicket(mticket, fila);
    ivaStream << std::fixed << std::setprecision(2) << IvaTicket(mticket, fila);
    totalStream << std::fixed << std::setprecision(2) << TotalTicket(mticket, fila);

    std::string subtotal = subtotalStream.str();
    std::string iva = ivaStream.str();
    std::string total = totalStream.str();

    salida << "Fecha " << fecha << " Ticket No." << idticket;
    salida << "\n" << MostrarTicket(mticket, fila);
    salida << "\n\n El total sin iva " << subtotal;
    salida << "\n el iva total es " << iva;
    salida << "\n el total de la venta fue " << total;

    return salida.str();
}

std::string MostrarListaProductosVenta(std::string vproductos[][4], int filas) {
    std::string salida;
    for (int ciclo = 0; ciclo < filas; ciclo++) {
        int existencia;
        std::istringstream(vproductos[ciclo][3]) >> existencia;
        if (existencia > 0) {

            std::string vproducto[4];
            for (int i = 0; i < 4; i++) {
                vproducto[i] = vproductos[ciclo][i];
            }
            std::string cadena = MostrarProducto(vproducto);
            salida += cadena + "\n";
        }
    }
    return salida;
}


void CapturaVentaProducto(string mticket[][4], string mproductos[][4], string idticket, int tamticket) {
    string codigo, info;
    info = MostrarListaProductosVenta(mproductos, 10);

    cout << info << "\nIntroduce el codigo del producto: ";
    getline(cin, codigo);
    if (!codigo.empty()) {
        int posp = ExisteProducto(codigo, mproductos);
        if (posp > -1) {
            int cant = stoi(mproductos[posp][3]);
            if (cant > 0) {
                string producto[4];
                for (int i = 0; i < 4; i++) {
                    producto[i] = mproductos[posp][i];
                }
                cant--;
                mproductos[posp][3] = to_string(cant);
                cout << MostrarProducto(producto) << endl;

                string venta[4] = { mproductos[posp][0], mproductos[posp][1], mproductos[posp][2], "1" };
                if (!InsertarProductoTicket(mticket, venta, tamticket)) {
                    cout << "El arreglo esta lleno\n";
                }
            }
            else {
                cout << "No hay productos para venta" << endl;
            }
        }
        else {
            cout << "El codigo no existe, no se puede agregar\n";
        }
    }
    else {
        cout << "Dato nulo\n";
    }
}

void RemoverProductoTicket(string mticket[][4], int pos, int filas) {
    int tam = ObtenerUltimaPosicion4(mticket, filas);
    if (tam > pos) {
        for (int i = pos; i < tam; i++) {
            for (int j = 0; j < 4; j++) {
                mticket[i][j] = mticket[i + 1][j];
            }
        }
        for (int j = 0; j < 4; j++) {
            mticket[tam][j] = ""; // Se usa una cadena vac�a en lugar de null
        }
    }
    else {
        mticket[pos][0] = ""; // Se usa una cadena vac�a en lugar de null
    }
}

void EliminarProductoTicket(string mticket[][4], int pos, int filas) {
    int cantidad = stoi(mticket[pos][3]);
    if (cantidad > 1)
        mticket[pos][3] = to_string(cantidad - 1);
    else
        RemoverProductoTicket(mticket, pos, filas);
}

void Eliminar(string mticket[][4], string mproductos[][4], int filas) {
    string codigo, info;
    info = MostrarTicket(mticket, filas);
    cout << info << "\nIntroduce el codigo del producto: ";
    getline(cin, codigo);

    if (!codigo.empty()) {
        int pos = ExisteTicketCodigo(mticket, codigo, filas);
        if (pos > -1) {
            int posproducto = ExisteProducto(codigo, mproductos);
            string nuevacantidad = to_string(stoi(mproductos[posproducto][3]) + 1);
            mproductos[posproducto][3] = nuevacantidad;
            RemoverProductoTicket(mticket, pos, filas);
        }
    }
    else {
        cout << "Dato nulo" << endl;
    }
}

void AgregarProductoAVenta(std::string mticket[][4], int tamTicket, std::string mventa[][5], int tamVenta, std::string idticket) {
    int posventas = ObtenerUltimaPosicion5(mventa, tamVenta);
    int posticket = ObtenerUltimaPosicion4(mticket, tamTicket);
    for (int i = 0; i <= posticket; i++) {
        if (!mticket[i][0].empty()) { // Verificar que la fila no est� vac�a
            posventas++;
            mventa[posventas][0] = idticket; // Establecer el ID del ticket
            mventa[posventas][1] = mticket[i][0]; // C�digo del producto
            mventa[posventas][2] = mticket[i][1]; // Nombre del producto
            mventa[posventas][3] = mticket[i][2]; // Precio del producto
            mventa[posventas][4] = mticket[i][3]; // Cantidad del producto
            // Incrementar la posici�n para la pr�xima venta
        }
    }
}


void Pagar(std::string idticket, std::string mventa[][5], int tamVenta, std::string mticket[][4], int tamTicket) {
    int posventas = ObtenerUltimaPosicion5(mventa, tamVenta);
    int post = ObtenerUltimaPosicion4(mticket, tamTicket);
    if ((posventas + post) < 100) {
        AgregarProductoAVenta(mticket, tamTicket, mventa, tamVenta, idticket);
    }
    else {
        std::cout << "Desbordamiento de Memoria de ventas" << std::endl;
    }
}

void DevolucionTicket(std::string mticket[][4], int filasticket, std::string mproductos[][4]) {
    int posmticket = ObtenerUltimaPosicion4(mticket, filasticket);
    for (int pos = 0; pos <= posmticket; ++pos) {
        std::string codigo = mticket[pos][0];
        int posp = ExisteProducto(codigo, mproductos);
        if (posp > -1) {
            int cant = std::stoi(mticket[pos][3]) + std::stoi(mproductos[posp][3]);
            mproductos[posp][3] = std::to_string(cant);
        }
    }
}

string MostrarVenta(string venta[5]) {
    string idticket = RellenarEspacios(venta[0], 6);
    string codigo = RellenarEspacios(venta[1], 5);
    string producto = RellenarEspacios(venta[2], 30);
    string precio = RellenarEspacios(venta[3], 10);
    string cantidad = RellenarEspacios(venta[4], 10);
    return idticket + codigo + producto + precio + cantidad;
}

string MostrarListaVentas(string ventas[][5], int filas) {
    int posventas = ObtenerUltimaPosicion5(ventas, filas);
    string salida = "";
    for (int ciclo = 0; ciclo <= posventas; ciclo++) {
        string venta[5] = { ventas[ciclo][0], ventas[ciclo][1], ventas[ciclo][2], ventas[ciclo][3], ventas[ciclo][4] };
        salida += MostrarVenta(venta) + "\n";
    }
    return salida;
}


std::string ObtenerUltimoValorVentas(string ventas[][5], int filas) {
    int ultimaposicion = ObtenerUltimaPosicion5(ventas, filas);
    string ultimoValor = "000";
    if (ultimaposicion >= 0) {
        ultimoValor = ventas[ultimaposicion][0];
    }
    return ultimoValor;
}

void EscribirArchivoCSV(const std::string& archivo, const std::string& contenido) {
    // ios::app abre el archivo en modo de a�adir
    std::ofstream escritor(archivo, std::ios::app); // Abre en modo append (a�adir)

    if (!escritor) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }
    escritor << contenido << std::endl; // std::endl a�ade un salto de l�nea
    escritor.close();
}

bool ExisteArchivo(const std::string narchivo) {
    std::ifstream archivo(narchivo);
    return archivo.good();
}

// TIPO: Procedimiento
// REALIZA: Abre un archivo en modo de "a�adir" (append) y escribe una l�nea de contenido al final del mismo.
// PAR�METROS:
//   - const std::string& archivo: El nombre o la ruta del archivo que se va a abrir.
//   - const std::string& contenido: La cadena de texto que se va a escribir en el archivo.
// REGRESA: Nada (void).
void EscribirArchivoCSV(const std::string& archivo, const std::string& contenido) {
    // Crea un objeto 'ofstream' (flujo de salida de archivo) para escribir.
    // std::ios::app es el modo que asegura que el contenido nuevo se a�ada al final sin borrar lo anterior.
    std::ofstream escritor(archivo, std::ios::app);

    // Verifica si el archivo se pudo abrir correctamente.
    if (!escritor) {
        // Si no se pudo abrir, muestra un mensaje de error en la salida de errores est�ndar.
        std::cerr << "Error al abrir el archivo." << std::endl;
        // Termina la ejecuci�n de la funci�n.
        return;
    }
    // Escribe la cadena de 'contenido' en el archivo, seguida de un salto de l�nea.
    escritor << contenido << std::endl;
    // Cierra el archivo para liberar los recursos y asegurar que los datos se guarden correctamente.
    escritor.close();
}

// TIPO: Funci�n
// REALIZA: Comprueba si un archivo existe y es accesible para lectura.
// PAR�METROS:
//   - const std::string narchivo: El nombre o la ruta del archivo a verificar.
// REGRESA: Un booleano. 'true' si el archivo existe y se puede abrir, 'false' en caso contrario.
bool ExisteArchivo(const std::string narchivo) {
    // Intenta abrir el archivo en modo de lectura.
    std::ifstream archivo(narchivo);
    // El m�todo .good() devuelve 'true' si el archivo se abri� sin errores, indicando que existe.
    return archivo.good();
}

// TIPO: Funci�n
// REALIZA: Formatea una fila de datos para un ticket en formato CSV (valores separados por comas).
// PAR�METROS:
//   - const std::string& idticket: El n�mero del ticket.
//   - const std::string& dato1 a dato4: Los datos del producto (c�digo, nombre, precio, cantidad).
// REGRESA: Una cadena (string) con todos los datos concatenados y separados por comas.
std::string GenerarCVSFilaTicket(const std::string& idticket, const std::string& dato1, const std::string& dato2,
    const std::string& dato3, const std::string& dato4) {
    // Concatena todos los par�metros con comas para formar una l�nea de CSV.
    return idticket + "," + dato1 + "," + dato2 + "," + dato3 + "," + dato4;
}

// TIPO: Procedimiento
// REALIZA: Convierte una matriz entera de un ticket a formato CSV y la guarda en un archivo.
// PAR�METROS:
//   - const std::string matriz[tamventas][4]: La matriz con los datos del ticket.
//   - const std::string& nombrearchivo: El nombre del archivo donde se guardar�n los datos.
//   - int filas: El n�mero de filas (productos) a procesar en la matriz.
//   - const std::string& idticket: El n�mero de ticket a registrar con cada producto.
// REGRESA: Nada (void).
void GuardarDatosCsvVentaTicket(const std::string matriz[tamventas][4], const std::string& nombrearchivo, int filas, const std::string& idticket) {
    // Inicializa una cadena para acumular todo el contenido CSV.
    std::string cadena;
    // Recorre cada fila (producto) de la matriz.
    for (int fila = 0; fila < filas; ++fila) {
        // Llama a la funci�n para generar la l�nea CSV para el producto actual.
        std::string cadenafila = GenerarCVSFilaTicket(idticket, matriz[fila][0], matriz[fila][1], matriz[fila][2], matriz[fila][3]);
        // Si no es la �ltima fila, a�ade un salto de l�nea.
        if (fila + 1 < filas)
            cadena += cadenafila + "\n";
        // Si es la �ltima fila, la a�ade sin salto de l�nea final.
        else
            cadena += cadenafila;
    }
    // Llama a la funci�n para escribir la cadena completa en el archivo CSV.
    EscribirArchivoCSV(nombrearchivo, cadena);
}

// TIPO: Funci�n
// REALIZA: Lee un archivo CSV y devuelve el primer campo (el valor antes de la primera coma) de la �ltima l�nea no vac�a.
// PAR�METROS:
//   - const std::string& nombreArchivo: El nombre del archivo a leer.
// REGRESA: Una cadena (string) con el dato extra�do.
std::string LeerDatosCSV(const std::string& nombreArchivo) {
    // Inicializa la variable que guardar� el dato extra�do.
    std::string primerDato = "";
    // Declara una cadena para almacenar cada l�nea le�da.
    std::string linea;
    // Abre el archivo en modo de lectura.
    std::ifstream archivo(nombreArchivo);

    // Comprueba si el archivo se abri� correctamente.
    if (archivo.is_open()) {
        // Lee el archivo l�nea por l�nea hasta el final.
        while (getline(archivo, linea)) {
            // Elimina posibles espacios en blanco al inicio de la l�nea.
            size_t primerNoEspacio = linea.find_first_not_of(" \t\n\r\f\v");
            if (std::string::npos != primerNoEspacio) {
                linea = linea.substr(primerNoEspacio);
            }

            // Procesa la l�nea solo si no est� vac�a.
            if (!linea.empty()) {
                // Busca la posici�n de la primera coma.
                size_t posComa = linea.find(',');
                // Si se encuentra una coma,
                if (posComa != std::string::npos) {
                    // extrae el texto desde el inicio hasta la coma.
                    primerDato = linea.substr(0, posComa);
                }
                // Si no hay coma,
                else {
                    // la l�nea completa se considera el primer dato.
                    primerDato = linea;
                }
            }
        }
        // Cierra el archivo.
        archivo.close();
    }
    // Si no se pudo abrir el archivo,
    else {
        // muestra un mensaje de error.
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
    }

    // Devuelve el �ltimo 'primerDato' que se encontr� (correspondiente a la �ltima l�nea).
    return primerDato;
}

// TIPO: Funci�n
// REALIZA: Formatea una fila de datos para el historial de ventas en formato CSV usando stringstream.
// PAR�METROS:
//   - string dato1 a dato5: Los cinco campos de datos para la fila de venta.
// REGRESA: Una cadena (string) con los datos concatenados y separados por comas.
string GenerarCsvFilaVenta(string dato1, string dato2, string dato3, string dato4, string dato5) {
    // Crea un objeto stringstream para construir la cadena eficientemente.
    std::stringstream ss;
    // Inserta cada dato en el stream, separado por una coma.
    ss << dato1 << "," << dato2 << "," << dato3 << "," << dato4 << "," << dato5;
    // Convierte el contenido del stream a una cadena y la devuelve.
    return ss.str();
}

// TIPO: Procedimiento
// REALIZA: Guarda una cadena de contenido en un archivo CSV. Act�a como un envoltorio para EscribirArchivoCSV.
// PAR�METROS:
//   - string nombreArchivo: El nombre del archivo donde se guardar� el contenido.
//   - string contenido: La cadena de texto a guardar.
// REGRESA: Nada (void).
void GuardarDatosCsvVenta(string nombreArchivo, string contenido) {
    // Simplemente llama a la funci�n gen�rica de escritura en modo "a�adir".
    // La comprobaci�n 'ExisteArchivo' no es necesaria porque el modo 'append' crea el archivo si no existe.
    EscribirArchivoCSV(nombreArchivo, contenido);
}


// TIPO: Procedimiento
// REALIZA: Es el motor principal del punto de venta. Gestiona una transacci�n completa: crea un ticket,
//          permite agregar/eliminar productos, y al pagar, registra la venta tanto en la memoria del programa
//          como en archivos CSV para persistencia de datos.
// PAR�METROS:
//   - string ventas[][5]: La matriz del historial de ventas en memoria.
//   - int tamventas: El tama�o m�ximo de la matriz de ventas.
//   - string& idticket: El ID del �ltimo ticket. Se pasa por referencia (&) para que el nuevo ID se actualice fuera de la funci�n.
//   - string productos[][4]: La matriz del cat�logo de productos para consultar y modificar el stock.
//   - string narchivo: El nombre del archivo CSV donde se guardar� el detalle de los productos de cada venta.
// REGRESA: Nada (void).
void MenuPuntoVenta(string ventas[][5], int tamventas, string& idticket, string productos[][4], string narchivo) {
    // Declara una cadena para la opci�n del usuario y otra para el encabezado del men�.
    string opcion, membrete;
    // Declara una bandera para saber si el ticket fue pagado. Inicia en 'false'.
    bool pago = false;
    // Define una constante para el tama�o m�ximo de productos en un solo ticket.
    const int tamticket = 50;
    // Crea una matriz local 'Vticket' que representar� el ticket actual. Se inicializa vac�a.
    string Vticket[tamticket][4] = { {} };
    // Llama a la funci�n para generar el siguiente n�mero de ticket basado en el �ltimo.
    idticket = IdTicketSiguiente(idticket);
    // Obtiene la fecha actual para mostrarla en el ticket.
    string fechadia = Fecha();
    // Inicia un bucle 'do-while' que se repetir� hasta que el usuario elija salir (opci�n "5").
    do {
        // Construye el encabezado del men� con la fecha y el n�mero de ticket.
        membrete = "Fecha del D�a: " + fechadia + " | Ticket No: " + idticket + "\n";
        // Agrega una l�nea separadora para mayor claridad.
        membrete += "-----------------------------------------------------\n";
        // Obtiene el contenido del ticket actual en formato de texto.
        string Tickettexto = MostrarTicket(Vticket, tamticket);
        // Si el ticket ya tiene productos,
        if (!Tickettexto.empty()) {
            // los agrega al encabezado para que el usuario vea lo que lleva comprado.
            membrete += "\n" + Tickettexto + "\n";
        }
        // Define las opciones del men� de venta.
        string datosmenu[] = { "1.- Agregar", "2.- Eliminar", "3.- Listado", "4.- Pagar", "5.- Salida" };
        // Muestra el men� completo (encabezado + opciones) y captura la elecci�n del usuario.
        opcion = DesplegarMenu(membrete + "\nMen� de Punto de Venta", datosmenu, 5);

        // Verifica si la opci�n introducida est� vac�a.
        if (opcion.empty()) {
            // Si est� vac�a, informa al usuario del error.
            cout << "Dato incorrecto introducido" << endl;
        }
        // Si la opci�n no est� vac�a,
        else {
            // la eval�a en una estructura 'switch'.
            switch (stoi(opcion)) {
                // Si la opci�n es 1 (Agregar),
            case 1:
                CapturaVentaProducto(Vticket, productos, idticket, tamticket);
                break;
                // Si la opci�n es 2 (Eliminar),
            case 2:
                Eliminar(Vticket, productos, tamticket);
                break;
                // Si la opci�n es 3 (Listado),
            case 3:
                // verifica si el ticket tiene contenido antes de intentar mostrarlo.
                if (!MostrarTicket(Vticket, tamticket).empty()) {
                    // Si no est� vac�o, muestra el contenido del ticket actual en la consola.
                    cout << MostrarTicket(Vticket, tamticket) << endl;
                }
                break;
                // Si la opci�n es 4 (Pagar),
            case 4:
                // muestra el ticket final al usuario.
                cout << MostrarTicket(Vticket, tamticket) << endl;
                // Llama a 'Pagar' para registrar la venta en la memoria del programa (en la matriz 'ventas').
                Pagar(idticket, ventas, tamventas, Vticket, tamticket);
                // Comprueba si el ticket tiene al menos un producto antes de intentar guardarlo en archivo.
                if (ObtenerUltimaPosicion4(Vticket, tamticket) > -1)
                {
                    // Mensaje de depuraci�n para ver el estado de los arreglos.
                    cout << "tama�o de venta creando archivo " + ObtenerUltimaPosicion5(ventas, tamventas) + ObtenerUltimaPosicion4(Vticket, tamticket);
                    // Guarda el detalle de los productos del ticket en el archivo CSV de detalle de ventas.
                    GuardarDatosCsvVentaTicket(Vticket, narchivo, ObtenerUltimaPosicion4(Vticket, tamticket) + 1, idticket);
                    // Crea stringstreams para formatear los totales con dos decimales.
                    std::stringstream s_subtotal, s_iva, s_total;
                    // Formatea el subtotal.
                    s_subtotal << std::fixed << std::setprecision(2) << SubTotalTicket(Vticket, tamticket);
                    // Formatea el IVA.
                    s_iva << std::fixed << std::setprecision(2) << IvaTicket(Vticket, tamticket);
                    // Formatea el total.
                    s_total << std::fixed << std::setprecision(2) << TotalTicket(Vticket, tamticket);
                    // Genera una l�nea de resumen de la venta en formato CSV.
                    string cadena = GenerarCsvFilaVenta(fechadia, idticket, s_subtotal.str(), s_iva.str(), s_total.str());
                    // Guarda la l�nea de resumen en el archivo CSV principal de ventas.
                    GuardarDatosCsvVenta("ventas.csv", cadena);
                }
                // Establece la bandera 'pago' en 'true'.
                pago = true;
                // Fija la 'opcion' a "5" para forzar la salida del bucle.
                opcion = "5";
                // Termina el caso.
                break;
                // Si la opci�n es 5 (Salida),
            case 5:
                // muestra un mensaje de salida.
                cout << "Salida del sistema" << endl;
                // Comprueba si el ticket NO fue pagado.
                if (!pago) {
                    // Si no se pag�, informa al usuario y cancela la venta.
                    cout << "No pag� el ticket. Ejecutando devoluci�n..." << endl;
                    // Llama a 'DevolucionTicket' para regresar el stock de los productos al inventario.
                    DevolucionTicket(Vticket, tamticket, productos);
                    // Informa que el ticket se est� eliminando.
                    cout << "Eliminando ticket " << idticket << endl;
                }
                break;
                // Si la opci�n no coincide con ning�n caso,
            default:
                cout << "Opci�n no v�lida" << endl;
                break;
            }
        }
    } while (opcion != "5");
}

void ModificarProducto(std::string productos[10][4]) {
    std::string codigo, precio;
    int posicion;
    std::string info = MostrarLista(productos);
    codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");

    if (!codigo.empty()) {
        posicion = ExisteProducto(codigo, productos);

        if (posicion > -1) {
            // Se crea una copia de la fila del producto para pasarla a la funci�n MostrarProducto.
            // Es necesario pasar un array de tama�o fijo de 4.
            std::string vproducto[4];
            for (int i = 0; i < 4; ++i) {
                vproducto[i] = productos[posicion][i];
            }

            precio = Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ");

            if (!precio.empty()) {
                if (EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1)) {
                    productos[posicion][2] = precio;
                    std::cout << "Producto modificado con �xito." << std::endl;
                }
                else {
                    std::cout << "no es un valor numerico" << std::endl;
                }
            }
            else {
                std::cout << "dato nulo" << std::endl;
            }
        }
        else {
            std::cout << "no existe el codigo" << std::endl;
        }
    }
    else {
        std::cout << "dato nulo" << std::endl;
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


void AgregarStock(string vproductos[][4]) {
    string codigo, cantidad;
    int posicion;
    string info = MostrarLista(vproductos);
    codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");

    if (!codigo.empty()) {
        posicion = ExisteProducto(codigo, vproductos);
        if (posicion > -1) {
            string vproducto[] = { vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][3], "" };
            cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ");

            if (!cantidad.empty()) {
                if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1)) {
                    string nuevacantidad = std::to_string(std::stoi(cantidad) + std::stoi(vproducto[2]));
                    vproductos[posicion][3] = nuevacantidad;
                }
                else {
                    std::cout << "no es un valor numerico" << std::endl;
                }
            }
            else {
                std::cout << "dato nulo" << std::endl;
            }
        }
        else {
            std::cout << "no existe el codigo" << std::endl;
        }
    }
    else {
        std::cout << "dato nulo" << std::endl;
    }
}

void MenuInventario(string vproductos[][4]) {
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
                std::cout << MostrarLista(vproductos) << std::endl;
                break;
            case 2:
                AgregarStock(vproductos);
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
// REALIZA: Es el bucle principal de la aplicaci�n. Al iniciar, intenta leer el �ltimo ticket de un archivo
//          CSV del d�a para mantener la continuidad. Muestra el men� principal y dirige al usuario a los
//          diferentes subm�dulos seg�n su elecci�n.
// PAR�METROS:
//   - string vproductos[][4]: La matriz del cat�logo de productos.
//   - string vventas[][5]: La matriz del historial de ventas en memoria.
//   - int tamventas: El tama�o m�ximo de la matriz de ventas.
// REGRESA: Nada (void).
void MenuPrincipal(string vproductos[][4], string vventas[][5], int tamventas) {
    // Declara una variable para almacenar la opci�n num�rica del usuario.
    int opcion = 0;
    // Declara una bandera booleana para controlar el bucle del men�. El programa se ejecuta mientras sea 'false'.
    bool salida = false;
    // Declara una cadena para almacenar el n�mero del �ltimo ticket.
    string idticket;
    // Define un arreglo constante con las opciones de texto que se mostrar�n en el men� principal.
    static const std::string datosmenuprincipal[] = { "1.-Productos ", "2.-Punto de Venta ", "3.-Inventario ","4.-Ventas ", "5.-Salida " };
    // Genera el nombre del archivo de ventas para el d�a actual (ej: "14-09-2025.csv").
    string narchivo = Fecha() + ".csv";
    // Comprueba si el archivo de ventas del d�a de hoy ya existe.
    if (ExisteArchivo(narchivo))
    {
        // Mensaje de depuraci�n para indicar que se est� leyendo un archivo existente.
        std::cout << "leyendo archivo" + narchivo;
        // Si existe, lee el archivo para obtener el �ltimo ID de ticket guardado.
        idticket = LeerDatosCSV(narchivo);
    }

    // Inicia un bucle 'while' que se ejecutar� continuamente hasta que la variable 'salida' sea 'true'.
    while (!salida) {
        // Si 'idticket' est� vac�o (porque el archivo no exist�a o una venta acaba de terminar),
        if ((idticket.empty()))
            // obtiene el �ltimo ID de ticket desde la memoria del programa como respaldo.
            idticket = ObtenerUltimoValorVentas(vventas, tamventas);
        // Muestra el men� principal y captura la elecci�n del usuario como una cadena de texto.
        std::string opcionStr = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Peque�a", datosmenuprincipal, 5);

        // Verifica si la opci�n introducida est� vac�a.
        if (opcionStr.empty()) {
            // Si est� vac�a, muestra un mensaje de error.
            std::cout << "opcion incorrecta " << std::endl;
        }
        // Si la opci�n no est� vac�a,
        else {
            // toma solo el primer car�cter de la entrada y lo convierte a un entero para manejar la opci�n.
            opcion = std::stoi(opcionStr.substr(0, 1));
            // Eval�a la opci�n num�rica en una estructura 'switch'.
            switch (opcion) {
                // Si la opci�n es 1 (Productos),
            case 1:
                MenuProductos(vproductos);
                break;
                // Si la opci�n es 2 (Punto de Venta),
            case 2:
                // llama al submen� del punto de venta, pas�ndole todos los datos necesarios, incluido el nombre del archivo.
                MenuPuntoVenta(vventas, tamventas, idticket, productos, narchivo);
                // Resetea 'idticket' para forzar que se vuelva a calcular en la siguiente iteraci�n del bucle.
                idticket = "";
                break;
                // Si la opci�n es 3 (Inventario),
            case 3:
                MenuInventario(vproductos);
                break;
                // Si la opci�n es 4 (Ventas),
            case 4:
                // llama a la funci�n que muestra el historial de ventas en memoria y lo imprime en consola.
                std::cout << MostrarListaVentas(vventas, tamventas) << std::endl;
                break;
                // Si la opci�n es 5 (Salida),
            case 5:
                // muestra un mensaje de despedida.
                std::cout << "Salida del Sistema " << std::endl;
                // Cambia la bandera 'salida' a 'true' para terminar el bucle 'while'.
                salida = true;
                break;
                // Si la opci�n no es ninguna de las anteriores,
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
    int ultipos = ObtenerUltimaPosicion4(productos, 10);
    std::cout << "PROBANDO " << std::endl;

    MenuPrincipal(productos, ventas, tamventas);
}
