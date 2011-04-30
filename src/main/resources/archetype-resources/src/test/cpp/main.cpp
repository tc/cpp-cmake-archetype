#set( $H = '#' )

${H}include <cppunit/extensions/TestFactoryRegistry.h>
${H}include <cppunit/ui/text/TestRunner.h>
${H}include <cppunit/TestResult.h>
${H}include <cppunit/TestResultCollector.h>
${H}include <cppunit/XmlOutputter.h>
${H}include <cppunit/TextOutputter.h>
${H}include <fstream>

${H}include <cstring>

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

