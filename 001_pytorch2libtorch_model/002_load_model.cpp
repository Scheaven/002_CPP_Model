//model_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <torch/script.h> // One-stop header.
#include <string>

#include <iostream>
#include <memory>

int main() 
{
	
	torch::jit::script::Module module;
	try 
	{
		// Deserialize the ScriptModule from a file using torch::jit::load().
		module = torch::jit::load("model.pt");
	}
	catch (const c10::Error& e) 
	{
		std::cerr << "error loading the model\n";
		return -1;
	}

	std::cout << "ok\n";
}


// int main() {
// 	// Deserialize the ScriptModule from a file using torch::jit::load().
// 	torch::jit::script::Module module = torch::jit::load("D:/CPP_project/04_REID/02_CPP_test/model_test/model_test/model.pt");

// 	assert(module != nullptr);
// 	std::cout << "ok\n";
// 	// Create a vector of inputs.
// 	std::vector<torch::jit::IValue> inputs;
// 	inputs.push_back(torch::ones({ 1, 3, 224, 224 }));

// 	// Execute the model and turn its output into a tensor.
// 	//at::Tensor output = module->forward(inputs).toTensor();

// 	//std::cout << output.slice(/*dim=*/1, /*start=*/0, /*end=*/5) << '\n';
// 	while (1);
// }

