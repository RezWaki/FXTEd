#pragma once
#include <msclr\marshal.h>

namespace fxted {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for search
	/// </summary>
	public ref class search : public System::Windows::Forms::Form {
	private:
		INT iLastFound;
		HWND hWnd;
	public:
		search( void ) {
			InitializeComponent();
			iLastFound = 0;
			hWnd = (HWND)this->Handle.ToPointer();
		}
	private: System::Windows::Forms::Label^  label1;
	public: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	public:	 RichTextBox^ text;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~search()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Find what:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(77, 6);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(268, 20);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(90, 32);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(255, 20);
			this->textBox2->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Replace with:";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(15, 58);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Replace";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &search::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(270, 58);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Find";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &search::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(96, 58);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Replace all";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &search::button3_Click);
			// 
			// search
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(357, 86);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"search";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Search";
			this->TopMost = true;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 char szMsg[256];

				 if( iLastFound < 0 ) iLastFound = 0;
				 iLastFound = text->Find( textBox1->Text, iLastFound, text->Text->Length, RichTextBoxFinds::None );
				 if( iLastFound < 0 ) {
					 sprintf( szMsg, "Couldn't find %s", (char*)Marshal::StringToHGlobalAnsi(textBox1->Text).ToPointer() );
					 MessageBoxA( hWnd, szMsg, "Error", MB_ICONERROR );
					 return;
				 }

				 text->Select( iLastFound, textBox1->Text->Length );
				 iLastFound += textBox1->Text->Length;
				 text->Focus();
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 char szMsg[256];

			 if( iLastFound >= text->Text->Length-textBox1->Text->Length || iLastFound < 0 ) iLastFound = 0;
			 iLastFound = text->Find( textBox1->Text, iLastFound, text->Text->Length, RichTextBoxFinds::None );
			 if( iLastFound < 0 ) {
				 sprintf( szMsg, "Couldn't find %s to replace", (char*)Marshal::StringToHGlobalAnsi(textBox1->Text).ToPointer() );
				 MessageBoxA( hWnd, szMsg, "Error", MB_ICONERROR );
				 return;
			 }

			 text->Text = text->Text->Remove( iLastFound, textBox1->Text->Length );
			 text->Text = text->Text->Insert( iLastFound, textBox2->Text );
			 text->Select( iLastFound, textBox1->Text->Length );
			 iLastFound += textBox1->Text->Length;
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 text->Text = text->Text->Replace( textBox1->Text, textBox2->Text );
		 }
};
}