#include "Utility.h"
#include "Lk_stack.h"
#include "Huffman.h"
#include "LZW.h"
#include <QtGui>

using namespace std;

void dofile(string path1,string pwd,string path2)
{
    FILE *fp1,*fp2;
    char ch;
    int j=0,j0=0;
    fp1=fopen(path1.c_str(),"rb");
    fp2=fopen(path2.c_str(), "wb");
    while(pwd[++j0]);
    ch=fgetc(fp1);
    while(!feof(fp1))
    {
        fputc(ch^pwd[j>=j0?j=0:j++],fp2);
        ch=fgetc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
}

string process(string inputFile,string outputFile,int type,bool zip,string password)
{
    qDebug() << QString::fromStdString(inputFile) << QString::fromStdString(outputFile) << type << zip << QString::fromStdString(password);
    if (type==1)
    {
        LzwCompression lzwC;
        //lzwC.showUI(zip);
        //system("pause");
        if (zip)
        {
            if (!password.empty()) lzwC.lzwCompression(inputFile,outputFile+ "-tmp");
            else lzwC.lzwCompression(inputFile, outputFile);
            if (!password.empty())
            {
                string pwd=password;
                dofile(outputFile + "-tmp",pwd,outputFile);
            }
        }
        else
        {
            if (!password.empty())
            {
                string pwd=password;
                dofile(inputFile,pwd,inputFile + "-tmp");
                inputFile += "-tmp";
            }
            lzwC.unlzwCompression(inputFile,outputFile);
        }
        return "";
    }
    if (type==0)
    {
        if (zip)
        {
            HuffmanTree ht;
            if (!password.empty()) ht.Code(inputFile,outputFile + "-tmp");
            else ht.Code(inputFile,outputFile);
            //ht.code_print();
            if (!password.empty())
            {
                string pwd=password;
                dofile(outputFile + "-tmp",pwd,outputFile);
            }
        }
        else
        {
            if (!password.empty())
            {
                string pwd=password;
                dofile(inputFile,pwd,inputFile + "-tmp");
                inputFile += "-tmp";
            }
            HuffmanTree ht;
            ht.UnCode(inputFile,outputFile);
        }
        return "";
    }
}
