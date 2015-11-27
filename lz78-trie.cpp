#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <vector>


template <typename T, typename U>
class hash_pair {
public:
  	std::size_t operator()(const std::pair<T, U> &x) const {
    	return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  	}
};
void lz78(std::ifstream& input_file, std::ofstream& output_file){
	std::unordered_map<std::pair<int64_t,char>,int64_t,
		hash_pair<int64_t,int8_t>> trie;
	int64_t lz78_factor = 0;

	//get length of file
	input_file.seekg (0, input_file.end);
    auto length = input_file.tellg();
    input_file.seekg (0, input_file.beg);

    //allocate buffer and read contents into memory
    std::vector<uint8_t> stream;
    input_file.read((char*)stream.data(),length);

    //lz78 factoring
    uint64_t new_factor = 1;
    for(int64_t i=0;i<length;){
    	int64_t lz78_factor = 0;
    	for(auto v = trie.find(std::make_pair(lz78_factor,stream[i]));v!=trie.end();i++){
    		lz78_factor = v->second;
    	}
    	output_file << "<" << lz78_factor << "," << stream[i-1] << "> ";
    	trie[std::make_pair(lz78_factor,stream[i-1])] = new_factor++;
    }
}

int main(int argc, char* argv[]){
	if(argc!=3){
		std::cout << "Error\n";
		std::cout << "Usage: ./lz78-trie <input-file> <output-file>\n";
		return 0;
	}
	std::ifstream input_file;
	std::ofstream output_file;
	input_file.open(argv[1],std::ifstream::binary);
	output_file.open(argv[2]);
	if(!input_file || !output_file){
		std::cout << "Error opening files\n";
		return -1;
	}
	lz78(input_file,output_file);
	return 0;
}