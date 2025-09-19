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
            valido = esNumeroEntero(dato);
            break;
        case 2:
            valido = esNumeroDouble(dato);
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

    // Separa la cadena en un arreglo usando el espacio y el car�cter ":"
    // Reemplaza los espacios por barras diagonales '/'
    // Invierte el orden de los elementos en el arreglo
    // Une los elementos del arreglo en una sola cadena usando el gui�n '-'
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
 * Tipo: Procedimiento as�ncrono.
 * Par�metros: Ninguno.
 * Prop�sito: Muestra un men� de opciones relacionadas con la gesti�n de productos.
 * Permite al usuario seleccionar entre modificar, listar o salir. El men� se
 * repetir� hasta que el usuario elija la opci�n de salida.
 * Devuelve: Nada.
 */
async function MenuProductos() {
    // Define las opciones que se mostrar�n en el men� de productos.
    const datosmenuproductos = ["1.-Modificar ", "2.-Listado ", "3.-Salida"];
    let opcion = "0"; // Inicializa la variable 'opcion' para controlar el bucle.

    // Inicia un bucle que se ejecutar� al menos una vez.
    do {
        // Muestra el men� y espera (await) a que el usuario ingrese una opci�n.
        opcion = await DesplegarMenu("Opciones de Productos", datosmenuproductos);

        // Si el usuario no ingresa nada (opcion es nula o vac�a), muestra un mensaje.
        if (!opcion) console.log("opcion incorrecta ");
        // Si ingres� una opci�n, eval�a cu�l fue.
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
                // Se ejecuta si la opci�n no coincide con ning�n caso anterior.
                console.log("No existe esta opcion");
                break;
        }
        // El bucle contin�a mientras la opci�n sea diferente de "3".
    } while (opcion !== "3");
}

/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros:
 * - idticket: Una cadena (string) con el n�mero del �ltimo ticket generado.
 * Prop�sito: Gestiona el men� del punto de venta para un nuevo ticket. Calcula el
 * siguiente n�mero de ticket, muestra un encabezado con la fecha y el nuevo n�mero,
 * y permite al usuario agregar, eliminar, listar art�culos, pagar o cancelar la venta.
 * Devuelve: Nada.
 */
async function MenuPuntoVenta(idticket) {
    let opcion, membrete; // Declara variables para la opci�n y el encabezado del men�.
    let pago = false; // Bandera para saber si el ticket fue pagado.

    // Calcula el n�mero del siguiente ticket.
    idticket = IdTicketSiguiente(idticket);
    // Obtiene la fecha actual.
    let fechadia = Fecha();
    // Crea el encabezado que se mostrar� en el men�.
    membrete = `Fecha del Dia ${fechadia} Ticket No ${idticket}`;
    membrete += "\n-------------------------------------------------------\n";
    // Define las opciones del men� de ventas.
    const datosmenu = ["1. - Agregar ", "2. - Eliminar ", "3. - Listado ", "4. - Pagar ", "5. - Salida"];

    // Inicia un bucle que se repetir� hasta que se elija salir.
    do {
        // Muestra el men� de ventas con su encabezado y espera la opci�n del usuario.
        opcion = await DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu);

        // Si la opci�n introducida no es v�lida.
        if (!opcion) console.log("dato incorrecto introducido");
        // Eval�a la opci�n seleccionada.
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
                // Cambia la opci�n a "5" para forzar la salida del bucle.
                opcion = "5";
                // Marca la bandera 'pago' como verdadera.
                pago = true;
                break;
            case "5":
                console.log("Salida del Ventas");
                // Si se sale sin haber pagado...
                if (!pago) {
                    // ...informa que el ticket no se pag� y se eliminar�.
                    console.log("No pago el ticket");
                    console.log("eliminando tickte" + idticket);
                }
                break;
            default:
                console.log("No existe esta opcion");
                break;
        }
        // El bucle contin�a mientras la opci�n sea diferente de "5".
    } while (opcion !== "5");
}

/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros: Ninguno.
 * Prop�sito: Despliega el men� de gesti�n de inventarios, permitiendo al usuario
 * listar, agregar o salir del m�dulo. Se mantiene activo hasta que se elige salir.
 * Devuelve: Nada.
 */
async function MenuInventario() {
    // Define las opciones del men� de inventarios.
    const datosmenuinventarios = ["1. - Listado ", "2. - Agregar ", "3. - Salida "];
    let opcion = "0"; // Inicializa la variable de control del bucle.

    // Bucle que se ejecuta hasta que la opci�n sea "3".
    do {
        // Muestra el men� y espera la selecci�n del usuario.
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
 * Par�metros: Ninguno.
 * Prop�sito: Es el men� principal de la aplicaci�n. Desde aqu� se puede navegar
 * a los submen�s de Productos, Punto de Venta e Inventarios, o salir del programa.
 * Devuelve: Nada.
 */
async function MenuPrincipal() {
    // Define las opciones del men� principal.
    const datosmenuprincipal = ["1.-Productos ", "2.-Punto de Venta ", "3.- Inventarios", "5. Salida"];
    let opcion = "0"; // Inicializa la opci�n para el bucle.

    // Bucle principal de la aplicaci�n.
    do {
        // Muestra el men� principal y espera la opci�n del usuario.
        opcion = await DesplegarMenu("Menu de Punto de Tienda de Abarrotes", datosmenuprincipal);

        if (!opcion)
            console.log("opcion incorrecta ");
        else switch (opcion) {
            // Llama a los submen�s correspondientes esperando a que terminen (await).
            case "1": await MenuProductos(); break;
            case "2": await MenuPuntoVenta("000"); break; // Inicia ventas con el ticket "000".
            case "3": await MenuInventario(); break;
            case "5": console.log("Salida del Sistema"); break;
            default: console.log("No existe esta opcion"); break;
        }
        // El bucle se repite hasta que el usuario elija la opci�n "5".
    } while (opcion !== "5");
}

// Esta es una funci�n as�ncrona autoejecutable (IIFE - Immediately Invoked Function Expression).
// Su prop�sito es iniciar la aplicaci�n llamando a la funci�n principal 'MenuPrincipal'.
(async () => {
    // Espera a que el Men� Principal termine su ejecuci�n.
    await MenuPrincipal();
})();