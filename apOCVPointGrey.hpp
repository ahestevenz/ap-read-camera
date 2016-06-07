#ifndef APOCVPOINTGREY_H
#define APOCVPOINTGREY_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include "flycapture/FlyCapture2.h"

#include <boost/shared_ptr.hpp>

using namespace FlyCapture2;
using namespace boost;
using namespace std;

typedef shared_ptr<Camera> Camera_ptr;

namespace ap {
    class OCVPointGrey
    {
    public:
        OCVPointGrey();
        ~OCVPointGrey();
        bool OpenCamera();
        bool StopCameraCapture();
        bool CameraDisconnect();
        cv::Mat GetOpenCVFormat();

    private:
        bool GetCamerasNumber(unsigned int num, BusManager *bus_mgr);
        bool GetCamera( BusManager *bus_mgr);
        bool CameraConnect();
        bool GetCameraInfo(CameraInfo camInfo, bool show);
        bool StartCameraCapture();
        bool RestoreCameraBuffer();
        cv::Mat ConvertPointGreyToOpenCV();
        void ConvertToRGB();

    private:
        Camera_ptr camera;
        PGRGuid guid;
        Image rawImage;
        Image rgbImage;

    };
}

#endif // APOCVPOINTGREY_H
