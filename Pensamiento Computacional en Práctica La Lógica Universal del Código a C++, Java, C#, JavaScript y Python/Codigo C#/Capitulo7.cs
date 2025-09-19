using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibroFundamentos.Capitulo7
{
    internal class Capitulo7
    {
        // Declara una matriz estática (global a la clase) para almacenar el catálogo de productos. Aún no está inicializada.
        static string[,] productos;

        // Declara una matriz estática para almacenar el historial de ventas. Aún no está inicializada.
        static String[,] ventas;
        // Declara un índice estático para rastrear la última posición utilizada en la matriz 'ventas'. Inicia en -1 porque está vacía.
        static int posventas = -1;
        // Declara una variable estática que define el tamaño máximo (capacidad) de la matriz 'ventas'.
        static int tamventas = 100;
        // Declara una variable de texto estática, destinada a guardar la fecha de operación.
        static String fecha;



        public static string MostrarMenu(string[] opciones)
        {
            string cadena = "";
            foreach (string info in opciones)
            {
                cadena += info + "\n";
            }
            return cadena;
        }

        public static bool EsNumeroEntero(string dato)
        {
            foreach (char c in dato)
            {
                if (!char.IsDigit(c))
                {
                    return false;
                }
            }
            return true;
        }


        public static bool EsNumeroDouble(string dato)
        {
            bool valido = false;

            foreach (char c in dato)
            {
                if (!char.IsDigit(c))
                {
                    if (c == '.' && !valido)
                    {
                        valido = true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            return valido;
        }

        public static bool EvaluarNumerico(string dato, int tipo)
        {
            bool valido = false;
            switch (tipo)
            {
                case 1:
                    valido = EsNumeroEntero(dato);
                    break;
                case 2:
                    valido = EsNumeroDouble(dato);
                    break;
            }
            return valido;
        }

        public static string Dialogo(string texto)
        {
            Console.Write(texto + " : ");
            return Console.ReadLine();
        }

        public static string Leer(string texto)
        {
            string cadena = "";
            cadena = Dialogo(texto);
            if (!string.IsNullOrEmpty(cadena))
            {
                cadena = cadena.Trim();
                if (string.IsNullOrEmpty(cadena))
                    cadena = null;
            }
            return cadena;
        }

        public static string DesplegarMenu(string Titulo1, string[] menu)
        {
            string cadena = Titulo1 + "\n\n" + MostrarMenu(menu) + "\nQue opcion deseas ";
            return Dialogo(cadena);
        }

        public static string RellenarEspacios(string dato, int tamano)
        {
            return dato.PadLeft(tamano);
        }

        public static string Fecha()
        {
            DateTime fecha = DateTime.Now;
            return fecha.ToString("dd-MM-yyyy");
        }

        public static string IdTicketSiguiente(string idTicket)
        {
            string idTicketNext = "";
            int num = int.Parse(idTicket) + 1;

            if (num < 10)
            {
                idTicketNext = "00" + num.ToString().Trim();
            }
            else if (num > 9 && num < 100)
            {
                idTicketNext = "0" + num.ToString().Trim();
            }
            else
            {
                idTicketNext = num.ToString().Trim();
            }
            return idTicketNext;
        }

        public static int ObtenerUltimaPosicion(string[,] matriz)
        {
            int ultimaPosicion = -1;
            for (int i = 0; i < matriz.GetLength(0); i++)
            {
                if (!string.IsNullOrEmpty(matriz[i, 0]))
                {
                    ultimaPosicion = i;
                }
            }
            return ultimaPosicion;
        }


        public static string[,] CargarProductos()
        {
            string[,] producto = 
            {
         { "001", "Arroz 1kg", "35", "10" },
        { "002", "Azúcar 1kg", "25", "10" },
        { "003", "Harina 1kg", "28", "10" },
        { "004", "Aceite 1L", "50", "10" },
         { "005", "Leche 1L", "35", "10" },
         { "006", "Huevos 12 unidades", "45", "10" },
        { "007", "Fideos 500g", "20", "10" },
        { "008", "Sal 1kg", "15", "10" },
        { "009", "Pasta de tomate 400g", "25", "10" },
        { "010", "Atún lata 170g", "35", "10" }
            };
            return producto;
        }



        public static string MostrarProducto(string[] vproducto)
        {
            string codigo = RellenarEspacios(vproducto[0], 5);
            string producto = RellenarEspacios(vproducto[1], 30);
            string precio = RellenarEspacios(vproducto[2], 10);
            string cantidad = RellenarEspacios(vproducto[3], 10);
            string cadena = codigo + producto + precio+cantidad;
            return cadena;
        }

        public static string MostrarLista(string[,] vproductos)
        {
            string salida = "";
            for (int ciclo = 0; ciclo < 10; ciclo++)
            {
                string[] vproducto = { vproductos[ciclo, 0], vproductos[ciclo,1], vproductos[ciclo,2], vproductos[ciclo, 3] };
                string cadena = MostrarProducto(vproducto);
                salida = string.Concat(salida, cadena, "\n");
            }
            return salida;
        }


        
        public static int ExisteProducto(string codigo, string[,] vproductos)
        {
            int enc = -1;
            int pos = 0;
            int tam = vproductos.GetLength(0);
            for (int ciclo = 0; ciclo < tam; ciclo++)
            {
                if (vproductos[ciclo, 0].Trim().Equals(codigo.Trim()))
                {
                    enc = pos;
                }
                pos++;
            }
            return enc;
        }

        public static void ModificarProducto(string[,] vproductos)
        {
            string codigo, precio;
            int posicion;
            string info = MostrarLista(vproductos);
            codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");
            if (codigo != null)
            {
                posicion = ExisteProducto(codigo, vproductos);
                if (posicion > -1)
                {
                    string[] vproducto = { vproductos[posicion,0], vproductos[posicion,1], vproductos[posicion,2] };
                    precio = Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ");
                    if (precio != null)
                    {
                        if (EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1))
                        {
                            vproductos[posicion,2] = precio;
                        }
                        else
                        {
                            Console.WriteLine("no es un valor numerico");
                        }
                    }
                    else
                    {
                        Console.WriteLine(" dato nulo");
                    }
                }
                else
                {
                    Console.WriteLine("no existe el codigo");
                }
            }
            else
            {
                Console.WriteLine(" dato nulo");
            }
        }


        public static void MenuProductos(String[,] vproductos)
        {
            string[] datosmenuproductos = { "1.-Modificar", "2.-Listado", "3.-Salida " };
            string opcion = "0";
            do
            {
                opcion = DesplegarMenu("Opciones de Productos ", datosmenuproductos);
                if (opcion == null)
                {
                    Console.WriteLine("Opcion incorrecta ");
                }
                else
                {
                    switch (opcion)
                    {
                        case "1": ModificarProducto(vproductos); break;
                        case "2": Console.WriteLine(MostrarLista(vproductos)); break;
                        case "3": Console.WriteLine("Salida del Sistema "); break;
                        default:
                            Console.WriteLine("No existe esta opcion ");
                            break;
                    }
                }
            } while (opcion.CompareTo("3") != 0);
        }


        // TIPO: Función
        // REALIZA: Crea y devuelve una nueva matriz vacía para almacenar el historial de ventas.
        // PARÁMETROS: Ninguno.
        // REGRESA: Una matriz de dos dimensiones (string[,]) con el tamaño definido por 'tamventas' y 5 columnas.
        public static string[,] CrearVenta()
        {
            // Crea una nueva instancia de una matriz de 2D con el tamaño especificado y la devuelve.
            return new string[tamventas, 5];
        }

        // TIPO: Función
        // REALIZA: Obtiene el ID del ticket de un registro de venta específico.
        // PARÁMETROS:
        //   - int pos: El índice (fila) del registro de venta.
        //   - string[,] mventa: La matriz del historial de ventas.
        // REGRESA: Una cadena (string) con el ID del ticket, o "000" si la posición es inválida.
        public static string UltimoTicket(int pos, string[,] mventa)
        {
            // Inicializa el ID del ticket con un valor por defecto.
            string idticket = "000";
            // Si la posición es válida (hay al menos una venta),
            if (pos > -1)
            {
                // obtiene el ID del ticket de la venta registrada en esa posición.
                idticket = mventa[pos, 0];
            }
            // Devuelve el ID del ticket encontrado o el valor por defecto.
            return idticket;
        }

        // TIPO: Función
        // REALIZA: Crea y devuelve una nueva matriz vacía para ser usada como un ticket temporal.
        // PARÁMETROS: Ninguno.
        // REGRESA: Una matriz de dos dimensiones (string[,]) de 20 filas y 4 columnas.
        public static string[,] CrearTicket()
        {
            // Crea una nueva instancia de una matriz de 2D para el ticket y la devuelve.
            return new string[20, 4];
        }

        // TIPO: Función
        // REALIZA: Verifica si un producto ya existe dentro del ticket actual.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket actual.
        //   - string codigo: El código del producto a buscar.
        // REGRESA: Un entero (int) con el índice del producto si se encuentra, o -1 si no.
        public static int ExisteTicketCodigo(string[,] mticket, string codigo)
        {
            // Inicializa el valor de retorno en -1 (no encontrado).
            int enc = -1;
            // Obtiene la última posición utilizada en el ticket.
            int pos = ObtenerUltimaPosicion(mticket);
            // Muestra un mensaje de depuración.
            Console.WriteLine("buscando " + codigo + " tamaño arreglo " + pos);
            // Recorre el ticket hasta la última posición utilizada.
            for (int ciclo = 0; ciclo <= pos; ciclo++)
            {
                // Compara el código del producto en la fila actual con el código buscado (ignorando espacios).
                if (mticket[ciclo, 0].Trim().CompareTo(codigo.Trim()) == 0)
                {
                    // Si coinciden, guarda el índice.
                    enc = ciclo;
                    // Retorna inmediatamente para optimizar la búsqueda.
                    return enc;
                }
            }
            // Si el bucle termina, devuelve -1.
            return enc;
        }

        // TIPO: Función
        // REALIZA: Inserta un producto en el ticket. Si ya existe, incrementa su cantidad.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket actual.
        //   - string[] datos: Los datos del producto a insertar.
        //   - int tamticket: El tamaño máximo del ticket.
        // REGRESA: Un booleano. `true` si la operación fue exitosa, `false` si el ticket está lleno.
        public static bool InsertarProductoTicket(string[,] mticket, string[] datos, int tamticket)
        {
            // Asume que la operación será exitosa.
            bool sucedio = true;
            // Verifica si el producto ya existe en el ticket.
            int enc = ExisteTicketCodigo(mticket, datos[0]);
            // Obtiene la última posición utilizada en el ticket.
            int posticket = ObtenerUltimaPosicion(mticket);
            // Comprueba si hay espacio en el ticket.
            if (posticket < tamticket)
            {
                // Si el producto ya fue encontrado,
                if (enc > -1)
                {
                    // informa al usuario y procede a incrementar la cantidad.
                    Console.WriteLine("ya existe el producto en el ticket lo incrementare");
                    // Convierte la cantidad actual a entero.
                    int cantidadactual = int.Parse(mticket[enc, 3]);
                    // Incrementa la cantidad en 1 y la convierte de nuevo a cadena para guardarla.
                    mticket[enc, 3] = (cantidadactual + 1).ToString();
                }
                else
                {
                    // Si no existe, incrementa la posición para añadir una nueva línea.
                    posticket++;
                    // Asigna los datos del producto a la nueva fila.
                    mticket[posticket, 0] = datos[0];
                    mticket[posticket, 1] = datos[1];
                    mticket[posticket, 2] = datos[2];
                    mticket[posticket, 3] = datos[3];
                    Console.WriteLine("Insertarndo No existe el producto en el ticket ");
                }
            }
            else
            {
                // Si no hay espacio, marca la operación como fallida.
                sucedio = false;
            }
            // Devuelve el estado de la operación.
            return sucedio;
        }

        // TIPO: Función
        // REALIZA: Calcula el costo total de una línea de producto (precio * cantidad).
        // PARÁMETROS:
        //   - string precio: El precio del producto.
        //   - string cantidad: La cantidad del producto.
        // REGRESA: Una cadena (string) con el total formateado con ceros a la izquierda y dos decimales.
        public static string TotalProducto(string precio, string cantidad)
        {
            // Convierte el precio y la cantidad de cadena a double y los multiplica.
            double total = double.Parse(precio) * double.Parse(cantidad);
            // Devuelve el total formateado como una cadena.
            return total.ToString("000000.00");
        }

        // TIPO: Función
        // REALIZA: Formatea una línea de producto del ticket para su visualización.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket actual.
        //   - int pos: El índice de la línea de producto a formatear.
        // REGRESA: Una cadena (string) con la línea del ticket formateada y alineada.
        public static string MostrarProductoTicket(string[,] mticket, int pos)
        {
            // Formatea cada campo con un ancho específico para alinearlo en columnas.
            string codigo = RellenarEspacios(mticket[pos, 0], 5);
            string producto = RellenarEspacios(mticket[pos, 1], 30);
            string precio = RellenarEspacios(mticket[pos, 2], 10);
            string cantidad = RellenarEspacios(mticket[pos, 3], 5);
            string totalproducto = RellenarEspacios(TotalProducto(mticket[pos, 2], mticket[pos, 3]), 10);
            // Concatena todas las partes para formar la línea completa.
            string cadena = codigo + producto + precio + cantidad + totalproducto;
            // Devuelve la cadena formateada.
            return cadena;
        }

        // TIPO: Función
        // REALIZA: Genera una representación en texto de todo el contenido del ticket actual.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket.
        // REGRESA: Una cadena (string) con todas las líneas del ticket.
        public static string MostrarTicket(string[,] mticket)
        {
            // Inicializa una cadena vacía para la salida.
            string salida = "";
            // Obtiene la última posición utilizada en el ticket.
            int pos = ObtenerUltimaPosicion(mticket);
            // Recorre el ticket hasta la última posición utilizada.
            for (int ciclo = 0; ciclo <= pos; ciclo++)
            {
                // Formatea la línea actual y la añade a la cadena de salida, con un salto de línea.
                salida = salida + MostrarProductoTicket(mticket, ciclo) + "\n";
            }
            // Devuelve la cadena con el ticket completo.
            return salida;
        }

        // TIPO: Función
        // REALIZA: Calcula el subtotal de la venta (suma de los totales de todos los productos).
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket.
        // REGRESA: Un valor double con el subtotal del ticket.
        public static double SubTotalTicket(string[,] mticket)
        {
            // Inicializa el subtotal en 0.
            double subtotal = 0;
            // Obtiene la última posición utilizada en el ticket.
            int pos = ObtenerUltimaPosicion(mticket);
            // Recorre cada producto en el ticket.
            for (int ciclo = 0; ciclo <= pos; ciclo++)
            {
                // Acumula el total de cada producto (convertido a double) en el subtotal.
                subtotal += double.Parse(TotalProducto(mticket[ciclo, 2], mticket[ciclo, 3]));
            }
            // Devuelve el subtotal calculado.
            return subtotal;
        }

        // TIPO: Función
        // REALIZA: Calcula el monto del IVA (16%) sobre el subtotal del ticket.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket.
        // REGRESA: Un valor double con el monto del IVA.
        public static double IvaTicket(string[,] mticket)
        {
            // Llama a SubTotalTicket para obtener el subtotal.
            double subtotal = SubTotalTicket(mticket);
            // Si el subtotal es positivo,
            if (subtotal > 0)
                // calcula el 16% de IVA.
                subtotal = 0.16 * subtotal;
            else
                // si no, establece un valor de error.
                subtotal = -1;
            // Devuelve el monto del IVA calculado.
            return subtotal;
        }

        // TIPO: Función
        // REALIZA: Calcula el total final de la venta (subtotal + IVA).
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket.
        // REGRESA: Un valor double con el total a pagar.
        public static double TotalTicket(string[,] mticket)
        {
            // Obtiene el subtotal.
            double total = SubTotalTicket(mticket);
            // Si el total es positivo,
            if (total > 0)
                // le suma el monto del IVA.
                total = IvaTicket(mticket) + total;
            // Devuelve el total final.
            return total;
        }

        // TIPO: Función
        // REALIZA: Genera el formato de impresión final del ticket.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket.
        //   - string idticket: El número de ticket.
        //   - string fecha: La fecha de la venta.
        // REGRESA: Una cadena (string) con el recibo completo listo para mostrar.
        public static string MostrarTicketVenta(string[,] mticket, string idticket, string fecha)
        {
            // Inicializa la cadena de salida.
            string salida = "";
            // Formatea los valores numéricos para que siempre tengan dos decimales.
            string subtotal = string.Format("{0:F2}", SubTotalTicket(mticket));
            string iva = string.Format("{0:F2}", IvaTicket(mticket));
            string total = string.Format("{0:F2}", TotalTicket(mticket));
            // Construye el encabezado del ticket.
            salida = "Fecha " + fecha + " Ticket No." + idticket;
            // Añade la lista de productos del ticket.
            salida += "\n" + MostrarTicket(mticket);
            // Añade el desglose de totales.
            salida += "\n\n El total sin iva " + subtotal;
            salida += "\n el iva total es " + iva;
            salida += "\n el total de la venta fue " + total;
            // Devuelve la cadena con el ticket completo.
            return salida;
        }

        // TIPO: Función
        // REALIZA: Genera una lista de productos disponibles para la venta (con existencia > 0).
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz del catálogo de productos.
        // REGRESA: Una cadena (string) con la lista formateada de productos en stock.
        public static string MostrarListaProductosVenta(string[,] vproductos)
        {
            // Inicializa la cadena de salida.
            string salida = "";
            // Recorre el catálogo de productos.
            for (int ciclo = 0; ciclo < 10; ciclo++)
            {
                // Convierte la cantidad en stock (string) a un entero.
                int existencia = int.Parse(vproductos[ciclo, 3]);
                // Si hay existencias del producto,
                if (existencia > 0)
                {
                    // crea un arreglo temporal con los datos del producto.
                    string[] vproducto = new string[vproductos.GetLength(1)];
                    for (int i = 0; i < vproductos.GetLength(1); i++)
                    {
                        vproducto[i] = vproductos[ciclo, i];
                    }
                    // Formatea el producto y lo añade a la lista de salida.
                    string cadena = MostrarProducto(vproducto);
                    salida += cadena + "\n";
                }
            }
            // Devuelve la lista de productos disponibles.
            return salida;
        }

        // TIPO: Procedimiento
        // REALIZA: Gestiona la captura de un producto para la venta.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket actual.
        //   - string[,] mproductos: La matriz del catálogo de productos.
        //   - string idticket: El número de ticket actual.
        //   - int tamticket: El tamaño máximo del ticket.
        // REGRESA: Nada (void).
        public static void CapturaVentaProducto(string[,] mticket, string[,] mproductos, string idticket, int tamticket)
        {
            // Declara variables para el código del producto y la información a mostrar.
            string codigo, info;
            // Obtiene la lista de productos disponibles para la venta.
            info = MostrarListaProductosVenta(mproductos);
            // Pide al usuario que introduzca un código.
            codigo = Leer(info + "\nIntroduce el codigo del producto");
            // Si el usuario introdujo un código,
            if (codigo != null)
            {
                // busca el producto en el catálogo.
                int posp = ExisteProducto(codigo.Trim(), mproductos);
                // Si el producto existe,
                if (posp > -1)
                {
                    // Si hay stock disponible,
                    if (int.Parse(mproductos[posp, 3]) > 0)
                    {
                        // crea un arreglo temporal para mostrar los datos del producto.
                        string[] producto = new string[mproductos.GetLength(1)];
                        for (int i = 0; i < mproductos.GetLength(1); i++)
                        {
                            producto[i] = mproductos[posp, i];
                        }
                        // Obtiene la cantidad actual en stock.
                        int cant = int.Parse(mproductos[posp, 3]);
                        // Reduce el stock en 1.
                        cant = cant - 1;
                        // Actualiza la cantidad en el catálogo de productos.
                        mproductos[posp, 3] = cant.ToString();
                        // Muestra el producto que se está agregando.
                        Console.WriteLine(MostrarProducto(producto));
                        // Prepara los datos para insertar en el ticket.
                        string[] venta = new string[4];
                        venta[0] = mproductos[posp, 0];
                        venta[1] = mproductos[posp, 1];
                        venta[2] = mproductos[posp, 2];
                        venta[3] = "1";
                        // Inserta el producto en el ticket.
                        if (!InsertarProductoTicket(mticket, venta, tamticket))
                            Console.WriteLine("el Arreglo esta lleno \n");
                    }
                    else
                        Console.WriteLine("no hay productos para venta");
                }
                else
                {
                    Console.WriteLine("el codigo no existe no se puede agregar\n");
                }
            }
            else
            {
                Console.WriteLine("dato nulo\n");
            }
        }

        // TIPO: Procedimiento
        // REALIZA: Elimina una línea de producto del ticket, desplazando las posteriores hacia arriba.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket.
        //   - int pos: El índice de la línea a eliminar.
        // REGRESA: Nada (void).
        public static void RemoverProductoTicket(string[,] mticket, int pos)
        {
            // Obtiene la última posición utilizada en el ticket.
            int tam = ObtenerUltimaPosicion(mticket);
            // Si la línea a eliminar no es la última,
            if (tam > pos)
            {
                // recorre el ticket desde la posición a eliminar.
                for (int i = pos; i < tam; i++)
                {
                    // Desplaza los datos de la siguiente fila a la actual.
                    for (int j = 0; j < mticket.GetLength(1); j++)
                    {
                        mticket[i, j] = mticket[i + 1, j];
                    }
                }
                // Limpia la última fila que ahora está duplicada.
                for (int j = 0; j < mticket.GetLength(1); j++)
                {
                    mticket[tam, j] = null;
                }
            }
            else
            {
                // Si es la última línea, simplemente la limpia.
                for (int j = 0; j < mticket.GetLength(1); j++)
                {
                    mticket[pos, j] = null;
                }
            }
        }

        // TIPO: Procedimiento
        // REALIZA: Gestiona la eliminación de un producto del ticket.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket.
        //   - int pos: El índice del producto a eliminar.
        // REGRESA: Nada (void).
        public static void EliminarProductoTicket(string[,] mticket, int pos)
        {
            // Obtiene la cantidad del producto en el ticket.
            int cantidad = int.Parse(mticket[pos, 3]);
            // Si la cantidad es mayor que 1,
            if (cantidad > 1)
            {
                // simplemente la decrementa.
                mticket[pos, 3] = (cantidad - 1).ToString();
            }
            else
            {
                // si es 1, elimina la línea completa del producto.
                RemoverProductoTicket(mticket, pos);
            }
        }

        // TIPO: Procedimiento
        // REALIZA: Orquesta la eliminación de un producto del ticket y devuelve el stock.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket.
        //   - string[,] mproductos: La matriz del catálogo de productos.
        // REGRESA: Nada (void).
        public static void Eliminar(string[,] mticket, string[,] mproductos)
        {
            // Declara variables para el código y la información.
            string codigo, info;
            // Muestra el contenido actual del ticket.
            info = MostrarTicket(mticket);
            // Pide al usuario el código del producto a eliminar.
            codigo = Leer(info + "\nIntroduce el codigo del producto");
            // Si se introdujo un código,
            if (codigo != null)
            {
                // busca el producto en el ticket.
                int pos = ExisteTicketCodigo(mticket, codigo);
                // Si se encuentra,
                if (pos > -1)
                {
                    // busca el mismo producto en el catálogo general.
                    int posproducto = ExisteProducto(codigo, mproductos);
                    // Devuelve 1 unidad al stock del inventario.
                    string nuevacantidad = (int.Parse(mproductos[posproducto, 3]) + 1).ToString();
                    mproductos[posproducto, 3] = nuevacantidad;
                    // Elimina el producto del ticket (o reduce su cantidad).
                    EliminarProductoTicket(mticket, pos);
                }
            }
            else
            {
                Console.WriteLine("dato nulo");
            }
        }

        // TIPO: Procedimiento
        // REALIZA: Transfiere los productos de un ticket pagado al historial de ventas.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket finalizado.
        //   - string[,] mventa: La matriz del historial de ventas.
        //   - string idticket: El número de ticket a registrar.
        // REGRESA: Nada (void).
        public static void AgregarProductoAVenta(string[,] mticket, string[,] mventa, string idticket)
        {
            // Declara variables para las posiciones.
            int posticket, posventas;
            // Obtiene la última posición en el historial de ventas y en el ticket.
            posventas = ObtenerUltimaPosicion(mventa);
            posticket = ObtenerUltimaPosicion(mticket);
            // Recorre cada producto en el ticket.
            for (int i = 0; i <= posticket; i++)
            {
                // Se asegura de que la fila no esté vacía.
                if (mticket[i, 0] != null)
                {
                    // Incrementa la posición en el historial de ventas.
                    posventas++;
                    // Copia los datos del ticket al historial de ventas.
                    mventa[posventas, 0] = idticket;
                    mventa[posventas, 1] = mticket[i, 0];
                    mventa[posventas, 2] = mticket[i, 1];
                    mventa[posventas, 3] = mticket[i, 2];
                    mventa[posventas, 4] = mticket[i, 3];
                }
            }
        }

        // TIPO: Procedimiento
        // REALIZA: Gestiona el proceso de pago, registrando la venta en el historial.
        // PARÁMETROS:
        //   - string idticket: El número de ticket a pagar.
        //   - string[,] mventa: La matriz del historial de ventas.
        //   - string[,] mticket: La matriz del ticket actual.
        // REGRESA: Nada (void).
        public static void Pagar(string idticket, string[,] mventa, string[,] mticket)
        {
            // Obtiene las últimas posiciones de ambos arreglos.
            int posventas = ObtenerUltimaPosicion(mventa);
            int post = ObtenerUltimaPosicion(mticket);
            // Verifica si hay suficiente espacio en el historial de ventas.
            if ((posventas + post) < 100)
            {
                // Si hay espacio, transfiere los productos al historial.
                AgregarProductoAVenta(mticket, mventa, idticket);
            }
            else
            {
                Console.WriteLine("Desbordamiento de Memoria de ventas");
            }
        }

        // TIPO: Procedimiento
        // REALIZA: Cancela un ticket no pagado, devolviendo el stock al inventario.
        // PARÁMETROS:
        //   - string[,] mticket: La matriz del ticket a cancelar.
        //   - string[,] mproductos: La matriz del catálogo de productos.
        // REGRESA: Nada (void).
        public static void DevolucionTicket(string[,] mticket, string[,] mproductos)
        {
            // Obtiene la última posición utilizada en el ticket.
            int posmticket = ObtenerUltimaPosicion(mticket);
            // Recorre cada producto en el ticket.
            for (int pos = 0; pos <= posmticket; pos++)
            {
                // Obtiene el código del producto.
                string codigo = mticket[pos, 0];
                // Busca el producto en el catálogo general.
                int posp = ExisteProducto(codigo.Trim(), mproductos);
                // Si lo encuentra,
                if (posp > -1)
                {
                    // suma la cantidad del ticket al stock del inventario.
                    int cant = int.Parse(mticket[pos, 3]) + int.Parse(mproductos[posp, 3]);
                    mproductos[posp, 3] = cant.ToString();
                }
            }
        }

        // TIPO: Procedimiento
        // REALIZA: Es el motor principal del punto de venta.
        // PARÁMETROS:
        //   - string[,] ventas: La matriz del historial de ventas.
        //   - string idticket: El ID del último ticket.
        //   - string[,] productos: La matriz del catálogo de productos.
        // REGRESA: Nada (void).
        public static void MenuPuntoVenta(string[,] ventas, string idticket, string[,] productos)
        {
            // Declara variables para la opción y el encabezado.
            string opcion, membrete;
            // Declara una bandera para saber si el ticket fue pagado.
            bool pago = false;
            // Define el tamaño máximo del ticket.
            int tamticket = 50;
            // Crea una matriz local para el ticket actual.
            string[,] Vticket = new string[tamticket, 4];

            // Genera el siguiente número de ticket.
            idticket = IdTicketSiguiente(idticket);
            // Obtiene la fecha actual.
            string fechadia = Fecha();
            // Inicializa la opción.
            opcion = "";
            // Inicia un bucle 'do-while' para el menú.
            do
            {
                // Construye el encabezado del menú.
                membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
                membrete += "\n-----------------------------------------------------\n";
                // Obtiene el contenido del ticket actual.
                string Tickettexto = MostrarTicket(Vticket).Trim();
                // Si el ticket tiene productos, los agrega al encabezado.
                if (!string.IsNullOrWhiteSpace(Tickettexto))
                {
                    membrete += "\n" + Tickettexto + "\n";
                }
                // Define las opciones del menú.
                string[] datosmenu = { "1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida " };
                // Muestra el menú y captura la elección del usuario.
                opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu);
                // Verifica si la opción es nula.
                if (opcion == null)
                {
                    Console.WriteLine("dato incorrecto introducido");
                }
                else
                {
                    // Evalúa la opción del usuario.
                    switch (opcion)
                    {
                        // Si la opción es "1" (Agregar),
                        case "1":
                            CapturaVentaProducto(Vticket, productos, idticket, tamticket);
                            break;
                        // Si la opción es "2" (Eliminar),
                        case "2":
                            Eliminar(Vticket, productos);
                            break;
                        // Si la opción es "3" (Listado),
                        case "3":
                            if (ObtenerUltimaPosicion(Vticket) > -1)
                                Console.WriteLine(MostrarTicket(Vticket));
                            break;
                        // Si la opción es "4" (Pagar),
                        case "4":
                            Console.WriteLine(MostrarTicketVenta(Vticket, idticket, fechadia).Trim());
                            // Registra la venta en la memoria.
                            Pagar(idticket, ventas, Vticket);
                            // Marca el ticket como pagado.
                            pago = true;
                            // Fuerza la salida del bucle.
                            opcion = "5";
                            break;
                        // Si la opción es "5" (Salida),
                        case "5":
                            Console.WriteLine("Salida del Ventas");
                            // Si no se pagó, cancela la venta y devuelve el stock.
                            if (!pago)
                            {
                                Console.WriteLine("No pago el ticket");
                                Console.WriteLine("eliminando ticket " + idticket);
                                DevolucionTicket(Vticket, productos);
                            }
                            break;
                        // Si la opción no es válida,
                        default:
                            Console.WriteLine("No existe esta opcion");
                            break;
                    }
                }
                // El bucle se repite mientras la opción no sea "5".
            } while (opcion.CompareTo("5") != 0);
        }


        // TIPO: Función
        // REALIZA: Formatea los datos de un único registro de venta en una sola cadena de texto con espacios de relleno para una correcta alineación.
        // PARÁMETROS:
        //   - string[] venta: Un arreglo que contiene los 5 campos de un registro de venta (idticket, código, producto, precio, cantidad).
        // REGRESA: Una cadena (string) con la información de la venta formateada en una sola línea.
        public static string MostrarVenta(string[] venta)
        {
            // Llama a 'RellenarEspacios' para formatear el ID del ticket a un ancho de 6 caracteres.
            string idticket = RellenarEspacios(venta[0], 6);
            // Formatea el código del producto a un ancho de 5 caracteres.
            string codigo = RellenarEspacios(venta[1], 5);
            // Formatea el nombre del producto a un ancho de 30 caracteres.
            string producto = RellenarEspacios(venta[2], 30);
            // Formatea el precio a un ancho de 10 caracteres.
            string precio = RellenarEspacios(venta[3], 10);
            // Formatea la cantidad a un ancho de 10 caracteres.
            string cantidad = RellenarEspacios(venta[4], 10);
            // Concatena todas las cadenas formateadas en una sola.
            string cadena = idticket + codigo + producto + precio + cantidad;
            // Devuelve la cadena final con el registro de venta formateado.
            return cadena;
        }

        // TIPO: Función
        // REALIZA: Genera una lista completa y formateada de todo el historial de ventas.
        // PARÁMETROS:
        //   - string[,] ventas: La matriz de 2D que contiene los datos de todas las ventas.
        // REGRESA: Una cadena (string) que contiene el historial de ventas, con cada registro en una nueva línea.
        public static string MostrarListaVentas(string[,] ventas)
        {
            // Obtiene el índice de la última venta registrada para saber hasta dónde recorrer el arreglo.
            int posventas = ObtenerUltimaPosicion(ventas);
            // Inicializa una cadena vacía que acumulará la lista completa.
            string salida = "";
            // Inicia un bucle 'for' que recorrerá desde el primer hasta el último registro de venta.
            for (int ciclo = 0; ciclo <= posventas; ciclo++)
            {
                // Crea un arreglo temporal de 1D para almacenar los datos de la fila (registro) actual.
                string[] venta = { ventas[ciclo, 0], ventas[ciclo, 1], ventas[ciclo, 2], ventas[ciclo, 3], ventas[ciclo, 4] };
                // Llama a 'MostrarVenta' para formatear los datos del registro actual.
                string cadena = MostrarVenta(venta);
                // Concatena la línea del registro formateado y un salto de línea a la cadena de salida.
                salida += cadena + "\n";
            }
            // Devuelve la cadena 'salida' que ahora contiene el historial completo.
            return salida;
        }

        // TIPO: Procedimiento
        // REALIZA: Gestiona la interfaz y la lógica para agregar stock (cantidad de inventario) a un producto existente.
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz de productos que será consultada y modificada.
        // REGRESA: Nada (void).
        public static void AgregarStock(string[,] vproductos)
        {
            // Declara cadenas para almacenar el código y la cantidad que introducirá el usuario.
            string codigo, cantidad;
            // Declara un entero para almacenar la posición (índice) del producto encontrado.
            int posicion;
            // Llama a una función para obtener la lista formateada de todos los productos.
            string info = MostrarLista(vproductos);
            // Muestra la lista y pide al usuario que introduzca un código, usando la función 'Leer' para capturar la entrada.
            codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");
            // Verifica si el usuario introdujo un código (si no es nulo).
            if (codigo != null)
            {
                // Busca la posición del producto usando el código proporcionado.
                posicion = ExisteProducto(codigo, vproductos);
                // Verifica si el producto fue encontrado (si la posición es un índice válido, mayor que -1).
                if (posicion > -1)
                {
                    // Crea un arreglo temporal para mostrar la información del producto (código, nombre, cantidad actual).
                    string[] vproducto = { vproductos[posicion, 0], vproductos[posicion, 1], vproductos[posicion, 3], "" };
                    // Pide al usuario que introduzca la cantidad de stock que desea agregar.
                    cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ");
                    // Verifica si el usuario introdujo una cantidad.
                    if (cantidad != null)
                    {
                        // Evalúa si la cantidad introducida es un número.
                        if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1))
                        {
                            // Suma la cantidad nueva a la existente y la convierte a cadena.
                            string nuevacantidad = (int.Parse(cantidad) + int.Parse(vproducto[2])).ToString();
                            // Actualiza la cantidad en la matriz original de productos.
                            vproductos[posicion, 3] = nuevacantidad;
                        }
                        else
                        {
                            // Si no es un número, informa al usuario.
                            Console.WriteLine("no es un valor numerico");
                        }
                    }
                    else
                    {
                        // Si el campo de cantidad se dejó vacío, informa al usuario.
                        Console.WriteLine("dato nulo");
                    }
                }
                else
                {
                    // Si el producto no fue encontrado, informa al usuario.
                    Console.WriteLine("no existe el codigo");
                }
            }
            else
            {
                // Si el campo de código se dejó vacío, informa al usuario.
                Console.WriteLine("dato nulo");
            }
        }

        // TIPO: Procedimiento
        // REALIZA: Muestra el menú de opciones para la gestión del inventario y maneja la selección del usuario.
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz de productos, que se pasará a las funciones de listado y modificación de stock.
        // REGRESA: Nada (void).
        public static void MenuInventario(string[,] vproductos)
        {
            // Define un arreglo con las opciones de texto que se mostrarán en el menú.
            string[] datosmenuinventario = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
            // Declara una cadena para almacenar la opción del usuario.
            string opcion = "0";
            // Inicia un bucle 'do-while' que se ejecutará hasta que el usuario elija salir.
            do
            {
                // Muestra el menú de inventarios y captura la elección del usuario.
                opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario);
                // Verifica si la opción es nula (entrada inválida).
                if (opcion == null)
                {
                    Console.WriteLine("opcion incorrecta ");
                }
                else
                {
                    // Evalúa la opción en un 'switch'.
                    switch (opcion)
                    {
                        // Si la opción es "1" (Listado),
                        case "1":
                            // muestra la lista de productos (inventario).
                            Console.WriteLine(MostrarLista(vproductos));
                            break;
                        // Si la opción es "2" (Agregar),
                        case "2":
                            // llama al procedimiento para agregar stock.
                            AgregarStock(vproductos);
                            break;
                        // Si la opción es "3" (Salida),
                        case "3":
                            Console.WriteLine("Salida del Sistema ");
                            break;
                        // Si no es ninguna de las anteriores,
                        default:
                            Console.WriteLine("No existe esta opcion ");
                            break;
                    }
                }
                // El bucle se repite mientras la opción seleccionada no sea "3".
            } while (opcion.CompareTo("3") != 0);
        }

        // TIPO: Procedimiento
        // REALIZA: Es el bucle principal de la aplicación. Muestra el menú de nivel superior y dirige al usuario
        //          a los diferentes submódulos (Productos, Punto de Venta, etc.) según su elección.
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz que contiene el catálogo de productos.
        //   - string[,] vventas: La matriz que contiene el historial de ventas.
        // REGRESA: Nada (void).
        public static void MenuPrincipal(string[,] vproductos, string[,] vventas)
        {
            // Define un arreglo de cadenas con las opciones del menú principal.
            string[] datosmenuprincipal = { "1.-Productos ", "2.-Punto de Venta ", "3.- Inventario", "4.-Ventas", "5.-Salida " };
            // Declara una cadena para almacenar la opción del usuario.
            string opcion = "0";
            // Declara una cadena para almacenar el número del último ticket.
            string idticket;
            // Inicia un bucle 'do-while' que se ejecutará continuamente.
            do
            {
                // Antes de mostrar el menú, obtiene el ID del último ticket del historial de ventas.
                idticket = ObtenerUltimoValorVentas(vventas);
                // Muestra el menú principal y captura la elección del usuario.
                opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña", datosmenuprincipal);
                // Verifica si la opción es nula (entrada inválida).
                if (opcion == null)
                {
                    Console.WriteLine("opcion incorrecta ");
                }
                else
                {
                    // Evalúa la opción del usuario con una estructura 'switch'.
                    switch (opcion)
                    {
                        // Si la opción es "1" (Productos),
                        case "1":
                            MenuProductos(vproductos);
                            break;
                        // Si la opción es "2" (Punto de Venta),
                        case "2":
                            // llama al submenú de venta, pasándole los datos necesarios.
                            MenuPuntoVenta(vventas, idticket, vproductos);
                            break;
                        // Si la opción es "3" (Inventario),
                        case "3":
                            MenuInventario(vproductos);
                            break;
                        // Si la opción es "4" (Ventas),
                        case "4":
                            // muestra el historial de ventas en consola.
                            Console.WriteLine(MostrarListaVentas(vventas));
                            break;
                        // Si la opción es "5" (Salida),
                        case "5":
                            Console.WriteLine("Salida del Sistema ");
                            break;
                        // Si no es ninguna de las anteriores,
                        default:
                            Console.WriteLine("No existe esta opcion ");
                            break;
                    }
                }
                // El bucle se repite mientras la opción seleccionada no sea "5".
            } while (opcion.CompareTo("5") != 0);
        }

        // TIPO: Función
        // REALIZA: Busca en el historial de ventas y obtiene el ID del último ticket registrado.
        // PARÁMETROS:
        //   - string[,] ventas: La matriz que contiene el historial de todas las ventas.
        // REGRESA: Una cadena (string) con el ID del último ticket. Si no hay ventas, regresa "000".
        public static string ObtenerUltimoValorVentas(string[,] ventas)
        {
            // Inicializa una variable con un valor por defecto ("000").
            string ultimoValor = "000";
            // Llama a una función para encontrar el índice (la fila) de la última venta registrada.
            int ultimaposicion = ObtenerUltimaPosicion(ventas);
            // Comprueba si se encontró una venta (si el índice es 0 o mayor).
            if (ultimaposicion >= 0)
                // Si hay ventas, extrae el ID del ticket de la última fila.
                ultimoValor = ventas[ultimaposicion, 0];
            // Devuelve el último ID de ticket encontrado o el valor por defecto.
            return ultimoValor;
        }

        // TIPO: Procedimiento (Principal)
        // REALIZA: Es el punto de entrada de todo el programa. Carga los datos iniciales y arranca el menú principal.
        // PARÁMETROS:
        //   - string[] args: Un arreglo para argumentos de línea de comandos (no se usa).
        // REGRESA: Nada (void).
        public static void Main(string[] args)
        {
            // Llama a la función para cargar los productos y guarda el resultado en una matriz.
            string[,] productos = CargarProductos();
            // Llama a una función (presumiblemente existente) para crear/inicializar la matriz de ventas.
            string[,] ventas = CrearVenta();
            // Llama al menú principal, pasándole las matrices de productos y ventas ya inicializadas.
            MenuPrincipal(productos, ventas);
        }
        // FIN DEL CLASE PRINCIPAL
    }

}
