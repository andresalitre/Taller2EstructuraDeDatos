# Taller 2 – Estructura de Datos

## Integrantes
Andrés Rojas Tejada | 22.065.446-k | andresalitre | ICCI | Paralelo: C1

## Descripción

Extensión del sistema del Taller 1. El hospital recibe pacientes desde un archivo de texto, los ordena en una cola y, al atenderlos, un árbol de decisión determina el servicio que les corresponde. Luego cada paciente se almacena en el **árbol AVL** de ese servicio, usando el ID como clave.

Flujo principal:

```
Archivo -> Cola -> Árbol de decisión -> Servicio -> AVL
```

Todo está desarrollado en C++ con estructuras implementadas manualmente (sin usar la STL para la cola, los árboles ni las listas).

## Estructura del proyecto

```
Taller2EstructuraDeDatos/
├── main.cpp
├── pacientes.txt
├── containers/
│   ├── Node.h
│   ├── List.h
│   ├── Queue.h
│   └── Stack.h
├── Dominio/
│   ├── Person.h / Person.cpp
│   ├── Patient.h / Patient.cpp
│   └── Service.h / Service.cpp
└── Arboles/
    ├── NodoAVL.h
    ├── AVL.h / AVL.cpp
    ├── NodoDecision.h
    └── ArbolDecision.h / ArbolDecision.cpp
```

## Instrucciones para compilar y correr el código

Linux / Codespace:

```bash
git clone https://github.com/andresalitre/Taller2EstructuraDeDatos
cd Taller2EstructuraDeDatos
g++ -std=c++17 main.cpp Dominio/Person.cpp Dominio/Patient.cpp Dominio/Service.cpp Arboles/AVL.cpp Arboles/ArbolDecision.cpp -o main
./main
```

Windows (PowerShell):

```powershell
git clone https://github.com/andresalitre/Taller2EstructuraDeDatos
cd Taller2EstructuraDeDatos
g++ -std=c++17 main.cpp Dominio/Person.cpp Dominio/Patient.cpp Dominio/Service.cpp Arboles/AVL.cpp Arboles/ArbolDecision.cpp -o main.exe
.\main.exe
```

El archivo `pacientes.txt` debe estar en la carpeta raíz del repositorio (la misma desde donde se ejecuta el programa).

## Formato del archivo de entrada

Cada línea representa un paciente. Las partes se separan con `;`.

```
ID;Nombre;Edad;Temperatura;PresionArterial;Dolor;TipoDolor;Trauma;SintomasNeurologicos;RequiereCirugia;DiasHospitalizacion
001;Juan Perez;25;37.0;120;3;otro;0;0;0;0
```

| Campo | Significado | Valores válidos |
|---|---|---|
| ID | Identificador único | Texto no vacío (se recomienda el mismo largo, ej. `001`) |
| Nombre | Nombre del paciente | Texto no vacío |
| Edad | Edad en años | 0 a 120 |
| Temperatura | Temperatura corporal (usar punto decimal) | 30.0 a 45.0 |
| PresionArterial | Valor numérico definido por el grupo: presión sistólica en mmHg | Entero >= 0 |
| Dolor | Escala de dolor | 0 a 10 |
| TipoDolor | Tipo de dolor (en minúscula) | `pecho`, `cabeza`, `abdomen`, `extremidad`, `otro` |
| Trauma | 0 = no existe, 1 = existe | 0 o 1 |
| SintomasNeurologicos | 0 = no existen, 1 = existen | 0 o 1 |
| RequiereCirugia | 0 = no requiere, 1 = requiere | 0 o 1 |
| DiasHospitalizacion | Días estimados | Entero >= 0 |

La presión arterial se valida pero no interviene en el árbol de decisión.

## Funcionamiento general

Menú de consola:

1. **Atender pacientes:** procesa toda la cola en orden de llegada. Para cada paciente: lo retira de la cola, lo evalúa con el árbol de decisión, obtiene el servicio, lo inserta en el AVL correspondiente e informa el resultado (datos, ruta recorrida y servicio asignado).
2. **Ver departamentos:** muestra, por cada servicio, los pacientes almacenados en su AVL (recorrido inorden) o "Sin pacientes".
3. **Buscar paciente:** busca por ID o por nombre en los AVL de los servicios. Muestra los datos del paciente, su departamento y la ruta de búsqueda dentro del AVL.
4. **Salir:** libera la memoria y termina el programa.

## Estructuras de datos implementadas manualmente

- `Node<T>`, `List<T>`, `Queue<T>` y `Stack<T>` (templates). La cola se construye sobre la lista enlazada, que guarda un puntero al último nodo para insertar al final en O(1). `Stack<T>` viene del Taller 1 y no se usa en este taller.
- `AVL`: árbol AVL de pacientes, con nodos `NodoAVL`.
- `ArbolDecision`: árbol binario de decisión, con nodos `NodoDecision`.

### Árbol AVL

- **Clave de ordenamiento:** el ID del paciente. Se compara como texto, por lo que los IDs deben tener el mismo largo para que el orden coincida con el numérico.
- **Operaciones:** insertar, buscar por ID, buscar por nombre, eliminar por ID, recorridos inorden, preorden y postorden, altura y factor de balance.
- **Rotaciones:** simple derecha, simple izquierda, doble izquierda-derecha y doble derecha-izquierda. Después de cada inserción y eliminación se recalcula la altura y se rebalancea el árbol.
- **Duplicados:** un ID repetido no se inserta.
- **Memoria:** el AVL es dueño de los pacientes y los libera en su destructor.

## Árbol de decisión

El árbol está formado por nodos y punteros. Cada nodo interno tiene una pregunta con una condición y dos hijos (sí / no). Cada hoja es un servicio. Permite construir el árbol, recorrerlo (preorden, inorden y postorden), evaluar un paciente y obtener el servicio resultante.

Atributos utilizados: Edad, Trauma, RequiereCirugia, SintomasNeurologicos, TipoDolor, Temperatura, Dolor y DiasHospitalizacion.

```
¿Edad < 14?
|-- Si: Pediatria
|-- No:
    ¿Trauma == 1?
    |-- Si:
    |   ¿RequiereCirugia == 1?
    |   |-- Si: Cirugia
    |   |-- No: Traumatologia
    |-- No:
        ¿SintomasNeurologicos == 1?
        |-- Si: Neurologia
        |-- No:
            ¿TipoDolor == "pecho"?
            |-- Si: Cardiologia
            |-- No:
                ¿Temperatura >= 38.5 o Dolor >= 8?
                |-- Si: Urgencias
                |-- No:
                    ¿DiasHospitalizacion >= 2?
                    |-- Si: Hospitalizacion
                    |-- No: Medicina General
```

Hay una ruta hacia cada uno de los ocho servicios.

### Justificación de cada decisión

| Decisión | Justificación |
|---|---|
| `Edad < 14` primero | Los menores de 14 años se atienden en Pediatría sin importar el resto de sus síntomas, porque es el servicio especializado para ellos. |
| `Trauma == 1` | Una lesión física se separa antes de evaluar síntomas generales. Se deriva a Traumatología, o a Cirugía si además requiere operación. |
| `RequiereCirugia == 1` | Dentro de los casos con trauma, distingue entre los que necesitan operación (Cirugía) y los que no (Traumatología). |
| `SintomasNeurologicos == 1` | Los síntomas neurológicos se tratan en Neurología y se evalúan antes que el dolor. |
| `TipoDolor == pecho` | El dolor de pecho se deriva a Cardiología. |
| `Temperatura >= 38.5 o Dolor >= 8` | Fiebre alta o dolor intenso se consideran urgentes y van a Urgencias. |
| `DiasHospitalizacion >= 2` | Si no hay señales de urgencia pero se estima una estadía de 2 días o más, el paciente va a Hospitalización. |
| Caso restante | El paciente sin ninguna condición especial va a Medicina General. |

### Casos de empate

Las preguntas se evalúan en orden y **gana la primera condición que se cumple**. Por eso no existen empates reales. Algunos ejemplos:

- Menor de 14 años con trauma o síntomas neurológicos: va a Pediatría.
- Paciente con trauma y síntomas neurológicos: va a Traumatología o Cirugía.
- Paciente con dolor de pecho y dolor 8: va a Cardiología.
- Paciente con fiebre alta y 3 días de hospitalización: va a Urgencias.

### Datos inválidos o insuficientes

- **Al leer el archivo:** una línea inválida se rechaza y se informa con su número de línea y el motivo. Los motivos son: cantidad de campos incorrecta (datos insuficientes), ID o nombre vacío, valor no numérico y datos fuera de rango. El resto del archivo se sigue procesando.
- **En el árbol de decisión:** si se evalúa un paciente con datos inválidos (`ArbolDecision::esValido` devuelve `false`), se deriva a **Urgencias** y la ruta indica "Datos invalidos". Se eligió Urgencias por ser la opción más segura ante la duda.

### Casos de prueba representativos

Incluidos en `pacientes.txt`:

| ID | Paciente | Característica | Servicio esperado |
|---|---|---|---|
| 001 | Juan Perez | Adulto sin síntomas | Medicina General |
| 002 | Maria Gonzalez | 8 años | Pediatria |
| 003 | Carlos Soto | Dolor de pecho | Cardiologia |
| 004 | Ana Rojas | Síntomas neurológicos | Neurologia |
| 005 | Luis Munoz | Trauma sin cirugía | Traumatologia |
| 006 | Pedro Diaz | Trauma con cirugía | Cirugia |
| 007 | Camila Torres | Temperatura 39.1 | Urgencias |
| 008 | Jose Fuentes | 5 días de hospitalización | Hospitalizacion |

Las últimas líneas del archivo son casos invalidos a propósito: ID duplicado, edad no numerica, dolor fuera de rango y línea con campos de menos.

## Manejo de errores

- **Archivo inexistente:** se muestra un mensaje y el programa continúa con la cola vacía.
- **Datos inválidos:** la línea se rechaza con su motivo.
- **Pacientes duplicados:** si el ID ya está en la cola, la línea se rechaza.
- **Entrada del menú:** una opción inválida muestra un mensaje y vuelve a pedir la opción.

## Liberación de memoria

- `List` libera sus nodos en el destructor, y `Queue` y `Stack` se apoyan en ella.
- `AVL` libera sus nodos y los pacientes que almacena.
- `ArbolDecision` libera todos sus nodos.
- Al salir, el programa libera los pacientes que quedaron en la cola y los servicios (cada servicio libera su AVL).
