package main

import (
	"fmt"
	"strconv"
)

// MenuPrincipal muestra el menú principal de la aplicación y permite navegar a los diferentes submódulos.
func MenuPrincipal() {
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
				MenuProductos()
			case 2:
				MenuPuntoVenta("000")
			case 3:
				MenuInventario()
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

// MenuProductos muestra y gestiona las opciones relacionadas con los productos.
func MenuProductos() {
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
				fmt.Println("Modificar Precio Producto")
			case 2:
				fmt.Println("Listado Producto")
			case 3:
				fmt.Println("Salida del Sistema")
			default:
				fmt.Println("No existe esta opcion")
			}
		}
	} while opcion != "3"
}

// MenuPuntoVenta gestiona el menú del punto de venta para un ticket específico.
func MenuPuntoVenta(idticket string) {
	var opcion, membrete string
	pago := false
	idticket = IdTicketSiguiente(idticket)
	fechadia := Fecha()
	membrete = "Fecha del Dia " + fechadia + " Ticket No " + idticket
	membrete += "
-----------------------------------------------------
"
	datosmenu := []string{"Agregar", "Eliminar", "Listado", "Pagar", "Salida"}

	do {
		opcion = DesplegarMenu(membrete+"
Menu de Punto de Venta", datosmenu)
		if opcion == "" {
			fmt.Println("dato incorrecto introducido")
		} else {
			op, _ := strconv.Atoi(opcion)
			switch op {
			case 1:
				fmt.Println("Agregar Articulo al Ticket")
			case 2:
				fmt.Println("Eliminar Articulo del Ticket")
			case 3:
				fmt.Println("Listado de Articulos del Ticket")
			case 4:
				fmt.Println("Pagar Ticket y salir")
				opcion = "5"
				pago = true
			case 5:
				fmt.Println("Salida del Ventas")
				if !pago {
					fmt.Println("No pago el ticket")
					fmt.Println("eliminando ticket", idticket)
				}
			default:
				fmt.Println("No existe esta opcion")
			}
		}
	} while opcion != "5"
}

// MenuInventario muestra y gestiona las opciones del inventario.
func MenuInventario() {
	datosmenuinventario := []string{"Listado", "Agregar", "Salida"}
	var opcion = "0"
	do {
		opcion = DesplegarMenu("Opciones de Inventarios", datosmenuinventario)
		if opcion == "" {
			fmt.Println("opcion incorrecta")
		} else {
			op, _ := strconv.Atoi(opcion)
			switch op {
			case 1:
				fmt.Println("Listado de Inventario")
			case 2:
				fmt.Println("Agregar Inventario")
			case 3:
				fmt.Println("Salida del Sistema")
			default:
				fmt.Println("No existe esta opcion")
			}
		}
	} while opcion != "3"
}
