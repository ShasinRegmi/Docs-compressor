using namespace std; 
namespace DecompressUtility {

void generate_huffman_tree(Node * const root, const  string &codes, const unsigned char ch) {
    Node *traverse = root;
    int i = 0;
    while(codes[i] != '\0') {
        if(codes[i] == '0') {
            if(!traverse->left) {
                traverse->left = new Node(0);
            }
            traverse = traverse->left;
        } else {
            if(!traverse->right) {
                traverse->right = new Node(0);
            }
            traverse = traverse->right;
        }
        ++i;
    }
    traverse->character = ch;
}

 pair<Node*,  pair<unsigned char, int>>decode_header(FILE *iptr) {
    Node *root = new Node(0);
    int charactercount, buffer, total_length = 1;
    char ch, len;
    charactercount = fgetc(iptr);
     string codes;
    ++charactercount;
    while(charactercount) {
        ch = fgetc(iptr);
        codes = ""; 
        len = fgetc(iptr);
        buffer = len;

        while(buffer > codes.size()) {
            codes.push_back(fgetc(iptr));
        }
        
        total_length += codes.size()+2;

        generate_huffman_tree(root, codes, ch);
        --charactercount;
    }
    unsigned char padding = fgetc(iptr);
    ++total_length;
    return {root, {padding, total_length}};
}

void decompress(string new_folder, const char*filename, const ll Filesize, const ll leftover) {
    const  string fl = filename;
    std::string base_filename = fl.substr(fl.find_last_of("/\\") + 1,fl.find_last_of('.')-fl.find_last_of("/\\") -1);
    

    std::string outputFilePath = new_folder + "\\" + base_filename;
    FILE *iptr = fopen(fl.c_str(), "rb");
    FILE *optr = fopen( string(fl.substr(0, fl.size() - 7)).c_str(), "wb");
    
    if (iptr == NULL) {
        perror("Error: File not found");
        exit(-1);
    }

     pair<Node*,  pair<unsigned char, int>>HeaderMetadata = decode_header(iptr);
    Node *const root = HeaderMetadata.first;
    const auto [padding, headersize] = HeaderMetadata.second;

    char ch, counter = 7;
    ll size = 0;
    const ll filesize = Filesize-headersize;
    Node *traverse = root;
    ch = fgetc(iptr);
    while (size != filesize) {
        while (counter >= 0) {
            traverse = ch & (1 << counter) ? traverse->right : traverse->left;
            ch ^= (1 << counter);
            --counter;
            if (!traverse->left && !traverse->right) {
                fputc(traverse->character, optr);
                if(size == filesize - 1 && padding == counter + 1) {
                    break;
                }
                traverse = root;
            }
        }
        ++size;
        counter = 7;
        if ((size * 100 / filesize) > ((size - 1) * 100 / filesize)) {
            printf("\r%lld%% completed, size: %lld bytes   ", (size * 100 / filesize), size);
        }
        ch = fgetc(iptr);
    }
    fclose(iptr);
    fclose(optr);
    std::filesystem::rename(string(fl.substr(0, fl.size() - 7)).c_str(),outputFilePath.c_str());

}

} 

}; 