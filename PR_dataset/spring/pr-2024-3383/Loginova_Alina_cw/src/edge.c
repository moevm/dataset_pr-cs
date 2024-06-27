//
// Created by zoomie on 5/21/24.
//

#include "edge.h"
#include <png.h>
#include "image_data.h"
#include "arrays.h"
#include <stdlib.h>
#include <string.h>

#define STEPS_NUM 8

pixel_point pop_first_element(Array_pixel_point *arr) {
//    for (int i = 0; i < arr->size; ++i)
//        if (arr->arr[i].x == element.x && arr->arr[i].y == element.y) {
//            memmove(&arr->arr[i], &arr->arr[i + 1], (arr->size-- - 1 - i) * sizeof (pixel_point));
//            break;
//        }
    if (!arr->size)
        exit(40);
    pixel_point ret = arr->arr[0];
    memmove(&arr->arr[0], &arr->arr[1], (--arr->size) * sizeof (pixel_point));
    return ret;
}

//void print_int_arr(Array_int arr) {
//    for (int i = 0; i < arr.size; ++i)
//        printf("%d ", arr.arr[i]);
//    printf("\n");
//}

int compare(const void *a, const void *b) {
    const pixel_point *p_a = (const pixel_point*)a;
    const pixel_point *p_b = (const pixel_point*)b;

    if(p_a->x < p_b->x)
        return -1;
    else if(p_a->x > p_b->x)
        return 1;
    else {
        if(p_a->y < p_b->y)
            return -1;
        else if(p_a->y > p_b->y)
            return 1;
        else
            return 0;
    }
}

png_bytepp edge(image_data image, pixel figure_color, pixel edge_color) {
    Array_pixel_point queue = create_pixel_point_array(NULL),
                      visited = create_pixel_point_array(NULL);

    const pixel_point steps[STEPS_NUM] = {
            {-1, -1},
            {-1,  0},
            {-1,  1},
            { 0, -1},
            { 0,  1},
            { 1, -1},
            { 1,  0},
            { 1,  1},
    };

    for(long i = 0; i < image.height; i++) {
        for(long j = 0; j < image.width; j++) {
            if (!memcmp(&image.rows[i][j], &figure_color, sizeof (char) * 3))
//            if(image.rows[i][j].R == figure_color.R
//                && image.rows[i][j].G == figure_color.G
//                && image.rows[i][j].B == figure_color.B)
            {
                pixel_point p = {j, i};
                add_pixel_point_element(&queue, p);
                goto found;
            }
        }
    }
    found:
    while (queue.size) {
        pixel_point point = pop_first_element(&queue);
        for (int i = 0; i < STEPS_NUM; ++i) {
            pixel_point step = { point.x + steps[i].x, point.y + steps[i]. y};
            if (step.x >= 0 && step.x < image.width && step.y >= 0 && step.y < image.height) {
                pixel* pix = &(image.rows[step.y][step.x]);
//                if (pix->R != figure_color.R || pix->G != figure_color.G || pix->B != figure_color.B) {
                if (memcmp(pix, &figure_color, sizeof (char) * 3)) {
                    *pix = edge_color;
                } else if (!bsearch(&step, visited.arr, visited.size, sizeof (pixel_point), compare)
                            && !bsearch(&step, queue.arr, queue.size, sizeof (pixel_point), compare)) {
                    // оптимизация -> добавляем в очередь только пиксели рядом с границей
                    for (int j = 0; j < STEPS_NUM; ++j) {
                        pixel_point step_temp = { point.x + steps[j].x, point.y + steps[j]. y};
                        if (step_temp.x >= 0 && step_temp.x < image.width && step_temp.y >= 0 && step_temp.y < image.height) {
                            pixel* pix_temp = &(image.rows[step_temp.y][step_temp.x]);
//                            if (pix_temp->R != figure_color.R || pix_temp->G != figure_color.G || pix_temp->B != figure_color.B) {
                            if (memcmp(pix_temp, &figure_color, sizeof (char) * 3)) {
                                add_pixel_point_element(&queue, step);
                                qsort(queue.arr, queue.size, sizeof(pixel_point), compare);
                            }
                        }
                    }
                }
            }
        }
        add_pixel_point_element(&visited, point);
        qsort(visited.arr, visited.size, sizeof (pixel_point), compare);
    }

    clear_pixel_point_array(&queue);
    clear_pixel_point_array(&visited);

    return (png_bytepp)image.rows;
}

