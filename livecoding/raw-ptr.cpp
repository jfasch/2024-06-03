#include <iostream>
#include <memory>

struct HaufenZeug
{
    HaufenZeug(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

void funktion(std::shared_ptr<HaufenZeug> raw)
{
    std::cout << raw->x << ',' << raw->y << std::endl;
}

int main()
{
    std::shared_ptr<HaufenZeug> mein_zeug(new HaufenZeug(1,2));

    funktion(mein_zeug);

    std::cout << mein_zeug->x << ',' << mein_zeug->y << std::endl;
    
    return 0;
}
