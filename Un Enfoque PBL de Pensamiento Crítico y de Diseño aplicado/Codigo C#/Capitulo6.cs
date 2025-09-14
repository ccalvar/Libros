using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibroFundamentos.Capitulo6
{
    internal class Capitulo6
    {

        static string[,] productos;

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

        public static string[,] CargarProductos()
        {
            string[,] producto = {
    { "001", "Arroz 1kg", "35","10" },
    { "002", "Azúcar 1kg", "25","10" },
    { "003", "Harina 1kg", "28" ,"10"},
    { "004", "Aceite 1L", "50" , "10"},
    { "005", "Leche 1L", "35" , "10"},
    { "006", "Huevos 12 unidades", "45" ,"10" },
    { "007", "Fideos 500g", "20","10" },
    { "008", "Sal 1kg", "15" , "10"},
    { "009", "Pasta de tomate 400g", "25" , "10"},
    { "010", "Atún lata 170g", "35" , "10"}
    };
            return producto;
        }


        public static string MostrarProducto(string[] vproducto)
        {
            string codigo = RellenarEspacios(vproducto[0], 5);
            string producto = RellenarEspacios(vproducto[1], 30);
            string precio = RellenarEspacios(vproducto[2], 10);
            string cantidad = RellenarEspacios(vproducto[3], 10);
            string cadena = codigo + producto + precio + cantidad;
            return cadena;
        }


        public static string MostrarLista(string[,] vproductos)
        {
            string salida = "";
            for (int ciclo = 0; ciclo < 10; ciclo++)
            {
                string[] vproducto = { vproductos[ciclo, 0], vproductos[ciclo, 1], vproductos[ciclo, 2], vproductos[ciclo, 3] };
                string cadena = MostrarProducto(vproducto);
                salida = string.Concat(salida, cadena, "\n");
            }
            return salida;
        }


        public static int ExisteProducto(string codigo, string[,] vproductos)
        {
            int enc, pos, tam, ciclo;
            enc = -1;
            pos = 0;
            tam = vproductos.GetLength(0);
            for (ciclo = 0; ciclo < tam; ciclo++)
            {
                if (vproductos[ciclo, 0].CompareTo(codigo.Trim()) == 0)
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
                Console.Out.WriteLine(codigo);
                posicion = ExisteProducto(codigo, vproductos);
                if (posicion > -1)
                {
                    string[] vproducto = { vproductos[posicion, 0], vproductos[posicion, 1], vproductos[posicion, 2], vproductos[posicion, 3] };
                    precio = Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ");
                    if (precio != null)
                    {
                        if (EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1))
                        {
                            vproductos[posicion, 2] = precio;
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







        public static void MenuPuntoVenta(String idticket)
        {
            string opcion, membrete;
            bool pago = false;
            idticket = IdTicketSiguiente(idticket); // Actualizar idticket
            string fechadia = Fecha();
            membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
            membrete += "\n-----------------------------------------------------\n";
            string[] datosmenu = { "1.-Agregar", "2.-Eliminar", "3.-Listado", "4.-Pagar ", "5.-Salida" };
            do
            {
                opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu);
                if (opcion == null)
                { Console.WriteLine("Dato incorrecto introducido"); }
                else
                {
                    switch (opcion)
                    {
                        case "1":
                            Console.WriteLine("Agregar Articulo al Ticket "); break;
                        case "2":
                            Console.WriteLine("Eliminar Articulo del Ticket "); break;
                        case "3":
                            Console.WriteLine("Listado de Articulos del Ticket "); break;
                        case "4":
                            Console.WriteLine("Pagar Ticket y salir");
                            opcion = "5";
                            pago = true;
                            break;
                        case "5":
                            Console.WriteLine("Salida del Ventas ");
                            if (!pago)
                            {
                                Console.WriteLine("No pago el ticket ");
                                Console.WriteLine("Eliminando ticket " + idticket);
                            }
                            break;
                        default:
                            Console.WriteLine("No existe esta opcion");
                            break;
                    }
                }
            } while (opcion.CompareTo("5") != 0);
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
                    // Pide al usuario que introduzca la cantidad de stock que desea agregar, mostrando los datos del producto.
                    cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar " + MostrarProducto(vproducto) + " ");
                    // Verifica si el usuario introdujo una cantidad.
                    if (cantidad != null)
                    {
                        // Evalúa si la cantidad introducida es un número (entero o double).
                        if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1))
                        {
                            // Convierte la cantidad ingresada y la cantidad existente a enteros, las suma.
                            int nuevacantidad = int.Parse(cantidad) + int.Parse(vproducto[2]);
                            // Actualiza la cantidad en la matriz original (columna 3), convirtiendo el resultado a cadena.
                            vproductos[posicion, 3] = nuevacantidad.ToString();
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
                        Console.WriteLine(" dato nulo");
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
                Console.WriteLine(" dato nulo");
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
                    Console.WriteLine("opcion incorrecta ");
                // Si no es nula,
                else
                    // evalúa la opción en un 'switch'.
                    switch (opcion)
                    {
                        // Si la opción es "1" (Listado),
                        case "1":
                            // llama a la función que muestra la lista de productos y la imprime en consola.
                            Console.WriteLine(MostrarLista(vproductos));
                            break;
                        // Si la opción es "2" (Agregar),
                        case "2":
                            // llama al procedimiento para agregar stock a un producto.
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
                // El bucle se repite mientras la opción seleccionada no sea "3".
            }
            while (opcion.CompareTo("3") != 0);
        }

        // TIPO: Procedimiento
        // REALIZA: Es el bucle principal de la aplicación. Muestra el menú de nivel superior y dirige al usuario
        //          a los diferentes submódulos según su elección.
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz que contiene el catálogo de productos. Se pasa a los submenús que la necesiten.
        // REGRESA: Nada (void).
        public static void MenuPrincipal(string[,] vproductos)
        {
            // Define un arreglo de cadenas con las opciones que se mostrarán en el menú principal.
            string[] datosmenuprincipal = { "1.-Productos ", "2.-Punto de Venta ", "3.-Inventario", "5.-Salida " };
            // Declara una cadena para almacenar la opción del usuario.
            string opcion = "0";
            // Inicia un bucle 'do-while' que se ejecutará continuamente hasta que el usuario elija la opción de salida.
            do
            {
                // Muestra el menú principal y captura la elección del usuario.
                opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña ", datosmenuprincipal);
                // Verifica si la opción es nula (entrada inválida).
                if (opcion == null)
                {
                    Console.WriteLine("Opcion incorrecta ");
                }
                else
                {
                    // Evalúa la opción del usuario con una estructura 'switch'.
                    switch (opcion)
                    {
                        // Si la opción es "1" (Productos),
                        case "1":
                            // llama al submenú de productos, pasándole la matriz del catálogo.
                            MenuProductos(vproductos);
                            break;
                        // Si la opción es "2" (Punto de Venta),
                        case "2":
                            // llama al submenú del punto de venta.
                            MenuPuntoVenta("000");
                            break;
                        // Si la opción es "3" (Inventario),
                        case "3":
                            // llama al submenú de inventario, pasándole la matriz del catálogo.
                            MenuInventario(vproductos);
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


        static void Main(string[] args)
        {
            productos = CargarProductos();
            MenuPrincipal(productos);
        }


        // FIN DEL CLASE PRINCIPAL
    }

}
