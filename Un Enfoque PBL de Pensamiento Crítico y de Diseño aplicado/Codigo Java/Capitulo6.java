

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Capitulo6 {
	
	static String[][] productos;

	static String ventas[][]; 
	static int posventas = -1; 
	static int tamventas = 100; 
	static String fecha; 

	
	public static String MostrarMenu(String[] opciones) 
	{             
	String cadena = ""; 
	for (String info : opciones)
	 { 
	cadena = cadena + info + "\n"; 
	         }
	return cadena; 
	}

	public static boolean EsNumeroEntero(String dato) {
		for (char c : dato.toCharArray()) {
		if (!Character.isDigit(c)) {
		return false;
		         }
		     }
		     return true;
		 }

	
	public static boolean EsNumeroDouble(String dato) {
		boolean valido = false;
		for (char c : dato.toCharArray()) {
		if (!Character.isDigit(c)) {
		       if (c == '.' && !valido) {
		valido = true;
		} 
		else {
			                return false;
		              }
		}
		}
		return valido;
		}

	

	public static boolean EvaluarNumerico(String dato, int tipo)
	{
		boolean valido = false;
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

	public static String Dialogo(String texto) throws IOException 
	{ 
	String cadena; 
	System.out.println(texto + " : "); 
	BufferedReader lectura = new BufferedReader(new InputStreamReader(System.in)); 
	cadena = lectura.readLine(); 
	return cadena; 
	}

	public static String Leer(String texto) throws IOException
		 { 
		String cadena = ""; 
		cadena = Dialogo(texto); 
		if (cadena != null) 
		{ 
			cadena = cadena.trim(); 
			if (cadena.isEmpty())
				cadena=null;
		}
		else
			cadena = null; 

		return cadena; 
		}

	public static String DesplegarMenu(String Titulo1, String[] menu) throws IOException 
	{ 
	String cadena; 
	       cadena=Titulo1 + "\n" + "\n"; 
	cadena=cadena+MostrarMenu(menu);
	cadena = cadena +"\n Que opcion deseas "; 
	return  cadena = Dialogo(cadena);
	}

	public static String RellenarEspacios(String dato, int tamano)
	 { 
	return String.format("%1$-" + tamano + "s", dato); 
	}

	public static String Fecha() {
		Date fecha = new Date();
		SimpleDateFormat formatodia = new SimpleDateFormat("dd-MM-yyyy");
		return formatodia.format(fecha);
		}


	public static String IdTicketSiguiente(String idticket) {
		String idticketnext = "";
		int num = Integer.parseInt(idticket) + 1;
		if (num < 10) 
		{ idticketnext = "00" + String.valueOf(num).trim(); } 	 
		else if ((num > 9) && (num < 100)) 
		{ idticketnext = "0" + String.valueOf(num).trim(); 
		}
		else {
		idticketnext = String.valueOf(num).trim(); 
		 }
		return idticketnext;
	}
	
	
	public static String[][] CargarProductos() {
	    String[][] producto = {
	        { "001", "Arroz 1kg", "35","10" },
	        { "002", "Azúcar 1kg", "25","10" },
	        { "003", "Harina 1kg", "28","10" },
	        { "004", "Aceite 1L", "50","10" },
	        { "005", "Leche 1L", "35","10" },
	        { "006", "Huevos 12 unidades", "45","10" },
	        { "007", "Fideos 500g", "20" ,"10"},
	        { "008", "Sal 1kg", "15","10" },
	        { "009", "Pasta de tomate 400g", "25","10" },
	        { "010", "Atún lata 170g", "35","10" }
	    };
	    return producto;
	} 		
	
public static String MostrarProducto(String[] vproducto) { 
String codigo = RellenarEspacios( vproducto[0], 5); 
String producto = RellenarEspacios( vproducto[1], 30); 
String precio = RellenarEspacios( vproducto[2], 10); 
String cantidad =RellenarEspacios( vproducto[3], 10);
String cadena = codigo.concat(producto+precio+cantidad); 
return cadena; 
}


public static String MostrarLista(String[][] vproductos) 
{ 
	String salida = "";
	for (int ciclo = 0; ciclo < 10; ciclo++) 
	{ 
	String[] vproducto = {vproductos[ciclo][0], vproductos[ciclo][1], vproductos[ciclo][2], vproductos[ciclo][3]}; 
	String cadena = MostrarProducto(vproducto); 
	salida = salida.concat(cadena + "\n"); 
	} 
	return salida; 
}

public static int ExisteProducto(String codigo, String[][] vproductos) {
int enc, pos, tam, ciclo;
enc = -1;
pos = 0;
tam = vproductos.length;
for (ciclo = 0; ciclo < tam; ciclo++) {
if (vproductos[ciclo][0].compareTo(codigo.trim()) == 0) {
enc = pos;
}
pos++;
}
return enc;
}

public static void ModificarProducto(String[][] vproductos) throws IOException {
	    String codigo, precio;
	    int posicion;
	    String info = MostrarLista(vproductos);
	    codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");
	    if (codigo != null) {
	        posicion = ExisteProducto(codigo, vproductos);
	        if (posicion > -1) {
      String[] vproducto = {vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][2],vproductos[posicion][3]};
        precio = Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ");
       if (precio != null) {
           if (EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1))
               vproductos[posicion][2] = precio;
          else
           System.out.println("no es un valor numerico");  } 
           else
	                System.out.println(" dato nulo"); } 
            else
	            System.out.println("no existe el codigo") ; } 
            else
	        System.out.println(" dato nulo");
	}
	
public  static void MenuProductos (String[][] vproductos) throws IOException 
{
String[] datosmenuproductos = { "1.-Modificar ", "2.-Listado ",  "3.-Salida " }; 
	String opcion = "0"; 
	do 
	{
	opcion = DesplegarMenu("Opciones de Productos",
	datosmenuproductos); 
	if (opcion == null) 
		System.out.println("opcion incorrecta ");
	else 
	switch (opcion) 
	{ 
	case "1": ModificarProducto(vproductos); break; 
	case "2": System.out.println(MostrarLista(vproductos)); break; 

		case "3": 
	System.out.println("Salida del Sistema "); break; 
	default: System.out.println("No existe esta opcion "); break; 
	} 
	} 
		while (opcion.compareTo("3") != 0); 
	}


	public static void MenuPuntoVenta(String idticket) throws IOException 
	{
	String opcion, membrete; 
	Boolean pago = false; 
	idticket = IdTicketSiguiente(idticket);
 	String fechadia = Fecha();
	membrete = "Fecha del Dia " + fechadia + " Ticket No " + 	idticket; 
	membrete = membrete + 
	"\n-----------------------------------------------------\n"; 
	String[] datosmenu = { "1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida " }; 
 	do 
	{ 
	opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta",datosmenu); 
	if (opcion == null)
	System.out.println("dato incorrecto introducido"); 
	else 
	switch (opcion) 
	{ 
	case "1": System.out.println("Agregar Articulo al Ticket "); break; 
	case "2": System.out.println("Eliminar Articulo del Ticket "); break; 
	case "3": System.out.println("Listado de Articulos del Ticket "); break; 
	case "4": 
		System.out.println("Pagar Ticket y salir"); 
  	                opcion = "5"; 
	                 pago = true; break;
                                 //marca pagado como true y fuerza la salida 
	case "5": 
	System.out.println("Salida del Ventas "); 
	if (!pago) 
	{ 
		System.out.println("No pago el ticket ");
	                System.out.println("eliminando tickte" + idticket); 
//Si se sale sin pagar, muestra un mensaje 
	}
	break; 
	default: 
	System.out.println("No existe esta opcion"); break; 
// Indica que la opción no existe.
	} 
	} while (opcion.compareTo("5") != 0); 
	} 

	
	/**
	 * Permite agregar stock a un producto existente en el inventario. Solicita al
	 * usuario el código del producto y la cantidad de stock a agregar. Valida que
	 * el código del producto exista y que la cantidad ingresada sea un valor
	 * numérico.
	 *
	 * @param vproductos Matriz que contiene los productos y sus detalles.
	 * @throws IOException Si ocurre un error de entrada/salida.
	 */
	public static void AgregarStock(String[][] vproductos) throws IOException {
		// Declaración de variables para almacenar el código del producto y la cantidad
		// a agregar
		String codigo, cantidad;
		int posicion;

		// Muestra la lista de productos disponibles
		String info = MostrarLista(vproductos);

		// Solicita al usuario el código del producto a modificar
		codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");

		if (codigo != null) {
			// Verifica si el producto existe en el inventario
			posicion = ExisteProducto(codigo, vproductos);
			if (posicion > -1) {
				// Obtiene los detalles del producto encontrado
				String[] vproducto = { vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][3], "" };

				// Solicita al usuario la cantidad de stock a agregar
				cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ");
				if (cantidad != null) {
					// Verifica si la cantidad ingresada es un valor numérico válido
					if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1)) {
						// Calcula la nueva cantidad de stock y la actualiza en el inventario
						String nuevacantidad = String
								.valueOf((Integer.valueOf(cantidad) + Integer.valueOf(vproducto[2])));
						vproductos[posicion][3] = nuevacantidad;
					} else {
						// Muestra un mensaje de error si la cantidad no es numérica
						System.out.println("no es un valor numerico");
					}
				} else {
					// Muestra un mensaje de error si la cantidad ingresada es nula
					System.out.println(" dato nulo");
				}
			} else {
				// Muestra un mensaje de error si el código del producto no existe
				System.out.println("no existe el codigo");
			}
		} else {
			// Muestra un mensaje de error si el código ingresado es nulo
			System.out.println(" dato nulo");
		}
	}

	/**
	 * Despliega el menú de inventario y permite al usuario interactuar con las
	 * opciones disponibles. Las opciones incluyen listar productos, agregar stock y
	 * salir del menú.
	 *
	 * @param vproductos Matriz que contiene los productos y sus detalles.
	 * @throws IOException Si ocurre un error de entrada/salida.
	 */
	public static void MenuInventario(String[][] vproductos) throws IOException {
		// Opciones disponibles en el menú de inventario
		String[] datosmenuinventario = { "1.-Listado ", "2.-Agregar ", "3.-Salida " };
		String opcion = "0"; // Variable para almacenar la opción seleccionada por el usuario

		do {
			// Muestra el menú y solicita al usuario que seleccione una opción
			opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario);

			if (opcion == null) {
				// Si la opción es nula, muestra un mensaje de error
				System.out.println("opcion incorrecta ");
			} else {
				// Evalúa la opción seleccionada por el usuario
				switch (opcion) {
				case "1":
					// Opción 1: Muestra la lista de productos
					System.out.println(MostrarLista(vproductos));
					break;
				case "2":
					// Opción 2: Permite agregar stock a un producto
					AgregarStock(vproductos);
					break;
				case "3":
					// Opción 3: Finaliza el menú de inventario
					System.out.println("Salida del Sistema ");
					break;
				default:
					// Si la opción no es válida, muestra un mensaje de error
					System.out.println("No existe esta opcion ");
					break;
				}
			}
		} while (opcion.compareTo("3") != 0); // Repite el menú hasta que el usuario seleccione la opción "3"
	}

	public  static void MenuPrincipal(String[][] vproductos) throws IOException 
	{  String[] datosmenuprincipal = { "1.-Productos ", "2.-Punto de Venta ","3.- Inventario",  "5.-Salida " }; 
	String opcion = "0"; 
	do 
	{
	opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña", 
	datosmenuprincipal); 
	if (opcion == null) 
		System.out.println("opcion incorrecta ");
	else 
	switch (opcion) 
	{ 
		case "1": MenuProductos(vproductos); break; 
		case "2": MenuPuntoVenta("000"); break; 
		case "3": MenuInventario(vproductos); break;  
			
		case "5": 
	System.out.println("Salida del Sistema "); break; 
	default: System.out.println("No existe esta opcion "); break; 
	} 
	} 
		while (opcion.compareTo("5") != 0); 
	}
	
	public static void main(String[] args) throws IOException
    {
		 productos = CargarProductos();
		 MenuPrincipal(productos);
    }

	
	
}
