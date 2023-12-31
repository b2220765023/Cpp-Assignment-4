#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    void displayPreOrderHelper(Sector* root);
    void displayInOrderHelper(Sector *root);
    void displayPostOrderHelper(Sector *root);
    bool findStellarPath(Sector *current, const std::string &target_sector_code, std::vector<Sector *> &path);
    Sector *findMin(Sector *node) const;
    Sector *deleteSectorHelper(Sector *current, const std::string &sector_code);



    void clearMemory(Sector *pSector);

    Sector *insertRecursive(Sector *current, Sector *newSector);

    bool findDeletingSector(const std::string &sector_code, Sector *current, std::vector<Sector *> &path) const;

    Sector *connectNodes(Sector *pSector, Sector *pSector1);

    void replaceNodeInParent(const std::vector<Sector *> &path, Sector *nodeToReplace, Sector *replacement);

    void replaceNodeWithInOrderSuccessor(Sector *nodeToReplace, Sector *inOrderSuccessor);
};

#endif // SPACESECTORBST_H
