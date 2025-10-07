package main

import (
	"fmt"
	"strconv"
)

// CargarProductos inicializa o "carga" una matriz de productos con datos predefinidos.
func CargarProductos() [][]string {
	productos := [][]string{
		{"001", "Arroz 1kg", "35", "10"},
		{"002", "Azúcar 1kg", "25", "10"},
		{"003", "Harina 1kg", "28", "10"},
		{"004", "Aceite 1L", "50", "10"},
		{"005", "Leche 1L", "35", "10"},
		{"006", "Huevos 12 unidades", "45", "10"},
		{"007", "Fideos 500g", "20", "10"},
		{"008", "Sal 1kg", "15", "10"},
		{"009", "Pasta de tomate 400g", "25", "10"},
		{"010", "Atún lata 170g", "35", "10"},
	}
	return productos
}

// MostrarProducto formatea los datos de un único producto en una sola cadena de texto.
func MostrarProducto(vproducto []string) string {
	codigo := RellenarEspacios(vproducto[0], 5)
	producto := RellenarEspacios(vproducto[1], 30)
	precio := RellenarEspacios(vproducto[2], 10)
	cantidad := RellenarEspacios(vproducto[3], 10)
	return codigo + producto + precio + cantidad
}

// MostrarLista genera una lista completa y formateada de todos los productos de la matriz.
func MostrarLista(vproductos [][]string) string {
	var salida string
	for _, vproducto := range vproductos {
		cadena := MostrarProducto(vproducto)
		salida += cadena + "
"
	}
	return salida
}

// ExisteProducto busca un producto en la matriz por su código.
func ExisteProducto(codigo string, vproductos [][]string) int {
	for i, vproducto := range vproductos {
		if vproducto[0] == codigo {
			return i
		}
	}
	return -1
}

// ModificarProducto gestiona la interfaz y la lógica para modificar el precio de un producto.
func ModificarProducto(vproductos [][]string) {
	info := MostrarLista(vproductos)
	codigo := Leer(info + "
Introduce el codigo del producto a modificar")

	if codigo != "" {
		posicion := ExisteProducto(codigo, vproductos)

		if posicion > -1 {
			vproducto := vproductos[posicion]
			precio := Leer("
Introduce el precio de " + MostrarProducto(vproducto) + " ")

			if precio != "" {
				if EvaluarNumerico(precio, 2) || EvaluarNumerico(precio, 1) {
					vproductos[posicion][2] = precio
					fmt.Println("Producto modificado con éxito.")
				} else {
					fmt.Println("no es un valor numerico")
				}
			} else {
				fmt.Println("dato nulo")
			}
		} else {
			fmt.Println("no existe el codigo")
		}
	} else {
		fmt.Println("dato nulo")
	}
}

// MenuProductos (actualizado) muestra el menú de opciones para la gestión de productos.
func MenuProductos(vproductos [][]string) {
	datosmenuproductos := []string{"Modificar", "Listado", "Salida"}
	var opcion = "0"
	do {
		opcion = DesplegarMenu("Opciones de Productos", datosmenuproductos)
		if opcion == "" {
			fmt.Println("opcion incorrecta")
		} else {
			op, _ := strconv.Atoi(opcion)
			switch op {
			case 1:
				ModificarProducto(vproductos)
			case 2:
				fmt.Println(MostrarLista(vproductos))
			case 3:
				fmt.Println("Salida del Sistema")
			default:
				fmt.Println("No existe esta opcion")
			}
		}
	} while opcion != "3"
}

// MenuPrincipal (reestructurado) es el bucle principal de la aplicación.
func MenuPrincipal(vproductos [][]string) {
	var opcion int
	var salida bool
	datosmenuprincipal := []string{"Productos", "Punto de Venta", "Inventario", "Ventas", "Salida"}

	for !salida {
		opcionStr := DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña", datosmenuprincipal)

		if opcionStr == "" {
			fmt.Println("opcion incorrecta")
		} else {
			opcion, _ = strconv.Atoi(opcionStr)
			switch opcion {
			case 1:
				MenuProductos(vproductos)
			case 2:
				// MenuPuntoVenta("000") Llama al menú de punto de venta
			case 3:
				// MenuInventario() Llama al menú de inventario
			case 4:
				fmt.Println("Ventas")
			case 5:
				fmt.Println("Salida del Sistema")
				salida = true
			default:
				fmt.Println("No existe esta opcion")
			}
		}
	}
}
