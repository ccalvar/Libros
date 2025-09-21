package Actividades;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ActividadCapitulo6 {

	
// se crea la matriz productos para almacenar los produtos
static	String[][] productos;
static int filas=20; // se establece el numero de filas
static int columnas=5; // se establece el numero de columnas

// se agrega los siguientes variables
static String ventas[][]; 
static int posventas = -1; 
static int tamventas = 100; 
static String fecha; 


	
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
	 * --------------------------------------------------------------------------
	 * MenuPuntoVenta
	 * --------------------------------------------------------------------------
	 * Procedimiento  configura y gestiona el menú del punto de venta, generando un
	 * encabezado dinámico con la fecha y el número de ticket.
	 * --------------------------------------------------------------------------
	 */
	public static void MenuPuntoVenta(String idticket) throws IOException {
	    // El parámetro 'idticket' recibe el número del último ticket.
	    String opcion, membrete;
	    Boolean pago = false;
	    
	    // Genera un nuevo número de ticket llamando a una función externa.
	    idticket = IdTicketSiguiente(idticket);
	    // Obtiene la fecha actual llamando a una función externa.
	    String fechadia = Fecha();
	    // Crea un encabezado personalizado para el menú.
	    membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket;
	    membrete = membrete + "\n-----------------------------------------------------\n";
	    
	    // Define los textos para las opciones del menú.
	    String[] datosmenupuntoventa = { "Agregar  ", "Eliminar ", "Listado ", "Pagar ", "Salida " };

	    // Define las acciones para cada opción.
	    Runnable[] acciones = new Runnable[] {
	            () -> System.out.println("Agregar Articulo al Ticket "),
	            () -> System.out.println("Eliminar Articulo del Ticket "),
	            () -> System.out.println("Listado de Articulos del Ticket "),
	            () -> System.out.println("Pagar Ticket y salir"),
	            () -> System.out.println("Salida")
	    };

	    // Llama al gestor de menús, pasando un arreglo booleano para indicar que la opción "Pagar" también debe cerrar el menú.
	    GestionarMenus(membrete + "\n Menu de Punto de Venta", datosmenupuntoventa, acciones, true );
	}

	
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
	public static void MenuPrincipal(String[][] vproductos) throws IOException {
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
	                    MenuPuntoVenta("000"); // Llama al menú de venta con un ticket inicial.
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
	            () -> System.out.println("Listado de Ventas del Dia"),
	            () -> System.out.println("Salida del Sistema")
	    };
	    
	    // Llama al gestor para mostrar el menú principal.
	    GestionarMenus("Menu de Punto de Tienda de Abarrotes la Pequeña", datosmenuprincipal, acciones, false);
	}

		
	
	
	public static void main(String[] args) throws IOException
    {
        productos = CargarProductos();
		MenuPrincipal(productos);
        
    }
}
