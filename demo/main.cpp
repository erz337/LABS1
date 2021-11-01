#include <student.hpp>


int main() {
  std::string jsonPath = PATH_TO_JSON;
  if(jsonPath.empty()) {
    throw std::runtime_error{"Missing path to json file"};
  }
  std::ifstream file{jsonPath};
  if (!file) {
    throw std::runtime_error{"unable to open json: " + jsonPath};
  }
  json data;
  file >> data;

  if (data["_meta"]["count"] != data["items"].size()){
    throw std::runtime_error{"_meta is incorrect"};
  }

  if (!data["items"].is_array()){
    throw std::runtime_error{"items is not array"};
  }

  std::vector<Student> students = read_file(data);
  print(students, std::cout);
}