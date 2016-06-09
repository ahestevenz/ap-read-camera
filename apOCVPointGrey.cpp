#include "apOCVPointGrey.hpp"

using namespace ap;

OCVPointGrey::OCVPointGrey()
    :camera(Camera_ptr(new Camera))
{

}

OCVPointGrey::~OCVPointGrey()
{

}

bool OCVPointGrey::OpenCamera()
{
    CameraInfo camInfo;
    BusManager busMgr;
    unsigned int numCameras=0;

    /* Number of cameras*/
    if(!GetCamerasNumber(numCameras, &busMgr)) return false;
    /* Get camera index */
    if(!GetCamera(&busMgr)) return false;
    /* Connect the camera */
    if(!CameraConnect()) return false;
    /* Get the camera info */
    if(!GetCameraInfo(camInfo, false)) return false;
    /* Start capture */
    if(!StartCameraCapture()) return false;

    return true;
}

bool OCVPointGrey::GetCamerasNumber(unsigned int num, BusManager *bus_mgr)
{
    Error error;
    error=bus_mgr->GetNumOfCameras(&num);
       if ( error != PGRERROR_OK )
       {
           cerr << "Failed to read the number of cameras" << endl;
           return false;
       }
       if( num == 0 )
       {
           cerr << "No camera is connected. Please connect the camera." << endl;
           return false;
       }
       if( num != 1 )
       {
           cerr << "Please connect only one camera: " << num << " cameras are connected." << endl;
           return false;
       }
   return true;
}

bool OCVPointGrey::GetCamera(FlyCapture2::BusManager *bus_mgr)
{
    Error error;
    error = bus_mgr->GetCameraFromIndex(0, &guid);
    if ( error != PGRERROR_OK )
    {
        cerr << "Failed to get the camera. Error code: "<< error.GetType() << endl;
        #ifdef DEBUG
        error.PrintErrorTrace();
        #endif
        return false;
    }

    return true;
}

bool OCVPointGrey::CameraConnect()
{
    Error error;
    error = camera->Connect(&guid );
    if ( error != PGRERROR_OK )
    {
        cerr << "Failed to connect to the camera. Error code: "<< error.GetType() << endl;
        #ifdef DEBUG
        error.PrintErrorTrace();
        #endif
        return false;
    }

    return true;
}

bool OCVPointGrey::GetCameraInfo(CameraInfo camInfo, bool show)
{
    Error error;
    error = camera->GetCameraInfo( &camInfo );
    if ( error != PGRERROR_OK )
    {
         cerr << "Failed to get information from the camera. Error code: "<< error.GetType() << endl;
         #ifdef DEBUG
         error.PrintErrorTrace();
         #endif
         return false;
    }
    if (show)
    {    cout << camInfo.vendorName << " "
         << camInfo.modelName << " "
         << camInfo.serialNumber << endl;
    }

    return true;
}

bool OCVPointGrey::StartCameraCapture()
{
    Error error;
    error = camera->StartCapture();
    if ( error == PGRERROR_ISOCH_BANDWIDTH_EXCEEDED )
    {
        cerr << "Bandwidth exceeded" << endl;
        return false;
    }
    else if ( error != PGRERROR_OK )
    {
        cerr << "Failed to start image capture. Error code: "<< error.GetType() << endl;
        #ifdef DEBUG
        error.PrintErrorTrace();
        #endif
        return false;
    }

    return true;
}

bool OCVPointGrey::StopCameraCapture()
{
    Error error;
    error = camera->StopCapture();
    if ( error != PGRERROR_OK )
    {
        cerr << "Failed to stop image capture. Error code: "<< error.GetType() << endl;
        #ifdef DEBUG
        error.PrintErrorTrace();
        #endif
        return false;
    }

    return true;
}

bool OCVPointGrey::CameraDisconnect()
{
    Error error;
    error=camera->Disconnect();
    if ( error != PGRERROR_OK )
    {
        cerr << "Failed to disconnect to the camera. Error code: "<< error.GetType() << endl;
        #ifdef DEBUG
        error.PrintErrorTrace();
        #endif
        return false;
    }

    return true;

}

bool OCVPointGrey::RestoreCameraBuffer()
{
    Error error;
    error=camera->RetrieveBuffer( &rawImage );
    if ( error != PGRERROR_OK )
    {
        cerr << "Capture error. Error code: "<< error.GetType() << endl;
        #ifdef DEBUG
        error.PrintErrorTrace();
        #endif
        return false;
    }

    return true;
}

void OCVPointGrey::ConvertToRGB()
{
    rawImage.Convert( FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage );
}

cv::Mat OCVPointGrey::ConvertPointGreyToOpenCV()
{
    unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize()/(double)rgbImage.GetRows();
    cv::Mat image = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(),rowBytes);

    return image;
}

cv::Mat OCVPointGrey::GetOpenCVFormat()
{
    RestoreCameraBuffer();
    ConvertToRGB();
    cv::Mat image = ConvertPointGreyToOpenCV();

    return image;
}

bool OCVPointGrey::IsHDRSupported()
{
	Error error;
	unsigned int RegVal;
	error = camera->ReadRegister( k_HDRCtrl, &RegVal );
	if (error != PGRERROR_OK)
	{
        cerr << "The camera is not HDR supported. Error code: "<< error.GetType() << endl;
        #ifdef DEBUG
        error.PrintErrorTrace();
        #endif
		return false;
	}

	return ( 0x80000000 & RegVal ) ? true : false;
}
