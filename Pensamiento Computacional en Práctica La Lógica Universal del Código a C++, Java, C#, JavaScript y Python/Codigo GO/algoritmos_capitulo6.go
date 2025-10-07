package main

import (
	"fmt"
	"strconv"
)

// AgregarStock gestiona la interfaz y la lógica para agregar stock a un producto existente.
func AgregarStock(vproductos [][]string) {
	info := MostrarLista(vproductos)
	codigo := Leer(info + "
Introduce el codigo del producto a modificar")

	if codigo != "" {
		posicion := ExisteProducto(codigo, vproductos)
		if posicion > -1 {
			vproducto := []string{vproductos[posicion][0], vproductos[posicion][1], vproductos[posicion][3], ""}
			cantidad := Leer("
Introduce la Cantidad de Stock a Agregar" + MostrarProducto(vproducto) + " ")

			if cantidad != "" {
				if EvaluarNumerico(cantidad, 1) {
					cantActual, _ := strconv.Atoi(vproducto[2])
					cantAgregar, _ := strconv.Atoi(cantidad)
					nuevacantidad := strconv.Itoa(cantActual + cantAgregar)
					vproductos[posicion][3] = nuevacantidad
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

// MenuInventario (actualizado) muestra el menú de opciones para la gestión del inventario.
func MenuInventario(vproductos [][]string) {
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
				fmt.Println(MostrarLista(vproductos))
			case 2:
				AgregarStock(vproductos)
			case 3:
				fmt.Println("Salida del Sistema")
			default:
				fmt.Println("No existe esta opcion")
			}
		}
	} while opcion != "3"
}
