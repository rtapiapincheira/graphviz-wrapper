#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
  * Una transicion, de la forma (desde, simbolos, hasta).
  */
typedef struct {
    int from;
    char pattern[1024+1];
    int to;
} transition;

/**
  * Un automata, con la cantidad de estados iniciales, estados finales,
  * estado inicial y transiciones.
  */
typedef struct {
    int states;

    int start_state;

    int *end_states;
    size_t num_end_states;

    transition *transitions;
    size_t num_transitions;

} automaton;

/**
 * @return 1 si graphviz esta disponible en el sistema, 0 si no lo esta.
 */
int graphviz_available() {
    if (system("dot -V") == 0) {
        return (1);
    }
    return (0);
}

/**
 * @param a Automata para ser volcado en formato dot.
 * @param filename Nombre de archivo para escribir en formato dot.
 * @return 1 si se pudo volcar a archivo correctamente, 0 si no.
 */
int graphviz_write(automaton *a, const char *filename) {
    size_t i;
    FILE* fid = fopen(filename, "w");
    if (!fid) {
        return (0);
    }
    fprintf(fid, "digraph finite_state_machine {\n");
    fprintf(fid, "    rankdir=LR;\n");
    fprintf(fid, "    node[shape=point, color=white, fontcolor=white]; start;\n");
    fprintf(fid, "    node[shape=doublecircle, color=black, fontcolor=black];");
    for (i = 0; i < a->num_end_states; i++) {
        fprintf(fid, " %d", a->end_states[i]);
    }
    if (a->num_end_states > 0) {
        fprintf(fid, ";");
    }
    fprintf(fid, "\n");
    fprintf(fid, "    node[shape=circle]; %d;\n", a->start_state);
    fprintf(fid, "    start -> %d;\n", a->start_state);
    for (i = 0; i < a->num_transitions; i++) {
        transition *ai = &a->transitions[i];
        fprintf(fid, "    %d -> %d [label=\"%s\"];\n", ai->from, ai->to, ai->pattern);
    }
    fprintf(fid, "}\n");
    fclose(fid);
    return (1);
}

int graphviz_convert(const char *dot_filename, const char *image_filename) {
    char command[4096+1];
    sprintf(command, "dot -Tpng %s -o %s", dot_filename, image_filename);
    return (system(command) == 0 ? 1 : 0);

}

transition make_transition(int from, const char *pattern, int to) {
    transition t;
    t.from = from;
    strncpy(t.pattern, pattern, 1024); // Copiar a lo mas 1024 caracteres!
    t.to = to;
    return (t);
}

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

    if (!graphviz_write(&a, "secuencia.dot")) {
        printf("No se puede escribir archivo .dot, abortando\n");
        return (1);
    }

    if (!graphviz_convert("secuencia.dot", "diagrama.png")) {
        printf("No se puede escribir archivo .png, abortando\n");
        return (1);
    }

    printf("Archivo guardado correctamente. Chao.\n");

    return (0);
}

