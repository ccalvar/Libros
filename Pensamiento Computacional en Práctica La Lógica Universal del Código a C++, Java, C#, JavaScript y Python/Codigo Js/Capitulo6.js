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
    const readline = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });

    return new Promise(resolve => {
        readline.question(texto+" ", ans => {
            readline.close();
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
    cadena += "\n Que opcion deseas : ";
    return await Dialogo(cadena);
}

function RellenarEspacios(dato, tamano) {
    return dato.padEnd(tamano);
}

function Fecha() {
    const date = new Date();

    return date.toLocaleDateString('en-GB').split(' : ')
        .map(part => part.replace(' ', '/'))
        .reverse()
        .join('-');
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


function CargarProductos() {
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
    return producto;
}


function MostrarProducto(vproducto) {
    let codigo = RellenarEspacios(vproducto[0], 5);
    let producto = RellenarEspacios(vproducto[1], 30);
    let precio = RellenarEspacios(vproducto[2], 10);
    let cantidad = RellenarEspacios(vproducto[3], 10);
    let cadena = codigo + producto + precio + cantidad;
    return cadena;
}

function MostrarLista(vproductos) {
    let salida = "";
    for (let ciclo = 0; ciclo < 10; ciclo++) {
        let vproducto = [vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3]];
        let cadena = MostrarProducto(vproducto);
        salida += cadena + "\n";
    }
    return salida;
}

function ExisteProducto(codigo, vproductos) {
    let enc = -1;
    let pos = 0;
    for (let ciclo = 0; ciclo < vproductos.length; ciclo++) {
        if (vproductos[ciclo][0].trim() === codigo.trim()) {
            enc = pos;
        }
        pos++;
    }
    return enc;
}

async function ModificarProducto(vproductos) {
    let codigo, precio;
    let posicion;
    let info = MostrarLista(vproductos);
    codigo = await Leer(info + "\nIntroduce el codigo del producto a modificar");
    if (codigo !== null) {
        posicion = ExisteProducto(codigo, vproductos);
        if (posicion > -1) {
            let vproducto = [vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2], vproductos[posicion][3]];
            precio = await Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ");
            if (precio !== null) {
                if (EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1)) {
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



async function MenuProductos(vproductos) {
    const datosmenuproductos = ["1.-Modificar", "2.-Listado", "3.-Salida "];
    let opcion = "0";

    do {
        opcion = await DesplegarMenu("Opciones de Productos ", datosmenuproductos);
        if (opcion !== null) {
            switch (opcion) {
                case "1":
                    await ModificarProducto(vproductos);
                    break;
                case "2":
                    console.log(MostrarLista(vproductos));
                    break;
                case "3":
                    console.log("Salida del Sistema ");
                    break;
                default:
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


/**
 * Tipo: Procedimiento asíncrono.
 * Parámetros:
 * - vproductos: El arreglo (Array) de productos cuyo stock se va a modificar.
 * Propósito: Permite al usuario agregar stock a un producto existente. Muestra la lista,
 * solicita un código de producto, pide la cantidad a agregar y actualiza el inventario
 * de ese producto en el arreglo principal.
 * Devuelve: Nada (modifica el arreglo original directamente).
 */
async function AgregarStock(vproductos) {
    // Muestra la lista completa de productos para que el usuario pueda ver los códigos.
    const info = MostrarLista(vproductos);
    // Pide al usuario que introduzca el código del producto al que quiere agregar stock.
    const codigo = await Leer(info + "\nIntroduce el codigo del producto a modificar");

    // Si el usuario introdujo un código (no es nulo ni vacío)...
    if (codigo) {
        // ...busca la posición del producto en el arreglo.
        const posicion = ExisteProducto(codigo, vproductos);
        // Si la posición es mayor a -1, el producto fue encontrado.
        if (posicion > -1) {
            // Prepara un arreglo temporal con los datos del producto para mostrarlos.
            const vproducto = [
                vproductos[posicion][0], // Código
                vproductos[posicion][1], // Nombre
                vproductos[posicion][3], // Cantidad actual (stock)
                "" // Espacio para el precio (no se usa aquí, se deja vacío)
            ];
            // Pide al usuario que introduzca la cantidad de stock a agregar.
            const cantidad = await Leer("\nIntroduce la Cantidad de Stock a Agregar " + MostrarProducto(vproducto) + " ");

            // Si el usuario introdujo una cantidad...
            if (cantidad) {
                // ...verifica que sea un valor numérico (entero o decimal).
                if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1)) {
                    // Calcula la nueva cantidad sumando el stock actual con el ingresado.
                    // Se convierten ambos a entero (parseInt) para asegurar una suma matemática.
                    const nuevacantidad = parseInt(cantidad) + parseInt(vproducto[2]);
                    // Actualiza la cantidad de stock en el arreglo original, convirtiendo el número a string.
                    vproductos[posicion][3] = nuevacantidad.toString();
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
 * Propósito: Despliega y gestiona el menú de inventarios, permitiendo al usuario
 * listar los productos, agregar stock o salir del módulo.
 * Devuelve: Nada.
 */
async function MenuInventario(vproductos) {
    // Define las opciones del menú de inventarios.
    const datosmenuinventario = ["1.-Listado ", "2.-Agregar ", "3.-Salida "];
    let opcion = "0"; // Inicializa la variable de control del bucle.

    // Bucle que se repite hasta que el usuario elija la opción "3".
    do {
        // Muestra el menú y espera la selección del usuario.
        opcion = await DesplegarMenu("Opciones de Inventarios", datosmenuinventario);

        // Si la opción es nula (entrada vacía).
        if (opcion === null) {
            console.log("opcion incorrecta");
        } else {
            // Evalúa la opción seleccionada.
            switch (opcion) {
                case "1":
                    // Muestra la lista de productos con su stock actual.
                    console.log(MostrarLista(vproductos));
                    break;
                case "2":
                    // Llama a la función para agregar stock, pasando el arreglo de productos.
                    await AgregarStock(vproductos);
                    break;
                case "3":
                    // Muestra un mensaje de salida del módulo.
                    console.log("Salida del Sistema");
                    break;
                default:
                    // Se ejecuta si la opción no es válida.
                    console.log("No existe esta opcion");
            }
        }
    } while (opcion !== "3");
}

/**
 * Tipo: Procedimiento asíncrono.
 * Parámetros:
 * - vproductos: Un arreglo (Array) que contiene la lista completa de productos.
 * Propósito: Funciona como el menú principal y el controlador central de la aplicación.
 * Desde aquí, el usuario puede navegar a los diferentes módulos del sistema.
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

        if (!opcion)
            console.log("opcion incorrecta ");
        else switch (opcion) {
            case "1":
                await MenuProductos(vproductos); // Va al menú de productos.
                break;
            case "2":
                await MenuPuntoVenta("000"); // Va al menú de ventas.
                break;
            case "3":
                await MenuInventario(vproductos); // Va al menú de inventarios, pasando la lista de productos.
                break;
            case "5":
                console.log("Salida del Sistema"); // Mensaje de despedida.
                break;
            default:
                console.log("No existe esta opcion"); // Mensaje para opciones no válidas.
                break;
        }
    } while (opcion !== "5");
}

// ----------------------------------------------------------------------------------
// PUNTO DE INICIO DE LA APLICACIÓN
// ----------------------------------------------------------------------------------
// Se utiliza una función asíncrona autoejecutable (IIFE) para iniciar el programa.
(async () => {
    // 1. Carga los datos iniciales de los productos en una variable.
    let productos = CargarProductos();
    // 2. Ejecuta el menú principal y le pasa la lista de productos para que toda la aplicación pueda usarla.
    await MenuPrincipal(productos);
})();
