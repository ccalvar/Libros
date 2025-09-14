

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Capitulo3 {

	public static String MostrarMenu(String[] opciones) {
	    String cadena = "";
	    int i = 0; // Índice para iterar sobre el arreglo
	// Bucle while para recorrer el arreglo de opciones
	    while (i < opciones.length) {
	        cadena += (i + 1) + ". " + opciones[i] + "\n";
	// Concatena la opción actual con su número correspondiente y un salto de línea
	        i++;
	        // Incrementa el índice para pasar a la siguiente opción
	    }
	    // Retorna la cadena del menú formateado  
	return cadena;
	}


	public static boolean EsNumeroEntero(String dato) {
		// Declara un método estático llamado EsNumeroEntero() que toma un //String dato como parámetro y devuelve un booleano.
		for (char c : dato.toCharArray()) {
		//Declara un bucle for que itera sobre los caracteres del String dato.
		if (!Character.isDigit(c)) {
		//Dentro del bucle, se comprueba si el carácter actual es un dígito. Si no lo //es, se devuelve false.
		return false;
		//Si todos los caracteres son dígitos, se devuelve true.
		         }
		     }
		     return true;
		 }

	
	public static boolean EsNumeroDouble(String dato) {
		//Declara un método estático llamado EsNumeroDouble() que toma un //String dato como parámetro y devuelve un booleano.
		boolean valido = false;
		// Declara una variable valido que se utilizará para indicar si el String dato //representa un número decimal. La variable se inicializa a false.
		for (char c : dato.toCharArray()) {
		//Declara un bucle for que itera sobre los caracteres del String dato.
		if (!Character.isDigit(c)) {
		//Dentro del bucle, se comprueba si el carácter actual es un dígito. Si no lo //es, se comprueba si es un punto.
		       if (c == '.' && !valido) {
		valido = true;
		//Si el carácter es un punto y la variable valido es false, significa que el //primer punto que se encuentra en el String es el punto decimal. En este //caso, se establece la variable valido a true para indicar que el String //representa un número decimal.
		} 
		else {
			                return false;
		              }
		// Si el carácter no es un dígito y no es un punto, o si el punto no es el primer //carácter del String, significa que el String no representa un número //decimal. En este caso, se devuelve false.
		}
		}
		return valido;
		}
		//Si todos los caracteres son dígitos o puntos, significa que el String //representa un número decimal. En este caso, se devuelve true.

	

	public static boolean EvaluarNumerico(String dato, int tipo)
	{
		//Declara un método estático llamado EvaluarNumerico que toma dos //parámetros: un String dato y un entero tipo. Devuelve un valor booleano.
		boolean valido = false;
		//Declara una variable booleana llamada valido y la inicializa a false. Esta //variable se usará para indicar si el String dato es un número válido o no.
		switch (tipo) {
		//Inicia un bloque switch para evaluar el valor del parámetro tipo.
		case 1:
		valido = EsNumeroEntero(dato);
		//Si tipo es igual a 1, se ejecuta este bloque de código. Llama al método //EsNumeroEntero(dato) para comprobar si el String dato es un número //entero. El resultado de esta llamada se asigna a la variable valido.
		break;

		case 2: 
		valido = EsNumeroDouble(dato);
		//Si tipo es igual a 2, se ejecuta este bloque de código.Llama al método //EsNumeroDouble(dato) para comprobar si el String dato es un número //decimal. El resultado de esta llamada se asigna a la variable valido.
		break;
		}
		return valido;
		}
		//Devuelve el valor de la variable valido, indicando si el String dato es un //número válido o no según el tipo especificado.

	public static String Dialogo(String texto) throws IOException 
	//El método toma un parámetro de tipo String llamado texto. El cual
	//Será la etiqueta a mostrar
	//El método devuelve un valor de tipo String.
	//El método indica que puede lanzar una excepción de tipo IOException.
	{ 
	String cadena; 
	System.out.println(texto + " : "); 
	//imprime en la consola el valor del parámetro texto seguido de dos //puntos y un espacio.
	//Esta línea muestra un mensaje al usuario para indicarle que debe //ingresar una respuesta.
	BufferedReader lectura = new BufferedReader(new InputStreamReader(System.in)); 
	//Crea un objeto de la clase BufferedReader llamado lectura.
	//Este objeto se utiliza para leer la entrada del usuario desde la consola.
	cadena = lectura.readLine(); 
	//Lee una línea de texto de la entrada del usuario y la almacena en la //variable cadena.
	//La lectura se detiene cuando el usuario presiona la tecla Enter.
	return cadena; 
	}

	public static String Leer(String texto) throws IOException
	//El método toma un parámetro de tipo String llamado texto.
	//El método devuelve un valor de tipo String.
		 { 
		String cadena = ""; 
		cadena = Dialogo(texto); 
	//Llama al método dialogo(), que lee una cadena de texto de la entrada del usuario
		if (cadena != null) 
	//Comprueba si la cadena devuelta por dialogo() es no nula.
		{ 
			cadena = cadena.trim(); 
	//Si la cadena es no nula, se elimina el espacio en blanco del principio y //del final de la cadena.
			if (cadena.isEmpty())
	//Si la cadena esta vacía , regresamos que es nula
				cadena=null;
		}
		else
			cadena = null; 
	//Si la cadena es un null , hacemos null la cadena

		return cadena; 
		}

	public static String DesplegarMenu(String Titulo1, String[] menu) throws IOException 
	//Toma dos parámetros:
	//Titulo1: Un String que representa el título del menú.
	//menu: Un arreglo de Strings que contiene las opciones del menú.
	//Devuelve un String que representa la opción elegida por el usuario.
	//Indica que puede lanzar una excepción de tipo IOException.
	{ 
	String cadena; 
	       cadena=Titulo1 + "\n" + "\n"; 
	// Inicializa la variable cadena con el título del menú y dos líneas en blanco
	cadena=cadena+MostrarMenu(menu);
	//Concatena la variable cadena con el resultado del método mostrarmenu()
	cadena = cadena +"\n Que opcion deseas "; 
	//Concatena la variable cadena con un mensaje que solicita al usuario que //elija una opción
	return  cadena = Dialogo(cadena);
	// Llama al método dialogo() para leer la opción elegida por el usuario
	//Devuelve la cadena que representa la opción elegida por el usuario
	}

	public static String Rellenarespacios(String dato, int tamano)
	//Toma dos parámetros:
	//dato: Una cadena de texto que se va a rellenar con espacios.
	//tamano: El tamaño total que debe tener la cadena resultante, contando //los espacios.
	 { 
	return String.format("%1$-" + tamano + "s", dato); 
	//utiliza el método String.format() para crear la cadena resultante:
	//%1$: Indica que se va a utilizar el primer argumento (dato).
	//-: Indica que el relleno se hará a la derecha (es decir, los espacios se //agregarán a la derecha del texto).
	//tamano: Especifica el tamaño total que debe tener la cadena resultante.
	//s: Indica que el argumento se debe formatear como una cadena de texto.
	}

	public static String Fecha() {
		//Declara un método estático llamado Fecha() que devuelve un String.
		Date fecha = new Date();
		//Crea un objeto Date que representa la fecha y hora actuales.
		SimpleDateFormat formatodia = new SimpleDateFormat("dd-MM-yyyy");
		//Crea un objeto SimpleDateFormat para formatear la fecha en el formato //deseado (dd-MM-yyyy).
		return formatodia.format(fecha);
		}
		//Formatea la fecha usando el objeto formatodia y la devuelve como un //String.

	
	
	

	public static String IdTicketSiguiente(String idticket) {
		//Declara un método estático llamado Idticketsiguiente() que 
		//toma un String idticket como parámetro y devuelve un String.
		String idticketnext = "";
		//Declara una variable idticketnext para almacenar el número de //ticket siguiente.
		int num = Integer.parseInt(idticket) + 1;
		//Convierte el idticket a un número entero, lo incrementa en 1 y lo almacena en la variable num.
		if (num < 10) 
		{ idticketnext = "00" + String.valueOf(num).trim(); } 	 
		//Si el número es menor que 10, se le agregan dos ceros a la //izquierda.
		else if ((num > 9) && (num < 100)) 
		{ idticketnext = "0" + String.valueOf(num).trim(); 
		}
		//Si el número es mayor que 9 y menor que 100, se le agrega un cero a //la izquierda.
		else {
		idticketnext = String.valueOf(num).trim(); 
		 }
		//Si el número es mayor o igual a 100, se devuelve el número tal cual.
		return idticketnext;
		//Devuelve el número de ticket siguiente formateado.
	}
	
	
}
