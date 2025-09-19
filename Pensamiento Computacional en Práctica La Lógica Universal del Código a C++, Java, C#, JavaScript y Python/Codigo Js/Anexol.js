// Importa el módulo 'fs' (File System) de Node.js.
// Se utiliza para interactuar con el sistema de archivos (leer y escribir archivos).
const fs = require('fs');

// Importa el módulo 'readline' de Node.js.
// Permite leer datos de un stream, como la entrada del teclado en la consola.
const readline = require('readline');

// Variable que almacenará el arreglo principal con todo el inventario de productos.
let productos;

// Variable que contendrá el arreglo con el historial de todas las ventas registradas.
let ventas;

// Contador para rastrear la última posición (índole) utilizada en el arreglo 'ventas'.
// Inicia en -1 para indicar que el arreglo está vacío.
let posventas = -1;

// Define el tamaño máximo o la capacidad del arreglo 'ventas'.
// En este caso, se podrán almacenar hasta 100 registros de venta.
let tamventas = 100;

// Variable destinada a guardar la fecha actual para las transacciones.
let fecha;


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
        readline.question(texto, ans => {
            readline.close();
            resolve(ans);
        });
    });
}

async function Leer(texto) {
    let cadena = await Dialogo(texto);
    console.log(cadena)
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
    cadena += "\n Que opcion deseas";
    return await Dialogo(cadena);
}

//function RellenarEspacios(dato, tamano) {
//   return dato.padEnd(tamano);
//}


function RellenarEspacios(dato, tamano) {
    return String(dato).padEnd(tamano);
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

function ObtenerUltimaPosicion(matriz) {
    let ultimaPosicion = -1;
    for (let i = 0; i < matriz.length; i++) {
        if (matriz[i][0] !== null && matriz[i][0] !== '') {
            ultimaPosicion = i;
        }
    }
    return ultimaPosicion;
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

//actuakkizar esto en el kbro
function MostrarLista(vproductos) {
    let salida = "";
    for (let ciclo = 0; ciclo < 10; ciclo++) {
        const vproducto = [vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3]];
        const cadena = MostrarProducto(vproducto);
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
            let vproducto = [vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2]];
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

function CrearVenta() {
    const venta = Array.from({ length: tamventas }, () => new Array(5).fill(null));
    return venta;
}

function UltimoTicket(pos, mventa) {
    let idticket = "000";
    if (pos > -1) {
        idticket = mventa[pos][0];
    }
    return idticket;
}

function CrearTicket() {
    return new Array(20, 4);
}


function ExisteTicketCodigo(mticket, codigo) {
    let enc = -1;
    let pos = ObtenerUltimaPosicion(mticket);
    for (let ciclo = 0; ciclo <= pos; ciclo++)
        if (mticket[ciclo][0] === codigo)  
            enc = ciclo;
    return enc;
}

function InsertarProductoTicket(mticket, datos, tamticket) {
    let sucedio = true;
    let posticket = ObtenerUltimaPosicion(mticket);

    let enc = ExisteTicketCodigo(mticket, datos[0]);
    console.log("buscar " + datos[0] + "  pos existe " + enc + "    Ultima--> " + posticket);
    if (posticket < tamticket) {
        if (enc > -1) {
            console.log("ya existe el producto en el ticket lo incrementare");
            let cantidadactual = parseInt(mticket[enc][3]);
            mticket[enc][3] = (cantidadactual + 1).toString();
        } else {
            posticket++;
            mticket[posticket][0] = datos[0];
            mticket[posticket][1] = datos[1];
            mticket[posticket][2] = datos[2];
            mticket[posticket][3] = datos[3];
            console.log("Insertarndo No existe el producto en el ticket ");
        }
    } else {
        sucedio = false;
    }
    return sucedio;
}

function TotalProducto(precio, cantidad) {
    const total = parseFloat(precio) * parseFloat(cantidad);
    return total.toFixed(2);
}



function MostrarProductoTicket(mticket, pos) {
    let codigo = RellenarEspacios(mticket[pos][0], 5);
    let producto = RellenarEspacios(mticket[pos][1], 30);
    let precio = RellenarEspacios(mticket[pos][2], 10);
    let cantidad = RellenarEspacios(mticket[pos][3], 5);
    let totalproducto = RellenarEspacios(TotalProducto(mticket[pos][2], mticket[pos][3]), 10);
    let cadena = codigo.concat(producto + precio + cantidad + totalproducto);
    return cadena;
}

function MostrarTicket(mticket) {
    let salida = "";
    let pos = ObtenerUltimaPosicion(mticket);
    if (pos > -1)
    for (let ciclo = 0; ciclo <= pos; ciclo++) {
        salida += MostrarProductoTicket(mticket, ciclo) + "\n";
    }
    return salida;
}

function SubTotalTicket(mticket) {
    let subtotal = 0;
    let pos = ObtenerUltimaPosicion(mticket);
    for (let ciclo = 0; ciclo <= pos; ciclo++) {
        subtotal += parseFloat(TotalProducto(mticket[ciclo][2], mticket[ciclo][3]));
    }
    return subtotal;
}

function IvaTicket(mticket) {
    let subtotal = SubTotalTicket(mticket);
    if (subtotal > 0)
        subtotal = 0.16 * subtotal;
    else
        subtotal = -1;
    return subtotal;
}

function TotalTicket(mticket) {
    let total = SubTotalTicket(mticket);
    if (total > 0)
        total = IvaTicket(mticket) + total;
    return total;
}

function MostrarTicketVenta(mticket, idticket, fecha) {
    let salida = "";
    let subtotal = SubTotalTicket(mticket).toFixed(2);
    let iva = IvaTicket(mticket).toFixed(2);
    let total = TotalTicket(mticket).toFixed(2);
    salida = "Fecha " + fecha + " Ticket No." + idticket;
    salida += "\n" + MostrarTicket(mticket);
    salida += "\n\n El total sin iva " + subtotal;
    salida += "\n el iva total es " + iva;
    salida += "\n el total de la venta fue " + total;
    return salida;
}



function MostrarListaProductosVenta(vproductos) {
    let salida = "";
    for (let ciclo = 0; ciclo < 10; ciclo++) {
        let existencia = parseInt(vproductos[ciclo][3]);
        if (existencia > 0) {
            let vproducto = vproductos[ciclo].slice();  // Clona el array
            let cadena = MostrarProducto(vproducto);
            salida += cadena + "\n";  // Concatenar con nueva línea
        }
    }
    return salida;
}


async function CapturaVentaProducto(mticket, mproductos, idticket, tamticket) {
    let codigo, info;
    info = MostrarListaProductosVenta(mproductos);

    codigo = await Leer(info + "\nIntroduce el codigo del producto");
    if (codigo !== null) {
        let posp = ExisteProducto(codigo.trim(), mproductos);
        if (posp > -1) {
            if (parseInt(mproductos[posp][3]) > 0) {

                let cant = parseInt(mproductos[posp][3]);
                cant = cant - 1
                mproductos[posp][3] = cant.toString();
                let producto = [...mproductos[posp]];

                console.log(MostrarProducto(producto));
                let venta = new Array(4);
                venta[0] = mproductos[posp][0];
                venta[1] = mproductos[posp][1];
                venta[2] = mproductos[posp][2];
                venta[3] = "1";
                if (!InsertarProductoTicket(mticket, venta, tamticket))
                    console.log("el Arreglo esta lleno \n");
            } else {
                console.log("no hay productos para venta");
            }
        } else {
            console.log("el codigo no existe no se puede agregar\n");
        }
    } else {
        console.log("dato nulo\n");
    }
}

function RemoverProductoTicket(mticket, pos) {
    let tam = ObtenerUltimaPosicion(mticket);
    console.log(" ultima posucion tam");
    if (tam > pos) {
        for (let i = pos; i < tam+1; i++) {
            mticket[i] = mticket[i + 1];
        }
        mticket[tam][0] = null;
    } else {
        mticket[pos][0] = null;
    }
}

function EliminarProductoTicket(mticket, pos) {
    let cantidad = parseInt(mticket[pos][3]);
    if (cantidad > 1) {
        mticket[pos][3] = (cantidad - 1).toString();
    } else {
        RemoverProductoTicket(mticket, pos);
    }
}


async function Eliminar(mticket,mproductos) {
    let info;
    info = MostrarTicket(mticket);
    console.log(" eliminar");
    let codigo = await Leer(info + "\nIntroduce el codigo del producto");
    if (codigo !== null) {
        let pos = ExisteTicketCodigo(mticket, codigo);
        if (pos > -1) {
            let posproducto = ExisteProducto(codigo, mproductos);
            let nuevacantidad = (parseInt(mproductos[posproducto][3]) + 1).toString();
            mproductos[posproducto][3] = nuevacantidad;
            EliminarProductoTicket(mticket, pos);
        }
    } else {
        console.log("dato nulo");
    }
}




function AgregarProductoAVenta(mticket, mventa, idticket) {
    let posventas = ObtenerUltimaPosicion(mventa);
    let posticket = ObtenerUltimaPosicion(mticket);
    for (let i = 0; i <= posticket; i++) {
        let codigoProducto = mticket[i][0];
        if (codigoProducto !== null) { // Verificar que la fila no esté vacía
            posventas++;
            mventa[posventas] = [
                idticket, // Establecer el ID del ticket
                codigoProducto, // Código del producto
                mticket[i][1], // Nombre del producto
                mticket[i][2], // Precio del producto
                mticket[i][3]  // Cantidad del producto
            ];
        }
    }
}

function Pagar(idticket, mventa, mticket) {
    let posventas = ObtenerUltimaPosicion(mventa);
    let post = ObtenerUltimaPosicion(mticket);
    if ((posventas + post) < 100) {
        AgregarProductoAVenta(mticket, mventa, idticket);
    } else {
        console.log("Desbordamiento de Memoria de ventas");
    }
}

function DevolucionTicket(mticket, mproductos) {
    let posmticket = ObtenerUltimaPosicion(mticket);

    for (let pos = 0; pos <= posmticket; pos++) {
        let codigo = mticket[pos][0];
        let posp = ExisteProducto(codigo.trim(), mproductos);
        if (posp > -1) {
            let cant = parseInt(mticket[pos][3]) + parseInt(mproductos[posp][3]);
            mproductos[posp][3] = String(cant);
        }
    }
}


async function MenuPuntoVenta(ventas, idticket, productos,narchivo) {
    let opcion, membrete;
    let pago = false;
    let tamticket = 50;
    let Vticket = Array.from({ length: tamticket }, () => new Array(4).fill(null)); // Inicializa con `null`
    console.log("recibi el idtcket " + idticket);
    idticket = await IdTicketSiguiente(idticket);
    
    let fechadia = await Fecha();
    opcion = "";
    do {
        membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
        membrete += "\n-----------------------------------------------------\n";
        let Tickettexto = MostrarTicket(Vticket).trim();
        if (Tickettexto.trim() !== "") {
            membrete += "\n" + Tickettexto + "\n";
        }
        let datosmenu = ["1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida "];
        opcion = await DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu);
        if (opcion === null) {
            console.log("dato incorrecto introducido");
        } else {
            switch (opcion) {
                case "1":
                    await CapturaVentaProducto(Vticket, productos, idticket, tamticket);
                    break;
                case "2":
                    await Eliminar(Vticket);
                    break;
                case "3":
                    if (ObtenerUltimaPosicion(Vticket) > -1)
                        console.log(MostrarTicket(Vticket));
                    break;
                case "4":
                    console.log(MostrarTicketVenta(Vticket, idticket, fechadia).trim());
                    await Pagar(idticket, ventas, Vticket);
                    if (ObtenerUltimaPosicion(Vticket) > -1) {
                        console.log("tamaño de venta" + ObtenerUltimaPosicion(ventas) + " " + ObtenerUltimaPosicion(Vticket));
                        GuardarDatosCsvVentaTicket(Vticket, narchivo, ObtenerUltimaPosicion(Vticket), idticket);
                        let cadena = generarCsvFilaVenta(fechadia, idticket, SubTotalTicket(Vticket).toFixed(2), IvaTicket(Vticket).toFixed(2), TotalTicket(Vticket).toFixed(2));
                        GuardarDatosCsvVenta("ventas.csv", cadena);
                       
                    }


                    pago = true;
                    opcion = "5";
                    break;




                case "5":
                    console.log("Salida del Ventas");
                    if (!pago) {
                        console.log("No pago el ticket");
                        console.log("eliminando ticket " + idticket);
                        DevolucionTicket(Vticket, productos);
                    }
                    break;
                default:
                    console.log("No existe esta opcion");
                    break;
            }
        }
    } while (opcion !== "5");
}

function MostrarVenta(venta) {
    let idticket = RellenarEspacios(venta[0], 6);
    let codigo = RellenarEspacios(venta[1], 5);
    let producto = RellenarEspacios(venta[2], 30);
    let precio = RellenarEspacios(venta[3], 10);
    let cantidad = RellenarEspacios(venta[4], 10);
    let cadena = idticket.concat(codigo + producto + precio + cantidad);
    return cadena;
}


function MostrarListaVentas(ventas) {
    let posventas = ObtenerUltimaPosicion(ventas);
    let salida = "";
    for (let ciclo = 0; ciclo <= posventas; ciclo++) {
        let venta = [ventas[ciclo][0], ventas[ciclo][1], ventas[ciclo][2], ventas[ciclo][3], ventas[ciclo][4]];
        let cadena = MostrarVenta(venta);
        salida = salida.concat(cadena + "\n");
    }
    return salida;
}



async function AgregarStock(vproductos) {
    const info = MostrarLista(vproductos);
    const codigo = await Leer(info + "\nIntroduce el codigo del producto a modificar");

    if (codigo) {
        const posicion = ExisteProducto(codigo, vproductos);
        if (posicion > -1) {
            const vproducto = [
                vproductos[posicion][0],
                vproductos[posicion][1],
                vproductos[posicion][3],
                ""
            ];
            const cantidad = await Leer("\nIntroduce la Cantidad de Stock a Agregar " + MostrarProducto(vproducto) + " ");

            if (cantidad) {
                if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1)) {
                    const nuevacantidad = parseInt(cantidad) + parseInt(vproducto[2]);
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


async function MenuInventario(vproductos) {
    const datosmenuinventario = ["1.-Listado ", "2.-Agregar ", "3.-Salida "];
    let opcion = "0";

    do {
        opcion = await DesplegarMenu("Opciones de Inventarios", datosmenuinventario);

        if (opcion === null) {
            console.log("opcion incorrecta");
        } else {
            switch (opcion) {
                case "1":
                    console.log(MostrarLista(vproductos));
                    break;
                case "2":
                    await AgregarStock(vproductos);
                    break;
                case "3":
                    console.log("Salida del Sistema");
                    break;
                default:
                    console.log("No existe esta opcion");
            }
        }
    } while (opcion !== "3");
}



async function MenuPrincipal(vproductos, vventas) {
    let datosmenuprincipal = ["1.-Productos ", "2.-Punto de Venta ", "3.- Inventario", "4.-Ventas", "5.-Salida "];
    let opcion = "0";
    let idticket = "000";

    let narchivo = Fecha() + ".csv";
    narchivo = narchivo.replace(/\//g, "-");
    console.log("buscando " + narchivo);
    if (ExisteArchivo(narchivo)) {
        {
            console.log("si existe "+narchivo);
            idticket = await LeerDatosCSV(narchivo);
            console.log(idticket + " se obtuvo " + idticket);
        }

    }
    do {
        if (idticket == "000")
            idticket = ObtenerUltimoValorVentas(vventas);

        opcion = await DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña", datosmenuprincipal);
        if (opcion === null) {
            console.log("opcion incorrecta ");
        } else {
            switch (opcion) {
                case "1":
                    await MenuProductos(vproductos);
                    break;
                case "2":
                    await MenuPuntoVenta(vventas, idticket, vproductos,narchivo); idticket = "000";
                    break;
                case "3":
                    await MenuInventario(vproductos);
                    break;
                case "4": 
                    console.log(await MostrarListaVentas(vventas));
                    break;
                case "5":
                    console.log("Salida del Sistema ");
                    
                    break;
                default:
                    console.log("No existe esta opcion ");
                    break;
            }
        }
    } while (opcion !== "5");
}

function ObtenerUltimoValorVentas(ventas) {
    let ultimoValor = "000";
    let tam = ObtenerUltimaPosicion(ventas)
    if (tam >=0)
         ultimoValor = ventas[tam][0];
    return ultimoValor;
}


/**
 * Tipo: Función
 * Parámetros:
 * - narchivo: El nombre o ruta del archivo a verificar.
 * Propósito: Comprobar de forma síncrona si un archivo existe en el sistema.
 * Devuelve: 'true' si el archivo existe, 'false' si no.
 */
function ExisteArchivo(narchivo) {
    // Usa un bloque try-catch para manejar el error que se produce si el archivo no existe.
    try {
        // fs.accessSync verifica el acceso al archivo. Lanza un error si falla.
        // fs.constants.F_OK comprueba únicamente la existencia del archivo.
        fs.accessSync(narchivo, fs.constants.F_OK);
        return true; // Si no hay error, el archivo existe.
    } catch (e) {
        return false; // Si se captura un error, el archivo no existe.
    }
}

/**
 * Tipo: Procedimiento
 * Parámetros:
 * - archivo: El nombre del archivo en el que se va a escribir.
 * - contenido: La cadena de texto que se va a agregar al archivo.
 * Propósito: Agregar (append) una línea de contenido al final de un archivo de texto.
 * Devuelve: Nada.
 */
function EscribirArchivoCSV(archivo, contenido) {
    try {
        // fs.appendFileSync agrega contenido a un archivo de forma síncrona.
        // Si el archivo no existe, lo crea. Agrega un salto de línea '\n' al final.
        fs.appendFileSync(archivo, contenido + '\n', 'utf8');
    } catch (error) {
        // En caso de error, lo muestra en la consola.
        console.error("Error al escribir en el archivo:", error.message);
    }
}

/**
 * Tipo: Función
 * Parámetros:
 * - dato1 a dato5: Los datos que compondrán la fila (ej: idticket, código, nombre, precio, cantidad).
 * Propósito: Formatear una fila de datos para un archivo CSV de un ticket, incluyendo
 * el cálculo del total del producto.
 * Devuelve: Una cadena (string) con los datos separados por comas.
 */
function GenerarCVSFilaTicket(dato1, dato2, dato3, dato4, dato5) {
    // Crea una cadena separada por comas y añade el total del producto al final.
    return `${dato1},${dato2},${dato3},${dato4},${dato5},${TotalProducto(dato4, dato5)}`;
}

/**
 * Tipo: Procedimiento
 * Parámetros:
 * - matriz: El arreglo bidimensional con los datos del ticket.
 * - nombrearchivo: El nombre del archivo donde se guardarán los datos.
 * - filas: El número de filas válidas en la matriz.
 * - idticket: El ID del ticket que se está guardando.
 * Propósito: Guardar todos los productos de un ticket en un archivo CSV.
 * Devuelve: Nada.
 */
function GuardarDatosCsvVentaTicket(matriz, nombrearchivo, filas, idticket) {
    let cadena = ""; // Inicializa una cadena para almacenar todo el contenido.
    // Itera sobre cada fila de la matriz del ticket.
    for (let fila = 0; fila <= filas; fila++) {
        // Genera la línea en formato CSV para la fila actual.
        let cadenafila = GenerarCVSFilaTicket(idticket, matriz[fila][0], matriz[fila][1], matriz[fila][2], matriz[fila][3]);
        // Agrega la fila formateada (con un salto de línea) a la cadena principal.
        cadena += cadenafila + "\n";
    }
    // Escribe la cadena completa con todas las filas en el archivo.
    EscribirArchivoCSV(nombrearchivo, cadena);
}

/**
 * Tipo: Función asíncrona
 * Parámetros:
 * - nombreArchivo: El nombre del archivo CSV a leer.
 * Propósito: Leer un archivo CSV para obtener el primer campo (generalmente el ID de ticket)
 * de la última línea del archivo.
 * Devuelve: Una Promesa (Promise) que se resuelve con el dato encontrado o 'null' si hay un error o el archivo está vacío.
 */
async function LeerDatosCSV(nombreArchivo) {
    let primerDato = "";
    try {
        // Lee todo el contenido del archivo de forma síncrona.
        const contenido = fs.readFileSync(nombreArchivo, 'utf8').trim();
        // Divide el contenido en líneas y filtra las que estén vacías.
        const lineas = contenido.split('\n').filter(linea => linea.trim() !== "");
        // Si hay líneas, toma la última, la divide por comas y extrae el primer elemento.
        primerDato = lineas.length ? lineas[lineas.length - 1].split(",")[0] : null;
        console.log("leyendo" + primerDato);
    } catch (e) {
        // Maneja errores de lectura.
        console.error("Error al leer el archivo:", e.message);
        primerDato = null;
    }
    // Devuelve el dato encontrado.
    return primerDato;
}

/**
 * Tipo: Función
 * Parámetros:
 * - dato1 a dato5: Los datos que compondrán la fila.
 * Propósito: Formatear una fila para el archivo CSV del historial de ventas.
 * Devuelve: Una cadena (string) con los datos limpios (sin espacios) y separados por comas.
 */
function generarCsvFilaVenta(dato1, dato2, dato3, dato4, dato5) {
    // .trim() elimina espacios en blanco al inicio y final de cada dato antes de unirlos.
    return `${dato1.trim()},${dato2.trim()},${dato3.trim()},${dato4.trim()},${dato5.trim()}`;
}

/**
 * Tipo: Procedimiento
 * Parámetros:
 * - nombreArchivo: El nombre del archivo donde se guardará el contenido.
 * - contenido: La cadena de texto ya formateada que se va a guardar.
 * Propósito: Guardar una línea de venta en el archivo CSV correspondiente.
 * Es una función auxiliar que llama a EscribirArchivoCSV.
 * Devuelve: Nada.
 */
function GuardarDatosCsvVenta(nombreArchivo, contenido) {
    EscribirArchivoCSV(nombreArchivo, contenido);
}


// ----------------------------------------------------------------------------------
// PUNTO DE INICIO DE LA APLICACIÓN
// ----------------------------------------------------------------------------------
// Se utiliza una función asíncrona autoejecutable (IIFE) para iniciar el programa.
(async () => {
    // 1. Carga los datos iniciales de los productos en una variable.
    productos = CargarProductos();
    // 2. Crea la estructura de datos para almacenar el historial de ventas.
    ventas = CrearVenta();
    // 3. Ejecuta el menú principal, pasando las estructuras de datos de productos y ventas.
    await MenuPrincipal(productos, ventas);
})();
