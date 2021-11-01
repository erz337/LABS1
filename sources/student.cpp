#include <student.hpp>


auto get_name(const json& j) -> std::string {
  return j.get<std::string>();
}

auto get_debt(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string> >();
}

auto get_avg(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<std::size_t>();
}

auto get_group(const json& j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::size_t>();
}

void from_json(const json& j, Student& s) {
  s.name = get_name(j.at("name"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
  s.group = get_group(j.at("group"));
}
void print(const Student& student, std::ostream& os){
  if (student.name.empty()){
    os << "| null\t|";
  } else {
    os << "| " << student.name << "\t|";
  }

  if (student.group.type() == typeid(std::string)){
    os << " " << std::any_cast<std::string>(student.group);
    std::size_t i = 10;
    for (; i-std::any_cast<std::string>(student.group).length() != 0; i--){
      os << " ";
    }
    os << "|";
  } else {
    os << " " << std::any_cast<std::size_t>(student.group)
       << " group\t|";
  }

  if (student.avg.type() == typeid(std::nullptr_t)){
    os << "null\t|";
  } else if (student.avg.type() == typeid(std::string)){
    os << " " << std::any_cast<std::string>(student.avg) << "\t|";
  } else if (student.avg.type() == typeid(std::double_t)){
    os << " " << std::any_cast<std::double_t>(student.avg) << "\t|";
  } else {
    os << " " << std::any_cast<std::size_t>(student.avg);
    std::size_t i = 0;
    for (; i<5-(std::any_cast<std::size_t>(student.avg)/10); i++){
      os << " ";
    }
    os << "|";
  }

  if (student.debt.type() == typeid(std::nullptr_t)) {
    os << " null      |" << std::endl;
  } else if (student.debt.type() == typeid(std::string)) {
    os << " " << std::any_cast<std::string>(student.debt);
    std::size_t i = 10;
    for (; i - std::any_cast<std::string>(student.debt).length() != 0; i--){
      os << " ";
    }
    os << "|" << std::endl;
  } else {
    os
        << " " << std::any_cast<std::vector<std::string>>(student.debt).size()
        << " items\t|" << std::endl;
  }
}

void print(const std::vector<Student>& students, std::ostream& os) {
  os << "| name          | group     | avg   | debt      |\n";
  os << "|---------------|-----------|-------|-----------|\n";
  for (auto const& student : students) {
    print(student, os);
    os << "|---------------|-----------|-------|-----------|\n";
  }
}
std::vector<Student> read_file(json data) {
  std::vector<Student> students;
  for (auto const &item : data.at("items")) {
    Student student;
    from_json(item, student);
    students.push_back(student);
  }
  return students;
}