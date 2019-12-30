#include <torch/script.h> // One-stop header.
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cerr << "usage: example-app <path-to-exported-script-module>\n";
    return -1;
  }
  // 模型加载
  torch::jit::script::Module module = torch::jit::load(argv[1]);

  int B = 64, N = 32, M = 8;
  vector<torch::jit::IValue> inputs;
  vector<float> raw_data(B * N, 1.0);
  // from_blob函数使用view将vector 映射为 tensor
  // 该方法一定要保证raw_data在内存中是连续存储，这样数据才不会乱
  torch::Tensor data = torch::from_blob(raw_data.data(), {B, N});
  inputs.push_back(data);

  // 模型预测，需要调用toTensor()方法将 c10::IValue 转换为 torch::Tensor
  torch::Tensor output = module.forward(inputs).toTensor();
  cout << output.slice(/*dim=*/0, /*start=*/0, /*end=*/1) << '\n';

  vector<vector<float>> answer(B, vector<float>(M));
  // 通过accessor获取数据
  auto a = output.accessor<float, 2>();
  for (int i=0; i<a.size(0); ++i)
  {
      auto a1 = a[i];
      for (int j=0; j<a1.size(0); j++)
      {
          answer[i][j] = a1[j];
      }
  }
}