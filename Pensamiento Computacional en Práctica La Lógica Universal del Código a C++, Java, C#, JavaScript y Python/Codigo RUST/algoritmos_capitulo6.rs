use std::io;

fn agregar_stock(vproductos: &mut [[String; 4]; 10]) {
    let info = mostrar_lista(vproductos);
    let codigo = leer(&format!("{}\nIntroduce el codigo del producto a modificar", info));

    if !codigo.is_empty() {
        let posicion = existe_producto(&codigo, vproductos);
        if posicion > -1 {
            let vproducto = &vproductos[posicion as usize];
            let cantidad_str = leer(&format!("\nIntroduce la Cantidad de Stock a Agregar a {} ", mostrar_producto(vproducto)));

            if !cantidad_str.is_empty() {
                if let Ok(cantidad_agregar) = cantidad_str.parse::<i32>() {
                    if let Ok(cantidad_actual) = vproducto[3].parse::<i32>() {
                        let nueva_cantidad = cantidad_actual + cantidad_agregar;
                        vproductos[posicion as usize][3] = nueva_cantidad.to_string();
                    } else {
                        println!("Error al convertir la cantidad actual");
                    }
                } else {
                    println!("no es un valor numerico");
                }
            } else {
                println!("dato nulo");
            }
        } else {
            println!("no existe el codigo");
        }
    } else {
        println!("dato nulo");
    }
}

fn menu_inventario(vproductos: &mut [[String; 4]; 10]) {
    let datosmenuinventario = vec!["Listado", "Agregar", "Salida"];
    let mut opcion = "0".to_string();
    while opcion != "3" {
        opcion = desplegar_menu("Opciones de Inventarios", &datosmenuinventario);
        if opcion.is_empty() {
            println!("opcion incorrecta");
        } else {
            let op: i32 = opcion.parse().unwrap_or(0);
            match op {
                1 => println!("{}", mostrar_lista(vproductos)),
                2 => agregar_stock(vproductos),
                3 => println!("Salida del Sistema"),
                _ => println!("No existe esta opcion"),
            }
        }
    }
}
