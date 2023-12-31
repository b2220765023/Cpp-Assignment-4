#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    Sector *insertRecursive(Sector *current, Sector *newSector);

    bool isRed(Sector *node) const;

    Sector *rotateLeft(Sector *h);

    Sector *rotateRight(Sector *h);

    void flipColors(Sector *h);

    void inOrderTraversal(Sector *node);

    void preOrderTraversal(Sector *node);

    void postOrderTraversal(Sector *node);


    bool findStellarPath(Sector *current, const std::string &target_sector_code, std::vector<Sector *> &path);

    void clearMemory(Sector *pSector);
};

#endif // SPACESECTORLLRBT_H
