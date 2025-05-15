// [DOCTEST framework set-up]
#include "doctest.h"

// [C++ headers]
#include <algorithm>
#include <string>

// [Code being tested.]
#include "resource_manager.hpp"

TEST_CASE("test_resource_manager_initialization") {
  std::vector<unsigned int> hash_lengths = {2, 5, 15};
  for (const auto& hash_length : hash_lengths) {
    resource_manager::ResourceManager<int> int_manager(hash_length);
    CHECK(int_manager.hash_length() == hash_length);
  }
}

unsigned int _my_int_default = 0;
float _my_float_default = 0;
bool _my_bool_default = false;

struct ForTest {
 public:
  unsigned int _my_int;
  float _my_float;
  bool _my_bool;

  ForTest() : _my_int(_my_int_default), _my_float(_my_float_default), _my_bool(_my_bool_default) {}
  ForTest(unsigned int my_int) : _my_int(my_int), _my_float(_my_float_default), _my_bool(_my_bool_default) {}
  ForTest(unsigned int my_int, float my_float) : _my_int(my_int), _my_float(my_float), _my_bool(_my_bool_default) {}
  ForTest(unsigned int my_int, float my_float, bool my_bool) : _my_int(my_int), _my_float(my_float), _my_bool(my_bool) {}
  ForTest(unsigned int my_int, bool my_bool, float my_float) : _my_int(my_int), _my_float(my_float), _my_bool(my_bool) {}
};

TEST_CASE("test_resource_manager_move_default") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  ForTest resource;
  std::string res_hash = for_test_mgr.MoveResource(&resource);
  ForTest* ptr = for_test_mgr.GetResourcePtr(res_hash);
  CHECK(ptr->_my_int == _my_int_default);
  CHECK(ptr->_my_float == _my_float_default);
  CHECK(ptr->_my_bool == _my_bool_default);
}

TEST_CASE("test_resource_manager_create_default") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  std::string res_hash = for_test_mgr.CreateResource();
  ForTest* ptr = for_test_mgr.GetResourcePtr(res_hash);
  CHECK(ptr->_my_int == _my_int_default);
  CHECK(ptr->_my_float == _my_float_default);
  CHECK(ptr->_my_bool == _my_bool_default);
}

TEST_CASE("test_resource_manager_create_variant_1") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  unsigned int my_int = 1;
  std::string res_hash = for_test_mgr.CreateResource(my_int);
  ForTest* ptr = for_test_mgr.GetResourcePtr(res_hash);
  CHECK(ptr->_my_int == my_int);
  CHECK(ptr->_my_float == _my_float_default);
  CHECK(ptr->_my_bool == _my_bool_default);
}

TEST_CASE("test_resource_manager_create_variant_2") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  unsigned int my_int = 1;
  float my_float = 2;
  std::string res_hash = for_test_mgr.CreateResource(my_int, my_float);
  ForTest* ptr = for_test_mgr.GetResourcePtr(res_hash);
  CHECK(ptr->_my_int == my_int);
  CHECK(ptr->_my_float == my_float);
  CHECK(ptr->_my_bool == _my_bool_default);
}

TEST_CASE("test_resource_manager_create_variant_3") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  unsigned int my_int = 1;
  float my_float = 2;
  bool my_bool = true;
  std::string res_hash = for_test_mgr.CreateResource(my_int, my_float, my_bool);
  ForTest* ptr = for_test_mgr.GetResourcePtr(res_hash);
  CHECK(ptr->_my_int == my_int);
  CHECK(ptr->_my_float == my_float);
  CHECK(ptr->_my_bool == my_bool);
}

TEST_CASE("test_resource_manager_create_variant_4") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  unsigned int my_int = 1;
  float my_float = 2;
  bool my_bool = true;
  std::string res_hash = for_test_mgr.CreateResource(my_int, my_bool, my_float);
  ForTest* ptr = for_test_mgr.GetResourcePtr(res_hash);
  CHECK(ptr->_my_int == my_int);
  CHECK(ptr->_my_float == my_float);
  CHECK(ptr->_my_bool == my_bool);
}

TEST_CASE("test_resource_manager_create_variant_4") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  unsigned int my_int = 1;
  float my_float = 2;
  bool my_bool = true;
  std::string res_hash = for_test_mgr.CreateResource(my_int, my_bool, my_float);
  ForTest* ptr = for_test_mgr.GetResourcePtr(res_hash);
  CHECK(ptr->_my_int == my_int);
  CHECK(ptr->_my_float == my_float);
  CHECK(ptr->_my_bool == my_bool);
}

TEST_CASE("test_resource_manager_bracket") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  unsigned int my_int = 1;
  float my_float = 2;
  bool my_bool = true;
  std::string res_hash = for_test_mgr.CreateResource(my_int, my_bool, my_float);
  CHECK(for_test_mgr[res_hash]._my_int == my_int);
  CHECK(for_test_mgr[res_hash]._my_float == my_float);
  CHECK(for_test_mgr[res_hash]._my_bool == my_bool);
}

TEST_CASE("test_resource_manager_bracket_ref") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  unsigned int my_int = 1;
  float my_float = 2;
  bool my_bool = true;
  std::string res_hash = for_test_mgr.CreateResource(my_int, my_bool, my_float);
  for_test_mgr[res_hash]._my_int = _my_int_default;
  ForTest* ptr = for_test_mgr.GetResourcePtr(res_hash);
  CHECK(ptr->_my_int == _my_int_default);
}

TEST_CASE("test_resource_manager_iteration") {
  resource_manager::ResourceManager<ForTest> for_test_mgr;
  std::vector<std::string> res_hashes;
  res_hashes.push_back(for_test_mgr.CreateResource());
  res_hashes.push_back(for_test_mgr.CreateResource());
  res_hashes.push_back(for_test_mgr.CreateResource());
  for (const auto& [res_hash, res] : for_test_mgr) {
    CHECK(std::count(res_hashes.begin(), res_hashes.end(), res_hash) == 1);
  }
}
