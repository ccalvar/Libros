// Variable que almacenar� el arreglo principal con todo el inventario de productos.
let productos;

// Variable que contendr� el arreglo con el historial de todas las ventas registradas.
let ventas;

// Contador para rastrear la �ltima posici�n (�ndice) utilizada en el arreglo 'ventas'.
// Inicia en -1 para indicar que el arreglo est� vac�o.
let posventas = -1;

// Define el tama�o m�ximo o la capacidad del arreglo 'ventas'.
// En este caso, se podr�n almacenar hasta 100 registros de venta.
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

/**
 * Tipo: Funci�n
 * Par�metros: Ninguno.
 * Prop�sito: Crear una estructura de datos (un arreglo bidimensional) para almacenar
 * el historial de todas las ventas. Se inicializa con un tama�o fijo 'tamventas'
 * y 5 columnas por venta, todas con valor 'null'.
 * Devuelve: Un arreglo bidimensional (Array) vac�o para las ventas.
 */
function CrearVenta() {
    // Crea un arreglo de 'tamventas' filas, donde cada fila es un nuevo arreglo de 5 columnas rellenado con 'null'.
    const venta = Array.from({ length: tamventas }, () => new Array(5).fill(null));
    return venta;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - pos: La posici�n del �ltimo elemento en el arreglo de ventas.
 * - mventa: El arreglo (Array) que contiene el historial de ventas.
 * Prop�sito: Obtener el ID del �ltimo ticket registrado en el historial de ventas.
 * Devuelve: Una cadena (string) con el �ltimo ID de ticket o "000" si no hay ventas.
 */
function UltimoTicket(pos, mventa) {
    // Asigna un valor por defecto al ID del ticket.
    let idticket = "000";
    // Si la posici�n es v�lida (hay al menos una venta),...
    if (pos > -1) {
        // ...obtiene el ID del ticket de la �ltima venta registrada.
        idticket = mventa[pos][0];
    }
    return idticket;
}

/**
 * Tipo: Funci�n
 * Par�metros: Ninguno.
 * Prop�sito: Crear la estructura base para un nuevo ticket.
 * Devuelve: Un arreglo bidimensional (Array) de 20 filas y 4 columnas.
 * NOTA: Esta funci�n parece devolver un arreglo de tama�o fijo [20, 4] en lugar de la estructura,
 * lo que podr�a ser un error. La intenci�n probable era similar a CrearVenta.
 */
function CrearTicket() {
    return new Array(20, 4);
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - mticket: El arreglo (Array) que representa el ticket actual.
 * - codigo: El c�digo del producto a buscar.
 * Prop�sito: Verificar si un producto ya existe dentro del ticket actual.
 * Devuelve: El �ndice (posici�n) del producto si se encuentra, de lo contrario -1.
 */
function ExisteTicketCodigo(mticket, codigo) {
    let enc = -1; // Valor por defecto "no encontrado".
    // Obtiene la �ltima posici�n ocupada en el ticket.
    let pos = ObtenerUltimaPosicion(mticket);
    // Recorre el ticket desde el inicio hasta la �ltima posici�n ocupada.
    for (let ciclo = 0; ciclo <= pos; ciclo++)
        // Si el c�digo del producto en el ciclo actual coincide con el buscado...
        if (mticket[ciclo][0] === codigo)
            // ...guarda el �ndice y termina la b�squeda.
            enc = ciclo;
    return enc;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket actual.
 * - datos: Un arreglo con los datos del producto a insertar [c�digo, nombre, precio, cantidad].
 * - tamticket: El tama�o m�ximo del ticket.
 * Prop�sito: Insertar un producto en el ticket. Si el producto ya existe, incrementa su
 * cantidad. Si no existe, lo a�ade como una nueva l�nea.
 * Devuelve: 'true' si el producto fue agregado/actualizado, 'false' si el ticket est� lleno.
 */
function InsertarProductoTicket(mticket, datos, tamticket) {
    let sucedio = true; // Asume que la operaci�n ser� exitosa.
    let posticket = ObtenerUltimaPosicion(mticket); // �ltima fila ocupada del ticket.

    // Busca si el producto ya est� en el ticket.
    let enc = ExisteTicketCodigo(mticket, datos[0]);

    // Comprueba si hay espacio en el ticket.
    if (posticket < tamticket) {
        // Si se encontr� el producto (enc > -1)...
        if (enc > -1) {
            // ...incrementa la cantidad del producto existente.
            let cantidadactual = parseInt(mticket[enc][3]);
            mticket[enc][3] = (cantidadactual + 1).toString();
        } else {
            // Si no existe, lo agrega en la siguiente posici�n libre.
            posticket++;
            mticket[posticket][0] = datos[0]; // C�digo
            mticket[posticket][1] = datos[1]; // Nombre
            mticket[posticket][2] = datos[2]; // Precio
            mticket[posticket][3] = datos[3]; // Cantidad
        }
    } else {
        // Si no hay espacio, marca la operaci�n como fallida.
        sucedio = false;
    }
    return sucedio;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - precio: El precio unitario del producto.
 * - cantidad: La cantidad de productos.
 * Prop�sito: Calcular el total para una l�nea de producto (precio * cantidad).
 * Devuelve: El total formateado como una cadena (string) con dos decimales.
 */
function TotalProducto(precio, cantidad) {
    const total = parseFloat(precio) * parseFloat(cantidad);
    return total.toFixed(2); // .toFixed(2) asegura que siempre tenga dos decimales.
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket.
 * - pos: La posici�n (fila) del producto a formatear.
 * Prop�sito: Formatear una sola l�nea de producto del ticket para su visualizaci�n.
 * Devuelve: Una cadena (string) con el producto formateado en columnas de ancho fijo.
 */
function MostrarProductoTicket(mticket, pos) {
    let codigo = RellenarEspacios(mticket[pos][0], 5);
    let producto = RellenarEspacios(mticket[pos][1], 30);
    let precio = RellenarEspacios(mticket[pos][2], 10);
    let cantidad = RellenarEspacios(mticket[pos][3], 5);
    // Calcula y formatea el total de la l�nea.
    let totalproducto = RellenarEspacios(TotalProducto(mticket[pos][2], mticket[pos][3]), 10);
    // Concatena todas las partes en una sola cadena.
    let cadena = codigo.concat(producto + precio + cantidad + totalproducto);
    return cadena;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket.
 * Prop�sito: Generar una representaci�n en texto de todos los productos en el ticket.
 * Devuelve: Una cadena (string) multil�nea con el contenido del ticket formateado.
 */
function MostrarTicket(mticket) {
    let salida = "";
    let pos = ObtenerUltimaPosicion(mticket);
    // Si el ticket no est� vac�o...
    if (pos > -1)
        // ...recorre cada producto y lo agrega a la cadena de salida.
        for (let ciclo = 0; ciclo <= pos; ciclo++) {
            salida += MostrarProductoTicket(mticket, ciclo) + "\n";
        }
    return salida;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket.
 * Prop�sito: Calcular el subtotal de la venta (suma de los totales de cada producto, sin IVA).
 * Devuelve: Un n�mero (number) con el valor del subtotal.
 */
function SubTotalTicket(mticket) {
    let subtotal = 0;
    let pos = ObtenerUltimaPosicion(mticket);
    for (let ciclo = 0; ciclo <= pos; ciclo++) {
        // Suma el total de cada l�nea de producto al subtotal general.
        subtotal += parseFloat(TotalProducto(mticket[ciclo][2], mticket[ciclo][3]));
    }
    return subtotal;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket.
 * Prop�sito: Calcular el monto del IVA (16%) sobre el subtotal del ticket.
 * Devuelve: Un n�mero (number) con el monto del IVA, o -1 si el subtotal es cero.
 */
function IvaTicket(mticket) {
    let subtotal = SubTotalTicket(mticket);
    if (subtotal > 0)
        subtotal = 0.16 * subtotal; // Calcula el 16% de IVA.
    else
        subtotal = -1;
    return subtotal;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket.
 * Prop�sito: Calcular el total final de la venta (Subtotal + IVA).
 * Devuelve: Un n�mero (number) con el total a pagar.
 */
function TotalTicket(mticket) {
    let total = SubTotalTicket(mticket);
    if (total > 0)
        total = IvaTicket(mticket) + total;
    return total;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - mticket: Arreglo (Array) del ticket.
 * - idticket: ID del ticket actual.
 * - fecha: Fecha de la venta.
 * Prop�sito: Generar el texto completo del recibo de venta final.
 * Devuelve: Una cadena (string) con el recibo formateado, incluyendo encabezado,
 * lista de productos y desglose de totales (subtotal, IVA, total).
 */
function MostrarTicketVenta(mticket, idticket, fecha) {
    let salida = "";
    // Calcula y formatea los montos finales.
    let subtotal = SubTotalTicket(mticket).toFixed(2);
    let iva = IvaTicket(mticket).toFixed(2);
    let total = TotalTicket(mticket).toFixed(2);
    // Construye la cadena del recibo.
    salida = "Fecha " + fecha + " Ticket No." + idticket;
    salida += "\n" + MostrarTicket(mticket);
    salida += "\n\n El total sin iva " + subtotal;
    salida += "\n el iva total es " + iva;
    salida += "\n el total de la venta fue " + total;
    return salida;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - vproductos: El arreglo (Array) principal de productos.
 * Prop�sito: Mostrar una lista de productos que tienen existencias (stock > 0).
 * Devuelve: Una cadena (string) formateada con los productos disponibles para la venta.
 */
function MostrarListaProductosVenta(vproductos) {
    let salida = "";
    // Recorre la lista de productos (asume un tama�o fijo de 10).
    for (let ciclo = 0; ciclo < 10; ciclo++) {
        // Convierte la existencia a n�mero para la comparaci�n.
        let existencia = parseInt(vproductos[ciclo][3]);
        // Si hay existencia...
        if (existencia > 0) {
            // ...clona el producto para no modificar el original al mostrarlo.
            let vproducto = vproductos[ciclo].slice();
            // Formatea y agrega el producto a la cadena de salida.
            let cadena = MostrarProducto(vproducto);
            salida += cadena + "\n";
        }
    }
    return salida;
}

/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket actual.
 * - mproductos: El arreglo (Array) principal de productos.
 * - idticket: El ID del ticket actual.
 * - tamticket: El tama�o m�ximo del ticket.
 * Prop�sito: Gestionar la captura de un producto para agregarlo a la venta.
 * Pide un c�digo, valida existencias, reduce el stock y lo inserta en el ticket.
 * Devuelve: Nada.
 */
async function CapturaVentaProducto(mticket, mproductos, idticket, tamticket) {
    let codigo, info;
    // Muestra la lista de productos disponibles.
    info = MostrarListaProductosVenta(mproductos);

    // Pide al usuario el c�digo del producto.
    codigo = await Leer(info + "\nIntroduce el codigo del producto");
    if (codigo !== null) {
        // Busca el producto en el inventario.
        let posp = ExisteProducto(codigo.trim(), mproductos);
        if (posp > -1) {
            // Si hay stock...
            if (parseInt(mproductos[posp][3]) > 0) {
                // ...reduce el stock en 1.
                let cant = parseInt(mproductos[posp][3]);
                cant = cant - 1;
                mproductos[posp][3] = cant.toString();
                // Prepara los datos del producto para agregarlo al ticket (siempre cantidad 1).
                let venta = new Array(4);
                venta[0] = mproductos[posp][0];
                venta[1] = mproductos[posp][1];
                venta[2] = mproductos[posp][2];
                venta[3] = "1";
                // Inserta el producto en el ticket.
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

/**
 * Tipo: Procedimiento.
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket.
 * - pos: La posici�n del producto a remover.
 * Prop�sito: Eliminar completamente una l�nea de producto del ticket, reordenando
 * el arreglo para no dejar huecos.
 * Devuelve: Nada.
 */
function RemoverProductoTicket(mticket, pos) {
    let tam = ObtenerUltimaPosicion(mticket);
    // Si el elemento a borrar no es el �ltimo...
    if (tam > pos) {
        // ...desplaza todos los elementos siguientes una posici�n hacia arriba.
        for (let i = pos; i < tam + 1; i++) {
            mticket[i] = mticket[i + 1];
        }
        // Limpia la �ltima posici�n que ahora est� duplicada.
        mticket[tam][0] = null;
    } else {
        // Si es el �ltimo elemento, simplemente lo limpia.
        mticket[pos][0] = null;
    }
}

/**
 * Tipo: Procedimiento.
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket.
 * - pos: La posici�n del producto a eliminar.
 * Prop�sito: Gestionar la eliminaci�n de un producto del ticket. Si la cantidad
 * es mayor a 1, solo la reduce. Si es 1, remueve la l�nea completa.
 * Devuelve: Nada.
 */
function EliminarProductoTicket(mticket, pos) {
    let cantidad = parseInt(mticket[pos][3]);
    // Si la cantidad en el ticket es mayor a 1...
    if (cantidad > 1) {
        // ...solo decrementa la cantidad.
        mticket[pos][3] = (cantidad - 1).toString();
    } else {
        // Si la cantidad es 1, remueve la l�nea completa del producto.
        RemoverProductoTicket(mticket, pos);
    }
}

/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket actual.
 * - mproductos: El arreglo (Array) principal de productos.
 * Prop�sito: Gestionar la eliminaci�n de un producto de la venta. Pide un c�digo,
 * lo elimina del ticket y devuelve la cantidad al stock del inventario.
 * Devuelve: Nada.
 */
async function Eliminar(mticket, mproductos) {
    let info;
    // Muestra el contenido actual del ticket.
    info = MostrarTicket(mticket);

    // Pide al usuario el c�digo del producto a eliminar.
    let codigo = await Leer(info + "\nIntroduce el codigo del producto");
    if (codigo !== null) {
        // Busca la posici�n del producto en el ticket.
        let pos = ExisteTicketCodigo(mticket, codigo);
        if (pos > -1) {
            // Busca el producto en el inventario para devolverle el stock.
            let posproducto = ExisteProducto(codigo, mproductos);
            // Incrementa el stock del producto en el inventario principal.
            let nuevacantidad = (parseInt(mproductos[posproducto][3]) + 1).toString();
            mproductos[posproducto][3] = nuevacantidad;
            // Elimina el producto del ticket (o reduce su cantidad).
            EliminarProductoTicket(mticket, pos);
        }
    } else {
        console.log("dato nulo");
    }
}

/**
 * Tipo: Procedimiento.
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket finalizado.
 * - mventa: El arreglo (Array) del historial de ventas.
 * - idticket: El ID del ticket a registrar.
 * Prop�sito: Copiar todos los productos de un ticket pagado al historial general de ventas.
 * Devuelve: Nada.
 */
function AgregarProductoAVenta(mticket, mventa, idticket) {
    let posventas = ObtenerUltimaPosicion(mventa);
    let posticket = ObtenerUltimaPosicion(mticket);
    // Recorre el ticket finalizado.
    for (let i = 0; i <= posticket; i++) {
        let codigoProducto = mticket[i][0];
        // Si la fila no est� vac�a...
        if (codigoProducto !== null) {
            // ...la agrega al historial de ventas.
            posventas++;
            mventa[posventas] = [
                idticket,
                codigoProducto,
                mticket[i][1],
                mticket[i][2],
                mticket[i][3]
            ];
        }
    }
}

/**
 * Tipo: Procedimiento.
 * Par�metros:
 * - idticket: El ID del ticket a pagar.
 * - mventa: El arreglo (Array) del historial de ventas.
 * - mticket: El arreglo (Array) del ticket actual.
 * Prop�sito: Finalizar una venta. Registra el ticket en el historial de ventas.
 * Devuelve: Nada.
 */
function Pagar(idticket, mventa, mticket) {
    let posventas = ObtenerUltimaPosicion(mventa);
    let post = ObtenerUltimaPosicion(mticket);
    // Comprueba si hay espacio en el arreglo de ventas.
    if ((posventas + post) < 100) {
        // Agrega los productos del ticket al historial de ventas.
        AgregarProductoAVenta(mticket, mventa, idticket);
    } else {
        console.log("Desbordamiento de Memoria de ventas");
    }
}

/**
 * Tipo: Procedimiento.
 * Par�metros:
 * - mticket: El arreglo (Array) del ticket cancelado.
 * - mproductos: El arreglo (Array) principal de productos.
 * Prop�sito: Devolver al inventario el stock de todos los productos de un
 * ticket que fue cancelado.
 * Devuelve: Nada.
 */
function DevolucionTicket(mticket, mproductos) {
    let posmticket = ObtenerUltimaPosicion(mticket);

    // Recorre el ticket cancelado.
    for (let pos = 0; pos <= posmticket; pos++) {
        let codigo = mticket[pos][0];
        // Busca el producto en el inventario.
        let posp = ExisteProducto(codigo.trim(), mproductos);
        if (posp > -1) {
            // Suma la cantidad del ticket al stock del inventario.
            let cant = parseInt(mticket[pos][3]) + parseInt(mproductos[posp][3]);
            mproductos[posp][3] = String(cant);
        }
    }
}

/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros:
 * - ventas: Arreglo (Array) del historial de ventas.
 * - idticket: El �ltimo ID de ticket generado.
 * - productos: El arreglo (Array) principal de productos.
 * Prop�sito: Es el men� principal del punto de venta, donde se gestiona un ticket
 * completo, desde su creaci�n hasta su pago o cancelaci�n.
 * Devuelve: Nada.
 */
async function MenuPuntoVenta(ventas, idticket, productos) {
    let opcion, membrete;
    let pago = false; // Bandera para controlar si el ticket se pag�.
    let tamticket = 50; // Tama�o m�ximo para un ticket.
    // Crea un arreglo vac�o para el nuevo ticket.
    let Vticket = Array.from({ length: tamticket }, () => new Array(4).fill(null));

    // Genera el siguiente n�mero de ticket.
    idticket = await IdTicketSiguiente(idticket);

    let fechadia = await Fecha();
    opcion = "";

    // Bucle principal del men� de venta.
    do {
        // Construye el encabezado del men�, que incluye la vista previa del ticket.
        membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
        membrete += "\n-----------------------------------------------------\n";
        let Tickettexto = MostrarTicket(Vticket).trim();
        if (Tickettexto.trim() !== "") {
            membrete += "\n" + Tickettexto + "\n";
        }
        let datosmenu = ["1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida "];
        // Muestra el men� y espera la opci�n del usuario.
        opcion = await DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu);

        if (opcion === null) {
            console.log("dato incorrecto introducido");
        } else {
            switch (opcion) {
                case "1":
                    // Llama a la funci�n para agregar un producto al ticket.
                    await CapturaVentaProducto(Vticket, productos, idticket, tamticket);
                    break;
                case "2":
                    // Llama a la funci�n para eliminar un producto del ticket.
                    await Eliminar(Vticket, productos); // Pasando mproductos para la devoluci�n
                    break;
                case "3":
                    // Muestra el contenido del ticket si no est� vac�o.
                    if (ObtenerUltimaPosicion(Vticket) > -1)
                        console.log(MostrarTicket(Vticket));
                    break;
                case "4":
                    // Muestra el recibo final, procesa el pago y sale del men�.
                    console.log(MostrarTicketVenta(Vticket, idticket, fechadia).trim());
                    await Pagar(idticket, ventas, Vticket);
                    pago = true;
                    opcion = "5"; // Forza la salida del bucle.
                    break;
                case "5":
                    console.log("Salida del Ventas");
                    // Si se sale sin pagar, cancela el ticket y devuelve el stock.
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

/**
 * Tipo: Funci�n
 * Par�metros:
 * - venta: Un arreglo (Array) con los datos de una l�nea de venta del historial.
 * Prop�sito: Formatear una sola l�nea del historial de ventas para su visualizaci�n.
 * Devuelve: Una cadena (string) formateada con los datos de la venta.
 */
function MostrarVenta(venta) {
    let idticket = RellenarEspacios(venta[0], 6);
    let codigo = RellenarEspacios(venta[1], 5);
    let producto = RellenarEspacios(venta[2], 30);
    let precio = RellenarEspacios(venta[3], 10);
    let cantidad = RellenarEspacios(venta[4], 10);
    let cadena = idticket.concat(codigo + producto + precio + cantidad);
    return cadena;
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - ventas: El arreglo (Array) completo del historial de ventas.
 * Prop�sito: Generar una representaci�n en texto de todo el historial de ventas.
 * Devuelve: Una cadena (string) multil�nea con todas las ventas registradas.
 */
function MostrarListaVentas(ventas) {
    let posventas = ObtenerUltimaPosicion(ventas);
    let salida = "";
    // Recorre el historial de ventas hasta la �ltima posici�n.
    for (let ciclo = 0; ciclo <= posventas; ciclo++) {
        // Extrae los datos de una venta.
        let venta = [ventas[ciclo][0], ventas[ciclo][1], ventas[ciclo][2], ventas[ciclo][3], ventas[ciclo][4]];
        // Formatea la venta y la agrega a la salida.
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



/**
 * Tipo: Procedimiento as�ncrono.
 * Par�metros:
 * - vproductos: El arreglo (Array) que contiene la base de datos de productos.
 * - vventas: El arreglo (Array) que contiene el historial de todas las ventas.
 * Prop�sito: Es el men� principal y el controlador central de toda la aplicaci�n.
 * Desde aqu� se navega a los diferentes m�dulos (Productos, Ventas, Inventario),
 * se puede consultar el historial de ventas y salir del sistema.
 * Devuelve: Nada.
 */
async function MenuPrincipal(vproductos, vventas) {
    // Define las opciones del men� principal, incluyendo la nueva opci�n "Ventas".
    let datosmenuprincipal = ["1.-Productos ", "2.-Punto de Venta ", "3.- Inventario", "4.-Ventas", "5.-Salida "];
    let opcion = "0"; // Inicializa la variable para la opci�n del usuario.
    let idticket = "000"; // Inicializa el ID del ticket.

    // Bucle principal que mantiene la aplicaci�n en ejecuci�n.
    do {
        // Antes de mostrar el men�, obtiene el �ltimo ID de ticket del historial de ventas.
        // Esto es crucial para que el "Punto de Venta" sepa cu�l es el siguiente n�mero.
        idticket = ObtenerUltimoValorVentas(vventas);

        // Muestra el men� principal y espera la selecci�n del usuario.
        opcion = await DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Peque�a", datosmenuprincipal);

        if (opcion === null) {
            console.log("opcion incorrecta ");
        } else {
            // Eval�a la opci�n seleccionada por el usuario.
            switch (opcion) {
                case "1":
                    // Llama al submen� de gesti�n de productos.
                    await MenuProductos(vproductos);
                    break;
                case "2":
                    // Llama al submen� de punto de venta, pasando el historial de ventas,
                    // el �ltimo ID de ticket y la lista de productos.
                    await MenuPuntoVenta(vventas, idticket, vproductos);
                    break;
                case "3":
                    // Llama al submen� de gesti�n de inventario.
                    await MenuInventario(vproductos);
                    break;
                case "4":
                    // Muestra el historial completo de ventas en la consola.
                    console.log(await MostrarListaVentas(vventas));
                    break;
                case "5":
                    // Muestra un mensaje de despedida.
                    console.log("Salida del Sistema ");
                    break;
                default:
                    // Se ejecuta si el usuario introduce una opci�n no v�lida.
                    console.log("No existe esta opcion ");
                    break;
            }
        }
        // El bucle contin�a mientras la opci�n sea diferente de "5".
    } while (opcion !== "5");
}

/**
 * Tipo: Funci�n
 * Par�metros:
 * - ventas: El arreglo (Array) que contiene el historial de ventas.
 * Prop�sito: Encontrar y devolver el ID del ticket de la �ltima venta registrada.
 * Esto permite generar el siguiente ID de forma secuencial.
 * Devuelve: Una cadena (string) con el �ltimo ID de ticket o "000" si no hay ventas.
 */
function ObtenerUltimoValorVentas(ventas) {
    // Establece un valor por defecto en caso de que no haya ventas.
    let ultimoValor = "000";
    // Obtiene el �ndice de la �ltima fila ocupada en el arreglo de ventas.
    let tam = ObtenerUltimaPosicion(ventas);
    // Si el �ndice es v�lido (es decir, el arreglo no est� vac�o)...
    if (tam >= 0)
        // ...obtiene el valor de la primera columna (el ID del ticket) de esa �ltima fila.
        ultimoValor = ventas[tam][0];
    // Devuelve el �ltimo ID encontrado o el valor por defecto.
    return ultimoValor;
}

// ----------------------------------------------------------------------------------
// PUNTO DE INICIO DE LA APLICACI�N
// ----------------------------------------------------------------------------------
// Se utiliza una funci�n as�ncrona autoejecutable (IIFE) para iniciar el programa.
(async () => {
    // 1. Carga los datos iniciales de los productos en una variable.
    let productos = CargarProductos();
    // 2. Crea la estructura de datos para almacenar el historial de ventas.
    let ventas = CrearVenta();
    // 3. Ejecuta el men� principal, pasando las estructuras de datos de productos y ventas
    //    para que toda la aplicaci�n pueda trabajar con ellas.
    await MenuPrincipal(productos, ventas);
})();