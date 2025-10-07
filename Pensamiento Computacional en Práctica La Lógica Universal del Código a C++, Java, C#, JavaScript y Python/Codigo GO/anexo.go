package main

import (
	"fmt"
	"strconv"
)

var productos [][]string
var ventas [][]string

func main() {
	productos = CargarProductos()
	ventas = CrearVenta()

	MenuPrincipal(productos, ventas)
}

// MenuPrincipal (reestructurado) es el bucle principal de la aplicación.
func MenuPrincipal(vproductos [][]string, vventas [][]string) {
	var opcion int
	var salida bool
	var idticket string
	datosmenuprincipal := []string{"Productos", "Punto de Venta", "Inventario", "Ventas", "Salida"}
	narchivo := Fecha() + ".csv"

	if ExisteArchivo(narchivo) {
		idticket = LeerDatosCSV(narchivo)
	}

	for !salida {
		if idticket == "" {
			idticket = ObtenerUltimoValorVentas(vventas)
		}
		opcionStr := DesplegarMenu("Menu de Punto de Tienda de Abarrotes la Pequeña", datosmenuprincipal)

		if opcionStr == "" {
			fmt.Println("opcion incorrecta")
		} else {
			opcion, _ = strconv.Atoi(opcionStr)
			switch opcion {
			case 1:
				MenuProductos(vproductos)
			case 2:
				MenuPuntoVenta(vventas, idticket, vproductos, narchivo)
				idticket = ""
			case 3:
				MenuInventario(vproductos)
			case 4:
				fmt.Println(MostrarListaVentas(vventas))
			case 5:
				fmt.Println("Salida del Sistema")
				salida = true
			default:
				fmt.Println("No existe esta opcion")
			}
		}
	}
}

// MenuPuntoVenta (actualizado) gestiona el menú del punto de venta para un ticket específico.
func MenuPuntoVenta(vventas [][]string, idticket string, vproductos [][]string, narchivo string) {
	var opcion, membrete string
	pago := false
	tamticket := 50
	Vticket := make([][]string, tamticket)
	idticket = IdTicketSiguiente(idticket)
	fechadia := Fecha()

	do {
		membrete = "Fecha del Día: " + fechadia + " | Ticket No: " + idticket + "
"
		membrete += "-----------------------------------------------------
"
		Tickettexto := MostrarTicket(Vticket)
		if Tickettexto != "" {
			membrete += "
" + Tickettexto + "
"
		}
		datosmenu := []string{"Agregar", "Eliminar", "Listado", "Pagar", "Salida"}
		opcion = DesplegarMenu(membrete+"
Menú de Punto de Venta", datosmenu)

		if opcion == "" {
			fmt.Println("Dato incorrecto introducido")
		} else {
			op, _ := strconv.Atoi(opcion)
			switch op {
			case 1:
				CapturaVentaProducto(Vticket, vproductos, idticket, tamticket)
			case 2:
				Eliminar(Vticket, vproductos)
			case 3:
				if MostrarTicket(Vticket) != "" {
					fmt.Println(MostrarTicket(Vticket))
				}
			case 4:
				fmt.Println(MostrarTicket(Vticket))
				Pagar(idticket, vventas, Vticket)
				if ObtenerUltimaPosicion(Vticket) > -1 {
					fmt.Println("tamaño de venta creando archivo", ObtenerUltimaPosicion(vventas), ObtenerUltimaPosicion(Vticket))
					GuardarDatosCsvVentaTicket(Vticket, narchivo, ObtenerUltimaPosicion(Vticket)+1, idticket)
					subtotal := fmt.Sprintf("%.2f", SubTotalTicket(Vticket))
					iva := fmt.Sprintf("%.2f", IvaTicket(Vticket))
					total := fmt.Sprintf("%.2f", TotalTicket(Vticket))
					cadena := GenerarCSVFilaVenta(fechadia, idticket, subtotal, iva, total)
					GuardarDatosCsvVentas("ventas.csv", cadena)
				}
				pago = true
				opcion = "5"
			case 5:
				fmt.Println("Salida del sistema")
				if !pago {
					fmt.Println("No pagó el ticket. Ejecutando devolución...")
					DevolucionTicket(Vticket, vproductos)
					fmt.Println("Eliminando ticket", idticket)
				}
			default:
				fmt.Println("Opción no válida")
			}
		}
	} while opcion != "5"
}
