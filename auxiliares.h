void read_n_k(int *n, int *k);
points_t *read_points(int n);
Matrix cria_matrix_A(points_t *points, unsigned int order);
Vector cria_vector_B(points_t *points, unsigned int order);
void print_coeficientes(Vector *b);
void print_residuo(points_t *points, Vector *b);
