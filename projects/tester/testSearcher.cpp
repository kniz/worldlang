#include <iostream>
#include "../searcher/Headers.hpp"
using namespace std;

int main()
{
    using namespace NE;

    cout << "test1\n";

    Folder root("C:\\", Folder::Option(false));
    while( ! root.next().isNull())
    {
        const File& e = root.peek();
        cout << e.getPath() << "\n";
    }

    system("pause");
}