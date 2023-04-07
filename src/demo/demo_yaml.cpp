#include <yaml-cpp/yaml.h>

#include <cstdlib>
#include <iostream>
#include <string>
struct PersonalInfo {
  std::string name;
  std::string sex;
  unsigned age;
};

void unmarshall_personal_info(YAML::Node &config, PersonalInfo &info) {
  info.name = config["name"].as<std::string>();
  info.sex = config["sex"].as<std::string>();
  info.age = config["age"].as<int>();
}

std::ostream &operator<<(std::ostream &os, const PersonalInfo &info) {
  os << "PersonalInfo(" << info.name << ", " << info.sex << ", " << info.age
     << ")";
  return os;
}

int main(int argc, char **argv) {
  try {
    YAML::Node config = YAML::LoadFile("config.yaml");
    PersonalInfo info;
    unmarshall_personal_info(config, info);

    std::cout << info << std::endl;
  } catch (YAML::Exception e) {
    std::cerr << "error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
