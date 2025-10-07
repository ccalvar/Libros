use std::io::{self, Write};
use chrono::Local;

// Dialogo muestra un texto y lee una línea de entrada del usuario.
fn dialogo(texto: &str) -> String {
    print!("{} : ", texto);
    io::stdout().flush().unwrap();
    let mut cadena = String::new();
    io::stdin().read_line(&mut cadena).unwrap();
    cadena.trim().to_string()
}

// MostrarMenu construye y formatea una cadena de texto que representa un menú de opciones.
fn mostrar_menu(opciones: &[&str]) -> String {
    let mut cadena = String::new();
    for (i, &opcion) in opciones.iter().enumerate() {
        cadena.push_str(&format!("{}. {}
", i + 1, opcion));
    }
    cadena
}

// DesplegarMenu muestra un título, un menú de opciones y solicita al usuario que elija una.
fn desplegar_menu(titulo1: &str, menu: &[&str]) -> String {
    let mut cadena = String::new();
    cadena.push_str(titulo1);
    cadena.push_str("\n\n");
    cadena.push_str(&mostrar_menu(menu));
    cadena.push_str("\nQue opcion deseas ");
    dialogo(&cadena)
}

// Leer pide un dato al usuario, lo lee y elimina los espacios en blanco al principio y al final.
fn leer(texto: &str) -> String {
    dialogo(texto)
}

// EsNumeroEntero verifica si una cadena de texto contiene únicamente dígitos numéricos.
fn es_numero_entero(dato: &str) -> bool {
    dato.parse::<i32>().is_ok()
}

// EsNumeroDouble verifica si una cadena de texto representa un número de tipo f64.
fn es_numero_double(dato: &str) -> bool {
    dato.parse::<f64>().is_ok()
}

// EvaluarNumerico evalúa si una cadena es de un tipo numérico específico (entero o double).
fn evaluar_numerico(dato: &str, tipo: i32) -> bool {
    match tipo {
        1 => es_numero_entero(dato),
        2 => es_numero_double(dato),
        _ => false,
    }
}

// RellenarEspacios rellena una cadena con espacios a la derecha hasta que alcance un tamaño específico.
fn rellenar_espacios(dato: &str, tamano: usize) -> String {
    format!("{:<width$}", dato, width = tamano)
}

// IdTicketSiguiente toma un ID de ticket como cadena, lo incrementa en 1 y lo formatea con ceros a la izquierda.
fn id_ticket_siguiente(idticket: &str) -> String {
    let num = idticket.parse::<i32>().unwrap_or(0) + 1;
    format!("{:03}", num)
}

// ObtenerUltimaPosicion encuentra el índice de la última fila utilizada en una matriz.
fn obtener_ultima_posicion(matriz: &[[String; 4]]) -> i32 {
    let mut ultima_posicion = -1;
    for (i, fila) in matriz.iter().enumerate() {
        if !fila[0].is_empty() {
            ultima_posicion = i as i32;
        }
    }
    ultima_posicion
}

// Fecha obtiene la fecha actual del sistema y la formatea como "dd-MM-yyyy".
fn fecha() -> String {
    Local::now().format("%d-%m-%Y").to_string()
}

