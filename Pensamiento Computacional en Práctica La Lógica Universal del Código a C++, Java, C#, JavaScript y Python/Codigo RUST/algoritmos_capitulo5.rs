use std::io;

fn cargar_productos() -> [[String; 4]; 10] {
    [
        [String::from("001"), String::from("Arroz 1kg"), String::from("35"), String::from("10")],
        [String::from("002"), String::from("Azúcar 1kg"), String::from("25"), String::from("10")],
        [String::from("003"), String::from("Harina 1kg"), String::from("28"), String::from("10")],
        [String::from("004"), String::from("Aceite 1L"), String::from("50"), String::from("10")],
        [String::from("005"), String::from("Leche 1L"), String::from("35"), String::from("10")],
        [String::from("006"), String::from("Huevos 12 unidades"), String::from("45"), String::from("10")],
        [String::from("007"), String::from("Fideos 500g"), String::from("20"), String::from("10")],
        [String::from("008"), String::from("Sal 1kg"), String::from("15"), String::from("10")],
        [String::from("009"), String::from("Pasta de tomate 400g"), String::from("25"), String::from("10")],
        [String::from("010"), String::from("Atún lata 170g"), String::from("35"), String::from("10")],
    ]
}

fn mostrar_producto(vproducto: &[String; 4]) -> String {
    let codigo = rellenar_espacios(&vproducto[0], 5);
    let producto = rellenar_espacios(&vproducto[1], 30);
    let precio = rellenar_espacios(&vproducto[2], 10);
    let cantidad = rellenar_espacios(&vproducto[3], 10);
    format!("{}{}{}{}", codigo, producto, precio, cantidad)
}

fn mostrar_lista(vproductos: &[[String; 4]; 10]) -> String {
    let mut salida = String::new();
    for vproducto in vproductos.iter() {
        let cadena = mostrar_producto(vproducto);
        salida.push_str(&cadena);
        salida.push('\n');
    }
    salida
}

fn existe_producto(codigo: &str, vproductos: &[[String; 4]; 10]) -> i32 {
    for (i, vproducto) in vproductos.iter().enumerate() {
        if vproducto[0] == codigo {
            return i as i32;
        }
    }
    -1
}

fn modificar_producto(vproductos: &mut [[String; 4]; 10]) {
    let info = mostrar_lista(vproductos);
    let codigo = leer(&format!("{}\nIntroduce el codigo del producto a modificar", info));

    if !codigo.is_empty() {
        let posicion = existe_producto(&codigo, vproductos);

        if posicion > -1 {
            let vproducto = &vproductos[posicion as usize];
            let precio = leer(&format!("\nIntroduce el precio de {} ", mostrar_producto(vproducto)));

            if !precio.is_empty() {
                if evaluar_numerico(&precio, 2) || evaluar_numerico(&precio, 1) {
                    vproductos[posicion as usize][2] = precio;
                    println!("Producto modificado con éxito.");
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

fn menu_productos(vproductos: &mut [[String; 4]; 10]) {
    let datosmenuproductos = vec!["Modificar", "Listado", "Salida"];
    let mut opcion = "0".to_string();
    while opcion != "3" {
        opcion = desplegar_menu("Opciones de Productos", &datosmenuproductos);
        if opcion.is_empty() {
            println!("opcion incorrecta");
        } else {
            let op: i32 = opcion.parse().unwrap_or(0);
            match op {
                1 => modificar_producto(vproductos),
                2 => println!("{}", mostrar_lista(vproductos)),
                3 => println!("Salida del Sistema"),
                _ => println!("No existe esta opcion"),
            }
        }
    }
}

fn menu_principal(vproductos: &mut [[String; 4]; 10]) {
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
                1 => menu_productos(vproductos),
                2 => {},
                3 => {},
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
