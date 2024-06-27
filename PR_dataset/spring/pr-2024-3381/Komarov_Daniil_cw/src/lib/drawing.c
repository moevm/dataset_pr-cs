#include "../include/drawing.h"

#define clip(value, min, max) ( \
    (value < min) ? min : ((value > max) ? max : value) \
)

#define min(a, b) ((a <= b) ? a : b)
#define max(a, b) ((a >  b) ? a : b)


// --------------------------------------------------------
// HIGH-LEVEL FUNCTIONS
// There are high-level drawing functions below
// --------------------------------------------------------

// This function draws enclosed polygon by vertices array
// Note: to draw solid polygon without outline pass same colors
//       to color and fill_color, fill=1
//
// Arguments:
// img - image to draw in
// coords - vertices of polygon in format [x0, y0, x1, y1 ... x_n, y_n]
// vertices_count - amount of vertices in polygon
// outline_thickness - polygon outline thickness
// color - polygon outline color
// fill - bool flag
// fill_color - polygon fill color, used if fill=1
void draw_polygon(Image *img, int64_t *coords, size_t vertices_count,
                  int64_t outline_thickness, Pixel color,
                  uint8_t fill, Pixel fill_color)
{
    // Draw infill using Scan-line polygon fill algorithm
    // Good guide for that algorithm:
    // https://www.cs.rit.edu/~icss571/filling/index.html
    if(fill)
    {
        // global edges array will store all edges of the polygon
        // except horizontal ones
        // filling all edges array
        struct edge_node *edges = (struct edge_node *)
            malloc(sizeof(struct edge_node) * vertices_count);
        size_t edges_count = 0;
        int64_t y_min = coords[1];
        int64_t y_max = coords[1];
        for(size_t i = 0; i < vertices_count; i++)
        {
            int64_t x0, x1, y0, y1;
            x0 = coords[i*2];
            y0 = coords[i*2+1];
            // last edge is (last point, first point)
            if(i == vertices_count - 1)
            {
                x1 = coords[0];
                y1 = coords[1];
            }
            else
            {
                x1 = coords[(i+1)*2];
                y1 = coords[(i+1)*2+1];
            }
            y_min = min(y0, y_min);
            y_max = max(y0, y_max);
            // Skip horizontal edges
            if(y0 == y1) continue;
            
            edges[edges_count].y_min = min(y0, y1);
            edges[edges_count].y_max = max(y0, y1);
            edges[edges_count].x_val =
                (edges[edges_count].y_min == y0) ? x0 : x1;
            edges[edges_count].m = ((double)x1 - (double)x0) /
                                       ((double)y1 - (double)y0);
            edges[edges_count].active = 1;
            edges_count++;

        }
        edges = (struct edge_node *)realloc(edges,
            sizeof(struct edge_node) * edges_count);
        
        // Disabling all active edges for now
        for(size_t i = 0; i < edges_count; i++)
        {
            edges[i].active = 0;
        }

        // Scan line is iterated from y_min of polygon to y_max
        for(int64_t scan_line = y_min;
            scan_line <= min(y_max, img->height-1);
            scan_line++)
        {
            // Add to active edges all edges, that has y_min == scan_line
            // Remove from active all edges, that has y_max == scan_line
            size_t active_edges_count = 0;
            for(size_t i = 0; i < edges_count; i++)
            {
                if(edges[i].y_min == scan_line) edges[i].active = 1;
                else if(edges[i].y_max == scan_line) edges[i].active = 0;
                if(edges[i].active) active_edges_count++;
            }
            // Sorting edges by y_min ascending, if y_min are equal, by x_val
            // Not active edges places at the end
            qsort(edges, edges_count, sizeof(struct edge_node), edge_node_cmp);
            // Scanning x with parity (only active edges)
            // and incrementing x_val after it
            uint8_t parity = 0;
            int64_t draw_from = 0;
            for(size_t i = 0; i < active_edges_count; i++)
            {
                parity = !parity;
                if(parity)
                {
                    draw_from = round(edges[i].x_val);
                    edges[i].x_val += edges[i].m;
                }
                else
                {
                    int64_t draw_to = round(edges[i].x_val);
                    edges[i].x_val += edges[i].m;
                    // At this point we have coordinates of vertical line
                    // to draw but this line may lay not in img
                    if(scan_line < 0) continue;
                    // scan_line max value is already limited
                    if(draw_from < 0 && draw_to < 0) continue;
                    if(draw_from > img->width-1 &&
                       draw_to   > img->width-1) continue;
                    
                    uint32_t draw_x0 = clip(draw_from, 0, img->width-1);
                    uint32_t draw_x1 = clip(draw_to,   0, img->width-1);
                    for(uint32_t x = draw_x0; x <= draw_x1; x++)
                    {
                        img->arr[(uint32_t)scan_line][x] = fill_color;
                    }
                }
            }
        }
        free(edges);
    }

        // Draw outline
    for(size_t i = 0; i < vertices_count; i++)
    {
        int64_t x0, x1, y0, y1;
        x0 = coords[i*2];
        y0 = coords[i*2+1];
        // last edge is (last point, first point)
        if(i == vertices_count - 1)
        {
            x1 = coords[0];
            y1 = coords[1];
        }
        else
        {
            x1 = coords[(i+1)*2];
            y1 = coords[(i+1)*2+1];
        }

        draw_line(img, x0, x1, y0, y1, outline_thickness, color);
    }

    // Draw filled circles at vertices if thickness is large
    // to avoid showing "non-colliding" sharp-ended lines
    if(outline_thickness > 2)
    {
        for(size_t i = 0; i < vertices_count; i++)
        {
            int64_t x0, y0;
            x0 = coords[i*2];
            y0 = coords[i*2+1];
            draw_circle(img, x0, y0, (outline_thickness-1)/2,
                color, 1, 1, color);
        }
    }
}


// This function draws circle by center point and radius
//
// Arguments:
// img - image to draw in
// x0 - center point X
// y0 - center point Y
// r - circle radius
// outline_color - circle outline color
// thickness - circle outline thickness
// fill - bool flag
// fill_color - polygon fill color, used if fill=1
void draw_circle(Image *img, int64_t x0, int64_t y0,
                 int64_t r, Pixel outline_color, int64_t thickness,
                 uint8_t fill, Pixel fill_color)
{
    // Circle equation: x^2 + y^2 = r^2
    // Let's iterate over x from 0 to r/2 and calculate
    // positive y values. This will five 1/8 of a circle
    // To create a full circle we can just mirror this part
    if(fill)
    {
        for(double r_i = r; r_i >= 1; r_i -= 0.5)
        {
            uint64_t r_sq = r_i*r_i;
            for(uint32_t x = 0; x <= round(sqrt(r_sq/2.0)); x++)
            {
                uint32_t y = round(sqrt(r_sq - x*x));
                if(x0+x > 0 && x0+x < img->width &&
                   y0+y > 0 && y0+y < img->height)
                        img->arr[y0+y][x0+x] = fill_color;
                
                if(x0+x > 0 && x0+x < img->width &&
                   y0-y > 0 && y0-y < img->height)
                        img->arr[y0-y][x0+x] = fill_color;
                
                if(x0-x > 0 && x0-x < img->width &&
                   y0+y > 0 && y0+y < img->height)
                        img->arr[y0+y][x0-x] = fill_color;
                
                if(x0-x > 0 && x0-x < img->width &&
                   y0-y > 0 && y0-y < img->height)
                        img->arr[y0-y][x0-x] = fill_color;
                
                if(x0+y > 0 && x0+y < img->width &&
                   y0+x > 0 && y0+x < img->height)
                        img->arr[y0+x][x0+y] = fill_color;
                
                if(x0+y > 0 && x0+y < img->width &&
                   y0-x > 0 && y0-x < img->height)
                        img->arr[y0-x][x0+y] = fill_color;
                
                if(x0-y > 0 && x0-y < img->width &&
                   y0+x > 0 && y0+x < img->height)
                        img->arr[y0+x][x0-y] = fill_color;
                
                if(x0-y > 0 && x0-y < img->width &&
                   y0-x > 0 && y0-x < img->height)
                        img->arr[y0-x][x0-y] = fill_color;
            }
        }
        if(x0 > 0 && x0 < img->width &&
           y0 > 0 && y0 < img->height)
                img->arr[y0][x0] = fill_color;
    }
    
    for(double r_i = r+(thickness-1)/2.0;
        r_i >= r-(thickness-1)/2.0;
        r_i -= 0.5)
    {
        uint64_t r_sq = r_i*r_i;
        for(uint32_t x = 0; x <= round(sqrt(r_sq/2.0)); x++)
        {
            uint32_t y = round(sqrt(r_sq - x*x));
                if(x0+x > 0 && x0+x < img->width &&
                   y0+y > 0 && y0+y < img->height)
                        img->arr[y0+y][x0+x] = outline_color;
                
                if(x0+x > 0 && x0+x < img->width &&
                   y0-y > 0 && y0-y < img->height)
                        img->arr[y0-y][x0+x] = outline_color;
                
                if(x0-x > 0 && x0-x < img->width &&
                   y0+y > 0 && y0+y < img->height)
                        img->arr[y0+y][x0-x] = outline_color;
                
                if(x0-x > 0 && x0-x < img->width &&
                   y0-y > 0 && y0-y < img->height)
                        img->arr[y0-y][x0-x] = outline_color;
                
                if(x0+y > 0 && x0+y < img->width &&
                   y0+x > 0 && y0+x < img->height)
                        img->arr[y0+x][x0+y] = outline_color;
                
                if(x0+y > 0 && x0+y < img->width &&
                   y0-x > 0 && y0-x < img->height)
                        img->arr[y0-x][x0+y] = outline_color;
                
                if(x0-y > 0 && x0-y < img->width &&
                   y0+x > 0 && y0+x < img->height)
                        img->arr[y0+x][x0-y] = outline_color;
                
                if(x0-y > 0 && x0-y < img->width &&
                   y0-x > 0 && y0-x < img->height)
                        img->arr[y0-x][x0-y] = outline_color;
        }
    }
}


// This functions flood fills region with selected color from start point
// Note: if memory allocation error occurs, function will call handle_error()
//       from "errors.h" and exit, no status code returned
//
// Arguments:
// img - image to draw in
// x_start - start point X
// y_start - start point Y
// color - color to fill with
void flood_fill_region(Image *img, uint32_t x_start, uint32_t y_start,
                       Pixel color)
{
    // Using flood fill on stack
    CoordQueue *q = coordqueue_new();
    if(q == NULL) return;

    int status_code;
    coordqueue_push(q, x_start, y_start, &status_code);
    if(handle_error(status_code)) return;
    
    Pixel old_color = img->arr[y_start][x_start];

    while(coordqueue_len(q))
    {
        uint32_t x, y;
        coordqueue_pop(q, &x, &y);

        if(img->arr[y][x].r == old_color.r &&
           img->arr[y][x].g == old_color.g &&
           img->arr[y][x].b == old_color.b &&
           img->arr[y][x].a == old_color.a)
        {
            img->arr[y][x] = color;
            if(y != 0) // North
            {
                coordqueue_push(q, x, y-1, &status_code);
                if(handle_error(status_code))
                {
                    coordqueue_destroy(q);
                    return;
                }
            }
            if(x != 0) // West
            {
                coordqueue_push(q, x-1, y, &status_code);
                if(handle_error(status_code))
                {
                    coordqueue_destroy(q);
                    return;
                }
            }
            if(y != img->height-1) // South
            {
                coordqueue_push(q, x, y+1, &status_code);
                if(handle_error(status_code))
                {
                    coordqueue_destroy(q);
                    return;
                }
            }
            if(x != img->width-1) // East
            {
                coordqueue_push(q, x+1, y, &status_code);
                if(handle_error(status_code))
                {
                    coordqueue_destroy(q);
                    return;
                }
            }
        }
    }
    coordqueue_destroy(q);
}


// This function draws line between two points
//
// Arguments:
// img - image to draw in
// x0_arg - first point X
// x1_arg - second point X
// y0_arg - first point Y
// y1_arg - second point Y
// thickness - line thickness
// color - line color
void draw_line(Image *img, int64_t x0_arg, int64_t x1_arg, int64_t y0_arg,
               int64_t y1_arg, int64_t thickness, Pixel color)
{
    // First of all, let's declare that x0 always less or eq to x1
    int64_t x0, y0, x1, y1;
    x0 = min(x0_arg, x1_arg);
    if(x0 == x0_arg) {
        x1 = x1_arg;
        y0 = y0_arg;
        y1 = y1_arg;
    }
    else {
        x1 = x0_arg;
        y0 = y1_arg;
        y1 = y0_arg;
    }
    
    if(x0 == x1) {
        if(y0 == y1) { // That's a point
            // Check borders
            if(x0 < 0 || y0 < 0 || x0 > img->width-1 || y0 > img->height-1)
            {
                return;
            }
            img->arr[y0][x0] = color;
        }
        else { // That's a vertical line
            uint32_t y_start = clip(y0, 0, img->height);
            uint32_t y_stop  = clip(y1, 0, img->height);
            // x_cur varies from "left" to "right" to achieve thickness
            // if the thickness is even, than line will be shifted to the left by one pixel
            uint32_t x_start = x0 - thickness/2;
            uint32_t x_stop  = x_start + thickness;
            for(uint32_t x_cur = x_start; x_cur != x_stop; x_cur++) {
                // Skip column if outside the picture
                if(x_cur < 0 || x_cur > img->width-1) continue;
                for(uint32_t y_cur = y_start; y_cur != y_stop; y_cur += (y_start < y_stop) ? 1 : -1) {
                    img->arr[y_cur][x_cur] = color;
                }
            }
        }
    }
    else if(y0 == y1) { // That's a horizontal line
        uint32_t x_start = clip(x0, 0, img->width);
        uint32_t x_stop  = clip(x1, 0, img->width);
        // x_cur varies from "left" to "right" to achieve thickness
        // if the thickness is even, than line will be shifted to the left by one pixel
        uint32_t y_start = y0 - thickness/2;
        uint32_t y_stop  = y_start + thickness;
        for(uint32_t y_cur = y_start; y_cur != y_stop; y_cur++) {
            // Skip line if outside the picture
            if(y_cur < 0 || y_cur > img->height-1) continue;
            for(uint32_t x_cur = x_start; x_cur != x_stop; x_cur += (x_start < x_stop) ? 1 : -1) {
                    img->arr[y_cur][x_cur] = color;
            }
        }
    }
    else { // That's a slanted line
        // Step 1. Let's find line equation in format y = a*x + b.
        // a = delta_y / delta_x
        // b = y0 - a*x0
        double a = ((double)y1 - (double)y0) / ((double)x1 - (double)x0);

        // Step 2. Let's find perpendicular line equation in format y_p = a_p*x + b_p
        // This equation (y_p) draws line that goes through (x0, y0)
        // "a_p" is inverse to "a" like:
        double a_p = -1 / a;
        // b_p0 is calculated to go through point (x0, y0)
        double b_p0 = (double)y0 - a_p * (double)x0;

        //printf("Main line: {%ld <= x <= %ld} y=%lfx\n", x0, x1, a);
        //printf("P1 line: y=%lfx + %lf\n", a_p, b_p0);
        // As we all know, distance between points is sqrt(delta_x^2 + delta_y^2)
        // So let's find out how much we need to change the x coordinate to move point along perpendicular for exact one pixel
        // sqrt(delta_x^2 + delta_y^2) = 1 => delta_x = 1 / sqrt(1+a_p^2)
        double target_move_x = 1 / sqrt(1 + a_p * a_p);

        // Step 3. Now let's "move" our "main" line up and down to reach target thickness
        // Lets' move it around for one pixel distance at time starting from "max left" and until "max right"
        // Max move is thickness / 2, leaving 1 pixel for "main" line
        double max_move = target_move_x * ((double)thickness-1) / 2;
        // printf("Max move: %lf\n", max_move);
        for(double x0_cur = x0 - max_move; x0_cur <= x0 + max_move; x0_cur += (target_move_x/2)) {
            // (x0_cur, y0_cur) is a start point for "sub" line
            double y0_cur = a_p * x0_cur + b_p0;
        
            // printf("Point: (%lf, %lf)\n", x0_cur, y0_cur);

            // x1_cur is an end point X for "sub" line
            double x1_cur = x1 + (x0_cur - x0);

            // this is "sub" line equation itself:
            // {y = a*x + b_cur; x0_cur <= x <= x1_cur}
            double b_cur = y0_cur - a * x0_cur;
            //printf("Sub line: {%lf <= x <= %lf} y = %lfx + %lf\n", x0_cur, x1_cur, a, b_cur);

            // Let's trim x start/stop to fit image dims
            int64_t sub_x_start = clip(x0_cur, 0, img->width-1);
            int64_t sub_x_stop  = clip(x1_cur, 0, img->width-1);

            // Now it's time to draw "sub" line
            interpolate_line(img, a, b_cur, sub_x_start, sub_x_stop, color);
        }
    }
}


// This function draws filled rectangle by angle points
// Note: draw_polygon() can be used, but this is optimized version
//
// Arguments:
// img - image to draw in
// x0, y0 - left top angle of the rectangle coords
// x1, y1 - right bottom angle of the rectangle coords
// color - polygon outline color
void draw_rectangle(Image *img, int64_t x0, int64_t y0, int64_t x1,
                    int64_t y1, Pixel color)
{
    for(int64_t y = y0; y <= y1; y++)
    {
        // Do not scan rows outside the image
        if(y < 0) continue;
        if(y >= img->height) break;

        for(int64_t x = x0; x <= x1; x++)
        {
            if(x < 0) continue;
            if(x >= img->width) break;

            img->arr[y][x] = color;
        }
    }
}

// --------------------------------------------------------
// LOW-LEVEL FUNCTIONS
// Do not call directly
// --------------------------------------------------------

// Draw "thin" one-pixel width line between coords
// Warning: this function shouldn't be used directly
// Use draw_line() instead
//
// This function supports drawbuf
// For more information please refer to draw_line() description
void interpolate_line(Image *img, double a, double b, int64_t x_start,
                      int64_t x_end, Pixel color)
{
    // There're two different options:
    // 1) Interpolate along X
    // 2) Interpolate along Y
    // If "a" is greater than 1.0, program must use 2), because else
    // resulting line will have gaps
    if(fabs(a) <= 1.0)
    {
        uint8_t drawed = 0;
        for(uint32_t x = x_start; x <= x_end; x++) {
            double y = a * x + b;
            uint32_t y_rounded = round(y);
            if(y_rounded >= 0 && y_rounded < img->height) {
                drawed = 1;
                img->arr[y_rounded][x] = color;
            }
            else if(drawed) {
                // If we've already drawn some pixels and now
                // point is outside of the picture, it's definitely no
                // pixels to draw on next iterations due to linearity of equation
                break;
            }
        }
    }
    else
    {
        int64_t y_v1 = round(a*x_start + b);
        int64_t y_v2 = round(a*x_end   + b);
        //printf("Ystart: %ld, Ystop: %ld\n", y_v1, y_v2);
        uint32_t y_start = clip(min(y_v1, y_v2), 0, img->height-1);
        uint32_t y_end   = clip(max(y_v1, y_v2), 0, img->height-1);
        uint8_t drawed = 0;
        for(uint32_t y = y_start; y <= y_end; y++) {
            // Reverse formula
            // y = a*x + b => x = (y - b)/a
            double x = (y - b)/a;
            uint32_t x_rounded = round(x);
            if(x_rounded >= 0 && x_rounded < img->width) {
                drawed = 1;
                img->arr[y][x_rounded] = color;
            }
            else if(drawed) {
                // If we've already drawn some pixels and now
                // point is outside of the picture, it's definitely no
                // pixels to draw on next iterations due to linearity of equation
                break;
            }
        }
    }
}

// This comparator used for scan-line fill algorithm
int edge_node_cmp(const void *a_ptr, const void *b_ptr)
{
    struct edge_node a = *(struct edge_node *)a_ptr;
    struct edge_node b = *(struct edge_node *)b_ptr;

    if(!a.active && b.active) return 1;
    else if(a.active && !b.active) return -1;
    else if(!a.active && !b.active) return 0;

    if(a.x_val > b.x_val) return 1;
    else if(a.x_val < b.x_val) return -1;
    else return 0;
}
