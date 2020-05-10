float *ReID_Utils::normalize(unsigned char *vsrc, int w, int h, int chan){
	float *data = (float*)malloc(h*w*chan*sizeof(float));
	int size = w*h;
	int size2 = size*2;

	unsigned char *srcData = (unsigned char*)vsrc;

	for(int i = 0;i<size;i++){
        *(data) = *(srcData + 2) /255.0f;
        *(data+size) = *(srcData + 1) /255.0f;
        *(data+size2) = *(srcData) /255.0f;
        data++;
        srcData+=3;
	}

	return data;
}
