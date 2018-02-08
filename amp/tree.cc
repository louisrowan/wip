#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

std::string getData(char** argv) {

    std::string file = argv[1] ? argv[1] : "./text.txt";

    std::ifstream data(file);
    std::string line;
    std::string total;
    while(std::getline(data, line)) {
        total += line;
        // total += line + "\n";
    }
    return total;
}

std::map<char, int> createCharacterMap(const std::string str) {

    std::map<char, int> map;
    std::string::const_iterator it;
    for (it = str.begin(); it != str.end(); ++it) {

        char c = *it;
        ++map[c];
    }
    return map;
}

struct huffmanTree {

    int value;
    std::string character;
    std::vector<huffmanTree> children;
};

void printHuffmanTree(huffmanTree t) {

    std::cout << "_________________" << std::endl;
    std::cout << "character = " << t.character << std::endl;
    std::cout << "value = " << t.value << std::endl;
    std::vector<huffmanTree>::const_iterator it;
    std::cout << "children:" << std::endl;
    for (it = t.children.begin(); it != t.children.end(); ++it) {
        printHuffmanTree(*it);
    }
    std::cout << "-----------------" << std::endl;
}

std::vector<huffmanTree> createTransformedMap(std::map<char, int> characterMap) {

    std::vector<huffmanTree> ret;
    std::map<char, int>::iterator it;
    for (it = characterMap.begin(); it != characterMap.end(); ++it) {

        huffmanTree tree;
        tree.character = it->first;
        tree.value = it->second;
        std::vector<huffmanTree> v;
        tree.children = v;
        ret.push_back(tree);
    }
    return ret;
}

std::vector<huffmanTree> findLowestTwo(std::vector<huffmanTree> map) {

    huffmanTree lowest_a;
    lowest_a.value = 0;
    huffmanTree lowest_b;
    lowest_b.value = 0;

    std::vector<huffmanTree>::iterator it;
    for (it = map.begin(); it != map.end(); ++it) {

        int val = it->value;
        
        if (val < lowest_a.value || ! lowest_a.value) {
            lowest_b = lowest_a;
            lowest_a = *it;
        }
        else if (val < lowest_b.value || !lowest_b.value) {
            lowest_b = *it;
        }
    }

    for (it = map.begin(); it != map.end(); ++it) {
        if (it->character == lowest_a.character || it->character == lowest_b.character) {
            map.erase(it);
            --it;
        }
    }

    huffmanTree combinedNode;
    combinedNode.character = lowest_a.character + lowest_b.character;
    combinedNode.value = lowest_a.value + lowest_b.value;

    combinedNode.children.push_back(lowest_a);
    combinedNode.children.push_back(lowest_b);

    map.push_back(combinedNode);

    return map;
}


huffmanTree createFinalTree(std::vector<huffmanTree> map) {

    while (map.size() > 1) {
        std::vector<huffmanTree> updated = findLowestTwo(map);
        map = updated;
    }
    return map[0];
}



int main (int argc, char** argv) {

    const std::string ORIGINAL_DATA = getData(argv);
    const std::map<char, int> CHARACTER_MAP = createCharacterMap(ORIGINAL_DATA);
    const std::vector<huffmanTree> TRANSFORMED_MAP = createTransformedMap(CHARACTER_MAP);
    const huffmanTree FINAL_TREE = createFinalTree(TRANSFORMED_MAP);

    
    return 0;
}