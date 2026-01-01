#ifndef __COLOR__
    #define __COLOR__

    namespace gl{
        class Color{
            public:
                Color(float r, float g, float b, float a);
                float   r = 0.0f,
                        g = 0.0f,
                        b = 0.0f,
                        a = 0.0f;
        };
    };

#endif