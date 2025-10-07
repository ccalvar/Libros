package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

// Dialogo muestra un texto y lee una línea de entrada del usuario.
func Dialogo(texto string) string {
	fmt.Printf("%s : ", texto)
	reader := bufio.NewReader(os.Stdin)
	cadena, _ := reader.ReadString('\n')
	return strings.TrimSpace(cadena)
}

// MostrarMenu construye y formatea una cadena de texto que representa un menú de opciones.
func MostrarMenu(opciones []string) string {
	var cadena strings.Builder
	for i, opcion := range opciones {
		cadena.WriteString(fmt.Sprintf("%d. %s\n", i+1, opcion))
	}
	return cadena.String()
}

// DesplegarMenu muestra un título, un menú de opciones y solicita al usuario que elija una.
func DesplegarMenu(titulo1 string, menu []string) string {
	var cadena strings.Builder
	cadena.WriteString(titulo1 + "\n\n")
	cadena.WriteString(MostrarMenu(menu))
	cadena.WriteString("\nQue opcion deseas ")
	return Dialogo(cadena.String())
}

// Leer pide un dato al usuario, lo lee y elimina los espacios en blanco al principio y al final.
func Leer(texto string) string {
	cadena := Dialogo(texto)
	return strings.TrimSpace(cadena)
}

// EsNumeroEntero verifica si una cadena de texto contiene únicamente dígitos numéricos.
func EsNumeroEntero(dato string) bool {
	_, err := strconv.Atoi(dato)
	return err == nil
}

// EsNumeroDouble verifica si una cadena de texto representa un número de tipo float64.
func EsNumeroDouble(dato string) bool {
	_, err := strconv.ParseFloat(dato, 64)
	return err == nil
}

// EvaluarNumerico evalúa si una cadena es de un tipo numérico específico (entero o double).
func EvaluarNumerico(dato string, tipo int) bool {
	switch tipo {
	case 1:
		return EsNumeroEntero(dato)
	case 2:
		return EsNumeroDouble(dato)
	default:
		return false
	}
}

// RellenarEspacios rellena una cadena con espacios a la derecha hasta que alcance un tamaño específico.
func RellenarEspacios(dato string, tamano int) string {
	return fmt.Sprintf("% -*s", tamano, dato)
}

// IdTicketSiguiente toma un ID de ticket como cadena, lo incrementa en 1 y lo formatea con ceros a la izquierda.
func IdTicketSiguiente(idticket string) string {
	num, _ := strconv.Atoi(idticket)
	num++
	return fmt.Sprintf("%03d", num)
}

// ObtenerUltimaPosicion encuentra el índice de la última fila utilizada en una matriz.
func ObtenerUltimaPosicion(matriz [][]string) int {
	ultimaPosicion := -1
	for i, fila := range matriz {
		if len(fila) > 0 && fila[0] != "" {
			ultimaPosicion = i
		}
	}
	return ultimaPosicion
}

// Fecha obtiene la fecha actual del sistema y la formatea como "dd-MM-yyyy".
func Fecha() string {
	return time.Now().Format("02-01-2006")
}
