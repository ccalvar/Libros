package Actividades;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ActividadCapitulo7 {

	
// se crea la matriz productos para almacenar los produtos
static	String[][] productos;
static int filas=20; // se establece el numero de filas
static int columnas=5; // se establece el numero de columnas

// se agrega los siguientes variables
static String ventas[][]; 
static int posventas = -1; 
static int tamventas = 100; 
static String fecha; 
static String idticket = "000"; // Esta será nuestra memoria para el ticket
static String Tickettexto="";

	
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


	
	/**
	 * FUNCIÓN: EvaluarNumerico
	 * Propósito: Determina si una cadena representa un número entero, decimal o es inválida
	 * @param dato - Cadena de texto a evaluar
	 * @return String - "entero", "decimal" o "invalido" según el caso
	 */
	public static String EvaluarNumerico(String dato) {
	    // Verificar si la cadena está vacía o nula usando una condición OR
	    if (dato == null || dato.trim().isEmpty()) {
	        // Retornar "invalido" si la cadena es nula o vacía después de quitar espacios
	        return "invalido";
	    }
	   
	    // Crear una nueva variable eliminando espacios en blanco al inicio y final
	    String datoLimpio = dato.trim();
	    // Variable booleana para rastrear si se encontró un punto decimal
	    boolean tienePunto = false;
	    // Variable booleana para rastrear si se encontró al menos un dígito
	    boolean tieneDigito = false;
	    
	    // Bucle for para iterar sobre cada carácter de la cadena limpia
	    for (int i = 0; i < datoLimpio.length(); i++) {
	        // Obtener el carácter en la posición actual del bucle
	        char c = datoLimpio.charAt(i);
	        
	        // Verificar si el carácter actual es un dígito usando Character.isDigit()
	        if (Character.isDigit(c)) {
	            // Marcar que se encontró al menos un dígito en la cadena
	            tieneDigito = true;
	        } 
	        // Verificar si el carácter actual es un punto decimal
	        else if (c == '.') {
	            // Si ya hay un punto O es el primer carácter O es el último carácter
	            if (tienePunto || i == 0 || i == datoLimpio.length() - 1) {
	                // Retornar inválido por punto duplicado o mal posicionado
	                return "invalido";
	            }
	            // Marcar que se encontró un punto decimal válido
	            tienePunto = true;
	        } 
	        // Verificar si el carácter actual es un signo negativo
	        else if (c == '-' ) {
	            // Si el signo no está en la primera posición
	            if (i != 0) {
	                // Retornar inválido por signo en posición incorrecta
	                return "invalido";
	            }
	        } 
	        // Cualquier otro carácter que no sea dígito, punto o signo
	        else {
	            // Retornar inválido por carácter no permitido
	            return "invalido";
	        }
	    }
	    
	    // Verificar si no se encontró ningún dígito después de procesar toda la cadena
	    if (!tieneDigito) {
	        // Retornar inválido si no hay dígitos
	        return "invalido";
	    }
	    
	    // Operador ternario: si tiene punto es decimal, sino es entero
	    return tienePunto ? "decimal" : "entero";
	}

	/**
	 * FUNCIÓN: EsEntero
	 * Propósito: Verifica si una cadena representa un número entero válido
	 * @param dato - Cadena de texto a evaluar
	 * @return boolean - true si es entero válido, false en caso contrario
	 */
	public static boolean EsEntero(String dato) {
	    // Llamar a EvaluarNumerico y comparar si el resultado es "entero"
	    return "entero".equals(EvaluarNumerico(dato));
	}

	/**
	 * FUNCIÓN: EsDecimal
	 * Propósito: Verifica si una cadena representa un número decimal válido
	 * @param dato - Cadena de texto a evaluar
	 * @return boolean - true si es decimal válido, false en caso contrario
	 */
	public static boolean EsDecimal(String dato) {
	    // Llamar a EvaluarNumerico y almacenar el resultado
	    String resultado = EvaluarNumerico(dato);
	    // Comparar si el resultado es "decimal"
	    return "decimal".equals(resultado);
	}

	/**
	 * FUNCIÓN: EsNumerico
	 * Propósito: Verifica si una cadena representa un número válido (entero o decimal)
	 * @param dato - Cadena de texto a evaluar
	 * @return boolean - true si es numérico válido, false en caso contrario
	 */
	public static boolean EsNumerico(String dato) {
	    // Llamar a EvaluarNumerico y almacenar el resultado
	    String resultado = EvaluarNumerico(dato);
	    // Verificar si el resultado es "entero" OR "decimal"
	    return "entero".equals(resultado) || "decimal".equals(resultado);
	}
	
	
	/**
	 * FUNCIÓN: Dialogo
	 * Propósito: Muestra un mensaje y lee una línea de texto desde la consola
	 * @param texto - Texto a mostrar al usuario
	 * @return String - null: error de lectura, "": no entregó nada (Enter), "texto": con información
	 * @throws IOException - Excepción de entrada/salida
	 */
	public static String Dialogo(String texto) throws IOException {
	    // Mostrar el texto del diálogo seguido de dos puntos
	    System.out.print(texto + " : ");
	    
	    try {
	        // Crear BufferedReader para leer desde la entrada estándar
	        BufferedReader lectura = new BufferedReader(new InputStreamReader(System.in));
	        
	        // Leer una línea de texto desde la consola
	        String cadena = lectura.readLine();
	        
	        // Si la lectura devuelve null, indica error de lectura
	        if (cadena == null) {
	            System.out.println("Error: No se pudo leer la entrada");
	            return null;
	        }
	        
	        // Si la cadena está vacía, usuario presionó Enter sin ingresar nada
	        if (cadena.isEmpty()) {
	            return "";
	        }
	        
	        // Devolver la cadena con información
	        return cadena;
	        
	    } catch (IOException e) {
	        // En caso de error de lectura, mostrar mensaje y devolver null
	        System.out.println("Error de lectura: " + e.getMessage());
	        return null;
	    }
	}


	/**
	 * FUNCIÓN: Leer
	 * Propósito: Solicita y valida datos numéricos del usuario propagando los estados de Dialogo
	 * @param textoDialogo - Texto a mostrar al usuario para solicitar el dato
	 * @param tipoDato - Tipo de dato esperado: "entero", "decimal" o "numerico"
	 * @return String - null: error, "": no hubo info, "dato": info válida
	 * @throws IOException - Excepción de entrada/salida
	 */
	public static String Leer(String textoDialogo, String tipoDato) throws IOException {
	    // Variable para almacenar el dato ingresado por el usuario
	    String dato;
	    // Variable para controlar si el dato es válido
	    boolean datoValido = false;
	    
	    // Bucle que se ejecuta hasta que se ingrese un dato válido o se detecte error/vacío
	    do {
	        // Solicitar el dato al usuario usando la función Dialogo
	        dato = Dialogo(textoDialogo);
	        
	        // Verificar si Dialogo retornó null (error de lectura)
	        if (dato == null) {
	            // Propagamos el null indicando error
	            return null;
	        }
	        // Verificar si Dialogo retornó vacío (usuario presionó Enter sin ingresar)
	        else if (dato.isEmpty()) {
	            // Propagamos el vacío indicando "no hubo info"
	            return "";
	        }
	        // Si no es null ni vacío, entonces hay información para validar
	        else {
	            // Limpiar el dato eliminando espacios al inicio y final
	            dato = dato.trim();
	            
	            // Evaluar el dato según el tipo solicitado usando EvaluarNumerico
	            String resultadoEvaluacion = EvaluarNumerico(dato);
	            
	            // Validar según el tipo de dato requerido
	            switch (tipoDato.toLowerCase()) {
	                case "entero":
	                    // Verificar si el dato es un entero válido
	                    if ("entero".equals(resultadoEvaluacion)) {
	                        datoValido = true;
	                    } else {
	                        // Mostrar mensaje de error específico para enteros
	                        System.out.println("Error: Debe ingresar un número entero válido. Intente nuevamente.");
	                    }
	                    break;
	                    
	                case "decimal":
	                    // Verificar si el dato es un decimal válido
	                    if ("decimal".equals(resultadoEvaluacion)) {
	                        datoValido = true;
	                    } else {
	                        // Mostrar mensaje de error específico para decimales
	                        System.out.println("Error: Debe ingresar un número decimal válido. Intente nuevamente.");
	                    }
	                    break;
	                    
	                case "numerico":
	                    // Verificar si el dato es numérico (entero o decimal)
	                    if ("entero".equals(resultadoEvaluacion) || "decimal".equals(resultadoEvaluacion)) {
	                        datoValido = true;
	                    } else {
	                        // Mostrar mensaje de error para datos numéricos
	                        System.out.println("Error: Debe ingresar un número válido (entero o decimal). Intente nuevamente.");
	                    }
	                    break;
	                    
	                default:
	                    // Mostrar error si el tipo de dato no es válido
	                    System.out.println("Error: Tipo de dato no válido. Use 'entero', 'decimal' o 'numerico'.");
	                    // Devolver null indicando error por tipo inválido
	                    return null;
	            }
	        }
	        
	    } while (!datoValido); // Repetir mientras el dato no sea válido
	    
	    // Devolver el dato validado y limpio
	    return dato;
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

	public static String RellenarEspacios(String dato, int tamano)
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
	

	/*
	 * ==========================================================================
	 /**
 * ⚙️ **Motor de Menú Genérico y Reutilizable**
 *
 * Este procedimiento actúa como un controlador central para crear y gestionar menús interactivos
 * basados en texto para una aplicación de consola. Su diseño permite definir el título, las
 * opciones y las acciones de cualquier menú de forma externa, promoviendo la reutilización de código
 * y la separación de responsabilidades.
 *
 * ---
 * ### **Comportamiento Clave:**
 * 1.  **Bucle Continuo:** El menú se muestra repetidamente hasta que el usuario selecciona una
 * opción que explícitamente termina el bucle.
 * 2.  **Ejecución de Acciones:** Asocia cada opción del menú con una acción ejecutable (un `Runnable`),
 * la cual se invoca cuando el usuario selecciona dicha opción.
 * 3.  **Salida Flexible:** Ofrece dos mecanismos para salir del menú:
 * - **Salida Estándar:** La última opción de la lista siempre funciona como salida.
 * Importante: ahora también ejecuta la acción asociada a esta opción antes de salir.
 * - **Salida Especial:** Si el parámetro `salir` es `true`, la penúltima opción también
 * provocará la salida del menú después de ejecutar su acción.
 * 4.  **Manejo de Errores:** Valida la entrada del usuario para asegurar que sea un número
 * dentro del rango de opciones válidas, mostrando mensajes de error claros en caso contrario.
 * ---
 *
 * @param titulo   El texto que se mostrará como encabezado del menú (ej. "Menú Principal").
 * @param opciones Un arreglo de Strings que contiene el texto de cada opción a mostrar.
 * @param acciones Un arreglo de `Runnable` que contiene las tareas a ejecutar. Debe haber una
 * acción por cada opción en el mismo orden.
 * @param salir    Un interruptor booleano. Si es `true`, la penúltima opción también actuará como
 * una opción de salida. Si es `false`, solo la última lo hará.
 * @throws IOException Si ocurre un error durante la lectura de la entrada del usuario desde
 * la consola (propagado desde `DesplegarMenu`).
 *
 * @author TuNombre
 * @version 2.0
 */
public static void GestionarMenus(String titulo, String[] opciones, Runnable[] acciones, boolean salir) throws IOException {
    String opcion; // Declara una variable para almacenar la entrada del usuario como texto.
    int opcionSalida = opciones.length; // Calcula el número de la opción de salida estándar (ej: 4 si hay 4 opciones).
    int opcionsalida2 = opciones.length - 1; // Calcula el número de la opción de salida especial (ej: 3 si hay 4 opciones).

    // Inicia un bucle 'do-while' que se ejecuta indefinidamente hasta que se rompa con 'break'.
    do {
        // Llama a un método externo para mostrar el menú y capturar la respuesta del usuario.
        opcion = DesplegarMenu(titulo, opciones);

        // Si la entrada es nula o inválida, notifica al usuario y reinicia el bucle.
        if (opcion == null || !EsEntero(opcion)) {
            System.out.println("Opción incorrecta, por favor ingrese solo el número.");
            continue;
        }

        // --- CONDICIÓN DE SALIDA #1: Salida Estándar ---
        // Comprueba si el usuario eligió la última opción de la lista.
        if (opcion.equals(String.valueOf(opcionSalida))) {
            // EJECUTA la acción asociada a la opción de salida (ej: un mensaje de despedida).
            acciones[Integer.parseInt(opcion) - 1].run();
            // Termina el bucle.
            break;
        }

        // Bloque 'try-catch' para manejar de forma segura la conversión de texto a número.
        try {
            // Convierte la opción del usuario (ej: "1") a un índice de arreglo (ej: 0).
            int indice = Integer.parseInt(opcion) - 1;

            // Valida que el índice esté dentro de los límites del arreglo de acciones.
            if (indice >= 0 && indice < acciones.length) {
                // ¡ACCIÓN PRINCIPAL! Ejecuta el código Runnable correspondiente a la opción elegida.
                acciones[indice].run();

                // --- CONDICIÓN DE SALIDA #2: Salida Especial ---
                // Si el interruptor 'salir' está en 'true' Y la opción elegida fue la penúltima...
                if ((salir) && (opcion.equals(String.valueOf(opcionsalida2)))) {
                    // ...también termina el bucle.
                    break;
                }

            } else {
                // Si el número está fuera de rango, informa al usuario.
                System.out.println("No existe esta opción.");
            }
        // Captura el error si el texto no puede ser convertido a número (aunque ya se validó antes, es una buena práctica mantenerlo).
        } catch (NumberFormatException e) {
            System.out.println("Por favor ingrese un número válido.");
        }

    } while (true); // La condición 'true' asegura que el bucle se repita hasta que se llame a 'break'.
}

	/*Agregado del capitulo 5
	 * 
	 * 
	 * 
	 * 
	 */
	

	public static String[][] CargarProductos() {
	    String[][] producto = {
	        // Código, Nombre, Precio, Existencias, IVA
	        { "001", "Arroz 1kg", "35", "10", "0" },
	        { "002", "Azúcar 1kg", "25", "10", "0" },
	        { "003", "Harina 1kg", "28", "10", "0" },
	        { "004", "Aceite 1L", "50", "10", "16" },
	        { "005", "Leche 1L", "35", "10", "0" },
	        { "006", "Huevos 12 unidades", "45", "10", "0" },
	        { "007", "Fideos 500g", "20", "10", "16" },
	        { "008", "Sal 1kg", "15", "10", "0" },
	        { "009", "Pasta de tomate 400g", "25", "10", "16" },
	        { "010", "Atún lata 170g", "35", "10", "16" },
	        // Productos adicionales
	        { "011", "Refresco Cola 600ml", "18", "15", "16" },
	        { "012", "Refresco Naranja 600ml", "18", "15", "16" },
	        { "013", "Sabritas Adobadas 45g", "15", "20", "16" },
	        { "014", "Sabritas Limón 45g", "15", "20", "16" },
	        { "015", "Queso Fresco 250g", "45", "8", "16" },
	        { "016", "Queso Manchego 200g", "55", "8", "16" },
	        { "017", "Jugo de Naranja 1L", "25", "12", "16" },
	        { "018", "Galletas Chocolate 150g", "22", "15", "16" },
	        { "019", "Café Instantáneo 100g", "40", "10", "16" },
	        { "020", "Chocolate en Polvo 500g", "48", "10", "16" }
	    };
	    return producto;
	}
	
	
	/**
	 * FUNCIÓN: MostrarProducto
	 * Propósito: Formatear los datos de un producto en una cadena de texto con columnas alineadas
	 *            para su visualización en formato de tabla o lista.
	 * @param vproducto - Array de Strings que contiene los datos del producto en el orden:
	 *                   [0]: Código del producto
	 *                   [1]: Nombre/descripción del producto  
	 *                   [2]: Precio del producto
	 *                   [3]: Cantidad en existencia
	 *                   [4]: Porcentaje de IVA aplicable
	 * @return String - Cadena formateada con los campos del producto alineados en columnas
	 */
	public static String MostrarProducto(String[] vproducto) { 
	    // Formatea el código del producto a un ancho fijo de 5 caracteres
	    String codigo = RellenarEspacios(vproducto[0], 5); 
	    
	    // Formatea el nombre del producto a un ancho fijo de 30 caracteres
	    String producto = RellenarEspacios(vproducto[1], 30); 
	    
	    // Formatea el precio del producto a un ancho fijo de 10 caracteres
	    String precio = RellenarEspacios(vproducto[2], 10); 
	    
	    // Formatea la cantidad en existencia a un ancho fijo de 10 caracteres
	    String cantidad = RellenarEspacios(vproducto[3], 10);
	    
	    // Formatea el porcentaje de IVA a un ancho fijo de 10 caracteres
	    String iva = RellenarEspacios(vproducto[4], 10);
	    
	    // Concatena todos los campos formateados en una sola cadena
	    String cadena = codigo.concat(producto + precio + cantidad + iva);
	    
	    // Retorna la cadena formateada con los datos del producto
	    return cadena; 
	}

	/**
	 * FUNCIÓN: MostrarLista
	 * Propósito: Generar una representación formateada en forma de tabla de una lista de productos,
	 *            incluyendo encabezados y separadores para mejorar la legibilidad.
	 * @param vproductos - Matriz bidimensional de Strings que contiene los datos de múltiples productos.
	 *                    Cada fila representa un producto con las columnas: [código, nombre, precio, stock, IVA]
	 * @return String - Cadena formateada con todos los productos en formato de tabla
	 */
	public static String MostrarLista(String[][] vproductos) { 
	    // Inicializa una cadena vacía para almacenar el resultado final 
	    String salida = "";
	    
	    // Crea y formatea la línea de título/encabezado de la tabla
	    String titulo = RellenarEspacios("Cod", 5);
	    titulo = titulo + RellenarEspacios("Nombre", 30);
	    titulo = titulo + RellenarEspacios("Precio ", 10);
	    titulo = titulo + RellenarEspacios("Stock", 10);
	    titulo = titulo + RellenarEspacios("IVA%", 10);
	    
	    // Imprime el encabezado de la tabla en la consola
	    System.out.println(titulo);
	    
	    // Imprime una línea separadora para mejorar la visualización de la tabla
	    System.out.println("-----------------------------------------------------------------------------------");

	    // Obtiene el número de productos en la lista (filas de la matriz)
	    int filas = vproductos.length;
	    
	    // Recorre cada fila de la matriz de productos 
	    for (int ciclo = 0; ciclo < filas; ciclo++) { 
	        // Extrae los datos del producto en la fila actual
	        // vproducto es un arreglo que contiene el código, nombre, precio, stock e IVA del producto 
	        String[] vproducto = {
	            vproductos[ciclo][0], // Código
	            vproductos[ciclo][1], // Nombre
	            vproductos[ciclo][2], // Precio
	            vproductos[ciclo][3], // Stock
	            vproductos[ciclo][4]  // IVA
	        }; 
	        
	        // Llama al método MostrarProducto para formatear el producto en una cadena 
	        // cadena contiene la representación en texto del producto formateado 
	        String cadena = MostrarProducto(vproducto); 
	        
	        // Añade la cadena formateada a la salida, seguida de un salto de línea 
	        salida = salida.concat(cadena + "\n"); 
	    } 
	    
	    // Devuelve la cadena resultante que contiene todos los productos formateados 
	    return salida; 
	}

	/**
	 * FUNCIÓN: ExisteProducto
	 * Propósito: Buscar un producto en la matriz de productos por su código y devolver su posición
	 * @param codigo - Código del producto a buscar
	 * @param vproductos - Matriz bidimensional que contiene la lista de productos
	 * @return int - Posición del producto en la matriz si se encuentra, -1 si no existe
	 */
	public static int ExisteProducto(String codigo, String[][] vproductos) {
	    // Declaramos las variables necesarias:
	    // - enc: Almacena la posición del producto encontrado, o -1 si no se encuentra
	    // - pos: Almacena la posición actual dentro de la matriz de productos
	    // - ciclo: Variable de control para el bucle que recorre la matriz de productos
	    int enc, pos, ciclo;
	    
	    // Inicializamos enc con -1, indicando que el producto no se ha encontrado aún
	    enc = -1;
	    
	    // Inicializamos pos con 0, que será la posición inicial en la matriz
	    pos = 0;
	    
	    // Obtenemos el número de filas (productos) en la matriz
	    int filas = vproductos.length;

	    // Iniciamos un bucle for que recorrerá la matriz de productos
	    for (ciclo = 0; ciclo < filas; ciclo++) {
	        // Comparamos el código del producto actual (vproductos[ciclo][0])
	        // con el código buscado (codigo.trim(), eliminando espacios en blanco)
	        // Si son iguales, asignamos la posición actual (pos) a enc
	        if (vproductos[ciclo][0].compareTo(codigo.trim()) == 0) {
	            enc = pos;
	            break; // Terminamos la búsqueda al encontrar el producto
	        }
	        // Incrementamos la posición actual (pos) para preparar la siguiente iteración
	        pos++;
	    }
	    
	    // Finalmente, devolvemos el valor de enc, que será la posición del
	    // producto encontrado o -1 si no se encontró
	    return enc;
	}

	/**
	 * PROCEDIMIENTO: ModificarProducto
	 * Propósito: Modificar el precio de un producto existente en la matriz de productos
	 * @param vproductos - Matriz bidimensional que contiene la lista de productos a modificar
	 * @throws IOException - Excepción de entrada/salida que puede ocurrir durante la lectura
	 */
	public static void ModificarProducto(String[][] vproductos) throws IOException {
	    // Declaramos las variables locales código, precio y posición
	    String codigo, precio;
	    int posicion;
	    
	    // Llamamos al método MostrarLista() para obtener la información de la lista de productos
	    String info = MostrarLista(vproductos);

	    // Pedimos al usuario que introduzca el código del producto a modificar
	    codigo = Leer(info + "\nIntroduce el codigo del producto a modificar", "entero");
	    
	    // Verificamos si se ingresó un código válido
	    if (codigo != null && !codigo.isEmpty()) {
	        // Buscamos la posición del producto en la matriz vproductos
	        posicion = ExisteProducto(codigo, vproductos);
	        
	        // Si el producto existe, procedemos a modificar el precio
	        if (posicion > -1) {
	            // Creamos un arreglo con la información del producto a modificar
	            String[] vproducto = {
	                vproductos[posicion][0], // Código
	                vproductos[posicion][1], // Nombre
	                vproductos[posicion][2], // Precio
	                vproductos[posicion][3], // Stock
	                vproductos[posicion][4]  // IVA
	            };
	            
	            // Pedimos al usuario que introduzca el nuevo precio
	            precio = Leer("\nIntroduce el precio de " + MostrarProducto(vproducto) + " ", "numerico");
	            
	            // Verificamos si se ingresó un precio válido NUMERICO
	            if (precio != null && !precio.isEmpty()) {
	                // Actualizamos el precio del producto en la matriz
	                vproductos[posicion][2] = precio;
	                System.out.println("Precio actualizado correctamente");
	            } else {
	                System.out.println("No se ingresó un valor numérico válido");  
	            }
	        } else {
	            System.out.println("No existe el código en la lista de productos"); 
	        }
	    } else {
	        System.out.println("No se ingresó un código válido");
	    }
	}
	
	
	
	
	
	
	
	
	/*
	 * --------------------------------------------------------------------------
	 * MenuProductos
	 * --------------------------------------------------------------------------
	 * Procedimiento
	 * Define y lanzar el menú  de gestión de productos.
	 * --------------------------------------------------------------------------
	 */
	public static void MenuProductos(String[][] vproductos) throws IOException {
	    // Define los textos que se mostrarán como opciones en el menú.
	    String[] datosmenuproductos = { "Modificar ", "Listado ", "Salida " };
	    
	    // Define las acciones (lambdas) que se ejecutarán para cada opción.
	    Runnable[] acciones = new Runnable[] {
	            () ->{ try {
					ModificarProducto(vproductos);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}},
	            () -> {
	            	System.out.println(MostrarLista(vproductos));
	            },
	            () -> System.out.println("Salida del Sistema") // Esta acción realmente no se ejecuta por la lógica de salida.
	    };
	    // Llama al gestor de menús para que construya y maneje este menú.
	    GestionarMenus("Opciones de Productos", datosmenuproductos, acciones, false);
	}

	/*
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * */
	

	
	
	
	/**
	 * Crea e inicializa el arreglo para las ventas.
	 *
	 * @return Una matriz bidimensional que representa las ventas.
	* idticket, codigo, producto, precio, cantidadvendida, iva
	 */
	
	public static String[][] CrearVenta() {
		return new String[tamventas][6];
	}

	/**
	 * Obtiene la última posición no vacía en una matriz bidimensional. Recorre la
	 * matriz para encontrar la última fila donde la primera columna no sea nula o
	 * esté vacía.
	 *
	 * @param matriz La matriz bidimensional a evaluar.
	 * @return El índice de la última posición no vacía, o -1 si todas las
	 *         posiciones están vacías.
	 */
	public static int ObtenerUltimaPosicion(String[][] matriz) {
		int ultimaPosicion = -1; // Inicializa la última posición como -1 (indicando que no se encontró una
									// posición válida)
		for (int i = 0; i < matriz.length; i++) {
			// Verifica si la primera columna de la fila actual no es nula ni está vacía
			if (matriz[i][0] != null && !matriz[i][0].isEmpty()) {
				ultimaPosicion = i; // Actualiza la última posición al índice actual
			}
		}
		return ultimaPosicion; // Devuelve la última posición válida encontrada
	}
	
	
	
	
	
	
	
	
	
	/**
	 * Obtiene el ID del último ticket registrado en el arreglo de ventas.
	 * @return El ID del último ticket, o "000" si no hay tickets registrados.
	 */
	public static String UltimoTicket(int pos, String[][] mventa) {
		String idticket = "000"; // Inicializa el ID del ticket como "000" por defecto
		if (pos > -1) { // Verifica si la posición es válida
			idticket = mventa[pos][0]; // Asigna el ID del ticket desde el arreglo de ventas
		}
		return idticket; // Devuelve el ID del último ticket
	}

	/**
	 * Crea e inicializa el arreglo para los tickets.
	 *
	 * @return Una matriz bidimensional que representa los tickets.
	 */
	public static String[][] CrearTicket() {
		return new String[20][5];
	}	
	
		

	/**
	 * Verifica si un código de producto existe en el ticket.
	 *
	 * @param mticket La matriz que representa el ticket.
	 * @param codigo  El código del producto a buscar.
	 * @return La posición del producto en el ticket si existe, o -1 si no se
	 *         encuentra.
	 */
	public static int ExisteTicketCodigo(String[][] mticket, String codigo) {
		int enc = -1; // Inicializa la variable de posición como -1 (no encontrado)
		int pos = ObtenerUltimaPosicion(mticket); // Obtiene la última posición válida en el ticket
		System.out.println(" buscando " + codigo + "  tamaño arreglo " + pos);
		for (int ciclo = 0; ciclo <= pos; ciclo++) {
			// Compara el código del producto con el código proporcionado
			if (mticket[ciclo][0].compareTo(codigo.trim()) == 0) {
				enc = ciclo; // Asigna la posición donde se encontró el producto
				return enc; // Retorna la posición encontrada
			}
		}
		return enc; // Retorna -1 si no se encuentra el producto
	}

	
	
	/**
	 * Inserta un producto en el ticket de ventas. Si el producto ya existe en el
	 * ticket, incrementa su cantidad. Si no existe, lo agrega como un nuevo
	 * producto.
	 *
	 * @param mticket   La matriz que representa el ticket de ventas.
	 * @param datos     Un arreglo que contiene los datos del producto a insertar.
	 * @param tamticket El tamaño máximo permitido para el ticket.
	 * @return `true` si el producto se insertó o actualizó correctamente, `false`
	 *         si el ticket está lleno.
	 */
	public static boolean InsertarProductoTicket(String[][] mticket, String[] datos, int tamticket) {
		boolean sucedio = true; // Indica si la operación fue exitosa
		int posticket = ObtenerUltimaPosicion(mticket); // Obtiene la última posición válida en el ticket
		int enc = ExisteTicketCodigo(mticket, datos[0]); // Verifica si el producto ya existe en el ticket

		if (posticket < tamticket) { // Verifica si hay espacio en el ticket
			if (enc > -1) { // Si el producto ya existe en el ticket
				int cantidadactual = Integer.parseInt(mticket[enc][3]); // Obtiene la cantidad actual del producto
				mticket[enc][3] = String.valueOf(cantidadactual + 1); // Incrementa la cantidad
			} else { // Si el producto no existe en el ticket
				posticket++; // Incrementa la posición del ticket
				mticket[posticket][0] = datos[0]; // Asigna el código del producto
				mticket[posticket][1] = datos[1]; // Asigna el nombre del producto
				mticket[posticket][2] = datos[2]; // Asigna el precio del producto
				mticket[posticket][3] = datos[3]; // Asigna la cantidad del producto
				mticket[posticket][4] = datos[4]; // Asigna el iva del producto
				System.out.println("Insertando: Por que No existe el producto en el ticket "+posticket);
			}
		} else {
			sucedio = false; // Indica que no se pudo insertar el producto porque el ticket está lleno
		}
		return sucedio; // Devuelve el resultado de la operación
	}
		

	
	
	public static String IvaProducto(String  precio,String iva,String cantidad) {
		double viva= Double.parseDouble(iva);
		double ivap=0;
		if (viva > 0) 
			ivap = (viva/100) * Double.parseDouble(precio)*Double.parseDouble(cantidad); // Calcula el 16% del subtotal como IVA
		return String.valueOf(ivap); // Retorna el monto del IVA calculado
	}
	
	/**
	 * Calcula el total por producto multiplicando el precio por la cantidad.
	 *
	 * @param precio   El precio unitario del producto como cadena.
	 * @param cantidad La cantidad del producto como cadena.
	 * @return El total calculado como una cadena con dos decimales.
	 */
	
	
	public static String TotalProducto(String precio, String cantidad, String iva) {
		double total = Double.parseDouble(precio) * Double.parseDouble(cantidad);
		double viva= Double.parseDouble(iva);
		if (viva!=0)
		 	total=Double.parseDouble(IvaProducto(precio,iva,cantidad))+total;
		return String.format("%.2f", total); // Formatea el total con dos decimales
	}

	
		
		/**
		 * Muestra los detalles de un producto en el ticket de ventas. Incluye el
		 * código, nombre, precio, cantidad y el total por producto.
		 *
		 * @param mticket La matriz que representa el ticket de ventas.
		 * @param pos     La posición del producto en el ticket.
		 * @return Una cadena con los detalles del producto en el ticket.
		 */
		public static String MostrarProductoTicket(String[][] mticket, int pos) {
			String codigo = RellenarEspacios(mticket[pos][0], 5); // Código del producto
			String producto = RellenarEspacios(mticket[pos][1], 30); // Nombre del producto
			String precio = RellenarEspacios(mticket[pos][2], 10); // Precio del producto
			String cantidad = RellenarEspacios(mticket[pos][3], 5); // Cantidad del producto
			String iva = RellenarEspacios(IvaProducto(precio,mticket[pos][4],cantidad),5); // iva del producto
			String totalproducto = RellenarEspacios(TotalProducto(precio, cantidad,mticket[pos][4]), 10); 
			String cadena = codigo.concat(producto + precio + cantidad +iva+totalproducto); // Concatenación de los
			return cadena; // Devuelve la cadena con los detalles del producto
		}
	

			/**
			 * Muestra el contenido del ticket de ventas. Recorre el ticket y genera una
			 * cadena con los detalles de cada producto.
			 *
			 * @param mticket La matriz que representa el ticket de ventas.
			 * @return Una cadena con el detalle de los productos en el ticket.
			 */
			public static String MostrarTicket(String[][] mticket) {
				String salida = "";
				int pos = ObtenerUltimaPosicion(mticket); // Obtiene la última posición válida en el ticket
				for (int ciclo = 0; ciclo <= pos; ciclo++)
					salida = salida.concat(MostrarProductoTicket(mticket, ciclo) + "\n"); // Agrega el detalle de cada
																							// producto
				return salida; // Devuelve la cadena con el contenido del ticket
			}


/**
 * Calcula el subtotal del ticket sumando el total de cada producto en el
 * ticket.
 *
 * @param mticket La matriz que representa el ticket de ventas.
 * @return El subtotal del ticket como un valor de tipo double.
 */
public static double SubTotalTicket(String[][] mticket) {
	double subtotal = 0;
	int pos = ObtenerUltimaPosicion(mticket); // Obtiene la última posición válida en el ticket
	for (int ciclo = 0; ciclo <= pos; ciclo++)
	{double precio =Double.parseDouble(mticket[ciclo][2]);
	 double cantidad=Double.parseDouble(mticket[ciclo][3]);	
		subtotal = subtotal + (precio*cantidad); // Suma el total
	}																									// de cada
																										// producto
	return subtotal; // Devuelve el subtotal calculado
}


public static double IvaTicket(String[][] mticket) {
	double ivatotal = 0;
	int pos = ObtenerUltimaPosicion(mticket); // Obtiene la última posición válida en el ticket
	for (int ciclo = 0; ciclo <= pos; ciclo++)
	{
		ivatotal=ivatotal+ Double.parseDouble(IvaProducto(mticket[ciclo][2],mticket[ciclo][4],mticket[ciclo][3]));
	}					
	return ivatotal; // Retorna el monto del IVA calculado
}

/**
 * Calcula el total del ticket, incluyendo el subtotal y el IVA.
 *
 * @param mticket La matriz que representa el ticket de ventas.
 * @return El total del ticket, que incluye el subtotal y el IVA.
 */
public static double TotalTicket(String[][] mticket) {
	double total = SubTotalTicket(mticket); // Obtiene el subtotal del ticket
	if (total > 0) {
		total = IvaTicket(mticket) + total; // Suma el IVA al subtotal
	}
	return total; // Devuelve el total del ticket
}

/**
 * Muestra el ticket de venta con el detalle de los productos, subtotal, IVA y
 * total. Incluye la fecha y el número de ticket en el encabezado.
 *
 * @param mticket  La matriz que representa el ticket de ventas.
 * @param idticket El ID del ticket actual.
 * @param fecha    La fecha de la venta.
 * @return Una cadena con el detalle del ticket de venta.
 */
public static String MostrarTicketVenta(String[][] mticket, String idticket, String fecha) {
	String salida = "";
	String subtotal = String.format("%.2f", SubTotalTicket(mticket)); // Calcula el subtotal del ticket
	String iva = String.format("%.2f", IvaTicket(mticket)); // Calcula el IVA del ticket
	String total = String.format("%.2f", TotalTicket(mticket)); // Calcula el total del ticket
	salida = "Fecha " + fecha + "Ticket No." + idticket; // Encabezado con la fecha y el número de ticket
	salida = salida + "\n" + MostrarTicket(mticket); // Agrega el detalle de los productos en el ticket
	salida = salida + "\n \n El total sin iva " + subtotal; // Agrega el subtotal al ticket
	salida = salida + "\n el iva total es " + iva; // Agrega el IVA al ticket
	salida = salida + "\n el total de la venta fue " + total; // Agrega el total al ticket
	return salida; // Devuelve el ticket completo como una cadena
}



/**
 * Muestra la lista de productos disponibles para la venta. Recorre el
 * inventario de productos y verifica si hay existencia disponible (cantidad
 * mayor a 0). Si el producto está disponible, lo agrega a la lista de salida.
 *
 * @param vproductos La matriz que representa el inventario de productos.
 * @return Una cadena con la lista de productos disponibles para la venta.
 */
public static String MostrarListaProductosVenta(String[][] vproductos) {
	String salida = "";
	for (int ciclo = 0; ciclo < 10; ciclo++) {
		int existencia = Integer.parseInt(vproductos[ciclo][3]); // Obtiene la cantidad disponible del producto
		if (existencia > 0) {
			String[] vproducto = vproductos[ciclo].clone(); // Clona los datos del producto
			String cadena = MostrarProducto(vproducto); // Genera la cadena con los datos del producto
			salida = salida.concat(cadena + "\n"); // Agrega el producto a la lista de salida
		}
	}
	return salida; // Devuelve la lista de productos disponibles
}


/**
 * Captura un producto para agregar al ticket de ventas. Muestra la lista de
 * productos disponibles para la venta, solicita el código del producto,
 * verifica su existencia y disponibilidad en el inventario, y lo agrega al
 * ticket si es posible. Si el producto no está disponible o el código no
 * existe, muestra mensajes de error correspondientes.
 *
 * @param mticket    La matriz que representa el ticket de ventas.
 * @param mproductos La matriz que representa el inventario de productos.
 * @param idticket   El ID del ticket actual.
 * @param tamticket  El tamaño máximo permitido para el ticket.
 * @throws IOException Si ocurre un error en la entrada/salida.
 */
public static void CapturaVentaProducto(String[][] mticket, String[][] mproductos, String idticket, int tamticket)
		throws IOException {
	String codigo, info;
	info = MostrarLista(mproductos); // Muestra la lista de productos disponibles para la venta
	codigo = Leer(info + "\nIntroduce el codigo del producto","entero"); // Solicita el código del producto
	if (codigo != null) {
		int posp = ExisteProducto(codigo.trim(), mproductos); // Verifica si el producto existe en el inventario
		if (posp > -1) {
			if (Integer.parseInt(mproductos[posp][3]) > 0) { // Verifica si hay suficiente stock del producto
				String[] producto = mproductos[posp].clone(); // Clona los datos del producto
				DescontarStock(mproductos,codigo,1);
				System.out.println(MostrarProducto(producto)); // Muestra los datos del producto seleccionado
				String[] venta = new String[5];
				venta[0] = mproductos[posp][0]; // Código del producto
				venta[1] = mproductos[posp][1]; // Nombre del producto
				venta[2] = mproductos[posp][2]; // Precio del producto
				venta[3] = "1"; // Cantidad inicial en el ticket
				venta[4] = mproductos[posp][4]; // iva del producto
				if (!InsertarProductoTicket(mticket, venta, tamticket)) // Intenta insertar el producto en el ticket
					System.out.println("el Arreglo esta lleno \n"); // Mensaje de error si el ticket está lleno
			} else {
				System.out.println("no hay productos para venta"); // Mensaje de error si no hay stock disponible
			}
		} else {
			System.out.println("el codigo no existe no se puede agregar\n"); // Mensaje de error si el código no existe
		}
	} else {
		System.out.println("dato nulo\n"); // Mensaje de error si el dato ingresado es nulo
	}
}


/**
 * Elimina un producto del ticket. Si el producto no es el último en la lista,
 * desplaza los elementos posteriores para llenar el espacio vacío. Si el
 * producto es el último, simplemente lo elimina.
 *
 * @param mticket La matriz que representa el ticket de ventas.
 * @param pos     La posición del producto en el ticket que se desea eliminar.
 */
public static void RemoverProductoTicket(String[][] mticket, int pos) {
	int tam = ObtenerUltimaPosicion(mticket); // Obtiene la última posición ocupada en el ticket
	if (tam > pos) {
		// Desplaza los elementos posteriores para llenar el espacio vacío
		for (int i = pos; i < tam + 1; i++) {
			mticket[i] = mticket[i + 1];
		}
		mticket[tam][0] = null; // Elimina el último elemento después del desplazamiento
	} else {
		mticket[pos][0] = null; // Elimina el producto si es el último en la lista
	}
}

/**
 * Elimina un producto del ticket. Si la cantidad del producto es mayor a 1,
 * simplemente decrementa la cantidad. Si la cantidad es 1, elimina el producto
 * completamente del ticket.
 *
 * @param mticket La matriz que representa el ticket de ventas.
 * @param pos     La posición del producto en el ticket que se desea eliminar.
 */
public static void EliminarProductoTicket(String[][] mticket, int pos) {
	int cantidad = Integer.parseInt(mticket[pos][3]); // Obtiene la cantidad del producto en el ticket
	if (cantidad > 1) {
		mticket[pos][3] = String.valueOf(cantidad - 1); // Decrementa la cantidad si es mayor a 1
	} else {
		RemoverProductoTicket(mticket, pos); // Elimina el producto completamente si la cantidad es 1
	}
}

/**
 * Elimina un producto del ticket y actualiza el inventario. Muestra los
 * productos en el ticket, solicita el código del producto a eliminar, y si el
 * producto existe en el ticket, lo elimina y actualiza la cantidad en el
 * inventario.
 *
 * @param mticket    La matriz que representa el ticket de ventas.
 * @param mproductos La matriz que representa el inventario de productos.
 * @throws IOException Si ocurre un error en la entrada/salida.
 */
public static void Eliminar(String[][] mticket, String[][] mproductos) throws IOException {
	String codigo, info;
	info = MostrarTicket(mticket); // Muestra los productos en el ticket
	codigo = Leer(info + "\nIntroduce el codigo del producto","entero"); // Solicita el código del producto
	if (codigo != null) {
		int pos = ExisteTicketCodigo(mticket, codigo); // Verifica si el producto existe en el ticket
		if (pos > -1) {
			int posproducto = ExisteProducto(codigo, mproductos); // Busca el producto en el inventario
			String nuevacantidad = String.valueOf((Integer.valueOf(mproductos[pos][3]) + 1)); // Incrementa la cantidad
																								// en el inventario
			mproductos[posproducto][3] = nuevacantidad; // Actualiza la cantidad en el inventario
			EliminarProductoTicket(mticket, pos); // Elimina el producto del ticket
		}
	} else {
		System.out.println("dato nulo"); // Mensaje de error si el dato es nulo
	}
}




/**
 * Agrega los productos de un ticket a la matriz de ventas. Recorre el ticket y
 * transfiere cada producto a la matriz de ventas, asignando el ID del ticket a
 * cada registro.
 *
 * @param mticket  La matriz que representa el ticket de venta.
 * @param mventa   La matriz que representa las ventas realizadas.
 * @param idticket El ID del ticket que se está procesando.
 */
public static void AgregarProductoAVenta(String[][] mticket, String[][] mventa, String idticket) {
	int posventas = ObtenerUltimaPosicion(mventa); // Obtiene la última posición ocupada en ventas
	int posticket = ObtenerUltimaPosicion(mticket); // Obtiene la última posición ocupada en el ticket
	for (int i = 0; i <= posticket; i++) {
		if (mticket[i][0] != null) { // Verifica que la fila del ticket no esté vacía
			posventas++; // Incrementa la posición en ventas
			mventa[posventas][0] = idticket; // Establece el ID del ticket
			mventa[posventas][1] = mticket[i][0]; // Código del producto
			mventa[posventas][2] = mticket[i][1]; // Nombre del producto
			mventa[posventas][3] = mticket[i][2]; // Precio del producto
			mventa[posventas][4] = mticket[i][3]; // Cantidad del producto
			mventa[posventas][5] = mticket[i][4]; // iva del producto
			
		}
	}
}


	/**
	 * Realiza el proceso de pago de un ticket, agregando los productos del ticket a
	 * las ventas. Verifica si hay suficiente espacio en el arreglo de ventas antes
	 * de realizar la operación.
	 *
	 * @param idticket El ID del ticket que se está pagando.
	 * @param mventa   La matriz que representa las ventas.
	 * @param mticket  La matriz que representa el ticket actual.
	 */
	public static void Pagar(String idticket, String[][] mventa, String[][] mticket) {
		int posventas = ObtenerUltimaPosicion(mventa); // Obtiene la última posición ocupada en las ventas
		int post = ObtenerUltimaPosicion(mticket); // Obtiene la última posición ocupada en el ticket

		// Verifica si hay espacio suficiente en el arreglo de ventas
		if ((posventas + post) < 100) {
			AgregarProductoAVenta(mticket, mventa, idticket); // Agrega los productos del ticket a las ventas
		} else {
			System.out.println("Desbordamiento de Memoria de ventas"); // Mensaje de error si no hay espacio
		}

	}

	/**
	 * Realiza la devolución de los productos de un ticket al inventario. Recorre el
	 * ticket y, por cada producto, incrementa la cantidad en el inventario.
	 *
	 * @param mticket    La matriz que representa el ticket de venta.
	 * @param mproductos La matriz que representa el inventario de productos.
	 */
	public static void DevolucionTicket(String[][] mticket, String[][] mproductos) {
		int posmticket = ObtenerUltimaPosicion(mticket); // Obtiene la última posición ocupada en el ticket

		for (int pos = 0; pos <= posmticket; pos++) {
			String codigo = mticket[pos][0]; // Obtiene el código del producto del ticket
			int posp = ExisteProducto(codigo.trim(), mproductos); // Busca el producto en el inventario
			if (posp > -1) { // Si el producto existe en el inventario
				int cant = Integer.parseInt(mticket[pos][3]) + Integer.parseInt(mproductos[posp][3]); // Suma las
																										// cantidades
				mproductos[posp][3] = String.valueOf(cant); // Actualiza la cantidad en el inventario
			}
		}
	}


	
	
	
	
	
	
	
	
 public static String DesplegarTicket(String[][] mticket,String  fechadia,String idticket)
 {
	 	String membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
	    membrete = "\n"+ membrete + "\n----------------------------------------------------------------------\n";
	    Tickettexto = MostrarTicket(mticket).trim()+"\n----------------------------------------------------------------------\n";;
    
	 return membrete.concat(Tickettexto);
 }
	
	
	/*
	 * --------------------------------------------------------------------------
	 * MenuPuntoVenta
	 * --------------------------------------------------------------------------
	 * Procedimiento  configura y gestiona el menú del punto de venta, generando un
	 * encabezado dinámico con la fecha y el número de ticket.
	 * --------------------------------------------------------------------------
	 */
	public static void MenuPuntoVenta(String[][] vventas,String vidticket,String[][] vproductos) throws IOException {
	    // El parámetro 'idticket' recibe el número del último ticket.
	    String opcion, membrete;
	    int tamticket = 50; // Tamaño máximo del ticket,
		String[][] vticket = new String[tamticket][5]; // Matriz para almacenar los productos del ticket
		String antidtiket=vidticket;

		// Genera el ID del siguiente ticket y obtiene la fecha actual
		idticket = IdTicketSiguiente(vidticket);

		// Obtiene la fecha actual llamando a una función externa.
	    String fechadia = Fecha();
	    String titulo=" Menu de Punto de Venta"+" Fecha del Dia " + fechadia + " Ticket No " + idticket;
	    // Crea un encabezado personalizado para el menú.
	    
	    
	    // Define los textos para las opciones del menú.
	    String[] datosmenupuntoventa = { "Agregar  ", "Eliminar ", "Listado ", "Pagar ", "Salida " };
	    
	    // Define las acciones para cada opción.
	    Runnable[] acciones = new Runnable[] {
	            () -> { try {
					CapturaVentaProducto(vticket, vproductos, idticket, tamticket);
					System.out.println(DesplegarTicket(vticket,fechadia,idticket));
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} },
	            () ->{	try {
					Eliminar(vticket, productos);
					System.out.println(DesplegarTicket(vticket,fechadia,idticket));
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}},
	            () -> {if (ObtenerUltimaPosicion(vticket) > -1) {
					System.out.println(MostrarTicket(vticket));
				}},
	            () -> { System.out.println("Procesando el pago del ticket "+ "\n"+DesplegarTicket(vticket,fechadia,idticket));
	             
	            		System.out.println(MostrarTicketVenta(vticket, idticket, fecha).trim());
							Pagar(idticket, vventas, vticket);
							
				},
	            () -> {DevolucionTicket(vticket, vproductos); // Si no se pagó, devuelve los productos al inventario
	            System.out.println("eliminando tickte " + idticket);
	            idticket = antidtiket;}
	            };

	    // Llama al gestor de menús, pasando un arreglo booleano para indicar que la opción "Pagar" también debe cerrar el menú.
	    GestionarMenus(titulo , datosmenupuntoventa, acciones, true );
	

	}
	
	

	/**
	 * Muestra los detalles de una venta específica. Incluye el ID del ticket, el
	 * código del producto, el nombre del producto, el precio y la cantidad.
	 *
	 * @param venta Un arreglo que contiene los datos de la venta: [0] - ID del
	 *              ticket [1] - Código del producto [2] - Nombre del producto [3] -
	 *              Precio del producto [4] - Cantidad del producto
	 * @return Una cadena con los detalles de la venta formateados.
	 */
	public static String MostrarVenta(String[] venta) {
		String idticket = RellenarEspacios(venta[0], 6); // ID del ticket
		String codigo = RellenarEspacios(venta[1], 5); // Código del producto
		String producto = RellenarEspacios(venta[2], 30); // Nombre del producto
		String precio = RellenarEspacios(venta[3], 10); // Precio del producto
		String cantidad = RellenarEspacios(venta[4], 10); // Cantidad del producto
		String iva = RellenarEspacios(venta[5], 10); // Cantidad del producto
		
		String cadena = idticket.concat(codigo + producto + precio + cantidad+iva); // Concatenación de los detalles
		return cadena; // Devuelve la cadena con los detalles de la venta
	}

		/**
		 * Muestra la lista de todas las ventas realizadas. Recorre la matriz de ventas
		 * y genera una cadena con los detalles de cada venta.
		 *
		 * @param ventas La matriz que representa las ventas realizadas.
		 * @return Una cadena con el detalle de todas las ventas.
		 */
		public static String MostrarListaVentas(String[][] ventas) {
			int posventas = ObtenerUltimaPosicion(ventas); // Obtiene la última posición válida en la matriz de ventas
			String salida = "";
			for (int ciclo = 0; ciclo <= posventas; ciclo++) {
				// Crea un arreglo con los datos de una venta específica
				String[] venta = { ventas[ciclo][0], ventas[ciclo][1], ventas[ciclo][2], ventas[ciclo][3],
						ventas[ciclo][4],ventas[ciclo][5] };
				String cadena = MostrarVenta(venta); // Genera una cadena con los detalles de la venta
				salida = salida.concat(cadena + "\n"); // Agrega la cadena al resultado final
			}
			return salida; // Devuelve la cadena con el detalle de todas las ventas
		}


	
	
	
	
	
	
	
	
	
	/*
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 */
	
	
	
	
	
	/**
	 * FUNCIÓN: DescontarStock
	 * Propósito: Descontar una cantidad específica del stock de un producto identificado por su código
	 * @param vproductos - Matriz bidimensional que contiene la lista de productos
	 * @param codigo - Código del producto al que se desea descontar stock
	 * @param cantidad - Cantidad a descontar del stock del producto (ya validada como numérica)
	 * @return int - Código de resultado de la operación:
	 *             -2: El producto no existe
	 *             -1: La cantidad a descontar es mayor al stock disponible
	 *              0: El producto tiene 0 en stock (no se puede descontar)
	 *              1: Se logró actualizar el stock correctamente
	 */
	/**
	 * Descuenta una cantidad del stock de un producto específico.
	 * @param vproductos Matriz con los datos de los productos [fila][columna].
	 * @param codigo El ID del producto a buscar.
	 * @param cantidad La cantidad a descontar.
	 * @return Un código de estado: 1 (éxito), 0 (sin stock), -1 (stock insuficiente), -2 (producto no existe).
	 */
	public static int DescontarStock(String[][] vproductos, String codigo, int cantidad) {
	    // Inicializa la variable de acción con -2 (estado por defecto: no encontrado).
	    int accion = -2;

	    // Llama a una función para buscar la fila donde está el producto.
	    int posicion = ExisteProducto(codigo, vproductos);

	    // Si la posición es -1, el producto no fue encontrado.
	    if (posicion == -1) {
	        accion = -2; // Asigna el código de "producto no existe".
	    } else { // Si el producto SÍ existe...
	        // Obtiene el stock actual (columna 3) y lo convierte a número.
	        int stockActual = Integer.parseInt(vproductos[posicion][3]);

	        // Verifica si el stock es exactamente 0.
	        if (stockActual == 0) {
	            accion = 0; // Asigna el código de "sin stock".
	        } else {
	            // Si hay stock, verifica si la cantidad solicitada es mayor a la existente.
	            if (cantidad > stockActual) {
	                accion = -1; // Asigna el código de "stock insuficiente".
	            } else {
	                // Si todo es correcto, procede a descontar.
	                int nuevoStock = stockActual - cantidad;
	                // Actualiza el valor en la matriz (convirtiéndolo de nuevo a String).
	                vproductos[posicion][3] = String.valueOf(nuevoStock);
	                accion = 1; // Asigna el código de "éxito".
	            }
	        }
	    }

	    // Devuelve el código de estado final de la operación.
	    return accion;
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
		codigo = Leer(info + "\nIntroduce el codigo del producto a modificar","entero");

		if (codigo != null) {
			// Verifica si el producto existe en el inventario
			posicion = ExisteProducto(codigo, vproductos);
			if (posicion > -1) {
				// Obtiene los detalles del producto encontrado
				String[] vproducto = { vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][3], "" };

				// Solicita al usuario la cantidad de stock a agregar
				cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ","entero");
				if (cantidad != null) {
					// Verifica si la cantidad ingresada es un valor numérico válido
						String nuevacantidad = String.valueOf((Integer.valueOf(cantidad) + Integer.valueOf(vproducto[2])));
						vproductos[posicion][3] = nuevacantidad;
					}
				else 
					// Muestra un mensaje de error si la cantidad ingresada es nula
					System.out.println(" dato nulo o incorrecto " );
				
			} else 
				// Muestra un mensaje de error si el código del producto no existe
				System.out.println("no existe el codigo");
			} else {
			// Muestra un mensaje de error si el código ingresado es nulo
			System.out.println(" dato nulo");
		}
	}


	
	
	/*
	 * --------------------------------------------------------------------------
	 *MenuInventario
	 * --------------------------------------------------------------------------
	 *Procedimiento  define y lanzar el menú de gestión de inventario.
	 * --------------------------------------------------------------------------
	 */
	public static void MenuInventario(String[][] vproductos) throws IOException {
	    // Define los textos de las opciones.
	    String[] datosmenuinventario = { "Listado ", "Agregar ", "Salida " };
	    // Define las acciones correspondientes.
	    Runnable[] acciones = new Runnable[] {
	            () ->System.out.println(MostrarLista(vproductos)),
	            () -> {
					try {
						AgregarStock(vproductos);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				},
	            () -> System.out.println("Salida")
	    };

	    // Llama al gestor genérico para mostrar el menú.
	    GestionarMenus("Opciones de Inventarios", datosmenuinventario, acciones, false);
	}

	/*
	 * --------------------------------------------------------------------------
	 * MÉTODO: MenuPrincipal
	 * --------------------------------------------------------------------------
	 * TIPO: Procedimiento ('void').
	 * * ¿PARA QUÉ NOS SIRVE?
	 * Es el punto de entrada principal del sistema de menús. Desde aquí se
	 * puede navegar a los otros submenús (Productos, Venta, etc.).
	 * --------------------------------------------------------------------------
	 */
	public static void MenuPrincipal(String[][] vproductos,String[][] vventas) throws IOException {
	    // Define los textos para las opciones del menú principal.
	    String[] datosmenuprincipal = { "Productos ", "Punto de Venta ", "Inventario", "Listado de Ventas", "Salida " };
	    
	    // Define las acciones. La clave aquí es que las acciones llaman a otros métodos de menú.
	    Runnable[] acciones = new Runnable[] {
	            () -> {
	                try {
	                    MenuProductos(vproductos); // Llama al procedimiento del menú de productos.
	                } catch (IOException e) {
	                    e.printStackTrace();
	                }
	            },
	            () -> {
	                try {
	                    MenuPuntoVenta(vventas,idticket,vproductos); // Llama al menú de venta con un ticket inicial.
	                } catch (IOException e) {
	                    e.printStackTrace();
	                }
	            },
	            () -> {
	                try {
	                    MenuInventario(vproductos); // Llama al procedimiento del menú de inventario.
	                } catch (IOException e) {
	                    e.printStackTrace();
	                }
	            },
	            () -> System.out.println(MostrarListaVentas(vventas)),
	            () -> System.out.println("Salida del Sistema")
	    };
	    
	    // Llama al gestor para mostrar el menú principal.
	    GestionarMenus("Menu de Punto de Tienda de Abarrotes la Pequeña", datosmenuprincipal, acciones, false);
	}

		
	
	
	public static void main(String[] args) throws IOException
    {
        productos = CargarProductos();
        ventas=CrearVenta(); 
		MenuPrincipal(productos,ventas);
        
    }
}
