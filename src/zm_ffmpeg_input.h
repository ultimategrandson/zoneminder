#ifndef ZM_FFMPEG_INPUT_H
#define ZM_FFMPEG_INPUT_H

#include "zm_define.h"

extern "C" {
#include <ffmpeg4.4/libavformat/avformat.h>
#include <ffmpeg4.4/libavformat/avio.h>
#include <ffmpeg4.4/libavcodec/avcodec.h>
}

class FFmpeg_Input {

  public:
    FFmpeg_Input();
    ~FFmpeg_Input();

    int Open(const char *filename );
    int Open(
        const AVStream *,
        const AVCodecContext *,
        const AVStream *,
        const AVCodecContext *);
    int Close();
    AVFrame *get_frame(int stream_id=-1);
    AVFrame *get_frame(int stream_id, double at);
    int get_video_stream_id() const {
      return video_stream_id;
    }
    int get_audio_stream_id() const {
      return audio_stream_id;
    }
    AVStream *get_video_stream() {
      return ( video_stream_id >= 0 ) ? input_format_context->streams[video_stream_id] : nullptr;
    }
    AVStream *get_audio_stream() {
      return ( audio_stream_id >= 0 ) ? input_format_context->streams[audio_stream_id] : nullptr;
    }
    AVFormatContext *get_format_context() { return input_format_context; };

  private:
    typedef struct {
        AVCodecContext *context;
        AVCodec *codec;
        int frame_count;
    } stream;

    stream *streams;
    int video_stream_id;
    int audio_stream_id;
    AVFormatContext *input_format_context;
    AVFrame *frame;
		int64_t last_seek_request;
};

#endif
