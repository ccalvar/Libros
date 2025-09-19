// Declara la variable 'productos' en el ámbito principal del script.
// Esta variable almacenará el arreglo con todo el inventario de productos
// una vez que sea inicializada por la función CargarProductos().
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
            // expresión regular /\d / para comprobar si el carácter actual c 
            //es un dígito numérico.
            //El método test() de la expresión regular devuelve true 
            //si el carácter es un dígito, y false en caso contrario.
            //El operador de negación! invierte el resultado, de modo que 
            //si el carácter no es un dígito, la condición se evalúa como true.
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
// Crea una interfaz de línea de comandos para leer y escribir en la terminal
    const readline = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });

 // Retorna una promesa que se resuelve cuando el usuario ingresa una respuesta
    return new Promise(resolve => {
 // Muestra el texto al usuario y espera su respuesta
        readline.question(texto, ans => {
 // Cierra la interfaz de línea de comandos
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

  // Separa la cadena en un arreglo usando el espacio y el carácter ":"
  // Reemplaza los espacios por barras diagonales '/'
 // Invierte el orden de los elementos en el arreglo
 // Une los elementos del arreglo en una sola cadena usando el guión '-'
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
 * Tipo: Función
 * Parámetros: Ninguno.
 * Propósito: Crear y devolver un arreglo (Array) que funciona como una base de datos
 * estática de productos. Cada producto es un arreglo interno con código, nombre,
 * precio y cantidad.
 * Devuelve: Un arreglo de arreglos (Array) con los datos de los productos.
 */
function CargarProductos() {
    // Define un arreglo constante 'producto' que contiene los datos de varios productos.
    // Estructura de cada producto: [código, descripción, precio, inventario]
    const producto = [
        ["001", "Arroz 1kg", "35", "10"],
        ["002", "Azúcar 1kg", "25", "10"],
        ["003", "Harina 1kg", "28", "10"],
        ["004", "Aceite 1L", "50", "10"],
        ["005", "Leche 1L", "35", "10"],
        ["006", "Huevos 12 unidades", "45", "10"],
        ["007", "Fideos 500g", "20", "10"],
        ["008", "Sal 1kg", "15", "10"],
        ["009", "Pasta de tomate 400g", "25", "10"],
        ["010", "Atún lata 170g", "35", "10"]
    ];
    // Retorna el arreglo completo de productos.
    return producto;
}

/**
 * Tipo: Función
 * Parámetros:
 * - vproducto: Un arreglo (Array) que contiene los datos de un solo producto.
 * Propósito: Formatear los datos de un producto en una sola cadena de texto con
 * anchos de columna fijos para una visualización ordenada.
 * Devuelve: Una cadena de texto (string) con el producto formateado.
 */
function MostrarProducto(vproducto) {
    // Formatea el código del producto para que ocupe 5 caracteres.
    let codigo = RellenarEspacios(vproducto[0], 5);
    // Formatea la descripción del producto para que ocupe 30 caracteres.
    let producto = RellenarEspacios(vproducto[1], 30);
    // Formatea el precio para que ocupe 10 caracteres.
    let precio = RellenarEspacios(vproducto[2], 10);
    // Formatea la cantidad para que ocupe 10 caracteres.
    let cantidad = RellenarEspacios(vproducto[3], 10);
    // Concatena todas las partes formateadas en una sola línea de texto.
    let cadena = codigo + producto + precio + cantidad;
    // Devuelve la línea de texto formateada.
    return cadena;
}

/**
 * Tipo: Función
 * Parámetros:
 * - vproductos: Un arreglo (Array) que contiene la lista completa de productos.
 * Propósito: Crear una cadena de texto multilínea con todos los productos de la lista,
 * cada uno formateado para mostrarse en una tabla.
 * Devuelve: Una cadena de texto (string) con la lista formateada.
 */
function MostrarLista(vproductos) {
    // Inicializa una cadena vacía para acumular la salida.
    let salida = "";
    // Itera sobre la lista de productos (asume que hay 10 productos).
    for (let ciclo = 0; ciclo < 10; ciclo++) {
        // Extrae los datos de un producto en la posición actual del ciclo.
        let vproducto = [vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3]];
        // Formatea el producto actual usando la función MostrarProducto.
        let cadena = MostrarProducto(vproducto);
        // Agrega la línea formateada y un salto de línea a la cadena de salida.
        salida += cadena + "\n";
    }
    // Devuelve la cadena completa con toda la lista.
    return salida;
}

/**
 * Tipo: Función
 * Parámetros:
 * - codigo: La cadena (string) del código de producto a buscar.
 * - vproductos: El arreglo (Array) donde se realizará la búsqueda.
 * Propósito: Buscar un producto por su código dentro del arreglo de productos.
 * Devuelve: El índice (posición) del producto si se encuentra; de lo contrario, devuelve -1.
 */
function ExisteProducto(codigo, vproductos) {
    // Inicializa la variable 'enc' en -1 (indicando "no encontrado").
    let enc = -1;
    // Inicializa un contador de posición.
    let pos = 0;
    // Itera sobre todo el arreglo de productos.
    for (let ciclo = 0; ciclo < vproductos.length; ciclo++) {
        // Compara el código del producto actual (limpiando espacios) con el código buscado.
        if (vproductos[ciclo][0].trim() === codigo.trim()) {
            // Si lo encuentra, guarda la posición actual en 'enc'.
            enc = pos;
        }
        // Incrementa el contador de posición en cada ciclo.
        pos++;
    }
    // Devuelve la posición encontrada o -1 si no se encontró.
    return enc;
}

/**
 * Tipo: Procedimiento asíncrono.
 * Parámetros:
 * - vproductos: El arreglo (Array) de productos que se va a modificar.
 * Propósito: Permite al usuario modificar el precio de un producto. Muestra la lista,
 * solicita un código, lo busca y, si existe, pide el nuevo precio y actualiza el arreglo.
 * Devuelve: Nada (modifica el arreglo original directamente).
 */
async function ModificarProducto(vproductos) {
    let codigo, precio;
    let posicion;
    // Genera una cadena con la lista de productos para mostrarla al usuario.
    let info = MostrarLista(vproductos);
    // Pide al usuario que introduzca el código del producto a modificar.
    codigo = await Leer(info + "\nIntroduce el codigo del producto a modificar");

    // Si el usuario introdujo un código (no es nulo)...
    if (codigo !== null) {
        // ...busca la posición del producto en el arreglo.
        posicion = ExisteProducto(codigo, vproductos);
        // Si la posición es mayor a -1, significa que el producto fue encontrado.
        if (posicion > -1) {
            // Extrae los datos del producto encontrado.
            let vproducto = [vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2], vproductos[posicion][3]];
            // Pide al usuario que introduzca el nuevo precio.
            precio = await Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ");
            // Si el precio introducido no es nulo...
            if (precio !== null) {
                // ...valida si el precio es un número (entero o decimal).
                if (EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1)) {
                    // Si es numérico, actualiza el precio en el arreglo original.
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
 * Tipo: Procedimiento asíncrono.
 * Parámetros:
 * - vproductos: El arreglo (Array) de productos.
 * Propósito: Muestra un menú de opciones para la gestión de productos y ejecuta la
 * acción seleccionada por el usuario (Modificar, Listar o Salir).
 * Devuelve: Nada.
 */
async function MenuProductos(vproductos) {
    // Define las opciones del menú.
    const datosmenuproductos = ["1.-Modificar", "2.-Listado", "3.-Salida "];
    let opcion = "0"; // Inicializa la opción del usuario.

    // Bucle que se repite hasta que el usuario elija la opción "3".
    do {
        // Muestra el menú y espera la selección del usuario.
        opcion = await DesplegarMenu("Opciones de Productos ", datosmenuproductos);
        // Si el usuario ingresó una opción...
        if (opcion !== null) {
            // ...evalúa la opción seleccionada.
            switch (opcion) {
                case "1":
                    // Si es "1", llama a la función para modificar un producto.
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
 * Tipo: Procedimiento asíncrono.
 * Parámetros:
 * - vproductos: Un arreglo (Array) que contiene la lista completa de productos.
 * Propósito: Funciona como el menú principal y el controlador central de la aplicación.
 * Desde aquí, el usuario puede navegar a los diferentes módulos del sistema
 * (Productos, Punto de Venta, Inventarios) o salir del programa.
 * Devuelve: Nada.
 */
async function MenuPrincipal(vproductos) {
    // Define las opciones que se mostrarán en el menú principal.
    const datosmenuprincipal = ["1.-Productos ", "2.-Punto de Venta ", "3.- Inventarios", "5. Salida"];
    let opcion = "0"; // Inicializa la variable para la opción del usuario.

    // Bucle principal que mantiene la aplicación en ejecución hasta que se elija salir.
    do {
        // Muestra el menú principal y espera (await) a que el usuario seleccione una opción.
        opcion = await DesplegarMenu("Menu de Punto de Tienda de Abarrotes", datosmenuprincipal);

        // Si el usuario no introduce una opción válida (ej. presiona Enter sin escribir nada).
        if (!opcion)
            console.log("opcion incorrecta ");
        // Si se introduce una opción, se evalúa con el switch.
        else switch (opcion) {
            // Cada caso llama al submenú correspondiente.
            // Se usa 'await' para asegurar que un menú termine antes de volver a mostrar el menú principal.
            case "1":
                await MenuProductos(vproductos); // Va al menú de productos y le pasa la lista de productos.
                break;
            case "2":
                await MenuPuntoVenta("000"); // Va al menú de ventas, iniciando con el ticket "000".
                break;
            case "3":
                await MenuInventario(); // Va al menú de inventarios.
                break;
            case "5":
                console.log("Salida del Sistema"); // Muestra un mensaje de despedida.
                break;
            default:
                console.log("No existe esta opcion"); // Mensaje para opciones no válidas.
                break;
        }
        // El bucle se repite mientras la opción seleccionada no sea "5".
    } while (opcion !== "5");
}

// ----------------------------------------------------------------------------------
// PUNTO DE INICIO DE LA APLICACIÓN
// ----------------------------------------------------------------------------------
// Se utiliza una función asíncrona autoejecutable (IIFE) para iniciar el programa.
// Esto permite usar 'await' en el nivel más alto del script.
(async () => {
    // 1. Carga los datos iniciales de los productos en una variable.
    let productos = CargarProductos();
    // 2. Ejecuta el menú principal y le pasa la lista de productos para que la aplicación pueda usarla.
    await MenuPrincipal(productos);
})();