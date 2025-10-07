use std::fs::{File, OpenOptions};
use std::io::{self, BufRead, Write};
use std::path::Path;

// ExisteArchivo verifica si un archivo existe.
fn existe_archivo(narchivo: &str) -> bool {
    Path::new(narchivo).exists()
}

// EscribirArchivoCSV escribe contenido en un archivo CSV.
fn escribir_archivo_csv(nombrearchivo: &str, contenido: &str) -> io::Result<()> {
    let mut file = OpenOptions::new()
        .create(true)
        .append(true)
        .open(nombrearchivo)?;
    writeln!(file, "{}", contenido)
}

// GenerarCVSFilaTicket genera una fila de ticket en formato CSV.
fn generar_cvs_fila_ticket(idticket: &str, dato1: &str, dato2: &str, dato3: &str, dato4: &str) -> String {
    format!("{},{},{},{},{}", idticket, dato1, dato2, dato3, dato4)
}

// GuardarDatosCsvVentaTicket guarda los datos de la venta de un ticket en un archivo CSV.
fn guardar_datos_csv_venta_ticket(matriz: &[[String; 4]], nombrearchivo: &str, idticket: &str) -> io::Result<()> {
    let mut cadena = String::new();
    for (i, fila) in matriz.iter().enumerate() {
        let cadena_fila = generar_cvs_fila_ticket(idticket, &fila[0], &fila[1], &fila[2], &fila[3]);
        cadena.push_str(&cadena_fila);
        if i < matriz.len() - 1 {
            cadena.push('\n');
        }
    }
    escribir_archivo_csv(nombrearchivo, &cadena)
}

// LeerDatosCSV lee la primera columna de la última línea de un archivo CSV.
fn leer_datos_csv(nombrearchivo: &str) -> io::Result<String> {
    let file = File::open(nombrearchivo)?;
    let reader = io::BufReader::new(file);
    let mut primer_dato = String::new();
    for line in reader.lines() {
        let linea = line?;
        if !linea.trim().is_empty() {
            if let Some(dato) = linea.split(',').next() {
                primer_dato = dato.to_string();
            }
        }
    }
    Ok(primer_dato)
}

// GenerarCSVFilaVenta genera una fila de venta en formato CSV.
fn generar_csv_fila_venta(dato1: &str, dato2: &str, dato3: &str, dato4: &str, dato5: &str) -> String {
    format!("{},{},{},{},{}\n", dato1, dato2, dato3, dato4, dato5)
}

// GuardarDatosCsvVentas guarda los datos de ventas en un archivo CSV.
fn guardar_datos_csv_ventas(nombrearchivo: &str, contenido: &str) -> io::Result<()> {
    escribir_archivo_csv(nombrearchivo, contenido)
}

