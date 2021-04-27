####TAREA 2

##Entrada

Se recibirá un entero C que representa los casos de prueba a evaluar. Seguido a esto se
recibirá una cantidad arbitraria de líneas con 2 nombres K y L cada una separados por un espacio,
que representan que K convirtió en vampiro por L. Posteriormente se recibirá una cantidad no
definida de nombres, uno por línea, que representa los vampiros de los cuales se desea saber a qué
clan pertenecen. Cada caso de prueba terminará con una línea que contiene únicamente un punto.

##Salida

La primera línea contendrá la cadena "Caso N:", donde N representa el número del caso de
prueba, empezando por el caso 1. Seguido de esto se escribirá entero L que representa la cantidad
de clanes encontrados. Luego, para cada clan se mostrará lo siguiente: Una línea con el mensaje
"Clan X:" donde X representa el número del clan, X ≥ 1. Seguido a esto, una línea con el nombre
del líder de ese clan, siendo el líder el miembro más antiguo. Posteriormente, se escribirá un par de
enteros M y G separados por un espacio, que representa la cantidad de miembros de ese clan y la
cantidad de generaciones presentes, respectivamente. Esto se hará tantas veces como clanes se
hayan encontrado. Luego, se escribirá el nombre del líder del clan al que pertenecen los vampiros a
ubicar, en el mismo orden en que fueron recibidos. Cada caso de prueba debe terminar con una
línea en blanco (indispensable para fines de presentación y evaluación). 

#Tarea 3

##Entrada:

La primera línea de la entrada tendrá un entero C, que indica el número de
casos de prueba. La primera línea de cada caso de prueba contendrá un par de
enteros N T separados con un espacio que representa la cantidad de estados que
conforman la MT y la cantidad de transiciones, respectivamente. Luego se recibirá
una línea de caracteres separados por espacios que representan los símbolos de
la cinta. Posteriormente se recibirán T líneas que representan las transiciones de
la MT, de la forma O F L E D que indica una transición desde el estado O hacia el
estado F leyendo L en la cadena, escribiendo E y realizando un desplazamiento D,
todos separados por un espacio. Finalmente, se recibirán una cadena para ser
evaluada por la MT.

##Salida:

En la primera línea de cada caso de prueba debe mostrar la cadena "Caso
X:", en donde X representa el número del caso de prueba actual (empezando en
1). Seguido de esto, se escribirá la cadena paso a paso, un paso por línea, donde
se reflejen los cambios aplicados por la MT, comenzando en la cadena original y
terminando en la cadena resultante. Posteriormente, se escribirá una línea con la
palabra "Aceptada" si la cadena es aceptada por la MT, o "Rechazada" en el caso
contrario. Cada caso de prueba debe terminar con una línea en blanco.
