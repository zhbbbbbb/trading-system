#include <iostream>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


template <typename T>
void actions_server(const char* memory_name, T val)
{
	using namespace boost::interprocess;
	// server, read and write
	// create a shared memory object
	shared_memory_object shared_m(create_only, memory_name, read_write);
	std::cout << "Shared memory (" << memory_name << ") has been created by server." << std::endl;
	shared_m.truncate(1000); // set size of the shared memory
	//// map the object
	mapped_region region(shared_m, read_write);
	std::cout << "Shared memory (" << memory_name << ") has been mapped by server." << std::endl;

	//Write an int to region
	T* data = static_cast<T*>(region.get_address());
	*data = val;

	std::cout << "Server wrote data: " << *data << std::endl;
}



template <typename T>
void actions_client(const char* memory_name)
{
	using namespace boost::interprocess;
	// client, only read
	// open a shared memory object
	shared_memory_object shared_m(open_only, memory_name, read_only); // can only read
	std::cout << "Shared memory (" << memory_name << ") has been opened by client." << std::endl;

	//// map the object
	mapped_region region(shared_m, read_only);
	std::cout << "Shared memory (" << memory_name << ") has been mapped by client." << std::endl;

	//Write an int to region
	T* data = static_cast<T*>(region.get_address());

	std::cout << "Client read data: " << *data << std::endl;
	shared_memory_object::remove(memory_name);
	std::cout << "Shared memory (" << memory_name << ") has been removed." << std::endl;
}



int main()
{
	const char* memory_name = "shared number";
	int val = 123;
	actions_server<int>(memory_name, val);
	actions_client<int>(memory_name);	

	return 0;
}