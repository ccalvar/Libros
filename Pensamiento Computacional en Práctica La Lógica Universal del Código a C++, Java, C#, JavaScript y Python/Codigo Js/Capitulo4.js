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
            valido = esNumeroEntero(dato);
            break;
        case 2:
            valido = esNumeroDouble(dato);
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
        if (cadena.isEmpty()) {
            cadena = null;
        }
    }
    return cadena;
}

async function DesplegarMenu(titulo, menu) {
    let cadena = titulo + "\n\n";
    cadena += MostrarMenu(menu);
    cadena += "\n Que opcion deseas";
    return await Dialogo(cadena);
}

function RellenaEspacios(dato, tamano) {
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
        idticketnext = "00" + num.toString().trim();
    } else if (num > 9 && num < 100) {
        idticketnext = "0" + num.toString().trim();
    }
    else {
        idticketnext = num.toString().trim();
    }
    return idticketnext;
}

/**
 * Tipo: Procedimiento asíncrono.
 * Parámetros: Ninguno.
 * Propósito: Muestra un menú de opciones relacionadas con la gestión de productos.
 * Permite al usuario seleccionar entre modificar, listar o salir. El menú se
 * repetirá hasta que el usuario elija la opción de salida.
 * Devuelve: Nada.
 */
async function MenuProductos() {
    // Define las opciones que se mostrarán en el menú de productos.
    const datosmenuproductos = ["1.-Modificar ", "2.-Listado ", "3.-Salida"];
    let opcion = "0"; // Inicializa la variable 'opcion' para controlar el bucle.

    // Inicia un bucle que se ejecutará al menos una vez.
    do {
        // Muestra el menú y espera (await) a que el usuario ingrese una opción.
        opcion = await DesplegarMenu("Opciones de Productos", datosmenuproductos);

        // Si el usuario no ingresa nada (opcion es nula o vacía), muestra un mensaje.
        if (!opcion) console.log("opcion incorrecta ");
        // Si ingresó una opción, evalúa cuál fue.
        else switch (opcion) {
            case "1":
                console.log("Modificar Precio Producto");
                break; // Termina este caso.
            case "2":
                console.log("Listado Producto");
                break; // Termina este caso.
            case "3":
                console.log("Salida del Sistema");
                break; // Termina este caso y prepara la salida del bucle.
            default:
                // Se ejecuta si la opción no coincide con ningún caso anterior.
                console.log("No existe esta opcion");
                break;
        }
        // El bucle continúa mientras la opción sea diferente de "3".
    } while (opcion !== "3");
}

/**
 * Tipo: Procedimiento asíncrono.
 * Parámetros:
 * - idticket: Una cadena (string) con el número del último ticket generado.
 * Propósito: Gestiona el menú del punto de venta para un nuevo ticket. Calcula el
 * siguiente número de ticket, muestra un encabezado con la fecha y el nuevo número,
 * y permite al usuario agregar, eliminar, listar artículos, pagar o cancelar la venta.
 * Devuelve: Nada.
 */
async function MenuPuntoVenta(idticket) {
    let opcion, membrete; // Declara variables para la opción y el encabezado del menú.
    let pago = false; // Bandera para saber si el ticket fue pagado.

    // Calcula el número del siguiente ticket.
    idticket = IdTicketSiguiente(idticket);
    // Obtiene la fecha actual.
    let fechadia = Fecha();
    // Crea el encabezado que se mostrará en el menú.
    membrete = `Fecha del Dia ${fechadia} Ticket No ${idticket}`;
    membrete += "\n-------------------------------------------------------\n";
    // Define las opciones del menú de ventas.
    const datosmenu = ["1. - Agregar ", "2. - Eliminar ", "3. - Listado ", "4. - Pagar ", "5. - Salida"];

    // Inicia un bucle que se repetirá hasta que se elija salir.
    do {
        // Muestra el menú de ventas con su encabezado y espera la opción del usuario.
        opcion = await DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu);

        // Si la opción introducida no es válida.
        if (!opcion) console.log("dato incorrecto introducido");
        // Evalúa la opción seleccionada.
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
                // Cambia la opción a "5" para forzar la salida del bucle.
                opcion = "5";
                // Marca la bandera 'pago' como verdadera.
                pago = true;
                break;
            case "5":
                console.log("Salida del Ventas");
                // Si se sale sin haber pagado...
                if (!pago) {
                    // ...informa que el ticket no se pagó y se eliminará.
                    console.log("No pago el ticket");
                    console.log("eliminando tickte" + idticket);
                }
                break;
            default:
                console.log("No existe esta opcion");
                break;
        }
        // El bucle continúa mientras la opción sea diferente de "5".
    } while (opcion !== "5");
}

/**
 * Tipo: Procedimiento asíncrono.
 * Parámetros: Ninguno.
 * Propósito: Despliega el menú de gestión de inventarios, permitiendo al usuario
 * listar, agregar o salir del módulo. Se mantiene activo hasta que se elige salir.
 * Devuelve: Nada.
 */
async function MenuInventario() {
    // Define las opciones del menú de inventarios.
    const datosmenuinventarios = ["1. - Listado ", "2. - Agregar ", "3. - Salida "];
    let opcion = "0"; // Inicializa la variable de control del bucle.

    // Bucle que se ejecuta hasta que la opción sea "3".
    do {
        // Muestra el menú y espera la selección del usuario.
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
 * Parámetros: Ninguno.
 * Propósito: Es el menú principal de la aplicación. Desde aquí se puede navegar
 * a los submenús de Productos, Punto de Venta e Inventarios, o salir del programa.
 * Devuelve: Nada.
 */
async function MenuPrincipal() {
    // Define las opciones del menú principal.
    const datosmenuprincipal = ["1.-Productos ", "2.-Punto de Venta ", "3.- Inventarios", "5. Salida"];
    let opcion = "0"; // Inicializa la opción para el bucle.

    // Bucle principal de la aplicación.
    do {
        // Muestra el menú principal y espera la opción del usuario.
        opcion = await DesplegarMenu("Menu de Punto de Tienda de Abarrotes", datosmenuprincipal);

        if (!opcion)
            console.log("opcion incorrecta ");
        else switch (opcion) {
            // Llama a los submenús correspondientes esperando a que terminen (await).
            case "1": await MenuProductos(); break;
            case "2": await MenuPuntoVenta("000"); break; // Inicia ventas con el ticket "000".
            case "3": await MenuInventario(); break;
            case "5": console.log("Salida del Sistema"); break;
            default: console.log("No existe esta opcion"); break;
        }
        // El bucle se repite hasta que el usuario elija la opción "5".
    } while (opcion !== "5");
}

// Esta es una función asíncrona autoejecutable (IIFE - Immediately Invoked Function Expression).
// Su propósito es iniciar la aplicación llamando a la función principal 'MenuPrincipal'.
(async () => {
    // Espera a que el Menú Principal termine su ejecución.
    await MenuPrincipal();
})();