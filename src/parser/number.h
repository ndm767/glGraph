#pragma once

class Number{
public:
    Number();
    Number(int wholeComponent, int decComponent);
    Number(float number);
    ~Number();

    float getAsFloat();
protected:
    int whole;
    int dec;
};
