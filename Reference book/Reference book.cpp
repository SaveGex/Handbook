#include <iostream>;
#include "Handbook.h"

using namespace std;


int main(){
    Handbook apple("Apple", "Steave Jobs", "1-800-676-2775", "USA", "Create electronic gizmos (and maybe other)");
    apple.Save();
    Handbook for_view;
    for_view;
    PrintAll(for_view);


    return 0;
}