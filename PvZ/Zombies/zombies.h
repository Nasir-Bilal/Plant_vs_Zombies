#pragma once


using namespace sf;
using namespace std;

struct position
{
    int x;
    int y;
    int xbottom;
    int ybottom;
    position(int x, int y) :x(x),y(y),xbottom(x),ybottom(y+ 144) {}



};

class Zombie {
public:
    int life;
    int speed;
    int damage;
    int textureIndex; //tracks the texture
    string texturePath;
    string tempTexturePath;
    Texture texture;
    Sprite sprite;
    position positionZ;
    Clock animationClock;
    
    Zombie(int x, int y,int life, int speed, int damage): positionZ(x,y), life(life),speed(speed), damage(damage) {}
    virtual ~Zombie() {}
    virtual void animation()=0; //pure virtual function
    virtual void changeTexture (int number) {}

    //getters
    int getX() const { return positionZ.x; }
    int getY() const { return positionZ.y; }
    int getXBottom() const { return positionZ.xbottom; }
    int getYBottom() const { return positionZ.ybottom; }

    void reducehealth()
    {
        life -= 2;

     }
    int getRowIndex()
    {
        int baseY = 130;
        int rowHeight = 109;
        return (positionZ.y - baseY) / rowHeight;
    }

};


