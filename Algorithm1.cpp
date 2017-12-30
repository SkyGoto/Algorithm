#include "iostream"
using namespace std;
bool isInt;
int index;
int MT[624];     // 624 * 32 - 31 = 19937
void srand(int seed)
{
    index = 0 ;
    isInt = 1;
    //MT数组初始化
    MT[0] = seed;
    for (int i=1 ; i<624 ; i++)
    {
        int t= 0x6c078965 * ( MT[i-1]^(MT[i-1] >> 30)) + i ;    //1812433253 == 0x6c078965
        MT[i] = t & 0xffffffff;  //截取前32位
    }
}

//生成一个624个未经编号的数组
void generate()
{
    for (int i=0;i<624;i++)
    {
        // 2^31 = 0x80000000
        // 2^31-1 = 0x7fffffff
        int y= (MT[i] & 0x80000000) + (MT[(i+1)%624] & 0x7fffffff) ;
        MT[i] = MT[(i+397)%624] ^ (y >> 6);
        if (y & 1)
        {
            MT[i] ^= 0x9908b0df ;//2567483615 == 0x9908b0df
        }

    }
}

int  rand()
{
    if (!isInt)
    {
        srand((int)time(NULL));
    }
    if (index == 0)
    {
        generate();
    }
    int y= MT[index];
    y= y ^ (y >> 11);                 //y右移11个bit
    y = y ^ ((y << 7) & 0x9d2c5680);   //y左移7个bit与2636928640相与，再与y进行异或  2636928640 == 0x9d2c5680
    y = y ^ ((y << 15) & 0xefc60000);  //y左移15个bit与4022730752相与，再与y进行异或  4022730752 == 0xefc60000
    y = y ^ (y >> 18);                 //y右移18个bit再与y进行异或
    index = (index + 1) % 624;
    return y;
}

int main()
{
    srand(0);  //设置随机种子
    int cnt = 0;
    for(int i = 0; i < 1000000; i++)
    {
        if(rand() & 1)
            cnt++;
    }
    cout<<cnt / 10000.0<<"%"<<endl;
    return 0;
}
