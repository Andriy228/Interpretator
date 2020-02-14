#include "MyForm.h"

using namespace OOP;

[STAThreadAttribute]


int main()
{
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew MyForm());
	return 0;
}