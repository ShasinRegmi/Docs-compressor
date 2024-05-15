#include <iostream>
#include <cstdio>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <chrono>
#define ll unsigned long long int
#include <filesystem>
#include <string>
#include <stdlib.h>

#include"huffman.h"
#include"Utility.h"
#include"compressUtliity.h"
#include"DecompressUtility.h"

using namespace std; 

int main(int argc, char *argv[]) {
    if(argc != 3) {
    
        exit(-1);
    }
    const char *option = argv[1];
    std::string foldername = argv[2];
    
     chrono::time_point < chrono::system_clock> start, end; 
     chrono::duration <double> time;
    ll filesize, predfilesize;
    ll compressedSie;
    if ( string(option) == "-c") {
    	  std::string path = foldername;
    	  std::string new_folder=foldername+"-compressed";
    	  filesystem::create_directory(new_folder);
    	start =  chrono::system_clock::now();

    	for (const auto & entry : std::filesystem::directory_iterator(path)){
	
        	std::cout << entry.path() << std::endl;
        	 string filename_string = entry.path().string();
        const char* filename = filename_string.c_str();
    
	       filesize += Utility::get_file_size(filename);
	        auto mapper = CompressUtility::parse_file(filename, filesize);
	        Node *const root = CompressUtility::generate_huffman_tree(mapper);
	         string buf = "";
	        predfilesize = CompressUtility::store_huffman_value(root, buf);
	       compressedSie += (predfilesize + 7) >> 3;
	    
	        CompressUtility::compress(new_folder,filename, filesize, predfilesize);
	        
<<<<<<< HEAD
	       
=======
	        
>>>>>>> c2fa84c2a9f51fdec4f862be7eb7bcd579dd812b
	    }
	    cout<<"Original Size:"<< filesize <<"bytes"<<endl;
	    cout << "Compressed Size (without header): " << compressedSie << " bytes" << std::endl;


	        end =  chrono::system_clock::now();
	
	        time = (end - start);
	         cout << "Compression Time: " << time.count() << "s" << endl<<endl;
		
    }
    else if (string(option) == "-dc") {
    	 std::string path = foldername;
    	  std::string new_folder=foldername+"-decompressed";
    	  filesystem::create_directory(new_folder);
    	start = chrono::system_clock::now();
    	for (const auto & entry : std::filesystem::directory_iterator(path)){
	
        	std::cout << entry.path() << std::endl;
        	 string filename_string = entry.path().string();
        const char* filename = filename_string.c_str();
        filesize = Utility::get_file_size(filename);
        
        DecompressUtility::decompress(new_folder,filename, filesize, predfilesize);
    }
        end = chrono::system_clock::now();

        time = (end - start);
        cout << "\nDecompression Time: " << time.count() << "s" << endl<<endl;
    
    } else {
        cout << "\nInvalid Option... Exiting\n";
    }
    return 0;
}
<<<<<<< HEAD


 //cout<<string(filename)+extension<<endl<<"..\\"+foldername+"-compressed"+"\\"+string(filename)+extension<<endl;
=======
// Run the program using the following command
//cout<<string(filename)+extension<<endl<<"..\\"+foldername+"-compressed"+"\\"+string(filename)+extension<<endl;
>>>>>>> c2fa84c2a9f51fdec4f862be7eb7bcd579dd812b
