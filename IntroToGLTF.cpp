#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    FILE* file = fopen("TriangleWithoutIndices.gltf", "r");
    if(!file) {
        printf("ERROR! File not found!");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    unsigned int size = ftell(file);
    rewind(file);

    unsigned char* fileData = new unsigned char[size];
    fread(fileData, size, 1, file);
    fclose(file);
    //printf("%s\n", fileData);

    /*
    bool firstQuote = false;
    for(int i = 0; i < size; i++) {
        if(firstQuote) {
            if(fileData[i] == '\"') {
                firstQuote = false;
                printf("\n");
            } else {
                printf("%c", fileData[i]);
            }
        } else if(fileData[i] == '\"') {
            firstQuote = true;
        }
    }*/
    std::vector<std::string> headers;
    std::string tempString;
    int moustache = 0;
    int square = 0;
    bool firstQuote = false;
    for(int i = 0; i < size; i++) {
        if(!firstQuote) {
            if(fileData[i] == '[')
                square++;
            else if(fileData[i] == ']')
                square--;
            else if(fileData[i] == '{')
                moustache++;
            else if(fileData[i] == '}')
                moustache--;
            else if(fileData[i] == '\"')
                firstQuote = true;
        } else {
            if(fileData[i] == '\"') {
                firstQuote = false;
                if(moustache == 1 && square == 0)
                    //printf("\n");
                    headers.push_back(tempString);
            } else {
                if(moustache == 1 && square == 0)
                    //printf("%c", fileData[i]);
                    tempString += fileData[i];
            }
        }
    }
    for(auto &&x : headers) {
        std::cout << x << '\n';
    }

    delete[] fileData;
}
