using namespace std; 
namespace Utility {
    
    ll get_file_size(const char *filename) {
        FILE *p_file = fopen(filename, "rb");
        fseek(p_file, 0, SEEK_END);
        ll size = ftello64(p_file);
        fclose(p_file);
        return size;
    }
    
    void Inorder(Node *root,  string &value) {
        if (root) {
            value.push_back('0');
            Inorder(root->left, value);
            value.pop_back();

            if (root->left == nullptr && root->right == nullptr) {
                cout << "Character: " << root->character << ", Count: " << root->count << ", ";
                 cout << "Huffman Value: " << value <<  endl;
            }
            
            value.push_back('1');
            Inorder(root->right, value);
            value.pop_back();
        }
    }
};