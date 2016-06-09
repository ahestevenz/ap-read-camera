#include <QCommandLineParser>
#include "apOCVPointGrey.hpp"


using namespace ap;
using namespace cv;

void help()
{
  cout
  << "--------------------------------------------------------------------------"  << endl
  << ""  << endl
  << ""  << endl
                                                                                   << endl
  << "Use:"                                                                        << endl
  << ""
  << ""  << endl
  << ""  << endl
  << ""  << endl
  << "--------------------------------------------------------------------------"  << endl
  << endl;
}



int main(int argc, char *argv[])
{
//    QCoreApplication arg(argc, argv);
//    QCoreApplication::setApplicationName("filtroHistograma");
//    QCoreApplication::setApplicationVersion("0.1");
//    QCommandLineParser parser;

//    parser.addHelpOption();
//    parser.addVersionOption();

//    QCommandLineOption liv(QStringList()<<"liv"<<"live","Opcion para levantar camara", "-1: PointGray ; Otro: ID Cámara");
//    QCommandLineOption vid(QStringList()<<"vid"<<"video","ruta del video","/principal_path/video/*.avi");
//    QCommandLineOption logPos(QStringList()<<"lPos"<<"loguerPos", "Opcion para activar el loguear la posición y ruta donde se loguea", "../outputs/");
//    QCommandLineOption logMedia(QStringList()<<"lMedia"<<"loguerMedia","Opcion para activar el loguear la posición y ruta donde se loguea","../outputs/media");

//    parser.addOption(liv);
//    parser.addOption(vid);
//    parser.addOption(logPos);
//    parser.addOption(logMedia);
//    parser.process(arg);

    string pathLogPos;
    string pathLogMedia;
    string pathVideo;

    int c = 0;
    int grabar = 0, cruz = 0, foto = 0;
    char fileName[200];


    namedWindow("Camara",CV_WINDOW_NORMAL);
    resizeWindow("Camara", 800, 800);


    OCVPointGrey ocvCamera;
    bool status=ocvCamera.OpenCamera();


    if (status)
    {

    char key = 0;
    while(key != 'q')
    {
        key = waitKey(1);

        Mat image=ocvCamera.GetOpenCVFormat();

//        if( data.datoDisponible )
//        {

//            set_propiedad(data, camera);
//            data.datoDisponible = 0;


//        }

//        if(data.accion)
//        {
//            if(!strcmp(data.accion, "start"))
//            {
//                grabar = 1;
//            }
//            if(!strcmp(data.accion, "stop"))
//            {
//                grabar = 0;
//            }
//            if(!strcmp(data.accion, "fin"))
//            {
//                key = 'q';
//            }
//            if(!strcmp(data.accion, "cruz"))
//            {
//                if(cruz)
//                    cruz = 0;
//                else
//                    cruz = 1;
//            }
//            if(!strcmp(data.accion, "foto"))
//            {
//                foto = 1;
//            }

//            if(!strcmp(data.accion, "ptoInicio"))
//            {
//                key = 'i';
//            }

//            if(!strcmp(data.accion, "ptoFin"))
//            {
//                key = 'f';
//            }
//            if(!strcmp(data.accion, "ptoDiferencia"))
//            {
//                key = 'd';
//            }


//            *data.accion = 0;

//        }
        //    putText(image, data.str , Point(200,200), FONT_HERSHEY_SIMPLEX, 4, Scalar(200,90,200), 4);



        if(grabar || key == 'g')
        {
            imwrite(fileName,   image);
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
            sprintf (fileName,"..//fotos//%s.%.03ld.jpg");
            imwrite(fileName,   image);
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
            imshow("Camara", image);
        }
    }
  }

    ocvCamera.StopCameraCapture();
    ocvCamera.CameraDisconnect();

    bool nada=ocvCamera.IsHDRSupported();


    return 0;

}
