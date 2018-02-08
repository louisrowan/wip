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
        // total += line;
        total += line + "\n";
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
    std::string binary;
    std::string character;
    std::vector<huffmanTree> children;
};

std::string createIndent(int indent) {

    std::string ret;
    for (int i = 0; i < indent; ++i) {
        ret += ' ';
    };
    return ret;
}

void printHuffmanTree(huffmanTree t, int indent = 0) {

    std::string in = createIndent(indent);

    std::cout << in << "-----------------" << std::endl;
    std::cout << in << "character = " << t.character << std::endl;
    std::cout << in << "value = " << t.value << std::endl;
    std::cout << in << "binary = " << t.binary << std::endl;
    std::vector<huffmanTree>::const_iterator it;
    std::cout << in << "children:" << std::endl;
    for (it = t.children.begin(); it != t.children.end(); ++it) {
        printHuffmanTree(*it, indent + 8);
    }
    std::cout << in << "-----------------" << std::endl;
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

    lowest_a.binary = "0";
    lowest_b.binary = "1";

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
    // printHuffmanTree(map[0]);
    return map[0];
}

std::string getCode (huffmanTree tree, char character, std::string path = "") {

    if (tree.character.size() == 1) {
        return path;
    }
    else {

        std::vector<huffmanTree>::iterator it;
        for (it = tree.children.begin(); it != tree.children.end(); ++it) {

            huffmanTree child = *it;

            if (child.character.find(character) < std::string::npos) {
                path += it->binary;
                path = getCode(child, character, path);
            }
        }
    }
    return path;
}

std::map<char, std::string> createEncodedMap(std::map<char, int> map, huffmanTree tree) {

    // printHuffmanTree(tree);

    std::map<char, std::string> ret;

    std::map<char, int>::iterator it;
    for (it = map.begin(); it != map.end(); ++it) {

        char key = it->first;
        std::string value = getCode(tree, key);
        ret[key] = value;
    }
    return ret;
}

std::string encode(std::string str, std::map<char, std::string> map) {

    std::string ret;
    std::string::const_iterator it;
    for (it = str.begin(); it != str.end(); ++it) {

        char character = *it;
        ret += map[character];
    }
    return ret;
}

std::map<std::string, char> createDecodedMap(std::map<char, std::string> encodedMap) {

    std::map<std::string, char> ret;

    std::map<char, std::string>::const_iterator it;
    for (it = encodedMap.begin(); it != encodedMap.end(); ++it) {

        std::string str = it->second;
        ret[str] = it->first;
    }
    return ret;
}

std::string decode(std::map<std::string, char> decodeMap, std::string encodedStr) {

    std::string decodedStr = "";
    std::string currentStr = "";

    std::string::const_iterator it;
    for (it = encodedStr.begin(); it != encodedStr.end(); ++it) {

        char character = *it;
        currentStr += character;
        if (decodeMap[currentStr]) {
            decodedStr += decodeMap[currentStr];
            currentStr = "";
        }
    }
    return decodedStr;
}



int main (int argc, char** argv) {

    const std::string ORIGINAL_DATA = getData(argv);
    std::cout << ORIGINAL_DATA << std::endl;
    const std::map<char, int> CHARACTER_MAP = createCharacterMap(ORIGINAL_DATA);
    const std::vector<huffmanTree> TRANSFORMED_MAP = createTransformedMap(CHARACTER_MAP);
    const huffmanTree FINAL_TREE = createFinalTree(TRANSFORMED_MAP);
    const std::map<char, std::string> ENCODE_MAP = createEncodedMap(CHARACTER_MAP, FINAL_TREE);
    const std::map<std::string, char> DECODE_MAP = createDecodedMap(ENCODE_MAP);

    std::string ENCODED_STR = encode(ORIGINAL_DATA, ENCODE_MAP);
    std::string DECODED_STR = decode(DECODE_MAP, ENCODED_STR);

    std::cout << "*****" << std::endl;
    std::cout << ENCODED_STR << std::endl;
    std::cout << "*****" << std::endl;
    std::cout << DECODED_STR << std::endl;

    std::cout << "original size: " << ORIGINAL_DATA.size() * 7 << std::endl;
    std::cout << "encoded size: " << ENCODED_STR.size() << std::endl;
    std::cout << "final size: " << DECODED_STR.size() * 7 << std::endl;

    
    return 0;
}