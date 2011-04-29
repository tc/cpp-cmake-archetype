#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TextOutputter.h>
#include <fstream>

#include <cstring>

int main(int argc, char* argv[]) {
	// Definimos las variables para recuperar los resultados
	using namespace CppUnit;
	using namespace std;

	TestResult controller;
	TestResultCollector result;
	controller.addListener(&result);

	TextUi::TestRunner runner;
	TestFactoryRegistry& registry = TestFactoryRegistry::getRegistry();
	Test* testToRun = registry.makeTest(); 

	if(argc > 1){
		testToRun = testToRun->findTest(argv[1]);
	}

	runner.addTest(testToRun);
	runner.run(controller);
	
	// Escribimos los resultados como salida XMl
	ofstream xmlFileOut("cpptestresults.xml");
	XmlOutputter xmlOut(&result, xmlFileOut);
	xmlOut.write();
	xmlFileOut.close();

	// También queremos ver los resultados por pantalla
	TextOutputter textOutput(&result, std::cout);
	textOutput.write();
	
	return 0;
}

