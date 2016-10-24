#include <QCommandLineParser>
#include "apOCVPointGrey.hpp"

using namespace ap;
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication arg(argc, argv);
    QCoreApplication::setApplicationName("pgrey");
    QCoreApplication::setApplicationVersion("0.1");
    QCommandLineParser parser;

    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption dir(QStringList()<<"d"<<"dir","Directory path to write the images", "/home/user/images_dir");

    parser.addOption(dir);
    parser.process(arg);

    string pathDirectory;

    if(arg.arguments().length()<2)
    {
            parser.showHelp(OCVPointGrey::OK);
    }

    if(parser.isSet("dir"))
    {
        pathDirectory=parser.value("dir").toStdString();
    }

    int c = 0;
    int grabar = 0, cruz = 0, foto = 0;   


    namedWindow("Camera",CV_WINDOW_NORMAL);
    resizeWindow("Camera", 800, 800);

    OCVPointGrey ocvCamera;
    bool status=ocvCamera.OpenCamera();   

    if (status)
    {

    char key = 0;
    while(key != 'q')
    {
        key = waitKey(1);

        Mat image=ocvCamera.GetOpenCVFormat();

        if(grabar || key == 'g')
        {
            imwrite(pathDirectory, image);
            c++;
            grabar = 1;
        }
        if( key == 's' )
        {
            grabar = 0;
        }
        if(foto || key == 't')
        {
            foto = 0;            
            imwrite(pathDirectory,   image);
        }
        if(cruz || key == 'c')
        {
            line( image, Point(image.cols/2, 0), Point(image.cols/2, image.rows), Scalar( 0, 0, 255 ), 1, 8 );
            line( image, Point(0, image.rows/2), Point(image.cols, image.rows/2), Scalar( 0, 0, 255 ), 1, 8 );
            cruz = 1;
        }
        if( key == 'n' )
        {
            cruz = 0;
        }
        else
        {
            imshow("Camera", image);
        }
    }
  }

    ocvCamera.StopCameraCapture();
    ocvCamera.CameraDisconnect();   

    return OCVPointGrey::OK;
}
