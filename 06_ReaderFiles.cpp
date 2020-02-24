class ParameterReader
{
public:
    void ReID_Utils::ParameterReader( string filename, float *pFeature)
    {
        ifstream fin(filename.c_str());
        if (!fin)
        {
            std::cerr<<"parameter file misseed"<<endl;
        }
        while(!fin.eof()) //eof(): 如果读文件到达文件末尾，返回true。else :fail() etc.
        {
            string str;
            getline(fin,str);
            string result;
            //将字符串读到input中
            stringstream input(str); 
            //依次输出到result中，并以空格分隔
            int j = 0;
            while(input>>result) 
            {
                // 将string 转化为 float
                istringstream iss(result);
                float tem;
                iss >> tem;  
                pFeature[j] = tem;
                j++;
                // std::cout << " ::::::::: "<< tem <<endl;
            }

            break;
        }
    }
}