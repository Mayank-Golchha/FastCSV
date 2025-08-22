#ifndef CSV_H
#define CSV_H

#include <string>

#include "file_handler.h"

class CSV{
    private:
        std::string file_path;
        FileHandler file;

    public:
        CSV(std::string file_path_) : file(file_path_){
            file_path = file_path_;
            file.find_indexes();
        }

        std::vector<std::string> read_row(int y){
            // y is the line no
            if (y >= file.last_line_no()) return {};
            std::string text = file.readLine(y);
            if (!text.size()) return {};
            int start = 0;
            std::vector<std::string> row;
            for (int i = 0;i<text.size();i++){
                if (text[i] == ','){
                    row.push_back(text.substr(start,i-start));
                    start = i+1;
                }
            }
            row.push_back(text.substr(start));
            return row;
        }

        std::vector<std::string> last_row(){
            return read_row(file.last_line_no());
        }

        void write_row(std::vector<std::string> row){
            std::string text;
            for (int i = 0;i<row.size();i++){
                text += row[i] + ",";
            }
            if (text != "") text.pop_back();
            file.write(text);
            file.insert_index(text.size()+2);
            // file.write(text);
        }
        
};

#endif
