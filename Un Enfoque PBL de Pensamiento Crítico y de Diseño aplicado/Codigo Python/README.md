La evolución del proyecto está organizada para reflejar el proceso de aprendizaje de un libro. Cada parte del código corresponde a un capítulo, y los comentarios explican los conceptos introducidos en ese punto. La versión final y consolidada del proyecto se encuentra en el Anexo

Capítulo 3: Modularización del Proyecto Este capítulo representa la base organizativa del código. En lugar de escribir un programa largo y monolítico, se enfoca en dividir el sistema en partes más pequeñas y reutilizables. Creación de "Funciones de Apoyo": Se desarrollan herramientas esenciales que se usarán a lo largo de todo el proyecto Tareas Específicas: Estas funciones se encargan de tareas como mostrar menús, validar que un dato sea numérico, formatear texto y obtener la fecha.

Capítulo 4: Diseño de la Estructura del Proyecto Principal En este capítulo se construye el "esqueleto" del sistema. Se toman las funciones de apoyo creadas en el capítulo anterior y se utilizan para ensamblar los menús interactivos del programa. Integración de Módulos: Conecta los diferentes menús (Principal, Productos, Inventarios, etc.) con sus respectivas funcione

Capítulo 5: Gestión de Productos Este capítulo se centra en implementar toda la lógica relacionada con los productos. Se utilizan matrices bidimensionales para almacenar y organizar la información de cada artículo (código, nombre, precio y cantidad).

Capítulo 6: Gestión de Inventario Este capítulo se enfoca específicamente en el control de las existencias (stock) de los productos. Control de Stock: Implementa la lógica para gestionar las cantidades de cada producto.

Capítulo 7: Gestión de Ventas Este es el núcleo del sistema, donde se implementa todo el proceso de una transacción comercial. Manejo de Tickets: Utiliza dos matrices: una para gestionar los productos del ticket de la venta actual y otra para guardar un historial de todas las ventas completadas. Proceso de Venta Completo: Detalla los algoritmos para agregar productos al ticket, eliminarlos, calcular el subtotal, IVA y total a pagar. Lógica de Negocio: Incluye la lógica para registrar el pago y, en caso de que una venta se cancele, devolver los productos al inventario para no afectar el stock

Anexo (Capítulo 8) El Anexo introduce un concepto fundamental que los capítulos anteriores no cubrían: la Almacenamiento Permanente: Mientras que en los capítulos anteriores toda la información (productos, ventas) se perdía al cerrar el programa, aquí se enseña cómo guardarla de forma permanente en archivos. Uso de Archivos CSV: Se explica cómo leer y escribir datos en archivos de texto con formato CSV (Valores Separados por Comas). Registro de Ventas: Permite que el sistema guarde un historial duradero de todas las transacciones, de modo que la información no dependa únicamente de la memoria temporal del programa

Operaciones CRUD: Desarrolla las funciones para Cargar, Mostrar, Buscar y Modificar los productos del inventario
