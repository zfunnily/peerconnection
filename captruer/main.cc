#include "captruer.h"

void desktop_capture_frame_callback1(int width, int height, int y_stride, int u_stride, int v_stride, const uint8_t* y, const uint8_t* u, const uint8_t* v, void* context)
{
    printf("回调数据\n");
}


int main()
{
    printf("000000");
    std::shared_ptr<RcrtcDesktopCapturer> captruer = std::shared_ptr<RcrtcDesktopCapturer>(new RcrtcDesktopCapturer());
    printf("111111");
    captruer->Start(desktop_capture_frame_callback1);
}