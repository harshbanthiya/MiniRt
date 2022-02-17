#include "structs.h"

/* 
    To see if we hit something we will solve a system of equations 
    1. The straight line equation is y = mx + b 
    2. The equation of a circle (x - a)2 + (y - b)2 = r2 // the two outside the bracket is squared and does not mean multiply by 2
    therefore for a circle at (2, 3) with radius 1 
    we will have 
    1. y = x + 1;
    2. (x - 2)2 + (y - 3)2 = 1; // the two outside the bracket is squared and does not mean multiply by 2
*/

/* 
    Lets presume the origin at lower left corner of the screen 
    if the center of the circle is at point C
    and there is a point P on the circle 
    Then the vector CP is the radius
    CP * CP will be r squared
    Now CP is can be substituted as (Vector P - Vector C)
    Therefor (P - C) * (P - C) = r squared
    Similarly we can substitute P as P(t) making (P(t) - C) * (P(t) - C) = r squared
    expanding further gives as (O + tD - C) * (O + tD - C) = r squared
    On further expansion, we get the quadratic equation form a(t squared) + bt + c = 0;
    which can be solved using the quadratic formula. Depending on the solution being 0 || 1 || 2 
    we will know how many intersection points we have
*/

/*  The function set_face_normal helps in considering the case where the sphere surrounds the camera. 
    if the camera is inside he sphere, the ray , the normal will point in the same direction, however 
    to calculate the interaction between the object and the light source, the normal and ray must point in 
    opposite directions. So we need this function to check whether the normal is in infact in the opposite
    direction of the ray
*/

void    set_face_normal(t_ray *r, t_hit_record *rec)
{
    /*  if the dot product of the direction vector and normal vector of intersection is negative 
        the ray hits in front of the object
    */
   rec->front_face = vdot(r->dir, rec->normal) < 0;
   /*
        if the ray is hit from the from side of the ray as it is, otherwise reverse the normal. 
        (To always use ray direction and normal vector as opposite)
    */
    rec->normal = (rec->front_face) ? rec->normal : vmult_(rec->normal, -1);
}

bool    hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_vec3  oc; // center of the sphere as a direction vector
    // a b c are coefficients of the quadratic equation with respect to t
    double  a;
    double  half_b; //changed b to half b
    double  c;
    double  discriminant;
    double  sqrtd;
    double  root;
    t_sphere *sp;

    sp = (t_sphere *)world->element;
    oc = vminus(ray->orig, sp->center);
    /*
    a = vdot(ray->dir, ray->dir);
    b = 2.0 * vdot(oc, ray->dir);
    c = vdot(oc, oc) - sp->radius2;
    discriminant = b * b - 4 * a * c;
    // when discriminant is less than 0: no real root
    if (discriminant < 0)
        return (-1.0);
    else 
        return ((-b - sqrt(discriminant)) / ( 2.0 * a)); // smaller of two roots as per quad equation
    */
    a = vlength2(ray->dir);
    half_b = vdot(oc, ray->dir);
    c = vlength2(oc) - sp->radius2;
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return (false);
    sqrtd = sqrt(discriminant);
    // check if there is a root between tmin and tmax among the two real roots(t), starting with the smallest root
    root = (-half_b - sqrtd) / a;
    if (root < rec->tmin || rec->tmax < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < rec->tmin || rec->tmax < root)
            return (false);
    }
    rec->t = root;
    rec->p = ray_at(ray, root);
    rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // Normalised normal vector
    set_face_normal(ray, rec); // compare normal vec with dir vec of ray and store it as bool it is in front or back
    rec->albedo = world->albedo;
    return (true);

}

// Now that we know the intersection of sphere, the ray and the centre of sphere 
// We can easily find the normal vector, the normalised normal cna be obtained by substracting the center 
// from the intersection and dividing by the radius of the sphere
// Directly making the colour change for normal in ray_color function 

// _______________________________________________

/* 
    Currently the hit sphere returns a value corresponding to the distance between the origin of the 
    Primary Ray and its intersection 

    But we need more information, to trace the ray and render the image. 
    
    First we need the exact location of the intersection.
        We the exact location of intersection to know the normal vector at intersection, 
        and we need the normal vector to calculate the effect of light source on the object. 
    
    Therefore we need a new structure. To record the hits. Check the structs.h for hit records 
*/

//________________________________________________________________

/*
    The function hit iterates through each object and checks whether the ray is hit, we have to hit the object
    that is closer when there are multiple objects. Therefore, when certain object is hit, tmax is changed to hit t
    and when examining the next object, it is not hit if it is farther object. 
*/

bool    hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
    bool            hit_anything;
    t_hit_record    temp_rec;

    temp_rec = *rec; // Just to initialize the tmin and tmax values of temp_rec
    hit_anything = false;
    while (world)
    {
        if (hit_obj(world, ray, &temp_rec))
        {
            hit_anything = true;
            temp_rec.tmax = temp_rec.t; // when we hit a closer object when multiple objs, it is isnt considered hit for further objects there. 
            *rec = temp_rec;
        }
        world = world->next;
    }
    return (hit_anything);
}

bool    hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
    bool  hit_result;

    hit_result = false;
    if (world->type == SP)
        hit_result = hit_sphere(world, ray, rec);
    return (hit_result);
}
