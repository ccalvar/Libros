package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// ExisteArchivo verifica si un archivo existe.
func ExisteArchivo(narchivo string) bool {
	info, err := os.Stat(narchivo)
	if os.IsNotExist(err) {
		return false
	}
	return !info.IsDir()
}

// EscribirArchivoCSV escribe contenido en un archivo CSV.
func EscribirArchivoCSV(nombrearchivo string, contenido string) {
	f, err := os.OpenFile(nombrearchivo, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Error al abrir el archivo:", err)
		return
	}
	defer f.Close()

	if _, err := f.WriteString(contenido + "
"); err != nil {
		fmt.Println("Error al escribir en el archivo:", err)
	}
}

// GenerarCVSFilaTicket genera una fila de ticket en formato CSV.
func GenerarCVSFilaTicket(idticket, dato1, dato2, dato3, dato4 string) string {
	return fmt.Sprintf("%s,%s,%s,%s,%s", idticket, dato1, dato2, dato3, dato4)
}

// GuardarDatosCsvVentaTicket guarda los datos de la venta de un ticket en un archivo CSV.
func GuardarDatosCsvVentaTicket(matriz [][]string, nombrearchivo string, filas int, idticket string) {
	var cadena strings.Builder
	for i := 0; i < filas; i++ {
		cadenaFila := GenerarCVSFilaTicket(idticket, matriz[i][0], matriz[i][1], matriz[i][2], matriz[i][3])
		cadena.WriteString(cadenaFila)
		if i < filas-1 {
			cadena.WriteString("
")
		}
	}
	EscribirArchivoCSV(nombrearchivo, cadena.String())
}

// LeerDatosCSV lee la primera columna de la última línea de un archivo CSV.
func LeerDatosCSV(nombrearchivo string) string {
	var primerDato string
	file, err := os.Open(nombrearchivo)
	if err != nil {
		fmt.Println("Error al abrir el archivo:", err)
		return ""
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		linea := strings.TrimSpace(scanner.Text())
		if linea != "" {
			partes := strings.Split(linea, ",")
			if len(partes) > 0 {
				primerDato = partes[0]
			}
		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error al leer el archivo:", err)
	}

	return primerDato
}

// GenerarCSVFilaVenta genera una fila de venta en formato CSV.
func GenerarCSVFilaVenta(dato1, dato2, dato3, dato4, dato5 string) string {
	return fmt.Sprintf("%s,%s,%s,%s,%s
", dato1, dato2, dato3, dato4, dato5)
}

// GuardarDatosCsvVentas guarda los datos de ventas en un archivo CSV.
func GuardarDatosCsvVentas(nombrearchivo string, contenido string) {
	EscribirArchivoCSV(nombrearchivo, contenido)
}
