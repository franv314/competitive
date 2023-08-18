#include <unordered_map>
using namespace std;
unordered_map<long long int, int> books;

void aggiungi(long long int id) {
    books[id]++;
}

void togli(long long int id) {
    books[id]--;
}

int conta(long long int id) {
    return books[id];
}