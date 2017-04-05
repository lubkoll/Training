#include <iostream>

using std::cout;
using std::endl;

struct Data{};

void process(Data* d)
{
    if(d)
        cout << "processing data" << endl;
    else
        cout << "processing nothing" << endl;
}

void process(char)
{
    cout << "processing char" << endl;
}


int main()
{
    Data* d = new Data;

    process(d);
    process(0);
//    process(NULL)

    delete d;
}
