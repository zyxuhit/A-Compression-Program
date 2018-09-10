#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED
typedef   unsigned   char   byte;

class LzwNode
{
public:
    int data1;
    byte data2;
};

class Lzw
{
public:
    int len;
    LzwNode lzw[4096];
    void unitLzw()
    {
        len=0;
        for (int i=0; i<256; i++)
        {
            lzw[i].data1=-1;
            lzw[i].data2=i;
            len++;
        }
    }
    void add(int ad,byte x)
    {
        lzw[len].data1=ad;
        lzw[len].data2=x;
        len++;
    }
    int check(int data1,byte data2)
    {
        for (int i=0; i<len; i++)
        {
            if ((lzw[i].data1==data1)&&((int)lzw[i].data2==(int)data2))
                return i;
        }
        return -1;
    }
    byte gethead(int i)
    {
        if (i<256)
            return lzw[i].data2;
        else
            return gethead(lzw[i].data1);
    }
};
class LzwCompression
{
public:
    void lzwCompression(string inputFile,string outputFile)
    {
        ifstream file1;
        ofstream file2;
        Lzw lz;
        //string inputFile,outputFile;
        //printf("请输入要压缩文件的位置及名称:");
        //cin >> inputFile;
        //printf("请输入压缩后文件保存的位置及名称:");
        //cin >> outputFile;
        int fore,after;
        file1.open(inputFile.c_str(),ios::binary);
        file2.open(outputFile.c_str(),ios::binary);
        int odd=0;
        byte odd0,odd1,odd2;
        int scount;
        while (!file1.eof())
        {
            lz.unitLzw();
            char x;
            scount=0;
            fore=-1;
            while ((!file1.eof())&&(lz.len<=4096))
            {
                file1.get(x);
                after=(int)(byte)x;
                //printf("%d ",after);
                while ((lz.check(fore,(byte)after)>=0)&&((!file1.eof())))
                {
                    fore=lz.check(fore,(byte)after);
                    file1.get(x);
                    after=(int)(byte)x;
                };
                if (lz.check(fore,(byte)after)<0)
                    lz.add(fore,(byte)after);
                //   printf("%d ",fore);
                if (odd==0)
                {
                    odd0=(byte)(fore>>4);
                    odd1=((byte)(fore&0x0000000F))<<4;
                }
                else
                {
                    odd1=odd1+(byte)(fore>>8);
                    odd2=(byte)(fore);
                    file2.put(odd0);
                    file2.put(odd1);
                    file2.put(odd2);
                }
                odd=(odd+1)%2;
                fore=after;
            }
            if (odd==0)
            {
                odd0=(byte)(fore>>4);
                odd1=((byte)(fore&0x0000000F))<<4;
            }
            else
            {
                odd1=odd1+(byte)(fore>>8);
                odd2=(byte)(fore);
                file2.put(odd0);
                file2.put(odd1);
                file2.put(odd2);
            }
            odd=(odd+1)%2;
        }
        if (odd==0)
        {
            odd0=(byte)(fore>>4);
            odd1=((byte)(fore&0x0000000F))<<4;
        }
        else
        {
            odd1=odd1+(byte)(fore>>8);
            odd2=(byte)(fore);
            file2.put(odd0);
            file2.put(odd1);
            file2.put(odd2);
        }
        odd=(odd+1)%2;
        if  (odd==1)
        {
            file2.put(odd0);
            file2.put(odd1);
        }
        file1.close();
        file2.close();
    }
    void unlzwCompression(string inputFile,string outputFile)
    {
        ifstream file1;
        ofstream file2;
        Lzw lz;
        //string inputFile, outputFile;
        //printf("请输入要解压文件的位置及名称:");
        //cin >> inputFile;
        //printf("请输入解压后文件保存的位置及名称:");
        //cin >> outputFile;
        file1.open(inputFile.c_str(),ios::binary);
        file2.open(outputFile.c_str(),ios::binary);
        char x;
        int num1,num2,fore,after,odd=0,scount,ii;
        byte odd0,odd1,odd2;
        byte s[4097];
        while (!file1.eof())
        {
            lz.unitLzw();
            fore=-1;
            if (odd==1)
                num1=num2;
            else
            {
                file1.get(x);
                odd0=(byte)x;
                file1.get(x);
                odd1=(byte)x;
                file1.get(x);
                odd2=(byte)x;
                num1=(((int)odd0)<<4)+(((int)odd1)>>4);
                num2=(((int)(odd1&0x0F))<<8)+((int)odd2);
            }
            odd=(odd+1)%2;
            scount=0;
            while ((!file1.eof())&&(lz.len<=4096))
            {
                if (num1>=lz.len)
                {
                    after=lz.gethead(fore);
                    lz.add(fore,lz.gethead(fore));
                    fore=num1;
                }
                else
                {
                    after=num1;
                    if (lz.check(fore,lz.gethead(after))<0)
                        lz.add(fore,lz.gethead(after));
                    fore=after;
                }
                ii=fore;
                scount=0;
                //printf("进");
                //printf("到了：‘%d’",ii);
                while (ii>=256)
                {
                    s[scount++]=lz.lzw[ii].data2;
                    ii=lz.lzw[ii].data1;
                    //printf("到了：‘%d’",ii);
                }
                //printf("出");
                s[scount++]=lz.lzw[ii].data2;
                for (int i=scount-1; i>=0; i--)
                {
                    file2.put(s[i]);
                    //printf("%d ",(int)s[i]);
                }
                if (odd==1)
                    num1=num2;
                else
                {
                    file1.get(x);
                    odd0=(byte)x;
                    file1.get(x);
                    odd1=(byte)x;
                    file1.get(x);
                    odd2=(byte)x;
                    num1=(((int)odd0)<<4)+(((int)odd1)>>4);
                    num2=(((int)(odd1&0x0F))<<8)+((int)odd2);
                }
                odd=(odd+1)%2;
            }
        }
        file1.close();
        file2.close();
    }
    /*void showUI(bool zip)
    {
        /*
        printf("\n\n\n\n");
        printf(" \n\n\n \t\t\t    *******LZW压缩软件********\n\n\n");
        printf("             1.压缩文件\n\n");
        printf("             2.解压缩文件\n\n");
        printf("             0.退出软件\n\n");
        printf("              请选择(0-2):");
        */
    //bool choice=zip;
    //scanf("%d",&choice);
    //if(choice<1&&choice>2)
    //choice=0;
    /*switch(choice)
    {
    case    1:
        lzwCompression();
        break;
    case    2:
        unlzwCompression();
        break;
    case    0:
        exit(0);
    }
    if (zip)
    lzwCompression();
    else
    unlzwCompression();
        }*/
};


#endif // LZW_H_INCLUDED
