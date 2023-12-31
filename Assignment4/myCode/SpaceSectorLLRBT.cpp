#include "SpaceSectorLLRBT.h"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
    std::ifstream inputFile(filename);
    std::string line;

    // Ignore the first line
    std::getline(inputFile, line);

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int x, y, z;
        char comma;

        if (!(iss >> x >> comma >> y >> comma >> z)) {
            std::cerr << "Error! Wrong Syntax" << std::endl; // If any error occurs.
            continue;
        }
        insertSectorByCoordinates(x, y, z);
    }
    inputFile.close();
}


void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
    Sector* newSector = new Sector(x, y, z);

    if (root == nullptr) {
        root = newSector;
        root->color = false;
        return;
    }
    root = insertRecursive(root, newSector);
    root->color = false;    //after insertion, root is always BLACK.

}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors
    // to STDOUT in the given format.
    std::cout << "Space sectors inorder traversal:" << std::endl;
    inOrderTraversal(root);
    std::cout << std::endl;
}
void SpaceSectorLLRBT::inOrderTraversal(Sector* node) {
    std::string color;

    if (node != nullptr) {
        if(node->color)
            color = "RED";
        else
            color = "BLACK";
        inOrderTraversal(node->left);
        std::cout << color << " sector: " << node->sector_code << std::endl;
        inOrderTraversal(node->right);
    }
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print
    // the sectors to STDOUT in the given format.
    std::cout << "Space sectors preorder traversal:" << std::endl;
    preOrderTraversal(root);
    std::cout << std::endl;
}

void SpaceSectorLLRBT::preOrderTraversal(Sector* node) {
    std::string color;
    if (node != nullptr) {
        if(node->color)
            color = "RED";
        else
            color = "BLACK";
        std::cout << color << " sector: " << node->sector_code << std::endl;
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}


void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print
    // the sectors to STDOUT in the given format.
    std::cout << "Space sectors postorder traversal:" << std::endl;
    postOrderTraversal(root);
    std::cout << std::endl;

}
void SpaceSectorLLRBT::postOrderTraversal(Sector* node) {
    std::string color;
    if (node != nullptr) {
        if(node->color)
            color = "RED";
        else
            color = "BLACK";
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        std::cout << color << " sector: " << node->sector_code << std::endl;
    }
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    findStellarPath(root, sector_code, path);
    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function
    // to STDOUT in the given format.
    if (path.empty()) {
        std::cout << "A path to Dr. Elara could not be found." << std::endl;
    } else {
        std::cout << "The stellar path to Dr. Elara: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i]->sector_code;
            if (i < path.size() - 1) {
                std::cout << "->";
            }
        }

    }
}

Sector* SpaceSectorLLRBT::insertRecursive(Sector* current, Sector* newSector) {
    if (current == nullptr) {
        return newSector;
    }

    if (newSector->x < current->x) {
        current->left = insertRecursive(current->left, newSector);
    } else if (newSector->x > current->x) {
        current->right = insertRecursive(current->right, newSector);
    } else {
        if (newSector->y < current->y) {
            current->left = insertRecursive(current->left, newSector);
        } else if (newSector->y > current->y) {
            current->right = insertRecursive(current->right, newSector);
        } else {
            if (newSector->z < current->z) {
                current->left = insertRecursive(current->left, newSector);
            } else if (newSector->z > current->z) {
                current->right = insertRecursive(current->right, newSector);
            } else {
                delete newSector;
                return current;
            }
        }
    }

    if (isRed(current->right) && !isRed(current->left)) {
        current = rotateLeft(current);
    }
    if (isRed(current->left) && isRed(current->left->left)) {
        current = rotateRight(current);
    }
    if (isRed(current->left) && isRed(current->right)) {
        flipColors(current);
    }

    return current;
}


bool SpaceSectorLLRBT::isRed(Sector* node) const {
    if (node == nullptr) {
        return false;
    }
    return node->color == RED;
}

Sector* SpaceSectorLLRBT::rotateLeft(Sector* h) {
    Sector* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector* h) {
    Sector* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void SpaceSectorLLRBT::flipColors(Sector* h) {
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}

bool SpaceSectorLLRBT::findStellarPath(Sector* current, const std::string& target_sector_code, std::vector<Sector*>& path) {
    if (current == nullptr) {
        return false;
    }

    path.push_back(current);


    if (target_sector_code == current->sector_code) {
        return true;
    }
    bool foundInLeft = findStellarPath(current->left, target_sector_code, path);
    bool foundInRight = findStellarPath(current->right, target_sector_code, path);

    if (foundInLeft || foundInRight) {
        return true;
    }

    path.pop_back();
    return false;
}

SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.
    clearMemory(root);
}

void SpaceSectorLLRBT::clearMemory(Sector* node) {
    if (node != nullptr) {
        clearMemory(node->left);
        clearMemory(node->right);

        delete node;
    }
}


