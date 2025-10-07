use std::io;

mod algoritmos_anexo;
mod algoritmos_capitulo3;
mod algoritmos_capitulo4;
mod algoritmos_capitulo5;
mod algoritmos_capitulo6;
mod algoritmos_capitulo7;

fn main() {
    let mut productos = cargar_productos();
    let mut ventas = crear_venta();

    menu_principal(&mut productos, &mut ventas);
}

fn menu_principal(vproductos: &mut [[String; 4]; 10], vventas: &mut Vec<[String; 5]>) {
    let mut opcion: i32;
    let mut salida = false;
    let mut idticket = "".to_string();
    let datosmenuprincipal = vec!["Productos", "Punto de Venta", "Inventario", "Ventas", "Salida"];
    let narchivo = format!("{}.csv", fecha());

    if existe_archivo(&narchivo) {
        if let Ok(id) = leer_datos_csv(&narchivo) {
            idticket = id;
        }
    }

    while !salida {
        if idticket.is_empty() {
            idticket = obtener_ultimo_valor_ventas(vventas);
        }
        let opcion_str = desplegar_menu("Menu de Punto de Tienda de Abarrotes la Pequeña", &datosmenuprincipal);

        if opcion_str.is_empty() {
            println!("opcion incorrecta");
        } else {
            opcion = opcion_str.parse().unwrap_or(0);
            match opcion {
                1 => menu_productos(vproductos),
                2 => {
                    menu_punto_venta(vventas, &mut idticket, vproductos, &narchivo);
                    idticket = "".to_string();
                }
                3 => menu_inventario(vproductos),
                4 => println!("{}", mostrar_lista_ventas(vventas)),
                5 => {
                    println!("Salida del Sistema");
                    salida = true;
                }
                _ => println!("No existe esta opcion"),
            }
        }
    }
}

fn menu_punto_venta(
    vventas: &mut Vec<[String; 5]>,
    idticket: &mut String,
    vproductos: &mut [[String; 4]; 10],
    narchivo: &str,
) {
    let mut opcion: String;
    let mut pago = false;
    const TAMTICKET: usize = 50;
    let mut vticket = Vec::with_capacity(TAMTICKET);
    *idticket = id_ticket_siguiente(idticket);
    let fechadia = fecha();

    loop {
        let mut membrete = format!("Fecha del Día: {} | Ticket No: \n", fechadia, idticket);
        membrete.push_str("-----------------------------------------------------\
");
        let ticket_texto = mostrar_ticket(&vticket);
        if !ticket_texto.is_empty() {
            membrete.push_str(&format!("\n{}\n", ticket_texto));
        }
        let datosmenu = vec!["Agregar", "Eliminar", "Listado", "Pagar", "Salida"];
        opcion = desplegar_menu(&format!("{}\nMenú de Punto de Venta", membrete), &datosmenu);

        if opcion.is_empty() {
            println!("Dato incorrecto introducido");
        } else {
            let op: i32 = opcion.parse().unwrap_or(0);
            match op {
                1 => captura_venta_producto(&mut vticket, vproductos, idticket, TAMTICKET),
                2 => eliminar(&mut vticket, vproductos),
                3 => {
                    if !mostrar_ticket(&vticket).is_empty() {
                        println!("{}", mostrar_ticket(&vticket));
                    }
                }
                4 => {
                    println!("{}", mostrar_ticket(&vticket));
                    pagar(idticket, vventas, &vticket);
                    if !vticket.is_empty() {
                        println!(
                            "tamaño de venta creando archivo {} {}",
                            vventas.len(),
                            vticket.len()
                        );
                        if let Err(e) = guardar_datos_csv_venta_ticket(&vticket, narchivo, idticket) {
                            println!("Error al guardar el ticket: {}", e);
                        }
                        let subtotal = format!("{{:.2}}", sub_total_ticket(&vticket));
                        let iva = format!("{{:.2}}", iva_ticket(&vticket));
                        let total = format!("{{:.2}}", total_ticket(&vticket));
                        let cadena = generar_csv_fila_venta(&fechadia, idticket, &subtotal, &iva, &total);
                        if let Err(e) = guardar_datos_csv_ventas("ventas.csv", &cadena) {
                            println!("Error al guardar la venta: {}", e);
                        }
                    }
                    pago = true;
                    break;
                }
                5 => {
                    println!("Salida del sistema");
                    if !pago {
                        println!("No pagó el ticket. Ejecutando devolución...");
                        devolucion_ticket(&vticket, vproductos);
                        println!("Eliminando ticket {}", idticket);
                    }
                    break;
                }
                _ => println!("Opción no válida"),
            }
        }
    }
}
