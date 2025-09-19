using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibroFundamentos.Capitulo5
{
    internal class Capitulo5
    {
        static string[,] productos;
        // Declara una matriz estática (global a la clase) para almacenar el catálogo de productos.

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

        // TIPO: Función
        // REALIZA: Crea e inicializa una matriz de 10x4 con los datos de los productos del catálogo.
        // PARÁMETROS: Ninguno.
        // REGRESA: Una matriz de dos dimensiones (string[,]) con todos los productos cargados.
        public static string[,] CargarProductos()
        {
            // Declara e inicializa directamente la matriz con los datos predefinidos.
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
            // Devuelve la matriz ya cargada con los datos.
            return producto;
        }

        // TIPO: Función
        // REALIZA: Formatea los datos de un único producto en una sola cadena de texto con espacios de relleno para una correcta alineación.
        // PARÁMETROS:
        //   - string[] vproducto: Un arreglo que contiene los 4 atributos (código, nombre, precio, cantidad) de un solo producto.
        // REGRESA: Una cadena (string) con la información del producto formateada en una sola línea.
        public static string MostrarProducto(string[] vproducto)
        {
            // Llama a 'RellenarEspacios' para formatear el código a un ancho de 5 caracteres.
            string codigo = RellenarEspacios(vproducto[0], 5);
            // Formatea el nombre del producto a un ancho de 30 caracteres.
            string producto = RellenarEspacios(vproducto[1], 30);
            // Formatea el precio a un ancho de 10 caracteres.
            string precio = RellenarEspacios(vproducto[2], 10);
            // Formatea la cantidad a un ancho de 10 caracteres.
            string cantidad = RellenarEspacios(vproducto[3], 10);
            // Concatena todas las cadenas formateadas en una sola.
            string cadena = codigo + producto + precio + cantidad;
            // Devuelve la cadena final con el producto formateado.
            return cadena;
        }

        // TIPO: Función
        // REALIZA: Genera una lista completa y formateada de todos los productos de la matriz.
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz de 2D que contiene los datos de todos los productos.
        // REGRESA: Una cadena (string) que contiene la lista de todos los productos, cada uno en una nueva línea.
        public static string MostrarLista(string[,] vproductos)
        {
            // Inicializa una cadena vacía que acumulará la lista completa.
            string salida = "";
            // Inicia un bucle 'for' que se repetirá para cada producto en la matriz.
            for (int ciclo = 0; ciclo < 10; ciclo++)
            {
                // Crea un arreglo temporal de 1D para almacenar los datos de la fila actual.
                string[] vproducto = { vproductos[ciclo, 0], vproductos[ciclo, 1], vproductos[ciclo, 2], vproductos[ciclo, 3] };
                // Llama a 'MostrarProducto' para formatear los datos del producto actual.
                string cadena = MostrarProducto(vproducto);
                // Concatena la línea del producto formateado y un salto de línea a la cadena de salida.
                salida = string.Concat(salida, cadena, "\n");
            }
            // Devuelve la cadena 'salida' que ahora contiene la lista completa.
            return salida;
        }

        // TIPO: Función
        // REALIZA: Busca un producto en la matriz por su código.
        // PARÁMETROS:
        //   - string codigo: El código del producto que se desea encontrar.
        //   - string[,] vproductos: La matriz de 2D que contiene todos los productos.
        // REGRESA: Un entero (int). Devuelve el índice (fila) del producto si lo encuentra; de lo contrario, devuelve -1.
        public static int ExisteProducto(string codigo, string[,] vproductos)
        {
            // Declara las variables para el bucle y los resultados.
            int enc, pos, tam, ciclo;
            // Inicializa 'enc' en -1. Este será el valor de retorno si no se encuentra el producto.
            enc = -1;
            // Inicializa 'pos' en 0 para llevar la cuenta de la fila actual (índice).
            pos = 0;
            // Obtiene el número total de filas (productos) en la matriz.
            tam = vproductos.GetLength(0);
            // Inicia un bucle 'for' que recorrerá cada fila de la matriz.
            for (ciclo = 0; ciclo < tam; ciclo++)
            {
                // Imprime un mensaje de depuración en la consola.
                Console.Out.WriteLine(" fila" + ciclo + " tamaño " + tam);
                // Compara el código del producto en la fila actual (columna 0) con el código buscado.
                if (vproductos[ciclo, 0].CompareTo(codigo.Trim()) == 0)
                {
                    // Si los códigos coinciden, asigna la posición actual a 'enc'.
                    enc = pos;
                }
                // Incrementa el contador de posición para la siguiente fila.
                pos++;
            }
            // Devuelve 'enc', que contendrá el índice del producto si fue encontrado, o -1 si no.
            return enc;
        }

        // TIPO: Procedimiento
        // REALIZA: Gestiona la interfaz y la lógica para modificar el precio de un producto.
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz de productos que será consultada y potencialmente modificada.
        // REGRESA: Nada (void).
        public static void ModificarProducto(string[,] vproductos)
        {
            // Declara cadenas para almacenar el código y el nuevo precio que introducirá el usuario.
            string codigo, precio;
            // Declara un entero para almacenar la posición (índice) del producto encontrado.
            int posicion;
            // Llama a la función 'MostrarLista' para obtener la lista formateada de todos los productos.
            string info = MostrarLista(vproductos);
            // Muestra la lista y pide al usuario que ingrese el código a modificar.
            codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");
            // Comprueba si el usuario introdujo algún dato (si no es nulo).
            if (codigo != null)
            {
                // Imprime un mensaje de depuración.
                Console.Out.WriteLine(codigo);
                // Llama a 'ExisteProducto' para buscar la posición del código introducido.
                posicion = ExisteProducto(codigo, vproductos);
                // Comprueba si el producto fue encontrado (si la posición es mayor que -1).
                if (posicion > -1)
                {
                    // Crea un arreglo temporal con los datos del producto encontrado para mostrarlo.
                    string[] vproducto = { vproductos[posicion, 0], vproductos[posicion, 1], vproductos[posicion, 2], vproductos[posicion, 3] };
                    // Pide al usuario que introduzca el nuevo precio para el producto seleccionado.
                    precio = Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ");
                    // Comprueba si el usuario introdujo un precio.
                    if (precio != null)
                    {
                        // Evalúa si el precio introducido es un número (entero o double).
                        if (EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1))
                        {
                            // Si es un número válido, actualiza el precio en la matriz original (columna 2).
                            vproductos[posicion, 2] = precio;
                        }
                        else
                        {
                            // Si no es un número, informa al usuario.
                            Console.WriteLine("no es un valor numerico");
                        }
                    }
                    else
                    {
                        // Si el campo de precio se dejó vacío, informa al usuario.
                        Console.WriteLine(" dato nulo");
                    }
                }
                else
                {
                    // Si 'ExisteProducto' devolvió -1, informa que el código no se encontró.
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
        // REALIZA: Muestra el menú de opciones para la gestión de productos y maneja la selección del usuario.
        // PARÁMETROS:
        //   - String[,] vproductos: La matriz de productos, que se pasará a otras funciones como ModificarProducto y MostrarLista.
        // REGRESA: Nada (void).
        public static void MenuProductos(String[,] vproductos)
        {
            // Define un arreglo con las opciones que se mostrarán en el menú.
            string[] datosmenuproductos = { "1.-Modificar", "2.-Listado", "3.-Salida " };
            // Declara una cadena para almacenar la opción del usuario.
            string opcion = "0";
            // Inicia un bucle 'do-while' que se ejecutará hasta que el usuario elija salir.
            do
            {
                // Muestra el menú de productos y captura la elección del usuario.
                opcion = DesplegarMenu("Opciones de Productos ", datosmenuproductos);
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
                        // Si la opción es "1" (Modificar),
                        case "1": ModificarProducto(vproductos); break;
                        // Si la opción es "2" (Listado),
                        case "2": Console.WriteLine(MostrarLista(vproductos)); break;
                        // Si la opción es "3" (Salida),
                        case "3": Console.WriteLine("Salida del Sistema "); break;
                        // Si la opción no es ninguna de las anteriores,
                        default:
                            Console.WriteLine("No existe esta opcion ");
                            break;
                    }
                }
                // El bucle se repite mientras la opción seleccionada no sea "3".
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

        public static void MenuInventario()
        {
            string[] datosmenuinventario = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
            string opcion = "0";
            do
            {
                opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario);
                if (opcion == null)
                    Console.WriteLine("opcion incorrecta ");
                else
                    switch (opcion)
                    {
                        case "1":
                            Console.WriteLine("Listado de Inventario  ");
                            break;
                        case "2":
                            Console.WriteLine("Agregar Inventario ");
                            break;
                        case "3":
                            Console.WriteLine("Salida del Sistema ");
                            break;
                        default:
                            Console.WriteLine("No existe esta opcion ");
                            break;
                    }
            }
            while (opcion.CompareTo("3") != 0);
        }


        // TIPO: Procedimiento
        // REALIZA: Es el bucle principal de la aplicación. Muestra el menú de nivel superior y dirige al usuario
        //          a los diferentes submódulos (Productos, Punto de Venta, etc.) según su elección.
        // PARÁMETROS:
        //   - string[,] vproductos: La matriz que contiene el catálogo de productos. Se pasa a los submenús que la necesiten.
        // REGRESA: Nada (void).
        public static void MenuPrincipal(string[,] vproductos)
        {
            // Define un arreglo de cadenas con las opciones que se mostrarán en el menú principal.
            string[] datosmenuprincipal = { "1.-Productos ", "2.-Punto de Venta ", "3.-Inventario", "5.-Salida " };
            // Declara una cadena para almacenar la opción del usuario, inicializada para que el bucle comience.
            string opcion = "0";
            // Inicia un bucle 'do-while' que se ejecutará continuamente hasta que el usuario elija la opción de salida.
            do
            {
                // Llama a 'DesplegarMenu' para mostrar las opciones y capturar la respuesta del usuario.
                opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña ", datosmenuprincipal);
                // Verifica si la opción es nula (lo que indica una entrada vacía o inválida).
                if (opcion == null)
                {
                    // Si es nula, muestra un mensaje de error.
                    Console.WriteLine("Opcion incorrecta ");
                }
                // Si la opción es válida,
                else
                {
                    // evalúa la opción del usuario con una estructura 'switch'.
                    switch (opcion)
                    {
                        // Si la opción es "1" (Productos),
                        case "1":
                            // llama al submenú de productos, pasándole la matriz del catálogo.
                            MenuProductos(vproductos);
                            // Termina este caso.
                            break;
                        // Si la opción es "2" (Punto de Venta),
                        case "2":
                            // llama al submenú del punto de venta.
                            MenuPuntoVenta("000");
                            // Termina este caso.
                            break;
                        // Si la opción es "3" (Inventario),
                        case "3":
                            // llama al submenú de inventario.
                            MenuInventario();
                            // Termina este caso.
                            break;
                        // Si la opción es "5" (Salida),
                        case "5":
                            // muestra un mensaje de despedida.
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
                // El bucle se repite mientras la opción seleccionada no sea "5". 'CompareTo' devuelve 0 si son iguales.
            } while (opcion.CompareTo("5") != 0);
        }

        // TIPO: Procedimiento (Principal)
        // REALIZA: Es el punto de entrada de todo el programa. Carga los datos iniciales y arranca el menú principal.
        // PARÁMETROS:
        //   - string[] args: Un arreglo para recibir argumentos desde la línea de comandos (no se usa en este programa).
        // REGRESA: Nada (void).
        static void Main(string[] args)
        {
            // Llama a la función para cargar los productos y guarda el resultado en la variable estática 'productos'.
            productos = CargarProductos();
            // Llama al menú principal para iniciar la interacción con el usuario, pasándole la matriz de productos ya cargada.
            MenuPrincipal(productos);
        }



        // FIN DEL CLASE PRINCIPAL
    }

}
