// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <nlohmann/json.hpp>
#include <any>
struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};


#endif // INCLUDE_HEADER_HPP_
