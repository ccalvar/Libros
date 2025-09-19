// Declara la variable 'productos' en el �mbito principal del script.
// Esta variable almacenar� el arreglo con todo el inventario de productos
// una vez que sea inicializada por la funci�n CargarProductos().
let productos;

function MostrarMenu(opciones) {
    let cadena = "";
    for (let info of opciones) {
        cadena += info + "\n";
    }
    return cadena;
}
function EsNumeroEntero(dato) {
    for (let c of dato) {
        if (! /\d/.test(c))
            // expresi�n regular /\d / para comprobar si el car�cter actual c 
            //es un d�gito num�rico.
            //El m�todo test() de la expresi�n regular devuelve true 
            //si el car�cter es un d�gito, y false en caso contrario.
            //El operador de negaci�n! invierte el resultado, de modo que 
            //si el car�cter no es un d�gito, la condici�n se eval�a como true.
        {
            return false;
        }
    }
    return true;
}

function EsNumeroDouble(dato) {
    let valido = false;
    for (let c of dato) {
        if (!
            /\d/.test(c)) {
            if (c ===
                '.' && !valido) {
                valido = true;
            } else {
                return false;
            }
        }
    }
    return valido;
}
function EvaluarNumerico(dato, tipo) {
    let valido = false;
    switch (tipo) {
        case 1:
            valido = EsNumeroEntero(dato);
            break;
        case 2:
            valido = EsNumeroDouble(dato);
            break;
    }
    return valido;
}

async function Dialogo(texto) {
// Crea una interfaz de l�nea de comandos para leer y escribir en la terminal
    const readline = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });

 // Retorna una promesa que se resuelve cuando el usuario ingresa una respuesta
    return new Promise(resolve => {
 // Muestra el texto al usuario y espera su respuesta
        readline.question(texto, ans => {
 // Cierra la interfaz de l�nea de comandos
            readline.close();
 // Resuelve la promesa con la respuesta del usuario
            resolve(ans);
        });
    });
}

async function Leer(texto) {
    let cadena = await Dialogo(texto);
    if (cadena !== null) {
        cadena = cadena.trim();
        if (!cadena) {
            cadena = null;
        }
    }
    return cadena;
}

async function DesplegarMenu(titulo, menu) {
    let cadena = titulo + "\n\n";
    cadena += MostrarMenu(menu);
    cadena +="\n Que opcion deseas";
    return await Dialogo(cadena);
}

function RellenarEspacios(dato, tamano) {
    return dato.padEnd(tamano);
}

function Fecha() {
    // Crea un objeto Date que representa la fecha actual
    const date = new Date();

    // Convierte la fecha a una cadena en formato dd/mm/yyyy
    return date.toLocaleDateString('en-GB').split(' : ')
        .map(part => part.replace(' ', '/'))
        .reverse()
        .join('-');

  // Separa la cadena en un arreglo usando el espacio y el car�cter ":"
  // Reemplaza los espacios por barras diagonales '/'
 // Invierte el orden de los elementos en el arreglo
 // Une los elementos del arreglo en una sola cadena usando el gui�n '-'
}
function IdTicketSiguiente(idticket) {
    let num = parseInt(idticket) + 1;
    let idticketnext = "";
    if (num < 10) {
        idticketnext ="00" + num.toString().trim();
    } else if (num > 9 && num < 100) {
        idticketnext = "0" + num.toString().trim();
    }
    else {
        idticketnext = num.toString().trim();
    }
    return idticketnext;
}

/**
 * Tipo: Funci�n
 * Par�metros: Ninguno.
 * Prop�sito: Crear y devolver un arreglo (Array) que funciona como una base de datos
 * est�tica de productos. Cada producto es un arreglo interno con c�digo, nombre,
 * precio y cantidad.
 * Devuelve: Un arreglo de arreglos (Array) con los datos de los productos.
 */
function CargarProductos() {
    // Define un arreglo constante 'producto' que contiene los datos de varios productos.
    // Estructura de cada producto: [c�digo, descripci�n, precio, inventario]
    const producto = [
        ["001", "Arroz 1kg", "35", "10"],
        ["002", "Az�car 1kg", "25", "10"],
        ["003", "Harina 1kg", "28", "10"],
        ["004", "Aceite 1L", "50", "10"],
        ["005", "Leche 1L", "35", "10"],
        ["006", "Huevos 12 unidades", "45", "10"],
        ["007", "Fideos 500g", "20", "10"],
        ["008", "Sal 1kg", "15", "10"],
        ["009", "Pasta de tomate 400g", "25", "10"],
        ["010", "At�n lata 170g", "35", "10"]
    ];
    // Retorna el arreglo completo de productos.
    return producto;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - vproducto: Un arreglo (Array) que contiene los datos de un solo producto.
 * Prop�sito: Formatear los datos de un producto en una sola cadena de texto con
 * anchos de columna fijos para una visualizaci�n ordenada.
 * Devuelve: Una cadena de texto (string) con el producto formateado.
 */
function MostrarProducto(vproducto) {
    // Formatea el c�digo del producto para que ocupe 5 caracteres.
    let codigo = RellenarEspacios(vproducto[0], 5);
    // Formatea la descripci�n del producto para que ocupe 30 caracteres.
    let producto = RellenarEspacios(vproducto[1], 30);
    // Formatea el precio para que ocupe 10 caracteres.
    let precio = RellenarEspacios(vproducto[2], 10);
    // Formatea la cantidad para que ocupe 10 caracteres.
    let cantidad = RellenarEspacios(vproducto[3], 10);
    // Concatena todas las partes formateadas en una sola l�nea de texto.
    let cadena = codigo + producto + precio + cantidad;
    // Devuelve la l�nea de texto formateada.
    return cadena;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - vproductos: Un arreglo (Array) que contiene la lista completa de productos.
 * Prop�sito: Crear una cadena de texto multil�nea con todos los productos de la lista,
 * cada uno formateado para mostrarse en una tabla.
 * Devuelve: Una cadena de texto (string) con la lista formateada.
 */
function MostrarLista(vproductos) {
    // Inicializa una cadena vac�a para acumular la salida.
    let salida = "";
    // Itera sobre la lista de productos (asume que hay 10 productos).
    for (let ciclo = 0; ciclo < 10; ciclo++) {
        // Extrae los datos de un producto en la posici�n actual del ciclo.
        let vproducto = [vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3]];
        // Formatea el producto actual usando la funci�n MostrarProducto.
        let cadena = MostrarProducto(vproducto);
        // Agrega la l�nea formateada y un salto de l�nea a la cadena de salida.
        salida += cadena + "\n";
    }
    // Devuelve la cadena completa con toda la lista.
    return salida;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - codigo: La cadena (string) del c�digo de producto a buscar.
 * - vproductos: El arreglo (Array) donde se realizar� la b�squeda.
 * Prop�sito: Buscar un producto por su c�digo dentro del arreglo de productos.
 * Devuelve: El �ndice (posici�n) del producto si se encuentra; de lo contrario, devuelve -1.
 */
function ExisteProducto(codigo, vproductos) {
    // Inicializa la variable 'enc' en -1 (indicando "no encontrado").
    let enc = -1;
    // Inicializa un contador de posici�n.
    let pos = 0;
    // Itera sobre todo el arreglo de productos.
    for (let ciclo = 0; ciclo < vproductos.length; ciclo++) {
        // Compara el c�digo del producto actual (limpiando espacios) con el c�digo buscado.
        if (vproductos[ciclo][0].trim() === codigo.trim()) {
            // Si lo encuentra, guarda la posici�n actual en 'enc'.
            enc = pos;
        }
        // Incrementa el contador de posici�n en cada ciclo.
        pos++;
    }
    // Devuelve la posici�n encontrada o -1 si no se encontr�.
    return enc;
}

/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros:
 * - vproductos: El arreglo (Array) de productos que se va a modificar.
 * Prop�sito: Permite al usuario modificar el precio de un producto. Muestra la lista,
 * solicita un c�digo, lo busca y, si existe, pide el nuevo precio y actualiza el arreglo.
 * Devuelve: Nada (modifica el arreglo original directamente).
 */
async function ModificarProducto(vproductos) {
    let codigo, precio;
    let posicion;
    // Genera una cadena con la lista de productos para mostrarla al usuario.
    let info = MostrarLista(vproductos);
    // Pide al usuario que introduzca el c�digo del producto a modificar.
    codigo = await Leer(info + "\nIntroduce el codigo del producto a modificar");

    // Si el usuario introdujo un c�digo (no es nulo)...
    if (codigo !== null) {
        // ...busca la posici�n del producto en el arreglo.
        posicion = ExisteProducto(codigo, vproductos);
        // Si la posici�n es mayor a -1, significa que el producto fue encontrado.
        if (posicion > -1) {
            // Extrae los datos del producto encontrado.
            let vproducto = [vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2], vproductos[posicion][3]];
            // Pide al usuario que introduzca el nuevo precio.
            precio = await Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ");
            // Si el precio introducido no es nulo...
            if (precio !== null) {
                // ...valida si el precio es un n�mero (entero o decimal).
                if (EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1)) {
                    // Si es num�rico, actualiza el precio en el arreglo original.
                    vproductos[posicion][2] = precio;
                } else {
                    console.log("no es un valor numerico");
                }
            } else {
                console.log(" dato nulo");
            }
        } else {
            console.log("no existe el codigo");
        }
    } else {
        console.log(" dato nulo");
    }
}

/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros:
 * - vproductos: El arreglo (Array) de productos.
 * Prop�sito: Muestra un men� de opciones para la gesti�n de productos y ejecuta la
 * acci�n seleccionada por el usuario (Modificar, Listar o Salir).
 * Devuelve: Nada.
 */
async function MenuProductos(vproductos) {
    // Define las opciones del men�.
    const datosmenuproductos = ["1.-Modificar", "2.-Listado", "3.-Salida "];
    let opcion = "0"; // Inicializa la opci�n del usuario.

    // Bucle que se repite hasta que el usuario elija la opci�n "3".
    do {
        // Muestra el men� y espera la selecci�n del usuario.
        opcion = await DesplegarMenu("Opciones de Productos ", datosmenuproductos);
        // Si el usuario ingres� una opci�n...
        if (opcion !== null) {
            // ...eval�a la opci�n seleccionada.
            switch (opcion) {
                case "1":
                    // Si es "1", llama a la funci�n para modificar un producto.
                    await ModificarProducto(vproductos);
                    break;
                case "2":
                    // Si es "2", muestra la lista de productos en la consola.
                    console.log(MostrarLista(vproductos));
                    break;
                case "3":
                    // Si es "3", muestra un mensaje de salida.
                    console.log("Salida del Sistema ");
                    break;
                default:
                    // Si no es ninguna de las anteriores, muestra un mensaje de error.
                    console.log("No existe esta opcion ");
            }
        } else {
            console.log("Opcion incorrecta ");
        }
    } while (opcion !== "3");
}


async function MenuPuntoVenta(idticket) {
    let opcion, membrete;
    let pago = false;
    idticket = IdTicketSiguiente(idticket);
    let fechadia = Fecha();
    membrete = `Fecha del Dia ${fechadia} Ticket No ${idticket}`;
    membrete += "\n-------------------------------------------------------\n"; 
    const datosmenu = ["1. - Agregar ", "2. - Eliminar ", "3. - Listado ", "4. - Pagar ", "5. - Salida"];  
        do {
            opcion = await DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu); 
        if (!opcion) console.log("dato incorrecto introducido");
                else switch (opcion) {
            case "1":
                console.log("Agregar Articulo al Ticket");
                break;
            case "2":
                console.log("Eliminar Articulo del Ticket");
                break;
            case "3":
                console.log("Listado de Articulos del Ticket");
         break;
            case "4":
                console.log("Pagar Ticket y salir");
                opcion = "5";
                pago = true;
                break;
            case "5":
                console.log("Salida del Ventas");
                if (!pago) {
                    console.log("No pago el ticket");
                    console.log("eliminando tickte" + idticket);
                }
                break;
            default:
                console.log("No existe esta opcion");
                break;
        }
    } while (opcion !== "5");
}

async function MenuInventario() {
    const datosmenuinventarios = ["1. - Listado ","2. - Agregar ",  "3. - Salida " ];
    let opcion = "0";
    do {
        opcion = await DesplegarMenu("Opciones de Inventarios", datosmenuinventarios);
        if (!opcion) console.log("opcion incorrecta ");
        else switch (opcion) {
            case "1":
                console.log("Listado de Inventario  ");
                break;
            case "2":
                console.log("Agregar Inventario  ");
                break;
            case "3":
                console.log("Salida de Inventarios");
                break;
            default:
                console.log("No existe esta opcion");
                break;
        }
    } while (opcion !== "3");
}



/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros:
 * - vproductos: Un arreglo (Array) que contiene la lista completa de productos.
 * Prop�sito: Funciona como el men� principal y el controlador central de la aplicaci�n.
 * Desde aqu�, el usuario puede navegar a los diferentes m�dulos del sistema
 * (Productos, Punto de Venta, Inventarios) o salir del programa.
 * Devuelve: Nada.
 */
async function MenuPrincipal(vproductos) {
    // Define las opciones que se mostrar�n en el men� principal.
    const datosmenuprincipal = ["1.-Productos ", "2.-Punto de Venta ", "3.- Inventarios", "5. Salida"];
    let opcion = "0"; // Inicializa la variable para la opci�n del usuario.

    // Bucle principal que mantiene la aplicaci�n en ejecuci�n hasta que se elija salir.
    do {
        // Muestra el men� principal y espera (await) a que el usuario seleccione una opci�n.
        opcion = await DesplegarMenu("Menu de Punto de Tienda de Abarrotes", datosmenuprincipal);

        // Si el usuario no introduce una opci�n v�lida (ej. presiona Enter sin escribir nada).
        if (!opcion)
            console.log("opcion incorrecta ");
        // Si se introduce una opci�n, se eval�a con el switch.
        else switch (opcion) {
            // Cada caso llama al submen� correspondiente.
            // Se usa 'await' para asegurar que un men� termine antes de volver a mostrar el men� principal.
            case "1":
                await MenuProductos(vproductos); // Va al men� de productos y le pasa la lista de productos.
                break;
            case "2":
                await MenuPuntoVenta("000"); // Va al men� de ventas, iniciando con el ticket "000".
                break;
            case "3":
                await MenuInventario(); // Va al men� de inventarios.
                break;
            case "5":
                console.log("Salida del Sistema"); // Muestra un mensaje de despedida.
                break;
            default:
                console.log("No existe esta opcion"); // Mensaje para opciones no v�lidas.
                break;
        }
        // El bucle se repite mientras la opci�n seleccionada no sea "5".
    } while (opcion !== "5");
}

// ----------------------------------------------------------------------------------
// PUNTO DE INICIO DE LA APLICACI�N
// ----------------------------------------------------------------------------------
// Se utiliza una funci�n as�ncrona autoejecutable (IIFE) para iniciar el programa.
// Esto permite usar 'await' en el nivel m�s alto del script.
(async () => {
    // 1. Carga los datos iniciales de los productos en una variable.
    let productos = CargarProductos();
    // 2. Ejecuta el men� principal y le pasa la lista de productos para que la aplicaci�n pueda usarla.
    await MenuPrincipal(productos);
})();