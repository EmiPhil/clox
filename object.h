#ifndef CLOX_OBJECT_H
#define CLOX_OBJECT_H

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value)     (AS_OBJ(value)->type)

#define IS_STRING(value)    is_obj_type(value, OBJ_STRING)

#define AS_STRING(value)    ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value)   (((ObjString *)AS_OBJ(value))->chars)

typedef enum {
    OBJ_STRING
} ObjType;

struct Obj {
    ObjType type;
    struct Obj * next;
};


// Adding the Obj as the first member of this struct allows us to convert it to the base Obj type in a inheritance
// like fashion (ObjString * can be safely cast to a Obj *). The reverse operation is true as well - a Obj * can be cast
// to a ObjString *, which can be unsafe if the underlying Obj * isn't actually an ObjString *.
struct ObjString {
    Obj obj;
    int length;
    char *chars;
};

ObjString * take_string(char * chars, int length);
ObjString * copy_string(const char *chars, int length);
void print_object(Value value);

static inline bool is_obj_type(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif //CLOX_OBJECT_H
