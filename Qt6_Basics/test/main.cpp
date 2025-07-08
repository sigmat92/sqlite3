#include <QCoreApplication>
#include <iostream>

int main(int argc, char *argv[]) {
	    QCoreApplication app(argc, argv);
	        std::cout << "Qt version: " << QT_VERSION_STR << std::endl;
		    return 0;
}

