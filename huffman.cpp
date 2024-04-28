using namespace std; 
namespace Huffman {
string extension=".shasin";
 string HuffmanValue[256] = {""};


class Node {
   public:
    char character;
    ll count;
    Node *left, *right;

    Node(ll count) {
        this->character = 0;
        this->count = count;
        this->left = this->right = nullptr;
    }

    Node(char character, ll count) {
        this->character = character;
        this->count = count;
        this->left = this->right = nullptr;
    }
};
