#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 2019/12/7 18:05
# @Author  : Scheaven
# @File    :  001_test.py
# @description:
import torch
class MyModel(torch.nn.Module):
    def __init__(self, N, M):
        super(MyModel, self).__init__()
        self.linear = torch.nn.Linear(N, M)

    def forward(self, inputs):
        output = self.linear(inputs)
        return output


if __name__== "__main__":
  B, N, M = 64, 32, 8
  model = MyModel(N, M)

  #第一种方法
  traced_script_module = torch.jit.script(model)
  traced_script_module.save("model.pt")


  # model = BaseLine().model.cpu().eval()
  # # An example input you would normally provide to your model's forward() method.
  # example = torch.rand(1, 3, 256, 128)

  #第二种方法
  # # Use torch.jit.trace to generate a torch.jit.ScriptModule via tracing.
  # traced_script_module = torch.jit.trace(model, example)
  # traced_script_module.save("demo/model.pt")