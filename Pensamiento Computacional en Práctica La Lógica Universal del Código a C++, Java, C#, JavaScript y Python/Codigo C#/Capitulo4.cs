using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibroFundamentos.Capitulo4
{
    internal class Capitulo4
    {

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


        // TIPO: Procedimiento
        // REALIZA: Muestra el menú de opciones para la gestión de productos y maneja la selección del usuario.
        // PARÁMETROS: Ninguno.
        // REGRESA: Nada (void).
        public static void MenuProductos()
        {
            // Define un arreglo de cadenas con las opciones que se mostrarán en el menú.
            string[] datosmenuproductos = { "1.-Modificar", "2.-Listado", "3.-Salida " };
            // Declara una cadena para almacenar la opción del usuario, inicializada para que el bucle comience.
            string opcion = "0";
            // Inicia un bucle 'do-while' que se ejecutará al menos una vez y continuará hasta que el usuario elija salir.
            do
            {
                // Llama a 'DesplegarMenu' para mostrar las opciones y capturar la respuesta del usuario.
                opcion = DesplegarMenu("Opciones de Productos ", datosmenuproductos);
                // Verifica si la opción es nula (lo que indica una entrada vacía o solo espacios).
                if (opcion == null)
                {
                    // Si es nula, muestra un mensaje de error.
                    Console.WriteLine("Opcion incorrecta ");
                }
                // Si la opción no es nula,
                else
                {
                    // evalúa la opción del usuario con una estructura 'switch'.
                    switch (opcion)
                    {
                        // Si la opción es "1",
                        case "1":
                            // muestra un mensaje indicando la acción.
                            Console.WriteLine("Modificar Precio Producto ");
                            // Termina este caso.
                            break;
                        // Si la opción es "2",
                        case "2":
                            // muestra un mensaje indicando la acción.
                            Console.WriteLine("Listado Producto ");
                            // Termina este caso.
                            break;
                        // Si la opción es "3",
                        case "3":
                            // muestra un mensaje de salida. El bucle terminará.
                            Console.WriteLine("Salida del Sistema ");
                            // Termina este caso.
                            break;
                        // Si la opción no es ninguna de las anteriores,
                        default:
                            // informa al usuario que la opción no es válida.
                            Console.WriteLine("No existe esta opcion ");
                            // Termina este caso.
                            break;
                    }
                }
                // El bucle se repite mientras la opción seleccionada no sea "3". 'CompareTo' devuelve 0 si son iguales.
            } while (opcion.CompareTo("3") != 0);
        }

        // TIPO: Procedimiento
        // REALIZA: Gestiona la interfaz del punto de venta para una transacción, simulando las operaciones.
        // PARÁMETROS:
        //   - String idticket: El ID del último ticket, usado como base para generar el nuevo.
        // REGRESA: Nada (void).
        public static void MenuPuntoVenta(String idticket)
        {
            // Declara una cadena para la opción del usuario y otra para el encabezado del menú.
            string opcion, membrete;
            // Declara una bandera para saber si el ticket fue pagado. Inicia en 'false'.
            bool pago = false;
            // Llama a la función para generar el siguiente número de ticket.
            idticket = IdTicketSiguiente(idticket);
            // Obtiene la fecha actual.
            string fechadia = Fecha();
            // Construye el encabezado del menú con la fecha y el número de ticket.
            membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
            // Agrega una línea separadora para mayor claridad.
            membrete += "\n-----------------------------------------------------\n";
            // Define un arreglo con las opciones del menú de venta.
            string[] datosmenu = { "1.-Agregar", "2.-Eliminar", "3.-Listado", "4.-Pagar ", "5.-Salida" };
            // Inicia un bucle 'do-while' que se ejecutará hasta que la opción sea "5".
            do
            {
                // Muestra el menú completo (encabezado + opciones) y captura la elección del usuario.
                opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta", datosmenu);
                // Verifica si la opción es nula.
                if (opcion == null)
                { Console.WriteLine("Dato incorrecto introducido"); }
                // Si la opción no es nula,
                else
                {
                    // la evalúa en una estructura 'switch'.
                    switch (opcion)
                    {
                        // Caso para la opción "1".
                        case "1":
                            Console.WriteLine("Agregar Articulo al Ticket "); break;
                        // Caso para la opción "2".
                        case "2":
                            Console.WriteLine("Eliminar Articulo del Ticket "); break;
                        // Caso para la opción "3".
                        case "3":
                            Console.WriteLine("Listado de Articulos del Ticket "); break;
                        // Caso para la opción "4" (Pagar).
                        case "4":
                            Console.WriteLine("Pagar Ticket y salir");
                            // Fija la 'opcion' a "5" para forzar la salida del bucle en la siguiente iteración.
                            opcion = "5";
                            // Establece la bandera 'pago' en 'true'.
                            pago = true;
                            break;
                        // Caso para la opción "5" (Salida).
                        case "5":
                            Console.WriteLine("Salida del Ventas ");
                            // Comprueba si el ticket NO fue pagado.
                            if (!pago)
                            {
                                // Si no se pagó, informa al usuario y simula la cancelación.
                                Console.WriteLine("No pago el ticket ");
                                Console.WriteLine("Eliminando ticket " + idticket);
                            }
                            break;
                        // Caso por defecto para opciones no válidas.
                        default:
                            Console.WriteLine("No existe esta opcion");
                            break;
                    }
                }
                // El bucle se repite mientras la opción seleccionada no sea "5".
            } while (opcion.CompareTo("5") != 0);
        }

        // TIPO: Procedimiento
        // REALIZA: Muestra el menú de opciones para la gestión de inventario.
        // PARÁMETROS: Ninguno.
        // REGRESA: Nada (void).
        public static void MenuInventario()
        {
            // Define un arreglo con las opciones del menú de inventario.
            string[] datosmenuinventario = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
            // Declara e inicializa la variable 'opcion' para controlar el bucle.
            string opcion = "0";
            // Inicia un bucle 'do-while' que se ejecutará hasta que la opción sea "3".
            do
            {
                // Muestra el menú de inventarios y captura la elección del usuario.
                opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario);
                // Verifica si la opción es nula.
                if (opcion == null)
                    Console.WriteLine("opcion incorrecta ");
                // Si no es nula, la evalúa en un 'switch'.
                else
                    switch (opcion)
                    {
                        // Caso para la opción "1".
                        case "1":
                            Console.WriteLine("Listado de Inventario  ");
                            break;
                        // Caso para la opción "2".
                        case "2":
                            Console.WriteLine("Agregar Inventario ");
                            break;
                        // Caso para la opción "3".
                        case "3":
                            Console.WriteLine("Salida del Sistema ");
                            break;
                        // Caso por defecto para opciones no válidas.
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
        // PARÁMETROS: Ninguno.
        // REGRESA: Nada (void).
        public static void MenuPrincipal()
        {
            // Define un arreglo con las opciones del menú principal.
            string[] datosmenuprincipal = { "1.-Productos ", "2.-Punto de Venta ", "3.-Inventario", "5.-Salida " };
            // Declara e inicializa la variable 'opcion' para controlar el bucle.
            string opcion = "0";
            // Inicia un bucle 'do-while' que se ejecutará hasta que el usuario elija salir.
            do
            {
                // Muestra el menú principal y captura la elección del usuario.
                opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña ", datosmenuprincipal);
                // Verifica si la opción es nula.
                if (opcion == null)
                {
                    Console.WriteLine("Opcion incorrecta ");
                }
                // Si no es nula,
                else
                {
                    // evalúa la opción en un 'switch'.
                    switch (opcion)
                    {
                        // Si la opción es "1" (Productos),
                        case "1":
                            // llama al submenú de gestión de productos.
                            MenuProductos();
                            break;
                        // Si la opción es "2" (Punto de Venta),
                        case "2":
                            // llama al submenú del punto de venta, iniciando con el ticket "000".
                            MenuPuntoVenta("000");
                            break;
                        // Si la opción es "3" (Inventario),
                        case "3":
                            // llama al submenú de gestión de inventario.
                            MenuInventario();
                            break;
                        // Si la opción es "5" (Salida),
                        case "5":
                            // muestra un mensaje de despedida.
                            Console.WriteLine("Salida del Sistema ");
                            break;
                        // Caso por defecto para opciones no válidas.
                        default:
                            Console.WriteLine("No existe esta opcion ");
                            break;
                    }
                }
                // El bucle se repite mientras la opción seleccionada no sea "5".
            } while (opcion.CompareTo("5") != 0);
        }

        // TIPO: Procedimiento (Principal)
        // REALIZA: Es el punto de entrada de todo el programa. Aquí comienza la ejecución.
        // PARÁMETROS:
        //   - string[] args: Un arreglo para recibir argumentos desde la línea de comandos (no se usa en este programa).
        // REGRESA: Nada (void).
        static void Main(string[] args)
        {
            // Llama al menú principal para iniciar la interacción con el usuario.
            MenuPrincipal();
        }




        // FIN DEL CLASE PRINCIPAL
    }

}
