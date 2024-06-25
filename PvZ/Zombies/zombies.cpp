    //#include "../Plants/PlantFactory.h"


    //void Zombie::handleCollision(PlantFactory& pFactory, pGrid& pzGrid) {
    //    int xPos = positionZ.x;
    //    int yPos = positionZ.y;

    //    int xcell = ((xPos - 188) / 92);
    //    int ycell = ((yPos - 130) / 109);

    //    if (pzGrid.oGrid[ycell][xcell].plantId == 1 || pzGrid.oGrid[ycell][xcell].plantId == 2) {
    //        // Different speed for different zombies
    //        if (speed == 1)
    //            positionZ.x += 2;
    //        else if (speed == 2)
    //            positionZ.x += 3;

    //        changeTexture(1); // Sets to attack

    //        // Health
    //        if (pFactory.plants[ycell][xcell]->currentHealth > 0)
    //            pFactory.plants[ycell][xcell]->currentHealth -= 1;

    //        cout << "current Health: " << pFactory.plants[ycell][xcell]->currentHealth << endl;

    //        if (pFactory.plants[ycell][xcell]->currentHealth == 0) {
    //            cout << "///////////////////" << endl;
    //            delete pFactory.plants[ycell][xcell];
    //            pFactory.plants[ycell][xcell] = nullptr;
    //            pzGrid.oGrid[ycell][xcell].plantId = 0;
    //            changeTexture(0); // Reset to walk
    //        }
    //    }
    //}
