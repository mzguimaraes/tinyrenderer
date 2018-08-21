#include "Model.h"

Model::Model(const char* filename) {
	std::ifstream file;
	file.open(filename);

	if (file.is_open()) {
		// std::cout << "Opening file" << std::endl;
		std::string line;
		std::vector<std::string> tokens; //tokens in line
		while (std::getline(file, line)) {
			tokens.clear();
			split(line, tokens);

			if (std::strncmp(tokens[0].c_str(), "#", 1) == 0)
				continue;

			if (std::strncmp(tokens[0].c_str(), "v", 2) == 0) {
				//add vertex

				// std::cout << "Adding vert "; 
				// for (int i = 0; i < tokens.size(); i ++) {
				// 	std::cout << tokens.at(i) << " ";
				// }
				// std::cout << std::endl;

				verts.push_back(new Vertex(std::stof(tokens[1]),
										   std::stof(tokens[2]),
										   std::stof(tokens[3])));
			}
			else if (std::strncmp(tokens[0].c_str(), "f", 1) == 0) {
				Face* newface = new Face(std::stoi(tokens[1])-1,
										 std::stoi(tokens[2])-1,
										 std::stoi(tokens[3])-1);
				faces.push_back(newface);
				// std::cout << "new Face " << newface->v0 << " " << newface->v1 << " " << newface->v2 << std::endl;
			}
			else {
				// std::cout << "Skipping line " << tokens[0] << std::endl;
			}
		}
	}
	else {
		std::cout << "Couldn't open file " << filename << std::endl;
	}

	file.close();
}

int Model::nfaces() const {
	return faces.size();
}

int Model::nverts() const {
	return verts.size();
}

Face* Model::face(int i) const {
	return faces.at(i);
}

Vertex* Model::vert(int i ) const {
	return verts.at(i);
}

// //copy control

// Model::~Model() {
// 	for (std::vector<Vertex*>::iterator it = verts.begin(); it != verts.end(); it++ ) {
// 		delete(*it);
// 	}
// 	verts.clear();

// 	for (std::vector<Face*>::iterator it = faces.begin(); it != faces.end(); it++ ) {
// 		delete(*it);
// 	}
// 	faces.clear();
// }

// Model::Model(const Model& model) : verts(model.verts.size()), faces(model.faces.size()) {
// 	for(std::size_t i = 0; i < model.verts.size(); i++) {
// 		verts[i] = new Vertex(*model.verts[i]);
// 	}
// 	for (std::size_t i = 0; i < model.faces.size(); i++) {
// 		faces[i] = new Face(*model.faces[i]);
// 	}
// }

// Model& Model::operator = (const Model& rhs) {
// 	//TODO
// 	throw "Not implemented yet";
// }

//helper functions

void split(const std::string& s, std::vector<std::string>& v,  const char* delim) {
	//splits str into a vector of tokens
	//source: http://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html

	// to avoid modifying original string
    // first duplicate the original string and return a char pointer then free the memory
    char * dup = strdup(s.c_str());
    char * token = strtok(dup, delim);
    while(token != NULL){
        v.push_back(std::string(token));
        // the call is treated as a subsequent calls to strtok:
        // the function continues from where it left in previous invocation
        token = strtok(NULL, delim);
    }
    free(dup);
}








