/*
 * b2bview.cpp
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#include "b2bview.h"

Building_BuildingView::Building_BuildingView(BuildingView *buildingView1, BuildingView *buildingView2):buildingView1(buildingView1),buildingView2(buildingView2)
{
    b2b = new Building_Building(buildingView1->getBuilding(), buildingView2->getBuilding());
}

/**
 * @brief Building_BuildingView::getLine
 * @return
 * calculate the optimate line between 2 buildings
 * draw 2 lines on building 1 :
 *
 *          B
 *
 *   \ topBottom   /
 *    \ __________/
 *    |\         /|
 *    | \       / |
 *    |  \  1  /  |
 *    |   \   /   |
 *    |    \ /    |      ___________
 * D  |     /     |  A  |           |
 *    |    / \    |     |           |
 *    |   /   \   |     |           |
 *    |  /     \  |     |           |
 *    | /       \ |     |           |
 *    |/_________\|     |    2      |
 *    /           \     |           |
 *   / bottomTop   \    |           |
 *                      |           |
 *          C           |           |
 *                      |___________|
 *
 */
QLine Building_BuildingView::getLine() const
{
    QLine line;

    // calculate of each equation:
    // topBottom : y = topBottoma * x + topBottomb
    // bottomTop : y = bottomTopa * x + bottomTopb
    float topBottoma = float(buildingView1->bottomRight().y()-buildingView1->topLeft().y())/float(buildingView1->bottomRight().x()- buildingView1->topLeft().x());
    float topBottomb = buildingView1->topLeft().y()-topBottoma*buildingView1->topLeft().x();
    float bottomTopa = float(buildingView1->topRight().y()-buildingView1->bottomLeft().y())/float(buildingView1->topRight().x()- buildingView1->bottomLeft().x());
    float bottomTopb = buildingView1->bottomLeft().y()-bottomTopa*buildingView1->bottomLeft().x();

    // calculate coordonate of the top/left point of building 2 named left2
    int left2x = buildingView2->topLeft().x();
    int left2y = buildingView2->topLeft().y();

    // if left2 if above topBottom
    if(left2y < topBottoma * left2x + topBottomb)
    {
        // calculate coordonate of the top/right point of the building 2 named right2
        int right2x = buildingView2->topRight().x();
        int right2y = buildingView2->topRight().y();

        // if right2 is under bottomTop
        if(right2x > (right2y-bottomTopb)/bottomTopa)
        {
            // case A
            line.setPoints(buildingView1->getMidRight(),buildingView2->getMidLeft());
        }
        else
        {   // case B
            line.setPoints(buildingView1->getMidTop(), buildingView2->getMidBottom());
        }
    }
    else
    {
        // calculate coordonate of the bottom/right point of the building 2 named right2
        int right2x = buildingView2->bottomRight().x();
        int right2y = buildingView2->bottomRight().y();

        // if right2 is under bottomTop
        if(right2x > (right2y-bottomTopb)/bottomTopa)
        {
            // case C
            line.setPoints(buildingView1->getMidBottom(),buildingView2->getMidTop());
        }
        else
        {
            // case D
            line.setPoints(buildingView1->getMidLeft(), buildingView2->getMidRight());
        }
    }
    return line;
}
