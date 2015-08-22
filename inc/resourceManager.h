#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#pragma once

#include <map>
#include <memory>
#include <cstdio>
#include <string>

template <typename T>
class ResourceManager
{
public:
	ResourceManager(std::function<T* (const std::string&)> retrieveMethod,
			std::function<void (T*)> removeMethod)
		:retrieveMethod_(retrieveMethod)
		,removeMethod_(removeMethod)
	{}

	std::shared_ptr<T> getResource(const std::string& filePath)
	{
		std::shared_ptr<T> ptrToReturn;

		if (storage_.count(filePath) == 1) {
			ptrToReturn = storage_[filePath].lock();
		} else {
			T* resourcePtr = retrieveMethod_(filePath);

			printf("Resource %s registered\n", filePath.c_str());
			ptrToReturn.reset(resourcePtr,
					  [this, filePath](T* ptr) {
						  printf("Resource %s unregistered\n", filePath.c_str());
						  removeMethod_(ptr);
						  storage_.erase(filePath);
					  });
			storage_.emplace(filePath, ptrToReturn);
		}

		return ptrToReturn;
	}
private:
	std::function<T* (const std::string&)> retrieveMethod_;
	std::function<void (T*)> removeMethod_;
	std::map<std::string, std::weak_ptr<T>> storage_;
};

#endif /* RESOURCE_MANAGER_H */
