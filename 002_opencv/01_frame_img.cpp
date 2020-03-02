cv::VideoCapture capture;
cv::Mat frame;

// opencv读取数据流、并转化为Tensor张量


frame = capture.open("data/003_s.mp4");
//    int fps = (int) cvGetCaptureProperty(frame, cv::CV_CAP_PROP_FPS);
int fps = (int) capture.get(cv::CAP_PROP_FPS);
double duration = capture.get(cv::CAP_PROP_FRAME_COUNT);

torch::Tensor init_frame;
torch::Tensor init_tensors;
bool is_First = true;
int i = 0 ;
vector<torch::Tensor> input_frames;
while(capture.read(frame))
{
    cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR); //修改图片格式
    frame.convertTo(frame, CV_32FC3, 1.0f / 255.0f); // 转化编码数据流，从8位无字符转换为float数据流
    init_frame = torch::from_blob(frame.data, {1 , frame.cols, frame.rows, 3}); //将float流转化为img帧Tensor矩阵张量
    init_frame = init_frame.to(at::kCUDA);
}