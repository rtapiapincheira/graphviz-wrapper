# graphviz-wrapper
A wrapper for graphviz for PLF course.

http://www.graphviz.org/Download..php

Compilar con:
```
   gcc main.c -o prueba
```

Ejecutar con:
```
   prueba.exe
```

Programa de ejemplo:
   ```
int main() {
    automaton a;

    // Numero de estados
    a.states = 3;

    // Estado inicial
    a.start_state = 0;

    // Estados finales
    a.num_end_states = 1;
    a.end_states = (int*)calloc(a.num_end_states, sizeof(int));
    a.end_states[0] = 2;

    // Transiciones
    a.num_transitions = 5;
    a.transitions = (transition*)calloc(a.num_transitions, sizeof(transition));
    a.transitions[0] = make_transition(0, "a", 1);
    a.transitions[1] = make_transition(1, "b", 2);
    a.transitions[2] = make_transition(2, "a", 2);
    a.transitions[3] = make_transition(2, "b", 2);
    a.transitions[4] = make_transition(1, "a", 0);

    // Crear archivo .dot en disco
    if (!graphviz_write(&a, "secuencia.dot")) {
        printf("No se puede escribir archivo .dot, abortando\n");
        return (1);
    }

    // Convertir archivo .dot en uno .png usando graphviz
    if (!graphviz_convert("secuencia.dot", "diagrama.png")) {
        printf("No se puede escribir archivo .png, abortando\n");
        return (1);
    }

    printf("Archivo guardado correctamente. Chao.\n");

    return (0);
}
```
