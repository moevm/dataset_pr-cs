#include <stdlib.h>

#include "pngdata.h"
#include "pngfill.h"
#include "pngmnp.h"

#define STACK_DEFAULT_CAPACITY 10

typedef struct px_t {
    int x, y;
} px_t;

typedef px_t type_t;

typedef struct stack_t {
    type_t* array;
    int top_index;
    size_t capacity;
} stack_t;

void push(stack_t* stack, type_t value);
void pop(stack_t* stack);
type_t top(stack_t* stack);
int is_empty(stack_t* stack);
size_t count(stack_t* stack);
stack_t* init_stack();
void free_stack(stack_t* stack);

void
push(stack_t* stack, type_t value) {
    if (count(stack) == stack->capacity) {
        stack->capacity += STACK_DEFAULT_CAPACITY;
        stack->array = (type_t*)realloc(stack->array, stack->capacity * sizeof(type_t));
    }
    stack->array[++(stack->top_index)] = value;
}

void
pop(stack_t* stack) {
    if (is_empty(stack)) {
        return;
    }
    stack->top_index -= 1;
}

type_t
top(stack_t* stack) {
    return stack->array[stack->top_index];
}

int
is_empty(stack_t* stack) {
    return count(stack) == 0;
}

size_t
count(stack_t* stack) {
    return stack->top_index + 1;
}

stack_t*
init_stack() {
    stack_t* stack = (stack_t*)malloc(1 * sizeof(stack_t));
    stack->capacity = STACK_DEFAULT_CAPACITY;
    stack->array = (type_t*)malloc(stack->capacity * sizeof(type_t));
    stack->top_index = -1;
    return stack;
}

void
free_stack(stack_t* stack) {
    free(stack->array);
    free(stack);
}

int
fill_canvas(canvas_t* canvas, color_t* color) {
    if (canvas == NULL || color == NULL) {
        printf("Error: Null pointer to canvas or color.\n");
        return 42;
    }
    for (size_t row = 0; row < canvas->height; ++row) {
        for (size_t column = 0; column < canvas->width; ++column) {
            set_pixel(canvas, color, column, row);
        }
    }
    return 0;
}

int inside(canvas_t* canvas, color_t* color, color_t* border_color, int x, int y);

int
inside(canvas_t* canvas, color_t* color, color_t* border_color, int x, int y) {
    if (canvas == NULL || color == NULL) {
        return 0;
    }
    if (!is_on_canvas(canvas, x, y)) {
        return 0;
    }
    color_t* got_color = get_pixel(canvas, x, y);
    if (border_color != NULL) {
        if (color_cmp(border_color, got_color)) {
            free(got_color);
            return 0;
        }
    }
    int cmp = color_cmp(color, got_color);
    free(got_color);
    if (cmp) {
        return 0;
    }
    return 1;
}

int
fill(canvas_t* canvas, color_t* color, color_t* border_color, int x, int y) {
    if (canvas == NULL || color == NULL) {
        printf("Error: Null pointer to canvas or color.\n");
        return 42;
    }
    stack_t* stack = init_stack();
    px_t px = {x, y};
    push(stack, px);
    while (!is_empty(stack)) {
        px_t n = top(stack);
        pop(stack);
        if (inside(canvas, color, border_color, n.x, n.y)) {
            set_pixel(canvas, color, n.x, n.y);
            if (inside(canvas, color, border_color, n.x - 1, n.y)) {
                px_t npx = {n.x - 1, n.y};
                push(stack, npx);
            }
            if (inside(canvas, color, border_color, n.x + 1, n.y)) {
                px_t npx = {n.x + 1, n.y};
                push(stack, npx);
            }
            if (inside(canvas, color, border_color, n.x, n.y - 1)) {
                px_t npx = {n.x, n.y - 1};
                push(stack, npx);
            }
            if (inside(canvas, color, border_color, n.x, n.y + 1)) {
                px_t npx = {n.x, n.y + 1};
                push(stack, npx);
            }
        }
    }
    free_stack(stack);
    return 0;
}