#include<iostream>
#include "Vec2.h"
#include "Game.h"

int main(){
    

    Game g("config.txt");
    g.run();

    // std::cout<<"It Works"<<std::endl;

    // Vec2 v1(2.4f, 4.f);
    // Vec2 v2(2.4f, 4.f);

    // std::cout<<(v1 == v2)<<std::endl;

    // (v1 * v2).print();

return 0;

}