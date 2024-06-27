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

    bool head;
    bool isEating;
    bool isDead;

    position temp;
    
    Zombie(int x, int y,int life, int speed, int damage): positionZ(x,y), life(life),speed(speed),
        damage(damage) , temp(0,0)
    {

    }
    virtual ~Zombie() {}
    virtual void animation(RenderWindow& window)=0; //pure virtual function
    virtual void changeTexture (int number) {}
    virtual  void refreshAnimation() {};
    //getters
    int getX() const { return positionZ.x; }
    int getY() const { return positionZ.y; }
    int getXBottom() const { return positionZ.xbottom; }
    int getYBottom() const { return positionZ.ybottom; }

    void reducehealth()
    {
        if (life > 2)
        {
            life -= 2;
           
        }
        else
        {
            isDead = true;
           
        }


     }

};


