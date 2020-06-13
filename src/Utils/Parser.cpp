//
// Created by Mathis on 21/04/2020.
//

#include "Parser.h"

void parser::parser_write(const std::string& nom,const std::map<std::string, std::string>& dico) {
    std::ofstream myfile;       //Define myfile in write mode
    myfile.open(nom);           //Open the file
    if (myfile.is_open()){      //Test if the file opened well
        for (auto& x: dico) {   //Write from dico into the file
            myfile << x.first << ";" << x.second << std::endl;  // first = key; second = value
        }
        myfile.close();         //Close the file
    }
    else {                      //Problem occured
        std::string ope="Problem when creating or opening file " + nom;
        warn(ope);
    }
}

std::map<std::string, std::string> parser::parser_read(const std::string& nom) {

    std::string line;       //Variable to stock the line from the txt
    std::map<std::string, std::string> dico;  //Creation of dico
    std::ifstream myfile(nom);  //Define and open myfile in reading mode
    if (myfile.is_open()){      //Test if myfile is opened
        while (std::getline(myfile, line)) {    //Reccuperation of the lines in txt
            int i = 0;
            std::string key;
            while(line[i]!=';'){    //Get the key (string before ;)
                key += line[i];
                i++;
                if (i == line.size()){
                    std::string fil = "Warning, " + nom + " file corrupted";
                    warn(fil);
                    break;
                }
            }
            if (i!=line.size()){
                std::string value;      //Reccuperation of value (string after ;)
                for (int j=i+1;j<line.size();j++){
                    value += line[j];
                }
                dico.emplace(key,value);    //Add the pair key;value to unordered_map
            }
        }
    }
    else {
        std::string warni = "Error while loading "+ nom;
        this ->warn(warni);
    }

    return dico;
}

std::string parser::descriptor() {
    return "(parse)";
}
