
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

// Permite usar nombres de la librer�a est�ndar de C++ (como 'cout' o 'string') sin el prefijo 'std::'.
using namespace std;

// Matriz para almacenar el cat�logo de hasta 10 productos, con 4 datos cada uno (C�digo, Nombre, Precio, Cantidad).
string productos[10][4];

// Constante que define el tama�o m�ximo del arreglo de ventas (se pueden registrar hasta 100 art�culos vendidos).
const int tamventas = 100;
// Variable que funciona como un �ndice para saber cu�l es la �ltima venta registrada en la matriz 'ventas'. Inicia en -1 porque el arreglo est� vac�o.
int posventas = -1;
// Matriz para guardar el historial de ventas. Puede almacenar los datos de hasta 100 art�culos vendidos.
string ventas[tamventas][5];
// Variable global de tipo string, probablemente destinada a almacenar una fecha de operaci�n o reporte.
string fechas;

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



int ObtenerUltimaPosicion4( std::string matriz[][4], int filas) {
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

// TIPO: Funci�n
// REALIZA: Obtiene el ID del �ltimo ticket registrado en el historial de ventas.
// PAR�METROS:
//   - int pos: El �ndice de la �ltima venta registrada.
//   - string mventa[][5]: La matriz del historial de ventas.
// REGRESA: Una cadena (string) con el �ltimo ID de ticket, o "000" si no hay ventas.
string UltimoTicket(int pos, string mventa[][5]) {
    // Inicializa el ID del ticket con un valor por defecto.
    string idticket = "000";
    // Si la posici�n es v�lida (hay al menos una venta),
    if (pos > -1) {
        // obtiene el ID del ticket de la �ltima venta registrada.
        idticket = mventa[pos][0];
    }
    // Devuelve el ID del ticket encontrado o el valor por defecto.
    return idticket;
}

// TIPO: Procedimiento
// REALIZA: Inicializa una matriz de ticket, asegur�ndose de que todas sus celdas est�n vac�as.
// PAR�METROS:
//   - std::string(*ticket)[4]: Un puntero a la matriz del ticket que se va a limpiar.
// REGRESA: Nada (void).
void CrearTicket(std::string(*ticket)[4]) {
    // Inicia un bucle para recorrer las 20 filas posibles del ticket.
    for (int i = 0; i < 20; ++i) {
        // Inicia un bucle anidado para recorrer las 4 columnas de cada fila.
        for (int j = 0; j < 4; ++j) {
            // Asigna una cadena vac�a a cada celda para limpiar datos anteriores.
            ticket[i][j] = "";
        }
    }
}

// TIPO: Funci�n
// REALIZA: Verifica si un producto, identificado por su c�digo, ya existe dentro del ticket actual.
// PAR�METROS:
//   - std::string mticket[][4]: La matriz del ticket actual.
//   - std::string codigo: El c�digo del producto a buscar.
//   - int filas: El tama�o m�ximo de la matriz del ticket.
// REGRESA: Un entero (int) con el �ndice del producto en el ticket si se encuentra, o -1 si no.
int ExisteTicketCodigo(std::string mticket[][4], std::string codigo, int filas) {
    // Inicializa el valor de retorno en -1 (no encontrado).
    int enc = -1;
    // Obtiene la �ltima posici�n utilizada en el ticket para no recorrer celdas vac�as.
    int pos = ObtenerUltimaPosicion4(mticket, filas);
    // Muestra un mensaje de depuraci�n en la consola.
    std::cout << "buscando " << codigo << " tama�o arreglo " << pos << std::endl;
    // Recorre el ticket desde la primera hasta la �ltima posici�n utilizada.
    for (int ciclo = 0; ciclo <= pos; ciclo++) {
        // Compara el c�digo del producto en la fila actual con el c�digo buscado.
        if (mticket[ciclo][0].compare(codigo) == 0) {
            // Si coinciden, guarda el �ndice actual.
            enc = ciclo;
            // Retorna inmediatamente para optimizar la b�squeda.
            return enc;
        }
    }
    // Si el bucle termina sin encontrar el producto, devuelve -1.
    return enc;
}

// TIPO: Funci�n
// REALIZA: Inserta un producto en el ticket. Si el producto ya existe, incrementa su cantidad. Si no, lo a�ade como una nueva l�nea.
// PAR�METROS:
//   - string mticket[][4]: La matriz del ticket actual.
//   - string datos[4]: Los datos del producto a insertar.
//   - int tamticket: El tama�o m�ximo del ticket.
// REGRESA: Un booleano. `true` si la operaci�n fue exitosa, `false` si el ticket est� lleno.
bool InsertarProductoTicket(string mticket[][4], string datos[4], int tamticket) {
    // Asume que la operaci�n ser� exitosa.
    bool sucedio = true;
    // Obtiene la �ltima posici�n utilizada en el ticket.
    int posticket = ObtenerUltimaPosicion4(mticket, tamticket);
    // Verifica si el producto ya existe en el ticket.
    int enc = ExisteTicketCodigo(mticket, datos[0], tamticket);
    // Comprueba si hay espacio en el ticket.
    if (posticket < tamticket) {
        // Si el producto ya fue encontrado en el ticket,
        if (enc > -1) {
            // informa al usuario y procede a incrementar la cantidad.
            cout << "Ya existe el producto en el ticket, lo incrementare" << endl;
            // Convierte la cantidad actual a entero.
            int cantidadactual = stoi(mticket[enc][3]);
            // Incrementa la cantidad en 1 y la convierte de nuevo a cadena para guardarla.
            mticket[enc][3] = to_string(cantidadactual + 1);
        }
        // Si el producto no existe en el ticket,
        else {
            // incrementa la posici�n para a�adir una nueva l�nea.
            posticket++;
            // Asigna los datos del producto a la nueva fila en el ticket.
            mticket[posticket][0] = datos[0]; // C�digo
            mticket[posticket][1] = datos[1]; // Nombre
            mticket[posticket][2] = datos[2]; // Precio
            mticket[posticket][3] = datos[3]; // Cantidad
            // Informa al usuario que se est� insertando un nuevo producto.
            cout << "Insertando, no existe el producto en el ticket" << endl;
        }
    }
    // Si no hay espacio en el ticket,
    else {
        // marca la operaci�n como fallida.
        sucedio = false;
    }
    // Devuelve el estado de la operaci�n.
    return sucedio;
}

// TIPO: Funci�n
// REALIZA: Calcula el costo total de una l�nea de producto (precio * cantidad).
// PAR�METROS:
//   - string precio: El precio del producto.
//   - string cantidad: La cantidad del producto.
// REGRESA: Una cadena (string) con el total formateado a dos decimales.
string TotalProducto(string precio, string cantidad) {
    // Convierte el precio y la cantidad de cadena a double y los multiplica.
    double total = stod(precio) * stod(cantidad);
    // Crea un stringstream para formatear el resultado.
    stringstream stream;
    // Formatea el total para que siempre tenga dos decimales.
    stream << fixed << setprecision(2) << total;
    // Devuelve el total formateado como una cadena.
    return stream.str();
}

// TIPO: Funci�n
// REALIZA: Formatea una l�nea de producto del ticket para su visualizaci�n, incluyendo el total.
// PAR�METROS:
//   - string mticket[][4]: La matriz del ticket actual.
//   - int pos: El �ndice de la l�nea de producto a formatear.
// REGRESA: Una cadena (string) con la l�nea del ticket formateada y alineada.
string MostrarProductoTicket(string mticket[][4], int pos) {
    // Formatea el c�digo del producto con un ancho de 5.
    string codigo = RellenarEspacios(mticket[pos][0], 5);
    // Formatea el nombre del producto con un ancho de 30.
    string producto = RellenarEspacios(mticket[pos][1], 30);
    // Formatea el precio con un ancho de 10.
    string precio = RellenarEspacios(mticket[pos][2], 10);
    // Formatea la cantidad con un ancho de 5.
    string cantidad = RellenarEspacios(mticket[pos][3], 5);
    // Calcula y formatea el total del producto con un ancho de 10.
    string totalproducto = RellenarEspacios(TotalProducto(mticket[pos][2], mticket[pos][3]), 10);
    // Concatena todas las partes para formar la l�nea completa.
    string cadena = codigo + producto + precio + cantidad + totalproducto;
    // Devuelve la cadena formateada.
    return cadena;
}

// TIPO: Funci�n
// REALIZA: Genera una representaci�n en texto de todo el contenido del ticket actual.
// PAR�METROS:
//   - std::string mticket[][4]: La matriz del ticket.
//   - int filas: El tama�o m�ximo de la matriz.
// REGRESA: Una cadena (string) con todas las l�neas del ticket, cada una en una nueva l�nea.
std::string MostrarTicket(std::string mticket[][4], int filas) {
    // Inicializa una cadena vac�a para la salida.
    std::string salida = "";
    // Obtiene la �ltima posici�n utilizada en el ticket.
    int pos = ObtenerUltimaPosicion4(mticket, filas);
    // Recorre el ticket desde el inicio hasta la �ltima posici�n utilizada.
    for (int ciclo = 0; ciclo <= pos; ciclo++) {
        // Formatea la l�nea actual y la a�ade a la cadena de salida, con un salto de l�nea.
        salida += MostrarProductoTicket(mticket, ciclo) + "\n";
    }
    // Devuelve la cadena con el ticket completo.
    return salida;
}

// TIPO: Funci�n
// REALIZA: Calcula el subtotal de la venta (la suma de los totales de todos los productos sin impuestos).
// PAR�METROS:
//   - std::string mticket[][4]: La matriz del ticket.
//   - int filas: El tama�o m�ximo de la matriz.
// REGRESA: Un valor double con el subtotal del ticket.
double SubTotalTicket(std::string mticket[][4], int filas) {
    // Inicializa el subtotal en 0.
    double subtotal = 0;
    // Declara una variable para almacenar el valor de cada l�nea.
    double valor;
    // Obtiene la �ltima posici�n utilizada en el ticket.
    int pos = ObtenerUltimaPosicion4(mticket, filas);
    // Recorre cada producto en el ticket.
    for (int ciclo = 0; ciclo <= pos; ciclo++) {
        // Declara una variable local para el valor.
        double valor;
        // Convierte el total del producto (que es un string) a un valor double.
        std::istringstream(TotalProducto(mticket[ciclo][2], mticket[ciclo][3])) >> valor;
        // Acumula el valor en el subtotal.
        subtotal = subtotal + valor;
    }
    // Devuelve el subtotal calculado.
    return subtotal;
}

// TIPO: Funci�n
// REALIZA: Calcula el monto del IVA (16%) sobre el subtotal del ticket.
// PAR�METROS:
//   - std::string mticket[][4]: La matriz del ticket.
//   - int filas: El tama�o m�ximo de la matriz.
// REGRESA: Un valor double con el monto del IVA. Devuelve -1 si el subtotal es cero o negativo.
double IvaTicket(std::string mticket[][4], int filas) {
    // Llama a SubTotalTicket para obtener el subtotal.
    double subtotal = SubTotalTicket(mticket, filas);
    // Si el subtotal es positivo,
    if (subtotal > 0)
        // calcula el 16% de IVA.
        subtotal = 0.16 * subtotal;
    // Si no,
    else
        // establece un valor de error.
        subtotal = -1;
    // Devuelve el monto del IVA calculado.
    return subtotal;
}

// TIPO: Funci�n
// REALIZA: Calcula el total final de la venta (subtotal + IVA).
// PAR�METROS:
//   - std::string mticket[][4]: La matriz del ticket.
//   - int filas: El tama�o m�ximo de la matriz.
// REGRESA: Un valor double con el total a pagar.
double TotalTicket(std::string mticket[][4], int filas) {
    // Obtiene el subtotal.
    double total = SubTotalTicket(mticket, filas);
    // Si el total es positivo,
    if (total > 0)
        // le suma el monto del IVA.
        total = IvaTicket(mticket, filas) + total;
    // Devuelve el total final.
    return total;
}

// TIPO: Funci�n
// REALIZA: Genera el formato de impresi�n final del ticket, incluyendo encabezado, productos, subtotal, IVA y total.
// PAR�METROS:
//   - std::string mticket[][4]: La matriz del ticket.
//   - std::string idticket: El n�mero de ticket.
//   - const std::string fecha: La fecha de la venta.
//   - int fila: El tama�o m�ximo de la matriz del ticket.
// REGRESA: Una cadena (string) con el recibo completo listo para mostrar.
std::string MostrarTicketVenta(std::string mticket[][4], std::string idticket, const std::string fecha, int fila) {
    // Crea un ostringstream para construir la cadena de salida.
    std::ostringstream salida;
    // Crea stringstreams para formatear los valores num�ricos a dos decimales.
    std::ostringstream subtotalStream, ivaStream, totalStream;

    // Formatea el subtotal.
    subtotalStream << std::fixed << std::setprecision(2) << SubTotalTicket(mticket, fila);
    // Formatea el IVA.
    ivaStream << std::fixed << std::setprecision(2) << IvaTicket(mticket, fila);
    // Formatea el total.
    totalStream << std::fixed << std::setprecision(2) << TotalTicket(mticket, fila);

    // Convierte los streams a cadenas de texto.
    std::string subtotal = subtotalStream.str();
    std::string iva = ivaStream.str();
    std::string total = totalStream.str();

    // Construye el encabezado del ticket.
    salida << "Fecha " << fecha << " Ticket No." << idticket;
    // A�ade la lista de productos del ticket.
    salida << "\n" << MostrarTicket(mticket, fila);
    // A�ade el desglose de totales.
    salida << "\n\n El total sin iva " << subtotal;
    salida << "\n el iva total es " << iva;
    salida << "\n el total de la venta fue " << total;

    // Devuelve la cadena con el ticket completo.
    return salida.str();
}

// TIPO: Funci�n
// REALIZA: Genera una lista de productos disponibles para la venta (aquellos con existencia mayor a cero).
// PAR�METROS:
//   - std::string vproductos[][4]: La matriz del cat�logo de productos.
//   - int filas: El n�mero de productos en el cat�logo.
// REGRESA: Una cadena (string) con la lista formateada de productos en stock.
std::string MostrarListaProductosVenta(std::string vproductos[][4], int filas) {
    // Inicializa la cadena de salida.
    std::string salida;
    // Recorre el cat�logo de productos.
    for (int ciclo = 0; ciclo < filas; ciclo++)
    {
        // Declara una variable para la existencia.
        int existencia;
        // Convierte la cantidad en stock (string) a un entero.
        std::istringstream(vproductos[ciclo][3]) >> existencia;
        // Si hay existencias del producto,
        if (existencia > 0) {
            // crea un arreglo temporal con los datos del producto.
            std::string vproducto[4];
            for (int i = 0; i < 4; i++) {
                vproducto[i] = vproductos[ciclo][i];
            }
            // Formatea el producto y lo a�ade a la lista de salida.
            std::string cadena = MostrarProducto(vproducto);
            salida = salida + cadena + "\n";
        }
    }
    // Devuelve la lista de productos disponibles.
    return salida;
}

// TIPO: Procedimiento
// REALIZA: Gestiona la captura de un producto para la venta: lo busca, verifica stock, lo descuenta del inventario y lo agrega al ticket.
// PAR�METROS:
//   - string mticket[][4]: La matriz del ticket actual.
//   - string mproductos[][4]: La matriz del cat�logo de productos.
//   - string idticket: El n�mero de ticket actual.
//   - int tamticket: El tama�o m�ximo del ticket.
// REGRESA: Nada (void).
void CapturaVentaProducto(string mticket[][4], string mproductos[][4], string idticket, int tamticket) {
    // Declara variables para el c�digo del producto y la informaci�n a mostrar.
    string codigo, info;
    // Obtiene la lista de productos disponibles para la venta.
    info = MostrarListaProductosVenta(mproductos, 10);
    // Muestra la lista y pide al usuario que introduzca un c�digo.
    cout << info << "\nIntroduce el codigo del producto: ";
    getline(cin, codigo);

    // Si el usuario introdujo un c�digo,
    if (!codigo.empty()) {
        // busca el producto en el cat�logo.
        int posp = ExisteProducto(codigo, mproductos);
        // Si el producto existe,
        if (posp > -1) {
            // obtiene la cantidad en stock.
            int cant = stoi(mproductos[posp][3]);
            // Si hay stock disponible,
            if (cant > 0) {
                // crea un arreglo temporal para mostrar los datos del producto vendido.
                string producto[4];
                for (int i = 0; i < 4; i++) {
                    producto[i] = mproductos[posp][i];
                }
                // Reduce el stock en 1.
                cant--;
                // Actualiza la cantidad en el cat�logo de productos.
                mproductos[posp][3] = to_string(cant);
                // Muestra el producto que se est� agregando.
                cout << MostrarProducto(producto) << endl;

                // Prepara los datos para insertar en el ticket (siempre se vende de 1 en 1).
                string venta[4] = { mproductos[posp][0], mproductos[posp][1], mproductos[posp][2], "1" };
                // Inserta el producto en el ticket y verifica si hubo error (ticket lleno).
                if (!InsertarProductoTicket(mticket, venta, tamticket)) {
                    cout << "El arreglo esta lleno\n";
                }
            }
            // Si no hay stock,
            else {
                cout << "No hay productos para venta" << endl;
            }
        }
        // Si el c�digo no existe,
        else {
            cout << "El codigo no existe, no se puede agregar\n";
        }
    }
    // Si no se introdujo un c�digo,
    else {
        cout << "Dato nulo\n";
    }
}

// TIPO: Procedimiento
// REALIZA: Elimina una l�nea de producto del ticket, desplazando las l�neas posteriores hacia arriba para llenar el espacio.
// PAR�METROS:
//   - string mticket[][4]: La matriz del ticket.
//   - int pos: El �ndice de la l�nea a eliminar.
//   - int filas: El tama�o m�ximo del ticket.
// REGRESA: Nada (void).
void RemoverProductoTicket(string mticket[][4], int pos, int filas) {
    // Obtiene la �ltima posici�n utilizada en el ticket.
    int tam = ObtenerUltimaPosicion4(mticket, filas);
    // Si la l�nea a eliminar no es la �ltima,
    if (tam > pos) {
        // recorre el ticket desde la posici�n a eliminar hasta el final.
        for (int i = pos; i < tam; i++) {
            // Desplaza los datos de la siguiente fila a la actual.
            for (int j = 0; j < 4; j++) {
                mticket[i][j] = mticket[i + 1][j];
            }
        }
        // Limpia la �ltima fila que ahora est� duplicada.
        for (int j = 0; j < 4; j++) {
            mticket[tam][j] = "";
        }
    }
    // Si la l�nea a eliminar es la �ltima,
    else {
        // simplemente la limpia.
        mticket[pos][0] = "";
    }
}

// TIPO: Procedimiento
// REALIZA: Gestiona la eliminaci�n de un producto del ticket. Si la cantidad es > 1, la reduce. Si es 1, elimina la l�nea completa.
// PAR�METROS:
//   - string mticket[][4]: La matriz del ticket.
//   - int pos: El �ndice del producto a eliminar.
//   - int filas: El tama�o m�ximo del ticket.
// REGRESA: Nada (void).
void EliminarProductoTicket(string mticket[][4], int pos, int filas) {
    // Obtiene la cantidad del producto en el ticket.
    int cantidad = stoi(mticket[pos][3]);
    // Si la cantidad es mayor que 1,
    if (cantidad > 1)
        // simplemente la decrementa.
        mticket[pos][3] = to_string(cantidad - 1);
    // Si la cantidad es 1,
    else
        // elimina la l�nea completa del producto.
        RemoverProductoTicket(mticket, pos, filas);
}

// TIPO: Procedimiento
// REALIZA: Orquesta la eliminaci�n de un producto del ticket por parte del usuario. Pide el c�digo, lo busca y devuelve el stock al inventario.
// PAR�METROS:
//   - string mticket[][4]: La matriz del ticket.
//   - string mproductos[][4]: La matriz del cat�logo de productos.
//   - int filas: El tama�o m�ximo del ticket.
// REGRESA: Nada (void).
void Eliminar(string mticket[][4], string mproductos[][4], int filas) {
    // Declara variables para el c�digo y la informaci�n.
    string codigo, info;
    // Muestra el contenido actual del ticket.
    info = MostrarTicket(mticket, filas);
    // Pide al usuario el c�digo del producto a eliminar.
    cout << info << "\nIntroduce el codigo del producto: ";
    getline(cin, codigo);

    // Si se introdujo un c�digo,
    if (!codigo.empty()) {
        // busca el producto en el ticket.
        int pos = ExisteTicketCodigo(mticket, codigo, filas);
        // Si se encuentra,
        if (pos > -1) {
            // busca el mismo producto en el cat�logo general.
            int posproducto = ExisteProducto(codigo, mproductos);
            // Devuelve 1 unidad al stock del inventario.
            string nuevacantidad = to_string(stoi(mproductos[posproducto][3]) + 1);
            mproductos[posproducto][3] = nuevacantidad;
            // Elimina el producto del ticket (o reduce su cantidad).
            RemoverProductoTicket(mticket, pos, filas);
        }
    }
    // Si no se introdujo un c�digo,
    else {
        cout << "Dato nulo" << endl;
    }
}

// TIPO: Procedimiento
// REALIZA: Transfiere los productos de un ticket pagado al historial de ventas.
// PAR�METROS:
//   - std::string mticket[][4]: La matriz del ticket finalizado.
//   - int tamTicket: El tama�o m�ximo del ticket.
//   - std::string mventa[][5]: La matriz del historial de ventas.
//   - int tamVenta: El tama�o m�ximo del historial de ventas.
//   - std::string idticket: El n�mero de ticket a registrar.
// REGRESA: Nada (void).
void AgregarProductoAVenta(std::string mticket[][4], int tamTicket, std::string mventa[][5], int tamVenta, std::string idticket) {
    // Obtiene la �ltima posici�n en el historial de ventas.
    int posventas = ObtenerUltimaPosicion5(mventa, tamVenta);
    // Obtiene la �ltima posici�n en el ticket actual.
    int posticket = ObtenerUltimaPosicion4(mticket, tamTicket);
    // Recorre cada producto en el ticket.
    for (int i = 0; i <= posticket; i++) {
        // Se asegura de que la fila no est� vac�a.
        if (!mticket[i][0].empty()) {
            // Incrementa la posici�n en el historial de ventas.
            posventas++;
            // Copia los datos del ticket al historial de ventas.
            mventa[posventas][0] = idticket;
            mventa[posventas][1] = mticket[i][0];
            mventa[posventas][2] = mticket[i][1];
            mventa[posventas][3] = mticket[i][2];
            mventa[posventas][4] = mticket[i][3];
        }
    }
}

// TIPO: Procedimiento
// REALIZA: Gestiona el proceso de pago. Verifica si hay espacio en el historial de ventas y registra la venta.
// PAR�METROS:
//   - std::string idticket: El n�mero de ticket a pagar.
//   - std::string mventa[][5]: La matriz del historial de ventas.
//   - int tamVenta: El tama�o m�ximo del historial de ventas.
//   - std::string mticket[][4]: La matriz del ticket actual.
//   - int tamTicket: El tama�o m�ximo del ticket.
// REGRESA: Nada (void).
void Pagar(std::string idticket, std::string mventa[][5], int tamVenta, std::string mticket[][4], int tamTicket) {
    // Obtiene las �ltimas posiciones de ambos arreglos.
    int posventas = ObtenerUltimaPosicion5(mventa, tamVenta);
    int post = ObtenerUltimaPosicion4(mticket, tamTicket);
    // Verifica si hay suficiente espacio en el historial de ventas.
    if ((posventas + post) < 100) {
        // Si hay espacio, transfiere los productos al historial de ventas.
        AgregarProductoAVenta(mticket, tamTicket, mventa, tamVenta, idticket);
    }
    // Si no hay espacio,
    else {
        // informa de un posible desbordamiento de memoria.
        std::cout << "Desbordamiento de Memoria de ventas" << std::endl;
    }
}

// TIPO: Procedimiento
// REALIZA: Cancela un ticket que no fue pagado, devolviendo el stock de todos sus productos al inventario.
// PAR�METROS:
//   - std::string mticket[][4]: La matriz del ticket a cancelar.
//   - int filasticket: El tama�o m�ximo del ticket.
//   - std::string mproductos[][4]: La matriz del cat�logo de productos.
// REGRESA: Nada (void).
void DevolucionTicket(std::string mticket[][4], int filasticket, std::string mproductos[][4]) {
    // Obtiene la �ltima posici�n utilizada en el ticket.
    int posmticket = ObtenerUltimaPosicion4(mticket, filasticket);
    // Recorre cada producto en el ticket.
    for (int pos = 0; pos <= posmticket; ++pos) {
        // Obtiene el c�digo del producto.
        std::string codigo = mticket[pos][0];
        // Busca el producto en el cat�logo general.
        int posp = ExisteProducto(codigo, mproductos);
        // Si lo encuentra,
        if (posp > -1) {
            // suma la cantidad del ticket al stock del inventario.
            int cant = std::stoi(mticket[pos][3]) + std::stoi(mproductos[posp][3]);
            mproductos[posp][3] = std::to_string(cant);
        }
    }
}

// TIPO: Funci�n
// REALIZA: Formatea una sola l�nea del historial de ventas para su visualizaci�n.
// PAR�METROS:
//   - string venta[5]: Un arreglo con los datos de un registro de venta.
// REGRESA: Una cadena (string) con el registro formateado.
string MostrarVenta(string venta[5]) {
    // Formatea el ID del ticket.
    string idticket = RellenarEspacios(venta[0], 6);
    // Formatea el c�digo del producto.
    string codigo = RellenarEspacios(venta[1], 5);
    // Formatea el nombre del producto.
    string producto = RellenarEspacios(venta[2], 30);
    // Formatea el precio.
    string precio = RellenarEspacios(venta[3], 10);
    // Formatea la cantidad.
    string cantidad = RellenarEspacios(venta[4], 10);
    // Devuelve la cadena concatenada y formateada.
    return idticket + codigo + producto + precio + cantidad;
}

// TIPO: Funci�n
// REALIZA: Genera una lista formateada de todo el historial de ventas.
// PAR�METROS:
//   - string ventas[][5]: La matriz del historial de ventas.
//   - int filas: El tama�o m�ximo del historial.
// REGRESA: Una cadena (string) con el historial completo de ventas.
string MostrarListaVentas(string ventas[][5], int filas) {
    // Obtiene la �ltima posici�n en el historial.
    int posventas = ObtenerUltimaPosicion5(ventas, filas);
    // Inicializa la cadena de salida.
    string salida = "";
    // Recorre el historial de ventas.
    for (int ciclo = 0; ciclo <= posventas; ciclo++) {
        // Crea un arreglo temporal con el registro actual.
        string venta[5] = { ventas[ciclo][0], ventas[ciclo][1], ventas[ciclo][2], ventas[ciclo][3], ventas[ciclo][4] };
        // Formatea el registro y lo a�ade a la salida.
        salida += MostrarVenta(venta) + "\n";
    }
    // Devuelve el historial formateado.
    return salida;
}


// TIPO: Procedimiento
// REALIZA: Es el motor principal del punto de venta. Gestiona la creaci�n de un ticket de venta,
//          permitiendo agregar y eliminar productos, y finaliza la transacci�n registrando la venta
//          o la cancela devolviendo el stock al inventario.
// PAR�METROS:
//   - string ventas[][5]: La matriz del historial de ventas, donde se registrar� el ticket si se paga.
//   - int tamventas: El tama�o m�ximo de la matriz de ventas.
//   - string& idticket: El ID del �ltimo ticket. Se pasa por referencia (&) para que el nuevo ID generado aqu�
//                     se actualice en la variable del men� principal.
//   - string productos[][4]: La matriz del cat�logo de productos, para consultar precios y descontar/devolver stock.
// REGRESA: Nada (void).
void MenuPuntoVenta(string ventas[][5], int tamventas, string& idticket, string productos[][4]) {
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
                // llama a la funci�n para capturar un nuevo producto en el ticket.
                CapturaVentaProducto(Vticket, productos, idticket, tamticket);
                // Termina el caso.
                break;
                // Si la opci�n es 2 (Eliminar),
            case 2:
                // llama a la funci�n para eliminar un producto del ticket.
                Eliminar(Vticket, productos, tamticket);
                // Termina el caso.
                break;
                // Si la opci�n es 3 (Listado),
            case 3:
                // verifica si el ticket tiene contenido antes de intentar mostrarlo.
                if (!MostrarTicket(Vticket, tamticket).empty()) {
                    // Si no est� vac�o, muestra el contenido del ticket actual en la consola.
                    cout << MostrarTicket(Vticket, tamticket) << endl;
                }
                // Termina el caso.
                break;
                // Si la opci�n es 4 (Pagar),
            case 4:
                // muestra el ticket final al usuario.
                cout << MostrarTicket(Vticket, tamticket) << endl;
                // Llama a la funci�n 'Pagar' para registrar la venta en el historial.
                Pagar(idticket, ventas, tamventas, Vticket, tamticket);
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
                // Termina el caso.
                break;
                // Si la opci�n no coincide con ning�n caso,
            default:
                // informa al usuario que la opci�n no es v�lida.
                cout << "Opci�n no v�lida" << endl;
                // Termina el caso.
                break;
            }
        }
        // El bucle se repite mientras la opci�n sea diferente de "5".
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


// TIPO: Funci�n
// REALIZA: Busca en el historial de ventas y obtiene el ID del �ltimo ticket registrado. 
//          Esto es �til para saber cu�l fue la �ltima venta y poder generar el siguiente n�mero de ticket.
// PAR�METROS:
//   - string ventas[][5]: La matriz que contiene el historial de todas las ventas.
//   - int filas: El tama�o m�ximo de la matriz de ventas.
// REGRESA: Una cadena (string) con el ID del �ltimo ticket. Si no hay ventas, regresa "000".
string ObtenerUltimoValorVentas(string ventas[][5], int filas) {
    // Llama a una funci�n auxiliar para encontrar el �ndice (la fila) de la �ltima venta registrada.
    int ultimaposicion = ObtenerUltimaPosicion5(ventas, filas);
    // Inicializa una variable con un valor por defecto ("000") que se usar� si no hay ventas.
    string ultimoValor = "000";
    // Comprueba si se encontr� una venta (si el �ndice es 0 o mayor).
    if (ultimaposicion >= 0) {
        // Si hay ventas, extrae el valor de la primera columna (el ID del ticket) de la �ltima fila encontrada.
        ultimoValor = ventas[ultimaposicion][0];
    }
    // Devuelve el �ltimo ID de ticket encontrado o el valor por defecto "000".
    return ultimoValor;
}

// TIPO: Procedimiento
// REALIZA: Es el bucle principal de la aplicaci�n. Muestra el men� de nivel superior y dirige al usuario
//          a los diferentes subm�dulos (Productos, Punto de Venta, Inventario, Ventas) seg�n su elecci�n.
// PAR�METROS:
//   - string vproductos[][4]: La matriz del cat�logo de productos.
//   - string vventas[][5]: La matriz del historial de ventas.
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
    // Inicia un bucle 'while' que se ejecutar� continuamente hasta que la variable 'salida' sea 'true'.
    while (!salida) {
        // Antes de mostrar el men�, obtiene el ID del �ltimo ticket del historial de ventas.
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
                // llama al submen� de gesti�n de productos.
                MenuProductos(vproductos);
                // Termina este caso.
                break;
                // Si la opci�n es 2 (Punto de Venta),
            case 2:
                // llama al submen� del punto de venta, pas�ndole todos los datos necesarios.
                MenuPuntoVenta(vventas, tamventas, idticket, productos);
                // Termina este caso.
                break;
                // Si la opci�n es 3 (Inventario),
            case 3:
                // llama al submen� de gesti�n de inventario.
                MenuInventario(vproductos);
                // Termina este caso.
                break;
                // Si la opci�n es 4 (Ventas),
            case 4:
                // llama a la funci�n que muestra el historial de ventas y lo imprime en consola.
                std::cout << MostrarListaVentas(vventas, tamventas) << std::endl;
                // Termina este caso.
                break;
                // Si la opci�n es 5 (Salida),
            case 5:
                // muestra un mensaje de despedida.
                std::cout << "Salida del Sistema " << std::endl;
                // Cambia la bandera 'salida' a 'true' para terminar el bucle 'while'.
                salida = true;
                // Termina este caso.
                break;
                // Si la opci�n no es ninguna de las anteriores,
            default:
                // informa al usuario que la opci�n no es v�lida.
                std::cout << "No existe esta opcion " << std::endl;
                // Termina este caso.
                break;
            }
        }
    }
}

// TIPO: Funci�n (principal)
// REALIZA: Es el punto de entrada de todo el programa. Prepara los datos iniciales y arranca el men� principal.
// PAR�METROS: Ninguno.
// REGRESA: Un entero (int). Por convenci�n, 0 indica que el programa termin� correctamente.
int main()
{
    // Llama al procedimiento para cargar los productos iniciales en la matriz global 'productos'.
    CargarProductos(productos);
    // Obtiene la posici�n del �ltimo producto cargado. (Nota: la variable 'ultipos' no se utiliza posteriormente en el c�digo).
    int ultipos = ObtenerUltimaPosicion4(productos, 10);
    // Llama al men� principal para iniciar la interacci�n con el usuario, pas�ndole las matrices de datos.
    MenuPrincipal(productos, ventas, tamventas);
}
