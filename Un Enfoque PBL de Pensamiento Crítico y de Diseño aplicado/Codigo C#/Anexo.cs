using System;
using System.Collections.Generic;
using System.IO;
// Importa el espacio de nombres para manejar la entrada y salida de datos (Input/Output), 
// especialmente para trabajar con el sistema de archivos. Contiene clases para leer y escribir en archivos, 
// manipular directorios y más.
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Net.WebRequestMethods;

namespace LibroFundamentos.Anexo
{
    internal class Anexo
    {
        static string[,] productos;

        static String[,] ventas;
	    static int posventas = -1;
        static int tamventas = 100;
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


        public static string[,] CrearVenta()
        {
            return  new string[tamventas,5];
        }

        public static string UltimoTicket(int pos, string[,] mventa)
        {
            string idticket = "000";
            if (pos > -1)
            {
                idticket = mventa[pos,0];
            }
            return idticket;
        }
        
        public static string[,] CrearTicket()
        {
            return new string [20,4];
        }


        public static int ExisteTicketCodigo(string[,] mticket, string codigo)
        {
            int enc = -1;
            int pos = ObtenerUltimaPosicion(mticket);
            Console.WriteLine("buscando " + codigo + " tamaño arreglo " + pos);
            for (int ciclo = 0; ciclo <= pos; ciclo++)
            {
                if (mticket[ciclo, 0].Trim().CompareTo(codigo.Trim()) == 0)
                {
                    enc = ciclo;
                    return enc;
                }
            }
            return enc;
        }

        public static bool InsertarProductoTicket(string[,] mticket, string[] datos, int tamticket)
        {
            bool sucedio = true;
            int enc = ExisteTicketCodigo(mticket, datos[0]);
            int posticket = ObtenerUltimaPosicion(mticket);
            if (posticket < tamticket)
            {
                if (enc > -1)
                {
                    Console.WriteLine("ya existe el producto en el ticket lo incrementare");
                    int cantidadactual = int.Parse(mticket[enc, 3]);
                    mticket[enc, 3] = (cantidadactual + 1).ToString();
                }
                else
                {
                    posticket++;
                    mticket[posticket, 0] = datos[0];
                    mticket[posticket, 1] = datos[1];
                    mticket[posticket, 2] = datos[2];
                    mticket[posticket, 3] = datos[3];
                    Console.WriteLine("Insertarndo No existe el producto en el ticket ");
                }
            }
            else
            {
                sucedio = false;
            }
            return sucedio;
        }

        public static string TotalProducto(string precio, string cantidad)
        {
            double total = double.Parse(precio) * double.Parse(cantidad);
            return total.ToString("000000.00");
        }

        public static string MostrarProductoTicket(string[,] mticket, int pos)
        {
            string codigo = RellenarEspacios(mticket[pos,0], 5);
            string producto = RellenarEspacios(mticket[pos,1], 30);
            string precio = RellenarEspacios(mticket[pos,2], 10);
            string cantidad = RellenarEspacios(mticket[pos,3], 5);
            string totalproducto = RellenarEspacios(TotalProducto(mticket[pos,2], mticket[pos,3]), 10);
            string cadena = codigo + producto + precio + cantidad + totalproducto;
            return cadena;
        }


        public static string MostrarTicket(string[,] mticket)
        {
            string salida = "";
            int pos = ObtenerUltimaPosicion(mticket);
            for (int ciclo = 0; ciclo <= pos; ciclo++)
            {
                salida = salida + MostrarProductoTicket(mticket, ciclo) + "\n";
            }
            return salida;
        }

        public static double SubTotalTicket(string[,] mticket)
        {
            double subtotal = 0;
            int pos = ObtenerUltimaPosicion(mticket);
            for (int ciclo = 0; ciclo <= pos; ciclo++)
            {
                subtotal += double.Parse(TotalProducto(mticket[ciclo, 2], mticket[ciclo, 3]));
            }
            return subtotal;
        }


        public static double IvaTicket(string[,] mticket)
        {
            double subtotal = SubTotalTicket(mticket);
            if (subtotal > 0)
                subtotal = 0.16 * subtotal;
            else
                subtotal = -1;
            return subtotal;
        }

        public static double TotalTicket(string[,] mticket)
        {
            double total = SubTotalTicket(mticket);
            if (total > 0)
                total = IvaTicket(mticket) + total;
            return total;
        }

        public static string MostrarTicketVenta(string[,] mticket, string idticket, string fecha)
        {
            string salida = "";
            string subtotal = string.Format("{0:F2}", SubTotalTicket(mticket));
            string iva = string.Format("{0:F2}", IvaTicket(mticket));
            string total = string.Format("{0:F2}", TotalTicket(mticket));
            salida = "Fecha " + fecha + " Ticket No." + idticket;
            salida += "\n" + MostrarTicket(mticket);
            salida += "\n\n El total sin iva " + subtotal;
            salida += "\n el iva total es " + iva;
            salida += "\n el total de la venta fue " + total;
            return salida;
        }

        public static string MostrarListaProductosVenta(string[,] vproductos)
        {
            string salida = "";
            for (int ciclo = 0; ciclo < 10; ciclo++)
            {
                int existencia = int.Parse(vproductos[ciclo, 3]);
                if (existencia > 0)
                {
                    string[] vproducto = new string[vproductos.GetLength(1)];
                    for (int i = 0; i < vproductos.GetLength(1); i++)
                    {
                        vproducto[i] = vproductos[ciclo, i];
                    }
                    string cadena = MostrarProducto(vproducto);
                    salida += cadena + "\n";
                }
            }
            return salida;
        }



        public static void CapturaVentaProducto(string[,] mticket, string[,] mproductos, string idticket, int tamticket)
        {
            string codigo, info;
            info = MostrarListaProductosVenta(mproductos);
            codigo = Leer(info + "\nIntroduce el codigo del producto");
            if (codigo != null)
            {
                int posp = ExisteProducto(codigo.Trim(), mproductos);
                if (posp > -1)
                {
                    if (int.Parse(mproductos[posp, 3]) > 0)
                    {
                        string[] producto = new string[mproductos.GetLength(1)];
                        for (int i = 0; i < mproductos.GetLength(1); i++)
                        {
                            producto[i] = mproductos[posp, i];
                        }
                        int cant = int.Parse(mproductos[posp,3]);
                        cant = cant - 1;
                        mproductos[posp, 3] = cant.ToString();
                        Console.WriteLine(MostrarProducto(producto));
                        string[] venta = new string[4];
                        venta[0] = mproductos[posp, 0];
                        venta[1] = mproductos[posp, 1];
                        venta[2] = mproductos[posp, 2];
                        venta[3] = "1";
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


        public static void RemoverProductoTicket(string[,] mticket, int pos)
        {
            int tam = ObtenerUltimaPosicion(mticket);
            if (tam > pos)
            {
                for (int i = pos; i < tam; i++)
                {
                    for (int j = 0; j < mticket.GetLength(1); j++)
                    {
                        mticket[i, j] = mticket[i + 1, j];
                    }
                }
                for (int j = 0; j < mticket.GetLength(1); j++)
                {
                    mticket[tam, j] = null;
                }
            }
            else
            {
                for (int j = 0; j < mticket.GetLength(1); j++)
                {
                    mticket[pos, j] = null;
                }
            }
        }

        public static void EliminarProductoTicket(string[,] mticket, int pos)
        {
            int cantidad = int.Parse(mticket[pos, 3]);
            if (cantidad > 1)
            {
                mticket[pos, 3] = (cantidad - 1).ToString();
            }
            else
            {
                RemoverProductoTicket(mticket, pos);
            }
        }

        public static void Eliminar(string[,] mticket, string[,] mproductos)
        {
            string codigo, info;
            info = MostrarTicket(mticket);
            codigo = Leer(info + "\nIntroduce el codigo del producto");
            if (codigo != null)
            {
                int pos = ExisteTicketCodigo(mticket, codigo);
                if (pos > -1)
                {
                    int posproducto = ExisteProducto(codigo, mproductos);
                    string nuevacantidad = (int.Parse(mproductos[posproducto, 3]) + 1).ToString();
                    mproductos[posproducto, 3] = nuevacantidad;
                    EliminarProductoTicket(mticket, pos);
                }
            }
            else
            {
                Console.WriteLine("dato nulo");
            }
        }

        public static void AgregarProductoAVenta(string[,] mticket, string[,] mventa, string idticket)
        {
            int posticket, posventas;
            posventas = ObtenerUltimaPosicion(mventa);
            posticket = ObtenerUltimaPosicion(mticket);
            for (int i = 0; i <= posticket; i++)
            {
                if (mticket[i, 0] != null)
                { // Verificar que la fila no esté vacía
                  // Asumimos que mticket tiene: [codigo, nombre, precio, cantidad]
                    posventas++;
                    mventa[posventas, 0] = idticket; // Establecer el ID del ticket
                    mventa[posventas, 1] = mticket[i, 0]; // Código del producto
                    mventa[posventas, 2] = mticket[i, 1]; // Nombre del producto
                    mventa[posventas, 3] = mticket[i, 2]; // Precio del producto
                    mventa[posventas, 4] = mticket[i, 3]; // Cantidad del producto
                }
            }
        }

        public static void Pagar(string idticket, string[,] mventa, string[,] mticket)
        {
            int posventas = ObtenerUltimaPosicion(mventa);
            int post = ObtenerUltimaPosicion(mticket);
            if ((posventas + post) < 100)
            {
                AgregarProductoAVenta(mticket, mventa, idticket);
            }
            else
            {
                Console.WriteLine("Desbordamiento de Memoria de ventas");
            }
        }

        public static void DevolucionTicket(string[,] mticket, string[,] mproductos)
        {
            int posmticket = ObtenerUltimaPosicion(mticket);

            for (int pos = 0; pos <= posmticket; pos++)
            {
                string codigo = mticket[pos, 0];
                int posp = ExisteProducto(codigo.Trim(), mproductos);

                if (posp > -1)
                {
                    int cant = int.Parse(mticket[pos, 3]) + int.Parse(mproductos[posp, 3]);
                    mproductos[posp, 3] = cant.ToString();
                }
            }
        }



        // TIPO: Procedimiento
        // REALIZA: Es el motor principal del punto de venta. Gestiona una transacción completa: crea un ticket,
        //          permite agregar/eliminar productos, y al pagar, registra la venta tanto en la memoria del programa
        //          como en archivos CSV para persistencia de datos.
        // PARÁMETROS:
        //   - string[,] ventas: La matriz del historial de ventas en memoria.
        //   - string idticket: El ID del último ticket, usado como base para generar el nuevo.
        //   - string[,] productos: La matriz del catálogo de productos para consultar y modificar el stock.
        //   - String narchivo: El nombre del archivo CSV donde se guardará el detalle de los productos de la venta actual.
        // REGRESA: Nada (void).
        public static void MenuPuntoVenta(string[,] ventas, string idticket, string[,] productos, String narchivo)
        {
            // Declara una cadena para la opción del usuario y otra para el encabezado del menú.
            string opcion, membrete;
            // Declara una bandera para saber si el ticket fue pagado. Inicia en 'false'.
            bool pago = false;
            // Define una constante para el tamaño máximo de productos en un solo ticket.
            int tamticket = 50;
            // Crea una matriz local 'Vticket' que representará el ticket actual. Se inicializa vacía.
            string[,] Vticket = new string[tamticket, 4];

            // Llama a la función para generar el siguiente número de ticket basado en el último.
            idticket = IdTicketSiguiente(idticket);
            // Obtiene la fecha actual para mostrarla en el ticket.
            string fechadia = Fecha();
            // Inicializa la variable 'opcion'.
            opcion = "";
            // Inicia un bucle 'do-while' que se repetirá hasta que el usuario elija salir (opción "5").
            do
            {
                // Construye el encabezado del menú con la fecha y el número de ticket.
                membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
                // Agrega una línea separadora para mayor claridad.
                membrete += "\n-----------------------------------------------------\n";
                // Obtiene el contenido del ticket actual en formato de texto.
                string Tickettexto = MostrarTicket(Vticket).Trim();
                // Si el ticket ya tiene productos (y no es solo espacio en blanco),
                if (!string.IsNullOrWhiteSpace(Tickettexto))
                {
                    // los agrega al encabezado para que el usuario vea lo que lleva comprado.
                    membrete += "\n" + Tickettexto + "\n";
                }
                // Define las opciones del menú de venta.
                string[] datosmenu = { "1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida " };
                // Muestra el menú completo (encabezado + opciones) y captura la elección del usuario.
                opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu);
                // Verifica si la opción es nula (entrada inválida).
                if (opcion == null)
                {
                    Console.WriteLine("dato incorrecto introducido");
                }
                else
                {
                    // Evalúa la opción del usuario en una estructura 'switch'.
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
                            // verifica si el ticket tiene contenido antes de intentar mostrarlo.
                            if (ObtenerUltimaPosicion(Vticket) > -1)
                                Console.WriteLine(MostrarTicket(Vticket));
                            break;
                        // Si la opción es "4" (Pagar),
                        case "4":
                            // muestra el recibo final al usuario.
                            Console.WriteLine(MostrarTicketVenta(Vticket, idticket, fechadia).Trim());
                            // Llama a 'Pagar' para registrar la venta en la memoria del programa.
                            Pagar(idticket, ventas, Vticket);
                            // Comprueba si el ticket tiene al menos un producto antes de guardarlo en archivo.
                            if (ObtenerUltimaPosicion(Vticket) > -1)
                            {
                                // Mensaje de depuración para ver el estado de los arreglos.
                                Console.WriteLine("tamaño de venta" + ObtenerUltimaPosicion(ventas) + " " + ObtenerUltimaPosicion(Vticket));
                                // Guarda el detalle de los productos del ticket en el archivo CSV diario.
                                GuardarDatosCsvVentaTicket(Vticket, narchivo, ObtenerUltimaPosicion(Vticket), idticket);
                                // Genera una línea de resumen de la venta en formato CSV.
                                string cadena = GenerarCsvFilaVenta(fechadia, idticket, string.Format("{0:F2}", SubTotalTicket(Vticket)), string.Format("{0:F2}", IvaTicket(Vticket)), string.Format("{0:F2}", TotalTicket(Vticket)));
                                // Guarda la línea de resumen en el archivo CSV principal de ventas.
                                GuardarDatosCsvVenta("ventas.csv", cadena);
                            }
                            // Establece la bandera 'pago' en 'true'.
                            pago = true;
                            // Fija la 'opcion' a "5" para forzar la salida del bucle.
                            opcion = "5";
                            break;
                        // Si la opción es "5" (Salida),
                        case "5":
                            Console.WriteLine("Salida del Ventas");
                            // Comprueba si el ticket NO fue pagado.
                            if (!pago)
                            {
                                // Si no se pagó, informa al usuario y cancela la venta.
                                Console.WriteLine("No pago el ticket");
                                Console.WriteLine("eliminando ticket " + idticket);
                                // Llama a 'DevolucionTicket' para regresar el stock de los productos al inventario.
                                DevolucionTicket(Vticket, productos);
                            }
                            break;
                        // Si la opción no coincide con ningún caso,
                        default:
                            Console.WriteLine("No existe esta opcion");
                            break;
                    }
                }
                // El bucle se repite mientras la opción sea diferente de "5".
            } while (opcion.CompareTo("5") != 0);
        }



        public static string MostrarVenta(string[] venta)
        {
            string idticket = RellenarEspacios(venta[0], 6);
            string codigo = RellenarEspacios(venta[1], 5);
            string producto = RellenarEspacios(venta[2], 30);
            string precio = RellenarEspacios(venta[3], 10);
            string cantidad = RellenarEspacios(venta[4], 10);
            string cadena = idticket + codigo + producto + precio + cantidad;
            return cadena;
        }

        public static string MostrarListaVentas(string[,] ventas)
        {
            int posventas = ObtenerUltimaPosicion(ventas);
            string salida = "";
            for (int ciclo = 0; ciclo <= posventas; ciclo++)
            {
                string[] venta = { ventas[ciclo, 0], ventas[ciclo, 1], ventas[ciclo, 2], ventas[ciclo, 3], ventas[ciclo, 4] };
                string cadena = MostrarVenta(venta);
                salida += cadena + "\n";
            }
            return salida;
        }

        public static void AgregarStock(string[,] vproductos)
        {
            string codigo, cantidad;
            int posicion;
            string info = MostrarLista(vproductos);
            codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");
            if (codigo != null)
            {
                posicion = ExisteProducto(codigo, vproductos);
                if (posicion > -1)
                {
                    string[] vproducto = { vproductos[posicion, 0], vproductos[posicion, 1], vproductos[posicion, 3], "" };
                    cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ");
                    if (cantidad != null)
                    {
                        if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1))
                        {
                            string nuevacantidad = (int.Parse(cantidad) + int.Parse(vproducto[2])).ToString();
                            vproductos[posicion, 3] = nuevacantidad;
                        }
                        else
                        {
                            Console.WriteLine("no es un valor numerico");
                        }
                    }
                    else
                    {
                        Console.WriteLine("dato nulo");
                    }
                }
                else
                {
                    Console.WriteLine("no existe el codigo");
                }
            }
            else
            {
                Console.WriteLine("dato nulo");
            }
        }

        public static void MenuInventario(string[,] vproductos)
        {
            string[] datosmenuinventario = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
            string opcion = "0";
            do
            {
                opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario);
                if (opcion == null)
                {
                    Console.WriteLine("opcion incorrecta ");
                }
                else
                {
                    switch (opcion)
                    {
                        case "1":
                            Console.WriteLine(MostrarLista(vproductos));
                            break;
                        case "2":
                            AgregarStock(vproductos);
                            break;
                        case "3":
                            Console.WriteLine("Salida del Sistema ");
                            break;
                        default:
                            Console.WriteLine("No existe esta opcion ");
                            break;
                    }
                }
            } while (opcion.CompareTo("3") != 0);
        }

        // TIPO: Procedimiento
        // REALIZA: Es el bucle principal de la aplicación. Al iniciar, intenta leer el último ticket de un archivo
        //          CSV del día para mantener la continuidad. Muestra el menú principal y dirige al usuario
        //          a los diferentes submódulos según su elección.
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz del catálogo de productos.
        //   - string[,] vventas: La matriz del historial de ventas en memoria.
        // REGRESA: Nada (void).
        public static void MenuPrincipal(string[,] vproductos, string[,] vventas)
        {
            // Define un arreglo de cadenas con las opciones que se mostrarán en el menú principal.
            string[] datosmenuprincipal = { "1.-Productos ", "2.-Punto de Venta ", "3.- Inventario", "4.-Ventas", "5.-Salida " };
            // Declara una cadena para almacenar la opción del usuario.
            string opcion = "0";
            // Declara una cadena para almacenar el número del último ticket.
            string idticket = "";

            // --- CAMBIO REALIZADO POR EL ANEXO ---
            // Genera el nombre del archivo de ventas para el día actual (ej: "14-09-2025.cvs").
            String narchivo = Fecha() + ".cvs";
            // Comprueba si el archivo de ventas del día de hoy ya existe.
            if (ExisteArchivo(narchivo))
            {
                // Mensaje de depuración para indicar que se está leyendo un archivo existente.
                Console.WriteLine("leyendo archivo" + narchivo);
                // Si existe, lee el archivo para obtener el último ID de ticket guardado y continuar la secuencia.
                idticket = LeerDatosCvs(narchivo);
            }
            // Inicia un bucle 'do-while' que se ejecutará continuamente hasta que el usuario elija la opción de salida.
            do
            {
                // Si 'idticket' está vacío o nulo (porque el archivo no existía o una venta acaba de terminar),
                if (String.IsNullOrEmpty(idticket))
                    // obtiene el último ID de ticket desde la memoria del programa como respaldo.
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
                            // llama al submenú de venta, pasándole todos los datos necesarios, incluido el nombre del archivo.
                            MenuPuntoVenta(vventas, idticket, vproductos, narchivo);
                            // Resetea 'idticket' a nulo para forzar que se vuelva a calcular en la siguiente iteración del bucle.
                            idticket = null;
                            break;
                        // Si la opción es "3" (Inventario),
                        case "3":
                            MenuInventario(vproductos);
                            break;
                        // Si la opción es "4" (Ventas),
                        case "4":
                            // muestra el historial de ventas en memoria.
                            Console.WriteLine(MostrarListaVentas(vventas));
                            break;
                        // Si la opción es "5" (Salida),
                        case "5":
                            Console.WriteLine("Salida del Sistema ");
                            break;
                        // Si la opción no es ninguna de las anteriores,
                        default:
                            Console.WriteLine("No existe esta opcion ");
                            break;
                    }
                }
                // El bucle se repite mientras la opción seleccionada no sea "5".
            } while (opcion.CompareTo("5") != 0);
        }


        public static string ObtenerUltimoValorVentas(string[,] ventas)
        {
            string ultimoValor = "000";
            int ultimaposicion = ObtenerUltimaPosicion(ventas);
                if (ultimaposicion>=0)
                    ultimoValor = ventas[ultimaposicion, 0];
            return ultimoValor;
        }
       
        // TIPO: Función
        // REALIZA: Comprueba si un archivo existe en la ruta especificada.
        // PARÁMETROS:
        //   - string narchivo: El nombre o la ruta del archivo a verificar.
        // REGRESA: Un booleano. 'true' si el archivo existe, 'false' en caso contrario.
        public static bool ExisteArchivo(string narchivo)
        {
            // Utiliza el método estático 'Exists' de la clase 'File' para realizar la comprobación de forma directa.
            return System.IO.File.Exists(narchivo);
        }

        // TIPO: Función
        // REALIZA: Formatea una fila de datos para un ticket en formato CSV (valores separados por comas).
        // PARÁMETROS:
        //   - string idticket: El número del ticket.
        //   - string dato1 a dato4: Los datos del producto (código, nombre, precio, cantidad).
        // REGRESA: Una cadena (string) con todos los datos concatenados y separados por comas.
        public static string GenerarCVSFilaTicket(string idticket, string dato1, string dato2, string dato3, string dato4)
        {
            // Concatena todos los parámetros con comas, eliminando espacios extra de cada dato con .Trim().
            return idticket.Trim() + "," + dato1.Trim() + "," + dato2.Trim() + "," + dato3.Trim() + "," + dato4.Trim();
        }

        // TIPO: Procedimiento
        // REALIZA: Convierte una matriz entera de un ticket a formato CSV y la guarda en un archivo.
        // PARÁMETROS:
        //   - string[,] matriz: La matriz con los datos del ticket.
        //   - string nombrearchivo: El nombre del archivo donde se guardarán los datos.
        //   - int filas: El número de filas (productos) a procesar en la matriz.
        //   - string idticket: El número de ticket a registrar con cada producto.
        // REGRESA: Nada (void).
        public static void GuardarDatosCsvVentaTicket(string[,] matriz, string nombrearchivo, int filas, string idticket)
        {
            // Inicializa una cadena para acumular todo el contenido CSV.
            string cadena = "";
            // Recorre cada fila (producto) de la matriz.
            for (int fila = 0; fila <= filas; fila++)
            {
                // Llama a la función para generar la línea CSV para el producto actual.
                string cadenafila = GenerarCVSFilaTicket(idticket, matriz[fila, 0], matriz[fila, 1], matriz[fila, 2], matriz[fila, 3]);
                // Imprime la línea en consola para depuración.
                Console.WriteLine(fila + " " + cadenafila + "\n");
                // Acumula la línea generada y un salto de línea en la cadena principal.
                cadena += cadenafila + "\n";
            }
            // Imprime la cadena completa en consola para depuración.
            Console.WriteLine("este es el archivo" + cadena + "\n");
            // Llama a la función para escribir la cadena completa en el archivo CSV.
            EscribirArchivoCSV(nombrearchivo, cadena);
        }

        // TIPO: Procedimiento
        // REALIZA: Abre un archivo en modo de "añadir" (append) y escribe una línea de contenido al final.
        // PARÁMETROS:
        //   - string archivo: El nombre o la ruta del archivo.
        //   - string contenido: La cadena de texto que se va a escribir.
        // REGRESA: Nada (void).
        static void EscribirArchivoCSV(string archivo, string contenido)
        {
            // Inicia un bloque 'try-catch' para manejar posibles errores de archivo.
            try
            {
                // Usa el método 'AppendAllText' que abre, escribe al final y cierra el archivo en una sola operación.
                // Si el archivo no existe, lo crea automáticamente.
                System.IO.File.AppendAllText(archivo, contenido);
                // Informa al usuario que la operación fue exitosa.
                Console.WriteLine("Datos guardados correctamente.");
            }
            catch (Exception e)
            {
                // Si ocurre un error, informa al usuario con el mensaje de la excepción.
                Console.WriteLine("Ocurrió un error al escribir en el archivo: " + e.Message);
            }
        }

        // TIPO: Función
        // REALIZA: Lee un archivo CSV y devuelve el primer campo de la última línea no vacía.
        // PARÁMETROS:
        //   - string nombreArchivo: El nombre del archivo a leer.
        // REGRESA: Una cadena (string) con el dato extraído (ej. el último ID de ticket).
        public static string LeerDatosCvs(string nombreArchivo)
        {
            // Inicializa la variable que guardará el dato extraído.
            string primerDato = "";
            // Inicia un bloque 'try-catch' para manejar errores de lectura.
            try
            {
                // Crea un objeto 'StreamReader' para leer el archivo de texto.
                StreamReader lector = new StreamReader(nombreArchivo);
                // Declara una cadena para almacenar cada línea leída.
                string linea;
                // Lee el archivo línea por línea hasta que no haya más contenido.
                while ((linea = lector.ReadLine()) != null)
                {
                    // Elimina espacios en blanco al principio y al final de la línea.
                    linea = linea.Trim();
                    // Procesa la línea solo si no está vacía.
                    if (!string.IsNullOrEmpty(linea))
                    {
                        // Divide la línea en partes usando la coma como separador.
                        string[] datos = linea.Split(',');
                        // Si la división generó al menos un dato,
                        if (datos.Length > 0)
                        {
                            // guarda el primer dato. Se sobrescribirá en cada línea, quedando al final el de la última.
                            primerDato = datos[0];
                        }
                    }
                }
            }
            catch (IOException e)
            {
                // Si ocurre un error de E/S, informa al usuario.
                Console.WriteLine("Error al leer el archivo: " + e.Message);
            }
            // Devuelve el último 'primerDato' que se encontró.
            return primerDato;
        }

        // TIPO: Función
        // REALIZA: Formatea una fila de resumen de venta en formato CSV.
        // PARÁMETROS:
        //   - string dato1 a dato5: Los cinco campos de datos para la fila de resumen.
        // REGRESA: Una cadena (string) con los datos concatenados, separados por comas y con un salto de línea final.
        public static string GenerarCsvFilaVenta(string dato1, string dato2, string dato3, string dato4, string dato5)
        {
            // Concatena los datos, les quita espacios y añade un salto de línea al final.
            return dato1.Trim() + "," + dato2.Trim() + "," + dato3.Trim() + "," + dato4.Trim() + "," + dato5.Trim() + "," + "\n";
        }

        // TIPO: Procedimiento
        // REALIZA: Guarda una cadena de contenido en un archivo CSV.
        // PARÁMETROS:
        //   - string nombreArchivo: El nombre del archivo donde se guardará el contenido.
        //   - string contenido:
        // REGRESA: Nada (void).
        public static void GuardarDatosCsvVenta(string nombreArchivo, string contenido)
        {
            // Comprueba si el archivo ya existe (aunque es opcional con el método de escritura usado).
            Boolean existe = ExisteArchivo(nombreArchivo);
            // Llama a la función genérica para escribir (añadir) el contenido al archivo.
            EscribirArchivoCSV(nombreArchivo, contenido);
        }

        public static void Main(string[] args)
        {
            string[,] productos = CargarProductos();
            string[,] ventas = CrearVenta();
            MenuPrincipal(productos, ventas);
        }




        // FIN DEL CLASE PRINCIPAL
    }

}
