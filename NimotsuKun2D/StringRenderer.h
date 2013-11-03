#pragma once

#include "image.h"

class StringRenderer
{
public:
    static StringRenderer& instance();
    void draw(std::string text, int x=0, int y=0);

private:
    StringRenderer();

private:
    Image image;
};
