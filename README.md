# MiniRt
A simple Ray Tracer written in C

PSEUDO CODE
    BASIC RAY TRACING ALGO 

    For each pixel of the screen
    {
        final color = 0;
        ray = {starting point, directio}
        repeat
        {
            for each object in the scene
            {
                determine the closest ray object/intersection
            }
            if intersection exists
            {
                for each light in the scene
                {
                    if the light is not the shadow of another object
                    {
                        add this light contribution to computed color
                    }
                }
            }
            final color = final color + computed color * previous reflection factor
            reflection factor = reflection factor * surface reflection property
            increment depth;
        }until refection factor is 0 or maximum depth is reached
    }
