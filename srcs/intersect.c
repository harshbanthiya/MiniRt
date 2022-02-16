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

double    hit_sphere(t_sphere *sp, t_ray *ray)
{
    t_vec3  oc; // center of the sphere as a direction vector
    // a b c are coefficients of the quadratic equation with respect to t
    double  a;
    double  b;
    double  c;
    double  discriminant;

    oc = vminus(ray->orig, sp->center);
    a = vdot(ray->dir, ray->dir);
    b = 2.0 * vdot(oc, ray->dir);
    c = vdot(oc, oc) - sp->radius2;

    discriminant = b * b - 4 * a * c;
    // when discriminant is less than 0: no real root
    if (discriminant < 0)
        return (-1.0);
    else 
        return ((-b - sqrt(discriminant)) / ( 2.0 * a)); // smaller of two roots as per quad equation
}

// Now that we know the intersection of sphere, the ray and the centre of sphere 
// We can easily find the normal vector, the normalised normal cna be obtained by substracting the center 
// from the intersection and dividing by the radius of the sphere
// Directly making the colour change for normal in ray_color function 