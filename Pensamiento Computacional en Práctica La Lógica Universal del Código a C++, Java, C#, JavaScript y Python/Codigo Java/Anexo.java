

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;


public class Anexo {
	
	static String[][] productos;

	static String ventas[][]; 
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
	
// agregagrlo a todos los capitulos anteriores
//*************************************************
	
	public static int ObtenerUltimaPosicion(String[][] matriz) {
	    int ultimaPosicion = -1;
	    for (int i = 0; i < matriz.length; i++) {
	        if (matriz[i][0] != null && !matriz[i][0].isEmpty()) {
	            ultimaPosicion = i;
	        }
	    }
	    return ultimaPosicion;
	}
	//*************************************************

	
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


	public static String[][]CrearVenta() { 
	return  new String[tamventas][5]; 
	}

	public static String UltimoTicket(int pos,String[][] mventa) { 
		String idticket = "000"; 
		if (pos > -1) { 
		idticket = mventa[pos][0]; 
		} 
		return idticket; 
		} 

	
	public static String[][]CrearTicket() { 
	
	return new String[20][4]; 
	}

	
	
		

	public static int ExisteTicketCodigo(String[][] mticket,String codigo ) 
	{ 
		int enc = -1; 
		int pos=ObtenerUltimaPosicion(mticket);
		System.out.println(" buscando "+codigo +"  tamaño arreglo "+pos);
		for (int ciclo = 0; ciclo <= pos;ciclo++) { 
			if (mticket[ciclo][0].compareTo(codigo.trim()) == 0)
			{		enc = ciclo; 
					return enc;
			}
		}
		return enc;
	}

	
	
		public static boolean InsertarProductoTicket(String[][] mticket,String[] datos,int tamticket)
		{
		boolean sucedio=true;
		int posticket= ObtenerUltimaPosicion(mticket);
		int 	enc=ExisteTicketCodigo(mticket,datos[0]);
		if (posticket < tamticket) {
		if (enc >-1)
		{  
			int cantidadactual =Integer.parseInt(mticket[enc][3]);
			mticket[enc][3]=String.valueOf(cantidadactual+1);
		}
		else {
				posticket++;
			    mticket[posticket][0]=datos[0];
				mticket[posticket][1]=datos[1];
				mticket[posticket][2]=datos[2];
				mticket[posticket][3]=datos[3];
				
				System.out.println("Insertarndo No existe el producto en el ticket ");
			}	
		}
		else
			sucedio=false;
		return sucedio;
		}
		
	
		public static String TotalProducto(String precio,String cantidad)
		{
			double total = Double.parseDouble(precio)*Double.parseDouble(cantidad);
			return String.format("%.2f", total);

		}

	
		
		public static String MostrarProductoTicket(String[][] mticket,int pos) { 
			String codigo = RellenarEspacios(mticket[pos][0], 5); 
			String producto = RellenarEspacios(mticket[pos][1], 30); 
			String precio = RellenarEspacios(mticket[pos][2], 10);
			String cantidad = RellenarEspacios(mticket[pos][3], 5);
			String totalproducto = RellenarEspacios( TotalProducto(mticket[pos][2],mticket[pos][3]), 10);
			String cadena = codigo.concat(producto+precio+cantidad+totalproducto);; 
			return cadena; 
			}

	

public static String MostrarTicket(String[][] mticket) { 
String salida = ""; 
int pos= ObtenerUltimaPosicion(mticket);
for (int ciclo = 0; ciclo <= pos; ciclo++)    
salida = salida.concat(MostrarProductoTicket(mticket,ciclo)+"\n");     
return salida; 
} 



public static double SubTotalTicket(String[][] mticket) { 
double subtotal = 0; 
int pos= ObtenerUltimaPosicion(mticket);
for (int ciclo = 0; ciclo <= pos; ciclo++)  
subtotal = subtotal + Double.parseDouble(TotalProducto(mticket[ciclo][2],mticket[ciclo][3])); 
return subtotal; 
}

public static double IvaTicket(String[][] mticket) {
double subtotal = SubTotalTicket(mticket);
if (subtotal>0)
subtotal = 0.16 * subtotal;
else
	subtotal=-1;
return subtotal; 
} 

public static double TotalTicket(String[][] mticket) { 
double total = SubTotalTicket(mticket);
if (total>0)
total = IvaTicket(mticket) + total;  
return total; 
} 


public static String MostrarTicketVenta(String[][] mticket,String idticket,String fecha) { 
String salida = "";
String subtotal=String.format("%.2f",SubTotalTicket(mticket));
String iva=String.format("%.2f",IvaTicket(mticket));
String total=String.format("%.2f",TotalTicket(mticket));
salida = "Fecha " + fecha + "Ticket No." + idticket; 
salida = salida + "\n" + MostrarTicket(mticket); 
salida = salida + "\n \n El total sin iva " + subtotal; 
salida = salida + "\n el iva total es " + iva; 
salida = salida + "\n el total de la venta fue " +total ; 
return salida; 
}



public static String MostrarListaProductosVenta(String[][] vproductos) 
{ 
	String salida = "";
	for (int ciclo = 0; ciclo < 10; ciclo++) 
	{ 
		int existencia = Integer.parseInt(vproductos[ciclo][3]);
		if ( existencia > 0)	
		{	String[] vproducto = vproductos[ciclo].clone();
			String cadena = MostrarProducto(vproducto); 
			salida = salida.concat(cadena + "\n"); 
		}
	} 
	return salida; 
}



public static void CapturaVentaProducto(String[][] mticket,String[][] mproductos,String idticket,int tamticket) throws IOException { 
String codigo, info; 
info = MostrarListaProductosVenta(mproductos); 
codigo = Leer(info + "\nIntroduce el codigo del producto");
if (codigo!=null)
{int posp = ExisteProducto(codigo.trim(),mproductos); 
if (posp > -1) { 
	
if (Integer.parseInt(mproductos[posp][3])>0 )
{
	String[] producto = mproductos[posp].clone();
	int cant= Integer.parseInt(mproductos[posp][3]);
	cant=cant-1;
	mproductos[posp][3]= String.valueOf(cant);
	System.out.println(MostrarProducto(producto)); 
	String[] venta = new String[4];
	venta[0] = mproductos[posp][0]; 
	venta[1] = mproductos[posp][1]; 
	venta[2] = mproductos[posp][2]; 
	venta[3] = "1";
	if (!InsertarProductoTicket(mticket,venta,tamticket) )
		System.out.println("el Arreglo esta lleno \n" );
} 
else 
	System.out.println("no hay productos para venta");

} else { 
 		System.out.println("el codigo no existe no se puede agregar\n "); 
}
} else System.out.println("dato nulo\n "); 

}

public static void RemoverProductoTicket(String[][] mticket, int pos) {
	int tam = ObtenerUltimaPosicion(mticket);
	if (tam>pos)
	{for (int i = pos; i < tam+1 ; i++) 
		mticket[i] = mticket[i + 1];
	 mticket[tam][0]=null;
	}
	else 
		mticket[pos][0]=null;
	
}


public static void  EliminarProductoTicket(String[][] mticket,int pos)
{	int cantidad = Integer.parseInt(mticket[pos][3]);
	if (cantidad>1)
		mticket[pos][3]=String.valueOf(cantidad-1);
	else
		RemoverProductoTicket(mticket,pos);
}

public static void Eliminar(String[][] mticket,String[][] mproductos) throws IOException { 
String codigo, info; 
info = MostrarTicket(mticket); 
codigo = Leer(info + "\nIntroduce el codigo del producto"); 
if (codigo!=null)
{
	int pos = ExisteTicketCodigo(mticket,codigo); 
	if (pos > -1)  
	{
		int		   posproducto = ExisteProducto(codigo, mproductos);
		   String nuevacantidad=  String.valueOf((Integer.valueOf(mproductos[pos][3])+1)); 
    	   mproductos[posproducto][3] =  nuevacantidad;
	EliminarProductoTicket(mticket,pos);
	}
}
else
	System.out.println("dato nulo");
} 




// este hay que agregar a pseint
public static void AgregarProductoAVenta(String[][] mticket, String[][] mventa, String idticket) {
    int posventas = ObtenerUltimaPosicion(mventa);
    int posticket = ObtenerUltimaPosicion(mticket);
	for (int i = 0; i <= posticket; i++) {
        if (mticket[i][0] != null) { // Verificar que la fila no esté vacía
           	posventas++;
        	mventa[posventas][0] = idticket; // Establecer el ID del ticket
            mventa[posventas][1] = mticket[i][0]; // Código del producto
            mventa[posventas][2] = mticket[i][1]; // Nombre del producto
            mventa[posventas][3] = mticket[i][2]; // Precio del producto
            mventa[posventas][4] = mticket[i][3]; // Cantidad del producto
            
        }
    }
   }



public static void Pagar(String idticket,String[][] mventa,String[][] mticket) 
{
	int posventas = ObtenerUltimaPosicion(mventa);
    int post = ObtenerUltimaPosicion(mticket);
if ((posventas+post)<100)
{
AgregarProductoAVenta(mticket,mventa,idticket);
	
}
else
System.out.println("Desbordamiento de Memeoria de ventas");	
	
}


// se agrego esto
public static void DevolucionTicket(String[][] mticket,String[][] mproductos)
{
int posmticket= ObtenerUltimaPosicion(mticket);
for(int pos=0;pos<=posmticket;pos++)
{		String codigo= mticket[pos][0];
		int posp = ExisteProducto(codigo.trim(),mproductos); 
		if (posp > -1)
		{
			int cant= Integer.parseInt(mticket[pos][3])+ Integer.parseInt(mproductos[posp][3]);
			mproductos[posp][3]=String.valueOf(cant);
		}
}
}




	public static void MenuPuntoVenta(String[][] ventas,String idticket,String[][] productos,String narchivo) throws IOException 
	{ 
	String opcion, membrete; 
	Boolean pago = false; 
	int tamticket=50;
	String[][] Vticket = new String[tamticket][4];
  	idticket = IdTicketSiguiente(idticket); 
	String fechadia = Fecha(); 
	opcion="";
	do 
	{ 		membrete = "Fecha del Dia " + fechadia + " Ticket No " + 	idticket; 
 		membrete = membrete + 
 				"\n-----------------------------------------------------\n"; 
		String Tickettexto = MostrarTicket(Vticket).trim();
		if (!Tickettexto.trim().isEmpty())
		{
			membrete = membrete + "\n" + Tickettexto + "\n"; 
		}	
			String[] datosmenu = { "1.-Agregar  ", "2.-Eliminar ", "3.-Listado ", "4.-Pagar ", "5.-Salida " }; 
			opcion = DesplegarMenu(membrete + "\n Menu de Punto de Venta",datosmenu); 
			if (opcion == null) 
				System.out.println("dato incorrecto introducido"); 
			else 
				switch (opcion) 
				{ 
				case "1": CapturaVentaProducto(Vticket,productos,idticket, tamticket); break; 
				case "2":  Eliminar(Vticket,productos); break;
	       case "3": if (ObtenerUltimaPosicion(Vticket)>-1)
	    	   		System.out.println(MostrarTicket(Vticket));
	       			break; 
	
case "4": 
    // Muestra el ticket de venta con los detalles del subtotal, IVA y total
    System.out.println(MostrarTicketVenta(Vticket, idticket, fecha).trim());

    // Realiza el proceso de pago y agrega los productos del ticket a las ventas
    Pagar(idticket, ventas, Vticket);

    // Verifica si el ticket tiene productos y guarda los datos en archivos CSV
    if (ObtenerUltimaPosicion(Vticket) > -1) {
        System.out.println("tamaño de venta" + ObtenerUltimaPosicion(ventas) + " " + ObtenerUltimaPosicion(Vticket));

        // Guarda los datos del ticket en un archivo CSV
        GuardarDatosCsvVentaTicket(Vticket, narchivo, ObtenerUltimaPosicion(Vticket), idticket);
     // Guarda los datos de las ventas en un archivo CSV
        String cadena = generarCSVFilaVenta(fechadia, idticket,  String.format("%.2f", SubTotalTicket(Vticket)),String.format("%.2f", IvaTicket(Vticket)), String.format("%.2f", TotalTicket(Vticket)) );
        // Guarda la línea de resumen en el archivo CSV principal de ventas.
        GuardarDatosCsvVentas("ventas.csv", cadena);
        
 					}
				
					pago = true;
					opcion = "5";
				break;
				case "5": 
					System.out.println("Salida del Ventas "); 
					if (!pago) 
					{ 
						System.out.println("No pago el ticket ");
						DevolucionTicket(Vticket,productos);
						System.out.println("eliminando tickte" +idticket);
					}
					break; 
				default: 
						System.out.println("No existe esta opcion"); break; 
				} // FIN DEL SWITCH 
	} //fin ciclo
	 while (opcion.compareTo("5") != 0);
	
	}
 	

	
	public static String MostrarVenta(String[] venta) { 
		String idticket= RellenarEspacios( venta[0], 6);
		String codigo = RellenarEspacios( venta[1], 5); 
		String producto = RellenarEspacios( venta[2], 30); 
		String precio = RellenarEspacios( venta[3], 10); 
		String cantidad = RellenarEspacios( venta[4], 10); 
		String cadena = idticket.concat(codigo+producto+precio+cantidad);
		return cadena; 
		}
	
	public static String MostrarListaVentas(String[][] ventas) 
	{ 
	int posventas =	ObtenerUltimaPosicion(ventas);
	String salida = "";	for (int ciclo = 0; ciclo <= posventas; ciclo++) 
	{ 
	String[] venta = {ventas[ciclo][0], ventas[ciclo][1], ventas[ciclo][2], ventas[ciclo][3],ventas[ciclo][4]}; 
	String cadena = MostrarVenta(venta); 
	salida = salida.concat(cadena + "\n"); 
	} 
	return salida; 
	}

	
	public static void AgregarStock(String[][] vproductos) throws IOException {
	    String codigo, cantidad;
	    int posicion;
	    String info = MostrarLista(vproductos);
	    codigo = Leer(info + "\nIntroduce el codigo del producto a modificar");
	    if (codigo != null) {
	        posicion = ExisteProducto(codigo, vproductos);
	        if (posicion > -1) {
      String[] vproducto = {vproductos[posicion][0], vproductos[posicion][1],vproductos[posicion][3],""};
        cantidad = Leer("\nIntroduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ");
       if (cantidad != null) {
           if (EvaluarNumerico(cantidad, 2) || EvaluarNumerico(cantidad, 1))
           {	       
        	   String nuevacantidad=  String.valueOf((Integer.valueOf(cantidad)+Integer.valueOf(vproducto[2]))); 
        	   vproductos[posicion][3] =  nuevacantidad;
           }
        	   else
           System.out.println("no es un valor numerico");  } 
           else
	                System.out.println(" dato nulo"); } 
            else
	            System.out.println("no existe el codigo") ; } 
            else
	        System.out.println(" dato nulo");
	}

	
	public  static void MenuInventario (String[][] vproductos ) throws IOException 
	{ 
	String[] datosmenuinventario = {  "1.-Listado ","2.-Agregar ",  "3.-Salida " }; 
	String opcion = "0"; 
	do 
	{
	opcion = DesplegarMenu("Opciones de Inventarios",datosmenuinventario); 
	if (opcion == null) 
		System.out.println("opcion incorrecta ");
	else 
	switch (opcion) 
	{ 
		case "1": System.out.println(MostrarLista(vproductos)); break; 
		case "2": AgregarStock(vproductos); break; 
		case "3": System.out.println("Salida del Sistema "); break; 
	default: System.out.println("No existe esta opcion "); break; 
	} 
	} 
		while (opcion.compareTo("3") != 0); 
	}

	
	
	public  static void MenuPrincipal(String[][] vproductos,String[][] vventas) throws IOException 
	{  String[] datosmenuprincipal = { "1.-Productos ", "2.-Punto de Venta ","3.- Inventario","4.-Ventas", "5.-Salida " }; 
	String opcion = "0"; 
	String idticket=null;
	//primer agregado CAMBIO REALIZADO POR EL ANEXO

// Genera el nombre del archivo CSV basado en la fecha actual
	String narchivo = Fecha() + ".csv";

// Verifica si el archivo existe
	if (ExisteArchivo(narchivo)) {
		// Si el archivo existe, lee el contenido y obtiene el último ID de ticket
		System.out.println("Leyendo archivo " + narchivo);
		idticket = LeerDatosCSV(narchivo);
	}

	do {
		// Si el ID del ticket es nulo o está en blanco, obtiene el último valor de
		// ventas
		if ((idticket == null) || (idticket.isBlank())) {
			idticket = ObtenerUltimoValorVentas(vventas);
		}

		opcion = DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña", 
	datosmenuprincipal); 
	if (opcion == null) 
		System.out.println("opcion incorrecta ");
	else 
	switch (opcion) 
	{ 
	//falta adecuar el idticket que revise ventas y si esta vacio sea 000 si no el ultimo del arreglo
		case "1": MenuProductos(vproductos); break; 
		case "2": MenuPuntoVenta(vventas,idticket,vproductos,narchivo);//tercer cambio
						idticket=null;break; 
		case "3": MenuInventario(vproductos); break;
		case "4": System.out.println(MostrarListaVentas(vventas)); break;
		case "5":
	System.out.println("Salida del Sistema "); break; 
	default: System.out.println("No existe esta opcion "); break; 
	} 
	} 
		while (opcion.compareTo("5") != 0); 
	}

	//implementar en pseint
	public static String ObtenerUltimoValorVentas(String[][] ventas) {
		
		int ultimaposicion = ObtenerUltimaPosicion(ventas);
		String ultimoValor = "000";
			if (ultimaposicion >=0)
				ultimoValor = ventas[ultimaposicion][1];
		return ultimoValor;
	}

	
	
	/**
	 * Verifica si un archivo existe en el sistema.
	 *
	 * @param narchivo El nombre del archivo que se desea verificar.
	 * @return true si el archivo existe, false en caso contrario.
	 */
	public static boolean ExisteArchivo(String narchivo) {
		File archivo = new File(narchivo);
		return archivo.exists();
	}

	/**
	 * Genera una fila en formato CSV para un ticket. Los datos se concatenan
	 * separados por comas y se calcula el total del producto.
	 *
	 * @param idticket El identificador del ticket.
	 * @param dato1    Primer dato de la fila (por ejemplo, código del producto).
	 * @param dato2    Segundo dato de la fila (por ejemplo, nombre del producto).
	 * @param dato3    Tercer dato de la fila (por ejemplo, precio del producto).
	 * @param dato4    Cuarto dato de la fila (por ejemplo, cantidad del producto).
	 * @return Una cadena que representa la fila en formato CSV.
	 */
	public static String generarCVSFilaTicket(String idticket, String dato1, String dato2, String dato3, String dato4) {
		return idticket + "," + dato1 + "," + dato2 + "," + dato3 + "," + dato4 + "," + TotalProducto(dato3, dato4);
	}
	
	/**
	 * Guarda los datos de un ticket en un archivo CSV. Genera las filas en formato
	 * CSV a partir de los datos de la matriz y las escribe en el archivo.
	 *
	 * @param matriz        La matriz que contiene los datos del ticket.
	 * @param nombrearchivo El nombre del archivo CSV donde se guardarán los datos.
	 * @param filas         El número de filas de la matriz que se procesarán.
	 * @param idticket      El identificador del ticket que se incluirá en cada
	 *                      fila.
	 */
	public static void GuardarDatosCsvVentaTicket(String[][] matriz, String nombrearchivo, int filas, String idticket) {
		String cadena = "";
		Boolean existe;
		for (int fila = 0; fila <= filas; fila++) {
			// Genera una fila en formato CSV para el ticket
			String cadenafila = generarCVSFilaTicket(idticket, matriz[fila][0], matriz[fila][1], matriz[fila][2],
					matriz[fila][3]);
			cadena = cadena + cadenafila + "\n"; // Agrega la fila generada a la cadena
			System.out.println("fila " + fila + " " + cadena); // Imprime la fila generada en la consola
		}
		// Escribe la cadena generada en el archivo CSV
		EscribirArchivoCSV(nombrearchivo, cadena);
	}
        
				/**
				 * Escribe contenido en un archivo CSV. Si el archivo ya existe, agrega el
				 * contenido al final del archivo.
				 *
				 * @param archivo   El nombre del archivo CSV donde se escribirá el contenido.
				 * @param contenido El contenido que se escribirá en el archivo.
				 */
				public static void EscribirArchivoCSV(String archivo, String contenido) {
					try (BufferedWriter escritor = new BufferedWriter(
							new FileWriter(archivo, ExisteArchivo(archivo)))) {
						escritor.write(contenido);
					} catch (IOException e) {
						System.out.println("Ocurrió un error al escribir en el archivo: " + e.getMessage());
					}
				}
	    
		/**
		 * Lee los datos de un archivo CSV y devuelve el primer dato de la última fila
		 * con datos. Recorre el archivo línea por línea, eliminando espacios en blanco
		 * y omitiendo filas vacías.
		 *
		 * @param nombreArchivo El nombre del archivo CSV que se desea leer.
		 * @return El primer dato de la última fila con datos, o una cadena vacía si no
		 *         se encuentra ningún dato.
		 */
		public static String LeerDatosCSV(String nombreArchivo) {
			String primerDato = "";
			try (BufferedReader lector = new BufferedReader(new FileReader(nombreArchivo))) {
				String linea;
				while ((linea = lector.readLine()) != null) {
					linea = linea.trim(); // Elimina espacios en blanco
					if (!linea.isEmpty()) { // Ignorar filas vacías
						String[] datos = linea.split(",");
						primerDato = datos[0]; // Guarda el primer dato de la última fila con datos
					}
				}
			} catch (IOException e) {
				System.out.println("Error al leer el archivo: " + e.getMessage());
			}
			return primerDato;
		}
	    

		/**
		 * Genera una fila en formato CSV para una venta. Los datos se concatenan
		 * separados por comas y se agrega un salto de línea al final.
		 *
		 * @param dato1 Primer dato de la fila (por ejemplo, fecha).
		 * @param dato2 Segundo dato de la fila (por ejemplo, ID del ticket).
		 * @param dato3 Tercer dato de la fila (por ejemplo, subtotal).
		 * @param dato4 Cuarto dato de la fila (por ejemplo, IVA).
		 * @param dato5 Quinto dato de la fila (por ejemplo, total).
		 * @return Una cadena que representa la fila en formato CSV.
		 */
		public static String generarCSVFilaVenta(String dato1, String dato2, String dato3, String dato4, String dato5) {
			return dato1 + "," + dato2 + "," + dato3 + "," + dato4 + "," + dato5 + "\n";
		}

	    
		/**
		 * Guarda los datos en un archivo CSV. Verifica si el archivo existe antes de
		 * escribir en él.
		 *
		 * @param nombrearchivo El nombre del archivo CSV donde se guardarán los datos.
		 * @param contenido     El contenido que se escribirá en el archivo.
		 */
		public static void GuardarDatosCsvVentas(String nombrearchivo, String contenido) {
			Boolean existe;
			existe = ExisteArchivo(nombrearchivo); // Verifica si el archivo ya existe
			EscribirArchivoCSV(nombrearchivo, contenido); // Escribe el contenido en el archivo
		}

	public static void main(String[] args) throws IOException
    {
		 productos = CargarProductos();
		  ventas=CrearVenta(); 
		 MenuPrincipal(productos,ventas);
    }
	


}