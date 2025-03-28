typedef enum ObjectKind {
    INTEGER
} object_kind_t ;

typedef union ObjectData {
    int v_int;
} object_data_t;

typedef struct Object {
    object_kind_t kind;
    object_data_t data;
} object_t;
