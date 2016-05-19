//
// Created by XiongMacAir on 16/2/13.
//

#include "NDKConverter.h"
//#include <cstring>
//#include <string.h>
//#include "vector"

#include <malloc.h>
#include <stdio.h>
#include <android/log.h>
#include "src/OpenCCConverter.hpp"

Opencc *CppOpenCCConverter = nullptr;
using namespace std;
extern char *openCC_ResoucePath;
extern char *OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD;
extern char *OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP;


char *ConvertSimpleTraditional(char *input)
{
    if (CppOpenCCConverter == nullptr)
    {
//创建转换器
        string openCCSimpToTrad = openCC_ResoucePath;
        openCCSimpToTrad += "s2t.json";
        CppOpenCCConverter = new Opencc(openCCSimpToTrad.data());
    }
    vector<string> *outPutChars = new vector<string>;
    CppOpenCCConverter->ConvertSingleCharacter(input, outPutChars);
    vector<string>::iterator end = outPutChars->end();
    string output;
    int count = 0;
    for (vector<string>::iterator i=outPutChars->begin(); i != end; ++i,count++) {
    //遍歷結果，拼接字符串
        output += *i;
    }
    delete outPutChars;
    char *outputString = new char[output.length() + 1];
    strcpy(outputString,output.data());
    return  outputString;
}
