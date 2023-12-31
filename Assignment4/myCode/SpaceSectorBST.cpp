#include "SpaceSectorBST.h"

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {

}



void SpaceSectorBST::displayInOrderHelper(Sector* root) {
    if (root != nullptr) {
        displayInOrderHelper(root->left);   //traversing left subtree

        std::cout <<  root->sector_code << std::endl;
        displayInOrderHelper(root->right); //traversing right subtree
    }
}
void SpaceSectorBST::displayPreOrderHelper(Sector* root) {
    if (root != nullptr) {
        std::cout << root->sector_code << std::endl;

        displayPreOrderHelper(root->left);   // Traverse left subtree
        displayPreOrderHelper(root->right);  // Traverse right subtree
    }
}

void SpaceSectorBST::displayPostOrderHelper(Sector* root) {
    if (root != nullptr) {
        displayPostOrderHelper(root->left);   // Traverse left subtree
        displayPostOrderHelper(root->right);  // Traverse right subtree

        std::cout <<  root->sector_code << std::endl;
    }
}
bool SpaceSectorBST::findStellarPath(Sector* current, const std::string& target_sector_code, std::vector<Sector*>& path) {
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

Sector* SpaceSectorBST::findMin(Sector* node) const {

    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

bool SpaceSectorBST::findDeletingSector(const std::string& sector_code, Sector* current, std::vector<Sector*>& path) const {
    if (current == nullptr) {
        return false;
    }
    path.push_back(current);
    if (sector_code == current->sector_code) {
        return true;
    }

    // Continue searching in both subtrees
    bool foundInLeft = findDeletingSector(sector_code, current->left, path);
    bool foundInRight = findDeletingSector(sector_code, current->right, path);

    if (foundInLeft || foundInRight) {
        return true;
    }
    path.pop_back();
    return false;
}

Sector* SpaceSectorBST::deleteSectorHelper(Sector* current, const std::string& sector_code) {

    std::vector<Sector*> path;
    bool found = findDeletingSector(sector_code, root, path);

    if (!found) {
        return root;
    }

    Sector* targetNode = nullptr;
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i]->sector_code == sector_code) {
            targetNode = path[i];
            break;
        }
    }


    if (targetNode->left == nullptr && targetNode->right == nullptr) {
        // Update parent pointers to remove the target node
        if (path.size() > 1) {
            Sector* parent = path[path.size() - 2];
            if (parent->left == targetNode) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }

        delete targetNode;
    }

        // Case 2: Node with one child
    else if (targetNode->left == nullptr) {
        Sector* temp = targetNode->right;
        if (path.size() > 1) {
            Sector* parent = path[path.size() - 2];
            if (parent->left == targetNode) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
        } else {
            root = temp;
        }

        delete targetNode;
    } else if (targetNode->right == nullptr) {
        Sector* temp = targetNode->left;
        if (path.size() > 1) {
            Sector* parent = path[path.size() - 2];
            if (parent->left == targetNode) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
        } else {
            root = temp;
        }

        delete targetNode;
    }


    else {
        Sector* successor = findMin(targetNode->right);
        Sector* temp;

        // Swap data between targetNode and successor
        targetNode->sector_code = successor->sector_code;
        targetNode->x = successor->x;
        targetNode->y = successor->y;
        targetNode->z = successor->z;
        targetNode->distance_from_earth = successor->distance_from_earth;
        if(targetNode->right->left == successor){
            targetNode->right->left = successor->right;
        }
        delete  successor;

    }
    return root;
}


void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::string line;

    // Discard the first line
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


void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    Sector newSector(x, y, z);

    if (root == nullptr) {
        root = new Sector(x, y, z);
        return;
    }

    Sector *current = root;
    while (true) {
        if (x < current->x) {
            if (current->left == nullptr) {
                current->left = new Sector(x, y, z);
                return;
            }
            current = current->left;
        } else if (x > current->x) {
            if (current->right == nullptr) {
                current->right = new Sector(x, y, z);
                return;
            }
            current = current->right;
        } else {
            if (y < current->y) {
                if (current->left == nullptr) {
                    current->left = new Sector(x, y, z);
                    return;
                }
                current = current->left;
            } else if (y > current->y) {
                if (current->right == nullptr) {
                    current->right = new Sector(x, y, z);
                    return;
                }
                current = current->right;
            } else {
                if (z < current->z) {
                    if (current->left == nullptr) {
                        current->left = new Sector(x, y, z);
                        return;
                    }
                    current = current->left;
                } else if (z > current->z) {
                    if (current->right == nullptr) {
                        current->right = new Sector(x, y, z);
                        return;
                    }
                    current = current->right;
                } else {
                    // If x,y and z are equal.
                    return;
                }
            }
        }
    }
}



void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
    if (root != nullptr && root->sector_code == sector_code) {
        return;
    }
    root = deleteSectorHelper(root, sector_code);
}

void SpaceSectorBST::displaySectorsInOrder() {
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format
    std::cout << "Space sectors inorder traversal:" << std::endl;
    displayInOrderHelper(root);
    std::cout << std::endl;
}


void SpaceSectorBST::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    //
    std::cout << "Space sectors preorder traversal:" << std::endl;
    displayPreOrderHelper(root);
    std::cout << std::endl;
}

void SpaceSectorBST::displaySectorsPostOrder() {
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    std::cout << "Space sectors postorder traversal:" << std::endl;
    displayPostOrderHelper(root);
    std::cout << std::endl;
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!

    findStellarPath(root, sector_code, path);

    return path;
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
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
        std::cout << std::endl;
    }
}


SpaceSectorBST::~SpaceSectorBST() {
    // Free any dynamically allocated memory in this class.
    clearMemory(root);
}

void SpaceSectorBST::clearMemory(Sector* node) {
    if (node != nullptr) {
        // Recursively delete left and right subtrees
        clearMemory(node->left);
        clearMemory(node->right);

        // Delete the current node
        delete node;
    }
}

Sector* SpaceSectorBST::connectNodes(Sector* node1, Sector* node2) {
    if (node1 == nullptr) {
        return node2;
    }

    Sector* temp = node1;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    temp->right = node2;

    return node1;
}

void SpaceSectorBST::replaceNodeWithInOrderSuccessor(Sector* nodeToReplace, Sector* inOrderSuccessor) {
    // Find the parent of the in-order successor
    Sector* successorParent = nullptr;
    Sector* successorCurrent = root;
    while (successorCurrent != nullptr && successorCurrent != inOrderSuccessor) {
        successorParent = successorCurrent;
        if (inOrderSuccessor->sector_code < successorCurrent->sector_code) {
            successorCurrent = successorCurrent->left;
        } else {
            successorCurrent = successorCurrent->right;
        }
    }

    // Update connections
    if (successorParent != nullptr) {
        if (successorCurrent->sector_code < successorParent->sector_code) {
            successorParent->left = inOrderSuccessor->right;
        } else {
            successorParent->right = inOrderSuccessor->right;
        }
    } else {
        // The in-order successor is the root
        root = inOrderSuccessor->right;
    }

    // Connect the in-order successor with the node to replace
    inOrderSuccessor->left = nodeToReplace->left;
    inOrderSuccessor->right = nodeToReplace->right;

    // Update the parent of the node to replace with the in-order successor
    Sector* parent = nullptr;
    Sector* current = root;
    while (current != nullptr && current != nodeToReplace) {
        parent = current;
        if (nodeToReplace->sector_code < current->sector_code) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (parent != nullptr) {
        if (nodeToReplace->sector_code < parent->sector_code) {
            parent->left = inOrderSuccessor;
        } else {
            parent->right = inOrderSuccessor;
        }
    } else {
        // The node to replace is the root
        root = inOrderSuccessor;
    }

    // Optional: Delete the node to replace if necessary
    delete nodeToReplace;
}