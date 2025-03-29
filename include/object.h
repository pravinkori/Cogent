typedef struct Object object_t;

typedef struct Vector {
    object_t *x;
    object_t *y;
    object_t *z;
} vector_t;

typedef enum ObjectKind {
    INTEGER,
    FLOAT,
    STRING,
    VECTOR3
} object_kind_t ;

typedef union ObjectData {
    int v_int;
    float v_float;
    char *v_string;
    vector_t v_vector3;
} object_data_t;

typedef struct Object {
    object_kind_t kind;
    object_data_t data;
} object_t;

object_t *new_integer(int value);

object_t *new_float(float value);

object_t *new_string(char *value);

object_t *new_vector(object_t *x, object_t *y, object_t *z);
