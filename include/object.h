typedef enum ObjectKind {
    INTEGER,
    FLOAT,
    STRING
} object_kind_t ;

typedef union ObjectData {
    int v_int;
    float v_float;
    char *v_string;
} object_data_t;

typedef struct Object {
    object_kind_t kind;
    object_data_t data;
} object_t;

object_t *new_integer(int value);

object_t *new_float(float value);

object_t *new_string(char *value);
