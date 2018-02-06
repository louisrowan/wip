// 1. get character count for inputted string



const str = "hello_from_my_computer"

const characterMap = {};

for (let i = 0; i < str.length; ++i) {

    const char = str[i];
    characterMap[char] ? ++characterMap[char] : characterMap[char] = 1;
}

const transformMap = (map) => {

    const returnArr = [];
    Object.keys(map).forEach((k) => {

        returnArr.push({ value: map[k], char: k })
    })
    return returnArr;
}


// 2. recursively find least frequest characers and combine least frequent 2 into one element in array


const findLowestTwo = (arr) => {

    let lowest_a = {};
    let lowest_b = {};

    arr.forEach((obj) => {

        const value = obj.value;

        if (value < lowest_a.value || !lowest_a.value) {
            lowest_b = lowest_a;
            lowest_a = obj;
        }
        else if ( value < lowest_b.value || !lowest_b.value) {
            lowest_b = obj;
        }
    });

    const lowest_a_index = arr.findIndex((f) => f.char === lowest_a.char);
    arr.splice(lowest_a_index, 1);
    const lowest_b_index = arr.findIndex((f) => f.char === lowest_b.char);
    arr.splice(lowest_b_index, 1);
    arr.push({
        value: lowest_a.value + lowest_b.value,
        char: lowest_a.char + lowest_b.char,
        children: {
            '0': {
                value: lowest_a.value,
                char: lowest_a.char,
                children: lowest_a.children
            },
            '1': {
                value: lowest_b.value,
                char: lowest_b.char,
                children: lowest_b.children
            }
        }
    })
}

const transformed = transformMap(characterMap);

while (transformed.length > 1) {

    findLowestTwo(transformed);
}
console.log(JSON.stringify(transformed[0], null, 2));



// 3. traverse tree and track path needed to reach each leaf node

const finalTree = transformed[0];

const getCode = (tree, char, path) => {

    if (tree.char === char) {
        return path;
    }
    else {
        Object.keys(tree.children).forEach((binary) => {

            const child = tree.children[binary];

            if (child.char.includes(char)) {
                path += binary;
                path = getCode(child, char, path);
            }
        })
    }
    return path;
}

const res = getCode(finalTree, 'h', '')

// 4. create map for character to binary representation

const encodedMap = {};

Object.keys(characterMap).forEach((char) => {

    encodedMap[char] = getCode(finalTree, char, '')
})

// 5. create encoded string


let encodedStr = '';
for (let i = 0; i < str.length; ++i) {

    const char = str[i];
    encodedStr += encodedMap[char];
}


// 6. reverse encoding map from binary representation -> character

const reverseEncodedMap = {};
Object.keys(encodedMap).forEach((k) => {

    const binary = encodedMap[k];
    reverseEncodedMap[binary] = k
})

// 7. traverse encoded string and convert binary rep to original character

let decodedStr = '';
let currentChar = '';
for (let i = 0; i < encodedStr.length; ++i) {

    const char = encodedStr[i];
    currentChar += char;
    if (reverseEncodedMap[currentChar]) {
        decodedStr += reverseEncodedMap[currentChar];
        currentChar = '';
    }
}

console.log('final decoded:::', decodedStr);