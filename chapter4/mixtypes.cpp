#include<iostream>
using namespace std;

struct antarctica
{
    int year;
    int month;
    int day;
};

int main()
{
    antarctica s1, s2, s3;
    s1.year = 2000;
    antarctica * pa = &s2;
    pa->year = 2001;
    
    antarctica trio[3];
    trio[0].year = 2002;
    trio[1].year = 2003;
    trio[2].year = 2004;
    const antarctica * arp[3] = {&s1, &s2, &s3};
    
}
