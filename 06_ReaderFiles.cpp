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
            //依次输出到result中，并存入res中
            int j = 0;
            while(input>>result)
            {
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