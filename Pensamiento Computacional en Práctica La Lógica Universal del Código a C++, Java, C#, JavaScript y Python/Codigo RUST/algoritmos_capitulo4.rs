use std::io;

fn menu_principal() {
    let mut opcion: i32;
    let mut salida = false;
    let datosmenuprincipal = vec!["Productos", "Punto de Venta", "Inventario", "Ventas", "Salida"];

    while !salida {
        let opcion_str = desplegar_menu("Menu de Punto de Tienda de Abarrotes la Pequeña", &datosmenuprincipal);

        if opcion_str.is_empty() {
            println!("opcion incorrecta");
        } else {
            opcion = opcion_str.parse().unwrap_or(0);
            match opcion {
                1 => menu_productos(),
                2 => menu_punto_venta("000"),
                3 => menu_inventario(),
                4 => println!("Ventas"),
                5 => {
                    println!("Salida del Sistema");
                    salida = true;
                }
                _ => println!("No existe esta opcion"),
            }
        }
    }
}

fn menu_productos() {
    let datosmenuproductos = vec!["Modificar", "Listado", "Salida"];
    let mut opcion = "0".to_string();
    while opcion != "3" {
        opcion = desplegar_menu("Opciones de Productos", &datosmenuproductos);
        if opcion.is_empty() {
            println!("opcion incorrecta");
        } else {
            let op: i32 = opcion.parse().unwrap_or(0);
            match op {
                1 => println!("Modificar Precio Producto"),
                2 => println!("Listado Producto"),
                3 => println!("Salida del Sistema"),
                _ => println!("No existe esta opcion"),
            }
        }
    }
}

fn menu_punto_venta(idticket: &str) {
    let mut opcion: String;
    let mut pago = false;
    let mut idticket = id_ticket_siguiente(idticket);
    let fechadia = fecha();
    let mut membrete = format!("Fecha del Dia {} Ticket No {}\n-----------------------------------------------------\n", fechadia, idticket);
    let datosmenu = vec!["Agregar", "Eliminar", "Listado", "Pagar", "Salida"];

    loop {
        opcion = desplegar_menu(&format!("{}\nMenu de Punto de Venta", membrete), &datosmenu);
        if opcion.is_empty() {
            println!("dato incorrecto introducido");
        } else {
            let op: i32 = opcion.parse().unwrap_or(0);
            match op {
                1 => println!("Agregar Articulo al Ticket"),
                2 => println!("Eliminar Articulo del Ticket"),
                3 => println!("Listado de Articulos del Ticket"),
                4 => {
                    println!("Pagar Ticket y salir");
                    opcion = "5".to_string();
                    pago = true;
                }
                5 => {
                    println!("Salida del Ventas");
                    if !pago {
                        println!("No pago el ticket");
                        println!("eliminando ticket {}", idticket);
                    }
                    break;
                }
                _ => println!("No existe esta opcion"),
            }
        }
    }
}

fn menu_inventario() {
    let datosmenuinventario = vec!["Listado", "Agregar", "Salida"];
    let mut opcion = "0".to_string();
    while opcion != "3" {
        opcion = desplegar_menu("Opciones de Inventarios", &datosmenuinventario);
        if opcion.is_empty() {
            println!("opcion incorrecta");
        } else {
            let op: i32 = opcion.parse().unwrap_or(0);
            match op {
                1 => println!("Listado de Inventario"),
                2 => println!("Agregar Inventario"),
                3 => println!("Salida del Sistema"),
                _ => println!("No existe esta opcion"),
            }
        }
    }
}
