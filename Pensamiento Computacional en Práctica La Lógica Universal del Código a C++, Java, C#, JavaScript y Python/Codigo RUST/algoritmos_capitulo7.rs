use std::io;

const TAM_VENTAS: usize = 100;

fn crear_venta() -> Vec<[String; 5]> {
    Vec::with_capacity(TAM_VENTAS)
}

fn ultimo_ticket(pos: i32, mventa: &[[String; 5]]) -> String {
    if pos > -1 {
        mventa[pos as usize][0].clone()
    } else {
        "000".to_string()
    }
}

fn crear_ticket() -> Vec<[String; 4]> {
    Vec::with_capacity(20)
}

fn existe_ticket_codigo(mticket: &[[String; 4]], codigo: &str) -> i32 {
    let pos = obtener_ultima_posicion(mticket);
    println!("buscando {} tamaño arreglo {}", codigo, pos);
    for ciclo in 0..=pos {
        if mticket[ciclo as usize][0] == codigo {
            return ciclo;
        }
    }
    -1
}

fn insertar_producto_ticket(mticket: &mut Vec<[String; 4]>, datos: [String; 4], tamticket: usize) -> bool {
    let posticket = obtener_ultima_posicion(mticket);
    let enc = existe_ticket_codigo(mticket, &datos[0]);
    if (posticket as usize) < tamticket {
        if enc > -1 {
            println!("Ya existe el producto en el ticket, lo incrementare");
            let cantidad_actual: i32 = mticket[enc as usize][3].parse().unwrap_or(0);
            mticket[enc as usize][3] = (cantidad_actual + 1).to_string();
        } else {
            mticket.push(datos);
            println!("Insertando, no existe el producto en el ticket");
        }
    } else {
        return false;
    }
    true
}

fn total_producto(precio: &str, cantidad: &str) -> String {
    let p: f64 = precio.parse().unwrap_or(0.0);
    let c: f64 = cantidad.parse().unwrap_or(0.0);
    format!("{:.2}", p * c)
}

fn mostrar_producto_ticket(mticket: &[[String; 4]], pos: usize) -> String {
    let codigo = rellenar_espacios(&mticket[pos][0], 5);
    let producto = rellenar_espacios(&mticket[pos][1], 30);
    let precio = rellenar_espacios(&mticket[pos][2], 10);
    let cantidad = rellenar_espacios(&mticket[pos][3], 5);
    let totalproducto = rellenar_espacios(&total_producto(&mticket[pos][2], &mticket[pos][3]), 10);
    format!("{}{}{}{}{}", codigo, producto, precio, cantidad, totalproducto)
}

fn mostrar_ticket(mticket: &[[String; 4]]) -> String {
    let mut salida = String::new();
    let pos = obtener_ultima_posicion(mticket);
    for ciclo in 0..=pos {
        salida.push_str(&mostrar_producto_ticket(mticket, ciclo as usize));
        salida.push('\n');
    }
    salida
}

fn sub_total_ticket(mticket: &[[String; 4]]) -> f64 {
    let mut subtotal = 0.0;
    let pos = obtener_ultima_posicion(mticket);
    for ciclo in 0..=pos {
        let valor: f64 = total_producto(&mticket[ciclo as usize][2], &mticket[ciclo as usize][3])
            .parse()
            .unwrap_or(0.0);
        subtotal += valor;
    }
    subtotal
}

fn iva_ticket(mticket: &[[String; 4]]) -> f64 {
    let subtotal = sub_total_ticket(mticket);
    if subtotal > 0.0 {
        0.16 * subtotal
    } else {
        -1.0
    }
}

fn total_ticket(mticket: &[[String; 4]]) -> f64 {
    let total = sub_total_ticket(mticket);
    if total > 0.0 {
        iva_ticket(mticket) + total
    } else {
        total
    }
}

fn mostrar_ticket_venta(mticket: &[[String; 4]], idticket: &str, fecha: &str) -> String {
    let subtotal = format!("{:.2}", sub_total_ticket(mticket));
    let iva = format!("{:.2}", iva_ticket(mticket));
    let total = format!("{:.2}", total_ticket(mticket));

    let mut salida = String::new();
    salida.push_str(&format!("Fecha {} Ticket No.{}\n", fecha, idticket));
    salida.push_str(&mostrar_ticket(mticket));
    salida.push_str(&format!("\n\nEl total sin iva {}", subtotal));
    salida.push_str(&format!("\nel iva total es {}", iva));
    salida.push_str(&format!("\nel total de la venta fue {}", total));

    salida
}

fn mostrar_lista_productos_venta(vproductos: &[[String; 4]; 10]) -> String {
    let mut salida = String::new();
    for vproducto in vproductos.iter() {
        let existencia: i32 = vproducto[3].parse().unwrap_or(0);
        if existencia > 0 {
            let cadena = mostrar_producto(vproducto);
            salida.push_str(&cadena);
            salida.push('\n');
        }
    }
    salida
}

fn captura_venta_producto(
    mticket: &mut Vec<[String; 4]>,
    mproductos: &mut [[String; 4]; 10],
    idticket: &str,
    tamticket: usize,
) {
    let info = mostrar_lista_productos_venta(mproductos);
    let codigo = leer(&format!("{}\nIntroduce el codigo del producto", info));

    if !codigo.is_empty() {
        let posp = existe_producto(&codigo, mproductos);
        if posp > -1 {
            let cant: i32 = mproductos[posp as usize][3].parse().unwrap_or(0);
            if cant > 0 {
                let mut producto = [String::new(), String::new(), String::new(), String::new()];
                for (i, item) in mproductos[posp as usize].iter().enumerate() {
                    producto[i] = item.clone();
                }
                let cant = cant - 1;
                mproductos[posp as usize][3] = cant.to_string();
                println!("{}", mostrar_producto(&producto));

                let venta = [
                    mproductos[posp as usize][0].clone(),
                    mproductos[posp as usize][1].clone(),
                    mproductos[posp as usize][2].clone(),
                    "1".to_string(),
                ];
                if !insertar_producto_ticket(mticket, venta, tamticket) {
                    println!("El arreglo esta lleno");
                }
            } else {
                println!("No hay productos para venta");
            }
        } else {
            println!("El codigo no existe, no se puede agregar");
        }
    } else {
        println!("Dato nulo");
    }
}

fn remover_producto_ticket(mticket: &mut Vec<[String; 4]>, pos: usize) {
    mticket.remove(pos);
}

fn eliminar_producto_ticket(mticket: &mut Vec<[String; 4]>, pos: usize) {
    let cantidad: i32 = mticket[pos][3].parse().unwrap_or(0);
    if cantidad > 1 {
        mticket[pos][3] = (cantidad - 1).to_string();
    } else {
        remover_producto_ticket(mticket, pos);
    }
}

fn eliminar(mticket: &mut Vec<[String; 4]>, mproductos: &mut [[String; 4]; 10]) {
    let info = mostrar_ticket(mticket);
    let codigo = leer(&format!("{}\nIntroduce el codigo del producto", info));

    if !codigo.is_empty() {
        let pos = existe_ticket_codigo(mticket, &codigo);
        if pos > -1 {
            let posproducto = existe_producto(&codigo, mproductos);
            let nueva_cantidad: i32 = mproductos[posproducto as usize][3].parse().unwrap_or(0) + 1;
            mproductos[posproducto as usize][3] = nueva_cantidad.to_string();
            remover_producto_ticket(mticket, pos as usize);
        }
    } else {
        println!("Dato nulo");
    }
}

fn agregar_producto_a_venta(
    mticket: &[[String; 4]],
    mventa: &mut Vec<[String; 5]>,
    idticket: &str,
) {
    let posticket = obtener_ultima_posicion(mticket);
    for i in 0..=posticket {
        if !mticket[i as usize][0].is_empty() {
            mventa.push([
                idticket.to_string(),
                mticket[i as usize][0].clone(),
                mticket[i as usize][1].clone(),
                mticket[i as usize][2].clone(),
                mticket[i as usize][3].clone(),
            ]);
        }
    }
}

fn pagar(idticket: &str, mventa: &mut Vec<[String; 5]>, mticket: &[[String; 4]]) {
    let posventas = mventa.len();
    let post = obtener_ultima_posicion(mticket);
    if (posventas + post as usize) < TAM_VENTAS {
        agregar_producto_a_venta(mticket, mventa, idticket);
    } else {
        println!("Desbordamiento de Memoria de ventas");
    }
}

fn devolucion_ticket(mticket: &[[String; 4]], mproductos: &mut [[String; 4]; 10]) {
    let posmticket = obtener_ultima_posicion(mticket);
    for pos in 0..=posmticket {
        let codigo = &mticket[pos as usize][0];
        let posp = existe_producto(codigo, mproductos);
        if posp > -1 {
            let cant_ticket: i32 = mticket[pos as usize][3].parse().unwrap_or(0);
            let cant_prod: i32 = mproductos[posp as usize][3].parse().unwrap_or(0);
            mproductos[posp as usize][3] = (cant_ticket + cant_prod).to_string();
        }
    }
}

fn obtener_ultimo_valor_ventas(ventas: &[[String; 5]]) -> String {
    if let Some(ultima_venta) = ventas.last() {
        ultima_venta[0].clone()
    } else {
        "000".to_string()
    }
}

fn mostrar_venta(venta: &[String; 5]) -> String {
    let idticket = rellenar_espacios(&venta[0], 6);
    let codigo = rellenar_espacios(&venta[1], 5);
    let producto = rellenar_espacios(&venta[2], 30);
    let precio = rellenar_espacios(&venta[3], 10);
    let cantidad = rellenar_espacios(&venta[4], 10);
    format!("{}{}{}{}{}", idticket, codigo, producto, precio, cantidad)
}

fn mostrar_lista_ventas(ventas: &[[String; 5]]) -> String {
    let mut salida = String::new();
    for venta in ventas.iter() {
        salida.push_str(&mostrar_venta(venta));
        salida.push('\n');
    }
    salida
}
