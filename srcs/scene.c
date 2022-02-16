#include "structs.h"

t_canvas    canvas(int width, int height)
{
    t_canvas canvas;

    canvas.width = width;
    canvas.height = height;
    canvas.aspect_ratio = (double) width / (double) height;
    return (canvas);
}

// The number of pixels in canvas is width * height 
// left bottom = (0 - (viewport width / 2), 0 - (viewport height / 2), 0 - focal length)

t_camera    camera(t_canvas *canvas, t_point3 orig)
{
    t_camera    cam;
    double      focal_len;
    double      viewport_height;

    viewport_height = 2.0;
    focal_len = 1.0;
    cam.orig = orig;
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = vec3(cam.viewport_w, 0, 0);
    cam.vertical = vec3(0, cam.viewport_h, 0);
    cam.lower_left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
                                        vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
    return (cam);
}

t_object    *object(t_object_type type, void *element)
{
    t_object    *new;

    if (!(new = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    new->type = type;
    new->element = element;
    new->next = NULL;
    return (new);
}

// sphere constructor

t_sphere    *sphere(t_point3 center, double radius)
{
    t_sphere    *sp;

    if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->center = center;
    sp->radius = radius;
    sp->radius2 = radius * radius;
    
    return (sp);
}