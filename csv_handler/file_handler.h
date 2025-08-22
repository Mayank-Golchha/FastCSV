#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class FileHandler{
    private:
        int buffer_size = 4096;
        std::vector<int> indexes;
        std::string file_path;
        // char* buffer = new char[buffer_size];
        std::string buffer;
        std::ofstream csv_writer;

    public:
        FileHandler(std::string file_path_) : buffer(buffer_size+1,'\0') , csv_writer(file_path_,std::ios::app){
            file_path = file_path_;
        }

        void find_indexes(){
            std::ifstream file(file_path,std::ios::binary);
            if (!file.is_open()) {
                indexes.clear();
                return;
            }
            int index = 0;
            indexes.push_back(0);
            while (file){
                file.read(&buffer[0],buffer_size);
    			std::streamsize s = file.gcount();
                if (s < 0) break;
                buffer[s] = '\0';
                int i = 0;
                for (i = 0;i<s;i++){
                    if (buffer[i] == '\n'){ 
                        indexes.push_back(index+i+1);
                    }

                }
                if (!file){
                    indexes.push_back(index+i+2);
                    return;
                }
                index += s;
            }
            file.close();
        }

        std::string readLine(int y){
            // y is the line no
            std::ifstream file(file_path);
        
            if (!file.is_open()) return ""; 
            if (y >= indexes.size()-1) return "";

            int size = indexes[y+1]-indexes[y]-2;
            std::string buffer(size,'\0');
            file.seekg(indexes[y]);

            file.read(&buffer[0],size);
            file.close();


            buffer.shrink_to_fit();

            return buffer;
        }

        int last_line_no(){
            return indexes.size()-2;
        }

        void insert_index(int size){
            // indexes[indexes.size()-1];
            indexes.push_back(indexes.back() + size);
        }

        void write(std::string text){
            if (!csv_writer.is_open()) return;

            csv_writer.seekp(0,std::ios::end);
            text += "\n";
            csv_writer << text;;
            // file.flush();
            // file.close();
        }
    
};

#endif