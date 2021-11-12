#ifndef __RCRTC_DESKTOP_CAPTURER__
#define __RCRTC_DESKTOP_CAPTURER__
#include <stdio.h>
#include "api/video/i420_buffer.h"

#include "third_party/libyuv/include/libyuv/convert.h"
#include "third_party/libyuv/include/libyuv/video_common.h"

#include "media/base/video_broadcaster.h"
#include "media/base/video_common.h"

#include "modules/desktop_capture/desktop_and_cursor_composer.h"
#include "rtc_base/thread.h"
#include "system_wrappers/include/sleep.h"

#include "test/vcm_capturer.h"
#include "rtc_base/platform_thread.h"

typedef void (*desktop_capture_frame_callback)(int width,
                                               int height,
                                               int y_stride,
                                               int u_stride,
                                               int v_stride,
                                               const uint8_t *y,
                                               const uint8_t *u,
                                               const uint8_t *v,
                                               void *context);

class RcrtcDesktopCapturerTrackSource : public webrtc::DesktopCapturer::Callback,
                                        public webrtc::test::TestVideoCapturer
{
public:
  RcrtcDesktopCapturerTrackSource(/*const std::map<std::string, std::string>& opts*/) {
    Start(nullptr);
  }
  inline ~RcrtcDesktopCapturerTrackSource() override {}

  static RcrtcDesktopCapturerTrackSource *Create()
  {
    std::unique_ptr<RcrtcDesktopCapturerTrackSource> desk(new RcrtcDesktopCapturerTrackSource);
    return desk.release();
  }
  // overide webrtc::DesktopCapturer::Callback
  void OnCaptureResult(webrtc::DesktopCapturer::Result result,
                       std::unique_ptr<webrtc::DesktopFrame> frame) override
  {
    if (result == webrtc::DesktopCapturer::Result::SUCCESS)
    {
      int width = frame->size().width();
      int height = frame->size().height();

      rtc::scoped_refptr<webrtc::I420Buffer> I420buffer =
          webrtc::I420Buffer::Create(width, height);

      int stride=width;
      uint8_t* yplane=I420buffer->MutableDataY();
      uint8_t* uplane=I420buffer->MutableDataU();
      uint8_t* vplane=I420buffer->MutableDataV();
      const int conversionResult = libyuv::ConvertToI420( frame->data(), 0, 
          yplane,stride,
          uplane,(stride+1)/2,
          vplane,(stride+1)/2,
          0, 0,
          width,height,
          width,height,
          // I420buffer->width(), I420buffer->height(), 
          // I420buffer->width(), I420buffer->height(), 
          libyuv::kRotate0, ::libyuv::FOURCC_ARGB);

      if (conversionResult >= 0)
      {
        // webrtc::VideoFrame videoFrame(I420buffer,
        //                               webrtc::VideoRotation::kVideoRotation_0,
        //                               rtc::TimeMicros());

        // rtc::scoped_refptr<webrtc::I420BufferInterface> buffer(
        //     videoFrame.video_frame_buffer()->ToI420());
        // _frameCallback(buffer->width(), buffer->height(), buffer->StrideY(),
        //                buffer->StrideU(), buffer->StrideV(), buffer->DataY(),
        //                buffer->DataU(), buffer->DataV(), this->_userContext);
        
        webrtc::VideoFrame videoFrame=webrtc::VideoFrame(I420buffer,0,0,webrtc::kVideoRotation_0);
        _sink->OnFrame(videoFrame);
      }
    }
  }

  void setExccludeWindow(webrtc::DesktopCapturer::Source windowId)
  {
    _excludeWindowList.push_back(windowId);
  }

  static void CaptureDeskThread(void *obj)
  {
    RcrtcDesktopCapturerTrackSource *capture = static_cast<RcrtcDesktopCapturerTrackSource *>(obj);
    capture->CaptureProcess();
  }
  void CaptureProcess()
  {
    webrtc::DesktopCaptureOptions opts =
        webrtc::DesktopCaptureOptions::CreateDefault();
    // opts.set_allow_use_magnification_api(true);  //设置过滤窗口选项
    // 使用 DesktopAndCursorComposer 可以采集鼠标
    std::unique_ptr<webrtc::DesktopCapturer> capturer =
        std::unique_ptr<webrtc::DesktopCapturer>(
            new webrtc::DesktopAndCursorComposer(
                webrtc::DesktopCapturer::CreateScreenCapturer(opts), opts));

    // 设置开始采集状态
    capturer->Start(this);

    // 设置要过滤的窗口
    for (auto source : _excludeWindowList)
    {
      capturer->SetExcludedWindow(source.id);
    }

    while (_isrunning)
    {
      webrtc::SleepMs(_msPerFrame);
      // 采集桌面图像
      capturer->CaptureFrame();
    }
  }

  bool Start(desktop_capture_frame_callback back)
  {
    printf("start desk capturer...\n");
    if (!_capture_thread)
    {
      _frameCallback = back;
      _isrunning = true;
      _capture_thread.reset(new rtc::PlatformThread(RcrtcDesktopCapturerTrackSource::CaptureDeskThread, this,
                                                    "CaptureThread", rtc::ThreadPriority::kHighPriority));

      _capture_thread->Start();
    }
    // CaptureThread();
    // _capture_thread = rtc::Thread::Create();
    // _capture_thread->Start();
    // _capture_thread->PostTask(RTC_FROM_HERE, [&]
    //                           { CaptureThread(); });
  }

  void Stop()
  {
    if (_isrunning)
    {
      _isrunning = false;
      _capture_thread->Stop();
      _capture_thread.reset();
    }
  }

  void AddOrUpdateSink(
      rtc::VideoSinkInterface<webrtc::VideoFrame> *sink,
      const rtc::VideoSinkWants &wants)
  {
    // Start(nullptr);
    _sink = sink;
  }

  void RemoveSink(rtc::VideoSinkInterface<webrtc::VideoFrame> *sink)
  {
    if (sink == _sink)
    {
      _sink = nullptr;
    }

    Stop();
  }

public:
  int _msPerFrame = 100;                                   // 100毫秒采集一次，每秒钟采集10帧
  webrtc::DesktopCapturer::SourceList _excludeWindowList;  //需要过滤的窗口列表
  desktop_capture_frame_callback _frameCallback = nullptr; //视频输出回调
  void *_userContext = nullptr;

private:
  std::unique_ptr<rtc::PlatformThread> _capture_thread;
  bool _isrunning = false;
  rtc::VideoSinkInterface<webrtc::VideoFrame> *_sink;
};

#endif