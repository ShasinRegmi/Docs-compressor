namespace CompressUtility {


Node *combine(Node *a, Node *b) {
    Node *parent = new Node((a ? a->count : 0)+(b ? b->count : 0));
    parent->left = b;
    parent->right = a;
    return parent;
}


bool sortbysec(const Node *a, const Node *b) { 
    return (a->count > b->count); 
}

 map<char, ll>parse_file(const char* filename, const ll Filesize) {
    FILE *ptr = fopen(filename, "rb");
    if (ptr == NULL) {
        perror("Error: File not found:");
        exit(-1);
    }
    unsigned char ch;
    ll size = 0, filesize = Filesize;
     vector<ll>Store(256, 0);

    while (size != filesize) {
        ch = fgetc(ptr);
        ++Store[ch];
        ++size;
    }

     map<char, ll>store;
    for (int i = 0; i < 256; ++i) {
        if (Store[i]) {
            store[i] = Store[i];
        }
    }
    fclose(ptr);
    return store;
}

 vector<Node*>sort_by_character_count(const  map<char, ll>&value) {
     vector<Node*> store;
    for (auto &x: value) {
        store.push_back(new Node(x.first, x.second));
    }
    sort(store.begin(), store.end(), sortbysec);
    return store;
}

 string generate_header(const char padding) {
     string header = "";
    unsigned char UniqueCharacter = 255;
    
    for (int i = 0; i < 256; ++i) {
        if (HuffmanValue[i].size()) {
            header.push_back(i);
            header.push_back(HuffmanValue[i].size());
            header += HuffmanValue[i];
            ++UniqueCharacter;
        }
    }
    char value = UniqueCharacter;
    return value+header+(char)padding;
}


ll store_huffman_value(const Node *root,  string &value) {
    ll temp = 0;  
    if (root) {
        value.push_back('0');
        temp = store_huffman_value(root->left, value);
        value.pop_back();
        if (!root->left && !root->right) {
            HuffmanValue[(unsigned char)root->character] = value;
            temp += value.size() * root->count;
        }
        value.push_back('1');
        temp += store_huffman_value(root->right, value);
        value.pop_back();
    }
    return temp;
}


Node *generate_huffman_tree(const  map <char, ll>&value) {
     vector<Node*> store = sort_by_character_count(value);
    Node *one, *two, *parent;
    sort(begin(store), end(store), sortbysec);
    if (store.size() == 1) {
        return combine(store.back(), nullptr);
    }
    while (store.size() > 2) {
        one = *(store.end() - 1); two = *(store.end() - 2);
        parent = combine(one, two);
        store.pop_back(); store.pop_back();
        store.push_back(parent);

         vector<Node*>::iterator it1 = store.end() - 2;
        while ((*it1)->count < parent->count && it1 != begin(store)) {
            --it1;
        }
         sort(it1, store.end(), sortbysec);
    }
    one = *(store.end() - 1); two = *(store.end() - 2);
    return combine(one, two);
}

void compress (string new_folder,const char *filename, const ll Filesize, const ll PredictedFileSize) {
    const char padding = (8 - ((PredictedFileSize)&(7)))&(7);
    std::string base_filename = string(filename).substr(string(filename).find_last_of("/\\") + 1);

    const  string header = generate_header(padding);
    int header_i = 0;
    const int h_length = header.size();
    std::string outputFilePath = new_folder + "\\" + base_filename + extension;

   
    FILE *iptr = fopen(filename, "rb"), *optr = fopen((std::string(filename) + extension).c_str(), "wb");
    
    if (!iptr) {
        perror("Error: File not found: ");
        exit(-1);
    }

    while (header_i < h_length) {
        fputc(header[header_i], optr);
        ++header_i;
    }

    unsigned char ch, fch = 0;
    char counter = 7;
    ll size = 0, i;
    while(size != Filesize) {
        ch = fgetc(iptr);
        i = 0;
        const  string &huffmanStr = HuffmanValue[ch];
        while(huffmanStr[i] != '\0') {
            fch = fch | ((huffmanStr[i] - '0') << counter);
            
            counter = (counter + 7) & 7;
            if(counter == 7) {
                fputc(fch, optr);
                fch ^= fch;
            }
            ++i;
        }
        ++size;
        if((size * 100 / Filesize) > ((size - 1) * 100 / Filesize)) {
            printf("\r%lld%% completed  ", (size * 100 / Filesize));
        }
    }
    if(fch) {
        fputc(fch, optr);
    }
    cout<<""<<endl;
    fclose(iptr);
    fclose(optr);
    try {
        std::filesystem::rename((std::string(filename) + extension).c_str(),outputFilePath.c_str());

  } catch (std::filesystem::filesystem_error& e) {
    std::cout << e.what() << '\n';
  }
}

};
