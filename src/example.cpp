#include "Camera.hpp"
#include "YuvFrame.hpp"
#include "BayerFrame.hpp"
#include <sstream>

void grab_frame(uframe_ptr &frame, Camera &camera, int i)
{
    std::stringstream filename;
    frame = std::make_unique<YuvFrame>();
    //frame = std::make_unique<BayerFrame>(cv::COLOR_BayerBG2BGR);
    camera.capture(frame, 0, 1);

    // save frames
    /*
    filename << "../out/raw_" << i << ".raw";
    frame->rawFrameToFile(filename.str());
    std::cout << "Raw frame saved\n";
    filename.str("");
    filename.clear();
*/
    filename << "../out/processed_" << i << ".png";
    frame->processedFrameToFile(filename.str());
    std::cout << "Processed frame saved\n";
    filename.str("");
    filename.clear();
}

int main(int argc, char const *argv[])
{
    // get camera capabilities
    ucap_ptr cap = std::make_unique<v4l2_capability>();

    Camera camera("/dev/video0");
    camera.getCapabilities(cap);

    if (!(cap->capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        std::cerr<<"This is not a video capture device\n";
        exit (EXIT_FAILURE);
    }

    if (!(cap->capabilities & V4L2_CAP_STREAMING))
    {
        std::cerr<<"V4L2_CAP_STREAMING failed\n";
        exit (EXIT_FAILURE);
    }

    // adjust camera settings
    camera.setFormat(960, 720, V4L2_PIX_FMT_YYUV);
    camera.set(V4L2_CID_EXPOSURE_AUTO, V4L2_EXPOSURE_MANUAL);

    double val;
    camera.get(V4L2_CID_EXPOSURE_AUTO, val);
    std::cout << "Value of V4L2_CID_EXPOSURE_AUTO: " << val << std::endl;

    // get frame
    uframe_ptr frame;

    for (int i = 0; i < 3; i++)
    {
        grab_frame(frame, camera, i);
    }

    frame = nullptr;

    camera.setFormat(960, 720, V4L2_PIX_FMT_MJPEG);

    grab_frame(frame, camera, 5);

    return 0;
}
