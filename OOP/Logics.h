#pragma once
#define JSI_SAVE_FILE 0
#define JSI_SAVE_FILE_AS 1
namespace JSI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	ref class Methods {
		OpenFileDialog ^ openFile;
		SaveFileDialog ^ saveFile;
		IO::StreamReader ^ reader;
		IO::StreamWriter ^ writer;
		String ^ path = nullptr;
	public:
		Methods() {
			openFile = gcnew OpenFileDialog;
			openFile->Filter = "File code|*.html";
			saveFile = gcnew SaveFileDialog;
			saveFile->Filter = "File code|*.html";
		}
		// Open file
		void OpenFile(TextBox ^ container) {
			container->Text = "";		\
			openFile->FileName = "";
			openFile->ShowDialog();
			if (openFile->FileName != "") {
				reader = gcnew IO::StreamReader(openFile->FileName);
				while (!reader->EndOfStream) {
					container->Text += reader->ReadLine() + Environment::NewLine;
				}
				reader->Close();
				delete reader;
			}
			path = openFile->FileName;//Записуємо шлях до нашого файлу
		}
		// Save file
		void SaveFile(TextBox ^ container,int mode) {
			switch (mode)
			{
			case JSI_SAVE_FILE: {
				if (!path) {
					saveFile->FileName = "";
					saveFile->ShowDialog();
					if (saveFile->FileName == "") {// не зберігати файл
						return;
					}
					else
						path = saveFile->FileName;//зберігати файл
				}
				break;
			}
			case JSI_SAVE_FILE_AS: {
				saveFile->FileName = "";
				saveFile->ShowDialog();
				if (saveFile->FileName == "")
					return;
				else
					path = saveFile->FileName;
				break;
			}
			default:
				break;
			}
			writer = gcnew IO::StreamWriter(path);
			for (register int i = 0; i < container->Lines->Length; i++)
			{
				writer->WriteLine(container->Lines[i]);
			}
			writer->Close();
			delete writer;
		}
		//Clean container
		void Clear(TextBox ^ container) {
			container->Clear();
			container->Text = "<script language=\"JavaScript\">"+Environment::NewLine;
			container->Text += Environment::NewLine;
			container->Text += "</script>";
		}
		inline void Run(WebBrowser ^ i,TextBox ^ container) {
			SaveFile(container, JSI_SAVE_FILE);
			if (path) {
				i->Navigate(path);
			}
		}
	};
}