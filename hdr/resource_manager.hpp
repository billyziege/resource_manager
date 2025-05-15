/**
 * A simple ResourceManager class for storing a templated resource.
 */
#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace resource_manager {
  /** @brief  Generates a random string of length length from the alphanum characters. **/
  std::string generate_random_hash(const unsigned int length) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
      std::string str_out;
      str_out.reserve(length);
      for (unsigned int i = 0; i < length; ++i) {
          str_out += alphanum[rand() % (sizeof(alphanum) - 1)];
      }
      
      return str_out;
  }
  
  
  template <typename T>
  class ResourceManager {
   protected:
    std::unordered_map<std::string, T> _resource_map;
    unsigned int _hash_length;
  
    /** @brief  Makes sure the returned hash is unique. **/
    std::string _GenHash() { 
      std::string res_hash = generate_random_hash(_hash_length);
      while (_resource_map.count(res_hash) != 0) { res_hash = generate_random_hash(_hash_length); }
      return res_hash;
    }
  
   public:
    ResourceManager(unsigned int hash_length = 10) : _hash_length(hash_length) {}
    
    // Inserting resources.
    /** @brief  Moves a resource into the resource manager. **/
    std::string MoveResource(T* resource) { 
      std::string res_hash = _GenHash();
      _resource_map.insert(std::make_pair(res_hash, std::move(*resource)));
      return res_hash;
    }
    /** @brief  Creates the resource and moves it into the resource manager. **/
    template <typename ...Args>
    std::string CreateResource(Args&&... args) { 
      T new_resource(std::forward<Args>(args)...);
      return MoveResource(&new_resource);
    }
    
    // Getter
    unsigned int hash_length() const { return _hash_length; }
    // Getting resources.
    T* GetResourcePtr(const std::string res_hash) { return &_resource_map[res_hash]; }
    T& operator[](const std::string res_hash) { return _resource_map[res_hash]; }
    
    // STL mapping
    size_t size() const { return _resource_map.size(); }
    //   Iterator mapping
    typename std::unordered_map<std::string, T>::iterator begin() { return _resource_map.begin(); }
    typename std::unordered_map<std::string, T>::const_iterator begin() const { return _resource_map.begin(); }
    typename std::unordered_map<std::string, T>::iterator end() { return _resource_map.end(); }
    typename std::unordered_map<std::string, T>::const_iterator end() const { return _resource_map.end(); }
  };
}  // end namespace resource_manager
