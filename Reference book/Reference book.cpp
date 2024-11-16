#include <iostream>;
#include "Handbook.h"

using namespace std;



void printAllFromJson(json some_datas) {
    for (auto data : some_datas) {
        if (data.is_array()) {
            printAllFromJson(data);
            cout << endl;
        }
        else {
            cout << data.dump() << endl;
        }
    }
    cout << endl;
}

int main(){
    //Handbook apple("Apple", "Steave Jobs", "1-800-676-2775", "USA", "Create electronic gizmos (and maybe other)");
    //apple.Save();

    //Handbook mcLaren("MClaren", "Ron Dennis", "0~0 44 1483 261500", "UK", "create sport cars. That cars in result are very expensive and one of the fastest cars in world");
    //mcLaren.Save();

    Handbook for_view;

    for_view;
    //PrintAll(for_view);

    json some_json_of_names = for_view.SearchByPNumber("");
    printAllFromJson(some_json_of_names);

    return 0;
}