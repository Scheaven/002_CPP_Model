#include "videoWriterFFmpeg.h"


int add_stream(OutputStream *ost, AVFormatContext *oc, AVCodec **codec, \
	enum AVCodecID codec_id, int bitrate, int frame_rate, int width, int height)
{
	AVCodecContext *c;
	*codec = avcodec_find_encoder(codec_id);
	if (!(*codec)) {
		printf("can not find encoder:%d\n", codec_id);
		return -1;
	}

	ost->st = avformat_new_stream(oc, *codec);
	if (!ost->st)
	{
		printf("avformat new stream error\n");
		return -1;
	}

	ost->st->id = oc->nb_streams - 1;
	c = ost->st->codec;
	if ((*codec)->type == AVMEDIA_TYPE_VIDEO)
	{
		c->codec_id = codec_id;
		c->bit_rate = bitrate;
		//·ÀÖ¹»º³å£¬ÊµÊ±±àÂë
		av_opt_set(c->priv_data, "preset", "superfast", 0);
		av_opt_set(c->priv_data, "tune", "zerolatency", 0);

		c->width = width;
		c->height = height;
		{
			AVRational r = { 1, frame_rate };
			ost->st->time_base = r;
		}
		c->time_base = ost->st->time_base;
		c->gop_size = 12;
		c->pix_fmt = AV_PIX_FMT_YUV420P;
		if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO)   c->max_b_frames = 2;
		if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO)   c->mb_decision = 2;
	}
	else
		return -1;
	/* Some formats want stream headers to be separate. */
	if (oc->oformat->flags & AVFMT_GLOBALHEADER)
		c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	return 0;
}


int fill_yuv_image(AVFrame *pict, int width, int height, Mat src) {
	int w, h, ret = av_frame_make_writable(pict);
	if (ret < 0) {
		printf("cannot make picture writable\n");
		return -1;
	}

	//Mat dst = Mat(height *3/2,width,CV_8UC1);
	for (h = 0; h < height; h++)
	{
		for (w = 0; w < width; w++)
		{
			//注意此处Mat为BGR格式
			uchar b = src.ptr<uchar>(h)[w * 3];
			uchar g = src.ptr<uchar>(h)[w * 3 + 1];
			uchar r = src.ptr<uchar>(h)[w * 3 + 2];
			//bgr转yuv，加减移位运算比浮点速度快
			uchar y = (uchar)((66 * r + 129 * g + 25 * b + 128) >> 8) + 16;
			uchar u = (uchar)((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128;
			uchar v = (uchar)((112 * r - 94 * g - 18 * b + 128) >> 8) + 128;
			if (y < 0) y = 0;
			else if (y > 255) y = 255;
			if (u > 255) u = 255;
			else if (u < 0) u = 0;
			if (v > 255) v = 255;
			else if (v < 0) v = 0;
			//AVFrame有个linesize，即跨度不一定与宽度一致
			//YUV420格式有点怪，yyuv排列，具体可以上网参考yuv420_plane
			pict->data[0][h*pict->linesize[0] + w] = y;
			if (w % 2 == 0 && h % 2 == 0)
			{
				pict->data[1][(h / 2)* pict->linesize[1] + w / 2] = u;
			}
			else if (w % 2 == 0)
			{
				pict->data[2][(h / 2)*pict->linesize[2] + w / 2] = v;
			}
		}
	}

	return 0;
}



videoWriterFFmpeg::videoWriterFFmpeg()
{
	io = { NULL };
	video_st = { 0 };
	videoFrameIdx = 0;
	fmt = NULL;
	oc = NULL;
	video_codec = NULL;
}

videoWriterFFmpeg::~videoWriterFFmpeg()
{

}

int videoWriterFFmpeg::open(char *out_mp4_file, int bitrate_in, int frame_rate_in, int width, int height)
{
	int flag = 0;
	int ret;
	AVCodecContext *c;
	AVDictionary* options = NULL;
	io.output_file_name = out_mp4_file;
	bitrate = bitrate_in;
	frame_rate = frame_rate_in;
	io.frame_width = width;
	io.frame_height = height;
	av_register_all();
	avformat_alloc_output_context2(&oc, NULL, NULL, io.output_file_name);
	if (!oc) {
		printf("Could not deduce output format from file extension: using MPEG.\n");
		avformat_alloc_output_context2(&oc, NULL, "mpeg", io.output_file_name);
		if (!oc)
		{
			flag = -1;
			goto End;
		}
	}
	fmt = oc->oformat;
	if (fmt->video_codec != AV_CODEC_ID_NONE)
	{
		ret = add_stream(&video_st, oc, &video_codec, fmt->video_codec, bitrate, frame_rate, width, height);
		if (ret != 0)
		{
			flag = -1;
			goto End;
		}

	}
	else
	{
		printf("cannot find codec id\n");
		flag = -1;
		goto End;
	}
	c = video_st.st->codec;
	ret = avcodec_open2(c, video_codec, 0);
	if (ret < 0)
	{
		printf("open video_codec failed\n");
		flag = -1;
		goto End;
	}
	video_st.frame = av_frame_alloc();
	if (!video_st.frame)
	{
		printf("alloc picture failed\n");
		flag = -1;
		goto End;
	}
	video_st.frame->format = c->pix_fmt;
	video_st.frame->width = c->width;
	video_st.frame->height = c->height;
	//ret = av_frame_get_buffer(video_st.frame, 32);
	ret = av_frame_get_buffer(video_st.frame, c->width * c->height);
	if (ret < 0)
	{
		printf("alloc buffer failed");
		flag = -1;
		goto End;
	}
	av_dump_format(oc, 0, io.output_file_name, 1);
	if (!(fmt->flags & AVFMT_NOFILE))
	{
		ret = avio_open(&oc->pb, io.output_file_name, AVIO_FLAG_WRITE);
		if (ret < 0)
		{
			printf("cannot open :%s\n", io.output_file_name);
			flag = -1;
			goto End;
		}
	}

	// ret = avformat_write_header(oc, 0);
	av_dict_set(&options, "movflags", "+frag_keyframe+empty_moov", 0);
	ret = avformat_write_header(oc, &options);
	assert(ret==0);

	if (ret < 0)
	{
		printf("write header error\n");
		flag = -1;
		goto End;
	}

End:
	//fclose(stderr);
	return flag;
}

int videoWriterFFmpeg::write(Mat src)
{
	AVFrame *frame = NULL;
	AVPacket pkt = { 0 };
	int got_packet = 0;
	AVRational r = { 1,1 };
	int ret;
	ret = av_frame_make_writable(video_st.frame);
	if (ret < 0) {
		printf("cannot make picture writable\n");
		return -1;
	}
	if (fill_yuv_image(video_st.frame, video_st.st->codec->width, video_st.st->codec->height, src) == 0)
	{
		video_st.frame->pts = video_st.next_pts++;
		frame = video_st.frame;
	}
	else
	{
		printf("cannot fill yuv images\n");
		return -1;
	}

	if (frame == NULL)
		return -1;
	av_init_packet(&pkt);
	ret = avcodec_encode_video2(video_st.st->codec, &pkt, frame, &got_packet);
	if (ret >= 0 && got_packet)
	{
		av_packet_rescale_ts(&pkt, video_st.st->codec->time_base, video_st.st->time_base);
		pkt.stream_index = video_st.st->index;
		ret = av_interleaved_write_frame(oc, &pkt);
		if (ret < 0)
			return -1;
	}
	videoFrameIdx++;
	return 0;
}

void videoWriterFFmpeg::close()
{
	av_write_trailer(oc);
	avcodec_close(video_st.st->codec);
	av_frame_free(&video_st.frame);
	av_frame_free(&video_st.tmp_frame);
	sws_freeContext(video_st.sws_ctx);
	swr_free(&video_st.swr_ctx);
	if (!(fmt->flags & AVFMT_NOFILE))  avio_closep(&oc->pb);
	avformat_free_context(oc);
	//fclose(stderr);
}
