#ifndef APOCVPOINTGREY_H
#define APOCVPOINTGREY_H

#define DEBUG

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include "flycapture/FlyCapture2.h"

#include <boost/shared_ptr.hpp>

using namespace FlyCapture2;
using namespace boost;
using namespace std;

typedef boost::shared_ptr<Camera> Camera_ptr;

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
        bool IsHDRSupported();
        bool SetWhiteBalance(int value_a=v_RedChannel, int value_b=v_BlueChannel);

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

    /* Registers */
        static const unsigned int k_HDRCtrl = 0x1800;
        static const unsigned int k_HDROn = 0x82000000;
        static const unsigned int k_HDROff = 0x80000000;
        static const unsigned int v_BlueChannel = 682;
        static const unsigned int v_RedChannel = 629;

    public:
        static const int OK=0;
        static const int FAILED=-1;
    };
}

#endif // APOCVPOINTGREY_H
