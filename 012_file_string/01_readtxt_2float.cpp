//读取文本文件并将每一行按照“，”逗号分隔，并将其转化为float类型    

    ifstream finL("./l_file.txt"); 
    char* d=",";
    string ptL;

    getline(finL,ptL);
    char *pL =  strdup(ptL.c_str());
    char *pa = strtok(pL,d);
    char *pb = strtok(NULL,d);
    float a = atof(pa);
    float b = atof(pb);

