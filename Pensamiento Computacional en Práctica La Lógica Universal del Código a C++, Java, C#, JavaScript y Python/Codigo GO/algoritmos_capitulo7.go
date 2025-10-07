package main

import (
	"fmt"
	"strconv"
)

const tamventas = 100

// CrearVenta inicializa una matriz de ventas vacía.
func CrearVenta() [][]string {
	return make([][]string, tamventas)
}

// UltimoTicket obtiene el ID del último ticket registrado en el historial de ventas.
func UltimoTicket(pos int, mventa [][]string) string {
	if pos > -1 {
		return mventa[pos][0]
	}
	return "000"
}

// CrearTicket inicializa una matriz de ticket vacía.
func CrearTicket() [][]string {
	return make([][]string, 20)
}

// ExisteTicketCodigo verifica si un producto ya existe dentro del ticket actual.
func ExisteTicketCodigo(mticket [][]string, codigo string) int {
	pos := ObtenerUltimaPosicion(mticket)
	fmt.Println("buscando", codigo, "tamaño arreglo", pos)
	for ciclo := 0; ciclo <= pos; ciclo++ {
		if mticket[ciclo][0] == codigo {
			return ciclo
		}
	}
	return -1
}

// InsertarProductoTicket inserta un producto en el ticket.
func InsertarProductoTicket(mticket [][]string, datos []string, tamticket int) bool {
	posticket := ObtenerUltimaPosicion(mticket)
	enc := ExisteTicketCodigo(mticket, datos[0])
	if posticket < tamticket {
		if enc > -1 {
			fmt.Println("Ya existe el producto en el ticket, lo incrementare")
			cantidadactual, _ := strconv.Atoi(mticket[enc][3])
			mticket[enc][3] = strconv.Itoa(cantidadactual + 1)
		} else {
			posticket++
			mticket[posticket] = datos
			fmt.Println("Insertando, no existe el producto en el ticket")
		}
	} else {
		return false
	}
	return true
}

// TotalProducto calcula el costo total de una línea de producto.
func TotalProducto(precio string, cantidad string) string {
	p, _ := strconv.ParseFloat(precio, 64)
	c, _ := strconv.ParseFloat(cantidad, 64)
	total := p * c
	return fmt.Sprintf("%.2f", total)
}

// MostrarProductoTicket formatea una línea de producto del ticket para su visualización.
func MostrarProductoTicket(mticket [][]string, pos int) string {
	codigo := RellenarEspacios(mticket[pos][0], 5)
	producto := RellenarEspacios(mticket[pos][1], 30)
	precio := RellenarEspacios(mticket[pos][2], 10)
	cantidad := RellenarEspacios(mticket[pos][3], 5)
	totalproducto := RellenarEspacios(TotalProducto(mticket[pos][2], mticket[pos][3]), 10)
	return codigo + producto + precio + cantidad + totalproducto
}

// MostrarTicket genera una representación en texto de todo el contenido del ticket actual.
func MostrarTicket(mticket [][]string) string {
	var salida string
	pos := ObtenerUltimaPosicion(mticket)
	for ciclo := 0; ciclo <= pos; ciclo++ {
		salida += MostrarProductoTicket(mticket, ciclo) + "
"
	}
	return salida
}

// SubTotalTicket calcula el subtotal de la venta.
func SubTotalTicket(mticket [][]string) float64 {
	var subtotal float64
	pos := ObtenerUltimaPosicion(mticket)
	for ciclo := 0; ciclo <= pos; ciclo++ {
		valor, _ := strconv.ParseFloat(TotalProducto(mticket[ciclo][2], mticket[ciclo][3]), 64)
		subtotal += valor
	}
	return subtotal
}

// IvaTicket calcula el monto del IVA.
func IvaTicket(mticket [][]string) float64 {
	subtotal := SubTotalTicket(mticket)
	if subtotal > 0 {
		return 0.16 * subtotal
	}
	return -1
}

// TotalTicket calcula el total final de la venta.
func TotalTicket(mticket [][]string) float64 {
	total := SubTotalTicket(mticket)
	if total > 0 {
		return IvaTicket(mticket) + total
	}
	return total
}

// MostrarTicketVenta genera el formato de impresión final del ticket.
func MostrarTicketVenta(mticket [][]string, idticket string, fecha string) string {
	subtotal := fmt.Sprintf("%.2f", SubTotalTicket(mticket))
	iva := fmt.Sprintf("%.2f", IvaTicket(mticket))
	total := fmt.Sprintf("%.2f", TotalTicket(mticket))

	var salida string
	salida += fmt.Sprintf("Fecha %s Ticket No.%s
", fecha, idticket)
	salida += MostrarTicket(mticket)
	salida += fmt.Sprintf("

El total sin iva %s", subtotal)
	salida += fmt.Sprintf("
el iva total es %s", iva)
	salida += fmt.Sprintf("
el total de la venta fue %s", total)

	return salida
}

// MostrarListaProductosVenta genera una lista de productos disponibles para la venta.
func MostrarListaProductosVenta(vproductos [][]string) string {
	var salida string
	for _, vproducto := range vproductos {
		existencia, _ := strconv.Atoi(vproducto[3])
		if existencia > 0 {
			cadena := MostrarProducto(vproducto)
			salida += cadena + "
"
		}
	}
	return salida
}

// CapturaVentaProducto gestiona la captura de un producto para la venta.
func CapturaVentaProducto(mticket [][]string, mproductos [][]string, idticket string, tamticket int) {
	info := MostrarListaProductosVenta(mproductos)
	codigo := Leer(info + "
Introduce el codigo del producto")

	if codigo != "" {
		posp := ExisteProducto(codigo, mproductos)
		if posp > -1 {
			cant, _ := strconv.Atoi(mproductos[posp][3])
			if cant > 0 {
				producto := make([]string, 4)
				copy(producto, mproductos[posp])
				cant--
				mproductos[posp][3] = strconv.Itoa(cant)
				fmt.Println(MostrarProducto(producto))

				venta := []string{mproductos[posp][0], mproductos[posp][1], mproductos[posp][2], "1"}
				if !InsertarProductoTicket(mticket, venta, tamticket) {
					fmt.Println("El arreglo esta lleno")
				}
			} else {
				fmt.Println("No hay productos para venta")
			}
		} else {
			fmt.Println("El codigo no existe, no se puede agregar")
		}
	} else {
		fmt.Println("Dato nulo")
	}
}

// RemoverProductoTicket elimina una línea de producto del ticket.
func RemoverProductoTicket(mticket [][]string, pos int) {
	tam := ObtenerUltimaPosicion(mticket)
	if tam > pos {
		mticket = append(mticket[:pos], mticket[pos+1:]...)
	} else {
		mticket[pos] = []string{}
	}
}

// EliminarProductoTicket gestiona la eliminación de un producto del ticket.
func EliminarProductoTicket(mticket [][]string, pos int) {
	cantidad, _ := strconv.Atoi(mticket[pos][3])
	if cantidad > 1 {
		mticket[pos][3] = strconv.Itoa(cantidad - 1)
	} else {
		RemoverProductoTicket(mticket, pos)
	}
}

// Eliminar orquesta la eliminación de un producto del ticket por parte del usuario.
func Eliminar(mticket [][]string, mproductos [][]string) {
	info := MostrarTicket(mticket)
	codigo := Leer(info + "
Introduce el codigo del producto")

	if codigo != "" {
		pos := ExisteTicketCodigo(mticket, codigo)
		if pos > -1 {
			posproducto := ExisteProducto(codigo, mproductos)
			nuevacantidad, _ := strconv.Atoi(mproductos[posproducto][3])
			mproductos[posproducto][3] = strconv.Itoa(nuevacantidad + 1)
			RemoverProductoTicket(mticket, pos)
		}
	} else {
		fmt.Println("Dato nulo")
	}
}

// AgregarProductoAVenta transfiere los productos de un ticket pagado al historial de ventas.
func AgregarProductoAVenta(mticket [][]string, mventa [][]string, idticket string) {
	posventas := ObtenerUltimaPosicion(mventa)
	posticket := ObtenerUltimaPosicion(mticket)
	for i := 0; i <= posticket; i++ {
		if len(mticket[i]) > 0 && mticket[i][0] != "" {
			posventas++
			mventa[posventas] = []string{idticket, mticket[i][0], mticket[i][1], mticket[i][2], mticket[i][3]}
		}
	}
}

// Pagar gestiona el proceso de pago.
func Pagar(idticket string, mventa [][]string, mticket [][]string) {
	posventas := ObtenerUltimaPosicion(mventa)
	post := ObtenerUltimaPosicion(mticket)
	if (posventas + post) < 100 {
		AgregarProductoAVenta(mticket, mventa, idticket)
	} else {
		fmt.Println("Desbordamiento de Memoria de ventas")
	}
}

// DevolucionTicket cancela un ticket que no fue pagado.
func DevolucionTicket(mticket [][]string, mproductos [][]string) {
	posmticket := ObtenerUltimaPosicion(mticket)
	for pos := 0; pos <= posmticket; pos++ {
		codigo := mticket[pos][0]
		posp := ExisteProducto(codigo, mproductos)
		if posp > -1 {
			cantTicket, _ := strconv.Atoi(mticket[pos][3])
			cantProd, _ := strconv.Atoi(mproductos[posp][3])
			mproductos[posp][3] = strconv.Itoa(cantTicket + cantProd)
		}
	}
}

// ObtenerUltimoValorVentas busca en el historial de ventas y obtiene el ID del último ticket registrado.
func ObtenerUltimoValorVentas(ventas [][]string) string {
	ultimaposicion := ObtenerUltimaPosicion(ventas)
	if ultimaposicion >= 0 {
		return ventas[ultimaposicion][0]
	}
	return "000"
}

// MostrarVenta formatea una sola línea del historial de ventas para su visualización.
func MostrarVenta(venta []string) string {
	idticket := RellenarEspacios(venta[0], 6)
	codigo := RellenarEspacios(venta[1], 5)
	producto := RellenarEspacios(venta[2], 30)
	precio := RellenarEspacios(venta[3], 10)
	cantidad := RellenarEspacios(venta[4], 10)
	return idticket + codigo + producto + precio + cantidad
}

// MostrarListaVentas genera una lista formateada de todo el historial de ventas.
func MostrarListaVentas(ventas [][]string) string {
	posventas := ObtenerUltimaPosicion(ventas)
	var salida string
	for ciclo := 0; ciclo <= posventas; ciclo++ {
		venta := ventas[ciclo]
		salida += MostrarVenta(venta) + "
"
	}
	return salida
}
