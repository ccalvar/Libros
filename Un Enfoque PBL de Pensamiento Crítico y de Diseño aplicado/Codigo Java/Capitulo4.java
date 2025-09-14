

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Capitulo4 {

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

	public static String Rellenarespacios(String dato, int tamano)
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
	



	
	
	public  static void MenuProductos () throws IOException 
	{ 
	String[] datosmenuproductos = { "1.-Modificar ", "2.-Listado ",  "3.-Salida " }; 
	//Se define un arreglo de Strings llamado datosmenuproductos que contiene las //opciones del menú productos.
	String opcion = "0"; 
	do 
	{
	// Se inicia un bucle do-while que se repite mientras la variable opcion no sea igual // a "3" (salida del sistema).
	opcion = DesplegarMenu("Opciones de Productos",
	datosmenuproductos); 
	//se llama a una función llamada desplegarMenu() para mostrar el menú y obtener la opción del usuario.
	if (opcion == null) 
		System.out.println("opcion incorrecta ");
	// Si la opción es null (el usuario no eligió ninguna opción válida), se muestra un mensaje de error. 
	else 
	switch (opcion) 
	//Si la opción es válida, se ejecuta el bloque switch para manejar las opciones.
	//El bloque switch evalúa la variable opcion y ejecuta el bloque de código //correspondiente a la opción elegida.	
	{ 
		case "1": System.out.println ("Modificar Precio Producto  "); break; 
	//El usuario elige la opción "1", el código ejecutará el siguiente código que imprime //el siguiente mensaje:  Modificar Precio Producto
		case "2": System.out.println ("Listado Producto "); break; 
	//El usuario elige la opción "2", el código ejecutará el siguiente código que imprime //el siguiente mensaje:  Listado Producto 
		case "3": 
	System.out.println("Salida del Sistema "); break; 
	//El usuario elige la opción "5", el código ejecutará el siguiente código que imprime //el siguiente mensaje:  Salida del Sistema 
	default: System.out.println("No existe esta opcion "); break; 
	} 
	} 
	// se repetirá mientras opción no sea igual a 3
		while (opcion.compareTo("3") != 0); 
	}

	

	
	
	public static void MenuPuntoVenta(String idticket) throws IOException 
	{
//recibe como parámetro el número del último ticket 
	String opcion, membrete; 
	Boolean pago = false; 
	idticket = IdTicketSiguiente(idticket);
//Genera un nuevo número de ticket.
 	String fechadia = Fecha();
//Obtiene la fecha actual.
	membrete = "Fecha del Dia " + fechadia + " Ticket No " + 
	idticket; 
	membrete = membrete + 
	"\n-----------------------------------------------------\n"; 
	String[] datosmenu = { "1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida " }; 


 	do 
//Inicia un Bucle que se repite hasta que se seleccione la opción 5 (salir).
	{ 
//Crea un membrete con la fecha, número de ticket y separador.
//Crea un Arreglo con las opciones del menú.
	opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta",datosmenu); 
//Despliega el menú y obtiene la opción elegida.
	if (opcion == null)
	System.out.println("dato incorrecto introducido"); 
//Si no se seleccionó una opción válida, muestra un mensaje.
	else 
//Según la opción elegida, realiza la acción correspondiente:
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

	
	public  static void MenuInventario () throws IOException 
	{ 
	String[] datosmenuinventario = {  "1.-Listado ","2.-Agregar ",  "3.-Salida " }; 
	//Se define un arreglo de Strings llamado datosmenuproductos que contiene las 
	//opciones del menú inventario.
	String opcion = "0"; 
	do 
	{
	// Se inicia un bucle do-while que se repite mientras la variable opcion no sea igual 
	// a "3" (salida del sistema).
	opcion = DesplegarMenu("Opciones de Inventarios",datosmenuinventario); 
	//se llama a una función llamada desplegarMenu() para mostrar el menú y obtener la opción del usuario.
	if (opcion == null) 
		System.out.println("opcion incorrecta ");
	// Si la opción es null (el usuario no eligió ninguna opción válida), se muestra un mensaje de error. 
	else 
	switch (opcion) 
	//Si la opción es válida, se ejecuta el bloque switch para manejar las opciones.
	//El bloque switch evalúa la variable opcion y ejecuta el bloque de código 
	//correspondiente a la opción elegida.	
	{ 
		case "1": System.out.println ("Listado de Inventario  "); break; 
	//El usuario elige la opción "1", el código ejecutará el siguiente código que imprime 
	//el siguiente mensaje:  listado de Inventario
		case "2": System.out.println ("Agregar Inventario "); break; 
	//El usuario elige la opción "2", el código ejecutará el siguiente código 
	// imprira siguiente mensaje:  Agregar Inventario 
		case "3": 
	System.out.println("Salida del Sistema "); break; 
	//El usuario elige la opción "5", el código ejecutará el siguiente código que imprime 
	//el siguiente mensaje:  Salida del Sistema 
	default: System.out.println("No existe esta opcion "); break; 
	} 
	} 
	// se repetirá mientras opción no sea igual a 3
		while (opcion.compareTo("3") != 0); 
	}

	
	
	
	
	public  static void MenuPrincipal() throws IOException 
	{  String[] datosmenuprincipal = { "1.-Productos ", "2.-Punto de Venta ","3.- Inventario",  "5.-Salida " }; 
	//Se define un arreglo de Strings llamado datosmenuprincipal que contiene las //opciones del menú principal.
	String opcion = "0"; 
	do 
	{
	// Se inicia un bucle do-while que se repite mientras la variable opcion no sea igual // a "5" (salida del sistema).
	opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña", 
	datosmenuprincipal); 
	//se llama a una función llamada desplegarMenu() para mostrar el menú y obtener la opción del usuario.
	if (opcion == null) 
		System.out.println("opcion incorrecta ");
	// Si la opción es null (el usuario no eligió ninguna opción válida), se muestra un mensaje de error. 
	else 
	switch (opcion) 
	//Si la opción es válida, se ejecuta el bloque switch para manejar las opciones.
	//El bloque switch evalúa la variable opcion y ejecuta el bloque de código //correspondiente a la opción elegida.	
	{ 
		case "1": MenuProductos(); break; 
		case "2": MenuPuntoVenta("000"); break; 
		case "3": MenuInventario(); break;  
		case "5": 
	System.out.println("Salida del Sistema "); break; 
	//El usuario elige la opción "5", el código ejecutará el siguiente código que imprime //el siguiente mensaje:  Salida del Sistema 
	default: System.out.println("No existe esta opcion "); break; 
	} 
	} 
	// se repetirá mientras opción no sea igual a 5
		while (opcion.compareTo("5") != 0); 
	}

	
	
	public static void main(String[] args) throws IOException
    {
        MenuPrincipal();
    }

	
	
}
